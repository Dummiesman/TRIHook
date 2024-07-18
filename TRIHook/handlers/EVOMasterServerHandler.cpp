#include "EVOMasterServerHandler.h"

char masterServer[256];

bool EVOMasterServerHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2;
}

// EVO1
void getMasterServerFilePrefix(char* buf)
{
    hook::StaticThunk<0x4C5110>::Call<void>(buf);
}

void EVOMasterServerHandler::Install(GameType gameType)
{
    auto overrideMasterServer = HookConfig::GetString("Multiplayer", "MasterServer", nullptr);
    if (overrideMasterServer != nullptr)
    {
        if (gameType == GameType::Game_EVO2)
        {
            sprintf_s(masterServer, ".%s/evo2-backend.txt", overrideMasterServer);
            mem::write(0x4E0E88 + 1, &masterServer);
        }
        else if (gameType == GameType::Game_EVO)
        {
            char filePrefixBuf[256];
            getMasterServerFilePrefix(filePrefixBuf);
            sprintf_s(masterServer, ".%s/%s-backend.txt", overrideMasterServer, filePrefixBuf);
            mem::write(0x4C7E50 + 1, &masterServer);
        }
        hook_output("[MULTIPLAYER] Master server: %s", masterServer);
    }
}
