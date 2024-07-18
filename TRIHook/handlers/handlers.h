#pragma once
#include <trihook\trihook.h>
#include "CallbacksHandler.h"
#include "TestHooks.h"
#include "PODHandler.h"
#include "FPSLimitHandler.h"
#include "TimeHandler.h"
#include "EVOMiscPatchHandler.h"
#include "OutputHandler.h"
#include "EVOSoundHandler.h"
#include "EVOMasterServerHandler.h"
#include "EVOInputPatchHandler.h"
#include "EVOWidescreenHandler.h"

static void InstallHandlers()
{
    TRIHookInstallHandler<OutputHandler>("OutputHandler");
    TRIHookInstallHandler<CallbacksHandler>("CallbacksHandler");
    TRIHookInstallHandler<PODHandler>("PODHandler");
    TRIHookInstallHandler<FPSLimitHandler>("FPSLimitHandler");
    TRIHookInstallHandler<TimeHandler>("TimeHandler");
    TRIHookInstallHandler<EVOMiscPatchHandler>("EVO Misc Patches");
    TRIHookInstallHandler<EVOInputPatchHandler>("EVO Input Patches");
    TRIHookInstallHandler<EVOSoundHandler>("EVO Sound Dev List Expansion");
    TRIHookInstallHandler<EVOMasterServerHandler>("EVO Master Server Override");
    TRIHookInstallHandler<TestHooks>("Test Hooks");
    TRIHookInstallHandler<EVOWidescreenHandler>("Widescreen Patches");
}
