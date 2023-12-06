//
// Yu-Gi-Oh! Tag Force - Deck Tutorial Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "deck.h"

uintptr_t _base_addr_decktutorial = 0;
uintptr_t _base_size_decktutorial = 0;

#ifdef YG_PRINTLINE_DEBUG
uintptr_t decktutorial_YgFont_PrintLine64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
    helpers_SetYgFontHookBase(_base_addr_decktutorial);
    return YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t decktutorial_YgFont_PrintLineFit64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
    helpers_SetYgFontHookBase(_base_addr_decktutorial);
    return YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}
#endif



int (*lDeckTutorial_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lDeckTutorial_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lDeckTutorial_CallBack)
        return 0;

    int result = lDeckTutorial_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStringsLang(ptrFolder);

    return result;
}

void decktutorial_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_decktutorial = base_addr;
    _base_size_decktutorial = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);


    minj_MakeJMPwNOP(0x30780, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x21710, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x12A6C, (uintptr_t)&YgSys_GetLang_Hook2);
    minj_MakeCALL(0x12C14, (uintptr_t)&YgSys_GetLang_Hook2);

    // max num lines in a dialog box
    minj_WriteMemory16(0x1D4B4, 3);

    // remove window padding to store more text
    minj_WriteMemory16(0x1D7BC, 0);
    minj_WriteMemory16(0x1D7C4, 0);
    minj_WriteMemory16(0x1D7CC, 0);


    //minj_WriteMemory16(0x1D78C, 0x78); // visual Y window size
    //minj_WriteMemory16(0x1D77C, 0);
    //minj_WriteMemory16(0x1D75C, 0);


    // float something1 = 1.0f;
    // float something2 = 1.0f;
    // 
    // minj_WriteMemory16(0x1D474, ((*(uint32_t*)&something1) & 0xFFFF0000) >> 16);
    // minj_WriteMemory16(0x1D484, ((*(uint32_t*)&something2) & 0xFFFF0000) >> 16);


    if (mfconfig_GetSwapConfirmButtons())
    {
        uintptr_t callback = minj_WriteLUI_ADDIU(0x21610, (uintptr_t)&lDeckTutorial_CallBack_Hook, MIPSR_t0);
        lDeckTutorial_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lDeckTutorial_CallBack: 0x%X", callback);
#endif
    }

#ifdef YG_PRINTLINE_DEBUG
    injector.MakeJMPwNOP(0x2EF28, (uintptr_t)&decktutorial_YgFont_PrintLine64_Hook);
    injector.MakeJMPwNOP(0x2EF38, (uintptr_t)&decktutorial_YgFont_PrintLineFit64_Hook);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}