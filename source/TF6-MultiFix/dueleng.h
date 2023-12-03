//
// Yu-Gi-Oh! Tag Force - Duel Engine Patches
// by xan1242 / Tenjoin
//

#ifndef DUELENG_H
#define DUELENG_H

void dueleng_Patch(uintptr_t base_addr, uintptr_t base_size);
void dueleng_chtSetOpponentLP(int16_t val);
void dueleng_chtSetPlayerLP(int16_t val);

#endif