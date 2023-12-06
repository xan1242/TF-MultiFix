//
// Yu-Gi-Oh! Tag Force - Duel Record/Rankings Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "duelrecord.h"

uintptr_t _base_addr_duelrecord = 0;
uintptr_t _base_size_duelrecord = 0;

#ifdef YG_PRINTLINE_DEBUG
uintptr_t duelrecord_YgFont_PrintLine64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
    helpers_SetYgFontHookBase(_base_addr_duelrecord);
    return YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t duelrecord_YgFont_PrintLineFit64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
    helpers_SetYgFontHookBase(_base_addr_duelrecord);
    return YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}
#endif
int (*lDuelRecord_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lDuelRecord_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lDuelRecord_CallBack)
        return 0;

    int result = lDuelRecord_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStringsLang(ptrFolder);

    return result;
}

void duelrecord_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_duelrecord = base_addr;
    _base_size_duelrecord = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fix line spacing
    minj_MakeJMPwNOP(0x11A58, (uintptr_t)&YgSys_GetLang_Hook);

    // path dependant
    minj_MakeCALL(0x4CB0, (uintptr_t)&YgSys_GetLang_Hook2);

    if (mfconfig_GetSwapConfirmButtons())
    {
        uintptr_t callback = minj_WriteLUI_ADDIU(0x4B28, (uintptr_t)&lDuelRecord_CallBack_Hook, MIPSR_t0);
        lDuelRecord_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lDuelRecord_CallBack: 0x%X", callback);
#endif
    }

#ifdef YG_PRINTLINE_DEBUG
    minj_MakeJMPwNOP(0x10200, (uintptr_t)&duelrecord_YgFont_PrintLine64_Hook);
    minj_MakeJMPwNOP(0x10210, (uintptr_t)&duelrecord_YgFont_PrintLineFit64_Hook);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}