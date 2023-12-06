//
// Yu-Gi-Oh! Tag Force - Duel Engine Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "dueleng.h"

uintptr_t _base_addr_dueleng = 0;
uintptr_t _base_size_dueleng = 0;

void dueleng_chtSetOpponentLP(int16_t val)
{
    *(int16_t*)(0x38BCD8 + _base_addr_dueleng) = val;
}

void dueleng_chtSetPlayerLP(int16_t val)
{
    *(int16_t*)(0x38B19C + _base_addr_dueleng) = val;
}

// void dueleng_UpdatePlayerStatusHook(int playerNum)
// {
//     if (_CheatOpponentLP >= 0)
//         dueleng_chtSetOpponentLP(_CheatOpponentLP);
//     if (_CheatPlayerLP >= 0)
//         dueleng_chtSetPlayerLP(_CheatPlayerLP);
// 
//     void (*UpdatePlayerStatus)(int) = (void(*)(int))(0x1EE124 + _base_addr_dueleng);
//     UpdatePlayerStatus(playerNum);
// }

void dueleng_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_dueleng = base_addr;
    _base_size_dueleng = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // don't hook if there's nothing to set
    //if ((_CheatOpponentLP >= 0) || (_CheatPlayerLP >= 0))
    //    minj_MakeCALL(0x1EE374, (uintptr_t)&dueleng_UpdatePlayerStatusHook);

    minj_SetBaseAddress(oldaddr, oldsize);
}
