//
// Yu-Gi-Oh! Tag Force - Duel Cheat Menu
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../MenuWindow.h"
#include "../dueleng.h"
#include "../dueldraw.h"
#include "cheatmenu_duel.h"
#include "../../../includes/psp/pspmallochelper.h"

MenuWindow* chtwndDuel;

int cheatmenu_duel_SetOppLP = 0;
int cheatmenu_duel_SetPlayerLP = 8000;

int cheatmenu_duel_last_item = 0;
int cheatmenu_duel_last_page = 0;

int cheatmenu_duel_SetPhase = 0;
int cheatmenu_duel_DrawCardAmount = 1;
int cheatmenu_duel_OppDrawCardAmount = 1;

const char* cheatmenu_duel_Phases[] =
{
    "DP",
    "SP",
    "MP1",
    "BP",
    "MP2",
    "EP",
    //"Opp. DP",
    //"Opp. SP",
    //"Opp. MP1",
    //"Opp. BP",
    //"Opp. MP2",
    //"Opp. EP",
};

#define CHEATMENU_DUEL_PHASES_COUNT sizeof(cheatmenu_duel_Phases) / sizeof(const char**)

duelPhase cheatmenu_duel_MapIdxToPhase(int idx)
{
    if (idx < 6)
    {
        return (duelPhase)(idx + 0xA);
    }
    //return (duelPhase)(idx + 0x800A);
}

MenuWindowItem cheatmenu_duel_Settings[CHEATMENU_DUEL_ITEM_COUNT] =
{
	{&cheatmenu_duel_SetOppLP,      0, UINT16_MAX, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_SETOPPONENTLP, CHEATMENU_DUEL_ITEM_NAME_SETOPPONENTLP, CHEATMENU_DUEL_ITEM_DESC_SETOPPONENTLP, NULL, 0, 0, 0},
	{&cheatmenu_duel_SetPlayerLP,   0, UINT16_MAX, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_SETPLAYERLP, CHEATMENU_DUEL_ITEM_NAME_SETPLAYERLP, CHEATMENU_DUEL_ITEM_DESC_SETPLAYERLP, NULL, 0, 0, 0},
	{&cheatmenu_duel_DrawCardAmount, 1, INT32_MAX, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_DRAWCARD, CHEATMENU_DUEL_ITEM_NAME_DRAWCARD, CHEATMENU_DUEL_ITEM_DESC_DRAWCARD, NULL, 0, 0, 0},
	{&cheatmenu_duel_OppDrawCardAmount, 1, INT32_MAX, MENUWINDOW_ITEM_TYPE_INT, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_OPPDRAWCARD, CHEATMENU_DUEL_ITEM_NAME_OPPDRAWCARD, CHEATMENU_DUEL_ITEM_DESC_OPPDRAWCARD, NULL},
	{&cheatmenu_duel_SetPhase, 0, CHEATMENU_DUEL_PHASES_COUNT - 1, MENUWINDOW_ITEM_TYPE_INTSTRING, 0, 1, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_SETPHASE, CHEATMENU_DUEL_ITEM_NAME_SETPHASE, CHEATMENU_DUEL_ITEM_DESC_SETPHASE, cheatmenu_duel_Phases, 0, 0, 0},
	{NULL,                     0, 0,          MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_TAKEAICONTROL, CHEATMENU_DUEL_ITEM_NAME_TAKEAICONTROL, CHEATMENU_DUEL_ITEM_DESC_TAKEAICONTROL, NULL, 0, 0, 0},
	{NULL,                     0, 0,          MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, 0, 0, CHEATMENU_DUEL_ITEM_GIVEAICONTROL, CHEATMENU_DUEL_ITEM_NAME_GIVEAICONTROL, CHEATMENU_DUEL_ITEM_DESC_GIVEAICONTROL, NULL, 0, 0, 0},
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

    chtwndDuel->selwnd->currentItemPage = cheatmenu_duel_last_page;
    chtwndDuel->selwnd->currentItem = cheatmenu_duel_last_item;
}

int cheatmenu_duel_Draw()
{
    if (!chtwndDuel)
    {
        //cheatmenu_duel_SetOppLP = 0;
        //cheatmenu_duel_SetPlayerLP = 8000;

        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);
        cheatmenu_duel_Create();
        return 0;
    }

    int menuRes = MenuWindow_Draw(chtwndDuel);
    if (menuRes)
    {
        cheatmenu_duel_last_item = chtwndDuel->selwnd->currentItem;
        cheatmenu_duel_last_page = chtwndDuel->selwnd->currentItemPage;

        int idxItem = MENUWINDOW_RESULT_ITEM(menuRes);

        if (MENUWINDOW_RESULT_DECIDESTATUS(menuRes) == YGSEL_DECIDESTATUS_CONFIRM)
        {
            switch (idxItem)
            {
                case CHEATMENU_DUEL_ITEM_OPPDRAWCARD:
                {
                    for (int i = 0; i < cheatmenu_duel_OppDrawCardAmount; i++)
                    {
                        dueleng_chtOppDrawCard();
                    }
                    break;
                }
                case CHEATMENU_DUEL_ITEM_DRAWCARD:
                {
                    for (int i = 0; i < cheatmenu_duel_DrawCardAmount; i++)
                    {
                        dueleng_chtDrawCard();
                    }
                    break;
                }
                case CHEATMENU_DUEL_ITEM_SETPHASE:
                {
                    dueleng_chtSetPhase(cheatmenu_duel_MapIdxToPhase(cheatmenu_duel_SetPhase));
                    break;
                }
                case CHEATMENU_DUEL_ITEM_GIVEAICONTROL:
                {
                    dueleng_chtSetPlayerControl(0, 1);
                    break;
                }
                case CHEATMENU_DUEL_ITEM_TAKEAICONTROL:
                {
                    dueleng_chtSetPlayerControl(0, 0);
                    break;
                }
                case CHEATMENU_DUEL_ITEM_SETPLAYERLP:
                {
                    dueldraw_SetPlayerLP(*cheatmenu_duel_Settings[idxItem].val);
                    dueleng_chtSetPlayerLP(*cheatmenu_duel_Settings[idxItem].val);
                    break;
                }
                case CHEATMENU_DUEL_ITEM_SETOPPONENTLP:
                {
                    dueldraw_SetOpponentLP(*cheatmenu_duel_Settings[idxItem].val);
                    dueleng_chtSetOpponentLP(*cheatmenu_duel_Settings[idxItem].val);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        cheatmenu_duel_Destroy();
        return menuRes;
    }

    return 0;
}
