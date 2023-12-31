//
// Yu-Gi-Oh! Tag Force - Menu window class
// by xan1242 / Tenjoin
//

#include "YgWindow.h"

#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#define MENUWINDOW_MAXVISIBLEITEMS 7
#define MENUWINDOW_ITEM_SELCURSOR_HEIGHT 16
#define MENUWINDOW_ITEM_FONTSIZE 12
#define MENUWINDOW_ITEM_MAXTEXT 64
#define MENUWINDOW_DESC_FONTSIZE 12
#define MENUWINDOW_DESC_MAXTEXT 256
#define MENUWINDOW_LABEL_BOOL_TRUE "<On>"
#define MENUWINDOW_LABEL_BOOL_FALSE "<Off>"
#define MENUWINDOW_SELWIDTH_DIFF 12

#define MENUWINDOW_RESULT_DECIDESTATUS(x) ((x) & 0xFF)
#define MENUWINDOW_RESULT_ITEM(x) ((x >> 8) & 0xFF)
#define MENUWINDOW_RESULT_VALCHANGE(x) ((x >> 16) & 0xFF)

typedef struct _MenuWindowItem
{
    int* val;
    float* fval;
    int min;
    int max;
    float fmin;
    float fmax;
    int type;
    int hidden;
    int selectable;
    int greyedout;
    int loopable;
    int index;
    char* name;
    char* description;
}MenuWindowItem;

typedef enum _MenuWindowItemType
{
    MENUWINDOW_ITEM_TYPE_UNK = -1,
    MENUWINDOW_ITEM_TYPE_NONE,
    MENUWINDOW_ITEM_TYPE_INT,
    MENUWINDOW_ITEM_TYPE_BOOL,
    MENUWINDOW_ITEM_TYPE_FLOAT,
    MENUWINDOW_ITEM_TYPE_INTSTRING,
    MENUWINDOW_ITEM_TYPE_COUNT
}MenuWindowItemType;

typedef struct _MenuWindow
{
	YgSelWnd* selwnd;
	ygBasicWindowPack* descwnd;
	int bInited;
	int bInitedDesc;
	int bNotifyDestroy;
	int bBlockGameControl;
    int bValueChanged;
	int zOrder;
    int itemCount;
    MenuWindowItem* items;
    MenuWindowItem** itemDrawList;
    uintptr_t itemDrawCallback;
	wchar_t* caption;
    wchar_t* descwindowtext;
}MenuWindow;

uintptr_t MenuWindow_Callback(uintptr_t ehpacket, int item_index, int X, int Y, MenuWindow* window);
int MenuWindow_IsActive(MenuWindow* window);
void MenuWindow_Destroy(MenuWindow* window);
void MenuWindow_Create(MenuWindow* window);
int MenuWindow_Draw(MenuWindow* window);

#endif