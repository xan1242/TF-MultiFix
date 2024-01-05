//
// Yu-Gi-Oh! Tag Force - Various helper functions
// by xan1242 / Tenjoin
//

#include <pspsdk.h>
#include <pspuser.h>
#include <stdio.h>
#include <systemctrl.h>
#include <kubridge.h>
#include <ctype.h>
#include "helpers.h"
#include "multifix.h"
//#include "multifixconfig.h"
#include "../../includes/psp/pspmallochelper.h"

int _bIsOnPPSSPP = 0;
//uintptr_t (*_EhPad_Get)() = (uintptr_t(*)())(0);
EhGameState helper_GameState = EHSTATE_UNKNOWN;

//unsigned char dummyPadBuf[0x40];
unsigned char* dummyPadBuf;
unsigned int konamiCodeSequence[KONAMI_CODE_LENGTH] = KONAMI_CODE;
int konamiCodeIndex = 0;
uint32_t konamiCodeLastButtons = 0;

uintptr_t (*_YgFont_PrintLine64)(int, int, uintptr_t, wchar_t*) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0);
uintptr_t (*_YgFont_PrintLineFit64)(int, int, uintptr_t, wchar_t*, int32_t) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0);

void (*_YgFont_SetShadowFlg)(int) = (void (*)(int))(0);
void (*_YgFont_SetRubyCharFlg)(int) = (void (*)(int))(0);
int (*_YgFont_GetShadowFlg)() = (int (*)())(0);
int (*_YgFont_GetRubyCharFlg)() = (int (*)())(0);
int (*_YgFont_GetStrWidth)(wchar_t* str) = (int (*)(wchar_t*))(0);
wchar_t* (*_YgSys_wcscat)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
wchar_t* (*_YgSys_wcscpy)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
wchar_t* (*_YgSys_wcsncpy)(wchar_t* dest, const wchar_t* src, size_t num) = (wchar_t* (*)(wchar_t*, const wchar_t*, size_t))(0);
size_t(*_YgSys_wcslen)(const wchar_t* str) = (size_t(*)(const wchar_t*))(0);
int(*_YgSys_wcsfind)(const wchar_t* str, wchar_t wc) = (int(*)(const wchar_t*, wchar_t))(0);
void* (*_YgSys_memset)(void* ptr, int value, size_t num) = (void* (*)(void*, int, size_t))(0);
void* (*_YgSys_memcpy)(void* dst, const void* src, size_t num) = (void* (*)(void*, const void*, size_t))(0);
char* (*_YgSys_strcpy)(char* dst, const char* src) = (char* (*)(char*, const char*))(0);
char* (*_YgSys_strncpy)(char* dst, const char* src, size_t num) = (char* (*)(char*, const char*, size_t))(0);
char* (*_YgSys_strcat)(char* dst, const char* src) = (char* (*)(char*, const char*))(0);
int (*_YgSys_strcmp)(const char*, const char*) = (int (*)(const char*, const char*))(0);
size_t(*_YgSys_strlen)(const char* str) = (size_t(*)(const char*))(0);
uintptr_t (*_YgSys_GetOption)() = (uintptr_t(*)())(0);
wchar_t* (*_YgSys_GetUserName)() = (wchar_t* (*)())(0);
wchar_t* (*_YgSys_uGetPartnerName)(int, int, int) = (wchar_t* (*)(int, int, int))(0);
wchar_t* (*_YgSys_GetStrFromResource)(uintptr_t, int) = (wchar_t* (*)(uintptr_t, int))(0);
uintptr_t (*_EhFolder_SearchFile)(uintptr_t, const char*, uintptr_t) = (uintptr_t (*)(uintptr_t, const char*, uintptr_t))(0);
void (*_YgSys_InitApplication)() = (void (*)())(0);

void (*_FirstLoopFunc)(int) = (void (*)(int))(0);
int (*_sceCccUTF8toUTF16)(wchar_t* dest, size_t size, char* src) = (int (*)(wchar_t*, size_t, char*))(0);
int (*_YgSys_sprintf)(char* str, const char* format, ...) = (int (*)(char*, const char*, ...))(0);
int (*_YgSys_SndPlaySE)(int sound) = (int (*)(int))(0);
uintptr_t(*_YgSys_GetTrunkFromMRK)(int mrk) = (uintptr_t(*)(int))(0);
uintptr_t(*_YgSys_GetPersonalInfoPtr)() = (uintptr_t(*)())(0);
uintptr_t(*_YgSys_GetBoxPtr)(int box) = (uintptr_t(*)(int))(0);
int(*_YgSys_GetTrust)(int charaID) = (int(*)(int))(0);
int(*_YgSys_SetTrust)(int charaID, int val) = (int(*)(int, int))(0);
wchar_t*(*_YgSys_GetChrNameFromID)(int charaID, int unk) = (wchar_t*(*)(int, int))(0);
int(*_YgSys_AddNpcRecipe)(int charaID, int val) = (int(*)(int, int))(0);
int(*_YgSys_ReciveRecipeFromNpc)(int rcpID, int charaID) = (int(*)(int, int))(0);
void (*_YgFont_SetWordSeparateFlg)(int) = (void (*)(int))(0);
int (*_YgFont_GetWordSeparateFlg)() = (int (*)())(0);
//void (*_YgSys_Recipe_Id2Deck)(int id, void* out) = (void (*)(int, void*))(0);
int (*_uYgSys_Recipe_ChrId2DeckId)(int charaId, int rcpNum) = (int (*)(int, int))(0);


