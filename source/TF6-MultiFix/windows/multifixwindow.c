//
// Yu-Gi-Oh! Tag Force - MultiFix configuration window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifixconfig.h"
#include "../YgWindow.h"
#include "multifixwindow.h"
#include <pspctrl.h>
#include <pspuser.h>


YgSelWnd mfWindow;
wchar_t mfWindowCaption[] = L"MultiFix Configuration";
int bMfWindowInited = 0;
int mfwindow_bValueChanged = 0;
int mfwindow_bCheatsEnabled = 0;
int mfwindow_bCheatLocals = 0;

ygBasicWindowPack mfWindow2;
int bMfWindow2Inited = 0;

#define MFWINDOW_ZORDER 10
#define MFWINDOW_MAXVISIBLEITEMS 4
#define MFWINDOW_VALPOSITION 3.6f
#define MFWINDOW_MAXTEXT 128
#define MFWINDOW_MAXVALTEXT 32
#define MFWINDOW2_MAXTEXT 256

char* mfWindowItemNames[] =
{
    MFWINDOW_ITEM_NAME_SWAPBUTTON,
    MFWINDOW_ITEM_NAME_MATRIXFONT,
    MFWINDOW_ITEM_NAME_PARTNERCARD,
    MFWINDOW_ITEM_NAME_DUELHELP,
    MFWINDOW_ITEM_NAME_INSTALLDISABLE,
    MFWINDOW_ITEM_NAME_SOUNDTEST,
    MFWINDOW_ITEM_NAME_CHEATSGLOBAL,
    MFWINDOW_ITEM_NAME_CHEATSLOCAL,
    MFWINDOW_ITEM_NAME_ABOUT,
};

char* mfWindowItemDescriptions[] =
{
    MFWINDOW_ITEM_DESC_SWAPBUTTON,
    MFWINDOW_ITEM_DESC_MATRIXFONT,
    MFWINDOW_ITEM_DESC_PARTNERCARD,
    MFWINDOW_ITEM_DESC_DUELHELP,
    MFWINDOW_ITEM_DESC_INSTALLDISABLE,
    MFWINDOW_ITEM_DESC_SOUNDTEST,
    MFWINDOW_ITEM_DESC_CHEATSGLOBAL,
    MFWINDOW_ITEM_DESC_CHEATSLOCAL,
    MFWINDOW_ITEM_DESC_ABOUT,
};

typedef struct _mfWindowSetting
{
    int* val;
    float* fval;
    int min;
    int max;
    float fmin;
    float fmax;
    int type;
    int hidden;
    int selectable;
    int greyedout;
    int index;
    char* name;
    char* description;
}mfWindowSetting;

mfWindowSetting mfWindowSettings[MFWINDOW_ITEM_COUNT] =
{
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_BOOL, 0, 0, 0, MFWINDOW_ITEM_SWAPBUTTON, NULL, NULL},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_BOOL, 0, 0, 0, MFWINDOW_ITEM_MATRIXFONT, NULL, NULL},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_BOOL, 0, 0, 0, MFWINDOW_ITEM_PARTNERCARD, NULL, NULL},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_BOOL, 0, 0, 0, MFWINDOW_ITEM_DUELHELP, NULL, NULL},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_BOOL, 0, 0, 0, MFWINDOW_ITEM_INSTALLDISABLE, NULL, NULL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 0, 1, 0, MFWINDOW_ITEM_SOUNDTEST, NULL, NULL},
    // cheats are always here
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 1, 1, 0, MFWINDOW_ITEM_CHEATSGLOBAL, NULL, NULL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 1, 1, 0, MFWINDOW_ITEM_CHEATSLOCAL, NULL, NULL},
    // about is always last!
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MFWINDOW_SETTING_TYPE_NONE, 0, 1, 0, MFWINDOW_ITEM_ABOUT, NULL, NULL},
};


mfWindowSetting* mfWindowSettingDrawList[MFWINDOW_ITEM_COUNT];

uintptr_t mfWindowCallback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    mfWindowSetting* currSetting = mfWindowSettingDrawList[item_index];
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

    char sprintfbuf[MFWINDOW_MAXTEXT];
    wchar_t convBuffer[MFWINDOW_MAXTEXT];

    YgSys_strcpy(sprintfbuf, currSetting->name);

    sceCccUTF8toUTF16(convBuffer, ((MFWINDOW_MAXTEXT - 1) * sizeof(wchar_t)), sprintfbuf);
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

        sceCccUTF8toUTF16(convBuffer, ((MFWINDOW_MAXVALTEXT - 1) * sizeof(wchar_t)), sprintfbuf);
        float valXpos = (float)X * MFWINDOW_VALPOSITION;
        YgFont_PrintLine64(((int)valXpos) << 6, (Y + 4) << 6, (480 - X) << 6, convBuffer);
    }

    return YgFont_GetEhPckt();
}

