//
// Yu-Gi-Oh! Tag Force - Card Album Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "cardalbum.h"

uintptr_t _base_addr_cardalbum = 0;
uintptr_t _base_size_cardalbum = 0;

void cardalbum_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_cardalbum = base_addr;
    _base_size_cardalbum = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMPwNOP(0x14138, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x643C, (uintptr_t)&YgSys_GetLang_Hook2);


    minj_SetBaseAddress(oldaddr, oldsize);
}