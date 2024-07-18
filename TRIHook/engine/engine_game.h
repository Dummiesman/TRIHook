#pragma once
#include <trihook/trihook.h>
#include "game/Game.h"

static void renderGameScreen(float a1)
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x44DD70>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x45FE60>;
#endif
    func::Call<void>(a1);
}