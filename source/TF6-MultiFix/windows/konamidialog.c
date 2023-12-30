//
// Yu-Gi-Oh! Tag Force - Konami Code window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../multifix.h"
#include "../multifixconfig.h"
#include "../DialogWindow.h"
#include "konamidialog.h"
#include "../../../includes/psp/pspmallochelper.h"

DialogWindow* konamiDialog;

int konamidialog_IsActive()
{
	return konamiDialog != NULL;
}

void konamidialog_Destroy()
{
	if (konamiDialog)
	{
		if (DialogWindow_IsActive(konamiDialog))
		{
			DialogWindow_Destroy(konamiDialog);
		}

		psp_free(konamiDialog);
		konamiDialog = NULL;
	}
}

void konamidialog_Create()
{
	if (konamiDialog)
		psp_free(konamiDialog);

	konamiDialog = (DialogWindow*)psp_malloc(sizeof(DialogWindow));
	YgSys_memset(konamiDialog, 0, sizeof(DialogWindow));

	konamiDialog->buttons = DIALOGWINDOW_BUTTONS_OK;
	konamiDialog->bBlockGameControl = 1;
	konamiDialog->zOrder = MULTIFIX_WINDOW_ZORDER;

	konamiDialog->text = KONAMIDIALOG_TEXT;

	DialogWindow_Create(konamiDialog);
}

int konamidialog_Draw()
{
	if (!konamiDialog)
	{
		konamidialog_Create();
		return 0;
	}

	if (DialogWindow_Draw(konamiDialog))
	{
		konamidialog_Destroy();
		return -1;
	}

	return 0;
}
