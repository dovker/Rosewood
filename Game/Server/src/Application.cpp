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
    };

}

int main()
{
    Rosewood::Log::Init();

    Game::Server server(25567, true);
    server.InitSSL(Rosewood::FileSystem::GetPath("certificate.crt"), Rosewood::FileSystem::GetPath("key.key"));
    server.Start();

    while (1)
	{
		server.Update(-1, true);
	}
    return 0;
}
