//
// Yu-Gi-Oh! Tag Force - MultiFix configuration window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "helpers.h"
#include "multifixconfig.h"
#include "YgWindow.h"
#include <pspctrl.h>


YgSelWnd mfWindow;
wchar_t mfWindowCaption[] = L"MultiFix Configuration";
int bMfWindowInited = 0;
int mfwindow_bValueChanged = 0;
//int bShowMfWindow = 0;

#define MFWINDOW_SETTING_TYPE_INT 0
#define MFWINDOW_SETTING_TYPE_BOOL 1
#define MFWINDOW_SETTING_TYPE_FLOAT 2
#define MFWINDOW_SETTING_TYPE_INTSTRING 3

#define MFWINDOW_VALPOSITION 3.6f

char* mfWindowItems[] =
{
    "Use X as confirm button",
    "Matrix font on cards",
    "See partner's cards",
    "Disable install feature",
};

typedef struct _mfWindowSetting
{
    int* val;
    int min;
    int max;
    int type;
}mfWindowSetting;

mfWindowSetting mfWindowSettings[sizeof(mfWindowItems) / sizeof(char*)];

#define MFWINDOW_MAXTEXT 128
#define MFWINDOW_MAXVALTEXT 32

ygBasicWindowPack mfWindow2;
int bMfWindow2Inited = 0;
char* mfWindow2Items[] =
{
    "Swaps cross and circle as confirm buttons.",
    "Enables matrix font style (uppercase glyphs for lower-case letters) on card names, types, etc.",
    "Shows partner's cards mid-duel, just like the older Tag Force games.",
    "This disables the \"Install Data\" feature. It is recommended to keep it disabled as it could potentially cause issues for translations and/or mods. This acts as a safe guard against it.",
};

#define MFWINDOW2_MAXTEXT 512

uintptr_t mfWindowCallback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    YgFont_SetEhPckt(ehpacket);

    YgFont_SetSize(15, 15);
    YgFont_SetRubyCharFlg(0);
    YgFont_SetShadowFlg(1);
    YgFont_SetChColorFlg(1);
    YgFont_SetDefaultColor(0xFF000000);

    char sprintfbuf[MFWINDOW_MAXTEXT];
    wchar_t convBuffer[MFWINDOW_MAXTEXT];

    YgSys_strcpy(sprintfbuf, mfWindowItems[item_index]);

    sceCccUTF8toUTF16(convBuffer, MFWINDOW_MAXTEXT - 1, sprintfbuf);
    YgFont_PrintLine64(X << 6, (Y + 4) << 6, (480 - X) << 6, convBuffer);

    switch (mfWindowSettings[item_index].type)
    {
        case MFWINDOW_SETTING_TYPE_BOOL:
        {
            if (*mfWindowSettings[item_index].val)
                YgSys_strcpy(sprintfbuf, "<On>");
            else
                YgSys_strcpy(sprintfbuf, "<Off>");
            break;
        }
        case MFWINDOW_SETTING_TYPE_FLOAT:
        {
            YgSys_sprintf(sprintfbuf, "<%.2f>", *mfWindowSettings[item_index].val);
            break;
        }
        case MFWINDOW_SETTING_TYPE_INT:
        default:
        {
            YgSys_sprintf(sprintfbuf, "<%d>", *mfWindowSettings[item_index].val);
            break;
        }
    }

    
    sceCccUTF8toUTF16(convBuffer, MFWINDOW_MAXVALTEXT - 1, sprintfbuf);
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
    mfWindowSettings[3].val = &config->bDisableInstall;

    mfWindowSettings[0].min = 0;
    mfWindowSettings[1].min = 0;
    mfWindowSettings[2].min = 0;
    mfWindowSettings[3].min = 0;

    mfWindowSettings[0].max = 1;
    mfWindowSettings[1].max = 1;
    mfWindowSettings[2].max = 1;
    mfWindowSettings[3].max = 1;

    mfWindowSettings[0].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[1].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[2].type = MFWINDOW_SETTING_TYPE_BOOL;
    mfWindowSettings[3].type = MFWINDOW_SETTING_TYPE_BOOL;

    YgSys_memset(&mfWindow, 0, sizeof(YgSelWnd));
    mfWindow.heapptr = helpers_GetMainEhHeap();
    mfWindow.window.caption = mfWindowCaption;
    mfWindow.itemcount = (sizeof(mfWindowItems) / sizeof(wchar_t*));
    mfWindow.selFlags = YGSEL_HIGHLIGHT | YGSEL_VERTICAL;

    mfWindow.window.width = 300;
    mfWindow.window.height = (32 * mfWindow.itemcount) - (4 * mfWindow.itemcount);

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
    mfWindow.window.bCaptionFontShadow = 1;
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
    mfWindow2.window.Ypos = mfWindow.window.Ypos + mfWindow.window.height;

    mfWindow2.window.windowBGColor = YGWINDOW_BG_DARK;

    mfWindow2.window.windowFontSize = 12;
    mfWindow2.window.windowFontColor = 0xFFFFFFFF;

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

    wchar_t convBuffer[MFWINDOW2_MAXTEXT];
    sceCccUTF8toUTF16(convBuffer, MFWINDOW2_MAXTEXT - 1, mfWindow2Items[mfWindow.currentItem]);
    mfWindow2.window.windowText = convBuffer;

    uintptr_t packet = EhPckt_Open(4, 0);

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
        mfwindow_Create();
        mfwindow2_Create();
        return 0;
    }

    helpers_SetDialogBoxWantsIO(1);

    uintptr_t packet = EhPckt_Open(4, 0);

    uint32_t buttons = GetPadButtons(1);
    mfWindowSetting* setting = &(mfWindowSettings[mfWindow.currentItem]);
    int* val = setting->val;

    if (buttons & PSP_CTRL_LEFT)
    {
        *val -= 1;
        mfwindow_bValueChanged = 1;
    }

    if (buttons & PSP_CTRL_RIGHT)
    {
        *val += 1;
        mfwindow_bValueChanged = 1;
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
        if (mfwindow_bValueChanged)
            return -2;
        return -1;
    }

    return 0;
}

