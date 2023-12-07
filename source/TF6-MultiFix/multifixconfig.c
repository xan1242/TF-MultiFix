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
	0,        // bInstaWinCheat
	0,		  // CheatOpponentLP
	8000,	  // CheatPlayerLP
	0,		  // bMatrixFont
	1,		  // bSeePartnerCards
	0		  // CheatControlPartner
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

int mfconfig_SetSwapConfirmButtons(int val)
{
	mfconfig.bSwapConfirmButtons = (val == 1);
	return val;
}

int mfconfig_GetInstaWinCheat()
{
	return mfconfig.bInstaWinCheat;
}

int mfconfig_SetInstaWinCheat(int val)
{
	mfconfig.bInstaWinCheat = (val == 1);
	return val;
}

int mfconfig_GetCheatOpponentLP()
{
	return mfconfig.CheatOpponentLP;
}

int mfconfig_SetCheatOpponentLP(int val)
{
	mfconfig.CheatOpponentLP = val;
	return val;
}

int mfconfig_GetCheatPlayerLP()
{
	return mfconfig.CheatPlayerLP;
}

int mfconfig_SetCheatPlayerLP(int val)
{
	mfconfig.CheatPlayerLP = val;
	return val;
}

int mfconfig_GetMatrixFont()
{
	return mfconfig.bMatrixFont;
}

int mfconfig_SetMatrixFont(int val)
{
	mfconfig.bMatrixFont = (val == 1);
	return val;
}

int mfconfig_GetSeePartnerCards()
{
	return mfconfig.bSeePartnerCards;
}

int mfconfig_SetSeePartnerCards(int val)
{
	mfconfig.bSeePartnerCards = val;
	return mfconfig.bSeePartnerCards;
}

int mfconfig_GetCheatControlPartner()
{
	return mfconfig.CheatControlPartner;
}

int mfconfig_SetCheatControlPartner(int val)
{
	mfconfig.CheatControlPartner = val;
	return mfconfig.CheatControlPartner;
}

void mfconfig_Init()
{
	// TODO: add config reading here

	// TEST
	mfconfig_SetInstaWinCheat(1);
	mfconfig_SetCheatControlPartner(1);

	//mfconfig_SetSwapConfirmButtons(0);
}
