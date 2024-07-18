#pragma once
#include <trihook/trihook.h>

#if defined(TRIHOOK_GAME_EVO)
static hook::Type<const char*> gtfoSourceFile = 0xADF6A8;
static hook::Type<int> gtfoSourceLine = 0xADF6AC;

static hook::Func<void> reallyGTFO = 0x473D30;
#elif defined(TRIHOOK_GAME_EVO2)
static hook::Type<const char*> gtfoSourceFile = 0xAA6F78;
static hook::Type<int> gtfoSourceLine = 0xAA6F7C;

static hook::Func<void> reallyGTFO = 0x48DF40;
#endif

#define GTFO(fmt, ...) gtfoSourceLine = __LINE__;\
                       gtfoSourceFile = __FILE__;\
                       reallyGTFO(fmt, __VA_ARGS__);