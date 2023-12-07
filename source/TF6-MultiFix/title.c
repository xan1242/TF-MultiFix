//
// Yu-Gi-Oh! Tag Force - Title Screen Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "title.h"

uintptr_t _base_addr_title = 0;
uintptr_t _base_size_title = 0;

int (*lTitle_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lTitle_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lTitle_CallBack)
        return 0;

    int result = lTitle_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    char strFilename[20];
    YgSys_strcpy(strFilename, "tushin_msg_j.bin");
    strFilename[11] = GetLangChar();

    PatchButtonStrings(ptrFolder, strFilename);

    return result;
}

void title_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_title = base_addr;
    _base_size_title = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);

    if (mfconfig_GetSwapConfirmButtons())
    {
        uintptr_t callback = minj_WriteLUI_ADDIU(0x18C30, (uintptr_t)&lTitle_CallBack_Hook, MIPSR_t0);
        lTitle_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lTitle_CallBack: 0x%X", callback);
#endif
    }


    minj_SetBaseAddress(oldaddr, oldsize);
}