//
// Yu-Gi-Oh! Tag Force - Duel Manager Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "duelmgr.h"


#include "helpers.h"
#ifdef YG_PRINTLINE_DEBUG
#include "../../includes/psp/pspmallochelper.h"
#include <wchar.h>
#endif

uintptr_t _base_addr_duelmgr = 0;
uintptr_t _base_size_duelmgr = 0;

#ifdef YG_PRINTLINE_DEBUG
uintptr_t duelmgr_YgFont_PrintLine64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
    helpers_SetYgFontHookBase(_base_addr_duelmgr);
    return YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t duelmgr_YgFont_PrintLineFit64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
    helpers_SetYgFontHookBase(_base_addr_duelmgr);
    return YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}
#endif

int (*lDuelMgr_Result_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lDuelMgr_Result_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lDuelMgr_Result_CallBack)
        return 0;

    int result = lDuelMgr_Result_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStrings(ptrFolder, "strTbl.bin");

    return result;
}

void duelmgr_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_duelmgr = base_addr;
    _base_size_duelmgr = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    //duelmgr_SwappedCount = 0;
    //YgSys_memset(duelmgr_SwappedStrings, 0, sizeof(wchar_t*) * DUELMGR_MAX_SWAP_STR);

    minj_MakeJMPwNOP(0x2D500, (uintptr_t)&YgSys_GetLang_Hook);

    // lang file specific exclusions
    minj_MakeCALL(0x10A8, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x6144, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0xAF74, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x16DD0, (uintptr_t)&YgSys_GetLang_Hook2);

    //
    // POST DUEL SCREEN
    //
    
//    // item text fix
//    injector.WriteMemory32(0x11044, 0x02209821); // move s3, s1
//
//    // bottom text fix
//    // leftmost text Y offset
//    injector.WriteMemory16(0x10544, 0x4000);
//    // center text Y offset
//    injector.WriteMemory16(0x10590, 0x4000);
//    // rightmost text Y offset
//    injector.WriteMemory16(0x105F8, 0x4000);
//
//    
    // fix DP column header Y pos
    minj_WriteMemory16(0xB9D0, 0xAE0);
    minj_WriteMemory16(0xB51C, 0xAE0);
//
    // fix bonus total label
    minj_WriteMemory16(0xBFC4, 0x38F0);
//
//    // challenge title card text fix
//    injector.WriteMemory16(0x12358, 3);
//
//    // high score column header
//    injector.MakeCALL(0xCC40, (uintptr_t)&duelmgr_hkTxt_40);
//
//    // item column header
//    injector.MakeCALL(0xBF90, (uintptr_t)&duelmgr_hkTxt_40);
//
//    // numerics
//    injector.MakeCALL(0xC570, (uintptr_t)&duelmgr_hkTxt_40);
//    // colon
//    injector.MakeCALL(0x1154C, (uintptr_t)&duelmgr_hkTxt_40);
//
//    // DP text
//    injector.MakeCALL(0x1143C, (uintptr_t)&duelmgr_hkTxt_40);
//    injector.MakeCALL(0xC004, (uintptr_t)&duelmgr_hkTxt_40);
//    injector.MakeCALL(0xB7DC, (uintptr_t)&duelmgr_hkTxt_40);
//
//    // headers
//    injector.MakeCALL(0x10C64, (uintptr_t)&duelmgr_hkFitTxt_40);
//    injector.MakeCALL(0x10C94, (uintptr_t)&duelmgr_hkFitTxt_40);
//
//    injector.MakeCALL(0x1323C, (uintptr_t)&duelmgr_hkFitTxt_40);
//
//    // numeric and text around
//    injector.MakeCALL(0x1337C, (uintptr_t)&duelmgr_hkFitTxt_40);
//    injector.MakeCALL(0x13308, (uintptr_t)&duelmgr_hkFitTxt_40);
//
    //
    // POST DUEL SCREEN END
    //

    //
    // JANKEN / RPS SCREEN
    //

    // "Choose a card." Y pos
    minj_WriteMemory16(0x8608, 0x3EE0);

//    // player name
//    injector.MakeCALL(0x1124, (uintptr_t)&duelmgr_hkFitTxt_50);

    //
    // JANKEN / RPS SCREEN END
    //

    if (mfconfig_GetSwapConfirmButtons())
    {
        // change the confirm button text (cross and square)
        uintptr_t callback = minj_WriteLUI_ADDIU(0xAFB8, (uintptr_t)&lDuelMgr_Result_CallBack_Hook, MIPSR_t0);
        lDuelMgr_Result_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);

#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lDuelMgr_Result_CallBack: 0x%X", callback);
#endif
    }

#ifdef YG_PRINTLINE_DEBUG
    minj_MakeJMPwNOP(0x2BCA8, (uintptr_t)&duelmgr_YgFont_PrintLine64_Hook);
    minj_MakeJMPwNOP(0x2BCB8, (uintptr_t)&duelmgr_YgFont_PrintLineFit64_Hook);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}
