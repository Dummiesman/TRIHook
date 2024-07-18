#pragma once
#include <trihook/trihook.h>

class GameSettings
{
private:
#if defined(TRIHOOK_GAME_EVO2)
    static hook::Type<LPCSTR> gLanguage;
#endif
public:
    static LPCSTR GetLanguage();
};

