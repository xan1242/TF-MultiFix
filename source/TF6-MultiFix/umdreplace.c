//
// Yu-Gi-Oh! Tag Force - UMD Recognizer Module Patches
// by xan1242 / Tenjoin
//

#include "../../includes/psp/pspmallochelper.h"
#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "umdreplace.h"

uintptr_t _base_addr_umdreplace = 0;
uintptr_t _base_size_umdreplace = 0;

int (*lUmdReplace_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lUmdReplace_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lUmdReplace_CallBack)
        return 0;

    int result = lUmdReplace_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStrings(ptrFolder, "strTbl.bin");

    return result;
}

void umdreplace_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    if (!mfconfig_GetSwapConfirmButtons())
        return;

    _base_addr_umdreplace = base_addr;
    _base_size_umdreplace = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    uintptr_t callback = minj_WriteLUI_ADDIU(0x3B7C, (uintptr_t)&lUmdReplace_CallBack_Hook, MIPSR_a1);
    lUmdReplace_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);

#ifdef TFMULTIFIX_DEBUG_PRINT
    sceKernelPrintf("lUmdReplace_CallBack: 0x%X", callback);
#endif

    minj_SetBaseAddress(oldaddr, oldsize);
}