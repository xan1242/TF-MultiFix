//
// Yu-Gi-Oh! Tag Force - Multifix configuration stuff
// by xan1242 / Tenjoin
//

#ifndef MULTIFIXCONFIG_H
#define MULTIFIXCONFIG_H

typedef struct _MultiFixConfig
{
	int bSwapConfirmButtons;
	int bMatrixFont;
	int bSeePartnerCards;
	int bDisableInstall;
	int bDisableDuelHelpIcon;
	int bCheatConstantControlPartner;
	int bCheatDisableBanlist;
	int bCheatUnlockAllCards;
	int bCheatInfiniteDP;

}MultiFixConfig;

// accessors
MultiFixConfig* mfconfig_GetConfig();
MultiFixConfig* mfconfig_SetConfig(MultiFixConfig* inConfig);
int mfconfig_GetSwapConfirmButtons();
int mfconfig_SetSwapConfirmButtons(int val);
int mfconfig_GetMatrixFont();
int mfconfig_SetMatrixFont(int val);
int mfconfig_GetSeePartnerCards();
int mfconfig_SetSeePartnerCards(int val);
int mfconfig_GetCheatControlPartner();
int mfconfig_SetCheatControlPartner(int val);
int mfconfig_GetDisableInstall();
int mfconfig_SetDisableInstall(int val);
int mfconfig_GetDisableDuelHelpIcon();
int mfconfig_SetDisableDuelHelpIcon(int val);

void mfconfig_Init();

#endif