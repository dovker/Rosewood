#include "rwpch.h"

#ifdef RW_NETWORKING_ENABLED
#include "Connection.h"

namespace Rosewood
{
    template <typename T>
    Connection<T>::Connection(Owner parent, asio::io_context& asioContext, asio::ssl::stream<asio::ip::tcp::socket> socket, TSQueue<OwnedMessage<T>>& qIn, bool ssl)
        : m_AsioContext(asioContext), m_Socket(std::move(socket)), m_MessageInQueue(qIn), m_Secure(ssl)
    {
        m_OwnerType = parent;
        //Maybe do like m_Socket.lowest_layer() = socket

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

    template <typename T>
    void Connection<T>::ConnectToClient(ServerInterface<T>* server, uint32_t uid)
    {
        if(m_OwnerType == Owner::Server)
        {
            if(m_Socket.lowest_layer().is_open())
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
    template <typename T>
    void Connection<T>::ConnectToServer(const asio::ip::tcp::resolver::results_type& endPoints)
    {
        if(m_OwnerType == Owner::Client)
        {
            asio::async_connect(m_Socket, endPoints,
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
    }

    template <typename T>
    void Connection<T>::HandleSSLHandshake(ServerInterface<T>* server)
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
                    m_Socket.lowest_layer().close();
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
                    m_Socket.lowest_layer().close();
                }
            });
        }
    }

    template <typename T>
    bool Connection<T>::Disconnect()
    {
        asio::post(m_AsioContext, [this]() { m_Socket.lowest_layer().close(); });
    }

    template <typename T>
    bool Connection<T>::IsConnected() 
    {
        return m_Socket.lowest_layer().is_open();
    }

    template <typename T>
    bool Connection<T>::Send(const Message<T>& msg)
    {
        asio::post(m_AsioContext, [this, msg]()
        {
            bool writingMessage = !m_MessageOutQueue.Empty();
            m_MessageOutQueue.PushBack(msg);
            if(!writingMessage)
                WriteHeader();
        });
    }

    template <typename T>
    void Connection<T>::ReadValidation(ServerInterface<T>* server)
    {
        asio::async_read(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(&m_HandshakeIn, sizeof(uint64_t)), 
            [this, server](std::error_code ec, std::size_t length)
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
                            m_Socket.lowest_layer().close();
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
                    m_Socket.lowest_layer().close();
                }
            });
    }


    template <typename T>
    void Connection<T>::WriteValidation()
    {
        asio::async_write(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(&m_HandshakeOut, sizeof(uint64_t)), 
            [this](std::error_code ec, std::size_t length)
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
                    m_Socket.lowest_layer().close();
                }
            });
    }

    //ASYNC
    template <typename T>
    void Connection<T>::ReadHeader()
    {
        asio::async_read(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(&m_TempMessageIn.Header, sizeof(MessageHeader<T>)), 
            [this](std::error_code ec, std::size_t length)
            {
                if(!ec)
                {
                    if(m_TempMessageIn.Header.Size > 0)
                    {
                        m_TempMessageIn.Body.Resize(m_TempMessageIn.Header.Size);
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
                    m_Socket.lowest_layer().close();
                }
            });
    }
    //ASYNC
    template <typename T>
    void Connection<T>::ReadBody()
    {
        asio::async_read(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(m_TempMessageIn.Body.Data, m_TempMessageIn.Header.Size), 
            [this](std::error_code ec, std::size_t length)
            {
                if(!ec)
                {
                    AddToIncomingMessageQueue();
                }
                else
                {
                    RW_CORE_ERROR("[{0}] Read Body fail.", m_ID);
                    m_Socket.lowest_layer().close();
                }
            });
    }
    //ASYNC
    template <typename T>
    void Connection<T>::WriteHeader()
    {
        asio::async_write(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(&m_MessageOutQueue.Front().Header, sizeof(MessageHeader<T>)), 
            [this](std::error_code ec, std::size_t length)
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
                    m_Socket.lowest_layer().close();
                }
            });
    }
    //ASYNC
    template <typename T>
    void Connection<T>::WriteBody()
    {
        asio::async_write(m_Secure ? m_Socket : m_Socket.lowest_layer(), asio::buffer(&m_MessageOutQueue.Front().Body.Data, m_MessageOutQueue.Front().Header.Size), 
            [this](std::error_code ec, std::size_t length)
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
                    m_Socket.lowest_layer().close();
                }
            });
    }
    template <typename T>
    void Connection<T>::AddToIncomingMessageQueue()
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
}
#endif