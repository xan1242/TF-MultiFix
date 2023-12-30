//
// Yu-Gi-Oh! Tag Force - Dialog window class
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "helpers.h"
#include "YgWindow.h"
#include "DialogWindow.h"
#include "../../includes/psp/pspmallochelper.h"

int DialogWindow_IsActive(DialogWindow* window)
{
	return (window->bInited != 0) || (window->selwnd != NULL);
}

void DialogWindow_Destroy(DialogWindow* window)
{
	window->bNotifyDestroy = 1;
	window->bInited = 0;
	if (window->selwnd)
	{
		YgSelWnd_Term(window->selwnd);
		psp_free(window->selwnd);
		window->selwnd = NULL;
	}
	//if (window->text)
	//{
	//	psp_free(window->text);
	//	window->text = NULL;
	//}
}

void DialogWindow_Create(DialogWindow* window)
{
	if (window->selwnd)
		psp_free(window->selwnd);
	//if (window->text)
	//	psp_free(window->text);

	window->selwnd = (YgSelWnd*)psp_malloc(sizeof(YgSelWnd));
	YgSys_memset(window->selwnd, 0, sizeof(YgSelWnd));
	window->selwnd->heapptr = helpers_GetMainEhHeap();

	switch (window->buttons)
	{
	case DIALOGWINDOW_BUTTONS_YESNOCANCEL:
		window->selwnd->selFlags = YGSEL_DIALOGBUTTONS_YESNOCANCEL;
		break;
	case DIALOGWINDOW_BUTTONS_YESNO:
		window->selwnd->selFlags = YGSEL_DIALOGBUTTONS_YESNO;
		break;
	case DIALOGWINDOW_BUTTONS_OKCANCEL:
		window->selwnd->selFlags = YGSEL_DIALOGBUTTONS_OKCANCEL;
		break;
	case DIALOGWINDOW_BUTTONS_OK:
		window->selwnd->selFlags = YGSEL_DIALOGBUTTONS_OK;
		break;
	default:
		break;
	}

	window->selwnd->window.color = 0xFFFFFFFF;
	window->selwnd->window.unk3 = 1;

	window->selwnd->window.maxWidth = 400;
	window->selwnd->window.minWidth = 100;

	window->selwnd->window.bAutoSizeWindow = 1;

	window->selwnd->window.topPadding = 8;
	window->selwnd->window.leftPadding = 10;
	window->selwnd->window.rightPadding = 10;

	window->selwnd->window.windowBGColor = YGWINDOW_BG_DARK;

	window->selwnd->window.windowFontSize = 12;
	window->selwnd->window.windowFontColor = 0xFFFFFFFF;
	window->selwnd->window.unk43 = 1;
	window->selwnd->window.unk44 = 1;
	window->selwnd->window.bFontShadow = 1;

	window->selwnd->window.windowText = window->text;

	YgSelWnd_Init(window->selwnd);

	window->selwnd->window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)window->selwnd->window.width * 0.5f));
	window->selwnd->window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)window->selwnd->window.height * 0.5f));
	window->bInited = 1;
}

int DialogWindow_Draw(DialogWindow* window)
{
	if ((!window->bInited) || (!window->selwnd) || (window->bNotifyDestroy))
		return 0;

	helpers_SetDialogBoxWantsIO(1);

	uintptr_t packet = EhPckt_Open(window->zOrder, 0);
	YgSelWnd_Cont(window->selwnd);
	YgSelWnd_Draw((uintptr_t)&packet, window->selwnd);
	EhPckt_Close(packet);

	if (window->selwnd->decideStatus)
	{
		return 1;
	}

	return 0;
}
