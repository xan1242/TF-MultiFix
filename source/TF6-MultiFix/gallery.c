//
// Yu-Gi-Oh! Tag Force - Photo Gallery Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "gallery.h"

uintptr_t _base_addr_gallery = 0;
uintptr_t _base_size_gallery = 0;

void gallery_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_gallery = base_addr;
    _base_size_gallery = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // extend the area for photo title
    minj_WriteMemory16(0x16E0, (400 << 6));

    minj_SetBaseAddress(oldaddr, oldsize);
}
