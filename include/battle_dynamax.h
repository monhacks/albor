#ifndef GUARD_BATTLE_DYNAMAX_H
#define GUARD_BATTLE_DYNAMAX_H

#define DYNAMAX_TURNS_COUNT	3

bool32 CanDynamax(u32 battler);
void ApplyDynamaxHPMultiplier(u32 battler, struct Pokemon* mon);
void ActivateDynamax(u32 battler);
void UndoDynamax(u32 battler);
bool32 IsMoveBlockedByMaxGuard(u32 move);
bool32 IsMoveBlockedByDynamax(u32 move);

void ChooseDamageNonTypesString(u8 type);

void BS_SetSteelsurge(void);
void BS_HealOneSixth(void);
void BS_TryRecycleBerry(void);
void BS_JumpIfDynamaxed(void);

#endif
