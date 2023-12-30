//
// Yu-Gi-Oh! Tag Force - MultiFix configuration window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifixconfig.h"
//#include "../YgWindow.h"
#include "../MenuWindow.h"
#include "multifixwindow.h"
#include <pspctrl.h>
//#include <pspuser.h>
#include "../../../includes/psp/pspmallochelper.h"

MenuWindow* mfWindow;
int mfwindow_bCheatsEnabled = 0;

MenuWindowItem mfWindowSettings[MFWINDOW_ITEM_COUNT] =
{
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, MFWINDOW_ITEM_SWAPBUTTON, MFWINDOW_ITEM_NAME_SWAPBUTTON, MFWINDOW_ITEM_DESC_SWAPBUTTON},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, MFWINDOW_ITEM_MATRIXFONT, MFWINDOW_ITEM_NAME_MATRIXFONT, MFWINDOW_ITEM_DESC_MATRIXFONT},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, MFWINDOW_ITEM_PARTNERCARD, MFWINDOW_ITEM_NAME_PARTNERCARD, MFWINDOW_ITEM_DESC_PARTNERCARD},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, MFWINDOW_ITEM_DUELHELP, MFWINDOW_ITEM_NAME_DUELHELP, MFWINDOW_ITEM_DESC_DUELHELP},
    {NULL, NULL, 0, 1, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_BOOL, 0, 0, 0, 1, MFWINDOW_ITEM_INSTALLDISABLE, MFWINDOW_ITEM_NAME_INSTALLDISABLE, MFWINDOW_ITEM_DESC_INSTALLDISABLE},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, MFWINDOW_ITEM_SOUNDTEST, MFWINDOW_ITEM_NAME_SOUNDTEST, MFWINDOW_ITEM_DESC_SOUNDTEST},
    // cheats are always here
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 1, 1, 0, 0, MFWINDOW_ITEM_CHEATSGLOBAL, MFWINDOW_ITEM_NAME_CHEATSGLOBAL, MFWINDOW_ITEM_DESC_CHEATSGLOBAL},
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 1, 1, 0, 0, MFWINDOW_ITEM_CHEATSLOCAL, MFWINDOW_ITEM_NAME_CHEATSLOCAL, MFWINDOW_ITEM_DESC_CHEATSLOCAL},
    // about is always last!
    {NULL, NULL, 0, 0, 0.0f, 0.0f, MENUWINDOW_ITEM_TYPE_NONE, 0, 1, 0, 0, MFWINDOW_ITEM_ABOUT, MFWINDOW_ITEM_NAME_ABOUT, MFWINDOW_ITEM_DESC_ABOUT},
};

//mfWindowSetting* mfWindowSettingDrawList[MFWINDOW_ITEM_COUNT];

int mfwindow_IsActive()
{
    return mfWindow != NULL;
}

void mfwindow_Destroy()
{
    if (mfWindow)
    {
        if (MenuWindow_IsActive(mfWindow))
        {
            MenuWindow_Destroy(mfWindow);
        }

        psp_free(mfWindow);
        mfWindow = NULL;
    }
}

uintptr_t mfWindowCallback(uintptr_t ehpacket, int item_index, int X, int Y)
{
    return MenuWindow_Callback(ehpacket, item_index, X, Y, mfWindow);
}

void mfwindow_Create()
{
    if (mfWindow)
        psp_free(mfWindow);
    mfWindow = (MenuWindow*)psp_malloc(sizeof(MenuWindow));
    YgSys_memset(mfWindow, 0, sizeof(MenuWindow));

    // assign some defaults
    mfWindow->caption = MFWINDOW_CAPTION;
    mfWindow->bBlockGameControl = 1;
    mfWindow->zOrder = MULTIFIX_WINDOW_ZORDER;
    mfWindow->itemDrawCallback = (uintptr_t)&mfWindowCallback;
    mfWindow->itemCount = MFWINDOW_ITEM_COUNT;
    mfWindow->items = mfWindowSettings;

    MultiFixConfig* config = mfconfig_GetConfig();
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

        if ((state == EHSTATE_DUEL) ||
            (state == EHSTATE_SHOP))
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

    MenuWindow_Create(mfWindow);
}

int mfwindow_GetItemCount()
{
    return MFWINDOW_ITEM_COUNT;
}

void mfwindow_SetCheatsEnabled(int val)
{
    mfwindow_bCheatsEnabled = val;
}

int mfwindow_Draw()
{
    if (!mfWindow)
    {
        YgSys_SndPlaySE(SOUND_ID_MENU_WINDOWPOPUP_1);
        mfwindow_Create();
        return 0;
    }

    int menuRes = MenuWindow_Draw(mfWindow);
    if (menuRes)
    {
        mfwindow_Destroy();
        return menuRes;
    }

    return 0;
}

