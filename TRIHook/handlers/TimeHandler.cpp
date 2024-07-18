#include "TimeHandler.h"

bool TimeHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2 || gameType == GameType::Game_EVO_ED;
}

void TimeHandler::Install(GameType gameType)
{
    // something is wrong with the way EVO uses QueryPerformanceCounter and QueryPerformanceFrequency
    // force the game into the "useLegacyTime" branch, which uses timeGetTime()
    // change JNZ into JMP
    if (gameType == GameType::Game_EVO)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x59BA88, 0XE9, 0xC9, 0x01, 0x00, 0x00, 0x90);
    }
    else if (gameType == GameType::Game_EVO2)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x60ADE8, 0XE9, 0xC9, 0x01, 0x00, 0x00, 0x90);
    }
    else if (gameType == GameType::Game_EVO_ED)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x5F4A78, 0XE9, 0xC9, 0x01, 0x00, 0x00, 0x90);
    }
}
