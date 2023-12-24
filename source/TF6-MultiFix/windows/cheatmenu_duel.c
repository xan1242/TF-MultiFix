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
#include "../YgWindow.h"
#include "../dueleng.h"
#include "multifixwindow.h"
#include "cheatmenu_duel.h"
#include "../../../includes/psp/pspmallochelper.h"

YgSelWnd* cheatmenu_duel_Window;
int cheatmenu_duel_bInited = 0;
int cheatmenu_duel_bNotifyDestroy = 0;

ygBasicWindowPack* cheatmenu_duel_Window2;
int cheatmenu_duel_bInited2 = 0;

int cheatmenu_duel_SetOppLP = 0;
int cheatmenu_duel_SetPlayerLP = 8000;

wchar_t cheatmenu_duel_Caption[] = L"Duel Cheat Menu";
#define CHEATMENU_DUEL_MAXVISIBLEITEMS 4
#define CHEATMENU_DUEL_MAXTEXT 128
#define CHEATMENU_DUEL_MAXVALTEXT 32
#define CHEATMENU_DUEL_VALPOSITION 3.6f
#define CHEATMENU_DUEL2_MAXTEXT 256

char* cheatmenu_duel_ItemNames[] =
{
    CHEATMENU_DUEL_ITEM_NAME_SETOPPONENTLP,
    CHEATMENU_DUEL_ITEM_NAME_SETPLAYERLP,
    CHEATMENU_DUEL_ITEM_NAME_DRAWCARD,
    CHEATMENU_DUEL_ITEM_NAME_TAKEAICONTROL,
    CHEATMENU_DUEL_ITEM_NAME_GIVEAICONTROL,
};

char* cheatmenu_duel_ItemDescriptions[] =
{
    CHEATMENU_DUEL_ITEM_DESC_SETOPPONENTLP,
    CHEATMENU_DUEL_ITEM_DESC_SETPLAYERLP,
    CHEATMENU_DUEL_ITEM_DESC_DRAWCARD,
    CHEATMENU_DUEL_ITEM_DESC_TAKEAICONTROL,
    CHEATMENU_DUEL_ITEM_DESC_GIVEAICONTROL,
};

mfWindowSetting cheatmenu_duel_Settings[CHEATMENU_DUEL_ITEM_COUNT] =
{
    {NULL, NULL, 0, UINT16_MAX, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_INT, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_SETOPPONENTLP, NULL, NULL},
    {NULL, NULL, 0, UINT16_MAX, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_INT, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_SETPLAYERLP, NULL, NULL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_DRAWCARD, NULL, NULL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_TAKEAICONTROL, NULL, NULL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 0, 1, 0, 0, CHEATMENU_DUEL_ITEM_GIVEAICONTROL, NULL, NULL},
};

mfWindowSetting* cheatmenu_duel_SettingDrawList[CHEATMENU_DUEL_ITEM_COUNT];

int cheatmenu_duel_IsActive()
{
    return (cheatmenu_duel_bInited != 0) || (cheatmenu_duel_Window != NULL);
}

void _cheatmenu_duel_Destroy()
{
    cheatmenu_duel_bInited = 0;
    YgSelWnd_Term(cheatmenu_duel_Window);
    psp_free(cheatmenu_duel_Window);
    cheatmenu_duel_Window = NULL;
}

void _cheatmenu_duel_Destroy2()
{
    cheatmenu_duel_bInited2 = 0;
    if (cheatmenu_duel_Window2)
    {
        ygBasicWindow_Term(&cheatmenu_duel_Window2->res);
        psp_free(cheatmenu_duel_Window2);
        cheatmenu_duel_Window2 = NULL;
    }
}

void cheatmenu_duel_Destroy()
{
    cheatmenu_duel_bNotifyDestroy = 1;
    _cheatmenu_duel_Destroy2();
    _cheatmenu_duel_Destroy();
}

