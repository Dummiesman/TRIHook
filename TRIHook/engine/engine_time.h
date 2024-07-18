#pragma once
#include <trihook/trihook.h>

#define TIME_TO_MS(x) (x) / 1180

static uint32_t getTime()
{
#if defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x60B020>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x5F4CB0>;
#else
    using func = hook::StaticThunk<0x59BCC0>;
#endif
    return func::Call<uint32_t>();
}