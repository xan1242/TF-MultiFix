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
//#include <string.h>
#include "multifix.h"
#include "helpers.h"

//#include "../../includes/psp/injector.h"
//#include "../../includes/psp/minjector.h"

// Define the name of the game's main module here
#define MODULE_NAME_INTERNAL "modehsys"

// This is the name of this module that will be presented to the PSP OS.
#define MODULE_NAME "TFMultiFix"



// Uncomment for logging
// We use a global definition like so to reduce final binary size (which is very important because PSP is memory constrained!)
//#define LOG

// We ignore Intellisense here to reduce squiggles in VS
#ifndef __INTELLISENSE__
PSP_MODULE_INFO(MODULE_NAME, 0, MODULE_VERSION_MAJOR, MODULE_VERSION_MINOR);
#endif

// Forward-declare initialization function
int MainInit();

int bPPSSPP = 0;
// static STMOD_HANDLER previous;

#ifdef LOG
#define LOG_NAME MODULE_NAME ".log"
// Default initialized path
char logpath[128] = "ms0:/seplugins/" LOG_NAME;

//
// A basic printf logger that writes to a file.
//
int logPrintf(const char* text, ...) {
    va_list list;
    char string[512];

    va_start(list, text);
    vsprintf(string, text, list);
    va_end(list);

    SceUID fd = sceIoOpen(logpath, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777);
    if (fd >= 0) {
        sceIoWrite(fd, string, strlen(string));
        sceIoWrite(fd, "\n", 1);
        sceIoClose(fd);
    }

    return 0;
}
#endif

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
#ifdef LOG
                logPrintf("Found module " MODULE_NAME_INTERNAL);
                logPrintf("text_addr: 0x%X\ntext_size: 0x%X", info.text_addr, info.text_size);
#endif
                minj_SetBaseAddress(info.text_addr, info.text_size);

                bFoundMainModule = 1;
            }
            else if (tf_strcmp(info.name, MODULE_NAME) == 0)
            {
#ifdef LOG
                logPrintf("PRX module " MODULE_NAME);
                logPrintf("text_addr: 0x%X\ntext_size: 0x%X", info.text_addr, info.text_addr);
#endif
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

    // Since we can't use OnModuleStart like on a PSP CFW, we have to scan for modules again
    // if we want to intercept another one. Read the note at the bottom of OnModuleStart for more info.

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

//
// OnModuleStart
// Executes any time a module is started
// This currently only works on PSP CFW, not on PPSSPP
//
// You can use this to hook any subsequently loaded modules.
//
// int OnModuleStart(SceModule2* mod) 
// {
// #ifdef LOG
//     logPrintf("OnModuleStart: %s", mod->modname);
// #endif
// 
//     // You can intercept other modules with new initializers and new base addresses.
//     // There are some games with separate modules so you will cases where you have to switch around.
//     // injector only works with one at a time, so keep that in mind and update the base addresses accordingly!
// 
//     // To search for a module, you may use the 'mod' argument here.
//     // Example:
//     // if (strcmp(mod->modname, "MyModuleName") == 0)
//     // {
//     //      Hook stuff here...
//     // }
//     //
// 
//     if (!previous)
//         return 0;
//     
//     // This passes the call to the next hook that may or may not be there
//     return previous(mod);
// }

void SetDefaultPaths()
{
    if (bPPSSPP) 
    {
        //strcpy(inipath, "ms0:/PSP/PLUGINS/" MODULE_NAME "/" INI_NAME);
#ifdef LOG
        strcpy(logpath, "ms0:/PSP/PLUGINS/" MODULE_NAME "/" LOG_NAME);
#endif
    }
    else 
    { 
        //strcpy(inipath, "ms0:/seplugins/" INI_NAME);
#ifdef LOG
        strcpy(logpath, "ms0:/seplugins/" LOG_NAME);
#endif
    }
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

    if (argc > 0) 
    { 
        // on real hardware we use module_start's argp path
        // location depending on where prx is loaded from
        // strcpy(inipath, (char*)argp);
        // ptr_path = strrchr(inipath, '/');
        // if (ptr_path)
        //     strcpy(ptr_path + 1, INI_NAME);
        // else
            SetDefaultPaths();
#ifdef LOG
        strcpy(logpath, (char*)argp);
        ptr_path = strrchr(logpath, '/');
        if (ptr_path)
            strcpy(ptr_path + 1, LOG_NAME);
        else
            SetDefaultPaths();
#endif
    }
    else 
    { 
        // no arguments found
        SetDefaultPaths();
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
int MainInit() {
#ifdef LOG
    logPrintf(MODULE_NAME " MainInit");
#endif

    TFFixesInject();

    sceKernelDcacheWritebackAll();
    return 0;
}
