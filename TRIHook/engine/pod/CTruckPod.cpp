#include "CTruckPod.h"

void CTruckPod::mountDefaultPodFiles()
{
#if defined(TRIHOOK_GAME_EVO)
    using func = hook::Thunk<0x4E8E10>;
#elif defined(TRIHOOK_GAME_EVO2)
    using func = hook::Thunk<0x503D30>;
#elif defined(TRIHOOK_GAME_EVO_ED)
    using func = hook::Thunk<0x52DE00>;
#endif
    func::Call<void>(this);
}