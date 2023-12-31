//
// Yu-Gi-Oh! Tag Force - Duel Engine Patches
// by xan1242 / Tenjoin
//

#ifndef DUELENG_H
#define DUELENG_H

typedef enum _duelPhase
{
	DUEL_PHASE_UNK = -1,
	DUEL_PHASE_FIRST = 0xA,
	DUEL_PHASE_DP,
	DUEL_PHASE_SP,
	DUEL_PHASE_MP1,
	DUEL_PHASE_BP,
	DUEL_PHASE_MP2,
	DUEL_PHASE_EP,
	DUEL_PHASE_OPP_DP = 0x800A,
	DUEL_PHASE_OPP_SP,
	DUEL_PHASE_OPP_MP1,
	DUEL_PHASE_OPP_BP,
	DUEL_PHASE_OPP_MP2,
	DUEL_PHASE_OPP_EP,
	DUEL_PHASE_COUNT = 6
}duelPhase;

void dueleng_Patch(uintptr_t base_addr, uintptr_t base_size);
void dueleng_chtSetOpponentLP(int16_t val);
void dueleng_chtSetPlayerLP(int16_t val);
void dueleng_chtSetPlayerControl(int PlayerNum, int val);
void dueleng_chtSetPhase(duelPhase phase);
void dueleng_chtDrawCard();
void dueleng_chtOppDrawCard();

#endif