#include "FPSLimitHandler.h"
#include <engine/engine_time.h>
#include <engine/engine_game.h>
#include <Windows.h>

uint64_t lastTime;
int frameTimeTarget;

void FPSLimitHandler::LimitFPS() 
{
    uint64_t time = getTime();
    while ((getTime() - lastTime) < frameTimeTarget)
    {
        // wait a little
    }
    lastTime = getTime();
}

void FPSLimitHandler::RenderGameScreen(float a1)
{
    renderGameScreen(a1);
    LimitFPS();
}

void FPSLimitHandler::BaseUI_paintAndProcessOneFrame()
{
    hook::StaticThunk<0x415090>::Call<void>(this);
    LimitFPS();
}

bool FPSLimitHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2;
}

void FPSLimitHandler::Install(GameType gameType)
{
    lastTime = 0;
    frameTimeTarget = HookConfig::GetInt("Rendering", "FrameTimeTarget", 0);
    if (frameTimeTarget == 0)
        return;

    if (gameType == GameType::Game_EVO)
    {
        InstallCallback("renderGameScreen",
            &RenderGameScreen, {
                cb::call(0x431373),
                cb::call(0x43169D),
                cb::call(0x44F6AA),
                cb::call(0x47F972),
            }
        );      
    }
    else if (gameType == GameType::Game_EVO2)
    {
        InstallCallback("renderGameScreen",
            &RenderGameScreen, {
                cb::call(0x4383D1),
                cb::call(0x438700),
                cb::call(0x4638C1),
            }
        );  
        InstallCallback("CBaseUI::paintAndProcessOneFrame",
            &BaseUI_paintAndProcessOneFrame, {
                cb::call(0x55EEFE),
                cb::call(0x494FC1),
            }
        );
    }
}
