#pragma once

namespace Game
{
    enum class GameMessages : uint32_t
    {
        Server_GetStatus,
        Server_GetPing,

        Client_Accepted,
        Client_AssignID,
        Client_RegisterWithServer,
        Client_UnregisterWithServer,

        Game_AddPlayer,
        Game_RemovePlayer,
        Game_UpdatePlayer,

        Misc_Hello,
    };
}