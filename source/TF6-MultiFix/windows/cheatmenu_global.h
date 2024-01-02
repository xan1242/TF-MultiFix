//
// Yu-Gi-Oh! Tag Force - Global Cheat Menu
// by xan1242 / Tenjoin
//

#ifndef CHEATMENUGLOBAL_H
#define CHEATMENUGLOBAL_H

typedef enum _cheatmenu_global_WindowItem
{
    CHEATMENU_GLOBAL_ITEM_UNK = -1,
    CHEATMENU_GLOBAL_ITEM_PARTNERCONTROL,
    CHEATMENU_GLOBAL_ITEM_DISABLEBANLIST,
    CHEATMENU_GLOBAL_ITEM_UNLOCKALLCARDS,
    CHEATMENU_GLOBAL_ITEM_UNLOCKALLBOXES,
    CHEATMENU_GLOBAL_ITEM_INFINITEDP,
    CHEATMENU_GLOBAL_ITEM_SETDP,
    CHEATMENU_GLOBAL_ITEM_TRUSTMENU,
    CHEATMENU_GLOBAL_ITEM_COUNT
}cheatmenu_global_WindowItem;

#define CHEATMENU_GLOBAL_CAPTION L"Cheat Menu"

#define CHEATMENU_GLOBAL_ITEM_NAME_PARTNERCONTROL  "Control partner"
#define CHEATMENU_GLOBAL_ITEM_NAME_DISABLEBANLIST  "Disable banlist"
#define CHEATMENU_GLOBAL_ITEM_NAME_UNLOCKALLCARDS  "Unlock all cards"
#define CHEATMENU_GLOBAL_ITEM_NAME_UNLOCKALLBOXES  "Unlock all boxes"
#define CHEATMENU_GLOBAL_ITEM_NAME_INFINITEDP      "Infinite DP"
#define CHEATMENU_GLOBAL_ITEM_NAME_SETDP           "Set DP"
#define CHEATMENU_GLOBAL_ITEM_NAME_TRUSTMENU       "Adjust character trust"

#define CHEATMENU_GLOBAL_DESC_NAME_PARTNERCONTROL  "Control the AI partner / CPU on player's side."
#define CHEATMENU_GLOBAL_DESC_NAME_DISABLEBANLIST  "Disables the forbidden & limited list entirely."
#define CHEATMENU_GLOBAL_DESC_NAME_UNLOCKALLCARDS  "Unlocks access to all cards."
#define CHEATMENU_GLOBAL_DESC_NAME_UNLOCKALLBOXES  "Unlocks access to all boxes in the card shop. (Reload card shop to take effect)"
#define CHEATMENU_GLOBAL_DESC_NAME_INFINITEDP      "Locks Duel Points to maximum. This also prevents the DP in your save file from being affected."
#define CHEATMENU_GLOBAL_DESC_NAME_SETDP           "Sets Duel Points in your save file to a given value."
#define CHEATMENU_GLOBAL_DESC_NAME_TRUSTMENU       "Opens a list of characters where you can set the trust points for each character in the game."


int cheatmenu_global_Draw();
int cheatmenu_global_IsActive();
void cheatmenu_global_Destroy();

#endif