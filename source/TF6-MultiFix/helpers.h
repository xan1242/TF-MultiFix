//
// Yu-Gi-Oh! Tag Force - Various helper functions
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include <systemctrl.h>

#ifndef TFHELPERS_H
#define TFHELPERS_H

#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272

#define PSP_SCREEN_HALF_WIDTH 480
#define PSP_SCREEN_HALF_HEIGHT 272

#define PSP_SCREEN_WIDTH_FLOAT 480.0f
#define PSP_SCREEN_HEIGHT_FLOAT 272.0f

#define PSP_SCREEN_HALF_WIDTH_FLOAT 240.0f
#define PSP_SCREEN_HALF_HEIGHT_FLOAT 136.0f

#define WCHAR_CIRCLE L'\x25CB'
#define WCHAR_CROSS L'\xD7'

#define MAIN_EHHEAP_ADDR 0x314BD4

typedef enum _EhGameState
{
	EHSTATE_UNKNOWN,
	EHSTATE_TITLE,
	EHSTATE_DECK,
	EHSTATE_SHOP,
	EHSTATE_DUEL,
	EHSTATE_FIELD,
	EHSTATE_COUNT
}EhGameState;

typedef struct _YgSelWnd
{
	uintptr_t unkptr1;
	char unk1[0x3C];
	int unk2; // 0x40 -- 1
	uintptr_t unkptr2; // pointer to some GIM texture
	uintptr_t unkptr3; // the heap allocated by EhHeap
	int unk3; // 0x4C -- 1
	int unk4;
	unsigned char BGColor; // 0x54 -- 2 -- background color type?
	unsigned char unk6; // 0x55 -- 2
	unsigned char unk7; // padding?
	unsigned char unk8; // padding?
	short Xpos; // 0x58 -- (int)(float)(240.0 - (float)((float)word_4CF9F0 * 0.5));
	short Ypos; // 0x5A -- (int)(float)(136.0 - (float)((float)word_4CF9F2 * 0.5));
	int unk11; 
	int unk12; // 0x60 -- 1
	short unk13; // 0x64 -- 400
	short unk14;
	short unk15; // 0x68 -- 100
	short unk16;
	short Xsize; // 0x6C -- word_4CF9F0
	short Ysize; // 0x6E -- word_4CF9F2
	uint32_t color; // 0x70 -- -1 -- color in ARGB
	int unk20;
	int unk21;
	int unk22; // 0x7C
	int unk23;
	int unk24; // 0x84 -- arg2 of lYgSys_SysMsg_CreateSelWindow, can be 0
	int unk25; // 0x88 -- 1
	int unk26;
	int unk27;
	short unk28; // 0x94 -- 10
	short unk29; // 0x96 -- 10
	short unk30; // 0x98 -- 8
	short unk31; // 0x9A
	unsigned char unk32; // 0x9C -- 13
	unsigned char unk33; // padding
	unsigned char unk34; // padding
	unsigned char unk35; // padding
	int unk36; // 0xA0 -- -1
	wchar_t* title; // 0xA4 -- WINDOW TITLE STRING
	unsigned char unk38; // 0xA8
	unsigned char unk39; // padding
	unsigned char unk40; // padding
	unsigned char unk41; // padding
	int unk42; // 0xAC
	int unk43; // 0xB0 -- 1
	int unk44; // 0xB4 -- 1
	float unk45; // 0xB8 -- 1.0
	float unk46; // 0xBC -- 1.0
	int unk47;
	int unk48;
	uintptr_t heapptr; // 0xC8
	unsigned char unk49; // 0xCC -- OR'd by 2 and 4 -- flags?? item flags
	unsigned char unk49_2; // 0xCD -- flags
	unsigned char unk50; // 0xCE -- & 0xF0 | a3 & 0xF -- flags again?? -- 0, can be 1, 3
	unsigned char unk51; // padding
	short itemcount; // 0xD0
	short unk53; // 0xD2
	unsigned char unk54;
	unsigned char unk55;
	unsigned char unk56;
	unsigned char unk57; // 0xD7 -- flags?? byte_4CFA5B & 0xF0 | a4 & 0xF -- 0, can be 3, 4
	int unk58;
	int unk59;
	int unk60; // 0xE0
	int unk61;
	uintptr_t unkptr5; // 0xE8 -- pointer to some GIM texture
	int unk62; // 0xEC
	int unk63; // 0xF0
	short SelDrawWidth1; // 0xF4
	short SelDrawHeight1; // 0xF6
	int unk66;
	short SelDrawWidth2; // 0xFC
	short SelDrawHeight2; // 0xFE
	uintptr_t ItemDrawCallback; // 0x100 -- some callback again? optional, takes 4 args - void* callback(void* ehpacket, int item_index, int X, int Y)
	uintptr_t CustomDrawCallback; // 0x104 -- item draw callback function, optional, takes 5 args
	char unk70[0x1C];
}YgSelWnd;

