//
// Yu-Gi-Oh! Tag Force - Field Mode Patches
// by xan1242 / Tenjoin
//

#include "../../includes/psp/injector.h"
#include "multifix.h"
#include "field.h"

#include "helpers.h"
#include "../../includes/psp/pspmallochelper.h"

uintptr_t _base_addr_field = 0;
uintptr_t _base_size_field = 0;

//void (*field_pda_item_menu)(uintptr_t, int32_t, int32_t, uintptr_t) = (void(*)(uintptr_t, int32_t, int32_t, uintptr_t))(0);
uintptr_t(*field_EhPckt_GuDrawSprite)(uintptr_t, int32_t, int32_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t) = (uintptr_t(*)(uintptr_t, int32_t, int32_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t))(0);

#ifdef YG_PRINTLINE_DEBUG
uintptr_t field_YgFont_PrintLine64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
    helpers_SetYgFontHookBase(_base_addr_field);
    return YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t field_YgFont_PrintLineFit64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
    helpers_SetYgFontHookBase(_base_addr_field);
    return YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}
#endif

uintptr_t field_EhPckt_GuDrawSprite_Hook(uintptr_t unk1, int32_t x, int32_t y, uintptr_t unk4, uintptr_t unk5, uintptr_t unk6, uintptr_t unk7, uintptr_t unk8)
{
    return field_EhPckt_GuDrawSprite(unk1, x, y + 0xC, unk4, unk5, unk6, unk7, unk8);
}

uintptr_t field_YgFont_PrintLineFit64_QuizHook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0, wchar_t* string2)
{
    size_t bufferSize1 = (YgSys_wcslen(string)) * sizeof(wchar_t);
    size_t bufferSize2 = (YgSys_wcslen(string2)) * sizeof(wchar_t);

    wchar_t* catstr = (wchar_t*)psp_malloc(bufferSize1 + bufferSize2 + 1);
    YgSys_memset(catstr, 0, bufferSize1 + bufferSize2 + 1);
    YgSys_wcscpy(catstr, string);
    YgSys_wcscat(catstr, string2);

    uintptr_t retval = YgFont_PrintLineFit64(X, Y, unk_a2 * 2, catstr, unk_t0);

    psp_free(catstr);

    return retval;
}

