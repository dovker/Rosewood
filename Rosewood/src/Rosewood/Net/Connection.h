#pragma once

#include "Networking.h"
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

        Connection(Owner parent, asio::io_context& asioContext, asio::ssl::stream<asio::ip::tcp::socket> socket, TSQueue<OwnedMessage<T>>& qIn, bool ssl = false);

        virtual ~Connection() {}

        uint32_t GetID() const
        {
            return m_ID;
        }

        void ConnectToClient(ServerInterface<T>* server = nullptr, uint32_t uid = 0);
        void ConnectToServer(const asio::ip::tcp::resolver::results_type& endPoints);
        void HandleSSLHandshake(ServerInterface<T>* server = nullptr);
        bool Disconnect();
        bool IsConnected();
        bool Send(const Message<T>& msg);
    private:  
        //ASYNC
        void ReadHeader();
        //ASYNC
        void ReadBody();
        //ASYNC
        void WriteHeader();
        //ASYNC
        void WriteBody();
        //ASYNC
        void ReadValidation(ServerInterface<T>* server = nullptr);
        //ASYNC
        void WriteValidation();

        void AddToIncomingMessageQueue();

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