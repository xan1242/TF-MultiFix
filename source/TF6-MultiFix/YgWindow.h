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

#define YGWINDOW_BG_LIGHT 0
#define YGWINDOW_BG_BLUE 1
#define YGWINDOW_BG_DARK 2

typedef struct _ygWindowResource
{
	uintptr_t unkptr1;
	char unk1[0x3C];
	int unk2; // 0x40 -- 1
	uintptr_t unkptr2; // pointer to some GIM texture
	uintptr_t unkptr3; // the heap allocated by EhHeap
}ygWindowResource;

typedef struct _ygBasicWindow
{
	/* 0x000 */ int unk3;
	/* 0x004 */ int unk4;
	/* 0x008 */ unsigned char windowBGColor; // 0x54 -- 2 -- background color type?
	/* 0x009 */ unsigned char captionBGColor; // 0x55 -- 2
	/* 0x00A */ unsigned char unk7; // padding?
	/* 0x00B */ unsigned char unk8; // padding?
	/* 0x00C */ short Xpos; // 0x58 -- (int)(float)(240.0 - (float)((float)word_4CF9F0 * 0.5));
	/* 0x00E */ short Ypos; // 0x5A -- (int)(float)(136.0 - (float)((float)word_4CF9F2 * 0.5));
	/* 0x010 */ int unk11;
	/* 0x014 */ int unk12; // 0x60 -- 1
	/* 0x018 */ short unk13; // 0x64 -- 400
	/* 0x01A */ short unk14;
	/* 0x01C */ short unk15; // 0x68 -- 100
	/* 0x01E */ short unk16;
	/* 0x020 */ short Xsize; // 0x6C -- word_4CF9F0
	/* 0x022 */ short Ysize; // 0x6E -- word_4CF9F2
	/* 0x024 */ uint32_t color; // color in ARGB
	/* 0x028 */ int unk20;
	/* 0x02C */ int bWindowCaption; // 0x78
	/* 0x030 */ int bAutoSizeCaption; // 0x7C
	/* 0x034 */ short captionWidth; // 0x80
	/* 0x036 */ short captionHeight; // 0x82
	/* 0x038 */ wchar_t* unk24; // 0x84 -- arg2 of lYgSys_SysMsg_CreateSelWindow, can be 0
	/* 0x03C */ int bCaptionFontShadow; // 0x88 -- 1
	/* 0x040 */ int unk26;
	/* 0x044 */ int bCaptionFontRuby; // 0x90
	/* 0x048 */ short unk28; // 0x94 -- 10
	/* 0x04A */ short unk29; // 0x96 -- 10
	/* 0x04C */ short unk30; // 0x98 -- 8
	/* 0x04E */ short unk31; // 0x9A
	/* 0x050 */ unsigned char unk32; // 0x9C -- 13
	/* 0x051 */ unsigned char unk33; // padding
	/* 0x052 */ unsigned char unk34; // padding
	/* 0x053 */ unsigned char unk35; // padding
	/* 0x054 */ int unk36; // 0xA0 -- -1
	/* 0x058 */ wchar_t* caption; // 0xA4 -- WINDOW TITLE STRING
	/* 0x05C */ unsigned char captionFontSize; // 0xA8
	/* 0x05D */ unsigned char unk39; // padding
	/* 0x05E */ unsigned char unk40; // padding
	/* 0x05F */ unsigned char unk41; // padding
	/* 0x060 */ uint32_t captionFontColor; // 0xAC
	/* 0x064 */ int unk43; // 0xB0 -- 1
	/* 0x068 */ int unk44; // 0xB4 -- 1
	/* 0x06C */ float unk45; // 0xB8 -- 1.0
	/* 0x07C */ float unk46; // 0xBC -- 1.0
	/* 0x074 */ int unk47;
	/* 0x078 */ int unk48;
	/* 0x07C */ uintptr_t heapptr; // 0xC8
}ygBasicWindow;

typedef struct _YgSelWnd
{
	ygWindowResource res;
	ygBasicWindow window;
	/* 0x080 */ unsigned int selFlags; // 0xCC
	/* 0x080 */ //unsigned char selFlags; // 0xCC -- OR'd by 2 and 4 -- flags?? item flags
	/* 0x081 */ //unsigned char unk49_2; // 0xCD -- flags
	/* 0x082 */ //unsigned char unk50; // 0xCE -- & 0xF0 | a3 & 0xF -- flags again?? -- 0, can be 1, 3
	/* 0x083 */ //unsigned char unk51; // padding
	/* 0x084 */ short itemcount; // 0xD0
	/* 0x086 */ short maxitems; // 0xD2
	/* 0x088 */ short unk54; // 0xD4
	/* 0x089 */ //unsigned char unk55;
	/* 0x08A */ unsigned char unk56;
	/* 0x08B */ unsigned char unk57; // 0xD7 -- flags?? byte_4CFA5B & 0xF0 | a4 & 0xF -- 0, can be 3, 4
	/* 0x08C */ int unk58;
	/* 0x090 */ int unk59;
	/* 0x094 */ int unk60; // 0xE0
	/* 0x098 */ int unk61;
	/* 0x09C */ uintptr_t unkptr5; // 0xE8 -- pointer to some GIM texture
	/* 0x0A0 */ int unk62; // 0xEC
	/* 0x0A4 */ int unk63; // 0xF0
	/* 0x0A8 */ short SelDrawWidth1; // 0xF4
	/* 0x0AA */ short SelDrawHeight1; // 0xF6
	/* 0x0AC */ int unk66;
	/* 0x0B0 */ short SelDrawWidth2; // 0xFC
	/* 0x0B2 */ short SelDrawHeight2; // 0xFE
	/* 0x0B4 */ uintptr_t ItemDrawCallback; // 0x100 -- some callback again? optional, takes 4 args - void* callback(void* ehpacket, int item_index, int X, int Y)
	/* 0x0B8 */ uintptr_t CustomDrawCallback; // 0x104 -- item draw callback function, optional, takes 5 args
	/* 0x0BC */ char unk70[0x1C];
}YgSelWnd;

uintptr_t YgSelWnd_Init(YgSelWnd* window);
uintptr_t YgSelWnd_Cont(YgSelWnd* window);
uintptr_t YgSelWnd_Draw(uintptr_t ehpacket, YgSelWnd* window);

void YgWindow_Init(uintptr_t base_addr);

#endif