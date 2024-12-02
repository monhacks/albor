#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_tower.h"
#include "battle_setup.h"
#include "event_data.h"
#include "event_scripts.h"
#include "fieldmap.h"
#include "field_message_box.h"
#include "international_string_util.h"
#include "item.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pokemon.h"
#include "script.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "util.h"
#include "constants/battle_ai.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/trainer_types.h"

#define HILL_MAX_TIME 215999 // 60 * 60 * 60 - 1

struct FloorTrainers
{
    u8 name[HILL_TRAINERS_PER_FLOOR][TRAINER_NAME_LENGTH + 1];
    u8 facilityClass[HILL_TRAINERS_PER_FLOOR];
};

static EWRAM_DATA struct {
    u8 floorId;
    struct TrainerHillChallenge challenge;
} *sHillData = NULL;

static EWRAM_DATA struct FloorTrainers *sFloorTrainers = NULL;

// This file's functions.
static void TrainerHillStartChallenge(void);
static void GetOwnerState(void);
static void GiveChallengePrize(void);
static void CheckFinalTime(void);
static void TrainerHillResumeTimer(void);
static void TrainerHillSetPlayerLost(void);
static void TrainerHillGetChallengeStatus(void);
static void BufferChallengeTime(void);
static void GetAllFloorsUsed(void);
static void IsTrainerHillChallengeActive(void);
static void ShowTrainerHillPostBattleText(void);
static void SetAllTrainerFlags(void);
static void GetGameSaved(void);
static void SetGameSaved(void);
static void ClearGameSaved(void);
static void GetChallengeWon(void);
static void TrainerHillSetMode(void);
static void SetUpDataStruct(void);
static void FreeDataStruct(void);
static void TrainerHillDummy(void);

// const data
#include "data/battle_frontier/trainer_hill.h"

struct
{
    u8 trainerClass;
    u8 musicId;
} static const sTrainerClassesAndMusic[] =
{
    {TRAINER_CLASS_TEAM_AQUA, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AQUA_ADMIN, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AQUA_LEADER, TRAINER_ENCOUNTER_MUSIC_AQUA},
    {TRAINER_CLASS_AROMA_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_BATTLE_GIRL, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SWIMMER_F, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_POKEFAN, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_DRAGON_TAMER, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_COOLTRAINER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_GUITARIST, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SAILOR, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TWINS, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_INTERVIEWER, TRAINER_ENCOUNTER_MUSIC_INTERVIEWER},
    {TRAINER_CLASS_RUIN_MANIAC, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_GENTLEMAN, TRAINER_ENCOUNTER_MUSIC_RICH},
    {TRAINER_CLASS_SWIMMER_M, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_POKEMANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_BLACK_BELT, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_OLD_COUPLE, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_BUG_MANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_CAMPER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_KINDLER, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_TEAM_MAGMA, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_MAGMA_ADMIN, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_MAGMA_LEADER, TRAINER_ENCOUNTER_MUSIC_MAGMA},
    {TRAINER_CLASS_LASS, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_BUG_CATCHER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_NINJA_BOY, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_RICH_BOY, TRAINER_ENCOUNTER_MUSIC_RICH},
    {TRAINER_CLASS_HEX_MANIAC, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_BEAUTY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_PARASOL_LADY, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_PICNICKER, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_PKMN_BREEDER, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_COLLECTOR, TRAINER_ENCOUNTER_MUSIC_SUSPICIOUS},
    {TRAINER_CLASS_PKMN_RANGER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_RIVAL, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_YOUNG_COUPLE, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_PSYCHIC, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_SR_AND_JR, TRAINER_ENCOUNTER_MUSIC_TWINS},
    {TRAINER_CLASS_ELITE_FOUR, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_YOUNGSTER, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_EXPERT, TRAINER_ENCOUNTER_MUSIC_INTENSE},
    {TRAINER_CLASS_TRIATHLETE, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_BIRD_KEEPER, TRAINER_ENCOUNTER_MUSIC_COOL},
    {TRAINER_CLASS_FISHERMAN, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_CHAMPION, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TUBER_M, TRAINER_ENCOUNTER_MUSIC_MALE},
    {TRAINER_CLASS_TUBER_F, TRAINER_ENCOUNTER_MUSIC_GIRL},
    {TRAINER_CLASS_SIS_AND_BRO, TRAINER_ENCOUNTER_MUSIC_SWIMMER},
    {TRAINER_CLASS_HIKER, TRAINER_ENCOUNTER_MUSIC_HIKER},
    {TRAINER_CLASS_LEADER, TRAINER_ENCOUNTER_MUSIC_FEMALE},
    {TRAINER_CLASS_SCHOOL_KID, TRAINER_ENCOUNTER_MUSIC_MALE},
};

