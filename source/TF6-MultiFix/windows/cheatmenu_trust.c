//
// Yu-Gi-Oh! Tag Force - Character Trust Cheat Menu
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../MenuWindow.h"
#include "cheatmenu_trust.h"
#include "../../../includes/psp/pspmallochelper.h"

MenuWindow* chtwndTrust;

int cheatmenu_trust_last_item = 0;
int cheatmenu_trust_last_page = 0;

MenuWindowItem* cheatmenu_trust_charaList;

int cheatmenu_trust_cbReadTrust(uintptr_t charaID)
{
    return YgSys_GetTrust(charaID);
}

int cheatmenu_trust_cbWriteTrust(int value, uintptr_t charaID)
{
    YgSys_SetTrust(charaID, value);
    return 0;
}

int cheatmenu_trust_IsActive()
{
	return chtwndTrust != NULL;
}

void cheatmenu_trust_Destroy()
{
    if (chtwndTrust)
    {
        cheatmenu_trust_last_item = chtwndTrust->selwnd->currentItem;
        cheatmenu_trust_last_page = chtwndTrust->selwnd->currentItemPage;

        if (MenuWindow_IsActive(chtwndTrust))
        {
            MenuWindow_Destroy(chtwndTrust);
        }

        psp_free(chtwndTrust);
        chtwndTrust = NULL;
    }

    if (cheatmenu_trust_charaList)
    {
        psp_free(cheatmenu_trust_charaList);
        cheatmenu_trust_charaList = NULL;
    }
}

uintptr_t cheatmenu_trust_Callback(uintptr_t ehpacket, int item_index, int X, int Y)
{
#ifdef CHEATMENU_TRUST_DEBUG_NUMS
    MenuWindowItem* currItem = chtwndTrust->itemDrawList[item_index];
    int Y_corrected = Y + 2;

    wchar_t convBuffer[MENUWINDOW_ITEM_MAXTEXT];

    int charaID = currItem->cbData;

    char sprintfbuf[32];
    YgSys_sprintf(sprintfbuf, "[%d]", charaID);
    size_t txtlen = YgSys_strlen(sprintfbuf) + 1;
    sceCccUTF8toUTF16(convBuffer, txtlen * sizeof(wchar_t), sprintfbuf);

    YgFont_SetEhPckt(ehpacket);
    YgFont_SetSize(MENUWINDOW_ITEM_FONTSIZE, MENUWINDOW_ITEM_FONTSIZE);
    YgFont_SetRubyCharFlg(0);
    YgFont_SetShadowFlg(1);
    YgFont_SetChColorFlg(1);
    YgFont_SetShadowFlg(1);
    YgFont_SetDefaultColor(0xFF000000);

    YgFont_PrintLine64((X + 100) << 6, Y_corrected << 6, (480 - X) << 6, convBuffer);
    return MenuWindow_Callback(YgFont_GetEhPckt(), item_index, X, Y, chtwndTrust);
#else
    return MenuWindow_Callback(ehpacket, item_index, X, Y, chtwndTrust);
#endif
}

