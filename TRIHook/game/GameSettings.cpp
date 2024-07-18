#include "GameSettings.h"

#if defined(TRIHOOK_GAME_EVO2)
declfield(GameSettings::gLanguage)(0x6742CC);
#endif

LPCSTR GameSettings::GetLanguage()
{
#if defined(TRIHOOK_GAME_EVO2)
    return GameSettings::gLanguage.get();
#else
    return "ENG";
#endif
}
