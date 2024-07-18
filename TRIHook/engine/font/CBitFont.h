#pragma once
#include <trihook/trihook.h>
#include <engine/engine_memory.h>

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2)
class CBitFont
{
private:
    char _class[0x4220];
private:
    void __cdecl reset();
public:
    TRI_ALLOCATOR;
    CBitFont();
    ~CBitFont();

    void __cdecl fontIsAntiAliased();
    void __cdecl init(const char* textureName, int textureWidth, int textureHeight, int unk);
    void __cdecl setTrueColor(unsigned int r, unsigned int g, unsigned int b);
    int __cdecl getCharHeight(int charcode);
    void __cdecl setYCharOffset(int offset, int range0, int range1);
    void __cdecl setUnkThing(int a, int b, int c);
};
#endif