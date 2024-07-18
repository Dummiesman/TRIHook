#pragma once
#include <trihook/trihook.h>

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO_ED)
class CEditorTools
{
private:
    static hook::Type<int> messageDialogTextColor;
    static hook::Type<int> warningDialogTextColor;
    static hook::Type<int> errorDialogTextColor;
public:
    void __cdecl genericDialog(const char* title, const char* text, int textColor);
    void __cdecl messageDialogF(const char* fmt, ...);
    void __cdecl warningDialogF(const char* fmt, ...);
    void __cdecl errorDialogF(const char* fmt, ...);

    BOOL __cdecl saveDialog(const char* title, const char* directory, const char* defaultExtension, char* pathBuf, bool copyInitialBufferValue);
    BOOL __cdecl pickFile(const char* title, const char* directory, const char* filter, char* pathBuf, bool selectInitialPath);

    BOOL __cdecl inputString(const char* title, char* buf, int bufSize, bool copyInitialBufferValue);
    BOOL __cdecl inputInt(const char* title, int* result, BOOL boundsCheck, int minValue, int maxValue, bool copyInitialValue);
    BOOL __cdecl inputInt(const char* title, int* result);
    BOOL __cdecl inputFloat(const char* title, float* result, BOOL boundsCheck, float minValue, float maxValue, bool copyInitialValue);
    BOOL __cdecl inputFloat(const char* title, float* result);
};
#endif