void mfwindow_Create()
{
    // assign some defaults
    for (int i = 0; i < MFWINDOW_ITEM_COUNT; i++)
    {
        mfWindowSettings[i].index = i;
        mfWindowSettings[i].name = mfWindowItemNames[i];
        mfWindowSettings[i].description = mfWindowItemDescriptions[i];
    }

    MultiFixConfig* config = mfconfig_GetConfig();
    mfwindow_bValueChanged = 0;
    mfWindowSettings[MFWINDOW_ITEM_SWAPBUTTON].val = &config->bSwapConfirmButtons;
    mfWindowSettings[MFWINDOW_ITEM_MATRIXFONT].val = &config->bMatrixFont;
    mfWindowSettings[MFWINDOW_ITEM_PARTNERCARD].val = &config->bSeePartnerCards;
    mfWindowSettings[MFWINDOW_ITEM_DUELHELP].val = &config->bDisableDuelHelpIcon;
    mfWindowSettings[MFWINDOW_ITEM_INSTALLDISABLE].val = &config->bDisableInstall;

    if (mfwindow_bCheatsEnabled)
    {
        mfWindowSettings[MFWINDOW_ITEM_CHEATSGLOBAL].hidden = 0;
        mfWindowSettings[MFWINDOW_ITEM_CHEATSLOCAL].hidden = 0;

        // check if we have locals
        EhGameState state = GetGameState();
        sceKernelPrintf("state: %d", state);

        if ((state == EHSTATE_DUEL) ||
            (state == EHSTATE_SHOP))
        {
            mfwindow_bCheatLocals = 1;
        }
        else
        {
            mfwindow_bCheatLocals = 0;
        }

        if (mfwindow_bCheatLocals)
        {
            mfWindowSettings[MFWINDOW_ITEM_CHEATSLOCAL].greyedout = 0;
            mfWindowSettings[MFWINDOW_ITEM_CHEATSLOCAL].selectable = 1;
        }
        else
        {
            mfWindowSettings[MFWINDOW_ITEM_CHEATSLOCAL].greyedout = 1;
            mfWindowSettings[MFWINDOW_ITEM_CHEATSLOCAL].selectable = 0;
        }

    }

    YgSys_memset(&mfWindow, 0, sizeof(YgSelWnd));
    YgSys_memset(&mfWindowSettingDrawList, 0, sizeof(mfWindowSettingDrawList));
    mfWindow.heapptr = helpers_GetMainEhHeap();
    mfWindow.window.caption = mfWindowCaption;
    mfWindow.itemcount = 0;
    // lock all by default
    mfWindow.itemLockBitfield = 0xFFFFFFFF;

    for (int i = 0; i < MFWINDOW_ITEM_COUNT; i++)
    {
        if (!mfWindowSettings[i].hidden)
        {
            int j = mfWindow.itemcount;
            mfWindowSettingDrawList[j] = &mfWindowSettings[i];
            if (mfWindowSettingDrawList[j]->selectable)
            {
                mfWindow.itemLockBitfield &= ~(YGSEL_LOCKITEM(j));
            }
            mfWindow.itemcount++;
        }
    }

    mfWindow.maxitems = MFWINDOW_MAXVISIBLEITEMS;
    mfWindow.selFlags = YGSEL_HIGHLIGHT | YGSEL_VERTICAL;

    mfWindow.window.width = 300;
    if (mfWindow.itemcount < MFWINDOW_MAXVISIBLEITEMS)
        mfWindow.window.height = (32 * mfWindow.itemcount) - (4 * mfWindow.itemcount);
    else
        mfWindow.window.height = (32 * MFWINDOW_MAXVISIBLEITEMS) - (4 * MFWINDOW_MAXVISIBLEITEMS);

    mfWindow.window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)mfWindow.window.width * 0.5f));
    mfWindow.window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)mfWindow.window.height * 0.5f));

    mfWindow.window.color = 0xFFFFFFFF;
    mfWindow.itemDrawCallback = (uintptr_t)&mfWindowCallback;

    mfWindow.window.unk3 = 1;
    mfWindow.window.windowBGColor = YGWINDOW_BG_LIGHT;
    mfWindow.window.captionBGColor = YGWINDOW_BG_DARK;
    //mfWindow.window.bAutoSizeWindow = 1;

    mfWindow.window.bWindowCaption = 1;
    mfWindow.window.bAutoSizeCaption = 1; // this is broken until the font is initialized
    mfWindow.window.captionWidth = (int)((float)mfWindow.window.width * 0.65f);
    mfWindow.window.captionHeight = 16;
    mfWindow.window.bFontShadow = 1;
    // mfWindow.window.leftPadding = 0;
    // mfWindow.window.rightPadding = 0;
    // mfWindow.window.topPadding = 0;
    // mfWindow.window.bottomPadding = 0;
    // mfWindow.window.windowFontSize = 0;
    // mfWindow.window.windowFontColor = 0;
    // mfWindow.window.unk43 = 0;
    // mfWindow.window.unk44 = 0;

    mfWindow.window.captionFontSize = 12;
    mfWindow.window.captionFontColor = 0xFFFFFFFF;
    

    int SelDrawWidth = mfWindow.window.width;
    mfWindow.selDrawWidth1 = SelDrawWidth - 12;
    mfWindow.selDrawHeight1 = 25;
    mfWindow.selDrawWidth2 = SelDrawWidth - 12;
    mfWindow.selDrawHeight1 = 25;

    YgSelWnd_Init(&mfWindow);

    mfWindow.window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)mfWindow.window.width * 0.5f));
    mfWindow.window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)mfWindow.window.height * 0.5f));

    bMfWindowInited = 1;
}

