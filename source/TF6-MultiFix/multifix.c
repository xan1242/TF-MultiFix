//
// Yu-Gi-Oh! Tag Force - MultiFix code
// by xan1242 / Tenjoin
//

#include <pspsdk.h>
#include <pspuser.h>
#include <stdio.h>
#include <systemctrl.h>
#include <kubridge.h>
#include <ctype.h>
//#include "../../includes/psp/injector.h"

#include "multifix.h"
#include "helpers.h"
#include "dueleng.h"
#include "duelmgr.h"
#include "dueldraw.h"
#include "deck.h"
#include "shop.h"
#include "field.h"
#include "charalist.h"
#include "tutoriallist.h"
#include "duelrecord.h"
#include "umdreplace.h"
#include "decktutorial.h"
#include "tutorial.h"
#include "password.h"
#include "selectcard.h"
#include "cardalbum.h"
#include "soundtest.h"
#include "gallery.h"
#include "recipeviewer.h"
#include "story.h"
#include "title.h"
#include <pspctrl.h>
#include "multifixconfig.h"

uintptr_t base_addr = 0;

// uintptr_t base_addr_field = 0;
// uintptr_t base_size_field = 0;
// 
// uintptr_t base_addr_shop = 0;
// uintptr_t base_size_shop = 0;
// 
// uintptr_t base_addr_deck = 0;
// uintptr_t base_size_deck = 0;
// 
// uintptr_t base_addr_dueleng = 0;
// uintptr_t base_size_dueleng = 0;
// 
// uintptr_t base_addr_duelmgr = 0;
// uintptr_t base_size_duelmgr = 0;
// 
// uintptr_t base_addr_charalist = 0;
// uintptr_t base_size_charalist = 0;
// 
// uintptr_t base_addr_tutoriallist = 0;
// uintptr_t base_size_tutoriallist = 0;


int bIsOnPPSSPP = 0;

void SetPPSSPP(int val)
{
    bIsOnPPSSPP = val;
    helpers_SetPPSSPP(val);
}

// int YgSys_GetLang_Hook()
// {
//     return 1;
// }
// 
// int YgSys_GetLang_Hook_Loud()
// {
// #ifdef TFMULTIFIX_DEBUG_PRINT
//     void* addr = __builtin_extract_return_addr(__builtin_return_address(0));
//     uintptr_t baseaddr = base_addr_deck;
//     sceKernelPrintf("RA: 0x%X (0x%X) (0x%X)", addr, (uintptr_t)addr - baseaddr, (uintptr_t)addr - baseaddr - 8);
// #endif
//     return 1;
// }
// 
// int YgSys_GetLang_Hook2()
// {
//     return 0;
// }

int (*ptr_lEhScript_ModuleRead_FinishCB)(uintptr_t unk1, uintptr_t unk2) = (int(*)(uintptr_t, uintptr_t))0;
int (*lEhModule_Load_EndCallback)(uintptr_t unk1, uintptr_t unk2) = (int(*)(uintptr_t, uintptr_t))0;
void (*lSoftReset)() = (void(*)())0;

