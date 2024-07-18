#pragma once
#include <engine\font\CBitFont.h>
#include <engine\font\CFont.h>

#if defined(TRIHOOK_GAME_EVO)
static hook::Type<CBitFont*> gSmallLCDFont = 0xB065E8;
static hook::Type<CBitFont*> gSmallFont = 0xB065EC;
static hook::Type<CBitFont*> gMediumFont = 0xB065F0;
static hook::Type<CBitFont*> gLargeFont = 0xB065F4;
static hook::Type<CBitFont*> gEPfont = 0xB065F8;
static hook::Type<CBitFont*> gMediumOSFont = 0xB065FC;

static hook::Type<CBitFont*> gEdFont = 0x71AF90;
#elif defined(TRIHOOK_GAME_EVO2)
static hook::Type<CBitFont*> gSmallLCDFont = 0xAE8678;
static hook::Type<CBitFont*> gSmallFont = 0xAE867C;
static hook::Type<CBitFont*> gMediumFont = 0xAE8680;
static hook::Type<CBitFont*> gLargeFont = 0xAE8684;
static hook::Type<CBitFont*> gEPfont = 0xAE8688;
static hook::Type<CBitFont*> gMediumOSFont = 0xAE868C;

static hook::Type<CBitFont*> gEdFont = 0x813380;
#endif