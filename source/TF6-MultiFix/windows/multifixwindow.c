//
// Yu-Gi-Oh! Tag Force - MultiFix configuration window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifixconfig.h"
#include "../YgWindow.h"
#include <pspctrl.h>
#include <pspuser.h>


YgSelWnd mfWindow;
wchar_t mfWindowCaption[] = L"MultiFix Configuration";
int bMfWindowInited = 0;
int mfwindow_bValueChanged = 0;
//int bShowMfWindow = 0;

#define MFWINDOW_ZORDER 10
#define MFWINDOW_MAXVISIBLEITEMS 4

#define MFWINDOW_SETTING_TYPE_INT 0
#define MFWINDOW_SETTING_TYPE_BOOL 1
#define MFWINDOW_SETTING_TYPE_FLOAT 2
#define MFWINDOW_SETTING_TYPE_INTSTRING 3
#define MFWINDOW_SETTING_TYPE_EMPTY 4

#define MFWINDOW_VALPOSITION 3.6f

char* mfWindowItems[] =
{
    "Use X as confirm button",
    "Matrix font on cards",
    "See partner's cards",
    "Disable duel \"Help\" icon",
    "Disable install feature",
};

//char* mfWindowItemDrawList[sizeof(mfWindowItems) / sizeof(char*)];

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
    char* name;
    char* description;
}mfWindowSetting;

mfWindowSetting mfWindowSettings[sizeof(mfWindowItems) / sizeof(char*)];
mfWindowSetting* mfWindowSettingDrawList[sizeof(mfWindowItems) / sizeof(char*)];

#define MFWINDOW_MAXTEXT 128
#define MFWINDOW_MAXVALTEXT 32

ygBasicWindowPack mfWindow2;
int bMfWindow2Inited = 0;
char* mfWindow2Items[] =
{
    "Swaps cross and circle as confirm buttons.",
    "Enables matrix font style (uppercase glyphs for lowercase letters) on card names, types, etc.",
    "Shows partner's cards mid-duel, just like the older Tag Force games.",
    "Disables the \"Help\" icon in the lower right corner during duels. The icon can obstruct the visibility of the card there.",
    "Disables the \"Install Data\" feature. It is recommended to keep it disabled as it could potentially cause issues for translations and/or mods. This acts as a safe guard against it.",
};

#define MFWINDOW2_MAXTEXT 256

uintptr_t mfWindowCallback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    mfWindowSetting* currSetting = mfWindowSettingDrawList[item_index];

    YgFont_SetEhPckt(ehpacket);

    YgFont_SetSize(15, 15);
    YgFont_SetRubyCharFlg(0);
    YgFont_SetShadowFlg(1);
    YgFont_SetChColorFlg(1);
    YgFont_SetDefaultColor(0xFF000000);

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
                YgSys_strcpy(sprintfbuf, "<On>");
            else
            {
                YgFont_SetShadowFlg(0);
                YgFont_SetDefaultColor(0xFF7F7F7F);
                YgSys_strcpy(sprintfbuf, "<Off>");
            }
            break;
        }
        case MFWINDOW_SETTING_TYPE_FLOAT:
        {
            YgSys_sprintf(sprintfbuf, "<%.2f>", *(currSetting->fval));
            break;
        }
        case MFWINDOW_SETTING_TYPE_INT:
        default:
        {
            YgSys_sprintf(sprintfbuf, "<%d>", *(currSetting->val));
            break;
        }
    }

    
    sceCccUTF8toUTF16(convBuffer, ((MFWINDOW_MAXVALTEXT - 1) * sizeof(wchar_t)), sprintfbuf);
    float valXpos = (float)X * MFWINDOW_VALPOSITION;
    YgFont_PrintLine64(((int)valXpos) << 6, (Y + 4) << 6, (480 - X) << 6, convBuffer);


    return YgFont_GetEhPckt();
}

