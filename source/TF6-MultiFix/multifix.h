//
// Yu-Gi-Oh! Tag Force - MultiFix code
// by xan1242 / Tenjoin
//

#ifndef MULTIFIX_H
#define MULTIFIX_H

#define MODULE_VERSION_MAJOR 1
#define MODULE_VERSION_MINOR 0

// formatting the window is a bit janky so we do it here...
#define MULTIFIX_ABOUT_FORMAT "\
             Tag Force 6 MultiFix v%d.%d\n\n%s\
"
#define MULTIFIX_ABOUT_TEXT "\
A multi-purpose fix & enhancement kit for\n\
Yu-Gi-Oh! Tag Force games.\n\
\n\
\n\
Created by Xan / Tenjoin\
"

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
#define YGFONT_FLAGS_ADDR 0x1EF99C

void TFFixesInject();
void SetPPSSPP(int val);
//int YgSys_GetLang_Hook();
//int YgSys_GetLang_Hook2();
//int YgSys_GetLang_Hook_Loud();

// string hashes
#define REL_CARDALBUM_PRX_STRHASH 0x35B64094
#define REL_CHARALIST_PRX_STRHASH 0x0075B844
#define REL_CONVMACHINE_PRX_STRHASH 0x8C566A34
#define REL_DECK_PRX_STRHASH 0xE08313A0
#define REL_DECKSWAP_PRX_STRHASH 0xE561735B
#define REL_DECKTUTORIAL_PRX_STRHASH 0xC9DBF674
#define REL_DUELDRAW_PRX_STRHASH 0x5F7E5D41
#define REL_DUELENG_PRX_STRHASH 0xBB3E266D
#define REL_DUELMGR_PRX_STRHASH 0x1382FD99
#define REL_DUELRECORD_PRX_STRHASH 0x4A8B63D2
#define REL_FIELD_PRX_STRHASH 0x28AACC8D
#define REL_GALLERY_PRX_STRHASH 0x34826239
#define REL_HTMLVIEW_PRX_STRHASH 0xAF6D1E19
#define REL_LABO_PRX_STRHASH 0x0C9C0107
#define REL_LIMITLIST_PRX_STRHASH 0xBCF63324
#define REL_PASSWORD_PRX_STRHASH 0x6FE7931C
#define REL_RECIPEVIEWER_PRX_STRHASH 0x49B06113
#define REL_SELECTCARD_PRX_STRHASH 0xDF7990A3
#define REL_SHOP_PRX_STRHASH 0xBBA5A523
#define REL_SOUNDTEST_PRX_STRHASH 0x33BCC992
#define REL_STORY_PRX_STRHASH 0x4B12052A
#define REL_TITLE_PRX_STRHASH 0x0A34A26B
#define REL_TUTORIAL_PRX_STRHASH 0x3ECE7B3D
#define REL_TUTORIALLIST_PRX_STRHASH 0x42EA7A19
#define REL_UMDREPLACE_PRX_STRHASH 0x70952A6B

#endif