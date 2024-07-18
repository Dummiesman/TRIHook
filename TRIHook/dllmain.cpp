#include "dllmain.h"
#include "trihook\trihook.h"
#include "handlers\handlers.h"

LPFNDIRECTINPUTCREATE lpDICreate;

// Export as 'DirectInputCreateA/W' so we can hook into the game
// (Apparently DirectInputCreateW gets called sometimes...)
#pragma comment(linker, "/EXPORT:DirectInputCreateA=_DirectInputCreateImpl")
#pragma comment(linker, "/EXPORT:DirectInputCreateW=_DirectInputCreateImpl")
HRESULT __declspec(naked) DirectInputCreateImpl(HINSTANCE hinst, DWORD dwVersion, LPVOID* ppDI, LPUNKNOWN punkOuter)
{
    _asm jmp dword ptr ds : lpDICreate
}

bool LoadSystemLibrary(LPCSTR lpDllName, HMODULE* out)
{
    char szDllFile[MAX_PATH]{ NULL }; // path to system dll

    GetSystemDirectory(szDllFile, sizeof(szDllFile));
    sprintf(szDllFile, "%s\\%s", szDllFile, lpDllName);

    if (SUCCEEDED(*out = LoadLibrary(szDllFile)))
    {
        printf("Loaded system library \"%s\" => %08X\n", szDllFile, *out);
        return true;
    }
    else
    {
        printf("System library \"%s\" not found!\n", szDllFile);
        return false;
    }
};

bool GetHookProcAddress(HMODULE hModule, LPCSTR lpProcName, FARPROC* out)
{
    if (SUCCEEDED(*out = GetProcAddress(hModule, lpProcName)))
    {
        printf("Found hook proc \"%s\" in module %08X => %08X\n", lpProcName, hModule, *out);
        return true;
    }
    else
    {
        printf("Hook proc \"%s\" not found in module %08X!\n", lpProcName, hModule);
        return false;
    }
};

static void Initialize() 
{
    HookConfig::Init();
    
    bool useConsole = HookConfig::GetBool("Debug", "ShowConsole", false);
    bool useLog = HookConfig::GetBool("Debug", "EnableLogFile", false);
    
    int outputFlags = 0;
    outputFlags |= (useConsole) ? HOOK_OUTPUT_CONSOLE : 0;
    outputFlags |= (useLog) ? HOOK_OUTPUT_LOGFILE : 0;
    InitOutput(outputFlags);
    atexit(KillOutput);

    //TEST
    if (SetProcessDPIAware() == FALSE)
        hook_output("DPI failure");
    //

    hook_output("%s for %s, compiled on %s %s", PRODUCT_NAME, GAME_NAME, __DATE__, __TIME__);
    InstallHandlers();
}

int crc16(char* data_p, int length) {
    unsigned char x;
    unsigned short crc = 0x1D0F;

    while (length--) {
        x = crc >> 8 ^ *data_p++;
        x ^= x >> 4; // x = x ^ (x >> 4)
        crc = (crc << 8) ^ ((unsigned short)(x << 12)) ^ ((unsigned short)(x << 5)) ^ ((unsigned short)x);
    }
    return crc;
}

bool CheckGameValid()
{
    FILE* p_file = NULL;
    int size = -1;
    char  error_buf[4096] = { 0 };

    char modname_buf[MAX_PATH];
    GetModuleFileName(NULL, modname_buf, sizeof(modname_buf));

    p_file = fopen(modname_buf, "rb");
    if (p_file != NULL) {
        fseek(p_file, 0, SEEK_END);
        size = ftell(p_file);
        fseek(p_file, 0, SEEK_SET);

        auto crc_buf = (char*)malloc(size);
        fread(crc_buf, 1, size, p_file);
        fclose(p_file);

        uint16_t crc = crc16(crc_buf, size);
        free(crc_buf);

        if (crc != GAME_CRC) 
        {
            sprintf_s(error_buf, "Game CRC does not match. Expected %x, got %x. Make sure you're trying to install TRIHook for %s", GAME_CRC, crc, GAME_NAME);
            MessageBox(NULL, error_buf, PRODUCT_NAME, MB_OK | MB_ICONERROR);
            return false;
        }
        
        return true;
    }
    else 
    {
        sprintf_s(error_buf, "Failed to find game executable: %s. This shouldn't happen.", modname_buf);
        MessageBox(NULL, error_buf, PRODUCT_NAME, MB_OK | MB_ICONERROR);
        return false;
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HMODULE hDIModule = NULL;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("Initting %s", PRODUCT_NAME);
        
        if (CheckGameValid())
        {
            if (LoadSystemLibrary("dinput.dll", &hDIModule) &&
                GetHookProcAddress(hDIModule, "DirectInputCreateA", (FARPROC*)&lpDICreate))
            {
                Initialize();
            }
            else 
            {
                MessageBox(NULL, "Could not inject into the game process. Unknown errors may occur.", PRODUCT_NAME, MB_OK | MB_ICONWARNING);
            }
        }
        else
        {
            ExitProcess(EXIT_FAILURE);
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}