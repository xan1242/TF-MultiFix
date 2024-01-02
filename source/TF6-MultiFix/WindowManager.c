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
#include "windows/cheatmenu_trust.h"

unsigned int WM_WindowDisplayMask = 0;

unsigned int WM_GetDispMask()
{
    return WM_WindowDisplayMask;
}

void WM_SetDispMask(unsigned int mask)
{
    WM_WindowDisplayMask = mask;
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
    if (cheatmenu_trust_IsActive())
        cheatmenu_trust_Destroy();
}

int WM_bIsAnyWindowShown()
{
    return WM_WindowDisplayMask != 0;
}

void WM_ShowWindow(unsigned int windowMask)
{
    WM_WindowDisplayMask |= windowMask;
}

void WM_SwitchToWindow(unsigned int windowMask)
{
    if (WM_bIsAnyWindowShown())
        WM_DestroyAllWindows();
    else 
        WM_WindowDisplayMask = 0;

    WM_ShowWindow(windowMask);
}

void WM_Draw()
{
    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_ABOUT)
    {
        if (aboutwindow_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_ABOUT;
        }
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_KONAMI)
    {
        if (konamidialog_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_KONAMI;
        }
    }

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_MFWINDOW)
    {
        if (mfwindow_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_MFWINDOW;
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

    if (WM_WindowDisplayMask & WINDOWMANAGER_DISP_TRUSTMENU)
    {
        if (cheatmenu_trust_Draw())
        {
            WM_WindowDisplayMask &= ~WINDOWMANAGER_DISP_TRUSTMENU;
        }
    }
}