#ifndef __INTELLISENSE__
__attribute__((naked)) void field_hkYgFont_PrintLineFit64()
{
    asm volatile (
        "move $t1, $s7\n"
        "b field_YgFont_PrintLineFit64_QuizHook\n"
        "nop"
        );
}
#endif
void field_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_field = base_addr;
    _base_size_field = base_size;
    uintptr_t oldaddr = injector.base_addr;
    uintptr_t oldsize = injector.base_size;

    injector.SetGameBaseAddress(base_addr, base_size);

    // max num lines in a dialog box
    injector.WriteMemory16(0xB99C, 3);

    // PDA fix
    injector.MakeCALL(0x17E0, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x1F40, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x237C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x2494, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x2924, (uintptr_t)&YgSys_GetLang_Hook);

    // scrolling bug fix for PDA
 //   injector.WriteMemory32(0x359C, 0x2631FF00); // addiu s1, s1, -0x100
    injector.WriteMemory16(0x2FF4, 0x24); // ITEM LIST FIX ICONS
    injector.WriteMemory16(0x3004, 0x26); // ITEM LIST FIX TXT
    injector.WriteMemory16(0x13954, 4); // LIST BOX TEXT CENTERING
    // injector.WriteMemory16(0x19D38, 3); // duelist status bar height fix

    // fix & extend item descriptions
    injector.WriteMemory16(0x2E14, 0xD4); // Y position
    injector.WriteMemory16(0x350C, 0x34); // Y cutoff point by EhPckt_GuScissor

    //injector.WriteMemory16(0x2E1C, 0xC9);
    //injector.WriteMemory16(0x2E30, 0xF4);

    //field_pda_item_menu = (void(*)(uintptr_t, int32_t, int32_t, uintptr_t))(0x2D6C + base_addr);
    //injector.MakeCALL(0xDBC, (uintptr_t)&pda_item_menu_hook);

    //uintptr_t dest = MIPS_GetJALDestination(*(uint32_t*)0x5D0D0 + base_addr);
    field_EhPckt_GuDrawSprite = (uintptr_t(*)(uintptr_t, int32_t, int32_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t, uintptr_t))(0x5D0D0 + base_addr);
    injector.MakeCALL(0x3638, (uintptr_t)&field_EhPckt_GuDrawSprite_Hook);


    // various safe lang switch fixes (fixes duelist status bar and many minor things)
    injector.MakeCALL(0x19DFC, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x19D2C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x19DFC, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x2C78C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x18A34, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x19D8C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x18938, (uintptr_t)&YgSys_GetLang_Hook);

    injector.MakeCALL(0x2F4, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x3DEC, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0x260, (uintptr_t)&YgSys_GetLang_Hook);

    injector.MakeCALL(0xDE8C, (uintptr_t)&YgSys_GetLang_Hook);
    injector.MakeCALL(0xF29C, (uintptr_t)&YgSys_GetLang_Hook);

    // deck name Y offset
    // injector.MakeCALL(0x19C70, (uintptr_t)&field_hkTxt_40);
    // // status bar numerics
    // injector.MakeCALL(0x19F30, (uintptr_t)&field_hkFitTxt_40);
    // injector.MakeCALL(0x1A054, (uintptr_t)&field_hkFitTxt_40);
    // injector.MakeCALL(0x1A178, (uintptr_t)&field_hkFitTxt_40);

    // fix duel quiz monster names Y offset
    // injector.MakeCALL(0x20894, (uintptr_t)&field_hkFitTxt_p40);
    // injector.MakeCALL(0x20714, (uintptr_t)&field_hkFitTxt_p40);
    // injector.MakeCALL(0x20424, (uintptr_t)&field_hkFitTxt_p40);
    // injector.MakeCALL(0x20594, (uintptr_t)&field_hkFitTxt_p40);
    // injector.MakeCALL(0x20A14, (uintptr_t)&field_hkFitTxt_p40);
    // 
    // injector.MakeCALL(0x20CF0, (uintptr_t)&field_hkFitTxt_p40);
    // injector.MakeCALL(0x20AEC, (uintptr_t)&field_hkFitTxt_p40);

    // card quiz text Y offset fix
    injector.WriteMemory16(0x0002057C, 0x13);
    injector.WriteMemory16(0x000206FC, 0x13);
    injector.WriteMemory16(0x0002087C, 0x13);
    injector.WriteMemory16(0x000209FC, 0x13);
    injector.WriteMemory16(0x2040C, 0x13);

    injector.WriteMemory16(0x00020CD8, 0x18);
    injector.WriteMemory16(0x20DA0, 0x18);
    injector.WriteMemory16(0x00020AD4, 0x27);

    // numbers quiz text Y offset fix
    injector.WriteMemory16(0x274A8, 0x5E0);

    // quiz "level" box fixes
    // numbers quiz
    const int nqLvBoxOffsetX = -20;
    const int nqLvBoxOffsetY = 10;
    // white box
    injector.WriteMemory16(0x27534, 0x31 + nqLvBoxOffsetX);
    injector.WriteMemory16(0x2711C, 9 + nqLvBoxOffsetY);
    // black box
    injector.WriteMemory16(0x27508, 0x30 + nqLvBoxOffsetX);
    injector.WriteMemory16(0x2750C, 8 + nqLvBoxOffsetY);
    // text
    injector.WriteMemory16(0x0002758C, (uint16_t)((0x33 + nqLvBoxOffsetX) << 6));
    injector.WriteMemory16(0x00027590, (uint16_t)((0xE + nqLvBoxOffsetY) << 6));

    // monster quiz
    const int mqLvBoxOffsetX = 7;
    const int mqLvBoxOffsetY = -10;
    // white box
    injector.WriteMemory16(0x1FF48, 0x15 + mqLvBoxOffsetX);
    injector.WriteMemory32(0x1FF58, 0x34060000 | (uint16_t)(0x15 + mqLvBoxOffsetY));
    // black box
    injector.WriteMemory16(0x1FF1C, 0x14 + mqLvBoxOffsetX);
    injector.WriteMemory32(0x1FF2C, 0x34060000 | (uint16_t)(0x14 + mqLvBoxOffsetY));
    // text
    injector.WriteMemory16(0x1FFA4, (uint16_t)((0x17 + mqLvBoxOffsetX) << 6));
    injector.WriteMemory16(0x1FFA8, (uint16_t)((0x1A + mqLvBoxOffsetY) << 6));
    // fix BG
    injector.WriteMemory32(0x1FF24, 0x5821); // move t3, zero

    // path quiz
    const int pqLvBoxOffsetX = -20;
    const int pqLvBoxOffsetY = 10;
    // white box
    injector.WriteMemory16(0x239B4, 0x31 + pqLvBoxOffsetX);
    injector.WriteMemory16(0x239B8, 9 + pqLvBoxOffsetY);
    // black box
    injector.WriteMemory16(0x23988, 0x30 + pqLvBoxOffsetX);
    injector.WriteMemory16(0x2398C, 8 + pqLvBoxOffsetY);
    // text
    injector.WriteMemory16(0x23A0C, (uint16_t)((0x33 + pqLvBoxOffsetX) << 6));
    injector.WriteMemory16(0x23A10, (uint16_t)((0xE + pqLvBoxOffsetY) << 6));

    // title fix
    // concat the name and the string into one
    // first, skip the second print
    injector.MakeJMPwNOP(0x23900, 0x23944 + base_addr);

    // then hook for concat
    injector.MakeCALL(0x238F0, (uintptr_t)&field_hkYgFont_PrintLineFit64);

    // Y offset
    injector.WriteMemory16(0x238E4, 0x5E0);
    injector.WriteMemory16(0x23928, 0x5E0);

    // fix items Y offset
    injector.WriteMemory16(0x22AD0, 8);

#ifdef YG_PRINTLINE_DEBUG
    injector.MakeJMPwNOP(0x0005ACF0, (uintptr_t)&field_YgFont_PrintLine64_Hook);
    injector.MakeJMPwNOP(0x0005AD00, (uintptr_t)&field_YgFont_PrintLineFit64_Hook);
#endif


    // baseline hook
    // injector.MakeJMPwNOP(0x5C548, (uintptr_t)&YgSys_GetLang_Hook_Loud);
    // // exclusions
    // injector.MakeCALL(0x30978, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0xCDAC, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0xCEC4, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x1390C, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x14024, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x14034, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x14058, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x14048, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x30FDC, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x1E230, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x23F60, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x20F00, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x35B50, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x33DD4, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x3484C, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x83CC, (uintptr_t)&YgSys_GetLang_Hook2);
    // injector.MakeCALL(0x8A9C, (uintptr_t)&YgSys_GetLang_Hook2);





    injector.SetGameBaseAddress(oldaddr, oldsize);
}