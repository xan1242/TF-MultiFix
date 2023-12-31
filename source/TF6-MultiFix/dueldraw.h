//
// Yu-Gi-Oh! Tag Force - Duel Renderer Patches
// by xan1242 / Tenjoin
//

#ifndef DUELDRAW_H
#define DUELDRAW_H

#define PLAYER_LP_VAL_ADDR 0xABE6C
#define OPPONENT_LP_VAL_ADDR 0xABE70

void dueldraw_Patch(uintptr_t base_addr, uintptr_t base_size);
void dueldraw_SetPlayerLP(uint16_t val);
void dueldraw_SetOpponentLP(uint16_t val);

#endif