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
#include "../../includes/psp/stringhash.h"

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
#include "YgWindow.h"
#include "MenuWindow.h"
#include <pspctrl.h>
#include "multifixconfig.h"
#include "windows/multifixwindow.h"
#include "windows/aboutwindow.h"
#include "windows/konamidialog.h"
#include "windows/cheatmenu_global.h"
#include "windows/cheatmenu_duel.h"

#include <psputility.h>
#include <psputility_msgdialog.h>

uintptr_t base_addr = 0;

int bCheatMenuEnabled = 0;

int bShowMfWindow = 0;
int bShowAboutWindow = 0;
int bShowKonamiDialog = 0;
int bShowCheatMenuGlobal = 0;
int bShowCheatMenuDuel = 0;

int bIsOnPPSSPP = 0;
void SetPPSSPP(int val)
{
    bIsOnPPSSPP = val;
    helpers_SetPPSSPP(val);
}

int (*ptr_lEhScript_ModuleRead_FinishCB)(uintptr_t unk1, uintptr_t unk2) = (int(*)(uintptr_t, uintptr_t))0;
int (*lEhModule_Load_EndCallback)(uintptr_t unk1, uintptr_t unk2) = (int(*)(uintptr_t, uintptr_t))0;
void (*lSoftReset)() = (void(*)())0;

void DestroyAllWindows()
{
    bShowMfWindow = 0;
    bShowAboutWindow = 0;
    bShowKonamiDialog = 0;
    bShowCheatMenuGlobal = 0;
    bShowCheatMenuDuel = 0;

    if (aboutwindow_IsActive())
        aboutwindow_Destroy();
    if (konamidialog_IsActive())
        konamidialog_Destroy();
    if (mfwindow_IsActive())
        mfwindow_Destroy();
    if (cheatmenu_global_IsActive())
        cheatmenu_global_Destroy();
    if (cheatmenu_duel_IsActive())
        cheatmenu_duel_Destroy();
}

int bIsAnyWindowShown()
{
    return bShowMfWindow || bShowAboutWindow || bShowKonamiDialog || bShowCheatMenuDuel || bShowCheatMenuGlobal;
}

int lEhScript_ModuleRead_FinishCB_Hook(uintptr_t unk1, uintptr_t unk2)
{
    char* modName = (char*)(unk1 + 4);

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("lEhScript_ModuleRead_FinishCB hooked, args: 0x%X 0x%X", unk1, unk2);
    sceKernelPrintf("LOADED MODULE: %s", modName);
#endif

    char modNameUpper[16];
    YgSys_strcpy(modNameUpper, modName);
    str_tocase(modNameUpper, 1);

    int nameHash = bStringHash(modNameUpper);

    if ((nameHash == PSMF_PRX_STRHASH) || (nameHash == LIBPSMFPLAYER_PRX_STRHASH))
    {
        if (lEhModule_Load_EndCallback)
            return lEhModule_Load_EndCallback(unk1, unk2);
        return 0;
    }

    SetGameState(EHSTATE_UNKNOWN);

    DestroyAllWindows();

    if (nameHash == REL_TITLE_PRX_STRHASH)
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

    if (nameHash == REL_DECK_PRX_STRHASH)
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

    if (nameHash == REL_DUELMGR_PRX_STRHASH)
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

    if (nameHash == REL_UMDREPLACE_PRX_STRHASH)
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

    if (nameHash == REL_GALLERY_PRX_STRHASH)
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

    if (nameHash == REL_STORY_PRX_STRHASH)
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

    char modNameUpper[16];
    YgSys_strcpy(modNameUpper, modName);
    str_tocase(modNameUpper, 1);
    int nameHash = bStringHash(modNameUpper);

    if ((nameHash == PSMF_PRX_STRHASH) || (nameHash == LIBPSMFPLAYER_PRX_STRHASH))
    {
        if (lEhModule_Load_EndCallback)
            return lEhModule_Load_EndCallback(unk1, unk2);
        return 0;
    }

    SetGameState(EHSTATE_UNKNOWN);
    DestroyAllWindows();
   
    if (nameHash == REL_FIELD_PRX_STRHASH)
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

    if (nameHash == REL_SHOP_PRX_STRHASH)
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

    if (nameHash == REL_DUELDRAW_PRX_STRHASH)
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

    if (nameHash == REL_DUELENG_PRX_STRHASH)
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

    if (nameHash == REL_CHARALIST_PRX_STRHASH)
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

    if (nameHash == REL_TUTORIALLIST_PRX_STRHASH)
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

    if (nameHash == REL_DUELRECORD_PRX_STRHASH)
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

    if (nameHash == REL_DECKTUTORIAL_PRX_STRHASH)
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

    if (nameHash == REL_TUTORIAL_PRX_STRHASH)
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

    if (nameHash == REL_PASSWORD_PRX_STRHASH)
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

    if (nameHash == REL_SELECTCARD_PRX_STRHASH)
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

    if (nameHash == REL_CARDALBUM_PRX_STRHASH)
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

    if (nameHash == REL_SOUNDTEST_PRX_STRHASH)
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

    if (nameHash == REL_RECIPEVIEWER_PRX_STRHASH)
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
    uint32_t confirm = PSP_CTRL_CIRCLE;
    uint32_t decline = PSP_CTRL_CROSS;

    if (mfconfig_GetSwapConfirmButtons())
    {
        confirm = PSP_CTRL_CROSS;
        decline = PSP_CTRL_CIRCLE;

        //if (!YgSys_GetLang()) // JP language swap
        //{
        //    confirm = PSP_CTRL_CROSS;
        //    decline = PSP_CTRL_CIRCLE;
        //}
    }
    //else
    //{
    //    if (YgSys_GetLang()) // non JP language swap
    //    {
    //        confirm = PSP_CTRL_CROSS;
    //        decline = PSP_CTRL_CIRCLE;
    //    }
    //}

    if (isDeclineButton)
        return decline;
    return confirm;

}

