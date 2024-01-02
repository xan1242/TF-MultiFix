//
// Yu-Gi-Oh! Tag Force - Menu window class
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include <stdio.h>
#include "helpers.h"
#include "YgWindow.h"
#include "MenuWindow.h"
#include <pspctrl.h>
#include <pspuser.h>
#include "../../includes/psp/pspmallochelper.h"

int MenuWindow_IsActive(MenuWindow* window)
{
	return (window->bInited != 0) || (window->selwnd != NULL) || (window->descwnd != NULL) || (window->itemDrawList != NULL) || (window->descwindowtext != NULL);
}

void MenuWindow_Destroy(MenuWindow* window)
{
	window->bNotifyDestroy = 1;
	window->bInited = 0;

	if (window->selwnd)
	{
		YgSelWnd_Term(window->selwnd);
		psp_free(window->selwnd);
		window->selwnd = NULL;
	}

	if (window->descwnd)
	{
		ygBasicWindow_Term(&window->descwnd->res);
		psp_free(window->descwnd);
		window->descwnd = NULL;
	}

	if (window->itemDrawList)
	{
		psp_free(window->itemDrawList);
		window->itemDrawList = NULL;
	}

	if (window->descwindowtext)
	{
		psp_free(window->descwindowtext);
		window->descwindowtext = NULL;
	}
}

uintptr_t MenuWindow_Callback(uintptr_t ehpacket, int item_index, int X, int Y, MenuWindow* window)
{
	if (!window)
		return ehpacket;

	MenuWindowItem* currItem = window->itemDrawList[item_index];
	int Y_corrected = Y + 2;

	int oldshadow = YgFont_GetShadowFlg();

	int currVal = 0;
	if (currItem->cbValRead)
	{
		int (*ReadCallback)(uintptr_t data) = (int (*)(uintptr_t))(currItem->cbValRead);
		currVal = ReadCallback(currItem->cbData);
	}
	else if (currItem->val)
	{
		currVal = *currItem->val;
	}

	YgFont_SetEhPckt(ehpacket);

	YgFont_SetSize(MENUWINDOW_ITEM_FONTSIZE, MENUWINDOW_ITEM_FONTSIZE);
	YgFont_SetRubyCharFlg(0);
	YgFont_SetShadowFlg(1);
	YgFont_SetChColorFlg(1);

	if (currItem->greyedout)
	{
		YgFont_SetShadowFlg(0);
		YgFont_SetDefaultColor(0xFF7F7F7F);
	}
	else
	{
		YgFont_SetShadowFlg(1);
		YgFont_SetDefaultColor(0xFF000000);
	}

	size_t txtlen = 0;
	wchar_t convBuffer[MENUWINDOW_ITEM_MAXTEXT];

	if (currItem->bWideCharName)
	{
		YgFont_PrintLine64(X << 6, Y_corrected << 6, (480 - X) << 6, (wchar_t*)currItem->name);
	}
	else
	{
		txtlen = YgSys_strlen(currItem->name) + 1;
		sceCccUTF8toUTF16(convBuffer, txtlen * sizeof(wchar_t), currItem->name);
		YgFont_PrintLine64(X << 6, Y_corrected << 6, (480 - X) << 6, convBuffer);
	}

	switch (currItem->type)
	{
		case MENUWINDOW_ITEM_TYPE_INTSTRING:
		{
			char sprintfbuf[32];
			YgSys_sprintf(sprintfbuf, "<%s>", currItem->options[currVal]);
			txtlen = YgSys_strlen((char*)currItem->options[currVal]) + 1 + 2;
			sceCccUTF8toUTF16(convBuffer, txtlen * sizeof(wchar_t), sprintfbuf);
			break;
		}
		case MENUWINDOW_ITEM_TYPE_BOOL:
		{
			if (currVal)
			{
				sceCccUTF8toUTF16(convBuffer, (sizeof(MENUWINDOW_LABEL_BOOL_TRUE)) * sizeof(wchar_t), MENUWINDOW_LABEL_BOOL_TRUE);
			}
			else
			{
				YgFont_SetShadowFlg(0);
				YgFont_SetDefaultColor(0xFF7F7F7F);
				sceCccUTF8toUTF16(convBuffer, (sizeof(MENUWINDOW_LABEL_BOOL_FALSE)) * sizeof(wchar_t), MENUWINDOW_LABEL_BOOL_FALSE);
			}
			break;
		}
		//case MENUWINDOW_ITEM_TYPE_FLOAT:
		//{
		//	char sprintfbuf[32];
		//	YgSys_sprintf(sprintfbuf, "<%.2f>", *(float*)(&currVal));
		//	sprintfbuf[sizeof(sprintfbuf) - 1] = 0;
		//	sceCccUTF8toUTF16(convBuffer, (sizeof(sprintfbuf)) * sizeof(wchar_t), sprintfbuf);
		//	break;
		//}
		case MENUWINDOW_ITEM_TYPE_INT:
		{
			char sprintfbuf[32];
			YgSys_sprintf(sprintfbuf, "<%d>", currVal);
			sprintfbuf[sizeof(sprintfbuf) - 1] = 0;
			sceCccUTF8toUTF16(convBuffer, (sizeof(sprintfbuf)) * sizeof(wchar_t), sprintfbuf);
			break;
		}
		case MENUWINDOW_ITEM_TYPE_NONE:
		default:
		{
			break;
		}
	}

	if (currItem->type != MENUWINDOW_ITEM_TYPE_NONE)
	{
		if (currItem->greyedout)
		{
			YgFont_SetShadowFlg(0);
			YgFont_SetDefaultColor(0xFF7F7F7F);
		}

		// manually right justify
		int valXpos = window->selwnd->window.width + window->selwnd->window.Xpos - (YgFont_GetStrWidth(convBuffer) >> 6) - MENUWINDOW_SELWIDTH_DIFF;
		YgFont_PrintLine64(valXpos << 6, Y_corrected << 6, (480 - X) << 6, convBuffer);
	}

	YgFont_SetShadowFlg(oldshadow);

	return YgFont_GetEhPckt();
}

