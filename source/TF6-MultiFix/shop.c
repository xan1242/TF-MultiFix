//
// Yu-Gi-Oh! Tag Force - Card Shop Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "shop.h"

uintptr_t _base_addr_shop = 0;
uintptr_t _base_size_shop = 0;

#ifdef YG_PRINTLINE_DEBUG
uintptr_t shop_YgFont_PrintLine64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string)
{
    helpers_SetYgFontHookBase(_base_addr_shop);
    return YgFont_PrintLine64(X, Y, unk_a2, string);
}

uintptr_t shop_YgFont_PrintLineFit64_Hook(int X, int Y, uintptr_t unk_a2, wchar_t* string, int32_t unk_t0)
{
    helpers_SetYgFontHookBase(_base_addr_shop);
    return YgFont_PrintLineFit64(X, Y, unk_a2, string, unk_t0);
}
#endif

int (*lShop_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lShop_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lShop_CallBack)
        return 0;

    int result = lShop_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStringsLang(ptrFolder);

    return result;
}

void shop_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_shop = base_addr;
    _base_size_shop = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    // fix pack title position
    //minj_WriteMemory32(0x88D4, 0x03C09021); // move s2, fp
    minj_MakeCALL(0x88B0, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x16A74, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x11868, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x117A0, (uintptr_t)&YgSys_GetLang_Hook);
    //minj_MakeCALL(0x6100, (uintptr_t)&YgSys_GetLang_Hook); // matrix font
    minj_MakeCALL(0x613C, (uintptr_t)&YgSys_GetLang_Hook);
    minj_MakeCALL(0x5660, (uintptr_t)&YgSys_GetLang_Hook);

    if (mfconfig_GetSwapConfirmButtons())
    {
        uintptr_t callback = minj_WriteLUI_ADDIU(0x174E8, (uintptr_t)&lShop_CallBack_Hook, MIPSR_t0);
        lShop_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lShop_CallBack: 0x%X", callback);
#endif
    }

#ifdef YG_PRINTLINE_DEBUG
    minj_MakeJMPwNOP(0x2CFE8, (uintptr_t)&shop_YgFont_PrintLine64_Hook);
    minj_MakeJMPwNOP(0x2CFF8, (uintptr_t)&shop_YgFont_PrintLineFit64_Hook);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}
