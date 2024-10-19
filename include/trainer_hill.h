#ifndef GUARD_TRAINER_HILL_H
#define GUARD_TRAINER_HILL_H

#define DUMMY_HILL_MON { .nickname = __("$$$$$$$$$$$") }

struct TrainerHillFloorMap
{
    u8 metatileData[HILL_FLOOR_WIDTH * HILL_FLOOR_HEIGHT_MAIN]; // Add NUM_METATILES_IN_PRIMARY to the values in this array to get metatile ids.
    u16 collisionData[HILL_FLOOR_WIDTH]; // One bit for each tile in column-major order, so every array entry is one row. 1 = impassable, 0 = passable
    u8 trainerCoords[HILL_TRAINERS_PER_FLOOR]; // Starting at (0,6). Format is 0bYYYYXXXX.
    u8 trainerDirections; // DIR_* - 1, 4 bits per trainer
    u8 trainerRanges; // 4 bits per trainer
};

struct TrainerHillChallenge
{
    u8 numTrainers;
    u8 numFloors;
    u32 checksum; // A byte array sum of the floor data
};

extern u32 *gTrainerHillVBlankCounter;

void CallTrainerHillFunction(void);
u8 GetTrainerHillOpponentClass(u16 trainerId);
void GetTrainerHillTrainerName(u8 *dst, u16 trainerId);
u8 GetTrainerHillTrainerFrontSpriteId(u16 trainerId);
void InitTrainerHillBattleStruct(void);
void FreeTrainerHillBattleStruct(void);
void CopyTrainerHillTrainerText(u8 which, u16 trainerId);
bool8 InTrainerHillChallenge(void);
void PrintOnTrainerHillRecordsWindow(void);
void LoadTrainerHillObjectEventTemplates(void);
bool32 LoadTrainerHillFloorObjectEventScripts(void);
void GenerateTrainerHillFloorLayout(u16 *mapArg);
bool32 InTrainerHill(void);
u8 GetCurrentTrainerHillMapId(void);
const struct WarpEvent* SetWarpDestinationTrainerHill4F(void);
const struct WarpEvent* SetWarpDestinationTrainerHillFinalFloor(u8 warpEventId);
u16 LocalIdToHillTrainerId(u8 localId);
bool8 GetHillTrainerFlag(u8 objectEventId);
void SetHillTrainerFlag(void);
const u8 *GetTrainerHillTrainerScript(void);
void FillHillTrainerParty(void);
void FillHillTrainersParties(void);
u8 GetTrainerEncounterMusicIdInTrainerHill(u16 trainerId);
u8 GetNumFloorsInTrainerHillChallenge(void);
bool32 OnTrainerHillEReaderChallengeFloor(void);

#endif // GUARD_TRAINER_HILL_H
