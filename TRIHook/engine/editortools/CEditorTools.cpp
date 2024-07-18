#include "CEditorTools.h"

#if defined(TRIHOOK_GAME_EVO2)
declfield(CEditorTools::messageDialogTextColor)(0x813DA0);
declfield(CEditorTools::warningDialogTextColor)(0x813DA4);
declfield(CEditorTools::errorDialogTextColor)(0x813DA8);
#elif defined(TRIHOOK_GAME_EVO)
declfield(CEditorTools::messageDialogTextColor)(0x71B99C);
declfield(CEditorTools::warningDialogTextColor)(0x71B9A0);
declfield(CEditorTools::errorDialogTextColor)(0x71B9A4);
#elif defined(TRIHOOK_GAME_EVO_ED)
declfield(CEditorTools::messageDialogTextColor)(0x89B65C);
declfield(CEditorTools::warningDialogTextColor)(0x89B660);
declfield(CEditorTools::errorDialogTextColor)(0x89B664);
#endif

#if defined(TRIHOOK_GAME_EVO2)
BOOL __cdecl CEditorTools::saveDialog(const char* title, const char* directory, const char* defaultExtension, char* pathBuf, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x442A90>::Call<BOOL>(this, title, directory, defaultExtension, pathBuf, copyInitialBufferValue);
}

BOOL __cdecl CEditorTools::pickFile(const char* title, const char* directory, const char* filter, char* pathBuf, bool selectInitialPath)
{
    return hook::StaticThunk<0x442180>::Call<BOOL>(this, title, directory, filter, pathBuf, selectInitialPath);
}

void __cdecl CEditorTools::genericDialog(const char* title, const char* text, int textColor)
{
    hook::StaticThunk<0x440C30>::Call<void>(title, text, textColor);
}

BOOL CEditorTools::inputString(const char* title, char* buf, int bufSize, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x443310>::Call<BOOL>(this, title, buf, bufSize, copyInitialBufferValue);
}

BOOL CEditorTools::inputInt(const char* title, int* result, BOOL boundsCheck, int minValue, int maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x442F60>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}

BOOL CEditorTools::inputFloat(const char* title, float* result, BOOL boundsCheck, float minValue, float maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x443030>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}
#elif defined(TRIHOOK_GAME_EVO_ED)
BOOL __cdecl CEditorTools::saveDialog(const char* title, const char* directory, const char* defaultExtension, char* pathBuf, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x45D2B0>::Call<BOOL>(this, title, directory, defaultExtension, pathBuf, copyInitialBufferValue);
}

BOOL __cdecl CEditorTools::pickFile(const char* title, const char* directory, const char* filter, char* pathBuf, bool selectInitialPath)
{
    return hook::StaticThunk<0x45C9B0>::Call<BOOL>(this, title, directory, filter, pathBuf, selectInitialPath);
}

void __cdecl CEditorTools::genericDialog(const char* title, const char* text, int textColor)
{
    hook::StaticThunk<0x45B3F0>::Call<void>(title, text, textColor);
}

BOOL CEditorTools::inputString(const char* title, char* buf, int bufSize, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x45DB30>::Call<BOOL>(this, title, buf, bufSize, copyInitialBufferValue);
}

BOOL CEditorTools::inputInt(const char* title, int* result, BOOL boundsCheck, int minValue, int maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x45D780>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}

BOOL CEditorTools::inputFloat(const char* title, float* result, BOOL boundsCheck, float minValue, float maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x45D850>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}
#elif defined(TRIHOOK_GAME_EVO)
BOOL __cdecl CEditorTools::saveDialog(const char* title, const char* directory, const char* defaultExtension, char* pathBuf, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x43B780>::Call<BOOL>(this, title, directory, defaultExtension, pathBuf, copyInitialBufferValue);
}

BOOL __cdecl CEditorTools::pickFile(const char* title, const char* directory, const char* filter, char* pathBuf, bool selectInitialPath)
{
    return hook::StaticThunk<0x43AE80>::Call<BOOL>(this, title, directory, filter, pathBuf, selectInitialPath);
}

void __cdecl CEditorTools::genericDialog(const char* title, const char* text, int textColor)
{
    hook::StaticThunk<0x4398E0>::Call<void>(title, text, textColor);
}

BOOL CEditorTools::inputString(const char* title, char* buf, int bufSize, bool copyInitialBufferValue)
{
    return hook::StaticThunk<0x43C000>::Call<BOOL>(this, title, buf, bufSize, copyInitialBufferValue);
}

BOOL CEditorTools::inputInt(const char* title, int* result, BOOL boundsCheck, int minValue, int maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x43BC50>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}

BOOL CEditorTools::inputFloat(const char* title, float* result, BOOL boundsCheck, float minValue, float maxValue, bool copyInitialValue)
{
    return hook::StaticThunk<0x43BD20>::Call<BOOL>(this, title, result, boundsCheck, minValue, maxValue, copyInitialValue);
}
#endif

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO_ED)
void __cdecl CEditorTools::messageDialogF(const char* fmt, ...)
{
    char buf[1024] = { 0 };

    va_list va;
    va_start(va, fmt);
    int bufLen = vsprintf_s(buf, fmt, va);
    va_end(va);

    genericDialog("Message", buf, messageDialogTextColor.get());
}

void __cdecl CEditorTools::warningDialogF(const char* fmt, ...)
{
    char buf[1024] = { 0 };

    va_list va;
    va_start(va, fmt);
    int bufLen = vsprintf_s(buf, fmt, va);
    va_end(va);

    genericDialog("Warning", buf, warningDialogTextColor.get());
}

void __cdecl CEditorTools::errorDialogF(const char* fmt, ...)
{
    char buf[1024] = { 0 };

    va_list va;
    va_start(va, fmt);
    int bufLen = vsprintf_s(buf, fmt, va);
    va_end(va);

    genericDialog("Error", buf, errorDialogTextColor.get());
}

BOOL CEditorTools::inputInt(const char* title, int* result)
{
    return inputInt(title, result, FALSE, 0, 0, false);
}

BOOL CEditorTools::inputFloat(const char* title, float* result)
{
    return inputFloat(title, result, FALSE, 0.0f, 0.0f, false);
}
#endif