void YgFont_SetMatrixFontFlg_Hook(int val)
{
    if (val && mfconfig_GetMatrixFont())
    {
        *(uint32_t*)(YGFONT_FLAGS_ADDR + base_addr) |= 0x4000;
    }
    else
    {
        *(uint32_t*)(YGFONT_FLAGS_ADDR + base_addr) &= ~0x4000;
    }
}

void HandleButtonInputs()
{
    uint32_t buttons = GetPadButtons(0);
    uint32_t buttons2 = GetPadButtons(1);
    if (GetGameState() == EHSTATE_TITLE)
    {
        if (helpers_KonamiCodeCheck(buttons2) && !bCheatMenuEnabled)
        {
            bCheatMenuEnabled = 1;
            mfwindow_SetCheatsEnabled(1);
            bShowKonamiDialog = 1;
        }
    }

    if ((buttons & PSP_CTRL_WLAN_UP) && (buttons & PSP_CTRL_RTRIGGER)) // wlan on & R = plugin input mode
    {
        helpers_SetBlockNextInputPoll(1);
        if (buttons & PSP_CTRL_TRIANGLE)
        {
            if (!bIsAnyWindowShown())
                bShowMfWindow = 1;
        }

        if (bCheatMenuEnabled)
        {
            if (buttons & PSP_CTRL_CIRCLE)
            {
                if (!bIsAnyWindowShown())
                    bShowCheatMenuGlobal = 1;
            }

            // duel cheats
            if (GetGameState() == EHSTATE_DUEL)
            {
                if (buttons & PSP_CTRL_SQUARE)
                {
                    if (!bIsAnyWindowShown())
                        bShowCheatMenuDuel = 1;
                }

                //            if (mfconfig_GetInstaWinCheat())
                //            {
                //                if (buttons & PSP_CTRL_SQUARE)
                //                {
                //#ifdef TFMULTIFIX_DEBUG_PRINT
                //                    sceKernelPrintf("Player Cheat on !!!");
                //#endif
                //                    dueleng_chtSetPlayerLP(mfconfig_GetCheatPlayerLP());
                //                }
                //
                //                if (buttons & PSP_CTRL_SELECT)
                //                {
                //#ifdef TFMULTIFIX_DEBUG_PRINT
                //                    sceKernelPrintf("Opponent LP Cheat on !!!");
                //#endif
                //                    dueleng_chtSetOpponentLP(mfconfig_GetCheatOpponentLP());
                //                }
                //            }
                //
                //            if (mfconfig_GetCheatControlPartner() == 1)
                //            {
                //                if (buttons & PSP_CTRL_LEFT)
                //                {
                //#ifdef TFMULTIFIX_DEBUG_PRINT
                //                    sceKernelPrintf("Player control cheat: AI off !!!");
                //#endif
                //                    dueleng_chtSetPlayerControl(0, 0);
                //                }
                //                else if (buttons & PSP_CTRL_RIGHT)
                //                {
                //#ifdef TFMULTIFIX_DEBUG_PRINT
                //                    sceKernelPrintf("Player control cheat: AI on !!!");
                //#endif
                //                    dueleng_chtSetPlayerControl(0, 1);
                //                }
            }
        }
   }
}

