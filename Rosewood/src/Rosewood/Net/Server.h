#pragma once

#include "Networking.h"
#include "Message.h"
#include "Rosewood/Data/TSQueue.h"
#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    template <typename T>
    class ServerInterface
    {
    public:
        ServerInterface(uint16_t port, bool secure = false)
            : m_AsioAcceptor(m_AsioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), m_AsioSSLContext(asio::ssl::context::sslv23), m_SecureServer(secure)
        {}
        virtual ~ServerInterface() 
        { 
            Stop();
        }

        //MUST BE CALLED BEFORE STARTING THE SERVER
        void InitSSL(const std::string& certPath, const std::string& keyFile)
        {
            m_AsioSSLContext.set_options(
                asio::ssl::context::default_workarounds
                | asio::ssl::context::no_sslv2
                | asio::ssl::context::single_dh_use);
            m_AsioSSLContext.use_certificate(certPath);
            m_AsioSSLContext.use_private_key_file(keyFile, asio::ssl::context::pem);
        }

        bool Start() 
        { 
            try
            {
                WaitForClientConnection();

                m_ThreadContext = std::thread([this]() { m_AsioContext.run(); });
            }
            catch (std::exception& e)
            {
                RW_CORE_ERROR("[SERVER] Exception: {0}", e.what());
                return false;
            }
            RW_CORE_INFO("[SERVER] Started");
            return true;
        }
        bool Stop() 
        { 
            m_AsioContext.stop();

            if(m_ThreadContext.joinable())
                m_ThreadContext.join();
            RW_CORE_INFO("[SERVER] Stopped");
        }

        //ASYNC
        void WaitForClientConnection()
        {
            m_AsioAcceptor.async_accept([this](std::error_code ec, asio::ssl::stream<asio::ip::tcp::socket> socket)
            {
                if(!ec)
                {
                    RW_CORE_INFO("[SERVER] New connection: ", socket.lowest_layer().remote_endpoint());
                    
                    Ref<Connection<T>> newConnection = CreateRef<Connection<T>>(Connection<T>::Owner::Server, m_AsioContext, m_AsioSSLContext, std::move(socket), m_MessageInQueue, m_SecureServer);
                    if(OnClientConnect(newConnection))
                    {
                        m_Connections.push_back(std::move(newConnection));

                        m_Connections.back()->ConnectToClient(this, m_IDCounter++);
                        
                        RW_CORE_INFO("[{0}] Connection Approved.", m_Connections.back()->GetID());
                    }
                    else
                    {
                        RW_CORE_INFO("[_____] Connection Denied");
                    }
                }
                else
                {
                    RW_CORE_ERROR("[SERVER] New connection Error: {0}", ec.message());
                }

                WaitForClientConnection();
            });
        }
        void MessageClient(Ref<Connection<T>> client, const Message<T>& message)
        {
            if(client && client->IsConnected())
            {
                client->Send(message);
            }
            else
            {
                OnClientDisconnect(client);
                client.reset();
                m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), client), m_Connections.end());
            }
        }
        void MessageAllClients(const Message<T>& message, Ref<Connection<T>> ignoreClient = nullptr)
        {
            bool invalidClientExists = false;
            for(auto& client : m_Connections)
            {
                if(client && client->IsConnected())
                {
                    if(client != ignoreClient)
                        client->Send(message);
                }
                else
                {
                    OnClientDisconnect(client);
                    client.reset();
                    invalidClientExists = true;
                }
            }
            if(invalidClientExists)
            {
                m_Connections.erase(std::remove(m_Connections.begin(), m_Connections.end(), nullptr), m_Connections.end());
            }
        }

        void Update(size_t maxMessages = -1, bool wait = false)
        {
            if(wait) m_MessageInQueue.Wait();
            size_t messageCount = 0;
            while(messageCount < maxMessages && !m_MessageInQueue.empty())
            {
                auto msg = m_MessageInQueue.PopFront();
                OnMessage(msg.Remote, msg.Msg);

                messageCount++;
            }
        }
    protected:
        virtual bool OnClientConnect(Ref<Connection<T>> client)
        {
            return false;
        }
        virtual void OnClientDisconnect(Ref<Connection<T>> client)
        {

        }
        virtual void OnMessage(Ref<Connection<T>> client, Message<T> message)
        {

        }
        virtual void OnClientValidated(Ref<Connection<T>> client)
        {

        }
        TSQueue<OwnedMessage<T>> m_MessageInQueue;
        std::deque<Ref<Connection<T>>> m_Connections;

        asio::io_context m_AsioContext;
        asio::ssl::context m_AsioSSLContext;
        std::thread m_ThreadContext;

        asio::ip::tcp::acceptor m_AsioAcceptor;

        uint32_t m_IDCounter = 0;

        bool m_SecureServer = false;
    };
}