void MenuWindow_CreateItemWindow(MenuWindow* window)
{
	if (window->selwnd)
		psp_free(window->selwnd);
	if (window->itemDrawList)
		psp_free(window->itemDrawList);

	window->selwnd = (YgSelWnd*)psp_malloc(sizeof(YgSelWnd));
	window->itemDrawList = (MenuWindowItem**)psp_malloc(sizeof(MenuWindowItem*) * window->itemCount);
	YgSys_memset(window->selwnd, 0, sizeof(YgSelWnd));
	YgSys_memset(window->itemDrawList, 0, sizeof(MenuWindowItem*) * window->itemCount);

	window->selwnd->heapptr = helpers_GetMainEhHeap();
	window->selwnd->window.caption = window->caption;
	window->selwnd->itemcount = 0;
	window->selwnd->maxitems = MENUWINDOW_MAXVISIBLEITEMS;
	window->selwnd->selFlags = YGSEL_HIGHLIGHT | YGSEL_VERTICAL;
	window->selwnd->window.color = 0xFFFFFFFF;
	window->selwnd->itemDrawCallback = window->itemDrawCallback;
	window->selwnd->window.unk3 = 1;
	window->selwnd->window.windowBGColor = YGWINDOW_BG_LIGHT;
	window->selwnd->window.captionBGColor = YGWINDOW_BG_DARK;
	window->selwnd->window.bWindowCaption = 1;
	window->selwnd->window.bAutoSizeCaption = 1; // this is broken until the font is initialized
	window->selwnd->window.captionWidth = (int)((float)window->selwnd->window.width * 0.65f);
	window->selwnd->window.captionHeight = 16;
	window->selwnd->window.bFontShadow = 1;
	window->selwnd->window.captionFontSize = 12;
	window->selwnd->window.captionFontColor = 0xFFFFFFFF;

	// lock all by default
	window->selwnd->itemLockBitfield = 0xFFFFFFFF;

	for (int i = 0; i < window->itemCount; i++)
	{
		if (!window->items[i].hidden)
		{
			int j = window->selwnd->itemcount;
			window->itemDrawList[j] = &(window->items[i]);
			
			if (window->itemDrawList[j]->selectable)
			{
				window->selwnd->itemLockBitfield &= ~(YGSEL_LOCKITEM(j));
			}
			window->selwnd->itemcount++;
		}
	}

	window->selwnd->window.width = 300;

	int size_maxcount = window->selwnd->itemcount;
	if (window->selwnd->itemcount < window->selwnd->maxitems)
		size_maxcount = window->selwnd->maxitems;

	window->selwnd->window.bAutoSizeWindow = 1;
	window->selwnd->window.maxWidth = 400;
	window->selwnd->window.minWidth = 300;
	window->selwnd->window.maxHeight = 138;
	
	int SelDrawWidth = window->selwnd->window.width;
	window->selwnd->selDrawWidth1 = SelDrawWidth - MENUWINDOW_SELWIDTH_DIFF;
	window->selwnd->selDrawHeight1 = MENUWINDOW_ITEM_SELCURSOR_HEIGHT;
	window->selwnd->selDrawWidth2 = SelDrawWidth - MENUWINDOW_SELWIDTH_DIFF;
	window->selwnd->selDrawHeight1 = MENUWINDOW_ITEM_SELCURSOR_HEIGHT;

	YgSelWnd_Init(window->selwnd);

	window->selwnd->window.Xpos = (int)(PSP_SCREEN_HALF_WIDTH_FLOAT - ((float)window->selwnd->window.width * 0.5f));
	window->selwnd->window.Ypos = (int)(PSP_SCREEN_HALF_HEIGHT_FLOAT - ((float)window->selwnd->window.height * 0.5f));
}

