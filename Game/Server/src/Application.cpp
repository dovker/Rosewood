#include "Rosewood.h"

#include "Shared/Common.h"

const std::string Rosewood::FileSystem::ProjectRoot = "../../../Game/Server/";

namespace Game
{
    class Server : public Rosewood::ServerInterface<GameMessages>
    {
    public:
        Server(uint16_t port, bool secure = false)
            : Rosewood::ServerInterface<GameMessages>(port, secure)
        {
            
        }
    protected:
        bool OnClientConnect(Rosewood::Ref<Rosewood::Connection<GameMessages>> client) override
        {
            
            return true;
        }

        void OnMessage(Rosewood::Ref<Rosewood::Connection<GameMessages>> client, Rosewood::Message<GameMessages> message) override
        {
            std::cout<<'\n';
            RW_CORE_INFO("Message Data: {0}, {1}", message.Header.Size, message.Header.Id);
            switch (message.Header.Id)
            {
                case GameMessages::Misc_Hello:
                {
                    //char str[256];
                    uint32_t integer;
                    message >> integer;
                    RW_INFO("Received a message from client {0}: {1}", client->GetID(), integer);
                    
                    break;
                }
                case GameMessages::Server_GetPing:
                {
                    uint64_t integer;
                    message >> integer;
                    RW_INFO("Received a notification from client {0}: {1}", client->GetID(), integer);
                    
                    break;
                }
            }
        }
    };

}

int main()
{
    Rosewood::Log::Init();

    Game::Server server(60023, true);
    server.InitSSL(Rosewood::FileSystem::GetPath("certificate.crt"), Rosewood::FileSystem::GetPath("key.key"));
    server.Start();

    while (1)
	{
		server.Update(-1, true);
	}
    return 0;
}
