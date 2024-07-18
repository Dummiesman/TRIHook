#include "CallbacksHandler.h"

std::vector<void(*)()> CallbacksHandler::postInitCallbacks = {};

void CallbacksHandler::EnginePostInit()
{
    for (auto cb : postInitCallbacks)
    {
        cb();
    }
}

void CallbacksHandler::RegisterEnginePostInitCallback(void(*cb)())
{
    postInitCallbacks.push_back(cb);
}

bool CallbacksHandler::IsGameSupported(GameType gameType)
{
    return true;
}

void CallbacksHandler::Install(GameType gameType)
{
    if (gameType == GameType::Game_EVO)
    {
        InstallCallback("PostInit",
            &EnginePostInit, {
                cb::call(0x47479A),
            }
        );
    }
    else if (gameType == GameType::Game_EVO2)
    {
        InstallCallback("PostInit",
            &EnginePostInit, {
                cb::call(0x48E67E),
            }
        );
    }
}
