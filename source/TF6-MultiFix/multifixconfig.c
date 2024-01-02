//
// Yu-Gi-Oh! Tag Force - MultiFix configuration stuff
// by xan1242 / Tenjoin
//

#include <stdio.h>
#include "multifix.h"
#include "helpers.h"
#include "multifixconfig.h"

MultiFixConfig mfconfig = 
{
    1,		  // bSwapConfirmButtons
    0,		  // bMatrixFont
    1,		  // bSeePartnerCards
    1,		  // bDisableInstall
    1,        // bDisableDuelHelpIcon
    0,		  // bCheatConstantControlPartner
    0,		  // bCheatDisableBanlist
    0,		  // bCheatUnlockAllCards
    0,		  // bCheatUnlockAllBoxes
    0,		  // bCheatInfiniteDP
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

int mfconfig_GetSwapConfirmButtons()
{
    return mfconfig.bSwapConfirmButtons;
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
    return mfconfig.bDisableInstall;
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

void mfconfig_Init()
{
    // TODO: add config reading here

    // TEST
    //mfconfig_SetCheatControlPartner(1);

    //mfconfig_SetSwapConfirmButtons(0);
}