// optional functions
//uintptr_t(*_YgSys_GetUnlockNpcInfo)(int charaID) = (uintptr_t(*)(int))(0);
//wchar_t* (*_YgSys_wcscmp)(const wchar_t* wcs1, const wchar_t* wcs2) = (wchar_t* (*)(const wchar_t*, const wchar_t*))(0);
//void (*_YgAdh_Update)() = (void (*)())(0);

// WINDOW DRAW STUFF
uintptr_t(*_EhPckt_Open)(int zorder, int unk2) = (uintptr_t(*)(int, int))(0);
int(*_EhPckt_Close)(uintptr_t packet) = (int(*)(uintptr_t))(0);
uintptr_t(*_YgFont_SetEhPckt)(uintptr_t ehpacket) = (uintptr_t(*)(uintptr_t))(0);
uintptr_t(*_YgFont_GetEhPckt)() = (uintptr_t(*)())(0);
void(*_YgFont_SetSize)(int size1, int size2) = (void(*)(int, int))(0);
void(*_YgFont_SetChColorFlg)(int val) = (void(*)(int))(0);
void(*_YgFont_SetDefaultColor)(uint32_t color_argb) = (void(*)(uint32_t))(0);

int _bBlockNextPoll = 0;
int _bDialogBoxWantsIO = 0;

char theJegfis[] = "jegfis";
char strTblDefaultFilename[] = "strTbl_j.bin";

uintptr_t helper_base = 0;
uintptr_t ygfont_base = 0;
uintptr_t yglang_base = 0;

EhGameState GetGameState()
{
    return helper_GameState;
}

EhGameState SetGameState(EhGameState newState)
{
    helper_GameState = newState;
    return newState;
}

// uintptr_t EhPad_Get()
// {
//     if (_EhPad_Get)
//         return _EhPad_Get();
//     return 0;
// }

uintptr_t EhPad_Get()
{
    if (_bBlockNextPoll)
        return (uintptr_t)dummyPadBuf;
    return (EHPAD_ADDR + helper_base);
}

uintptr_t EhPad_GetAlways()
{
    return EHPAD_ADDR + helper_base;
}

uint32_t GetPadButtons(int bGiveOneShot)
{
    uintptr_t ptrPad = EhPad_GetAlways();

    if (bGiveOneShot)
        return *(uint32_t*)(ptrPad + 0x24);

    return *(uint32_t*)(ptrPad + 0x18);
}

void YgSys_InitApplication()
{
    return _YgSys_InitApplication();
}

//void YgAdh_Update()
//{
//    return _YgAdh_Update();
//}

void FirstLoopFunc(int unk)
{
    return _FirstLoopFunc(unk);
}

int YgSys_SndPlaySE(int sound)
{
    return _YgSys_SndPlaySE(sound);
}

uintptr_t YgSys_GetPersonalInfoPtr()
{
    return _YgSys_GetPersonalInfoPtr();
}

uintptr_t YgSys_GetTrunkFromMRK(int mrk)
{
    return _YgSys_GetTrunkFromMRK(mrk);
}

int YgSys_GetLimitation(uint16_t cardID)
{
    int result = 3;
    uintptr_t trunk = YgSys_GetTrunkFromMRK(cardID);
    if (trunk)
    {
        result = *(uint8_t*)(trunk + 2) & 3;
    }
    return result;
}

int YgSys_GetLimitation_Default(uint16_t cardID)
{
    for (int i = 0; i < DEFAULT_LIMITLIST_COUNT; i++)
    {
        uint16_t id = *(uint16_t*)(DEFAULT_LIMITLIST_ADDR + helper_base + (i * (sizeof(uint16_t) * 2)));
        if (id == cardID)
            return *(uint16_t*)(DEFAULT_LIMITLIST_ADDR + helper_base + (i * (sizeof(uint16_t) * 2)) + sizeof(uint16_t));
    }
    return 3;
}

int YgSys_GetTrunk(uint16_t cardID)
{
    int result = 0;
    uintptr_t trunk = YgSys_GetTrunkFromMRK(cardID);
    if (trunk)
    {
        result = *(uint8_t*)(trunk + 1) & 0x7F;
    }
    return result;
}

int YgSys_GetDuelPoint()
{
    return *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET);
}

void YgSys_SetDuelPoint(int val)
{
    *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET) = val;
}

// void YgSys_UpdateDuelPoint(int amount)
// {
//     int newval = *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET) + amount;
//     if (newval > DUELPOINT_MAX)
//         newval = DUELPOINT_MAX;
//     if (newval < 0)
//         newval = 0;
// 
//     *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET) = newval;
// 
//     if (amount > 0)
//     {
//         int newval2 = *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET2) + amount;
//         if (newval2 > DUELPOINT_MAX)
//             newval2 = DUELPOINT_MAX;
//         if (newval2 < 0)
//             newval2 = 0;
// 
//         *(int*)(YgSys_GetPersonalInfoPtr() + DUELPOINT_OFFSET2) = newval2;
//     }
// }

