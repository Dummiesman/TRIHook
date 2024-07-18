#include "Keyboard.h"

#if defined(TRIHOOK_GAME_EVO2)
declfield(Keyboard::keyset)(0x8218E0);
#elif defined(TRIHOOK_GAME_EVO)
declfield(Keyboard::keyset)(0x728850);
#endif

bool Keyboard::checkKeyPressed(byte keycode)
{
#if defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO)
    return keyset.ptr()[keycode];
#else
    return false;
#endif
}

void Keyboard::clearKeyPressed(byte keycode)
{
#if defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO)
    *(keyset.ptr() + keycode) = 0;
#endif
}
