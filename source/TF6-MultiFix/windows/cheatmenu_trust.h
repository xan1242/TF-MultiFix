//
// Yu-Gi-Oh! Tag Force - Character Trust Cheat Menu
// by xan1242 / Tenjoin
//

#ifndef CHEATMENUTRUST_H
#define CHEATMENUTRUST_H

#define CHEATMENU_TRUST_CAPTION L"Character Trust Adjust"
#define CHEATMENU_TRUST_DESC "Adjust the trust points for the highlighted character. 1000 = 1 heart"

#define CHEATMENU_TRUST_SKIP_TOP 2
#define CHEATMENU_TRUST_SKIP_BOTTOM 57

// uncomment for numeric display of names next to each name
//#define CHEATMENU_TRUST_DEBUG_NUMS


int cheatmenu_trust_Draw();
int cheatmenu_trust_IsActive();
void cheatmenu_trust_Destroy();

#endif