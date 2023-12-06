//
// Yu-Gi-Oh! Tag Force - Sound Test / Music Player Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "soundtest.h"

uintptr_t _base_addr_soundtest = 0;
uintptr_t _base_size_soundtest = 0;

void soundtest_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_soundtest = base_addr;
    _base_size_soundtest = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fixes various UI bugs
    minj_MakeJMPwNOP(0xD2D0, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x2EC, (uintptr_t)&YgSys_GetLang_Hook2);

    minj_SetBaseAddress(oldaddr, oldsize);
}
