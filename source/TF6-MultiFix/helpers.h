//
// Yu-Gi-Oh! Tag Force - Various helper functions
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include <systemctrl.h>

#ifndef TFHELPERS_H
#define TFHELPERS_H

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
uintptr_t MIPS_DiscoverPtr_a2(uintptr_t start, uintptr_t* outptrLUI, uintptr_t* outptrADDIU);
void MIPS_CalcNewA2Value(uint32_t val, uint32_t* outLUI, uint32_t* outADDIU);
uintptr_t MIPS_GetJALDestination(uint32_t instruction);
int tfFindModuleByName(const char* name, uintptr_t* outAddr, uintptr_t* outSize);
size_t tf_wcstombs(char* dest, const wchar_t* src, size_t n);
size_t tf_wcstombs2(char* dest, const wchar_t* src, size_t n);
wchar_t* tf_wcschr(wchar_t* ws, wchar_t wc);
// wchar_t* tf_wcsrchr(wchar_t* ws, wchar_t wc);
uintptr_t EhPad_Get();
uint32_t GetPadButtons(int bGiveOneShot);
EhGameState GetGameState();
EhGameState SetGameState(EhGameState newState);
uintptr_t YgFont_PrintLine64(int X, int Y, uintptr_t unk_a2, wchar_t* string);
uintptr_t YgFont_PrintLineFit64(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0);
void* YgSys_memset(void* ptr, int value, size_t num);
void* YgSys_memcpy(void* dst, const void* src, size_t num);
size_t YgSys_wcslen(const wchar_t* str);
wchar_t* YgSys_wcscpy(wchar_t* dest, const wchar_t* src);
wchar_t* YgSys_wcscat(wchar_t* dest, const wchar_t* src);
uint32_t ReturnZeroFunc();
void helpers_SetPPSSPP(int val);
void helpers_Init(uintptr_t base_addr);
void helpers_SetYgFontHookBase(uintptr_t base_addr);

#endif