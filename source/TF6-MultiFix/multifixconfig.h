//
// Yu-Gi-Oh! Tag Force - Multifix configuration stuff
// by xan1242 / Tenjoin
//

#ifndef MULTIFIXCONFIG_H
#define MULTIFIXCONFIG_H

typedef struct _MultiFixConfig
{
	int bSwapConfirmButtons;
	int bInstaWinCheat;
	int CheatOpponentLP;
	int CheatPlayerLP;
	int bMatrixFontInDeckEdit;
}MultiFixConfig;

// accessors
MultiFixConfig* mfconfig_GetConfig();
MultiFixConfig* mfconfig_SetConfig(MultiFixConfig* inConfig);
int mfconfig_GetSwapConfirmButtons();
int mfconfig_SetSwapConfirmButtons(int val);
int mfconfig_GetInstaWinCheat();
int mfconfig_SetInstaWinCheat(int val);
int mfconfig_GetCheatOpponentLP();
int mfconfig_SetCheatOpponentLP(int val);
int mfconfig_GetCheatPlayerLP();
int mfconfig_SetCheatPlayerLP(int val);
int mfconfig_GetMatrixFontInDeckEdit();
int mfconfig_SetMatrixFontInDeckEdit(int val);

void mfconfig_Init();

#endif