uintptr_t cheatmenu_duel_Callback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    mfWindowSetting* currSetting = cheatmenu_duel_SettingDrawList[item_index];
    //sceKernelPrintf("showing opt: %s", currSetting->name);

    YgFont_SetEhPckt(ehpacket);

    YgFont_SetSize(15, 15);
    YgFont_SetRubyCharFlg(0);
    YgFont_SetShadowFlg(1);
    YgFont_SetChColorFlg(1);
    if (currSetting->greyedout)
    {
        YgFont_SetShadowFlg(0);
        YgFont_SetDefaultColor(0xFF7F7F7F);
    }
    else
    {
        YgFont_SetShadowFlg(1);
        YgFont_SetDefaultColor(0xFF000000);
    }

    char sprintfbuf[CHEATMENU_DUEL_MAXTEXT];
    wchar_t convBuffer[CHEATMENU_DUEL_MAXTEXT];

    YgSys_strcpy(sprintfbuf, currSetting->name);

    sceCccUTF8toUTF16(convBuffer, ((CHEATMENU_DUEL_MAXTEXT - 1) * sizeof(wchar_t)), sprintfbuf);
    YgFont_PrintLine64(X << 6, (Y + 4) << 6, (480 - X) << 6, convBuffer);

    switch (currSetting->type)
    {
    case MFWINDOW_SETTING_TYPE_BOOL:
    {
        if (*(currSetting->val))
            YgSys_strcpy(sprintfbuf, MFWINDOW_LABEL_BOOL_TRUE);
        else
        {
            YgFont_SetShadowFlg(0);
            YgFont_SetDefaultColor(0xFF7F7F7F);
            YgSys_strcpy(sprintfbuf, MFWINDOW_LABEL_BOOL_FALSE);
        }
        break;
    }
    case MFWINDOW_SETTING_TYPE_FLOAT:
    {
        YgSys_sprintf(sprintfbuf, "<%.2f>", *(currSetting->fval));
        break;
    }
    case MFWINDOW_SETTING_TYPE_INT:
    {
        YgSys_sprintf(sprintfbuf, "<%d>", *(currSetting->val));
        break;
    }
    case MFWINDOW_SETTING_TYPE_NONE:
    default:
    {
        break;
    }
    }

    if (currSetting->type != MFWINDOW_SETTING_TYPE_NONE)
    {
        if (currSetting->greyedout)
        {
            YgFont_SetShadowFlg(0);
            YgFont_SetDefaultColor(0xFF7F7F7F);
        }

        sceCccUTF8toUTF16(convBuffer, ((CHEATMENU_DUEL_MAXVALTEXT - 1) * sizeof(wchar_t)), sprintfbuf);
        // manually right justify
        int valXpos = cheatmenu_duel_Window->window.width + cheatmenu_duel_Window->window.Xpos - (YgFont_GetStrWidth(convBuffer) >> 6) - MFWINDOW_SELWIDTH_DIFF;
        YgFont_PrintLine64(valXpos << 6, (Y + 4) << 6, (480 - X) << 6, convBuffer);
    }

    return YgFont_GetEhPckt();
}

