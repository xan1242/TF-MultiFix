//
// Yu-Gi-Oh! Tag Force - Deck Edit Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "deck.h"

uintptr_t _base_addr_deck = 0;
uintptr_t _base_size_deck = 0;

void deck_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_deck = base_addr;
    _base_size_deck = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMPwNOP(0x35380, (uintptr_t)&YgSys_GetLang_Hook);

    // injector.MakeCALL(0x6D0, (uintptr_t)&YgSys_GetLang_Hook);
    // injector.MakeCALL(0x6E0, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x1E31C, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x1E174, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x5568, (uintptr_t)&YgSys_GetLang_Hook2);

    // fix help topic text positions
    minj_WriteMemory16(0x5144, (uint16_t)(9 << 6));

    // button text
    minj_WriteMemory16(0x6120, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x6144, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x617C, (uint16_t)(0xF8 << 6));
    minj_WriteMemory16(0x61A4, (uint16_t)(0xF8 << 6));

    // current topic title
    minj_WriteMemory16(0x6674, (uint16_t)(9 << 6));
    // fix starchip infront of the category menu
    minj_WriteMemory32(0x6894, 0x02403021); // move a2, s2

    //injector.MakeCALL(0x24F4, (uintptr_t)&YgSys_GetLang_Hook2);
    //injector.MakeCALL(0x2548, (uintptr_t)&YgSys_GetLang_Hook2); // matrix font

    //injector.MakeCALL(0x35AC, (uintptr_t)&YgSys_GetLang_Hook2);
    //injector.MakeCALL(0x3624, (uintptr_t)&YgSys_GetLang_Hook2);
    //injector.MakeCALL(0x3624, (uintptr_t)&YgSys_GetLang_Hook2);
    //injector.MakeCALL(0x3514, (uintptr_t)&YgSys_GetLang_Hook2);
    //injector.MakeCALL(0x34E0, (uintptr_t)&YgSys_GetLang_Hook2); // matrix font

    // if (!mfconfig_GetMatrixFontInDeckEdit())
    // {
    //     // kill matrix font for card names
    //     minj_MakeJMPwNOP(0x33BA8, (uintptr_t)&ReturnZeroFunc);
    // }

    // injector.MakeCALL(0x88B0, (uintptr_t)&YgSys_GetLang_Hook);


    minj_SetBaseAddress(oldaddr, oldsize);
}