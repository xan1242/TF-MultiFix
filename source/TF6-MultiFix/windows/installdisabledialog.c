//
// Yu-Gi-Oh! Tag Force - Install disabled dialog window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifixconfig.h"
#include "../YgWindow.h"
#include "installdisabledialog.h"
#include "../../../includes/psp/pspmallochelper.h"

YgSelWnd* installDisableWindow;
int bInstallDisableWindowInited = 0;
int installDisableWindow_bNotifyDestroy = 0;

wchar_t installDisableText[] = L"The installation feature has been disabled.\n\nYou can re-enable it in the\nMultiFix Configuration window.";

int installdisabledialog_IsActive()
{
	return (bInstallDisableWindowInited != 0) || (installDisableWindow != NULL);
}

void installdisabledialog_Destroy()
{
	installDisableWindow_bNotifyDestroy = 1;
	bInstallDisableWindowInited = 0;
	YgSelWnd_Term(installDisableWindow);
	psp_free(installDisableWindow);
	installDisableWindow = NULL;
}

void installdisabledialog_Create()
{
	if (installDisableWindow)
		psp_free(installDisableWindow);

	installDisableWindow = (YgSelWnd*)psp_malloc(sizeof(YgSelWnd));
	YgSys_memset(installDisableWindow, 0, sizeof(YgSelWnd));
	installDisableWindow->heapptr = helpers_GetMainEhHeap();

	installDisableWindow->selFlags = YGSEL_DIALOGBUTTONS_OK;

	installDisableWindow->window.color = 0xFFFFFFFF;
	installDisableWindow->window.unk3 = 1;

	//installDisableWindow->window.width = 300;
	//installDisableWindow->window.height = 108;
	installDisableWindow->window.maxWidth = 400;
	installDisableWindow->window.minWidth = 100;

	installDisableWindow->window.bAutoSizeWindow = 1;

	installDisableWindow->window.topPadding = 8;
	//installDisableWindow->window.bottomPadding = 0;
	installDisableWindow->window.leftPadding = 10;
	installDisableWindow->window.rightPadding = 10;

	installDisableWindow->window.windowBGColor = YGWINDOW_BG_DARK;

	installDisableWindow->window.windowText = installDisableText;
	installDisableWindow->window.windowFontSize = 12;
	installDisableWindow->window.windowFontColor = 0xFFFFFFFF;
	installDisableWindow->window.unk43 = 1;
	installDisableWindow->window.unk44 = 1;
	installDisableWindow->window.bFontShadow = 1;

	YgSelWnd_Init(installDisableWindow);

	installDisableWindow->window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)installDisableWindow->window.width * 0.5f));
	installDisableWindow->window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)installDisableWindow->window.height * 0.5f));
	bInstallDisableWindowInited = 1;
}

int installdisabledialog_Draw()
{
	if (!bInstallDisableWindowInited)
	{
		installDisableWindow_bNotifyDestroy = 0;
		installdisabledialog_Create();
		return 0;
	}

	if (installDisableWindow_bNotifyDestroy)
		return 0;

	uintptr_t packet = EhPckt_Open(4, 0);
	YgSelWnd_Cont(installDisableWindow);
	YgSelWnd_Draw((uintptr_t)&packet, installDisableWindow);

	EhPckt_Close(packet);

	if (installDisableWindow->decideStatus)
	{
		installdisabledialog_Destroy();
		return -1;
	}

	return 0;
}
