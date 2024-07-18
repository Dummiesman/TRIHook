#pragma once
#include <trihook/trihook.h>
#include "engine_common.h"
#if defined(TRIHOOK_GAME_EVO)
static void setGravity(float gravity)
{
    mem::write<float>(0x5D726D, gravity);
    mem::write<float>(0x5D7291, gravity);
    mem::write<float>(0x5D7319, gravity);
    mem::write<float>(0x5D7221, gravity);
    mem::write<float>(0x5D7149, gravity);
    mem::write<float>(0x5D7059, gravity);
    mem::write<float>(0x5D7029, gravity);
    mem::write<float>(0x5D6E8D, gravity);
}
#elif defined(TRIHOOK_GAME_EVO2)
static void setGravity(float gravity)
{
    // gravity for everything
    mem::write<float>(0x6302FD, gravity);
    mem::write<float>(0x64A3CA, gravity);
    mem::write<float>(0x64A532, gravity);
    mem::write<float>(0x64A694, gravity);
    mem::write<float>(0x64A6B8, gravity);
    mem::write<float>(0x64A6D8, gravity);
    mem::write<float>(0x64B3A7, gravity);
    mem::write<float>(0x65F070, gravity);

    // gravity for vehicle main
    mem::write<float>(0x64B3AB, gravity * 1.75f);
}
#endif