void mfwindow_Create()
{
    MultiFixConfig* config = mfconfig_GetConfig();
    mfwindow_bValueChanged = 0;
    mfWindowSettings[0].val = &config->bSwapConfirmButtons;
    mfWindowSettings[1].val = &config->bMatrixFont;
    mfWindowSettings[2].val = &config->bSeePartnerCards;
    mfWindowSettings[3].val = &config->bDisableDuelHelpIcon;
    mfWindowSettings[4].val = &config->bDisableInstall;

    mfWindowSettings[0].min = 0;
    mfWindowSettings[1].min = 0;
    mfWindowSettings[2].min = 0;
    mfWindowSettings[3].min = 0;
    mfWindowSettings[4].min = 0;

    mfWindowSettings[0].max = 1;
    mfWindowSettings[1].max = 1;
    mfWindowSettings[2].max = 1;
    mfWindowSettings[3].max = 1;
    mfWindowSettings[4].max = 1;

    mfWindowSettings[0].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[1].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[2].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[3].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[4].type = MFWINDOW_SETTING_TYPE_BOOL;

    mfWindowSettings[0].hidden = 0;
    mfWindowSettings[1].hidden = 0;
    mfWindowSettings[2].hidden = 0;
    mfWindowSettings[3].hidden = 0;
    mfWindowSettings[4].hidden = 0;

    mfWindowSettings[0].name = mfWindowItems[0];
    mfWindowSettings[1].name = mfWindowItems[1];
    mfWindowSettings[2].name = mfWindowItems[2];
    mfWindowSettings[3].name = mfWindowItems[3];
    mfWindowSettings[4].name = mfWindowItems[4];

    mfWindowSettings[0].description = mfWindow2Items[0];
    mfWindowSettings[1].description = mfWindow2Items[1];
    mfWindowSettings[2].description = mfWindow2Items[2];
    mfWindowSettings[3].description = mfWindow2Items[3];
    mfWindowSettings[4].description = mfWindow2Items[4];


    YgSys_memset(&mfWindow, 0, sizeof(YgSelWnd));
    YgSys_memset(&mfWindowSettingDrawList, 0, sizeof(mfWindowSettingDrawList));
    mfWindow.heapptr = helpers_GetMainEhHeap();
    mfWindow.window.caption = mfWindowCaption;
    mfWindow.itemcount = 0;


    for (int i = 0; i < (sizeof(mfWindowItems) / sizeof(wchar_t*)); i++)
    {
        if (!mfWindowSettings[i].hidden)
        {
            mfWindowSettingDrawList[mfWindow.itemcount] = &mfWindowSettings[i];
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
    // lock all
    mfWindow.itemLockBitfield = 0xFFFFFFFF;

    int SelDrawWidth = mfWindow.window.width;
    mfWindow.selDrawWidth1 = SelDrawWidth - 12;
    mfWindow.selDrawHeight1 = 25;
    mfWindow.selDrawWidth2 = SelDrawWidth - 12;
    mfWindow.selDrawHeight1 = 25;

    YgSelWnd_Init(&mfWindow);
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

    //sceKernelPrintf("curr item: 0x%08X | val2: 0x%08X\n", mfWindow.currentItem, mfWindow.unk54);

    int currItem = mfWindow.currentItem + mfWindow.currentItemPage;

    uintptr_t packet = EhPckt_Open(MFWINDOW_ZORDER, 0);

    uint32_t buttons = GetPadButtons(1);
    mfWindowSetting* setting = mfWindowSettingDrawList[currItem];
    int* val = setting->val;

    if (buttons & PSP_CTRL_LEFT)
    {
        *val -= 1;
        mfwindow_bValueChanged = 1;
        YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
    }

    if (buttons & PSP_CTRL_RIGHT)
    {
        *val += 1;
        mfwindow_bValueChanged = 1;
        YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
    }

    *val = loopAround(*val, setting->min, setting->max);



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
        int retval = (mfWindow.decideStatus & 0xFF) | ((currItem & 0xFF) << 8) | ((mfwindow_bValueChanged & 0xFF) << 16);

        return retval;
    }

    return 0;
}