int PPSSPP_FindModuleByName(const char* name, SceKernelModuleInfo* outInfo);
void str_tocase(char* str, int bToUpper);
//uintptr_t MIPS_DiscoverPtr(uintptr_t start, uintptr_t* outptrLUI, uintptr_t* outptrADDIU, RegisterID register_num);
//uintptr_t MIPS_DiscoverPtr_a2(uintptr_t start, uintptr_t* outptrLUI, uintptr_t* outptrADDIU);
//void MIPS_CalcNewRegValue(uint32_t val, uint32_t* outLUI, uint32_t* outADDIU, RegisterID register_num);
//void MIPS_CalcNewA2Value(uint32_t val, uint32_t* outLUI, uint32_t* outADDIU);
//uintptr_t MIPS_GetJALDestination(uint32_t instruction);
//uintptr_t MIPS_WriteLUI_ADDIU(uintptr_t addr, uintptr_t dest, RegisterID reg);
int tfFindModuleByName(const char* name, uintptr_t* outAddr, uintptr_t* outSize);
size_t tf_wcstombs(char* dest, const wchar_t* src, size_t n);
//size_t tf_wcstombs2(char* dest, const wchar_t* src, size_t n);
wchar_t* tf_wcschr(wchar_t* ws, wchar_t wc);
char* tf_strstr(register char* string, char* substring);
int tf_strcmp(const char* s1, const char* s2);
//wchar_t* tf_wcsrchr(wchar_t* ws, wchar_t wc);
uintptr_t EhPad_Get();
uint32_t GetPadButtons(int bGiveOneShot);
EhGameState GetGameState();
EhGameState SetGameState(EhGameState newState);
uintptr_t YgFont_PrintLine64(int X, int Y, uintptr_t unk_a2, wchar_t* string);
uintptr_t YgFont_PrintLineFit64(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0);
void YgFont_SetWordSeparateFlg(int val);
int YgFont_GetWordSeparateFlg();
void YgFont_SetShadowFlg(int val);
int YgFont_GetShadowFlg();
void YgFont_SetRubyCharFlg(int val);
int YgFont_GetRubyCharFlg();
void* YgSys_memset(void* ptr, int value, size_t num);
void* YgSys_memcpy(void* dst, const void* src, size_t num);
size_t YgSys_wcslen(const wchar_t* str);
wchar_t* YgSys_wcscpy(wchar_t* dest, const wchar_t* src);
wchar_t* YgSys_wcscat(wchar_t* dest, const wchar_t* src);
char* YgSys_strcpy(char* dest, const char* src);
char* YgSys_strcat(char* dest, const char* src);
int YgSys_strcmp(const char* str1, const char* str2);
size_t YgSys_strlen(const char* str);
wchar_t* YgSys_GetStrFromResource(uintptr_t ptrRes, int index);
uintptr_t YgSys_GetOption();
wchar_t* YgSys_GetUserName();
wchar_t* YgSys_uGetPartnerName(int unk1, int unk2, int unk3);
int YgSys_GetLang();
int YgSys_GetLang_Hook();
int YgSys_GetLang_Hook2();
void YgSys_InitApplication();
uintptr_t EhFolder_SearchFile(uintptr_t ptrMemEhFolder, const char* filename, uintptr_t unk);
void tf_SwapButtonIcons(wchar_t* str);
void tf_SwapButtonIcons_SJIS(char* str);
wchar_t* GetYgBasicWindowString(uintptr_t dialogconfig);
void SetYgBasicWindowString(uintptr_t dialogconfig, wchar_t* str);
uint32_t GetStrResourceCount(uintptr_t ptrStrTbl);
uint32_t GetTxtResourceCount(uintptr_t ptrTxtbl);
uintptr_t GetTxtResourceStrPtr(uintptr_t ptrTxtTbl, int index);
char GetLangChar();
const char* GetDefaultStrTblFilename();
int bContainsSJISSymbol(const char* inputString);
int PatchButtonStrings(uintptr_t ptrFolder, const char* filename);
int PatchButtonStringsLang(uintptr_t ptrFolder);
int PatchButtonStrings_Text(uintptr_t ptrFolder, const char* filename);
int PatchButtonStrings_Text_SJIS(uintptr_t ptrFolder, const char* filename);
//void tf_ReplaceFirstChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr);
//void tf_ReplaceLastChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr);
uint32_t ReturnZeroFunc();
void helpers_SetPPSSPP(int val);
void helpers_Init(uintptr_t base_addr);
void helpers_SetYgFontHookBase(uintptr_t base_addr);
void helpers_SetYgLangHookBase(uintptr_t base_addr);
uintptr_t helpers_GetMainEhHeap();

// WINDOW DRAW STUFF
uintptr_t EhPckt_Open(int unk1, int unk2);
int EhPckt_Close(uintptr_t packet);
uintptr_t YgSelWnd_Init(YgSelWnd* window);
uintptr_t YgSelWnd_Cont(YgSelWnd* window);
uintptr_t YgSelWnd_Draw(uintptr_t ehpacket, YgSelWnd* window);
uintptr_t YgFont_SetEhPckt(uintptr_t ehpacket);
uintptr_t YgFont_GetEhPckt();
void YgFont_SetSize(int size1, int size2);
void YgFont_SetChColorFlg(int val);
void YgFont_SetDefaultColor(uint32_t color_argb);

#endif