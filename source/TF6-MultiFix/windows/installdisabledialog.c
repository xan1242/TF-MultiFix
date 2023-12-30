//
// Yu-Gi-Oh! Tag Force - Install disabled dialog window
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "../helpers.h"
#include "../DialogWindow.h"
#include "installdisabledialog.h"
#include "../../../includes/psp/pspmallochelper.h"

DialogWindow* installDisableWindow;

int installdisabledialog_IsActive()
{
	return installDisableWindow != NULL;
}

void installdisabledialog_Destroy()
{
	if (installDisableWindow)
	{
		if (DialogWindow_IsActive(installDisableWindow))
		{
			DialogWindow_Destroy(installDisableWindow);
		}

		psp_free(installDisableWindow);
		installDisableWindow = NULL;
	}
}

void installdisabledialog_Create()
{
	if (installDisableWindow)
		psp_free(installDisableWindow);

	installDisableWindow = (DialogWindow*)psp_malloc(sizeof(DialogWindow));
	YgSys_memset(installDisableWindow, 0, sizeof(DialogWindow));

	installDisableWindow->buttons = DIALOGWINDOW_BUTTONS_OK;
	installDisableWindow->zOrder = 4;

	installDisableWindow->text = INSTALLDISABLEDIALOG_TEXT;

	DialogWindow_Create(installDisableWindow);
}

int installdisabledialog_Draw()
{
	if (!installDisableWindow)
	{
		installdisabledialog_Create();
		return 0;
	}

	if (DialogWindow_Draw(installDisableWindow))
	{
		installdisabledialog_Destroy();
		return -1;
	}

	return 0;
}
