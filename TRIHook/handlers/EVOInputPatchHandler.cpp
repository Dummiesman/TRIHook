#include "EVOInputPatchHandler.h"

static bool noJoy = false;
static bool ignoreUnknownDevices = true;
static bool ignoreAllDevices = false;
static int eRes = 0;

static bool IsNoJoyDevice(LPCDIDEVICEINSTANCEA lpDev)
{
    return (lpDev->dwDevType == 258 && !strcmp(lpDev->tszProductName, "Mouse")) ||
           (lpDev->dwDevType == 1027 && !strcmp(lpDev->tszProductName, "Keyboard"));
}

static bool CheckShouldSkip(LPCDIDEVICEINSTANCEA lpDev)
{
    if (ignoreAllDevices)
    {
        hook_output("--> skipping: ignore all devices specified");
        return true;
    }

    if (noJoy && !IsNoJoyDevice(lpDev))
    {
        hook_output("--> skipping: joystick support disabled.");
        return true;
    }

    int deviceClass = lpDev->dwDevType & 0x000000FF;
    if (deviceClass == DIDEVTYPE_DEVICE && ignoreUnknownDevices)
    {
        hook_output("--> skipping: unknown device type.");
        return true;
    }

    return false;
}

static BOOL __stdcall EnumDevicesHook_EVO(LPCDIDEVICEINSTANCEA lpDev, LPVOID lpParam)
{
    hook_output("[Input] Scanning device %s - %s (type %i)", lpDev->tszInstanceName, lpDev->tszProductName, lpDev->dwDevType);

    if (CheckShouldSkip(lpDev))
    {
        return DIENUM_CONTINUE;
    }

    eRes = hook::Func<BOOL>::StdCall(0x59B0F0)(lpDev, lpParam);
    return eRes;
}

static BOOL __stdcall EnumDevicesHook_EVO2(LPCDIDEVICEINSTANCEA lpDev, LPVOID lpParam)
{
    hook_output("[Input] Scanning device %s - %s (type %i)", lpDev->tszInstanceName, lpDev->tszProductName, lpDev->dwDevType);

    if (CheckShouldSkip(lpDev))
    {
        return DIENUM_CONTINUE;
    }

    eRes = hook::Func<BOOL>::StdCall(0x60A450)(lpDev, lpParam);
    return eRes;
}

bool __cdecl EVOInputPatchHandler::EVO1_CDIInterface_updateDevices()
{
    return hook::StaticThunk<0x59A8F0>::Call<bool>(this);
}

bool __cdecl EVOInputPatchHandler::EVO2_CDIInterface_updateDevices()
{
    return hook::StaticThunk<0x609C50>::Call<bool>(this);
}

bool EVOInputPatchHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2;
}

void EVOInputPatchHandler::Install(GameType gameType)
{
    noJoy = HookConfig::GetBool("Input", "DisableJoystickSupport", noJoy);
    ignoreUnknownDevices = HookConfig::GetBool("Input", "IgnoreUnknownDevices", ignoreUnknownDevices);
    ignoreAllDevices = HookConfig::GetBool("Input", "IgnoreAllDevices", ignoreAllDevices);

    // Input enumerator hook
    if (gameType == GameType::Game_EVO) 
    {
        InstallVTableHook("CDIInterface::updateDevices", &EVO1_CDIInterface_updateDevices, { 0x5EF4C4 });
        InstallCallback("DirectInput_EnumDevices",
            &EnumDevicesHook_EVO, {
                cb::push(0x59A921),
            }
        );
    }
    else if (gameType == GameType::Game_EVO2)
    {
        mem::nop(0x48E60C, 5); // remove redundant call to joystick stuff
        InstallVTableHook("CDIInterface::updateDevices", &EVO2_CDIInterface_updateDevices, { 0x668454 });
        InstallCallback("DirectInput_EnumDevices",
            &EnumDevicesHook_EVO2, {
                cb::push(0x609C81),
            }
        );
    }
}
