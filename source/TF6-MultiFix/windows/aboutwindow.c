//
// Yu-Gi-Oh! Tag Force - About window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
//#include "../multifixconfig.h"
//#include "../YgWindow.h"
#include "../DialogWindow.h"
#include "aboutwindow.h"
#include "../../../includes/psp/pspmallochelper.h"

DialogWindow* aboutWindow;
wchar_t* aboutWindowText;
//int bAboutWindowInited = 0;
//int aboutWindow_bNotifyDestroy = 0;

#define ABOUTWINDOW_MAXTEXT 512

int aboutwindow_IsActive()
{
	return aboutWindow != NULL;
}

void aboutwindow_Destroy()
{
	if (aboutWindow)
	{
		if (DialogWindow_IsActive(aboutWindow))
		{
			DialogWindow_Destroy(aboutWindow);
		}

		psp_free(aboutWindow);
		aboutWindow = NULL;
	}

	if (aboutWindowText)
	{
		psp_free(aboutWindowText);
		aboutWindowText = NULL;
	}
}

void aboutwindow_Create()
{
	if (aboutWindow)
		psp_free(aboutWindow);
	if (aboutWindowText)
		psp_free(aboutWindowText);
	aboutWindow = (DialogWindow*)psp_malloc(sizeof(DialogWindow));
	YgSys_memset(aboutWindow, 0, sizeof(DialogWindow));

	aboutWindow->buttons = DIALOGWINDOW_BUTTONS_OK;
	aboutWindow->bBlockGameControl = 1;
	aboutWindow->zOrder = MULTIFIX_WINDOW_ZORDER;

	char printbuf[ABOUTWINDOW_MAXTEXT];
	YgSys_sprintf(printbuf, MULTIFIX_ABOUT_FORMAT, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR, MULTIFIX_ABOUT_TEXT);

	aboutWindowText = (wchar_t*)psp_malloc((YgSys_strlen(printbuf) + 1) * sizeof(wchar_t));

	sceCccUTF8toUTF16(aboutWindowText, (ABOUTWINDOW_MAXTEXT - 1) * 2, printbuf);
	aboutWindow->text = aboutWindowText;

	DialogWindow_Create(aboutWindow);
}

int aboutwindow_Draw()
{
	if (!aboutWindow)
	{
		aboutwindow_Create();
		return 0;
	}

	if (DialogWindow_Draw(aboutWindow))
	{
		aboutwindow_Destroy();
		return -1;
	}

	return 0;
}
