//
// Yu-Gi-Oh! Tag Force - Duel Engine Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "dueleng.h"

uintptr_t _base_addr_dueleng = 0;
uintptr_t _base_size_dueleng = 0;

#define DUELENG_BASE_ENG_ADDR 0x38A980

void (*dueleng_sub_5228)() = (void (*)())(0);
int (*dueleng_uUpdatePlayerState)() = (int (*)())(0);
void (*dueleng_uDrawCard)() = (void (*)())(0);

void dueleng_chtSetOpponentLP(int16_t val)
{
    if (_base_addr_dueleng)
        *(int16_t*)(0x38B19C + 0xB3C + _base_addr_dueleng) = val;

    if (dueleng_uUpdatePlayerState)
        dueleng_uUpdatePlayerState();
}

void dueleng_chtSetPlayerLP(int16_t val)
{
    if (_base_addr_dueleng)
        *(int16_t*)(0x38B19C + _base_addr_dueleng) = val;

    if (dueleng_uUpdatePlayerState)
        dueleng_uUpdatePlayerState();
}

// Player 0 = player
// Player 1 = opponent
// val 0 = player controls
// val 1 = ai controls
// val 2 = nobody (used in multiplayer)
void dueleng_chtSetPlayerControl(int PlayerNum, int val)
{
    if (dueleng_sub_5228)
        dueleng_sub_5228();

    // *(int*)(0x38E3E0 + 8 + _base_addr_dueleng) = val;
    // *(int*)(0x38E3E8 + 8 + _base_addr_dueleng) = val;

    *(uint32_t*)(4 * PlayerNum + (0x38E3DC + _base_addr_dueleng) + 8) = val;
}

int dueleng_SetPartnerCardVisibility()
{
    return 1;
}

int dueleng_SetPartnerCardVisibility_Hook(int retval)
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bSeePartnerCards)
        return 1;
    return retval;
}

int dueleng_hkSetPartnerCardVisibility();
#ifndef __INTELLISENSE__
asm
(
    ".global dueleng_hkSetPartnerCardVisibility\n"
    "dueleng_hkSetPartnerCardVisibility:\n"
    "move $a0, $v0\n"
    "j dueleng_SetPartnerCardVisibility_Hook\n"
    "nop\n"
);
#endif

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

//void (*dueleng_sub_A28C)(uintptr_t, int) = (void (*)(uintptr_t, int))(0);

void dueleng_sub_A28C_Hook(int PlayerNum, int WhoIsInControl)
{
    if (!dueleng_sub_5228)
        return;

    dueleng_sub_5228();

    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatConstantControlPartner)
    {
        if (PlayerNum == 0)
            *(uint32_t*)(4 * PlayerNum + (0x38E3DC + _base_addr_dueleng) + 8) = 0;
        else
            *(uint32_t*)(4 * PlayerNum + (0x38E3DC + _base_addr_dueleng) + 8) = WhoIsInControl;
    }
    else
        *(uint32_t*)(4 * PlayerNum + (0x38E3DC + _base_addr_dueleng) + 8) = WhoIsInControl;
}

void dueleng_chtSetPhase(duelPhase phase)
{
    *(uint16_t*)(DUELENG_BASE_ENG_ADDR + _base_addr_dueleng) = (phase & 0xFFFF);
    *(uint16_t*)(DUELENG_BASE_ENG_ADDR + 8 + _base_addr_dueleng) = (phase & 0xFFFF);
    *(uint32_t*)(DUELENG_BASE_ENG_ADDR + 0x808 + _base_addr_dueleng) = 1;
}

void dueleng_chtDrawCard()
{
    // set command
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + _base_addr_dueleng) = 0x56;
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + 8 + _base_addr_dueleng) = 0x56;
    dueleng_uDrawCard();

    *(int16_t*)(DUELENG_BASE_ENG_ADDR + _base_addr_dueleng) = 0x56;
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + 8 + _base_addr_dueleng) = 0x56;
    dueleng_uDrawCard();
}

void dueleng_chtOppDrawCard()
{
    // set command
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + _base_addr_dueleng) = -0x56;
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + 8 + _base_addr_dueleng) = -0x56;
    dueleng_uDrawCard();

    *(int16_t*)(DUELENG_BASE_ENG_ADDR + _base_addr_dueleng) = -0x56;
    *(int16_t*)(DUELENG_BASE_ENG_ADDR + 8 + _base_addr_dueleng) = -0x56;
    dueleng_uDrawCard();
}

void dueleng_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_dueleng = base_addr;
    _base_size_dueleng = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMP(0x5770, (uintptr_t)&dueleng_hkSetPartnerCardVisibility);
    minj_MakeJMP(0x5790, (uintptr_t)&dueleng_hkSetPartnerCardVisibility);

    //if (mfconfig_GetSeePartnerCards())
    //{
    //    minj_MakeJMPwNOP(0x5738, (uintptr_t)&dueleng_SetPartnerCardVisibility);
    //}

    //dueleng_sub_A28C = (void (*)(uintptr_t, int))(0xA28C + base_addr);
    dueleng_sub_5228 = (void (*)())(0x5228 + base_addr);
    dueleng_uUpdatePlayerState = (int (*)())(0x1EE320 + base_addr);
    dueleng_uDrawCard = (void (*)())(0x311BA0 + base_addr);

    //if (mfconfig_GetCheatControlPartner() == 2)
    //{
        minj_MakeJMPwNOP(0xA28C, (uintptr_t)&dueleng_sub_A28C_Hook);
    //}


    // minj_MakeCALL(0x698, (uintptr_t)&dueleng_sub_A28C_Hook);
    // minj_MakeCALL(0x714, (uintptr_t)&dueleng_sub_A28C_Hook);
    // minj_WriteMemory32(0x3186D0, (uint32_t)&dueleng_sub_A28C_Hook);


    //if (mfconfig_GetCheatControlPartner() == 2)
    //{
    //    minj_WriteMemory32(0x718, 0x00002825); // move a1, zero
    //    //minj_MakeNOP(0xA2B8);
    //    //minj_MakeNOP(0x1BAAEC);
    //    //minj_MakeNOP(0x1BAAF0);
    //}

    // don't hook if there's nothing to set
    //if ((_CheatOpponentLP >= 0) || (_CheatPlayerLP >= 0))
    //    minj_MakeCALL(0x1EE374, (uintptr_t)&dueleng_UpdatePlayerStatusHook);

    minj_SetBaseAddress(oldaddr, oldsize);
}