int lEhScript_ModuleRead_FinishCB_Hook(uintptr_t unk1, uintptr_t unk2)
{
    char* modName = (char*)(unk1 + 4);

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("lEhScript_ModuleRead_FinishCB hooked, args: 0x%X 0x%X", unk1, unk2);
    sceKernelPrintf("LOADED MODULE: %s", modName);
#endif

    char modNameLower[16];
    YgSys_strcpy(modNameLower, modName);
    str_tolower(modNameLower);

    if (tf_strstr(modNameLower, "psmf"))
    {
        if (lEhModule_Load_EndCallback)
            return lEhModule_Load_EndCallback(unk1, unk2);
        return 0;
    }

    SetGameState(EHSTATE_UNKNOWN);

    if (tf_strstr(modNameLower, "title.p"))
    {
        SetGameState(EHSTATE_TITLE);

        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modtitle", &bs, &sz))
        {
            title_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "deck.p"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("moddeck", &bs, &sz))
        {
            SetGameState(EHSTATE_DECK);
            // base_addr_deck = bs;
            // base_size_deck = sz;
            deck_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "duelmgr.p"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modduel_mgr", &bs, &sz))
        {
            // base_addr_duelmgr = bs;
            // base_size_duelmgr = sz;
            duelmgr_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "umdreplace"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modumd_replace", &bs, &sz))
        {
            umdreplace_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "gallery"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modgallery", &bs, &sz))
        {
            gallery_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "story"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modstory", &bs, &sz))
        {
            story_Patch(bs, sz);

            if (ptr_lEhScript_ModuleRead_FinishCB)
                return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
            return 0;
        }
    }

    if (ptr_lEhScript_ModuleRead_FinishCB)
        return ptr_lEhScript_ModuleRead_FinishCB(unk1, unk2);
    return 0;
}

int lEhModule_Load_EndCallback_Hook(uintptr_t unk1, uintptr_t unk2)
{
    char* modName = (char*)(unk1 + 0x14);

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("lEhModule_Load_EndCallback hooked, args: 0x%X 0x%X", unk1, unk2);
    sceKernelPrintf("LOADED MODULE: %s", modName);
#endif

    char modNameLower[16];
    YgSys_strcpy(modNameLower, modName);
    str_tolower(modNameLower);

    if (tf_strstr(modNameLower, "psmf"))
    {
        if (lEhModule_Load_EndCallback)
            return lEhModule_Load_EndCallback(unk1, unk2);
        return 0;
    }

    SetGameState(EHSTATE_UNKNOWN);


    if (tf_strstr(modNameLower, "field"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modfield", &bs, &sz))
        {
            SetGameState(EHSTATE_FIELD);
            // base_addr_dueleng = bs;
            // base_size_dueleng = sz;
            field_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "shop"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modshop", &bs, &sz))
        {
            SetGameState(EHSTATE_SHOP);
            // base_addr_dueleng = bs;
            // base_size_dueleng = sz;
            shop_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "dueldraw.p"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modduel_draw", &bs, &sz))
        {
            // base_addr_dueleng = bs;
            // base_size_dueleng = sz;
            dueldraw_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "dueleng.p"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modduel_eng", &bs, &sz))
        {
            SetGameState(EHSTATE_DUEL);
            // base_addr_dueleng = bs;
            // base_size_dueleng = sz;
            dueleng_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "charalist"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modcharalist", &bs, &sz))
        {
            // base_addr_charalist = bs;
            // base_size_charalist = sz;
            charalist_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "tutoriallist"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modtutoriallist", &bs, &sz))
        {
            // base_addr_tutoriallist = bs;
            // base_size_tutoriallist = sz;
            tutoriallist_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "duelrec"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modduelrecord", &bs, &sz))
        {
            // base_addr_tutoriallist = bs;
            // base_size_tutoriallist = sz;
            duelrecord_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "decktut"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("moddeck_tutorial", &bs, &sz))
        {
            decktutorial_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "_tutori")) // for tf1 it's libtutorial.prx, for tf6 it's rel_Tutorial.prx
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modtutorial", &bs, &sz))
        {
            tutorial_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "password"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modpassword", &bs, &sz))
        {
            password_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "selectca"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modselect_card", &bs, &sz))
        {
            selectcard_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "cardalbum"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modcardalbum", &bs, &sz))
        {
            cardalbum_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "soundtest"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modsoundtest", &bs, &sz))
        {
            soundtest_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (tf_strstr(modNameLower, "recipe"))
    {
        uintptr_t bs = 0;
        uintptr_t sz = 0;

        if (tfFindModuleByName("modrecipe_viewer", &bs, &sz))
        {
            recipeviewer_Patch(bs, sz);

            if (lEhModule_Load_EndCallback)
                return lEhModule_Load_EndCallback(unk1, unk2);
            return 0;
        }
    }

    if (lEhModule_Load_EndCallback)
        return lEhModule_Load_EndCallback(unk1, unk2);
    return 0;
}

#ifndef __INTELLISENSE__
__attribute__((naked)) void hkPrintLineFontYOffset()
{
    asm volatile
    (
        "addiu $a1, $a1, -0x40\n"
        "sw $a1, 0x98($sp)\n"
        "addu $s4, $s1, $s4\n"
        "jr $ra\n"
        "lui $s5, 5\n"
    );
}

__attribute__((naked)) void hkPrintBoxFontYOffset()
{
    asm volatile
    (
            "addiu $fp, $fp, -0x40\n"
            "addu $s3, $a3, $fp\n"
            "lui $a1, 5\n"
            "addu $a1, $s2, $a1\n"
            "jr $ra\n"
            "nop\n"
            
    );
}
#endif

// swap cross and circle for accept
int YgSys_GetAssignButton_Hook(int isDeclineButton)
{
    if (YgSys_GetLang())
    {
        if (isDeclineButton)
            return PSP_CTRL_CROSS;
        return PSP_CTRL_CIRCLE;
    }

    if (isDeclineButton)
        return PSP_CTRL_CIRCLE;
    return PSP_CTRL_CROSS;
}

// uintptr_t HookCallback(uintptr_t addr, uintptr_t dest)
// {
//     uintptr_t ptrLUI = 0;
//     uintptr_t ptrADDIU = 0;
// 
//     uintptr_t cbptr = MIPS_DiscoverPtr(addr + base_addr, &ptrLUI, &ptrADDIU, a2);
// 
//     uint32_t newLUI = 0;
//     uint32_t newADDIU = 0;
// 
//     MIPS_CalcNewRegValue((uint32_t)dest, &newLUI, &newADDIU, a2);
// 
//     injector.WriteMemory32(ptrLUI, newLUI);
//     injector.WriteMemory32(ptrADDIU, newADDIU);
// 
//     return cbptr;
// }

void HandleButtonCheats()
{
    uint32_t buttons = GetPadButtons(0);

    if (buttons & (PSP_CTRL_WLAN_UP | PSP_CTRL_RTRIGGER)) // wlan on & R = cheat input mode
    {
        // duel cheats
        if (GetGameState() == EHSTATE_DUEL)
        {
            if (mfconfig_GetInstaWinCheat())
            {
                if (buttons & PSP_CTRL_SQUARE)
                {
#ifdef TFMULTIFIX_DEBUG_PRINT
                    sceKernelPrintf("Player Cheat on !!!");
#endif
                    dueleng_chtSetPlayerLP(mfconfig_GetCheatPlayerLP());
                }

                if (buttons & PSP_CTRL_SELECT)
                {
#ifdef TFMULTIFIX_DEBUG_PRINT
                    sceKernelPrintf("Opponent LP Cheat on !!!");
#endif
                    dueleng_chtSetOpponentLP(mfconfig_GetCheatOpponentLP());
                }
            }

            if (mfconfig_GetCheatControlPartner() == 1)
            {
                if (buttons & PSP_CTRL_LEFT)
                {
#ifdef TFMULTIFIX_DEBUG_PRINT
                    sceKernelPrintf("Player control cheat: AI off !!!");
#endif
                    dueleng_chtSetPlayerControl(0, 0);
                }
                else if (buttons & PSP_CTRL_RIGHT)
                {
#ifdef TFMULTIFIX_DEBUG_PRINT
                    sceKernelPrintf("Player control cheat: AI on !!!");
#endif
                    dueleng_chtSetPlayerControl(0, 1);
                }
            }
        }
    }
}

// do stuff at the end of main loop
void lSoftReset_Hook()
{
    HandleButtonCheats();
    return lSoftReset();
}

//
// YgSys_CardDetail_Raw_DrawSmallText text fix
//
int YgFont_GetShadowFlg_Hook()
{
    int oldflg = YgFont_GetWordSeparateFlg();

    return (YgFont_GetShadowFlg() & 1) | (oldflg << 1); // store old state on the second bit
}

void YgFont_SetShadowFlg_Hook1(int val)
{
    YgFont_SetWordSeparateFlg(1);
    return YgFont_SetShadowFlg(val);
}

void YgFont_SetShadowFlg_Hook2(int val)
{
    YgFont_SetWordSeparateFlg((val & 2) >> 1);
    return YgFont_SetShadowFlg(val & 1);
}

void TFFixesInject()
{
	base_addr = minj_GetBaseAddress();
    //base_size = injector.base_size;

#ifndef MINJECTOR_MINIMAL
    minj_SetMemsetAddress(0x4A4E0);
    minj_SetMemcpyAddress(0x4A1DC);
#endif

    helpers_Init(base_addr);
    mfconfig_Init();

    // main loop hook
    lSoftReset = (void(*)())(0x5954 + base_addr);
    minj_MakeCALL(0x5BF0, (uintptr_t)&lSoftReset_Hook);

    //uintptr_t modreadcb = MIPS_WriteLUI_ADDIU(0x3D5B0 + base_addr, (uintptr_t)&lEhScript_ModuleRead_FinishCB_Hook, a2);
    uintptr_t modreadcb = minj_WriteLUI_ADDIU(0x3D5B0, (uintptr_t)&lEhScript_ModuleRead_FinishCB_Hook, MIPSR_a2);
    ptr_lEhScript_ModuleRead_FinishCB = (int(*)(uintptr_t, uintptr_t))modreadcb;


    uintptr_t modloadcb = minj_WriteLUI_ADDIU(0x39CA4, (uintptr_t)&lEhModule_Load_EndCallback_Hook, MIPSR_a2);
    lEhModule_Load_EndCallback = (int(*)(uintptr_t, uintptr_t))modloadcb;

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("EhScript_ModuleRead Callback: 0x%X", modreadcb);
    sceKernelPrintf("EhModule_Load Callback: 0x%X", modloadcb);
#endif

    // force non-taboo flag
    minj_MakeJMPwNOP(0x2068, 0x21AC + base_addr);
    minj_MakeJMPwNOP(0x20A4, 0x20CC + base_addr);

    // fix line spacing
    minj_MakeNOP(0x17B8);
    minj_WriteMemory32(0x17A8, 0x00A02021); // move a0, a1
    minj_WriteMemory16(0x1430, LINE_SPACING_VAL);

    minj_WriteMemory16(0x2848, LINE_SPACING_VAL);
    minj_WriteMemory16(0x28F8, LINE_SPACING_VAL);
    minj_WriteMemory16(0x292C, LINE_SPACING_VAL);


    minj_WriteMemory16(0x19BC, (uint16_t)(-LINE_SPACING_VAL));
    minj_WriteMemory16(0x1F70, (uint16_t)(-LINE_SPACING_VAL));
    minj_WriteMemory16(0x37B8, (uint16_t)(-LINE_SPACING_VAL));
    minj_WriteMemory16(0x386C, (uint16_t)(-LINE_SPACING_VAL));

    minj_WriteMemory16(0x53CC, (uint16_t)(-LINE_SPACING_VAL));

    minj_WriteMemory32(0x5AE8, 0x34050001); // li a1, 1
    minj_MakeCALL(0xE6A8, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x16344, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x16DF0, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x16E3C, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x17DF4, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0xC3B0, (uintptr_t)&YgSys_GetLang_Hook);
    minj_WriteMemory16(0x17E64, 0x480);

    minj_MakeCALL(0x14D8, (uintptr_t)&YgSys_GetLang_Hook);


#ifndef __INTELLISENSE__
    // global font Y offset
    minj_MakeCALL(0x1844, (uintptr_t)&hkPrintLineFontYOffset);
    minj_MakeCALL(0x34D8, (uintptr_t)&hkPrintBoxFontYOffset);
#endif

    if (mfconfig_GetSwapConfirmButtons())
    {
        // swap cross and circle
        minj_MakeJMPwNOP(0x8DA0, (uintptr_t)&YgSys_GetAssignButton_Hook);
    }

    if (!mfconfig_GetMatrixFont())
    {
        // kill YgFont_SetMatrixFontFlg
        minj_MakeJMPwNOP(0x2218, 0x224C + base_addr);
    }

#ifdef YG_GETLANG_DEBUG
    minj_MakeJMPwNOP(0x298D8, (uintptr_t)&YgSys_GetLang);
#endif

    // YgSys_CardDetail_Raw_DrawSmallText fix
    minj_MakeCALL(0xCF38, (uintptr_t)&YgFont_GetShadowFlg_Hook);
    minj_MakeCALL(0xCF44, (uintptr_t)&YgFont_SetShadowFlg_Hook1);
    minj_MakeCALL(0xCF6C, (uintptr_t)&YgFont_SetShadowFlg_Hook2);

    // get partner name from regular chr names
    //minj_MakeNOP(0x23A10);

    //injector.WriteMemory16(0x2848, 0x40);


    // injector.MakeJMPwNOP(0x298D8, (uintptr_t)&YgSys_GetLang_Hook);
    // 
    // injector.MakeCALL(0x23088, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x23C9C, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x19504, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x1958C, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0xEE10, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0xEEC4, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0xEEC4, (uintptr_t)&YgSys_GetLang_Hook2);


    //injector.MakeInline(1, 0x8DE8, li(a0, 1));
    //injector.MakeInlineLI(0x8DE8, 1);
    
}