uintptr_t YgSys_GetBoxPtr(int box)
{
    return _YgSys_GetBoxPtr(box);
}

int YgSys_GetBoxStatus(int box)
{
    int result = 0;
    uintptr_t boxptr = YgSys_GetBoxPtr(box);

    if (boxptr)
    {
        result = (*(uint16_t*)boxptr & 0x700) >> 8;
    }

    return result;
}

int YgSys_GetTrust(int charaID)
{
    return _YgSys_GetTrust(charaID);
}


int YgSys_SetTrust(int charaID, int val)
{
    return _YgSys_SetTrust(charaID, val);
}

wchar_t* YgSys_GetChrNameFromID(int charaID, int unk)
{
    return _YgSys_GetChrNameFromID(charaID, unk);
}

//uintptr_t YgSys_GetUnlockNpcInfo(int charaID)
//{
//    return _YgSys_GetUnlockNpcInfo(charaID);
//}

int YgSys_AddNpcRecipe(int charaID, int val)
{
    return _YgSys_AddNpcRecipe(charaID, val);
}

int YgSys_ReciveRecipeFromNpc(int rcpID, int charaID)
{
    return _YgSys_ReciveRecipeFromNpc(rcpID, charaID);
}

//void YgSys_Recipe_Id2Deck(int id, void* out)
//{
//    return _YgSys_Recipe_Id2Deck(id, out);
//}

int uYgSys_Recipe_ChrId2DeckId(int id, int rcpNum)
{
    return _uYgSys_Recipe_ChrId2DeckId(id, rcpNum);
}

int YgSys_GetLang()
{
#ifdef YG_GETLANG_DEBUG
    void* addr = __builtin_extract_return_addr(__builtin_return_address(0));
    sceKernelPrintf("RAL: 0x%X (0x%X) (0x%X)", addr, (uintptr_t)addr - yglang_base, (uintptr_t)addr - yglang_base - 8);
#endif
    return *(uint32_t*)_YgSys_GetOption() & 7;
}

int YgSys_GetLang_Hook()
{
    return 1;
}

int YgSys_GetLang_Hook2()
{
    return 0;
}

uintptr_t YgSys_GetOption()
{
    return _YgSys_GetOption();
}

wchar_t* YgSys_GetUserName()
{
    return _YgSys_GetUserName();
}

wchar_t* YgSys_uGetPartnerName(int unk1, int unk2, int unk3)
{
    return _YgSys_uGetPartnerName(unk1, unk2, unk3);
}

void* YgSys_memset(void* ptr, int value, size_t num)
{
    //sceKernelPrintf("debugme");
    //if (!_YgSys_memset)
    //    return NULL;
    return _YgSys_memset(ptr, value, num);
}

void* YgSys_memcpy(void* dst, const void* src, size_t num)
{
    //sceKernelPrintf("debugme");
    //if (!_YgSys_memcpy)
    //    return NULL;
    return _YgSys_memcpy(dst, src, num);
}

size_t YgSys_wcslen(const wchar_t* str)
{
    //if (!_YgSys_wcslen)
    //    return 0;
    return _YgSys_wcslen(str);
}

wchar_t* YgSys_wcscpy(wchar_t* dest, const wchar_t* src)
{
    //if (!_YgSys_wcscpy)
    //    return NULL;
    return _YgSys_wcscpy(dest, src);
}

wchar_t* YgSys_wcsncpy(wchar_t* dest, const wchar_t* src, size_t num)
{
    //if (!_YgSys_wcscpy)
    //    return NULL;
    return _YgSys_wcsncpy(dest, src, num);
}

//wchar_t* YgSys_wcscmp(const wchar_t* wcs1, const wchar_t* wcs2)
//{
//    if (!_YgSys_wcscmp)
//        return NULL;
//    return _YgSys_wcscmp(wcs1, wcs2);
//}

wchar_t* YgSys_wcscat(wchar_t* dest, const wchar_t* src)
{
    //if (!_YgSys_wcscat)
    //    return NULL;
    return _YgSys_wcscat(dest, src);
}

int YgSys_wcsfind(const wchar_t* str, wchar_t wc)
{
    return _YgSys_wcsfind(str, wc);
}

char* YgSys_strcpy(char* dest, const char* src)
{
    //if (!_YgSys_strcpy)
    //    return NULL;
    return _YgSys_strcpy(dest, src);
}

char* YgSys_strncpy(char* dest, const char* src, size_t num)
{
    return _YgSys_strncpy(dest, src, num);
}

char* YgSys_strcat(char* dest, const char* src)
{
    //if (!_YgSys_strcat)
    //    return NULL;
    return _YgSys_strcat(dest, src);
}

int YgSys_strcmp(const char* str1, const char* str2)
{
    //if (!_YgSys_strcmp)
    //    return 1;
    return _YgSys_strcmp(str1, str2);
}

size_t YgSys_strlen(const char* str)
{
    //if (!_YgSys_strlen)
    //    return 0;
    return _YgSys_strlen(str);
}

wchar_t* YgSys_GetStrFromResource(uintptr_t ptrRes, int index)
{
    //if (!_YgSys_GetStrFromResource)
    //    return NULL;
    return _YgSys_GetStrFromResource(ptrRes, index);
}

