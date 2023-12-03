//
// Yu-Gi-Oh! Tag Force - Card Shop Patches
// by xan1242 / Tenjoin
//

#include "../../includes/psp/injector.h"
#include "multifix.h"
#include "shop.h"

uintptr_t _base_addr_shop = 0;
uintptr_t _base_size_shop = 0;

void shop_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_shop = base_addr;
    _base_size_shop = base_size;
    uintptr_t oldaddr = injector.base_addr;
    uintptr_t oldsize = injector.base_size;

    injector.SetGameBaseAddress(base_addr, base_size);


    // fix pack title position
    //injector.WriteMemory32(0x88D4, 0x03C09021); // move s2, fp
    injector.MakeCALL(0x88B0, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x16A74, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x11868, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x117A0, (uintptr_t)&YgSys_GetLang_Hook);
    //injector.MakeCALL(0x6100, (uintptr_t)&YgSys_GetLang_Hook); // matrix font
    injector.MakeCALL(0x613C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x5660, (uintptr_t)&YgSys_GetLang_Hook);



    injector.SetGameBaseAddress(oldaddr, oldsize);
}
