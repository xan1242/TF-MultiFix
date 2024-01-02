//
// Yu-Gi-Oh! Tag Force - Window manager class
// by xan1242 / Tenjoin
//

#include "WindowManager.h"
#include "helpers.h"
#include "MenuWindow.h"
#include "windows/multifixwindow.h"
#include "windows/aboutwindow.h"
#include "windows/konamidialog.h"
#include "windows/cheatmenu_global.h"
#include "windows/cheatmenu_duel.h"

unsigned int WM_WindowDisplayMask = 0;

int WM_bCheatMenuEnabled = 0;

unsigned int WM_GetDispMask()
{
    return WM_WindowDisplayMask;
}

void WM_SetDispMask(unsigned int mask)
{
    WM_WindowDisplayMask = mask;
}

void WM_SetCheatMenuEnable(int val)
{
    WM_bCheatMenuEnabled = val;
}

void WM_DestroyAllWindows()
{
    WM_WindowDisplayMask = 0;

    if (aboutwindow_IsActive())
        aboutwindow_Destroy();
    if (konamidialog_IsActive())
        konamidialog_Destroy();
    if (mfwindow_IsActive())
        mfwindow_Destroy();
    if (cheatmenu_global_IsActive())
        cheatmenu_global_Destroy();
    if (cheatmenu_duel_IsActive())
        cheatmenu_duel_Destroy();
}

int WM_bIsAnyWindowShown()
{
    return WM_WindowDisplayMask != 0;
}

void WM_Draw()
{
    //helpers_SetDialogBoxWantsIO(0);

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_ABOUT)
    {
        if (aboutwindow_Draw())
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_ABOUT;
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_KONAMI)
    {
        if (konamidialog_Draw())
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_KONAMI;
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_MFWINDOW)
    {
        int retval = mfwindow_Draw();
        if (retval)
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_MFWINDOW;

            int itemIdx = MENUWINDOW_RESULT_ITEM(retval);

            if (MENUWINDOW_RESULT_DECIDESTATUS(retval) == YGSEL_DECIDESTATUS_CONFIRM)
            {
                switch (itemIdx)
                {
                case MFWINDOW_ITEM_ABOUT:
                {
                    WM_WindowDisplayMask |= WINDOWMANAGER_DISP_ABOUT;
                    break;
                }
                case MFWINDOW_ITEM_CHEATSGLOBAL:
                {
                    if (WM_bCheatMenuEnabled)
                    {
                        WM_WindowDisplayMask |= WINDOWMANAGER_DISP_CHEATGLOBAL;
                    }
                    break;
                }
                case MFWINDOW_ITEM_CHEATSLOCAL:
                {
                    if (WM_bCheatMenuEnabled && ((GetGameState() == EHSTATE_DUEL)))
                    {
                        WM_WindowDisplayMask |= WINDOWMANAGER_DISP_CHEATDUEL;
                    }
                    break;
                }
                default:
                    break;
                }
            }

        }
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_CHEATGLOBAL)
    {
        if (cheatmenu_global_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_CHEATGLOBAL;
        }
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_CHEATDUEL)
    {
        if (cheatmenu_duel_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_CHEATDUEL;
        }
    }
}
