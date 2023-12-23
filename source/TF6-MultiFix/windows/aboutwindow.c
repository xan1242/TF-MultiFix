//
// Yu-Gi-Oh! Tag Force - About window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../YgWindow.h"
#include "aboutwindow.h"

YgSelWnd aboutWindow;
int bAboutWindowInited = 0;

//wchar_t installDisableText[] = L"The installation feature has been disabled.\n\nYou can re-enable it in the MultiFix Configuration window.";
char aboutWindow_VersionFormat[] = MULTIFIX_ABOUT_FORMAT;

#define ABOUTWINDOW_MAXTEXT 512

void aboutwindow_Create()
{
	YgSys_memset(&aboutWindow, 0, sizeof(YgSelWnd));
	aboutWindow.heapptr = helpers_GetMainEhHeap();

	aboutWindow.selFlags = YGSEL_DIALOGBUTTONS_OK;

	aboutWindow.window.color = 0xFFFFFFFF;
	aboutWindow.window.unk3 = 1;

	aboutWindow.window.width = 0;
	aboutWindow.window.height = 0;
	aboutWindow.window.maxWidth = 400;
	aboutWindow.window.minWidth = 100;

	aboutWindow.window.bAutoSizeWindow = 1;

	aboutWindow.window.topPadding = 8;
	aboutWindow.window.bottomPadding = 0;
	aboutWindow.window.leftPadding = 10;
	aboutWindow.window.rightPadding = 10;

	aboutWindow.window.windowBGColor = YGWINDOW_BG_DARK;

	//aboutWindow.window.windowText = installDisableText;
	aboutWindow.window.windowFontSize = 12;
	aboutWindow.window.windowFontColor = 0xFFFFFFFF;
	aboutWindow.window.unk43 = 1;
	aboutWindow.window.unk44 = 1;
	aboutWindow.window.bFontShadow = 1;

	char printbuf[ABOUTWINDOW_MAXTEXT];
	YgSys_sprintf(printbuf, aboutWindow_VersionFormat, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR, MULTIFIX_ABOUT_TEXT);
	wchar_t windowtext[ABOUTWINDOW_MAXTEXT];
	sceCccUTF8toUTF16(windowtext, (ABOUTWINDOW_MAXTEXT - 1) * 2, printbuf);
	aboutWindow.window.windowText = windowtext;

	YgSelWnd_Init(&aboutWindow);

	aboutWindow.window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)aboutWindow.window.width * 0.5f));
	aboutWindow.window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)aboutWindow.window.height * 0.5f));
	bAboutWindowInited = 1;
}

int aboutwindow_Draw()
{
	if (!bAboutWindowInited)
	{
		aboutwindow_Create();
		return 0;
	}

	helpers_SetDialogBoxWantsIO(1);

	char printbuf[ABOUTWINDOW_MAXTEXT];
	YgSys_sprintf(printbuf, aboutWindow_VersionFormat, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR, MULTIFIX_ABOUT_TEXT);
	wchar_t windowtext[ABOUTWINDOW_MAXTEXT];
	sceCccUTF8toUTF16(windowtext, (ABOUTWINDOW_MAXTEXT - 1) * 2, printbuf);
	aboutWindow.window.windowText = windowtext;

	uintptr_t packet = EhPckt_Open(10, 0);
	YgSelWnd_Cont(&aboutWindow);
	YgSelWnd_Draw((uintptr_t)&packet, &aboutWindow);

	EhPckt_Close(packet);

	if (aboutWindow.decideStatus)
	{
		bAboutWindowInited = 0;
		YgSelWnd_Term(&aboutWindow);
		return -1;
	}

	return 0;
}
