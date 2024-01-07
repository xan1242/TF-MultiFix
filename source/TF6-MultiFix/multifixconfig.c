//
// Yu-Gi-Oh! Tag Force - MultiFix configuration stuff
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "multifix.h"
#include "helpers.h"
#include "multifixconfig.h"
#include <pspiofilemgr.h>

MultiFixConfig mfconfig = 
{
    1,		  // bSwapConfirmButtons
    0,		  // bMatrixFont
    1,		  // bSeePartnerCards
    1,		  // bDisableInstall
    1,        // bDisableDuelHelpIcon
    0,        // bUTF8Story
    1,        // bSensibleExpDisplay
    0,        // bConstantCheats
    0,		  // bCheatConstantControlPartner
    0,		  // bCheatDisableBanlist
    0,		  // bCheatUnlockAllCards
    0,		  // bCheatUnlockAllBoxes
    0,		  // bCheatInfiniteDP
    -1,		  // CheatMaxRents
};

// accessors
MultiFixConfig* mfconfig_GetConfig()
{
    return &mfconfig;
}

MultiFixConfig* mfconfig_SetConfig(MultiFixConfig* inConfig)
{
    YgSys_memcpy(&mfconfig, inConfig, sizeof(MultiFixConfig));

    return &mfconfig;
}

void mfconfig_GetPath(char* outStr)
{
    YgSys_Ms_GetDirPath(outStr);
    YgSys_strcat(outStr, "/");
    YgSys_strcat(outStr, MULTIFIXCONFIG_FILENAME);
}

int mfconfig_GetSwapConfirmButtons()
{
    return mfconfig.basic.bSwapConfirmButtons;
}
//
//int mfconfig_SetSwapConfirmButtons(int val)
//{
//    mfconfig.bSwapConfirmButtons = (val == 1);
//    return val;
//}
//
//int mfconfig_GetMatrixFont()
//{
//    return mfconfig.bMatrixFont;
//}
//
//int mfconfig_SetMatrixFont(int val)
//{
//    mfconfig.bMatrixFont = (val == 1);
//    return val;
//}
//
//int mfconfig_GetSeePartnerCards()
//{
//    return mfconfig.bSeePartnerCards;
//}
//
//int mfconfig_SetSeePartnerCards(int val)
//{
//    mfconfig.bSeePartnerCards = val;
//    return mfconfig.bSeePartnerCards;
//}
//
//int mfconfig_GetCheatControlPartner()
//{
//    return mfconfig.bCheatConstantControlPartner;
//}
//
//int mfconfig_SetCheatControlPartner(int val)
//{
//    mfconfig.bCheatConstantControlPartner = val;
//    return mfconfig.bCheatConstantControlPartner;
//}
//
int mfconfig_GetDisableInstall()
{
    return mfconfig.basic.bDisableInstall;
}
//
//int mfconfig_SetDisableInstall(int val)
//{
//    mfconfig.bDisableInstall = (val == 1);
//    return val;
//}
//
//int mfconfig_GetDisableDuelHelpIcon()
//{
//    return mfconfig.bDisableDuelHelpIcon;
//}
//
//int mfconfig_SetDisableDuelHelpIcon(int val)
//{
//    mfconfig.bDisableDuelHelpIcon = (val == 1);
//    return val;
//}

int mfconfig_GetCheatInfiniteDP()
{
    return mfconfig.extra.bCheatInfiniteDP;
}

int mfconfig_GetCheatDisableBanlist()
{
    return mfconfig.extra.bCheatDisableBanlist;
}

int mfconfig_GetCheatUnlockAllBoxes()
{
    return mfconfig.extra.bCheatUnlockAllBoxes;
}

int mfconfig_GetUTF8Story()
{
    return mfconfig.basic.bUTF8Story;
}

int mfconfig_WriteConfig(const char* filename)
{
    SceUID f = sceIoOpen(filename, PSP_O_WRONLY, 0777);
    if (f < 0)
    {
        f = sceIoOpen(filename, PSP_O_WRONLY | PSP_O_CREAT, 0777);
        if (f < 0)
            return -1;
    }

    uint32_t magic = MULTIFIXCONFIG_MAGIC;
    uint32_t version = MULTIFIXCONFIG_VERSION;
    uint32_t cfgsize = sizeof(MultiFixBasicConfig);

    sceIoWrite(f, &magic, sizeof(uint32_t));
    sceIoWrite(f, &version, sizeof(uint32_t));
    sceIoWrite(f, &cfgsize, sizeof(uint32_t));
    sceIoWrite(f, &mfconfig.basic, sizeof(MultiFixBasicConfig));

    sceIoClose(f);
    return 0;
}

int mfconfig_ReadConfig(const char* filename)
{
    SceUID f = sceIoOpen(filename, PSP_O_RDONLY, 0777);
    if (f < 0)
        return -1;

    uint32_t magic = 0;
    uint32_t version = 0;
    uint32_t cfgsize = 0;

    sceIoRead(f, &magic, sizeof(uint32_t));
    if (magic != MULTIFIXCONFIG_MAGIC)
    {
        sceIoClose(f);
        return -2;
    }

    sceIoRead(f, &version, sizeof(uint32_t));
    if (version != MULTIFIXCONFIG_VERSION)
    {
        sceIoClose(f);
        return -3;
    }

    sceIoRead(f, &cfgsize, sizeof(uint32_t));
    if (cfgsize != sizeof(MultiFixBasicConfig))
    {
        sceIoClose(f);
        return -4;
    }

    sceIoRead(f, &mfconfig.basic, sizeof(MultiFixBasicConfig));

    sceIoClose(f);
    return 0;
}

void mfconfig_Update()
{
    char cfgpath[64];
    mfconfig_GetPath(cfgpath);
    mfconfig_WriteConfig(cfgpath);
}

void mfconfig_Init()
{
    char cfgpath[64];
    mfconfig_GetPath(cfgpath);

    if (mfconfig_ReadConfig(cfgpath) < 0)
    {
        mfconfig_WriteConfig(cfgpath);
    }

    // TODO: add config reading here

    // TEST
    //mfconfig_SetCheatControlPartner(1);

    //mfconfig_SetSwapConfirmButtons(0);
}