uintptr_t EhFolder_SearchFile(uintptr_t ptrMemEhFolder, const char* filename, uintptr_t unk)
{
    //if (!_EhFolder_SearchFile)
    //    return NULL;
    return _EhFolder_SearchFile(ptrMemEhFolder, filename, unk);
}

int sceCccUTF8toUTF16(wchar_t* dest, size_t size, char* src)
{
    return _sceCccUTF8toUTF16(dest, size, src);
}

uint32_t GetStrResourceCount(uintptr_t ptrStrTbl)
{
    return *(uint32_t*)ptrStrTbl;
}

uint32_t GetTxtResourceCount(uintptr_t ptrTxtTbl)
{
    return *(uint32_t*)(ptrTxtTbl) / 8;
}

uintptr_t GetTxtResourceStrPtr(uintptr_t ptrTxtTbl, int index)
{
    return *(uint32_t*)(ptrTxtTbl + (8 * index)) + ptrTxtTbl;
}

int PPSSPP_FindModuleByName(const char* name, SceKernelModuleInfo* outInfo)
{
    if (!outInfo)
        return -1;

    SceUID modules[10];
    int count = 0;
    if (sceKernelGetModuleIdList(modules, sizeof(modules), &count) >= 0)
    {
        int i;
        SceKernelModuleInfo info;
        for (i = 0; i < count; ++i)
        {
            info.size = sizeof(SceKernelModuleInfo);
            if (sceKernelQueryModuleInfo(modules[i], &info) < 0)
            {
                continue;
            }
            if (YgSys_strcmp(info.name, name) == 0)
            {
                //*outInfo = info;
                YgSys_memcpy(outInfo, &info, sizeof(SceKernelModuleInfo));
                return 0;
            }
        }
    }

    return -1;
}

void str_tocase(char* str, int bToUpper)
{
    if (!str)
        return;

    while (*str)
    {
        if (bToUpper != 0)
            *str = toupper(*str);
        else
            *str = tolower(*str);
        str++;
    }
}

int tfFindModuleByName(const char* name, uintptr_t* outAddr, uintptr_t* outSize)
{
    *outAddr = 0;
    *outSize = 0;

    if (_bIsOnPPSSPP)
    {
        //SceKernelModuleInfo info = { 0 };
        SceKernelModuleInfo info;
        YgSys_memset(&info, 0, sizeof(SceKernelModuleInfo));
        int res = PPSSPP_FindModuleByName(name, &info);
        if (res < 0)
        {
#ifdef TFMULTIFIX_DEBUG_PRINT
            sceKernelPrintf("PPSSPP failed to find module: %s", name);
#endif
            return 0;
        }
        *outAddr = info.text_addr;
        *outSize = info.text_size;
    }
    else
    {
        //SceModule2 mod = { 0 };
        SceModule2 mod;
        YgSys_memset(&mod, 0, sizeof(SceModule2));
        int kuErrCode = kuKernelFindModuleByName((char*)name, (SceModule*)&mod);
        if (kuErrCode != 0)
        {
#ifdef TFMULTIFIX_DEBUG_PRINT
            sceKernelPrintf("failed to find module: %s", name);
#endif
            return 0;
        }
        *outAddr = mod.text_addr;
        *outSize = mod.text_size;
    }

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("module: %s | addr: 0x%X | size 0x%X", name, *outAddr, *outSize);
#endif

    return 1;
}

#if defined (YG_PRINTLINE_DEBUG) || defined (YG_PRINTBOX_DEBUG)
size_t tf_wcstombs(char* dest, const wchar_t* src, size_t n)
{
    size_t i, count = 0;

    for (i = 0; i < n && src[i] != L'\0'; ++i) 
    {
        // For simplicity, assuming UTF-16 wide characters
        wchar_t wc = src[i];

        if (wc < 0x80) 
        {
            if (dest) dest[count] = (char)wc;
            ++count;
        }
        else if (wc < 0x800) 
        {
            if (dest) 
            {
                dest[count++] = (char)(0xC0 | (wc >> 6));
                dest[count++] = (char)(0x80 | (wc & 0x3F));
            }
            else 
            {
                count += 2;
            }
        }
        // else 
        // {
        //     // Handle other cases as needed
        //     // (This is a simplified example for UTF-16)
        // }
    }

    if (dest && count < n) 
    {
        dest[count] = '\0'; // Null-terminate the multibyte string
    }

    return count;
}

// size_t tf_wcstombs2(char* dest, const wchar_t* src, size_t n)
// {
//     size_t count = 0;
// 
//     for (size_t i = 0; i < n && src[i] != L'\0'; ++i) 
//     {
//         wchar_t wc = src[i];
// 
//         // Determine the size needed for the current wide character
//         int size = wctomb(NULL, wc);
// 
//         // Check for invalid wide character
//         if (size == -1) 
//         {
//             return (size_t)-1;
//         }
// 
//         // Check if there is enough space in the destination buffer
//         if (dest && count + size <= n) 
//         {
//             // Convert the wide character to multibyte
//             size_t result = wctomb(dest + count, wc);
// 
//             // Check for errors during conversion
//             if (result == (size_t)-1) 
//             {
//                 return (size_t)-1;
//             }
// 
//             count += result;
//         }
//         else 
//         {
//             // If dest is NULL or there is not enough space, just count the characters
//             count += size;
//         }
//     }
// 
//     if (dest && count < n) 
//     {
//         dest[count] = '\0'; // Null-terminate the multibyte string
//     }
// 
//     return count;
// }
#endif
wchar_t* tf_wcschr(wchar_t* ws, wchar_t wc)
{
    size_t len = YgSys_wcslen(ws);
    for (int i = 0; i < len; i++)
    {
        if (ws[i] == wc)
            return &ws[i];
    }
    return NULL;
}

