#include "CPickList.h"

#if defined(TRIHOOK_GAME_EVO)
CPickList::CPickList()
{
    hook::StaticThunk<0x43F030>::Call<void>(this);
}

CPickList::~CPickList()
{
    //hack, call virtual dtor
    hook::StaticThunk<0x43F120>::Call<void>(this, 0);
}

void __cdecl CPickList::addItem(const char* text)
{
    hook::StaticThunk<0x43DEE0>::Call<void>(this, text);
}

void __cdecl CPickList::free()
{
    hook::StaticThunk<0x440E60>::Call<void>(this);
}

int __cdecl CPickList::drawWindow(const char* title, int selectedOption, int unk)
{
    return hook::StaticThunk<0x43F2C0>::Call<int>(this, title, selectedOption, unk);
}
#elif defined(TRIHOOK_GAME_EVO2)
CPickList::CPickList()
{
    hook::StaticThunk<0x446A30>::Call<void>(this);
}

CPickList::~CPickList()
{
    //hack, call virtual dtor
    hook::StaticThunk<0x446B20>::Call<void>(this, 0);
}

void __cdecl CPickList::free()
{
    hook::StaticThunk<0x448880>::Call<void>(this);
}

void __cdecl CPickList::addItem(const char* text)
{
    hook::StaticThunk<0x445870>::Call<void>(this, text);
}

int __cdecl CPickList::drawWindow(const char* title, int selectedOption, int unk)
{
    return hook::StaticThunk<0x446CC0>::Call<int>(this, title, selectedOption, unk);
}
#elif defined(TRIHOOK_GAME_EVO_ED)
CPickList::CPickList()
{
    hook::StaticThunk<0x460BE0>::Call<void>(this);
}

CPickList::~CPickList()
{
    //hack, call virtual dtor
    hook::StaticThunk<0x460CD0>::Call<void>(this, 0);
}

//void __cdecl CPickList::free()
//{
//    hook::StaticThunk<0x448880>::Call<void>(this);
//}

void __cdecl CPickList::addItem(const char* text)
{
    hook::StaticThunk<0x45FA60>::Call<void>(this, text);
}

int __cdecl CPickList::drawWindow(const char* title, int selectedOption, int unk)
{
    return hook::StaticThunk<0x460E70>::Call<int>(this, title, selectedOption, unk);
}
#endif