#pragma once
#include "trihook_defs.h"
#include "trihook_util.h"
#include "framework/hook_framework.h"

template <typename THandler>
static void TRIHookInstallHandler(const char* name) {
    bool gSupport = THandler::IsGameSupported(GAME_TYPE);
    if (gSupport)
    {
        static void(*lpInstall)(GameType) = &THandler::Install;
        lpInstall(GAME_TYPE);
    }
}