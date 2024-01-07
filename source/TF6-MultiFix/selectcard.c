//
// Yu-Gi-Oh! Tag Force - Rental Machine Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "selectcard.h"

uintptr_t _base_addr_selectcard = 0;
uintptr_t _base_size_selectcard = 0;

int selectcard_MaxRentals()
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->extra.CheatMaxRents >= 0)
        return config->extra.CheatMaxRents;

    int result = 1;
    int level = YgSys_uGetLevel();

    if (level > 9)
        result = 2;
    if (level > 19)
        result = 3;
    if (level > 29)
        result = 4;
    if (level > 39)
        result = 5;

    return result;
}

void selectcard_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_selectcard = base_addr;
    _base_size_selectcard = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMPwNOP(0x26620, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x1593C, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x15B30, (uintptr_t)&YgSys_GetLang_Hook2);

    // max rental cheat
    minj_MakeJMPwNOP(0x124F0, (uintptr_t)&selectcard_MaxRentals);

    minj_SetBaseAddress(oldaddr, oldsize);
}