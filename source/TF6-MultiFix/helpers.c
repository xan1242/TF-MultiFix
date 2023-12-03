//
// Yu-Gi-Oh! Tag Force - Various helper functions
// by xan1242 / Tenjoin
//

#include <pspsdk.h>
#include <pspuser.h>
#include <stdio.h>
#include <string.h>
#include <systemctrl.h>
#include <kubridge.h>
#include <ctype.h>
//#include <stdlib.h>
#include "helpers.h"
#include "multifix.h"
#include "../../includes/psp/pspmallochelper.h"

int _bIsOnPPSSPP = 0;
uintptr_t (*_EhPad_Get)() = (uintptr_t(*)())(0);
EhGameState helper_GameState = EHSTATE_UNKNOWN;

uintptr_t (*_YgFont_PrintLine64)(int, int, uintptr_t, wchar_t*) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0);
uintptr_t (*_YgFont_PrintLineFit64)(int, int, uintptr_t, wchar_t*, int32_t) = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0);
wchar_t* (*_YgSys_wcscat)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
wchar_t* (*_YgSys_wcscpy)(wchar_t* dest, const wchar_t* src) = (wchar_t* (*)(wchar_t*, const wchar_t*))(0);
size_t(*_YgSys_wcslen)(const wchar_t* str) = (size_t(*)(const wchar_t*))(0);
void* (*_YgSys_memset)(void* ptr, int value, size_t num) = (void* (*)(void*, int, size_t))(0);
void* (*_YgSys_memcpy)(void* dst, const void* src, size_t num) = (void* (*)(void*, const void*, size_t))(0);

uintptr_t ygfont_base = 0;

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
            if (strcmp(info.name, name) == 0)
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

uintptr_t MIPS_DiscoverPtr_a2(uintptr_t start, uintptr_t* outptrLUI, uintptr_t* outptrADDIU)
{
    uintptr_t ptrLUI = 0;
    uintptr_t ptrADD = start;

    // find the first LUI after ADDIU
    for (int i = 0; i < 10; i++)
    {
        uint32_t ins = *(uint32_t*)(ptrADD + (4 * i)) & 0xFFFF0000;
        if (ins == 0x3C060000)
        {
            ptrLUI = ptrADD + (4 * i);
            break;
        }
    }

    if (ptrLUI == NULL)
        return NULL;


    ptrADD = NULL;

    // find the first ADDIU after LUI
    for (int i = 0; i < 10; i++)
    {
        uint32_t ins = *(uint32_t*)(ptrLUI + (4 * i)) & 0xFFFF0000;
        if (ins == 0x24C60000)
        {
            ptrADD = ptrLUI + (4 * i);
            break;
        }
    }

    if (ptrADD == NULL)
        return NULL;

    uint32_t insLUI = *(uint32_t*)ptrLUI;
    uint32_t insADD = *(uint32_t*)ptrADD;

    // construct the ptr from the instructions
    uint32_t part1 = (insLUI & 0xFFFF);
    uint32_t part2 = (insADD & 0xFFFF);
    // TODO: check for negative numbers, this is a signed number
    if (part2 > 0x7FFF)
        part1 -= 1;
    part1 <<= 16;

    uintptr_t retVal = part1 | part2;

    if (outptrLUI)
        *outptrLUI = ptrLUI;
    if (outptrADDIU)
        *outptrADDIU = ptrADD;

    return retVal;
}

void MIPS_CalcNewA2Value(uint32_t val, uint32_t* outLUI, uint32_t* outADDIU)
{
    uint32_t part2 = val & 0xFFFF;
    uint32_t part1 = (val >> 16) & 0xFFFF;

    if (part2 > 0x7FFF)
        part1 += 1;

    *outLUI = 0x3C060000 | part1;
    *outADDIU = 0x24C60000 | part2;
}

uintptr_t MIPS_GetJALDestination(uint32_t instruction)
{
    return (instruction & 0x03FFFFFF) << 2;
}

int tfFindModuleByName(const char* name, uintptr_t* outAddr, uintptr_t* outSize)
{
    *outAddr = 0;
    *outSize = 0;

    if (_bIsOnPPSSPP)
    {
        SceKernelModuleInfo info = { 0 };
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
        SceModule2 mod = { 0 };
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

#ifdef YG_PRINTLINE_DEBUG
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
//         len--;
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

uint32_t ReturnZeroFunc()
{
    return 0;
}

void helpers_SetYgFontHookBase(uintptr_t base_addr)
{
    ygfont_base = base_addr;
}

void helpers_SetPPSSPP(int val)
{
    _bIsOnPPSSPP = val;
}

void helpers_Init(uintptr_t base_addr)
{
    _EhPad_Get = (uintptr_t(*)())(0x3A428 + base_addr);
    _YgFont_PrintLine64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*))(0x17F0 + base_addr);
    _YgFont_PrintLineFit64 = (uintptr_t(*)(int, int, uintptr_t, wchar_t*, int32_t))(0x4410 + base_addr);
    _YgSys_wcscat = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BFA0 + base_addr);
    _YgSys_wcscpy = (wchar_t* (*)(wchar_t*, const wchar_t*))(0x0002BF10 + base_addr);
    _YgSys_wcslen = (size_t(*)(const wchar_t*))(0x0002BEB0 + base_addr);
    _YgSys_memset = (void* (*)(void*, int, size_t))(0x4A4E0 + base_addr);
    _YgSys_memcpy = (void* (*)(void*, const void*, size_t))(0x4A1DC + base_addr);

    ygfont_base = base_addr;
}