// wchar_t* tf_wcsrchr(wchar_t* ws, wchar_t wc)
// {
//     size_t len = YgSys_wcslen(ws);
// 
//     while (len)
//     {
//         if (ws[len] == wc)
//             return &ws[len];
//         --len;
//     }
// 
//     return NULL;
// }

int tf_strfind(const char* str, char c)
{
    if (!*str)
        return -1;

    for (int i = 0; str[i] != 0; i++)
    {
        if (c == str[i])
            return i;
    }

    return -1;
}

uintptr_t YgFont_PrintLine64(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
#ifdef YG_PRINTLINE_DEBUG
    size_t bufferSize = YgSys_wcslen(string) * sizeof(wchar_t);
    char* mbString = (char*)psp_malloc(bufferSize + 1);

    tf_wcstombs(mbString, string, bufferSize);
    mbString[bufferSize] = '\0';

    sceKernelPrintf("STR: %s", mbString);

#ifdef TFMULTIFIX_DEBUG_PRINT
    void* addr = __builtin_extract_return_addr(__builtin_return_address(0));
    sceKernelPrintf("RA: 0x%X (0x%X) (0x%X)", addr, (uintptr_t)addr - ygfont_base, (uintptr_t)addr - ygfont_base - 8);
#endif

    psp_free(mbString);
#endif

    return _YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t YgFont_PrintLineFit64(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
#ifdef YG_PRINTLINE_DEBUG
    size_t bufferSize = YgSys_wcslen(string) * sizeof(wchar_t);
    char* mbString = (char*)psp_malloc(bufferSize + 1);

    tf_wcstombs(mbString, string, bufferSize);
    mbString[bufferSize] = '\0';

    sceKernelPrintf("STRF: %s", mbString);

#ifdef TFMULTIFIX_DEBUG_PRINT
    void* addr = __builtin_extract_return_addr(__builtin_return_address(0));
    sceKernelPrintf("RAF: 0x%X (0x%X) (0x%X)", addr, (uintptr_t)addr - ygfont_base, (uintptr_t)addr - ygfont_base - 8);
#endif

    psp_free(mbString);
#endif

    return _YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}

#ifndef __INTELLISENSE__
asm
(
    ".global YgSys_sprintf\n"
    "YgSys_sprintf:\n"
    "lui $v0, %hi(_YgSys_sprintf)\n"
    "addiu $v0, $v0, %lo(_YgSys_sprintf)\n"
    "lw $v0, 0($v0)\n"
    "jr $v0\n"
    "nop\n"
);
#endif

void YgFont_SetWordSeparateFlg(int val)
{
    //if (!_YgFont_SetWordSeparateFlg)
    //    return;

    _YgFont_SetWordSeparateFlg(val);
}

int YgFont_GetWordSeparateFlg()
{
    //if (!_YgFont_GetWordSeparateFlg)
    //    return 0;
    return _YgFont_GetWordSeparateFlg();
}

void YgFont_SetShadowFlg(int val)
{
    //if (!_YgFont_SetShadowFlg)
    //    return;

    _YgFont_SetShadowFlg(val);
}

int YgFont_GetShadowFlg()
{
    //if (!_YgFont_GetShadowFlg)
    //    return 0;
    return _YgFont_GetShadowFlg();
}

void YgFont_SetRubyCharFlg(int val)
{
    //if (!_YgFont_SetRubyCharFlg)
    //    return;

    _YgFont_SetRubyCharFlg(val);
}

//int YgFont_GetRubyCharFlg()
//{
//    if (!_YgFont_GetRubyCharFlg)
//        return 0;
//    return _YgFont_GetRubyCharFlg();
//}

int YgFont_GetStrWidth(wchar_t* str)
{
    return _YgFont_GetStrWidth(str);
}

// void tf_ReplaceFirstChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr)
// {
//     wchar_t* firstChar = tf_wcschr(str, target_chr);
//     
//     if (firstChar)
//     {
//         *firstChar = new_chr;
//     }
// }
// 
// void tf_ReplaceLastChar(wchar_t* str, wchar_t target_chr, wchar_t new_chr)
// {
//     wchar_t* lastChar = tf_wcsrchr(str, target_chr);
//     if (lastChar)
//     {
//         *lastChar = new_chr;
//     }
// }

int bContainsSJISSymbol(const char* str)
{
    unsigned char* inputString = (unsigned char*)str;
    for (int i = 0; inputString[i] != '\0'; i++)
    {
        if (inputString[i] == 0x81)
        {
            if (inputString[i + 1] == 0x9B || inputString[i + 1] == 0x7E)
            {
                return 1;
            }
        }
    }

    return 0;
}

wchar_t* GetYgBasicWindowString(uintptr_t dialogconfig)
{
    if (*(uintptr_t*)(dialogconfig))
    {
        uintptr_t ptrStr = *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(dialogconfig)+8) + 0x38);
        return (wchar_t*)ptrStr;
    }
    return NULL;
}

