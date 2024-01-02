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
#define WCHAR_SQUARE L'\x25A1'
#define WCHAR_TRIANGLE L'\x25B3'

#define MAIN_EHHEAP_ADDR 0x314BD4
#define EHPAD_ADDR 0x59D4BC
#define DUELPOINT_OFFSET 0x24F4C
#define DUELPOINT_OFFSET2 0x24F50
#define DUELPOINT_MAX 999999999
#define YG_CHARACTER_COUNT 180
#define YG_CHARACTER_MAXTRUST 4000

#define SOUND_ID_MENU_CURSOR 0xDA75
#define SOUND_ID_MENU_DECIDE 0xDA76
#define SOUND_ID_MENU_CANCEL 0xDA77
#define SOUND_ID_MENU_INVALID 0xDA78
#define SOUND_ID_MENU_WINDOWPOPUP_1 0xDA79
#define SOUND_ID_MENU_WINDOWPOPUP_2 0xDA7D

#define KONAMI_CODE_LENGTH 10
#define KONAMI_CODE {PSP_CTRL_UP, PSP_CTRL_UP, PSP_CTRL_DOWN, PSP_CTRL_DOWN, PSP_CTRL_LEFT, PSP_CTRL_RIGHT, PSP_CTRL_LEFT, PSP_CTRL_RIGHT, PSP_CTRL_CIRCLE, PSP_CTRL_CROSS}

#define DEFAULT_LIMITLIST_ADDR 0x6C770
#define DEFAULT_LIMITLIST_COUNT 280

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

int PPSSPP_FindModuleByName(const char* name, SceKernelModuleInfo* outInfo);
void str_tocase(char* str, int bToUpper);
int tfFindModuleByName(const char* name, uintptr_t* outAddr, uintptr_t* outSize);
wchar_t* tf_wcschr(wchar_t* ws, wchar_t wc);
int tf_strcmp(const char* s1, const char* s2);
uintptr_t EhPad_Get();
uintptr_t EhPad_GetAlways();
uint32_t GetPadButtons(int bGiveOneShot);
EhGameState GetGameState();
EhGameState SetGameState(EhGameState newState);
uintptr_t YgFont_PrintLine64(int X, int Y, uintptr_t unk_a2, wchar_t* string);
uintptr_t YgFont_PrintLineFit64(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0);
void YgFont_SetShadowFlg(int val);
int YgFont_GetShadowFlg();
void YgFont_SetRubyCharFlg(int val);
int YgFont_GetStrWidth(wchar_t* str);
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
void FirstLoopFunc(int unk);
int YgSys_sprintf(char* str, const char* format, ...);
int sceCccUTF8toUTF16(wchar_t* dest, size_t size, char* src);
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
int YgSys_SndPlaySE(int sound);
uintptr_t YgSys_GetTrunkFromMRK(int mrk);
int YgSys_GetLimitation(uint16_t cardID);
int YgSys_GetLimitation_Default(uint16_t cardID);
int YgSys_GetTrunk(uint16_t cardID);
int YgSys_GetDuelPoint();
void YgSys_SetDuelPoint(int val);
void YgSys_UpdateDuelPoint(int amount);
uintptr_t YgSys_GetPersonalInfoPtr();
uintptr_t YgSys_GetBoxPtr(int box);
int YgSys_GetBoxStatus(int box);
int YgSys_GetTrust(int charaID);
int YgSys_SetTrust(int charaID, int val);
wchar_t* YgSys_GetChrNameFromID(int charaID, int unk);
uintptr_t YgSys_GetUnlockNpcInfo(int charaID);
void YgFont_SetWordSeparateFlg(int val);
int YgFont_GetWordSeparateFlg();

// optional functions
//uintptr_t YgSys_GetUnlockNpcInfo(int charaID);
//
//wchar_t* YgSys_wcscmp(const wchar_t* wcs1, const wchar_t* wcs2);
//void YgFont_SetMatrixFontFlg(int val);
//int YgFont_GetRubyCharFlg();

//void YgAdh_Update();
//void tf_ReplaceFirstChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr);
//void tf_ReplaceLastChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr);
//size_t tf_wcstombs2(char* dest, const wchar_t* src, size_t n);
//char* tf_strstr(register char* string, char* substring);
//wchar_t* tf_wcsrchr(wchar_t* ws, wchar_t wc);
//size_t tf_wcstombs(char* dest, const wchar_t* src, size_t n);


//uint32_t ReturnZeroFunc();
int loopAround(int value, int min, int max);
void helpers_SetPPSSPP(int val);
void helpers_Init(uintptr_t base_addr);
void helpers_SetYgFontHookBase(uintptr_t base_addr);
void helpers_SetYgLangHookBase(uintptr_t base_addr);
void helpers_SetBlockNextInputPoll(int val);
int helpers_GetBlockNextInputPoll();
void helpers_SetDialogBoxWantsIO(int val);
int helpers_GetDialogBoxWantsIO();
int helpers_KonamiCodeCheck(uint32_t buttons);
void helpers_SetLastTwoKonamiButtons(uint32_t decline, uint32_t accept);
uintptr_t helpers_GetMainEhHeap();

// WINDOW DRAW STUFF
uintptr_t EhPckt_Open(int zorder, int unk2);
int EhPckt_Close(uintptr_t packet);
uintptr_t YgFont_SetEhPckt(uintptr_t ehpacket);
uintptr_t YgFont_GetEhPckt();
void YgFont_SetSize(int size1, int size2);
void YgFont_SetChColorFlg(int val);
void YgFont_SetDefaultColor(uint32_t color_argb);

#endif