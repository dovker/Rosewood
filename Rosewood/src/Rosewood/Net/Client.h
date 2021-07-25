#pragma once

#include "Networking.h"
#include "Message.h"
#include "Rosewood/Data/TSQueue.h"
#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    template <typename T>
    class ClientInterface
    {
    public:
        ClientInterface() : m_Socket(m_AsioContext) {}
        virtual ~ClientInterface() { Disconnect(); }

        bool Connect(const std::string& host, const uint16_t port)
        {
            try
            {
                m_Connection = CreateRef<Connection<T>>();

                asio::ip::tcp::resolver resolver(m_AsioContext);
                asio::ip::tcp::resolver::results_type endPoints = resolver.resolve(host, std::to_string(port));

                m_Connection->ConnectToServer(endPoints);

                m_ThreadContext = std::thread([this]() { m_AsioContext.run(); });
            }
            catch(const std::exception& e)
            {
                RW_CORE_ERROR("[CLIENT] Exception: {0}", e.what());
                return false;
            }
            
            return true;
        }
        void Disconnect()
        {
            if(IsConnected())
            {
                m_Connection->Disconnect();
            }

            m_AsioContext.stop();

            if(m_ThreadContext.joinable())
                m_ThreadContext.join();

            m_Connection.release();
        }

        bool IsConnected() 
        { 
            if (m_Connection)
                return m_Connection->IsConnected();
            else
                return false;
        }
        TSQueue<OwnedMessage>& GetIncomingMessages() { return m_MessageInQueue; }
    protected:
        asio::io_context m_AsioContext;

        std::thread m_ThreadContext;

        asio::ip::tcp::socket m_Socket;

        Ref<Connection<T>> m_Connection;
    private:
        TSQueue<OwnedMessage> m_MessageInQueue;
    }
}