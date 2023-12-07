//
// Yu-Gi-Oh! Tag Force - Recipe Viewer Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "recipeviewer.h"

uintptr_t _base_addr_recipeviewer = 0;
uintptr_t _base_size_recipeviewer = 0;



void recipeviewer_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_recipeviewer = base_addr;
    _base_size_recipeviewer = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);


    minj_MakeJMPwNOP(0x16860, (uintptr_t)&YgSys_GetLang_Hook);

    // path exclusions
    minj_MakeCALL(0x95E4, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x9428, (uintptr_t)&YgSys_GetLang_Hook2);

    minj_SetBaseAddress(oldaddr, oldsize);
}