void HandleDialogs()
{
    helpers_SetDialogBoxWantsIO(0);

    if (bShowAboutWindow)
    {
        if (aboutwindow_Draw())
            bShowAboutWindow = 0;
    }

    if (bShowKonamiDialog)
    {
        if (konamidialog_Draw())
            bShowKonamiDialog = 0;
    }

    if (bShowMfWindow)
    {
        int retval = mfwindow_Draw();
        if (retval)
        {
            bShowMfWindow = 0;

            int itemIdx = MENUWINDOW_RESULT_ITEM(retval);

            //int decideStatus = retval & 0xFF;
            //int currItem = (retval >> 8) & 0xFF;
            //int bValueChanged = (retval >> 16) & 0xFF;

            if (MENUWINDOW_RESULT_DECIDESTATUS(retval) == YGSEL_DECIDESTATUS_CONFIRM)
            {
                switch (itemIdx)
                {
                    case MFWINDOW_ITEM_ABOUT:
                    {
                        bShowAboutWindow = 1;
                        break;
                    }
                    case MFWINDOW_ITEM_CHEATSGLOBAL:
                    {
                        if (bCheatMenuEnabled)
                        {
                            bShowCheatMenuGlobal = 1;
                        }
                        break;
                    }
                    case MFWINDOW_ITEM_CHEATSLOCAL:
                    {
                        if (bCheatMenuEnabled && ((GetGameState() == EHSTATE_DUEL)))
                        {
                            bShowCheatMenuDuel = 1;
                        }
                        break;
                    }
                    default:
                        break;
                }

                //if (itemIdx == MFWINDOW_ITEM_ABOUT)
                //{
                //    bShowAboutWindow = 1;
                //}
                //
                //if ((itemIdx == MFWINDOW_ITEM_CHEATSLOCAL) && bCheatMenuEnabled)
                //{
                //    if (GetGameState() == EHSTATE_DUEL)
                //        bShowCheatMenuDuel = 1;
                //}
            }

        }
    }

    if (bShowCheatMenuGlobal)
    {
        if (cheatmenu_global_Draw())
        {
            bShowCheatMenuGlobal = 0;
        }
    }

    if (bShowCheatMenuDuel)
    {
        if (cheatmenu_duel_Draw())
        {
            bShowCheatMenuDuel = 0;
        }
    }
}

// do stuff at the end of main loop
//void lSoftReset_Hook()
//{
//    //DrawTestWindow();
//    //DrawBasicTestWindow();
//    //DrawDialogTestWindow();
//    //HandleButtonCheats();
//    return lSoftReset();
//}

// do stuff before VSync
//void YgAdh_Update_Hook()
//{
//
//
//    return YgAdh_Update();
//}

void FirstLoopFunc_Hook(int unk)
{
    helpers_SetBlockNextInputPoll(0);
    HandleDialogs();
    HandleButtonInputs();

    if (helpers_GetDialogBoxWantsIO())
        helpers_SetBlockNextInputPoll(1);

    return FirstLoopFunc(unk);
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

int YgSys_GetLimitation_Hook(uint16_t cardID)
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatDisableBanlist)
    {
        return 3;
    }
    return YgSys_GetLimitation(cardID);
}

int YgSys_GetLimitation_Default_Hook(uint16_t cardID)
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatDisableBanlist)
    {
        return 3;
    }
    return YgSys_GetLimitation_Default(cardID);
}

int YgSys_GetTrunk_Hook(uint16_t cardID)
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatUnlockAllCards)
    {
        if (YgSys_GetTrunkFromMRK(cardID))
            return 9;
    }

    return YgSys_GetTrunk(cardID);
}

int YgSys_GetDuelPoint_Hook()
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatInfiniteDP)
    {
        return INT32_MAX;
    }
    return YgSys_GetDuelPoint();
}

void YgSys_UpdateDuelPoint_Hook(int amount)
{
    MultiFixConfig* config = mfconfig_GetConfig();
    if (config->bCheatInfiniteDP)
    {
        return;
    }
    return YgSys_UpdateDuelPoint(amount);
}

