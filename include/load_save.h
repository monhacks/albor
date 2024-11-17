#ifndef GUARD_LOAD_SAVE_H
#define GUARD_LOAD_SAVE_H

#include "pokemon_storage_system.h"

extern struct SaveBlock1 gSaveblock1;
extern struct SaveBlock2 gSaveblock2;
extern struct PokemonStorage gPokemonStorage;
extern bool32 gFlashMemoryPresent;
extern struct SaveBlock1 *gSaveBlock1Ptr;
extern struct SaveBlock2 *gSaveBlock2Ptr;
extern struct PokemonStorage *gPokemonStoragePtr;

void CheckForFlashMemory(void);
void SetSaveBlocksPointers(void);
void MoveSaveBlocks_ResetHeap(void);
u32 UseContinueGameWarp(void);
void ClearContinueGameWarpStatus(void);
void SetContinueGameWarpStatus(void);
void SetContinueGameWarpStatusToDynamicWarp(void);
void ClearContinueGameWarpStatus2(void);
void SavePlayerParty(void);
void LoadPlayerParty(void);
void SaveObjectEvents(void);
void LoadObjectEvents(void);
void CopyPartyAndObjectsToSave(void);
void CopyPartyAndObjectsFromSave(void);
void LoadPlayerBag(void);
void SavePlayerBag(void);

#endif // GUARD_LOAD_SAVE_H