void cheatmenu_duel_Create()
{
    if (cheatmenu_duel_Window)
        psp_free(cheatmenu_duel_Window);
    cheatmenu_duel_Window = (YgSelWnd*)psp_malloc(sizeof(YgSelWnd));
    YgSys_memset(cheatmenu_duel_Window, 0, sizeof(YgSelWnd));
    cheatmenu_duel_Window->heapptr = helpers_GetMainEhHeap();
    cheatmenu_duel_Window->window.caption = cheatmenu_duel_Caption;
    cheatmenu_duel_Window->itemcount = 0;
    // lock all by default
    cheatmenu_duel_Window->itemLockBitfield = 0xFFFFFFFF;

    // assign some defaults
    for (int i = 0; i < CHEATMENU_DUEL_ITEM_COUNT; i++)
    {
        cheatmenu_duel_Settings[i].name = cheatmenu_duel_ItemNames[i];
        cheatmenu_duel_Settings[i].description = cheatmenu_duel_ItemDescriptions[i];
    }

    cheatmenu_duel_Settings[CHEATMENU_DUEL_ITEM_SETOPPONENTLP].val = &cheatmenu_duel_SetOppLP;
    cheatmenu_duel_Settings[CHEATMENU_DUEL_ITEM_SETPLAYERLP].val = &cheatmenu_duel_SetPlayerLP;

    for (int i = 0; i < CHEATMENU_DUEL_ITEM_COUNT; i++)
    {
        if (!cheatmenu_duel_Settings[i].hidden)
        {
            int j = cheatmenu_duel_Window->itemcount;
            cheatmenu_duel_SettingDrawList[j] = &cheatmenu_duel_Settings[i];
            if (cheatmenu_duel_SettingDrawList[j]->selectable)
            {
                cheatmenu_duel_Window->itemLockBitfield &= ~(YGSEL_LOCKITEM(j));
            }
            cheatmenu_duel_Window->itemcount++;
        }
    }

    cheatmenu_duel_Window->maxitems = CHEATMENU_DUEL_MAXVISIBLEITEMS;
    cheatmenu_duel_Window->selFlags = YGSEL_HIGHLIGHT | YGSEL_VERTICAL;

    cheatmenu_duel_Window->window.width = 300;
    if (cheatmenu_duel_Window->itemcount < CHEATMENU_DUEL_MAXVISIBLEITEMS)
        cheatmenu_duel_Window->window.height = (32 * cheatmenu_duel_Window->itemcount) - (4 * cheatmenu_duel_Window->itemcount);
    else
        cheatmenu_duel_Window->window.height = (32 * CHEATMENU_DUEL_MAXVISIBLEITEMS) - (4 * CHEATMENU_DUEL_MAXVISIBLEITEMS);

    cheatmenu_duel_Window->window.color = 0xFFFFFFFF;
    cheatmenu_duel_Window->itemDrawCallback = (uintptr_t)&cheatmenu_duel_Callback;

    cheatmenu_duel_Window->window.unk3 = 1;
    cheatmenu_duel_Window->window.windowBGColor = YGWINDOW_BG_LIGHT;
    cheatmenu_duel_Window->window.captionBGColor = YGWINDOW_BG_DARK;

    cheatmenu_duel_Window->window.bWindowCaption = 1;
    cheatmenu_duel_Window->window.bAutoSizeCaption = 1;
    cheatmenu_duel_Window->window.captionWidth = (int)((float)cheatmenu_duel_Window->window.width * 0.65f);
    cheatmenu_duel_Window->window.captionHeight = 16;
    cheatmenu_duel_Window->window.captionFontSize = 12;
    cheatmenu_duel_Window->window.captionFontColor = 0xFFFFFFFF;
    cheatmenu_duel_Window->window.bFontShadow = 1;

    int SelDrawWidth = cheatmenu_duel_Window->window.width;
    cheatmenu_duel_Window->selDrawWidth1 = SelDrawWidth - MFWINDOW_SELWIDTH_DIFF;
    cheatmenu_duel_Window->selDrawHeight1 = 25;
    cheatmenu_duel_Window->selDrawWidth2 = SelDrawWidth - MFWINDOW_SELWIDTH_DIFF;
    cheatmenu_duel_Window->selDrawHeight1 = 25;

    YgSelWnd_Init(cheatmenu_duel_Window);
    cheatmenu_duel_Window->window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)cheatmenu_duel_Window->window.width * 0.5f));
    cheatmenu_duel_Window->window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)cheatmenu_duel_Window->window.height * 0.5f));
    cheatmenu_duel_bInited = 1;
}

