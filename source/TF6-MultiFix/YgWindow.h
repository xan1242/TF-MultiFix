//
// Yu-Gi-Oh! Tag Force - ygBasicWindow & YgSelWnd interface
// by xan1242 / Tenjoin
//

#include <stdint.h>
#include <stddef.h>

#ifndef YGWINDOW_H
#define YGWINDOW_H

#define YGSEL_INACTIVE 1
#define YGSEL_HIGHLIGHT 2
#define YGSEL_DISABLEITEM 4
#define YGSEL_NOAUTOTERM 8
#define YGSEL_SKIPDISABLED 1 << 8
#define YGSEL_INVISIBLE 4 << 8
#define YGSEL_HORIZONTAL 8 << 8
#define YGSEL_VERTICAL 16 << 8
#define YGSEL_DIALOGBUTTONS_OK 1 << 16
#define YGSEL_DIALOGBUTTONS_OKCANCEL 2 << 16
#define YGSEL_DIALOGBUTTONS_YESNO 3 << 16
#define YGSEL_DIALOGBUTTONS_YESNOCANCEL 4 << 16

#define YGSEL_LOCKITEM(index) 1 << (index)

#define YGWINDOW_BG_LIGHT 0
#define YGWINDOW_BG_BLUE 1
#define YGWINDOW_BG_DARK 2

typedef struct _ygWindowResource
{
	uintptr_t unkptr1;
	char unk1[0x3C];
	int unk2; // 0x40 -- 1
	uintptr_t selCsrTexture; // pointer to some GIM texture
	uintptr_t unkptr3; // the heap allocated by EhHeap
}ygWindowResource;

typedef struct _ygBasicWindow
{
	/* off   / seloff*/

	/* 0x000 / 0x04C */ int unk3;
	/* 0x004 / 0x050 */ int unk4;
	/* 0x008 / 0x054 */ unsigned char windowBGColor;
	/* 0x009 / 0x055 */ unsigned char captionBGColor; // 2
	/* 0x00A / 0x056 */ unsigned char unk7; // padding?
	/* 0x00B / 0x057 */ unsigned char unk8; // padding?
	/* 0x00C / 0x058 */ short Xpos;
	/* 0x00E / 0x05A */ short Ypos;
	/* 0x010 / 0x05C */ int unk11;
	/* 0x014 / 0x060 */ int bAutoSizeWindow; // 1
	/* 0x018 / 0x064 */ short maxWidth; // 400
	/* 0x01A / 0x066 */ short maxHeight;
	/* 0x01C / 0x068 */ short minWidth; // 100
	/* 0x01E / 0x06A */ short minHeight;
	/* 0x020 / 0x06C */ short width;
	/* 0x022 / 0x06E */ short height;
	/* 0x024 / 0x070 */ uint32_t color; // color in ARGB
	/* 0x028 / 0x074 */ int unk20;
	/* 0x02C / 0x078 */ int bWindowCaption;
	/* 0x030 / 0x07C */ int bAutoSizeCaption;
	/* 0x034 / 0x080 */ short captionWidth;
	/* 0x036 / 0x082 */ short captionHeight;
	/* 0x038 / 0x084 */ wchar_t* windowText; // arg2 of lYgSys_SysMsg_CreateSelWindow, can be 0
	/* 0x03C / 0x088 */ int bCaptionFontShadow; // 1
	/* 0x040 / 0x08C */ int unk26;
	/* 0x044 / 0x090 */ int bCaptionFontRuby;
	/* 0x048 / 0x094 */ short leftPadding; // 10
	/* 0x04A / 0x096 */ short rightPadding; // 10
	/* 0x04C / 0x098 */ short topPadding; // 8
	/* 0x04E / 0x09A */ short bottomPadding;
	/* 0x050 / 0x09C */ unsigned char windowFontSize; // 13
	/* 0x051 / 0x09D */ unsigned char unk33; // padding
	/* 0x052 / 0x09E */ unsigned char unk34; // padding
	/* 0x053 / 0x09F */ unsigned char unk35; // padding
	/* 0x054 / 0x0A0 */ uint32_t windowFontColor; // -1
	/* 0x058 / 0x0A4 */ wchar_t* caption;
	/* 0x05C / 0x0A8 */ unsigned char captionFontSize;
	/* 0x05D / 0x0A9 */ unsigned char unk39; // padding
	/* 0x05E / 0x0AA */ unsigned char unk40; // padding
	/* 0x05F / 0x0AB */ unsigned char unk41; // padding
	/* 0x060 / 0x0AC */ uint32_t captionFontColor;
	/* 0x064 / 0x0B0 */ int unk43; // 1
	/* 0x068 / 0x0B4 */ int unk44; // 1
	/* 0x06C / 0x0B8 */ float unk45; // 1.0
	/* 0x07C / 0x0BC */ float unk46; // 1.0
	/* 0x074 / 0x0C0 */ int unk47;
	/* 0x078 / 0x0C4 */ int unk48;
}ygBasicWindow;

typedef struct _ygBasicWindowPack
{
	ygWindowResource res;
	ygBasicWindow window;
}ygBasicWindowPack;

