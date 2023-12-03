//
// Yu-Gi-Oh! Tag Force - Duel Renderer Patches
// by xan1242 / Tenjoin
//

#include "../../includes/psp/injector.h"
#include "multifix.h"
#include "dueldraw.h"
#include "helpers.h"

uintptr_t _base_addr_dueldraw = 0;
uintptr_t _base_size_dueldraw = 0;


void dueldraw_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_dueldraw = base_addr;
    _base_size_dueldraw = base_size;
    uintptr_t oldaddr = injector.base_addr;
    uintptr_t oldsize = injector.base_size;
    injector.SetGameBaseAddress(base_addr, base_size);

    // fix displayed card when presenting cards from decks (e.g. Pot of Duality shows a random card from the deck)
    injector.MakeCALL(0x290C4, 0x121AC + base_addr);


    injector.SetGameBaseAddress(oldaddr, oldsize);
}