//
// Yu-Gi-Oh! Tag Force - Password Machine Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "password.h"

uintptr_t _base_addr_password = 0;
uintptr_t _base_size_password = 0;

int (*lPassword_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lPassword_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lPassword_CallBack)
        return 0;

    int result = lPassword_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    PatchButtonStringsLang(ptrFolder);

    return result;
}

void password_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_password = base_addr;
    _base_size_password = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    if (mfconfig_GetSwapConfirmButtons())
    {
        uintptr_t callback = minj_WriteLUI_ADDIU(0x3030, (uintptr_t)&lPassword_CallBack_Hook, MIPSR_t0);
        lPassword_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lPassword_CallBack: 0x%X", callback);
#endif
    }

    minj_SetBaseAddress(base_addr, base_size);
}