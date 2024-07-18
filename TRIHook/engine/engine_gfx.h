#pragma once
#include <ddraw.h>

#if defined(TRIHOOK_GAME_EVO)
static hook::Type<int> gamePIXX = 0x5F9424;
static hook::Type<int> gamePIXY = 0x5F9428;
static hook::Type<int> gameBPP = 0x5F942C;

static hook::Type<int> PIXX = 0x5F8AC0;
static hook::Type<int> PIXY = 0x5F8AC4;

static hook::Type<int> bitsPerPixel = 0x5F8AC8;

static BOOL setScreenResolution(int resX, int resY, int bpp)
{
    return hook::StaticThunk<0x596B40>::Call<BOOL>(resX, resY, bpp);
}
#elif defined(TRIHOOK_GAME_EVO_ED)
static hook::Type<int> gamePIXX = 0x66C0A4;
static hook::Type<int> gamePIXY = 0x66C0A8;

static hook::Type<int> PIXX = 0x66A320;
static hook::Type<int> PIXY = 0x66A324;

static hook::Type<int> bitsPerPixel = 0x66A328;
#elif defined(TRIHOOK_GAME_EVO2)
static hook::Type<int> gamePIXX = 0x672A68;
static hook::Type<int> gamePIXY = 0x672A6C;
static hook::Type<int> gameBPP = 0x672A70;

static hook::Type<int> PIXX = 0x672040;
static hook::Type<int> PIXY = 0x672044;

static hook::Type<int> bitsPerPixel = 0x672048;

static BOOL setScreenResolution(int resX, int resY, int bpp)
{
    return hook::StaticThunk<0x601CC0>::Call<BOOL>(resX, resY, bpp);
}
#endif