void SetYgBasicWindowString(uintptr_t dialogconfig, wchar_t* str)
{
    if (*(uintptr_t*)(dialogconfig))
    {
        if (*(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(dialogconfig)+8) + 0x38))
            *(uintptr_t*)(*(uintptr_t*)(*(uintptr_t*)(dialogconfig)+8) + 0x38) = (uintptr_t)str;
    }
}

char GetLangChar()
{
    return theJegfis[YgSys_GetLang()];
}

const char* GetDefaultStrTblFilename()
{
    return strTblDefaultFilename;
}

int PatchButtonStrings(uintptr_t ptrFolder, const char* filename)
{
#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("Patching button strings in file: %s", filename);
#endif
    uintptr_t strfile = EhFolder_SearchFile(ptrFolder, filename, 0);
    if (strfile == 0)
    {
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("Failed to find file: %s", filename);
#endif
        return 1;
    }

    int strCount = GetStrResourceCount(strfile);

    //uintptr_t patchedList[32];
    //int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        wchar_t* str = YgSys_GetStrFromResource(strfile, i);
        //uintptr_t strPtr = (uintptr_t)str;
        //int bPatchMe = 1;


        //for (int j = 0; j < 32; j++)
        //{
        //    if (patchedList[j] == strPtr)
        //    {
        //        bPatchMe = 0;
        //        break;
        //    }
        //}

        //if (bPatchMe)
        {
            if (tf_wcschr(str, WCHAR_CIRCLE) || tf_wcschr(str, WCHAR_CROSS))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons(str);
                //patchedList[patchCount] = strPtr;
                //patchCount++;
                //patchCount %= 32;
            }
        }
    }
    return 0;
}

int PatchButtonStringsLang(uintptr_t ptrFolder)
{
    char strFilename[16];
    YgSys_strcpy(strFilename, GetDefaultStrTblFilename());
    strFilename[7] = GetLangChar();

    return PatchButtonStrings(ptrFolder, strFilename);
}

int PatchButtonStrings_Text(uintptr_t ptrFolder, const char* filename)
{
#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("Patching button strings in file: %s", filename);
#endif
    uintptr_t strfile = EhFolder_SearchFile(ptrFolder, filename, 0);
    if (strfile == 0)
    {
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("Failed to find file: %s", filename);
#endif
        return 1;
    }

    int strCount = GetTxtResourceCount(strfile);

    //uintptr_t patchedList[16];
    //int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        wchar_t* str = (wchar_t*)GetTxtResourceStrPtr(strfile, i);
        //uintptr_t strPtr = (uintptr_t)str;
        //int bPatchMe = 1;


        //for (int j = 0; j < 16; j++)
        //{
        //    if (patchedList[j] == strPtr)
        //    {
        //        bPatchMe = 0;
        //        break;
        //    }
        //}

       // if (bPatchMe)
        {
            if (tf_wcschr(str, WCHAR_CIRCLE) || tf_wcschr(str, WCHAR_CROSS))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons(str);
                //patchedList[patchCount] = strPtr;
                //patchCount++;
                //patchCount %= 16;
            }
        }
    }
    return 0;
}

int PatchButtonStrings_Text_SJIS(uintptr_t ptrFolder, const char* filename)
{
#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("Patching button strings in file: %s", filename);
#endif
    uintptr_t strfile = EhFolder_SearchFile(ptrFolder, filename, 0);
    if (strfile == 0)
    {
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("Failed to find file: %s", filename);
#endif
        return 1;
    }

    int strCount = GetTxtResourceCount(strfile);
    //uintptr_t patchedList[16];
    //int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        uintptr_t strPtr = GetTxtResourceStrPtr(strfile, i);
        char* str = (char*)strPtr;
        //int bPatchMe = 1;

        //for (int j = 0; j < 16; j++)
        //{
        //    if (patchedList[j] == strPtr)
        //    {
        //        bPatchMe = 0;
        //        break;
        //    }
        //}

        //if (bPatchMe)
        {
            if (bContainsSJISSymbol(str))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons_SJIS(str);
                //patchedList[patchCount] = strPtr;
                //patchCount++;
                //patchCount %= 16;
            }
        }
    }
    return 0;
}

void tf_SwapButtonIcons(wchar_t* str)
{
    while (*str != L'\0') 
    {
        if (*str == WCHAR_CROSS)
        {
            *str = WCHAR_CIRCLE;
        }
        else if (*str == WCHAR_CIRCLE)
        {
            *str = WCHAR_CROSS;
        }
        ++str;
    }
}

void tf_SwapButtonIcons_SJIS(char* str)
{
    unsigned char* ustr = (unsigned char*)str;

    for (int i = 0; ustr[i] != 0; i++)
    {
        if (ustr[i] == 0x81)
        {
            //sceKernelPrintf("found char start at: 0x%X", &str[i]);
            if (ustr[i + 1] == 0x9B)
            {
                //sceKernelPrintf("found circle char at: 0x%X", &str[i+1]);
                // replace circle with cross
                str[i + 1] = 0x7E;
                i++;
            }
            else if (ustr[i + 1] == 0x7E)
            {
                //sceKernelPrintf("found cross char at: 0x%X", &str[i+1]);
                // replace cross with circle
                str[i + 1] = 0x9B;
                i++;
            }
        }
    }
}

