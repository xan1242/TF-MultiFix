//
// Yu-Gi-Oh! Tag Force - MultiFix entrypoint
// by xan1242 / Tenjoin
//

#include <pspsdk.h>
#include <pspuser.h>
#include <pspctrl.h>
#include <systemctrl.h>
#include <kubridge.h>
#include <stdio.h>
#include "multifix.h"
#include "helpers.h"


// Define the name of the game's main module here
#define MODULE_NAME_INTERNAL "modehsys"

// This is the name of this module that will be presented to the PSP OS.
#define MODULE_NAME "TFMultiFix"


// We ignore Intellisense here to reduce squiggles in VS
#ifndef __INTELLISENSE__
PSP_MODULE_INFO(MODULE_NAME, 0, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR);
#endif

// Forward-declare initialization function
int MainInit();

int bPPSSPP = 0;

//
// CheckModules
// Executes only once on startup
// This works both on a real PSP and PPSSPP, but we limit this to PPSSPP because kuKernelFindModuleByName is better
//
static void CheckModules()
{
    SceUID modules[10];
    int count = 0;
    int bFoundMainModule = 0;
    int bFoundInternalModule = 0;
    if (sceKernelGetModuleIdList(modules, sizeof(modules), &count) >= 0)
    {
        int i;
        SceKernelModuleInfo info;
        for (i = 0; i < count; ++i)
        {
            info.size = sizeof(SceKernelModuleInfo);
            if (sceKernelQueryModuleInfo(modules[i], &info) < 0)
            {
                continue;
            }
            if (tf_strcmp(info.name, MODULE_NAME_INTERNAL) == 0)
            {
                minj_SetBaseAddress(info.text_addr, info.text_size);

                bFoundMainModule = 1;
            }
            else if (tf_strcmp(info.name, MODULE_NAME) == 0)
            {
                minj_SetModBaseAddress(info.text_addr, info.text_size);

                bFoundInternalModule = 1;
            }
    }
}

    if (bFoundInternalModule)
    {
        if (bFoundMainModule)
        {
            MainInit();
        }
    }

    return;
}

//
// CheckModulesPSP
// Executes only once on startup
// Works only on PSP CFW
//
void CheckModulesPSP()
{
    SceModule2 mod;
    int kuErrCode = kuKernelFindModuleByName(MODULE_NAME_INTERNAL, &mod);
    if (kuErrCode != 0)
        return;

    SceModule2 this_module;
    kuErrCode = kuKernelFindModuleByName(MODULE_NAME, &this_module);
    if (kuErrCode != 0)
        return;

    minj_SetBaseAddress(mod.text_addr, mod.text_size);
    minj_SetModBaseAddress(this_module.text_addr, this_module.text_addr);

    MainInit();
}

int module_start(SceSize argc, void* argp) 
{
    char* ptr_path;
    // If a kemulator interface exists, we know that we're in an emulator
    if (sceIoDevctl("kemulator:", 0x00000003, NULL, 0, NULL, 0) == 0)
    {
        bPPSSPP = 1;
        SetPPSSPP(1);
    }

    if (bPPSSPP)
        CheckModules(); // scan the modules using normal/official syscalls (https://github.com/hrydgard/ppsspp/pull/13335#issuecomment-689026242)
    else // PSP
    {
        CheckModulesPSP();
        // previous = sctrlHENSetStartModuleHandler(OnModuleStart);
    }

    return 0;
}

//
// MainInit
// Put your initialization code here
//
int MainInit() 
{
    TFFixesInject();

    sceKernelDcacheWritebackAll();
    return 0;
}
