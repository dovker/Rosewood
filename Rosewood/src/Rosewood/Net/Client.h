#pragma once

#include "rwpch.h"

#include "Message.h"
#include "Rosewood/Data/TSQueue.h"
#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    template <typename T>
    class ClientInterface
    {
    public:
        ClientInterface(){}
        virtual ~ClientInterface() { Disconnect(); }

        bool Connect(const std::string& host, const uint16_t port, bool ssl, const std::string& certificatePath = "")
        {
            try
            {
                asio::ip::tcp::resolver resolver(m_AsioContext);
                asio::ip::tcp::resolver::results_type endPoints = resolver.resolve(host, std::to_string(port));

                asio::ssl::stream<asio::ip::tcp::socket> sslSocket(m_AsioContext, m_AsioSSLContext);
                //Do the SSL INIT STUFF
                if(ssl)
                {
                    m_AsioSSLContext.load_verify_file(certificatePath);

                    sslSocket.set_verify_mode(asio::ssl::verify_none); //TODO: verify_peer on release
                    sslSocket.set_verify_callback([this](bool preverified, asio::ssl::verify_context& ctx)
                    {
                        char subject_name[256];
                        X509* cert = X509_STORE_CTX_get_current_cert(m_AsioSSLContext.native_handle());
                        X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
                        RW_CORE_INFO("[CLIENT] Verifying: {0}", subject_name);

                        return preverified;
                    });
                }

                m_Connection = CreateRef<Connection<T>>(Connection<T>::Owner::Client, m_AsioContext, std::move(sslSocket), m_MessageInQueue, ssl, certificatePath);

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
        TSQueue<OwnedMessage<T>>& GetIncomingMessages() { return m_MessageInQueue; }
    protected:
        asio::io_context m_AsioContext;
        asio::ssl::context m_AsioSSLContext;

        std::thread m_ThreadContext;

        Ref<Connection<T>> m_Connection;
    private:
        TSQueue<OwnedMessage<T>> m_MessageInQueue;
    };
}