//int InstallDialogHook(pspUtilityMsgDialogParams* params)
//{
//    YgSys_strcpy(params->message, "The installation feature has been disabled.\nTo re-enable, please reconfigure the plugin.");
//    YgSys_strcpy((char*)((uintptr_t)params + 0x284), "Back");
//    params->options = 0;
//
//    return sceUtilityMsgDialogInitStart(params);
//}

// void HandlePreInit()
// {
// 
// }

//void HandlePostInit()
//{
//#ifdef TFMULTIFIX_DEBUG_PRINT
//    sceKernelPrintf("After YgSys_InitApplication(), heap addr: 0x%X", helpers_GetMainEhHeap());
//#endif
//}

//void YgSys_InitApplication_Hook()
//{
//    YgSys_InitApplication();
//    HandlePostInit();
//}

void TFFixesInject()
{
	base_addr = minj_GetBaseAddress();
    //base_size = injector.base_size;

#ifndef MINJECTOR_MINIMAL
    minj_SetMemsetAddress(0x4A4E0);
    minj_SetMemcpyAddress(0x4A1DC);
#endif

    helpers_Init(base_addr);
    YgWindow_Init(base_addr);
    mfconfig_Init();

    // init hook
    //minj_MakeCALL(0x5AD0, (uintptr_t)&YgSys_InitApplication_Hook);

    // main loop hook
    lSoftReset = (void(*)())(0x5954 + base_addr);
    //minj_MakeCALL(0x5BF0, (uintptr_t)&lSoftReset_Hook);
    //minj_MakeCALL(0x5BE0, (uintptr_t)&YgAdh_Update_Hook);
    minj_MakeCALL(0x5B7C, (uintptr_t)&FirstLoopFunc_Hook);
    // EhPad_Get with input blocking
    minj_MakeJMPwNOP(0x3A428, (uintptr_t)&EhPad_Get);

    //minj_MakeCALL(0x934, 0x640DC);
    //_YgFont_Printf = (uintptr_t(*)(int, int, const char*, ...))(0xB70 + base_addr);

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
    minj_MakeCALL(0x17E48, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x17DF4, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0xC3B0, (uintptr_t)&YgSys_GetLang_Hook);
    minj_WriteMemory16(0x17E64, 0x480);

    minj_MakeCALL(0x14D8, (uintptr_t)&YgSys_GetLang_Hook);


#ifndef __INTELLISENSE__
    // global font Y offset
    minj_MakeCALL(0x1844, (uintptr_t)&hkPrintLineFontYOffset);
    minj_MakeCALL(0x34D8, (uintptr_t)&hkPrintBoxFontYOffset);
#endif

    minj_MakeJMPwNOP(0x8DA0, (uintptr_t)&YgSys_GetAssignButton_Hook);
    // matrix font stuff
    minj_MakeJMPwNOP(0x2218, (uintptr_t)&YgFont_SetMatrixFontFlg_Hook);
    minj_MakeNOP(0xE698);
    minj_MakeNOP(0x18520);

    // banlist stuff
    minj_MakeJMPwNOP(0x29204, (uintptr_t)&YgSys_GetLimitation_Hook);
    minj_MakeJMPwNOP(0x880C, (uintptr_t)&YgSys_GetLimitation_Default_Hook);

    // card unlock
    minj_MakeJMPwNOP(0x2B700, (uintptr_t)&YgSys_GetTrunk_Hook);

    // infinite DP
    minj_MakeJMPwNOP(0x25D20, (uintptr_t)&YgSys_GetDuelPoint_Hook);
    minj_MakeJMPwNOP(0x25D58, (uintptr_t)&YgSys_UpdateDuelPoint_Hook);

#ifdef YG_GETLANG_DEBUG
    minj_MakeJMPwNOP(0x298D8, (uintptr_t)&YgSys_GetLang);
#endif

    // YgSys_CardDetail_Raw_DrawSmallText fix
    minj_MakeCALL(0xCF38, (uintptr_t)&YgFont_GetShadowFlg_Hook);
    minj_MakeCALL(0xCF44, (uintptr_t)&YgFont_SetShadowFlg_Hook1);
    minj_MakeCALL(0xCF6C, (uintptr_t)&YgFont_SetShadowFlg_Hook2);

}