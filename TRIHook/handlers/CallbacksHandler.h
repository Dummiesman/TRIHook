#pragma once
#include <trihook\trihook.h>
#include <vector>

class CallbacksHandler
{
private:
    static std::vector<void(*)()> postInitCallbacks;
private:
    static void EnginePostInit();
public:
    static void RegisterEnginePostInitCallback(void(*cb)());

    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

