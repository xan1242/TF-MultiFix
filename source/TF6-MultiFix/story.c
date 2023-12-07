//
// Yu-Gi-Oh! Tag Force - Story Mode Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "story.h"

uintptr_t _base_addr_story = 0;
uintptr_t _base_size_story = 0;

wchar_t* story_YgSys_wcscat_Hook(wchar_t* dest, const wchar_t* src)
{
    return YgSys_wcscat(dest, L" & ");
}

void story_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_story = base_addr;
    _base_size_story = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMPwNOP(0x35790, (uintptr_t)&YgSys_GetLang_Hook);

    // exclude path sensitive stuff
    minj_MakeCALL(0xB070, (uintptr_t)&YgSys_GetLang_Hook2);

    // add spacing to ampersand
    minj_MakeCALL(0x9828, (uintptr_t)&story_YgSys_wcscat_Hook);
    minj_MakeCALL(0x2414, (uintptr_t)&story_YgSys_wcscat_Hook);


    minj_SetBaseAddress(oldaddr, oldsize);

}