void cheatmenu_duel_Create2()
{
    if (cheatmenu_duel_Window2)
        psp_free(cheatmenu_duel_Window2);
    cheatmenu_duel_Window2 = (ygBasicWindowPack*)psp_malloc(sizeof(ygBasicWindowPack));

    ygBasicWindow_Init(&cheatmenu_duel_Window2->res, helpers_GetMainEhHeap());
    YgSys_memset(&cheatmenu_duel_Window2->window, 0, sizeof(ygBasicWindow));

    cheatmenu_duel_Window2->window.color = 0xFFFFFFFF;
    cheatmenu_duel_Window2->window.unk3 = 1;

    cheatmenu_duel_Window2->window.width = cheatmenu_duel_Window->window.width;
    cheatmenu_duel_Window2->window.height = 64;

    cheatmenu_duel_Window2->window.Xpos = cheatmenu_duel_Window->window.Xpos;
    cheatmenu_duel_Window2->window.Ypos = cheatmenu_duel_Window->window.Ypos + cheatmenu_duel_Window->window.height + 4;

    cheatmenu_duel_Window2->window.windowBGColor = YGWINDOW_BG_DARK;

    cheatmenu_duel_Window2->window.windowFontSize = 12;
    cheatmenu_duel_Window2->window.windowFontColor = 0xFFFFFFFF;
    cheatmenu_duel_Window2->window.bFontShadow = 1;

    cheatmenu_duel_Window2->window.unk43 = 1;
    cheatmenu_duel_Window2->window.unk44 = 1;

    ygBasicWindow_Create(&cheatmenu_duel_Window2->res, &cheatmenu_duel_Window2->window);
    ygBasicWindow_ReqestOpenAnim(&cheatmenu_duel_Window2->res, &cheatmenu_duel_Window2->window);
    cheatmenu_duel_bInited2 = 1;
}

int cheatmenu_duel_Draw2()
{
    if (!cheatmenu_duel_bInited2)
        return 0;

    if (cheatmenu_duel_bNotifyDestroy)
        return 0;

    int currItem = cheatmenu_duel_Window->currentItem + cheatmenu_duel_Window->currentItemPage;
    mfWindowSetting* currSetting = cheatmenu_duel_SettingDrawList[currItem];

    wchar_t convBuffer[CHEATMENU_DUEL2_MAXTEXT];
    sceCccUTF8toUTF16(convBuffer, (CHEATMENU_DUEL2_MAXTEXT * sizeof(wchar_t)) - 1, currSetting->description);
    cheatmenu_duel_Window2->window.windowText = convBuffer;

    uintptr_t packet = EhPckt_Open(10, 0);

    ygBasicWindow_Draw((uintptr_t)&packet, &cheatmenu_duel_Window2->res);

    EhPckt_Close(packet);

    cheatmenu_duel_Window2->window.windowText = NULL;

    //if (mfWindow->decideStatus)
    //{
    //    _mfwindow2_Destroy();
    //    return -1;
    //}

    return 0;
}

int cheatmenu_duel_Draw()
{
    if (!cheatmenu_duel_bInited)
    {
        cheatmenu_duel_bNotifyDestroy = 0;

        cheatmenu_duel_SetOppLP = 0;
        cheatmenu_duel_SetPlayerLP = 8000;

        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);
        cheatmenu_duel_Create();
        cheatmenu_duel_Create2();
        return 0;
    }

    if (cheatmenu_duel_bNotifyDestroy)
        return 0;

    helpers_SetDialogBoxWantsIO(1);

    int currItem = cheatmenu_duel_Window->currentItem + cheatmenu_duel_Window->currentItemPage;
    mfWindowSetting* setting = cheatmenu_duel_SettingDrawList[currItem];
    mfWindowSetting_HandleExtraControls(setting);
    YgSelWnd_Cont(cheatmenu_duel_Window);

    uintptr_t packet = EhPckt_Open(10, 0);
    YgSelWnd_Draw((uintptr_t)&packet, cheatmenu_duel_Window);
    EhPckt_Close(packet);

    cheatmenu_duel_Draw2();

    if (cheatmenu_duel_Window->decideStatus)
    {
        cheatmenu_duel_Destroy();
        return -1;
    }

    return 0;
}