void MenuWindow_CreateDescWindow(MenuWindow* window)
{
	if (window->descwnd)
		psp_free(window->descwnd);
	if (window->descwindowtext)
		psp_free(window->descwindowtext);

	window->descwnd = (ygBasicWindowPack*)psp_malloc(sizeof(ygBasicWindowPack));
	window->descwindowtext = (wchar_t*)psp_malloc(MENUWINDOW_DESC_MAXTEXT * sizeof(wchar_t));

	ygBasicWindow_Init(&window->descwnd->res, helpers_GetMainEhHeap());
	YgSys_memset(&window->descwnd->window, 0, sizeof(ygBasicWindow));
	YgSys_memset(window->descwindowtext, 0, MENUWINDOW_DESC_MAXTEXT * sizeof(wchar_t));

	window->descwnd->window.windowText = window->descwindowtext;

	window->descwnd->window.color = 0xFFFFFFFF;
	window->descwnd->window.unk3 = 1;

	window->descwnd->window.width = window->selwnd->window.width;
	window->descwnd->window.height = 64;

	window->descwnd->window.Xpos = window->selwnd->window.Xpos;
	window->descwnd->window.Ypos = window->selwnd->window.Ypos + window->selwnd->window.height + 4;

	window->descwnd->window.windowBGColor = YGWINDOW_BG_DARK;

	window->descwnd->window.windowFontSize = MENUWINDOW_DESC_FONTSIZE;
	window->descwnd->window.windowFontColor = 0xFFFFFFFF;
	window->descwnd->window.bFontShadow = 1;

	window->descwnd->window.unk43 = 1;
	window->descwnd->window.unk44 = 1;

	ygBasicWindow_Create(&window->descwnd->res, &window->descwnd->window);
	ygBasicWindow_ReqestOpenAnim(&window->descwnd->res, &window->descwnd->window);
}

void MenuWindow_Create(MenuWindow* window)
{
	MenuWindow_CreateItemWindow(window);
	MenuWindow_CreateDescWindow(window);
	window->bInited = 1;
}

void MenuWindow_AddInt(MenuWindowItem* item, int addval)
{
	int val = 0;
	
	if (item->cbValRead)
	{
		int (*ReadCallback)(uintptr_t data) = (int (*)(uintptr_t))(item->cbValRead);
		val = ReadCallback(item->cbData);
	}
	else if (item->val)
	{
		val = *item->val;
	}

	val += addval;
	if (item->loopable)
		val = loopAround(val, item->min, item->max);
	else
	{
		if (val > item->max)
			val = item->max;
		if (val < item->min)
			val = item->min;
	}

	if (item->cbValWrite)
	{
		int (*WriteCallback)(int value, uintptr_t data) = (int (*)(int, uintptr_t))(item->cbValWrite);
		WriteCallback(val, item->cbData);
	}
	else if (item->val)
	{
		*item->val = val;
	}
}

