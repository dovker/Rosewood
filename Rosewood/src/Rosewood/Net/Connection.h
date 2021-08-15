#pragma once

#include "rwpch.h"

#include "Message.h"
#include "Rosewood/Data/TSQueue.h"

namespace Rosewood
{
    template <typename T>
    class ServerInterface;

    template <typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>>
    {
    public:
        enum class Owner
        {
            Server,
            Client
        };

        Connection(Owner parent, asio::io_context& asioContext, asio::ssl::context& sslContext, asio::ssl::stream<asio::ip::tcp::socket> socket, TSQueue<OwnedMessage<T>>& qIn, bool ssl = false)
            : m_AsioContext(asioContext), m_AsioSSLContext(sslContext), m_Socket(std::move(socket)), m_MessageInQueue(qIn), m_Secure(ssl)
        {
            m_OwnerType = parent;

            if(m_OwnerType == Owner::Server)
            {
                m_HandshakeOut = uint64_t(std::chrono::system_clock::now().time_since_epoch().count());

                m_HandshakeCheck = Scramble(m_HandshakeOut);
            }
            else
            {
                m_HandshakeOut = 0;
                m_HandshakeIn = 0;
            }
        }

        virtual ~Connection() {}

        uint32_t GetID() const
        {
            return m_ID;
        }

        void ConnectToClient(ServerInterface<T>* server = nullptr, uint32_t uid = 0)
        {
            if(m_OwnerType == Owner::Server)
            {
                if(IsConnected())
                {
                    m_ID = uid;
                    if(m_Secure)
                    {
                        HandleSSLHandshake(server);
                    }
                    else
                    {
                        WriteValidation();
                        ReadValidation(server);
                    }
                }
            }
        }

        void ConnectToServer(const asio::ip::tcp::resolver::results_type& endPoints)
        {
            if(m_OwnerType == Owner::Client)
            {
                asio::async_connect(m_Socket.lowest_layer(), endPoints,
                [this](std::error_code ec, asio::ip::tcp::endpoint endpoint)
                {
                    if(!ec)
                    {
                        if(m_Secure)
                        {
                            HandleSSLHandshake();
                        }
                        else
                        {
                            ReadValidation();
                        }
                    }
                });
            }
            else
            {
                //Do Other connection
            }
        }
        void HandleSSLHandshake(ServerInterface<T>* server = nullptr)
        {
            if(m_OwnerType == Owner::Server)
            {
                m_Socket.async_handshake(asio::ssl::stream_base::server, [this, server](std::error_code ec)
                {
                    if(!ec)
                    {
                        WriteValidation();
                        ReadValidation(server);
                    }
                    else
                    {
                        RW_CORE_ERROR("Server side SSL Handshake failed.");
                        CloseSocket();
                    }
                });
            }
            else
            {
                m_Socket.async_handshake(asio::ssl::stream_base::client, [this](std::error_code ec)
                {
                    if(!ec)
                    {
                        ReadValidation();
                    }
                    else
                    {
                        RW_CORE_ERROR("Client side SSL Handshake failed.");
                        CloseSocket();
                    }
                });
            }
        }

        bool Disconnect()
        {
            asio::post(m_AsioContext, [this]() { CloseSocket(); });
        }

        bool IsConnected()
        {
            return m_Socket.lowest_layer().is_open();
        }

        bool Send(const Message<T>& msg)
        {
            asio::post(m_AsioContext, [this, msg]()
            {
                bool writingMessage = !m_MessageOutQueue.Empty();
                m_MessageOutQueue.PushBack(msg);
                if(!writingMessage)
                    WriteHeader();
            });
        }
    private:  
        void CloseSocket()
        {
            m_Socket.lowest_layer().close();
        }
        //ASYNC
        void ReadHeader()
        {
            auto fn = [this](std::error_code ec, std::size_t length)
                    {
                        if(!ec)
                        {
                            if(m_TempMessageIn.Header.Size > 0)
                            {
                                m_TempMessageIn.Data.resize(m_TempMessageIn.Header.Size);
                                ReadBody();
                            }
                            else
                            {
                                AddToIncomingMessageQueue();
                            }
                        }
                        else
                        {
                            RW_CORE_ERROR("[{0}] Read Header fail.", m_ID);
                            CloseSocket();
                        }
                    };
            if(m_Secure) //TODO: FIX THIS NONSENSE
                asio::async_read(m_Socket, asio::buffer(&m_TempMessageIn.Header, sizeof(MessageHeader<T>)), fn);
            else
                m_Socket.next_layer().async_read_some(asio::buffer(&m_TempMessageIn.Header, sizeof(MessageHeader<T>)), fn);
        }
        //ASYNC
        void ReadBody()
        {
            auto fn = [this](std::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        AddToIncomingMessageQueue();
                    }
                    else
                    {
                        RW_CORE_ERROR("[{0}] Read Body fail.", m_ID);
                        CloseSocket();
                    }
                };
            if(m_Secure)
                asio::async_read(m_Socket, asio::buffer(m_TempMessageIn.Data.data(), m_TempMessageIn.Header.Size), fn);
            else
                m_Socket.next_layer().async_read_some(asio::buffer(m_TempMessageIn.Data.data(), m_TempMessageIn.Header.Size), fn);
        }
        //ASYNC
        void WriteHeader()
        {
            auto fn = [this](std::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        if(m_TempMessageIn.Front().Header.Size > 0)
                        {
                            WriteBody();
                        }
                        else
                        {
                            m_MessageOutQueue.PopFront();
                            if(!m_MessageOutQueue.Empty())
                            {
                                WriteHeader();
                            }
                        }
                    }
                    else
                    {
                        RW_CORE_ERROR("[{0}] Write Header fail.", m_ID);
                        CloseSocket();
                    }
                };
            if(m_Secure)
                asio::async_write(m_Socket, asio::buffer(&m_MessageOutQueue.Front().Header, sizeof(MessageHeader<T>)), fn);
            else
                asio::async_write(m_Socket.next_layer(), asio::buffer(&m_MessageOutQueue.Front().Header, sizeof(MessageHeader<T>)), fn);

        }
        //ASYNC
        void WriteBody()
        {
            auto fn = [this](std::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        m_MessageOutQueue.PopFront();
                        if(!m_MessageOutQueue.Empty())
                        {
                            WriteHeader();
                        }
                    }
                    else
                    {
                        RW_CORE_ERROR("[{0}] Write Body fail.", m_ID);
                        CloseSocket();
                    }
                };
            if(m_Secure)
                asio::async_write(m_Socket, asio::buffer(&m_MessageOutQueue.Front().Body.Data, m_MessageOutQueue.Front().Header.Size), fn);
            else
                asio::async_write(m_Socket.next_layer(), asio::buffer(&m_MessageOutQueue.Front().Body.Data, m_MessageOutQueue.Front().Header.Size), fn);
        }
        //ASYNC
        void ReadValidation(ServerInterface<T>* server = nullptr)
        {
            auto fn = [this, server](std::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        if(m_OwnerType == Owner::Server)
                        {
                            if(m_HandshakeIn == m_HandshakeCheck)
                            {
                                RW_CORE_INFO("Connection Approved.");
                                server->OnClientValidated(this->shared_from_this());

                                ReadHeader();
                            }
                            else
                            {
                                RW_CORE_ERROR("Client Disconnected (Failed validation)");
                                CloseSocket();
                            }
                        }
                        else
                        {
                            m_HandshakeOut = Scramble(m_HandshakeIn);
                            WriteValidation();
                        }
                    }
                    else
                    {
                        RW_CORE_ERROR("Client Disconnected (Failed validation)");
                        CloseSocket();
                    }
                };
            if(m_Secure)
                asio::async_read(m_Socket, asio::buffer(&m_HandshakeIn, sizeof(uint64_t)), fn);
            else
                m_Socket.next_layer().async_read_some(asio::buffer(&m_HandshakeIn, sizeof(uint64_t)), fn);
        }
        //ASYNC
        void WriteValidation()
        {
            auto fn = [this](std::error_code ec, std::size_t length)
                {
                    if(!ec)
                    {
                        if(m_OwnerType == Owner::Client)
                        {
                            ReadHeader();
                        }
                    }
                    else
                    {
                        CloseSocket();
                    }
                };
            if(m_Secure)
                asio::async_write(m_Socket, asio::buffer(&m_HandshakeOut, sizeof(uint64_t)), fn);
            else
                asio::async_write(m_Socket.next_layer(), asio::buffer(&m_HandshakeOut, sizeof(uint64_t)), fn);
        }

        void AddToIncomingMessageQueue()
        {
            if(m_OwnerType == Owner::Server)
            {
                m_MessageInQueue.PushBack({this->shared_from_this(), m_TempMessageIn});
            }
            else
            {
                m_MessageInQueue.PushBack({nullptr, m_TempMessageIn});
            }
            ReadHeader();
        }

        uint64_t Scramble(uint64_t input)
        {
            uint64_t out = input ^ 0x1DFF4DAAFF12ABCE;
            out = (out & 0xFFFFAAAA0000AAAA) >> 4 | (out & 0xF99FABBA0110ABBA) << 4;
            return out ^ 0XCCDA9790DDFFB15A; //ADD VERSION NUMBER
        }

    protected:
        //TODO: ADD UDP TO CONNECTION
        asio::ssl::stream<asio::ip::tcp::socket> m_Socket;

        asio::io_context& m_AsioContext;
        asio::ssl::context& m_AsioSSLContext;

        TSQueue<Message<T>> m_MessageOutQueue;
        Message<T> m_TempMessageIn;
        TSQueue<OwnedMessage<T>>& m_MessageInQueue;

        Owner m_OwnerType = Owner::Server;
        uint32_t m_ID = 0;

        uint64_t m_HandshakeIn = 0;
        uint64_t m_HandshakeOut = 0;
        uint64_t m_HandshakeCheck = 0;

        bool m_Secure = false;
    };
}