void cheatmenu_trust_Create()
{
    if (chtwndTrust)
        psp_free(chtwndTrust);
    chtwndTrust = (MenuWindow*)psp_malloc(sizeof(MenuWindow));
    YgSys_memset(chtwndTrust, 0, sizeof(YgSelWnd));

    char characterDupes[YG_CHARACTER_COUNT - (CHEATMENU_TRUST_SKIP_TOP + CHEATMENU_TRUST_SKIP_BOTTOM)];
    YgSys_memset(characterDupes, 0, sizeof(char) * (YG_CHARACTER_COUNT - (CHEATMENU_TRUST_SKIP_TOP + CHEATMENU_TRUST_SKIP_BOTTOM)));

    int characterCount = YG_CHARACTER_COUNT - (CHEATMENU_TRUST_SKIP_TOP + CHEATMENU_TRUST_SKIP_BOTTOM);
    wchar_t* lastName = 0;
    for (int i = CHEATMENU_TRUST_SKIP_TOP; i < (YG_CHARACTER_COUNT - CHEATMENU_TRUST_SKIP_BOTTOM); i++)
    {
        if (lastName == YgSys_GetChrNameFromID(i, 0))
        {
            characterDupes[i] = 1;
            characterCount--;
            continue;
        }
        lastName = YgSys_GetChrNameFromID(i, 0);
    }
    // second pass for repeats that are coming from bottom of the list...
    for (int i = CHEATMENU_TRUST_SKIP_TOP; i < (YG_CHARACTER_COUNT - CHEATMENU_TRUST_SKIP_BOTTOM); i++)
    {
        if (characterDupes[i])
            continue;
    
        wchar_t* name = YgSys_GetChrNameFromID(i, 0);
        for (int j = (YG_CHARACTER_COUNT - CHEATMENU_TRUST_SKIP_BOTTOM) - 1; j >= 0; j--)
        {
            if (characterDupes[j])
                continue;

            if (name == YgSys_GetChrNameFromID(j, 0) && (i != j))
            {
                //sceKernelPrintf("names [%d] 0x%08X & [%d] 0x%08X match", i, name, j, YgSys_GetChrNameFromID(j, 0));
                characterDupes[j] = 1;
                characterCount--;
                break;
            }
        }
    }

    //sceKernelPrintf("name[170] = 0x%08X", YgSys_GetChrNameFromID(170, 0));
    //sceKernelPrintf("name[2] = 0x%08X", YgSys_GetChrNameFromID(2, 0));

    chtwndTrust->caption = CHEATMENU_TRUST_CAPTION;
    chtwndTrust->bBlockGameControl = 1;
    chtwndTrust->zOrder = MULTIFIX_WINDOW_ZORDER;
    chtwndTrust->itemDrawCallback = (uintptr_t)&cheatmenu_trust_Callback;
    chtwndTrust->itemCount = characterCount;
    
    cheatmenu_trust_charaList = (MenuWindowItem*)psp_malloc(sizeof(MenuWindowItem) * chtwndTrust->itemCount);
    YgSys_memset(cheatmenu_trust_charaList, 0, sizeof(MenuWindowItem) * chtwndTrust->itemCount);
    chtwndTrust->items = cheatmenu_trust_charaList;

    int j = 0;

    for (int i = CHEATMENU_TRUST_SKIP_TOP; i < (YG_CHARACTER_COUNT - CHEATMENU_TRUST_SKIP_BOTTOM); i++)
    {
        if (characterDupes[i])
            continue;

        MenuWindowItem* item = &(cheatmenu_trust_charaList[j]);
        item->val = NULL;
        item->min = 0;
        item->max = YG_CHARACTER_MAXTRUST;
        item->type = MENUWINDOW_ITEM_TYPE_INT;
        item->hidden = 0;
        item->selectable = 0;
        item->greyedout = 0;
        item->loopable = 0;
        item->bWideCharName = 1;
        item->bWideCharDesc = 0;
        item->index = (unsigned int)j;
        item->name = (char*)YgSys_GetChrNameFromID(i, 0);
        item->description = CHEATMENU_TRUST_DESC;
        item->options = NULL;
        item->cbValRead = (uintptr_t)cheatmenu_trust_cbReadTrust;
        item->cbValWrite = (uintptr_t)cheatmenu_trust_cbWriteTrust;
        item->cbData = (uintptr_t)i;
        j++;

        lastName = (wchar_t*)item->name;
    }

    MenuWindow_Create(chtwndTrust);

    chtwndTrust->selwnd->currentItemPage = cheatmenu_trust_last_page;
    chtwndTrust->selwnd->currentItem = cheatmenu_trust_last_item;
}

int cheatmenu_trust_Draw()
{
    if (!chtwndTrust)
    {
        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);

        cheatmenu_trust_Create();
        return 0;
    }

    int menuRes = MenuWindow_Draw(chtwndTrust);
    if (menuRes)
    {
        cheatmenu_trust_Destroy();
        return menuRes;
    }

    return 0;
}