typedef struct _YgSelWnd
{
	/* 0x000 */ ygWindowResource res;
	/* 0x04C */ ygBasicWindow window;
	/* 0x0C8 */ uintptr_t heapptr;
	/* 0x0CC */ unsigned int selFlags;
	/* 0x0D0 */ short itemcount;
	/* 0x0D2 */ short maxitems;
	/* 0x0D4 */ short unk54; // seems important
	/* 0x0D6 */ unsigned char unk56; // seems important, can't tell what this is
	/* 0x0D7 */ unsigned char unk57; // flags?? byte_4CFA5B & 0xF0 | a4 & 0xF -- 0, can be 3, 4
	/* 0x0D8 */ int unk58; // padding?
	/* 0x0DC */ int unk59; // has something to do with unk56 and selFlags & 0x7800
	/* 0x0E0 */ uint32_t itemLockBitfield; // locks items
	/* 0x0E4 */ int unk61; // has something to do with scroll triangle
	/* 0x0E8 */ uintptr_t buttonTexture;
	/* 0x0EC */ unsigned char unk62_1; // some flags again, decide button related
	/* 0x0ED */ unsigned char unk62_2; // seems important - WndAnimCount related?
	/* 0x0EE */ unsigned char unk62_3; // padding?
	/* 0x0EF */ unsigned char unk62_4; // padding?
	/* 0x0F0 */ int unk63; // padding?
	/* 0x0F4 */ short SelDrawWidth1;
	/* 0x0F6 */ short SelDrawHeight1;
	/* 0x0F8 */ short SelDrawOffsetX;
	/* 0x0F6 */ short SelDrawOffsetY;
	/* 0x0FC */ short SelDrawWidth2;
	/* 0x0FE */ short SelDrawHeight2;
	/* 0x100 */ uintptr_t ItemDrawCallback; // optional, takes 4 args - void* callback(void* ehpacket, int item_index, int X, int Y)
	/* 0x104 */ uintptr_t CustomDrawCallback; // window draw callback function, optional, takes 5 args
	/* 0x108 */ uintptr_t unkCallback1;
	/* 0x10C */ uintptr_t unkCallback2;
	/* 0x110 */ uintptr_t selCsrDrawCallback;
	/* 0x114 */ uintptr_t unkCallback4;
	/* 0x118 */ uintptr_t selItemBGDrawCallback;
	/* 0x11C */ uintptr_t unkCallback6;
	/* 0x120 */ int unk71;
}YgSelWnd;

uintptr_t YgSelWnd_Init(YgSelWnd* window);
uintptr_t YgSelWnd_Cont(YgSelWnd* window);
uintptr_t YgSelWnd_Term(YgSelWnd* window);
uintptr_t YgSelWnd_Draw(uintptr_t ehpacket, YgSelWnd* window);

// reduce functions on compile time to optimize size
// these aren't critical to basic functionality of a YgSelWnd
#ifndef YGWINDOW_ESSENTIALS_ONLY
uintptr_t YgSelWnd_DecideButton(YgSelWnd* window, unsigned char unk);
uintptr_t YgSelWnd_DecideSelect(YgSelWnd* window, int unk);
uintptr_t YgSelWnd_ReqestCloseAnim(YgSelWnd* window);
uintptr_t YgSelWnd_DrawButton(uintptr_t ehpacket, YgSelWnd* window, int X, int Y);
uintptr_t YgSelWnd_DrawSelectCsr(uintptr_t ehpacket, YgSelWnd* window, int X, int Y);
uintptr_t YgSelWnd_DrawSelectItemBG(uintptr_t ehpacket, YgSelWnd* window, int X, int Y);
uintptr_t YgSelWnd_SelCsrDec(YgSelWnd* window);
uintptr_t YgSelWnd_SelCsrInc(YgSelWnd* window);
#endif

uintptr_t ygBasicWindow_Init(ygWindowResource* res, uintptr_t heap);
uintptr_t ygBasicWindow_Create(ygWindowResource* res, ygBasicWindow* window);
uintptr_t ygBasicWindow_Term(ygBasicWindow* window);
uintptr_t ygBasicWindow_Draw(uintptr_t ehpacket, ygWindowResource* window);

#ifndef YGWINDOW_ESSENTIALS_ONLY
uintptr_t ygBasicWindow_DeleteWindow(ygWindowResource* res, ygBasicWindow* window);
uintptr_t ygBasicWindow_ReqestOpenAnim(ygWindowResource* res, ygBasicWindow* window);
uintptr_t ygBasicWindow_ReqestCloseAnim(ygWindowResource* res, ygBasicWindow* window);
uintptr_t ygBasicWindow_IsFinishAnim(ygWindowResource* res, ygBasicWindow* window);
int ygBasicWindow_GetWndStringBottom(ygWindowResource* res, ygBasicWindow* window);
uintptr_t ygBasicWindow_GetWndStringRect(ygWindowResource* res, ygBasicWindow* window, int* outWidth, int* outHeight);
int ygBasicWindow_GetWndState(ygWindowResource* res, ygBasicWindow* window);
#endif

void YgWindow_Init(uintptr_t base_addr);

#endif