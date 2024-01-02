//
// Yu-Gi-Oh! Tag Force - Global Cheat Menu
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../MenuWindow.h"
#include "../WindowManager.h"
#include "cheatmenu_global.h"
#include "../../../includes/psp/pspmallochelper.h"

MenuWindow* chtwndGlobal;

int cheatmenu_global_cbReadDP(uintptr_t)
{
    return YgSys_GetDuelPoint();
}

int cheatmenu_global_cbWriteDP(int value, uintptr_t)
{
    YgSys_SetDuelPoint(value);
    return 0;
}

MenuWindowItem cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_COUNT] =
{
	{NULL, 0, 1, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, 0, 0, CHEATMENU_GLOBAL_ITEM_PARTNERCONTROL, CHEATMENU_GLOBAL_ITEM_NAME_PARTNERCONTROL, CHEATMENU_GLOBAL_DESC_NAME_PARTNERCONTROL, NULL, 0, 0, 0},
	{NULL, 0, 1, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, 0, 0, CHEATMENU_GLOBAL_ITEM_DISABLEBANLIST, CHEATMENU_GLOBAL_ITEM_NAME_DISABLEBANLIST, CHEATMENU_GLOBAL_DESC_NAME_DISABLEBANLIST, NULL, 0, 0, 0},
	{NULL, 0, 1, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, 0, 0, CHEATMENU_GLOBAL_ITEM_UNLOCKALLCARDS, CHEATMENU_GLOBAL_ITEM_NAME_UNLOCKALLCARDS, CHEATMENU_GLOBAL_DESC_NAME_UNLOCKALLCARDS, NULL, 0, 0, 0},
	{NULL, 0, 1, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, 0, 0, CHEATMENU_GLOBAL_ITEM_UNLOCKALLBOXES, CHEATMENU_GLOBAL_ITEM_NAME_UNLOCKALLBOXES, CHEATMENU_GLOBAL_DESC_NAME_UNLOCKALLBOXES, NULL, 0, 0, 0},
	{NULL, 0, 1, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, 0, 0, CHEATMENU_GLOBAL_ITEM_INFINITEDP, CHEATMENU_GLOBAL_ITEM_NAME_INFINITEDP, CHEATMENU_GLOBAL_DESC_NAME_INFINITEDP, NULL, 0, 0, 0},
    {NULL, 0, INT32_MAX, MENUWINDOW_ITEM_TYPE_INT, 0, 0, 0, 0, 0, 0, CHEATMENU_GLOBAL_ITEM_SETDP, CHEATMENU_GLOBAL_ITEM_NAME_SETDP, CHEATMENU_GLOBAL_DESC_NAME_SETDP, NULL, (uintptr_t)&cheatmenu_global_cbReadDP, (uintptr_t)&cheatmenu_global_cbWriteDP, 0},
    {NULL, 0, 0, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, 0, 0, CHEATMENU_GLOBAL_ITEM_TRUSTMENU, CHEATMENU_GLOBAL_ITEM_NAME_TRUSTMENU, CHEATMENU_GLOBAL_DESC_NAME_TRUSTMENU, NULL, 0, 0, 0},
};

int cheatmenu_global_IsActive()
{
	return chtwndGlobal != NULL;
}

void cheatmenu_global_Destroy()
{
    if (chtwndGlobal)
    {
        if (MenuWindow_IsActive(chtwndGlobal))
        {
            MenuWindow_Destroy(chtwndGlobal);
        }

        psp_free(chtwndGlobal);
        chtwndGlobal = NULL;
    }
}

uintptr_t cheatmenu_global_Callback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    return MenuWindow_Callback(ehpacket, item_index, X, Y, chtwndGlobal);
}

void cheatmenu_global_Create()
{
    if (chtwndGlobal)
        psp_free(chtwndGlobal);
    chtwndGlobal = (MenuWindow*)psp_malloc(sizeof(MenuWindow));
    YgSys_memset(chtwndGlobal, 0, sizeof(YgSelWnd));


    // assign some defaults
    chtwndGlobal->caption = CHEATMENU_GLOBAL_CAPTION;
    chtwndGlobal->bBlockGameControl = 1;
    chtwndGlobal->zOrder = MULTIFIX_WINDOW_ZORDER;
    chtwndGlobal->itemDrawCallback = (uintptr_t)&cheatmenu_global_Callback;
    chtwndGlobal->itemCount = CHEATMENU_GLOBAL_ITEM_COUNT;
    chtwndGlobal->items = cheatmenu_global_Items;

    MultiFixConfig* config = mfconfig_GetConfig();
    cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_PARTNERCONTROL].val = &config->bCheatConstantControlPartner;
    cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_DISABLEBANLIST].val = &config->bCheatDisableBanlist;
    cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_UNLOCKALLCARDS].val = &config->bCheatUnlockAllCards;
    cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_UNLOCKALLBOXES].val = &config->bCheatUnlockAllBoxes;
    cheatmenu_global_Items[CHEATMENU_GLOBAL_ITEM_INFINITEDP].val = &config->bCheatInfiniteDP;

    MenuWindow_Create(chtwndGlobal);
}

int cheatmenu_global_Draw()
{
    if (!chtwndGlobal)
    {
        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);

        cheatmenu_global_Create();
        return 0;
    }

    int menuRes = MenuWindow_Draw(chtwndGlobal);
    if (menuRes)
    {
        int idxItem = MENUWINDOW_RESULT_ITEM(menuRes);

        if (MENUWINDOW_RESULT_DECIDESTATUS(menuRes) == YGSEL_DECIDESTATUS_CONFIRM)
        {
            switch (idxItem)
            {
                case CHEATMENU_GLOBAL_ITEM_TRUSTMENU:
                {
                    WM_ShowWindow(WINDOWMANAGER_DISP_TRUSTMENU);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        cheatmenu_global_Destroy();
        return menuRes;
    }

    return 0;
}
