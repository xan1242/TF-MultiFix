//
// Yu-Gi-Oh! Tag Force - Various helper functions
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include <systemctrl.h>

#ifndef TFHELPERS_H
#define TFHELPERS_H

#define WCHAR_CIRCLE L'\x25CB'
#define WCHAR_CROSS L'\xD7'

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
void str_tolower(char* str);
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

#endif