//
// Yu-Gi-Oh! Tag Force - Duel Cheat Menu
// by xan1242 / Tenjoin
//

//
// TODO: this is mostly a clone of multifixwindow!!! find a way to abstract it!
// The only things that are specific are the settings and the callback!
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../MenuWindow.h"
#include "../dueleng.h"
#include "cheatmenu_duel.h"
#include "../../../includes/psp/pspmallochelper.h"

MenuWindow* chtwndDuel;

int cheatmenu_duel_SetOppLP = 0;
int cheatmenu_duel_SetPlayerLP = 8000;


MenuWindowItem cheatmenu_duel_Settings[CHEATMENU_DUEL_ITEM_COUNT] =
{
	{&cheatmenu_duel_SetOppLP,      NULL, 0, UINT16_MAX, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_SETOPPONENTLP, CHEATMENU_DUEL_ITEM_NAME_SETOPPONENTLP, CHEATMENU_DUEL_ITEM_DESC_SETOPPONENTLP},
	{&cheatmenu_duel_SetPlayerLP,   NULL, 0, UINT16_MAX, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_SETPLAYERLP, CHEATMENU_DUEL_ITEM_NAME_SETPLAYERLP, CHEATMENU_DUEL_ITEM_DESC_SETPLAYERLP},
	{NULL,                          NULL, 0, 0,          0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_DRAWCARD, CHEATMENU_DUEL_ITEM_NAME_DRAWCARD, CHEATMENU_DUEL_ITEM_DESC_DRAWCARD},
	{NULL,                          NULL, 0, 0,          0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_TAKEAICONTROL, CHEATMENU_DUEL_ITEM_NAME_TAKEAICONTROL, CHEATMENU_DUEL_ITEM_DESC_TAKEAICONTROL},
	{NULL,                          NULL, 0, 0,          0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_GIVEAICONTROL, CHEATMENU_DUEL_ITEM_NAME_GIVEAICONTROL, CHEATMENU_DUEL_ITEM_DESC_GIVEAICONTROL},
};

int cheatmenu_duel_IsActive()
{
    return chtwndDuel != NULL;
}

void cheatmenu_duel_Destroy()
{
    if (chtwndDuel)
    {
        if (MenuWindow_IsActive(chtwndDuel))
        {
            MenuWindow_Destroy(chtwndDuel);
        }

        psp_free(chtwndDuel);
        chtwndDuel = NULL;
    }
}

uintptr_t cheatmenu_duel_Callback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    return MenuWindow_Callback(ehpacket, item_index, X, Y, chtwndDuel);
}

void cheatmenu_duel_Create()
{
    if (chtwndDuel)
        psp_free(chtwndDuel);
    chtwndDuel = (MenuWindow*)psp_malloc(sizeof(MenuWindow));
    YgSys_memset(chtwndDuel, 0, sizeof(YgSelWnd));


    // assign some defaults
    chtwndDuel->caption = CHEATMENU_DUEL_CAPTION;
    chtwndDuel->bBlockGameControl = 1;
    chtwndDuel->zOrder = MULTIFIX_WINDOW_ZORDER;
    chtwndDuel->itemDrawCallback = (uintptr_t)&cheatmenu_duel_Callback;
    chtwndDuel->itemCount = CHEATMENU_DUEL_ITEM_COUNT;
    chtwndDuel->items = cheatmenu_duel_Settings;

    
    MenuWindow_Create(chtwndDuel);
}

int cheatmenu_duel_Draw()
{
    if (!chtwndDuel)
    {
        cheatmenu_duel_SetOppLP = 0;
        cheatmenu_duel_SetPlayerLP = 8000;

        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);
        cheatmenu_duel_Create();
        return 0;
    }

    int menuRes = MenuWindow_Draw(chtwndDuel);
    if (menuRes)
    {
        cheatmenu_duel_Destroy();
        return menuRes;
    }

    return 0;
}