//char* tf_strstr(register char* string, char* substring)
//{
//    register char* a, * b;
//
//    b = substring;
//    if (*b == 0) {
//        return string;
//    }
//    for (; *string != 0; string += 1) {
//        if (*string != *b) {
//            continue;
//        }
//        a = string;
//        while (1) {
//            if (*b == 0) {
//                return string;
//            }
//            if (*a++ != *b++) {
//                break;
//            }
//        }
//        b = substring;
//    }
//    return NULL;
//}

int tf_strcmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int loopAround(int value, int min, int max) 
{
    int range = max - min + 1;

    value = (value - min + range) % range + min;

    return value;
}

// window draw stuff -- not checking func pointers for performance reasons
uintptr_t EhPckt_Open(int zorder, int unk2)
{
    return _EhPckt_Open(zorder, unk2);
}

int EhPckt_Close(uintptr_t packet)
{
    return _EhPckt_Close(packet);
}

// uintptr_t YgSelWnd_Init(YgSelWnd* window)
// {
//     return _YgSelWnd_Init(window);
// }
// 
// uintptr_t YgSelWnd_Cont(YgSelWnd* window)
// {
//     return _YgSelWnd_Cont(window);
// }
// 
// uintptr_t YgSelWnd_Draw(uintptr_t ehpacket, YgSelWnd* window)
// {
//     return _YgSelWnd_Draw(ehpacket, window);
// }

uintptr_t YgFont_SetEhPckt(uintptr_t ehpacket)
{
    return _YgFont_SetEhPckt(ehpacket);
}

uintptr_t YgFont_GetEhPckt()
{
    return _YgFont_GetEhPckt();
}

void YgFont_SetSize(int size1, int size2)
{
    return _YgFont_SetSize(size1, size2);
}

void YgFont_SetChColorFlg(int val)
{
    return _YgFont_SetChColorFlg(val);
}

void YgFont_SetDefaultColor(uint32_t color_argb)
{
    return _YgFont_SetDefaultColor(color_argb);
}

//uint32_t ReturnZeroFunc()
//{
//    return 0;
//}

#ifdef YG_PRINTLINE_DEBUG
void helpers_SetYgFontHookBase(uintptr_t base_addr)
{
    ygfont_base = base_addr;
}
#endif

#ifdef YG_GETLANG_DEBUG
void helpers_SetYgLangHookBase(uintptr_t base_addr)
{
    yglang_base = base_addr;
}
#endif

#ifdef TFMULTIFIX_DEBUG_PRINT
void helpers_PrintMemDump(void* buf, size_t size)
{
    char* printBuf = (char*)psp_malloc(size * 3);
    for (int i = 0; i < size; i++)
    {
        YgSys_sprintf(&printBuf[i * 3], "%02X ", (((char*)buf)[i] & 0xFF));
    }
    sceKernelPrintf(printBuf);

    psp_free(printBuf);
}
#endif

int helpers_KonamiCodeCheck(uint32_t buttons) 
{
    helpers_SetLastTwoKonamiButtons(YgSys_GetAssignButton_Hook(1), YgSys_GetAssignButton_Hook(0));

    if (!buttons)
        return 0;

    if (buttons & konamiCodeSequence[konamiCodeIndex]) 
    {
        konamiCodeIndex++;
    }
    else 
    {
        konamiCodeIndex = 0;
    }

    if (konamiCodeIndex == KONAMI_CODE_LENGTH) 
    {
        konamiCodeIndex = 0;
        return 1;
    }

    konamiCodeLastButtons = buttons;

    return 0;
}

void helpers_SetLastTwoKonamiButtons(uint32_t decline, uint32_t accept)
{
    konamiCodeSequence[KONAMI_CODE_LENGTH - 2] = decline;
    konamiCodeSequence[KONAMI_CODE_LENGTH - 1] = accept;
}

uintptr_t helpers_GetMainEhHeap()
{
    return *(uintptr_t*)(MAIN_EHHEAP_ADDR + helper_base);
}

void helpers_SetBlockNextInputPoll(int val)
{
    _bBlockNextPoll = val;
}

int helpers_GetBlockNextInputPoll()
{
    return _bBlockNextPoll;
}

void helpers_SetDialogBoxWantsIO(int val)
{
    _bDialogBoxWantsIO = val;
}

int helpers_GetDialogBoxWantsIO()
{
    return _bDialogBoxWantsIO;
}

void helpers_SetPPSSPP(int val)
{
    _bIsOnPPSSPP = val;
}

