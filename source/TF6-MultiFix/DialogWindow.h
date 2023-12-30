//
// Yu-Gi-Oh! Tag Force - Dialog window class
// by xan1242 / Tenjoin
//

#include "YgWindow.h"

#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

typedef enum _DialogWindowButtons
{
	DIALOGWINDOW_BUTTONS_UNK = -1,
	DIALOGWINDOW_BUTTONS_NONE,
	DIALOGWINDOW_BUTTONS_OK,
	DIALOGWINDOW_BUTTONS_OKCANCEL,
	DIALOGWINDOW_BUTTONS_YESNO,
	DIALOGWINDOW_BUTTONS_YESNOCANCEL,
	DIALOGWINDOW_BUTTONS_COUNT
}DialogWindowButtons;

// typedef enum _DialogWindowBGColor
// {
// 	DIALOGWINDOW_BGCOLOR_UNK = -1,
// 	DIALOGWINDOW_BGCOLOR_LIGHT,
// 	DIALOGWINDOW_BGCOLOR_BLUE,
// 	DIALOGWINDOW_BGCOLOR_DARK,
// 	DIALOGWINDOW_BGCOLOR_COUNT
// }DialogWindowBGColor;

typedef struct _DialogWindow
{
	YgSelWnd* selwnd;
	int bInited;
	int bNotifyDestroy;
	int bBlockGameControl;
	int zOrder;
	// add these in if necessary, removed for optimization & simplification
	//int bAutoSize;
	//int bFontShadow;
	//int minWidth;
	//int minHeight;
	//int maxWidth;
	//int maxHeight;
	//int padTop;
	//int padBot;
	//int padLeft;
	//int padRight;
	//DialogWindowBGColor bgColor;
	DialogWindowButtons buttons;
	wchar_t* text;
}DialogWindow;

int DialogWindow_IsActive(DialogWindow* window);
void DialogWindow_Destroy(DialogWindow* window);
void DialogWindow_Create(DialogWindow* window);
int DialogWindow_Draw(DialogWindow* window);


#endif