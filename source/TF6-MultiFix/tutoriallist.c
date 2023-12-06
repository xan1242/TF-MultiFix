//
// Yu-Gi-Oh! Tag Force - Tutorial List Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "tutoriallist.h"

uintptr_t _base_addr_tutoriallist = 0;
uintptr_t _base_size_tutoriallist = 0;

void tutoriallist_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_tutoriallist = base_addr;
    _base_size_tutoriallist = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fix line spacing in the list
    minj_MakeJMPwNOP(0xF698, (uintptr_t)&YgSys_GetLang_Hook);
    // exclude path
    minj_MakeCALL(0x2BB4, (uintptr_t)&YgSys_GetLang_Hook2);


    minj_SetBaseAddress(oldaddr, oldsize);
}