#include "Rosewood.h"

#include "Shared/Common.h"

const std::string Rosewood::FileSystem::ProjectRoot = "../../../Game/Server/";

// namespace Game
// {
//     class Server : public Rosewood::ServerInterface<GameMessages>
//     {

//     };
// }

int main()
{
    // Game::Server server(25565, true);
    // server.InitSSL(Rosewood::FileSystem::GetPath("certificate.crt"), Rosewood::FileSystem::GetPath("key.key"));
    // server.Start();
    #ifdef RW_NETWORKING_ENABLED
    RW_INFO("PENIS");
    #endif

    // while (1)
	// {
	// 	server.Update(-1, true);
	// }
    return 0;
}