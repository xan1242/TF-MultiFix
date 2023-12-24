//
// Yu-Gi-Oh! Tag Force - Konami Code window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../YgWindow.h"
#include "konamidialog.h"
#include "../../../includes/psp/pspmallochelper.h"

YgSelWnd* konamiDialog;
int bKonamiDialogInited = 0;
int konamiDialog_bNotifyDestroy = 0;

wchar_t KonamiDialogText[] = KONAMIDIALOG_TEXT;

int konamidialog_IsActive()
{
	return (bKonamiDialogInited != 0) || (konamiDialog != NULL);
}

void konamidialog_Destroy()
{
	konamiDialog_bNotifyDestroy = 1;
	bKonamiDialogInited = 0;
	YgSelWnd_Term(konamiDialog);
	psp_free(konamiDialog);
	konamiDialog = NULL;
}

void konamidialog_Create()
{
	if (konamiDialog)
		psp_free(konamiDialog);
	konamiDialog = (YgSelWnd*)psp_malloc(sizeof(YgSelWnd));
	YgSys_memset(konamiDialog, 0, sizeof(YgSelWnd));
	konamiDialog->heapptr = helpers_GetMainEhHeap();

	konamiDialog->selFlags = YGSEL_DIALOGBUTTONS_OK;

	konamiDialog->window.color = 0xFFFFFFFF;
	konamiDialog->window.unk3 = 1;

	konamiDialog->window.width = 0;
	konamiDialog->window.height = 0;
	konamiDialog->window.maxWidth = 400;
	konamiDialog->window.minWidth = 100;

	konamiDialog->window.bAutoSizeWindow = 1;

	konamiDialog->window.topPadding = 8;
	konamiDialog->window.bottomPadding = 0;
	konamiDialog->window.leftPadding = 10;
	konamiDialog->window.rightPadding = 10;

	konamiDialog->window.windowBGColor = YGWINDOW_BG_DARK;

	//aboutWindow.window.windowText = installDisableText;
	konamiDialog->window.windowFontSize = 12;
	konamiDialog->window.windowFontColor = 0xFFFFFFFF;
	konamiDialog->window.unk43 = 1;
	konamiDialog->window.unk44 = 1;
	konamiDialog->window.bFontShadow = 1;

	konamiDialog->window.windowText = KonamiDialogText;

	YgSelWnd_Init(konamiDialog);

	konamiDialog->window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)konamiDialog->window.width * 0.5f));
	konamiDialog->window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)konamiDialog->window.height * 0.5f));
	bKonamiDialogInited = 1;
}

int konamidialog_Draw()
{
	if (!bKonamiDialogInited)
	{
		konamiDialog_bNotifyDestroy = 0;
		konamidialog_Create();
		return 0;
	}

	if (konamiDialog_bNotifyDestroy)
		return 0;

	helpers_SetDialogBoxWantsIO(1);

	uintptr_t packet = EhPckt_Open(10, 0);
	YgSelWnd_Cont(konamiDialog);
	YgSelWnd_Draw((uintptr_t)&packet, konamiDialog);

	EhPckt_Close(packet);

	if (konamiDialog->decideStatus)
	{
		konamidialog_Destroy();
		return -1;
	}

	return 0;
}
