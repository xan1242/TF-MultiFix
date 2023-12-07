//
// Yu-Gi-Oh! Tag Force - Duel Renderer Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "dueldraw.h"
#include "helpers.h"

uintptr_t _base_addr_dueldraw = 0;
uintptr_t _base_size_dueldraw = 0;


void dueldraw_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_dueldraw = base_addr;
    _base_size_dueldraw = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fix displayed card when presenting cards from decks (e.g. Pot of Duality shows a random card from the deck)
    minj_MakeCALL(0x290C4, 0x121AC + base_addr);

    // lang fixes (L trigger menu)
    minj_MakeCALL(0x7ADE4, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x7AE30, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x1C77C, (uintptr_t)&YgSys_GetLang_Hook);

    // lang fix the help topics
    minj_MakeCALL(0x21B4, (uintptr_t)&YgSys_GetLang_Hook);

    // fix help topic text positions
    minj_WriteMemory16(0x1794, (uint16_t)(9 << 6));

    // button text
    minj_WriteMemory16(0x23E8, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x240C, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x2444, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x246C, (uint16_t)(0xF8 << 6));

    // current topic title
    minj_WriteMemory16(0x293C, (uint16_t)(9 << 6));
    // fix starchip infront of the category menu
    minj_WriteMemory32(0x2B5C, 0x02403021); // move a2, s2


    minj_SetBaseAddress(oldaddr, oldsize);
}