static const u16 sPrizeListRareCandy1[]  = {ITEM_RARE_CANDY,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListLuxuryBall1[] = {ITEM_LUXURY_BALL,      ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxRevive1[]  = {ITEM_MAX_REVIVE,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxEther1[]   = {ITEM_MAX_ETHER,        ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListElixir1[]     = {ITEM_ELIXIR,           ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListRoar[]        = {ITEM_TM_ROAR,          ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSludgeBomb[]  = {ITEM_TM_SLUDGE_BOMB,   ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListToxic[]       = {ITEM_TM_TOXIC,         ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSunnyDay[]    = {ITEM_TM_SUNNY_DAY,     ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListEarthQuake[]  = {ITEM_TM_EARTHQUAKE,    ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};

static const u16 sPrizeListRareCandy2[]  = {ITEM_RARE_CANDY,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListLuxuryBall2[] = {ITEM_LUXURY_BALL,      ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxRevive2[]  = {ITEM_MAX_REVIVE,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListMaxEther2[]   = {ITEM_MAX_ETHER,        ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListElixir2[]     = {ITEM_ELIXIR,           ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListBrickBreak[]  = {ITEM_TM_BRICK_BREAK,   ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListTorment[]     = {ITEM_TM_TORMENT,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListSkillSwap[]   = {ITEM_TM_SKILL_SWAP,    ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListGigaDrain[]   = {ITEM_TM_GIGA_DRAIN,    ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};
static const u16 sPrizeListAttract[]     = {ITEM_TM_ATTRACT,       ITEM_ETHER, ITEM_MAX_POTION, ITEM_REVIVE, ITEM_FLUFFY_TAIL, ITEM_GREAT_BALL};

static const u16 *const sPrizeLists1[NUM_TRAINER_HILL_PRIZE_LISTS] =
{
    sPrizeListRareCandy1,
    sPrizeListLuxuryBall1,
    sPrizeListMaxRevive1,
    sPrizeListMaxEther1,
    sPrizeListElixir1,
    sPrizeListRoar,
    sPrizeListSludgeBomb,
    sPrizeListToxic,
    sPrizeListSunnyDay,
    sPrizeListEarthQuake
};

static const u16 *const sPrizeLists2[NUM_TRAINER_HILL_PRIZE_LISTS] =
{
    sPrizeListRareCandy2,
    sPrizeListLuxuryBall2,
    sPrizeListMaxRevive2,
    sPrizeListMaxEther2,
    sPrizeListElixir2,
    sPrizeListBrickBreak,
    sPrizeListTorment,
    sPrizeListSkillSwap,
    sPrizeListGigaDrain,
    sPrizeListAttract
};

static const u16 *const *const sPrizeListSets[] =
{
    sPrizeLists1,
    sPrizeLists2
};

static const u8 sRecordWinColors[] = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_LIGHT_GRAY};

static const struct TrainerHillChallenge *const sChallengeData[NUM_TRAINER_HILL_MODES] =
{
    [HILL_MODE_NORMAL]  = &sChallenge_Normal,
    [HILL_MODE_VARIETY] = &sChallenge_Variety,
    [HILL_MODE_UNIQUE]  = &sChallenge_Unique,
    [HILL_MODE_EXPERT]  = &sChallenge_Expert,
};

// Unused.
static const u8 *const sFloorStrings[] =
{
    gText_TrainerHill1F,
    gText_TrainerHill2F,
    gText_TrainerHill3F,
    gText_TrainerHill4F,
};

static void (* const sHillFunctions[])(void) =
{
    [TRAINER_HILL_FUNC_START]                 = TrainerHillStartChallenge,
    [TRAINER_HILL_FUNC_GET_OWNER_STATE]       = GetOwnerState,
    [TRAINER_HILL_FUNC_GIVE_PRIZE]            = GiveChallengePrize,
    [TRAINER_HILL_FUNC_CHECK_FINAL_TIME]      = CheckFinalTime,
    [TRAINER_HILL_FUNC_RESUME_TIMER]          = TrainerHillResumeTimer,
    [TRAINER_HILL_FUNC_SET_LOST]              = TrainerHillSetPlayerLost,
    [TRAINER_HILL_FUNC_GET_CHALLENGE_STATUS]  = TrainerHillGetChallengeStatus,
    [TRAINER_HILL_FUNC_GET_CHALLENGE_TIME]    = BufferChallengeTime,
    [TRAINER_HILL_FUNC_GET_ALL_FLOORS_USED]   = GetAllFloorsUsed,
    [TRAINER_HILL_FUNC_IN_CHALLENGE]          = IsTrainerHillChallengeActive,
    [TRAINER_HILL_FUNC_POST_BATTLE_TEXT]      = ShowTrainerHillPostBattleText,
    [TRAINER_HILL_FUNC_SET_ALL_TRAINER_FLAGS] = SetAllTrainerFlags,
    [TRAINER_HILL_FUNC_GET_GAME_SAVED]        = GetGameSaved,
    [TRAINER_HILL_FUNC_SET_GAME_SAVED]        = SetGameSaved,
    [TRAINER_HILL_FUNC_CLEAR_GAME_SAVED]      = ClearGameSaved,
    [TRAINER_HILL_FUNC_GET_WON]               = GetChallengeWon,
    [TRAINER_HILL_FUNC_SET_MODE]              = TrainerHillSetMode,
};

static const u8 *const sModeStrings[NUM_TRAINER_HILL_MODES] =
{
    [HILL_MODE_NORMAL]  = gText_NormalTagMatch,
    [HILL_MODE_VARIETY] = gText_VarietyTagMatch,
    [HILL_MODE_UNIQUE]  = gText_UniqueTagMatch,
    [HILL_MODE_EXPERT]  = gText_ExpertTagMatch,
};

static const struct ObjectEventTemplate sTrainerObjectEventTemplate =
{
    .graphicsId = OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL,
    .elevation = 3,
    .movementType = MOVEMENT_TYPE_LOOK_AROUND,
    .movementRangeX = 1,
    .movementRangeY = 1,
    .trainerType = TRAINER_TYPE_NORMAL,
};

static const u8 sTrainerPartySlots[HILL_TRAINERS_PER_FLOOR][PARTY_SIZE / 2] =
{
    {0, 1, 2},
    {3, 4, 5}
};

void CallTrainerHillFunction(void)
{
    SetUpDataStruct();
    sHillFunctions[gSpecialVar_0x8004]();
    FreeDataStruct();
}

void ResetTrainerHillResults(void)
{

}

static u8 GetFloorId(void)
{
    return 0;
}

u8 GetTrainerHillOpponentClass(u16 trainerId)
{
    return 0;
}

void GetTrainerHillTrainerName(u8 *dst, u16 trainerId)
{
    s32 i;
    u8 id = trainerId - 1;

    for (i = 0; i < TRAINER_NAME_LENGTH + 1; i++)
        dst[i] = sFloorTrainers->name[id][i];
}

u8 GetTrainerHillTrainerFrontSpriteId(u16 trainerId)
{
    return 0;
}

static void SetUpDataStruct(void)
{

}

static void FreeDataStruct(void)
{
    TRY_FREE_AND_SET_NULL(sHillData);
}

void CopyTrainerHillTrainerText(u8 which, u16 trainerId)
{

}

static void TrainerHillStartChallenge(void)
{
    TrainerHillDummy();
}

static void GetOwnerState(void)
{

}

static void GiveChallengePrize(void)
{

}

// If bestTime > timer, the challenge was completed faster and its a new record
// Otherwise the owner says it was a slow time and to complete it faster next time
static void CheckFinalTime(void)
{

}

static void TrainerHillResumeTimer(void)
{

}

static void TrainerHillSetPlayerLost(void)
{

}

static void TrainerHillGetChallengeStatus(void)
{

}

static void BufferChallengeTime(void)
{

}

// Returns TRUE if all 4 floors are used
// Returns FALSE otherwise, and buffers the number of floors used
// The only time fewer than all 4 floors are used is for the JP-exclusive E-Reader and Default modes
static void GetAllFloorsUsed(void)
{
    SetUpDataStruct();
    if (sHillData->challenge.numFloors != NUM_TRAINER_HILL_FLOORS)
    {
        ConvertIntToDecimalStringN(gStringVar1, sHillData->challenge.numFloors, STR_CONV_MODE_LEFT_ALIGN, 1);
        gSpecialVar_Result = FALSE;
    }
    else
    {
        gSpecialVar_Result = TRUE;
    }

    FreeDataStruct();
}

bool8 InTrainerHillChallenge(void)
{
    return FALSE;
}

static void IsTrainerHillChallengeActive(void)
{
    if (!InTrainerHillChallenge())
        gSpecialVar_Result = FALSE;
    else
        gSpecialVar_Result = TRUE;
}

static void TrainerHillDummy(void)
{

}

void PrintOnTrainerHillRecordsWindow(void)
{

}

void LoadTrainerHillObjectEventTemplates(void)
{

}

bool32 LoadTrainerHillFloorObjectEventScripts(void)
{
    SetUpDataStruct();
    // Something may have been dummied here
    FreeDataStruct();
    return TRUE;
}

void GenerateTrainerHillFloorLayout(u16 *mapArg)
{

}

bool32 InTrainerHill(void)
{
    return 0;
}

u8 GetCurrentTrainerHillMapId(void)
{
    return 0;
}

const struct WarpEvent* SetWarpDestinationTrainerHill4F(void)
{
    return 0;
}

u16 LocalIdToHillTrainerId(u8 localId)
{
    return gSaveBlockPtr->frontier.trainerIds[localId - 1];
}

bool8 GetHillTrainerFlag(u8 objectEventId)
{
    u32 trainerIndexStart = GetFloorId() * HILL_TRAINERS_PER_FLOOR;
    u8 bitId = gObjectEvents[objectEventId].localId - 1 + trainerIndexStart;

    return gSaveBlockPtr->frontier.trainerFlags & (1u << bitId);
}

void SetHillTrainerFlag(void)
{
    u8 i;
    u8 trainerIndexStart = GetFloorId() * HILL_TRAINERS_PER_FLOOR;

    for (i = 0; i < HILL_TRAINERS_PER_FLOOR; i++)
    {
        if (gSaveBlockPtr->frontier.trainerIds[i] == gTrainerBattleOpponent_A)
        {
            gSaveBlockPtr->frontier.trainerFlags |= 1u << (trainerIndexStart + i);
            break;
        }
    }

    if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
    {
        for (i = 0; i < HILL_TRAINERS_PER_FLOOR; i++)
        {
            if (gSaveBlockPtr->frontier.trainerIds[i] == gTrainerBattleOpponent_B)
            {
                gSaveBlockPtr->frontier.trainerFlags |= 1u << (trainerIndexStart + i);
                break;
            }
        }
    }
}

const u8 *GetTrainerHillTrainerScript(void)
{
    return TrainerHill_EventScript_TrainerBattle;
}

static void ShowTrainerHillPostBattleText(void)
{
    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_AFTER, gSpecialVar_LastTalked);
    ShowFieldMessageFromBuffer();
}

static void CreateNPCTrainerHillParty(u16 trainerId, u8 firstMonId)
{

}

void FillHillTrainerParty(void)
{
    ZeroEnemyPartyMons();
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_A, 0);
}

void FillHillTrainersParties(void)
{
    ZeroEnemyPartyMons();
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_A, 0);
    CreateNPCTrainerHillParty(gTrainerBattleOpponent_B, PARTY_SIZE / 2);
}

u8 GetTrainerEncounterMusicIdInTrainerHill(u16 trainerId)
{
    return 0;
}

u8 GetNumFloorsInTrainerHillChallenge(void)
{
    u8 floors;

    SetUpDataStruct();
    floors = sHillData->challenge.numFloors;
    FreeDataStruct();

    return floors;
}

static void SetAllTrainerFlags(void)
{
    gSaveBlockPtr->frontier.trainerFlags = 0xFF;
}

static void GetGameSaved(void)
{
    gSpecialVar_Result = gSaveBlockPtr->frontier.savedGame;
}

static void SetGameSaved(void)
{
    gSaveBlockPtr->frontier.savedGame = TRUE;
}

static void ClearGameSaved(void)
{
    gSaveBlockPtr->frontier.savedGame = FALSE;
}

static void GetChallengeWon(void)
{

}

static void TrainerHillSetMode(void)
{

}