void MenuWindow_HandleExtraControls(MenuWindow* window, MenuWindowItem* item)
{
	if (item->type == MENUWINDOW_ITEM_TYPE_NONE)
		return;

	uint32_t buttons = GetPadButtons(1);
	uint32_t buttons_fast = GetPadButtons(0);

	if (item->val || (item->cbValRead && item->cbValWrite))
	{
		int bCheckLeft = 0;
		int bCheckRight = 0;

		int inc = 1;
		int dec = -1;

		if (buttons_fast & PSP_CTRL_SQUARE)
		{
			bCheckLeft = buttons_fast & PSP_CTRL_LEFT;
			bCheckRight = buttons_fast & PSP_CTRL_RIGHT;
		}
		else
		{
			bCheckLeft = buttons & PSP_CTRL_LEFT;
			bCheckRight = buttons & PSP_CTRL_RIGHT;
		}

		if (item->type != MENUWINDOW_ITEM_TYPE_BOOL)
		{
			if (buttons_fast & PSP_CTRL_LTRIGGER)
			{
				inc = 10;
				dec = -10;
			}

			if (buttons_fast & PSP_CTRL_RTRIGGER)
			{
				inc = 100;
				dec = -100;
			}

			if ((buttons_fast & PSP_CTRL_LTRIGGER) && (buttons_fast & PSP_CTRL_RTRIGGER))
			{
				inc = 1000;
				dec = -1000;
			}
		}

		if (bCheckLeft)
		{
			window->bValueChanged = 1;
			YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
			if ((item->type == MENUWINDOW_ITEM_TYPE_INT) || (item->type == MENUWINDOW_ITEM_TYPE_BOOL) || (item->type == MENUWINDOW_ITEM_TYPE_INTSTRING))
				MenuWindow_AddInt(item, dec);
		}

		if (bCheckRight)
		{
			window->bValueChanged = 1;
			YgSys_SndPlaySE(SOUND_ID_MENU_CURSOR);
			if ((item->type == MENUWINDOW_ITEM_TYPE_INT) || (item->type == MENUWINDOW_ITEM_TYPE_BOOL) || (item->type == MENUWINDOW_ITEM_TYPE_INTSTRING))
				MenuWindow_AddInt(item, inc);
		}
	}
}

int MenuWindow_DrawDesc(MenuWindow* window)
{
	if (!window->descwnd)
		return 0;

	int idx = window->selwnd->currentItem + window->selwnd->currentItemPage;
	MenuWindowItem* currItem = window->itemDrawList[idx];
	
	if (currItem->description)
	{
		if (currItem->bWideCharDesc)
			YgSys_wcscpy(window->descwindowtext, (wchar_t*)currItem->description);
		else
			sceCccUTF8toUTF16(window->descwindowtext, (MENUWINDOW_DESC_MAXTEXT * sizeof(wchar_t)), currItem->description);

		uintptr_t packet = EhPckt_Open(window->zOrder, 0);
		ygBasicWindow_Draw((uintptr_t)&packet, &window->descwnd->res);
		EhPckt_Close(packet);
	}

	return 0;
}

int MenuWindow_DrawItems(MenuWindow* window)
{
	if (!window->selwnd)
		return 0;

	int itemIdx = window->selwnd->currentItem + window->selwnd->currentItemPage;
	MenuWindowItem* item = window->itemDrawList[itemIdx];
	MenuWindow_HandleExtraControls(window, item);
	YgSelWnd_Cont(window->selwnd);

	uintptr_t packet = EhPckt_Open(window->zOrder, 0);
	YgSelWnd_Draw((uintptr_t)&packet, window->selwnd);
	EhPckt_Close(packet);
}

int MenuWindow_Draw(MenuWindow* window)
{
	if ((!window->bInited) || (window->bNotifyDestroy))
		return 0;

	if (window->bBlockGameControl)
		helpers_SetDialogBoxWantsIO(1);

	MenuWindow_DrawItems(window);
	MenuWindow_DrawDesc(window);

	if (window->selwnd->decideStatus)
	{
		int itemIdx = window->selwnd->currentItem + window->selwnd->currentItemPage;
		MenuWindowItem* item = window->itemDrawList[itemIdx];

		// return value status pack
		// in order
		// 8 bits = decide status
		// 8 bits = item index
		// 8 bits = bValueChanged
		int retval = (window->selwnd->decideStatus & 0xFF) | ((item->index & 0xFF) << 8) | ((window->bValueChanged & 0xFF) << 16);
		return retval;
	}

	return 0;
}
