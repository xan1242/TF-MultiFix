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
uintptr_t (*_EhPad_Get)() = (uintptr_t(*)())(0);
EhGameState helper_GameState = EHSTATE_UNKNOWN;

uintptr_t (*_YgFont_PrintLine64)(int, int, uintptr_t, wchar_t*) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0);
uintptr_t (*_YgFont_PrintLineFit64)(int, int, uintptr_t, wchar_t*, int32_t) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0);
void (*_YgFont_SetWordSeparateFlg)(int) = (void (*)(int))(0);
int (*_YgFont_GetWordSeparateFlg)() = (int (*)())(0);
void (*_YgFont_SetShadowFlg)(int) = (void (*)(int))(0);
int (*_YgFont_GetShadowFlg)() = (int (*)())(0);
wchar_t* (*_YgSys_wcscat)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
wchar_t* (*_YgSys_wcscpy)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
size_t(*_YgSys_wcslen)(const wchar_t* str) = (size_t(*)(const wchar_t*))(0);
void* (*_YgSys_memset)(void* ptr, int value, size_t num) = (void* (*)(void*, int, size_t))(0);
void* (*_YgSys_memcpy)(void* dst, const void* src, size_t num) = (void* (*)(void*, const void*, size_t))(0);
char* (*_YgSys_strcpy)(char* dst, const char* src) = (char* (*)(char*, const char*))(0);
char* (*_YgSys_strcat)(char* dst, const char* src) = (char* (*)(char*, const char*))(0);
int (*_YgSys_strcmp)(const char*, const char*) = (int (*)(const char*, const char*))(0);
size_t(*_YgSys_strlen)(const char* str) = (size_t(*)(const char*))(0);
uintptr_t (*_YgSys_GetOption)() = (uintptr_t(*)())(0);
wchar_t* (*_YgSys_GetUserName)() = (wchar_t* (*)())(0);
wchar_t* (*_YgSys_uGetPartnerName)(int, int, int) = (wchar_t* (*)(int, int, int))(0);
wchar_t* (*_YgSys_GetStrFromResource)(uintptr_t, int) = (wchar_t* (*)(uintptr_t, int))(0);
uintptr_t (*_EhFolder_SearchFile)(uintptr_t, const char*, uintptr_t) = (uintptr_t (*)(uintptr_t, const char*, uintptr_t))(0);

char theJegfis[] = "jegfis";
char strTblDefaultFilename[] = "strTbl_j.bin";

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

uintptr_t EhPad_Get()
{
    if (_EhPad_Get)
        return _EhPad_Get();
    return 0;
}

uint32_t GetPadButtons(int bGiveOneShot)
{
    if (!_EhPad_Get)
        return 0;
    uintptr_t ptrPad = EhPad_Get();

    if (bGiveOneShot)
        return *(uint32_t*)(ptrPad + 0x24);

    return *(uint32_t*)(ptrPad + 0x18);
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
    if (!_YgSys_memset)
        return NULL;
    return _YgSys_memset(ptr, value, num);
}

void* YgSys_memcpy(void* dst, const void* src, size_t num)
{
    //sceKernelPrintf("debugme");
    if (!_YgSys_memcpy)
        return NULL;
    return _YgSys_memcpy(dst, src, num);
}

size_t YgSys_wcslen(const wchar_t* str)
{
    if (!_YgSys_wcslen)
        return 0;
    return _YgSys_wcslen(str);
}

wchar_t* YgSys_wcscpy(wchar_t* dest, const wchar_t* src)
{
    if (!_YgSys_wcscpy)
        return NULL;
    return _YgSys_wcscpy(dest, src);
}

wchar_t* YgSys_wcscat(wchar_t* dest, const wchar_t* src)
{
    if (!_YgSys_wcscat)
        return NULL;
    return _YgSys_wcscat(dest, src);
}

char* YgSys_strcpy(char* dest, const char* src)
{
    if (!_YgSys_strcpy)
        return NULL;
    return _YgSys_strcpy(dest, src);
}

char* YgSys_strcat(char* dest, const char* src)
{
    if (!_YgSys_strcat)
        return NULL;
    return _YgSys_strcat(dest, src);
}

int YgSys_strcmp(const char* str1, const char* str2)
{
    if (!_YgSys_strcmp)
        return 1;
    return _YgSys_strcmp(str1, str2);
}

size_t YgSys_strlen(const char* str)
{
    if (!_YgSys_strlen)
        return 0;
    return _YgSys_strlen(str);
}

wchar_t* YgSys_GetStrFromResource(uintptr_t ptrRes, int index)
{
    if (!_YgSys_GetStrFromResource)
        return NULL;
    return _YgSys_GetStrFromResource(ptrRes, index);
}

