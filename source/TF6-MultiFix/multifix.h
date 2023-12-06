//
// Yu-Gi-Oh! Tag Force - MultiFix code
// by xan1242 / Tenjoin
//

#ifndef MULTIFIX_H
#define MULTIFIX_H

// define for debug printing to sceKernelPrintf
#define TFMULTIFIX_DEBUG_PRINT
// define for debug printing of the return address of YgFont_PrintLine64 and YgFont_PrintLineFit64
//#define YG_PRINTLINE_DEBUG
// define for debug printing of the return address of YgFont_PrintBox64
//#define YG_PRINTBOX_DEBUG

// define for debug printing of the return address of YgSys_GetLang
//#define YG_GETLANG_DEBUG


#include "../../includes/psp/minjector.h"

#define LINE_SPACING_VAL 0x40

void TFFixesInject();
void SetPPSSPP(int val);
//int YgSys_GetLang_Hook();
//int YgSys_GetLang_Hook2();
//int YgSys_GetLang_Hook_Loud();

#endif