//
// Yu-Gi-Oh! Tag Force - Character List Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "charalist.h"

uintptr_t _base_addr_charalist = 0;
uintptr_t _base_size_charalist = 0;

void charalist_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_charalist = base_addr;
    _base_size_charalist = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fix team/class background sprite size in the description box
    minj_WriteMemory16(0x6808, 0);


#ifdef YG_GETLANG_DEBUG
    helpers_SetYgLangHookBase(base_addr);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}