void helpers_Init(uintptr_t base_addr)
{
    _YgSys_InitApplication = (void (*)())(0x84F8 + base_addr);
    _FirstLoopFunc = (void (*)(int))(0x2B064 + base_addr);
    //_EhPad_Get = (uintptr_t(*)())(0x3A428 + base_addr);
    _YgFont_PrintLine64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0x17F0 + base_addr);
    _YgFont_PrintLineFit64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0x4410 + base_addr);
    
    
    _YgFont_SetShadowFlg = (void (*)(int))(0x2140 + base_addr);
    _YgFont_SetRubyCharFlg = (void (*)(int))(0x2284 + base_addr);
    _YgFont_GetShadowFlg = (int (*)())(0x217C + base_addr);
    
    _YgFont_GetStrWidth = (int (*)(wchar_t*))(0x1360 + base_addr);
    _YgSys_wcscat = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BFA0 + base_addr);
    _YgSys_wcscpy = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BF10 + base_addr);
    _YgSys_wcsncpy = (wchar_t* (*)(wchar_t*, const wchar_t*, size_t))(0x2BF50 + base_addr);
    _YgSys_wcsfind = (int (*)(const wchar_t*, wchar_t))(0x2BED4 + base_addr);
    
    _YgSys_wcslen = (size_t(*)(const wchar_t*))(0x0002BEB0 + base_addr);
    _YgSys_memset = (void* (*)(void*, int, size_t))(0x4A4E0 + base_addr);
    _YgSys_memcpy = (void* (*)(void*, const void*, size_t))(0x4A1DC + base_addr);
    _YgSys_GetOption = (uintptr_t(*)())(0x292B8 + base_addr);
    _YgSys_GetUserName = (wchar_t*(*)())(0x25BF8 + base_addr);
    _YgSys_uGetPartnerName = (wchar_t* (*)(int, int, int))(0x22FE4 + base_addr);
    _YgSys_GetStrFromResource = (wchar_t* (*)(uintptr_t, int))(0x9094 + base_addr);
    _EhFolder_SearchFile = (uintptr_t(*)(uintptr_t, const char*, uintptr_t))(0x33EB0 + base_addr);
    _YgSys_strcmp = (int (*)(const char*, const char*))(0x4A628 + base_addr);
    _YgSys_strcpy = (char* (*)(char*, const char*))(0x4A65C + base_addr);
    _YgSys_strncpy = (char* (*)(char*, const char*, size_t))(0x4A788 + base_addr);
    _YgSys_strcat = (char* (*)(char*, const char*))(0x4A5CC + base_addr);
    _YgSys_strlen = (size_t(*)(const char*))(0x4A6A0 + base_addr);
    _sceCccUTF8toUTF16 = (int (*)(wchar_t*, size_t, char*))(0x640DC + base_addr);
    _YgSys_sprintf = (int (*)(char*, const char*, ...))(0x48FB4 + base_addr);
    _YgSys_SndPlaySE = (int (*)(int))(0x2D258 + base_addr);
    _YgSys_GetTrunkFromMRK = (uintptr_t(*)(int))(0x2B678 + base_addr);
    _YgSys_GetPersonalInfoPtr = (uintptr_t(*)())(0x8748 + base_addr);
    _YgSys_GetBoxPtr = (uintptr_t(*)(int))(0x29C0C + base_addr);
    _YgSys_GetTrust = (int(*)(int))(0x2A29C + base_addr);
    _YgSys_SetTrust = (int(*)(int, int))(0x2A2D4 + base_addr);
    _YgSys_GetChrNameFromID = (wchar_t*(*)(int, int))(0x23074 + base_addr);
    _YgFont_GetWordSeparateFlg = (int (*)())(0x21E8 + base_addr);
    _YgFont_SetWordSeparateFlg = (void (*)(int))(0x21AC + base_addr);

    _YgSys_AddNpcRecipe = (int(*)(int, int))(0x2A1DC + base_addr);
    _YgSys_ReciveRecipeFromNpc = (int(*)(int, int))(0x2A820 + base_addr);
    //_YgSys_Recipe_Id2Deck = (void(*)(int, void*))(0x23CF8 + base_addr);
    _uYgSys_Recipe_ChrId2DeckId = (int(*)(int, int))(0x24114 + base_addr);

    // optional functions
    //_YgSys_GetUnlockNpcInfo = (uintptr_t(*)(int))(0x2A268 + base_addr);
    //_YgSys_wcscmp = (wchar_t* (*)(const wchar_t*, const wchar_t*))(0x2BE74 + base_addr);
    //_YgFont_GetRubyCharFlg = (int (*)())(0x22C4 + base_addr);
    //_YgAdh_Update = (void (*)())(0x1D75C + base_addr);

    // window draw stuff
    _EhPckt_Open = (uintptr_t(*)(int, int))(0x0003A954 + base_addr);
    _EhPckt_Close = (int(*)(uintptr_t))(0x3AA40 + base_addr);
    _YgFont_SetEhPckt = (uintptr_t(*)(uintptr_t))(0x2324 + base_addr);
    _YgFont_GetEhPckt = (uintptr_t(*)())(0x2368 + base_addr);
    _YgFont_SetSize = (void(*)(int, int))(0x12A0 + base_addr);
    _YgFont_SetChColorFlg = (void(*)(int))(0x20D4 + base_addr);
    _YgFont_SetDefaultColor = (void(*)(uint32_t))(0x12F4 + base_addr);
    

    // needed for analog sticks
    dummyPadBuf = (unsigned char*)psp_malloc(0x40);
    YgSys_memset(dummyPadBuf, 0, 0x40);

    dummyPadBuf[0x10] = 0x80;
    dummyPadBuf[0x14] = 0x80;

    ygfont_base = base_addr;
    yglang_base = base_addr;
    helper_base = base_addr;
}