void mfwindow2_Create()
{
    ygBasicWindow_Init(&mfWindow2.res, helpers_GetMainEhHeap());
    YgSys_memset(&mfWindow2.window, 0, sizeof(ygBasicWindow));

    mfWindow2.window.color = 0xFFFFFFFF;
    mfWindow2.window.unk3 = 1;

    mfWindow2.window.width = mfWindow.window.width;
    mfWindow2.window.height = 64;

    mfWindow2.window.Xpos = mfWindow.window.Xpos;
    mfWindow2.window.Ypos = mfWindow.window.Ypos + mfWindow.window.height + 4;

    mfWindow2.window.windowBGColor = YGWINDOW_BG_DARK;

    mfWindow2.window.windowFontSize = 12;
    mfWindow2.window.windowFontColor = 0xFFFFFFFF;
    mfWindow2.window.bFontShadow = 1;

    mfWindow2.window.unk43 = 1;
    mfWindow2.window.unk44 = 1;

    ygBasicWindow_Create(&mfWindow2.res, &mfWindow2.window);
    ygBasicWindow_ReqestOpenAnim(&mfWindow2.res, &mfWindow2.window);
    bMfWindow2Inited = 1;
}

int mfwindow2_Draw()
{
    if (!bMfWindow2Inited)
        return;

    int currItem = mfWindow.currentItem + mfWindow.currentItemPage;
    mfWindowSetting* currSetting = mfWindowSettingDrawList[currItem];

    wchar_t convBuffer[MFWINDOW2_MAXTEXT];
    sceCccUTF8toUTF16(convBuffer, (MFWINDOW2_MAXTEXT * sizeof(wchar_t)) - 1, currSetting->description);
    mfWindow2.window.windowText = convBuffer;

    uintptr_t packet = EhPckt_Open(MFWINDOW_ZORDER, 0);

    ygBasicWindow_Draw((uintptr_t)&packet, &mfWindow2.res);

    EhPckt_Close(packet);

    mfWindow2.window.windowText = NULL;

    if (mfWindow.decideStatus)
    {
        bMfWindow2Inited = 0;
        ygBasicWindow_Term(&mfWindow2.res);
        return -1;
    }

    return 0;
}

int mfwindow_GetItemCount()
{
    return MFWINDOW_ITEM_COUNT;
}

void mfwindow_SetCheatsEnabled(int val)
{
    mfwindow_bCheatsEnabled = val;
}

void mfwindow_SetCheatLocals(int val)
{
    mfwindow_bCheatLocals = val;
}

int mfwindow_Draw()
{
    if (!bMfWindowInited)
    {
        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);
        mfwindow_Create();
        mfwindow2_Create();
        return 0;
    }

    helpers_SetDialogBoxWantsIO(1);

    //sceKernelPrintf("item: 0x%08X | page: 0x%08X\n", mfWindow.currentItem, mfWindow.currentItemPage);

    int currItem = mfWindow.currentItem + mfWindow.currentItemPage;

    uintptr_t packet = EhPckt_Open(MFWINDOW_ZORDER, 0);

    uint32_t buttons = GetPadButtons(1);
    mfWindowSetting* setting = mfWindowSettingDrawList[currItem];
    int* val = setting->val;

    if (val)
    {
        if (buttons & PSP_CTRL_LEFT)
        {
            *val -= 1;
            mfwindow_bValueChanged = 1;
            YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
            *val = loopAround(*val, setting->min, setting->max);
        }

        if (buttons & PSP_CTRL_RIGHT)
        {
            *val += 1;
            mfwindow_bValueChanged = 1;
            YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
            *val = loopAround(*val, setting->min, setting->max);
        }
    }


    YgSelWnd_Cont(&mfWindow);
    YgSelWnd_Draw((uintptr_t)&packet, &mfWindow);

    EhPckt_Close(packet);

    mfwindow2_Draw();

    if (mfWindow.decideStatus)
    {
        bMfWindowInited = 0;
        YgSelWnd_Term(&mfWindow);

        // return value status pack
        // in order
        // 8 bits = decide status
        // 8 bits = item
        // 8 bits = mfwindow_bValueChanged
        int retval = (mfWindow.decideStatus & 0xFF) | ((setting->index & 0xFF) << 8) | ((mfwindow_bValueChanged & 0xFF) << 16);

        return retval;
    }

    return 0;
}

