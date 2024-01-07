//
// Yu-Gi-Oh! Tag Force - Multifix configuration stuff
// by xan1242 / Tenjoin
//

#include "multifix.h"

#ifndef MULTIFIXCONFIG_H
#define MULTIFIXCONFIG_H

#define MULTIFIXCONFIG_FILENAME "TF-Multifix.cfg"
#define MULTIFIXCONFIG_MAGIC 0x4643464D
#define MULTIFIXCONFIG_VERSION ((MODULE_VERSION_MAJOR) | ((MODULE_VERSION_MINOR & 0xFF) << 8))

typedef struct _MultiFixBasicConfig
{
	int bSwapConfirmButtons;
	int bMatrixFont;
	int bSeePartnerCards;
	int bDisableInstall;
	int bDisableDuelHelpIcon;
	int bUTF8Story;
	int bSensibleExpDisplay;
	int bConstantCheats;
}MultiFixBasicConfig;

typedef struct _MultiFixExtraConfig
{
	int bCheatConstantControlPartner;
	int bCheatDisableBanlist;
	int bCheatUnlockAllCards;
	int bCheatUnlockAllBoxes;
	int bCheatInfiniteDP;
	int CheatMaxRents;
}MultiFixExtraConfig;

typedef struct _MultiFixConfig
{
	MultiFixBasicConfig basic;
	MultiFixExtraConfig extra;
}MultiFixConfig;



// accessors
MultiFixConfig* mfconfig_GetConfig();
MultiFixConfig* mfconfig_SetConfig(MultiFixConfig* inConfig);
int mfconfig_GetSwapConfirmButtons();
//int mfconfig_SetSwapConfirmButtons(int val);
//int mfconfig_GetMatrixFont();
//int mfconfig_SetMatrixFont(int val);
//int mfconfig_GetSeePartnerCards();
//int mfconfig_SetSeePartnerCards(int val);
//int mfconfig_GetCheatControlPartner();
//int mfconfig_SetCheatControlPartner(int val);
int mfconfig_GetDisableInstall();
//int mfconfig_SetDisableInstall(int val);
//int mfconfig_GetDisableDuelHelpIcon();
//int mfconfig_SetDisableDuelHelpIcon(int val);
int mfconfig_GetCheatInfiniteDP();
int mfconfig_GetCheatDisableBanlist();
int mfconfig_GetUTF8Story();
int mfconfig_GetCheatUnlockAllBoxes();
void mfconfig_Update();
void mfconfig_Init();

#endif