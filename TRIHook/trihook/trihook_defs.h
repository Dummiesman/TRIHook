#pragma once
#include <stdint.h>

static const char* PRODUCT_NAME = "TRIHook";

enum GameType {
    Game_Unknown = -1,
    Game_EVO = 2,
    Game_EVO2 = 3,
    Game_EVO_ED = 4
};

#if _DEBUG
#define trihook_assert(cond) if(!(cond)) { MessageBox(NULL, #cond, "Assertion failed", MB_OK | MB_ICONERROR); ExitProcess(EXIT_FAILURE); }
#else
#define trihook_assert(cond) if(!(cond)) { /* empty */ }
#endif

//#define TRIHOOK_ENABLE_INCOMPLETE_FEATURES

//#define TRIHOOK_GAME_EVO
#define TRIHOOK_GAME_EVO2
//#define TRIHOOK_GAME_EVO_ED

#if defined(TRIHOOK_GAME_EVO)
    static const char* GAME_NAME = "4x4 Evo (Build 57)";
    static const uint16_t GAME_CRC = 0x3d52;
    static const GameType GAME_TYPE = GameType::Game_EVO;
#elif defined(TRIHOOK_GAME_EVO2)
    static const char* GAME_NAME = "4x4 Evo 2 (Build 139)";
    static const uint16_t GAME_CRC = 0x7af4;
    static const GameType GAME_TYPE = GameType::Game_EVO2;
#elif defined(TRIHOOK_GAME_EVO_ED)
    static const char* GAME_NAME = "4x4 Evo Editor";
    static const uint16_t GAME_CRC = 0xa372;
    static const GameType GAME_TYPE = GameType::Game_EVO_ED;
#else
    static const char* GAME_NAME = "No Game Defined";
    static const uint16_t GAME_CRC = 0;
    static const GameType GAME_TYPE = GameType::Game_Unknown;
#endif