uintptr_t EhFolder_SearchFile(uintptr_t ptrMemEhFolder, const char* filename, uintptr_t unk)
{
    if (!_EhFolder_SearchFile)
        return NULL;
    return _EhFolder_SearchFile(ptrMemEhFolder, filename, unk);
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

void str_tolower(char* str)
{
    if (!str)
        return;

    // Iterate through each character in the string
    while (*str)
    {
        // Convert uppercase characters to lowercase
        *str = tolower(*str);
        // Move to the next character
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

void YgFont_SetWordSeparateFlg(int val)
{
    if (!_YgFont_SetWordSeparateFlg)
        return;

    _YgFont_SetWordSeparateFlg(val);
}

int YgFont_GetWordSeparateFlg()
{
    if (!_YgFont_GetWordSeparateFlg)
        return 0;
    return _YgFont_GetWordSeparateFlg();
}

void YgFont_SetShadowFlg(int val)
{
    if (!_YgFont_SetShadowFlg)
        return;

    _YgFont_SetShadowFlg(val);
}

int YgFont_GetShadowFlg()
{
    if (!_YgFont_GetShadowFlg)
        return 0;
    return _YgFont_GetShadowFlg();
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

    uintptr_t patchedList[32];
    int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        wchar_t* str = YgSys_GetStrFromResource(strfile, i);
        uintptr_t strPtr = (uintptr_t)str;
        int bPatchMe = 1;


        for (int j = 0; j < 32; j++)
        {
            if (patchedList[j] == strPtr)
            {
                bPatchMe = 0;
                break;
            }
        }

        if (bPatchMe)
        {
            if (tf_wcschr(str, WCHAR_CIRCLE) || tf_wcschr(str, WCHAR_CROSS))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons(str);
                patchedList[patchCount] = strPtr;
                patchCount++;
                patchCount %= 32;
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

    uintptr_t patchedList[16];
    int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        wchar_t* str = (wchar_t*)GetTxtResourceStrPtr(strfile, i);
        uintptr_t strPtr = (uintptr_t)str;
        int bPatchMe = 1;


        for (int j = 0; j < 16; j++)
        {
            if (patchedList[j] == strPtr)
            {
                bPatchMe = 0;
                break;
            }
        }

        if (bPatchMe)
        {
            if (tf_wcschr(str, WCHAR_CIRCLE) || tf_wcschr(str, WCHAR_CROSS))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons(str);
                patchedList[patchCount] = strPtr;
                patchCount++;
                patchCount %= 16;
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
    uintptr_t patchedList[16];
    int patchCount = 0;

    for (int i = 0; i < strCount; i++)
    {
        uintptr_t strPtr = GetTxtResourceStrPtr(strfile, i);
        char* str = (char*)strPtr;
        int bPatchMe = 1;

        for (int j = 0; j < 16; j++)
        {
            if (patchedList[j] == strPtr)
            {
                bPatchMe = 0;
                break;
            }
        }

        if (bPatchMe)
        {
            if (bContainsSJISSymbol(str))
            {
#ifdef TFMULTIFIX_DEBUG_PRINT
                sceKernelPrintf("Patching str: 0x%X", str);
#endif
                tf_SwapButtonIcons_SJIS(str);
                patchedList[patchCount] = strPtr;
                patchCount++;
                patchCount %= 16;
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

char* tf_strstr(register char* string, char* substring)
{
    register char* a, * b;

    b = substring;
    if (*b == 0) {
        return string;
    }
    for (; *string != 0; string += 1) {
        if (*string != *b) {
            continue;
        }
        a = string;
        while (1) {
            if (*b == 0) {
                return string;
            }
            if (*a++ != *b++) {
                break;
            }
        }
        b = substring;
    }
    return NULL;
}

int tf_strcmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

uint32_t ReturnZeroFunc()
{
    return 0;
}

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

void helpers_SetPPSSPP(int val)
{
    _bIsOnPPSSPP = val;
}

void helpers_Init(uintptr_t base_addr)
{
    _EhPad_Get = (uintptr_t(*)())(0x3A428 + base_addr);
    _YgFont_PrintLine64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0x17F0 + base_addr);
    _YgFont_PrintLineFit64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0x4410 + base_addr);
    _YgFont_SetWordSeparateFlg = (void (*)(int))(0x21AC + base_addr);
    _YgFont_GetWordSeparateFlg = (int (*)())(0x21E8 + base_addr);
    _YgFont_SetShadowFlg = (void (*)(int))(0x2140 + base_addr);
    _YgFont_GetShadowFlg = (int (*)())(0x217C + base_addr);
    _YgSys_wcscat = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BFA0 + base_addr);
    _YgSys_wcscpy = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BF10 + base_addr);
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
    _YgSys_strcat = (char* (*)(char*, const char*))(0x4A5CC + base_addr);
    _YgSys_strlen = (size_t(*)(const char*))(0x4A6A0 + base_addr);

    ygfont_base = base_addr;
    yglang_base = base_addr;
}