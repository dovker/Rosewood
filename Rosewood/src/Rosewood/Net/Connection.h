#pragma once

#include "Networking.h"
#include "Message.h"
#include "Rosewood/Data/TSQueue.h"

namespace Rosewood
{
    template <typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>>
    {
    public:
        enum class Owner
        {
            Server,
            Client
        }
        Connection(Owner parent, asio::io_context& asioContext, asio::ip::tcp::socket socket, TSQueue<OwnedMessage<T>>& qIn)
            : m_AsioContext(asioContext), m_Socket(socket), m_MessageInQueue(qIn)
        {
            m_OwnerType = parent;
        }
        virtual ~Connection() {}

        uint32_t GetID() const
        {
            return m_ID;
        }

        bool ConnectToServer(uint32_t uid = 0)
        {
            if(m_OwnerType == Owner::Server)
            {
                if(m_Socket.is_open())
                {
                    m_ID = uid;
                }
            }
        }
        bool ConnectToServer();
        bool Disconnect();
        bool IsConnected() const
        {
            return m_Socket.is_open();
        }

        bool Send(const Message<T>& msg);
    
    private:  
        //ASYNC
        void ReadHeader()
        {

        }
        //ASYNC
        void ReadBody()
        {

        }
        //ASYNC
        void WriteHeader()
        {

        }
        //ASYNC
        void WriteBody()
        {

        }

    protected:
        //TODO: ADD TCP TO CONNECTION
        asio::ip::tcp::socket m_Socket;

        asio::io_context& m_AsioContext;

        TSQueue<Message<T>> m_MessageOutQueue;

        TSQueue<OwnedMessage<T>>& m_MessageInQueue;

        Owner m_OwnerType = Owner::Server;
        uint32_t m_ID = 0;
    }
}