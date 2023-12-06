//
// Yu-Gi-Oh! Tag Force - Duel Tutorial Patches
// by xan1242 / Tenjoin
//

#include "multifix.h"
#include "multifixconfig.h"
#include "helpers.h"
#include "tutorial.h"

uintptr_t _base_addr_tutorial = 0;
uintptr_t _base_size_tutorial = 0;

int (*lTutorial_CallBack)(uintptr_t ptrFile, uintptr_t filesize) = (int(*)(uintptr_t, uintptr_t))0;
int lTutorial_CallBack_Hook(uintptr_t ptrFolder, size_t filesize)
{
    if (!lTutorial_CallBack)
        return 0;

    int result = lTutorial_CallBack(ptrFolder, filesize);
    if (!result)
        return result;

    //uintptr_t ptrFolder = *(uintptr_t*)(0x51290 + _base_addr_tutorial);

    char strFilename[16];
    YgSys_strcpy(strFilename, "tuto_text_j.bin");
    strFilename[10] = GetLangChar();

    if (YgSys_GetLang())
        PatchButtonStrings_Text(ptrFolder, strFilename);
    else
        PatchButtonStrings_Text_SJIS(ptrFolder, strFilename);

    return result;
}

void tutorial_Patch(uintptr_t base_addr, uintptr_t base_size)
{
    _base_addr_tutorial = base_addr;
    _base_size_tutorial = base_size;
    uintptr_t oldaddr = minj_GetBaseAddress();
    uintptr_t oldsize = minj_GetBaseSize();

    minj_SetBaseAddress(base_addr, base_size);


    minj_MakeJMPwNOP(0x54798, (uintptr_t)&YgSys_GetLang_Hook);

    minj_MakeCALL(0x30C8, (uintptr_t)&YgSys_GetLang_Hook2);


    if (mfconfig_GetSwapConfirmButtons())
    {
        // patch the callback param at EhFile_NbRead to pass the EhFolder pointer to the callback
        minj_WriteMemory32(0x2DB4, 0x00404825); // move t1, v0

        uintptr_t callback = minj_WriteLUI_ADDIU(0x2D9C, (uintptr_t)&lTutorial_CallBack_Hook, MIPSR_t0);
        lTutorial_CallBack = (int(*)(uintptr_t, uintptr_t))(callback);
#ifdef TFMULTIFIX_DEBUG_PRINT
        sceKernelPrintf("lTutorial_CallBack: 0x%X", callback);
#endif
    }


    minj_SetBaseAddress(oldaddr, oldsize);
}