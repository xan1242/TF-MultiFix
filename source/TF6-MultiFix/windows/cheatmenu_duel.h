//
// Yu-Gi-Oh! Tag Force - Duel Cheat Menu
// by xan1242 / Tenjoin
//

#ifndef CHEATMENUDUEL_H
#define CHEATMENUDUEL_H

typedef enum _cheatmenu_duel_WindowItem
{
    CHEATMENU_DUEL_ITEM_UNK = -1,
    CHEATMENU_DUEL_ITEM_SETOPPONENTLP,
    CHEATMENU_DUEL_ITEM_SETPLAYERLP,
    CHEATMENU_DUEL_ITEM_DRAWCARD,
    CHEATMENU_DUEL_ITEM_OPPDRAWCARD,
    //CHEATMENU_DUEL_ITEM_SETPHASE,
    CHEATMENU_DUEL_ITEM_TAKEAICONTROL,
    CHEATMENU_DUEL_ITEM_GIVEAICONTROL,
    CHEATMENU_DUEL_ITEM_COUNT
}cheatmenu_duel_WindowItem;

#define CHEATMENU_DUEL_CAPTION L"Duel Cheat Menu"

#define CHEATMENU_DUEL_ITEM_NAME_SETOPPONENTLP   "Set opponent LP"
#define CHEATMENU_DUEL_ITEM_NAME_SETPLAYERLP     "Set player LP"
#define CHEATMENU_DUEL_ITEM_NAME_DRAWCARD        "Draw cards"
#define CHEATMENU_DUEL_ITEM_NAME_OPPDRAWCARD     "Draw cards (opponent)"
//#define CHEATMENU_DUEL_ITEM_NAME_SETPHASE        "Set phase"
#define CHEATMENU_DUEL_ITEM_NAME_TAKEAICONTROL   "Take control of AI partner"
#define CHEATMENU_DUEL_ITEM_NAME_GIVEAICONTROL   "Give control to AI"

#define CHEATMENU_DUEL_ITEM_DESC_SETOPPONENTLP   "Sets opponent's Life Points to a given value. (Takes effect after confirm)"
#define CHEATMENU_DUEL_ITEM_DESC_SETPLAYERLP     "Sets player's Life Points to a given value. (Takes effect after confirm)"
#define CHEATMENU_DUEL_ITEM_DESC_DRAWCARD        "Draw a specified amount of cards from the deck."
#define CHEATMENU_DUEL_ITEM_DESC_OPPDRAWCARD     "Opponent draws a specified amount of cards from the deck."
//#define CHEATMENU_DUEL_ITEM_DESC_SETPHASE        "Manually override the current phase. (Currently broken)"
#define CHEATMENU_DUEL_ITEM_DESC_TAKEAICONTROL   "Takes immediate control of AI partner (or take back control from AI given by the option below)."
#define CHEATMENU_DUEL_ITEM_DESC_GIVEAICONTROL   "Gives control to AI immediately. To take effect, you may need to enter the Phase Menu and then exit out of it."


int cheatmenu_duel_Draw();
int cheatmenu_duel_IsActive();
void cheatmenu_duel_Destroy();

#endif