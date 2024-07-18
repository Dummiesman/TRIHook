#include "EVOConfigSkipHandler.h"

void EVOConfigSkipHandler::goToMenu()
{
}

bool EVOConfigSkipHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2 || gameType == GameType::Game_EVO_ED;
}

void EVOConfigSkipHandler::Install(GameType gameType)
{
    if (gameType == GameType::Game_EVO)
    {
        //InstallCallback("getVideoMemory",
        //    &goToMenu, {
        //        cb::call(0x47CA08),
        //    }
        //);
    }
    else if (gameType == GameType::Game_EVO_ED)
    {
        //InstallCallback("getVideoMemory",
        //    &getVideoMemory, {
        //        cb::call(0x4BC14D),
        //    }
        //);
    }
    else if (gameType == GameType::Game_EVO2)
    {
        //InstallCallback("getVideoMemory",
        //    &getVideoMemory, {
        //        cb::call(0x4BC14D),
        //    }
        //);
    }
}
