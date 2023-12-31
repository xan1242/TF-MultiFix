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
    CHEATMENU_GLOBAL_ITEM_COUNT
}cheatmenu_global_WindowItem;

#define CHEATMENU_GLOBAL_CAPTION L"Cheat Menu"

#define CHEATMENU_GLOBAL_ITEM_NAME_PARTNERCONTROL  "Control partner"
#define CHEATMENU_GLOBAL_ITEM_NAME_DISABLEBANLIST  "Disable banlist"
#define CHEATMENU_GLOBAL_ITEM_NAME_UNLOCKALLCARDS  "Unlock all cards"

#define CHEATMENU_GLOBAL_DESC_NAME_PARTNERCONTROL  "Control the AI partner / CPU on player's side."
#define CHEATMENU_GLOBAL_DESC_NAME_DISABLEBANLIST  "Disables forbidden & limited list entirely."
#define CHEATMENU_GLOBAL_DESC_NAME_UNLOCKALLCARDS  "Unlocks access to all cards."


int cheatmenu_global_Draw();
int cheatmenu_global_IsActive();
void cheatmenu_global_Destroy();

#endif