#pragma once
#include <trihook/trihook.h>
#include <engine/engine_memory.h>

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO_ED)
class CPickList
{
private:
    int classSize[240];
public:
    TRI_ALLOCATOR
    CPickList();
    ~CPickList();
    void __cdecl addItem(const char* text);
    void __cdecl free();
    int __cdecl drawWindow(const char* title, int selectedOption, int unk);
};
#endif