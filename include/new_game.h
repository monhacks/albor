#ifndef GUARD_NEW_GAME_H
#define GUARD_NEW_GAME_H

extern bool8 gDiferentePartidaGuardada;

void SetTrainerId(u32 trainerId, u8 *dst);
void NewGameInitData(void);
void ResetMenuAndMonGlobals(void);
void SetDefaultOptions(void);

#endif // GUARD_NEW_GAME_H
