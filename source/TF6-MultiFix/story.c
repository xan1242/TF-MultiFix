//
// Yu-Gi-Oh! Tag Force - Story Mode Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "story.h"

uintptr_t _base_addr_story = 0;
uintptr_t _base_size_story = 0;

uintptr_t* (*story_uStoryLangIndex)() = (uintptr_t* (*)())(0);
uintptr_t (*story_uStoryLangText)() = (uintptr_t (*)())(0);

uintptr_t story_GetLangText_Hook(int index)
{
    uintptr_t* offsets = story_uStoryLangIndex();
    if (mfconfig_GetCheatUTF8Story())
    {
        return story_uStoryLangText() + (offsets[index] * sizeof(char));
    }

    return story_uStoryLangText() + (offsets[index] * sizeof(wchar_t));
}

wchar_t* story_YgSys_wcscpy_UTF8(wchar_t* dest, const wchar_t* src)
{
    if (mfconfig_GetCheatUTF8Story())
    {
        sceCccUTF8toUTF16(dest, (YgSys_strlen((char*)src) + 1) * sizeof(wchar_t), (char*)src);
        return dest;
    }
    return YgSys_wcscpy(dest, src);
}

wchar_t* story_YgSys_wcsncpy_UTF8(wchar_t* dest, const wchar_t* src, size_t num)
{
    if (mfconfig_GetCheatUTF8Story())
    {
        return (wchar_t*)YgSys_strncpy((char*)dest, (const char*)src, num);
    }

    return YgSys_wcsncpy(dest, src, num);
}

int story_YgSys_wcsfind_UTF8(const wchar_t* str, wchar_t c)
{
    if (mfconfig_GetCheatUTF8Story())
    {
        return tf_strfind((const char*)str, (char)c);
    }
    return YgSys_wcsfind(str, c);
}

int story_YgSys_wcslen_UTF8(const wchar_t* str)
{
    if (mfconfig_GetCheatUTF8Story())
    {
        return YgSys_strlen((const char*)str);
    }
    return YgSys_wcslen(str);
}

wchar_t* story_YgSys_wcscat_Hook(wchar_t* dest, const wchar_t* src)
{
    return YgSys_wcscat(dest, L" & ");
}

uintptr_t hkStoryItemStrHook_ExitAddr = 0;
void hkStoryItemStrHook();
#ifndef __INTELLISENSE__
asm
(
    ".global hkStoryItemStrHook\n"
    "hkStoryItemStrHook:\n"
    "move $s6, $s5\n"
    "jal mfconfig_GetCheatUTF8Story\n"
    "lui $v1, %hi(hkStoryItemStrHook_ExitAddr)\n"
    "addiu $v1, $v1, %lo(hkStoryItemStrHook_ExitAddr)\n"
    "bnez $v0, story_ExitUTF8\n"
    "addu $s6, $s5, $s5\n"
    "story_ExitUTF8:\n"
    "addu $s6, $s1, $s6\n"
    "lw $v1, 0($v1)\n"
    "jr $v1\n"
);
#endif

void story_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_story = base_addr;
    _base_size_story = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    minj_MakeJMPwNOP(0x35790, (uintptr_t)&YgSys_GetLang_Hook);

    // exclude path sensitive stuff
    minj_MakeCALL(0xB070, (uintptr_t)&YgSys_GetLang_Hook2);

    // add spacing to ampersand
    minj_MakeCALL(0x9828, (uintptr_t)&story_YgSys_wcscat_Hook);
    minj_MakeCALL(0x2414, (uintptr_t)&story_YgSys_wcscat_Hook);

    // UTF-8 story
    minj_MakeCALL(0x163A4, (uintptr_t)&story_YgSys_wcscpy_UTF8);
    minj_MakeCALL(0x162C8, (uintptr_t)&story_YgSys_wcsfind_UTF8);
    minj_MakeCALL(0x16294, (uintptr_t)&story_YgSys_wcslen_UTF8);
    minj_MakeCALL(0x162E0, (uintptr_t)&story_YgSys_wcsncpy_UTF8);

    story_uStoryLangIndex = (uintptr_t* (*)())(0xC8D0 + base_addr);
    story_uStoryLangText = (uintptr_t (*)())(0xC860 + base_addr);
    minj_MakeJMPwNOP(0xC884, (uintptr_t)&story_GetLangText_Hook);

    hkStoryItemStrHook_ExitAddr = 0x162C4 + base_addr;
    minj_MakeJMPwNOP(0x162BC, (uintptr_t)&hkStoryItemStrHook);


    minj_SetBaseAddress(oldaddr, oldsize);
}

