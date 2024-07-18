#include "CBitFont.h"

#if defined(TRIHOOK_GAME_EVO)
CBitFont::CBitFont()
{
    hook::StaticThunk<0x447390>::Call<void>(this);
}

CBitFont::~CBitFont()
{
    hook::StaticThunk<0x4473B0>::Call<void>(this);
}

void __cdecl CBitFont::reset()
{
    hook::StaticThunk<0x4473D0>::Call<void>(this);
}

void __cdecl CBitFont::fontIsAntiAliased()
{
    hook::StaticThunk<0x448140>::Call<void>(this);
}

void __cdecl CBitFont::init(const char* textureName, int textureWidth, int textureHeight, int unk)
{
    hook::StaticThunk<0x4474F0>::Call<void>(this, textureName, textureWidth, textureHeight, unk);
}

void __cdecl CBitFont::setTrueColor(unsigned int r, unsigned int g, unsigned int b)
{
    hook::StaticThunk<0x448E20>::Call<void>(this, r, g, b);
}

int __cdecl CBitFont::getCharHeight(int charcode)
{
    return hook::StaticThunk<0x44ADD0>::Call<int>(this, charcode);
}

void __cdecl CBitFont::setYCharOffset(int offset, int range0, int range1)
{
    hook::StaticThunk<0x44AE30>::Call<void>(this, offset, range0, range1);
}

void __cdecl CBitFont::setUnkThing(int a, int b, int c)
{
    setPtr<int>(this, 0x3668, a);
    setPtr<int>(this, 0x41FC, b);
    setPtr<int>(this, 0x4200, c);
}
#elif defined(TRIHOOK_GAME_EVO2)
CBitFont::CBitFont()
{
    hook::StaticThunk<0x455AA0>::Call<void>(this);
}

CBitFont::~CBitFont()
{
    hook::StaticThunk<0x455AC0>::Call<void>(this);
}

void __cdecl CBitFont::init(const char* textureName, int textureWidth, int textureHeight, int unk)
{
    hook::StaticThunk<0x455C10>::Call<void>(this, textureName, textureWidth, textureHeight, unk);
}

void __cdecl CBitFont::fontIsAntiAliased()
{
    hook::StaticThunk<0x4568F0>::Call<void>(this);
}

void __cdecl CBitFont::setYCharOffset(int offset, int range0, int range1)
{
    hook::StaticThunk<0x4595E0>::Call<void>(this, offset, range0, range1);
}

void __cdecl CBitFont::setUnkThing(int a, int b, int c)
{
    setPtr<int>(this, 0x3668, a);
    setPtr<int>(this, 0x41FC, b);
    setPtr<int>(this, 0x4200, c);
}
#endif