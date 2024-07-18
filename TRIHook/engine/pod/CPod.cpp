#include "CPod.h"

CPod::CPod()
{
}

CPod::~CPod()
{
}

void CPod::mountDefaultPodFiles()
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x4E7EB0>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x52CDB0>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x502D70>;
#endif
    func::Call<void>(this);
}

int CPod::getFileInfo(void* info)
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x4E87E0>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x503700>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x52D7C0>;
#endif
    return func::Call<int>(this, info);
}

int CPod::mountPodVolume(const char* name, char* returnErrMsg)
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x4E7EE0>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x502DA0>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x52CDE0>;
#endif
    return func::Call<int>(this, name, returnErrMsg);
}

void CPod::unmountPodVolume(const char* name)
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x4E8090>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x502F50>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x52CFD0>;
#endif
    func::Call<void>(this, name);
}

void CPod::remountAllPods()
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::StaticThunk<0x4E7FE0>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x502EA0>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::StaticThunk<0x52CF20>;
#endif
    func::Call<void>(this);
}
