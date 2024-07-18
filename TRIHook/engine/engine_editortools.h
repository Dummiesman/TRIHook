#pragma once
#include <engine\editortools\CEditorTools.h>
#include <engine\editortools\CPickList.h>

#if defined(TRIHOOK_GAME_EVO)
static hook::Type<CEditorTools*> gEdTools = 0x5F81C0;
#elif defined(TRIHOOK_GAME_EVO2)
static hook::Type<CEditorTools*> gEdTools = 0x671750;
#elif defined(TRIHOOK_GAME_EVO_ED)
static hook::Type<CEditorTools*> gEdTools = 0x669A70;
#endif