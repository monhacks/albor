#include "global.h"
#include "battle_tower.h"
#include "apprentice.h"
#include "event_data.h"
#include "battle_setup.h"
#include "overworld.h"
#include "random.h"
#include "text.h"
#include "main.h"
#include "international_string_util.h"
#include "battle.h"
#include "frontier_util.h"
#include "strings.h"
#include "recorded_battle.h"
#include "easy_chat.h"
#include "gym_leader_rematch.h"
#include "battle_transition.h"
#include "trainer_see.h"
#include "new_game.h"
#include "string_util.h"
#include "data.h"
#include "link.h"
#include "field_message_box.h"
#include "battle_factory.h"
#include "constants/abilities.h"
#include "constants/apprentice.h"
#include "constants/battle_dome.h"
#include "constants/battle_frontier.h"
#include "constants/battle_frontier_mons.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_tent.h"
#include "constants/battle_tent_mons.h"
#include "constants/battle_tent_trainers.h"
#include "constants/battle_tower.h"
#include "constants/flags.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/trainers.h"
#include "constants/event_objects.h"
#include "constants/moves.h"

// EWRAM vars.
EWRAM_DATA const struct BattleFrontierTrainer *gFacilityTrainers = NULL;
EWRAM_DATA const struct TrainerMon *gFacilityTrainerMons = NULL;

// IWRAM common
u16 gFrontierTempParty[MAX_FRONTIER_PARTY_SIZE];

// This file's functions.
static void InitTowerChallenge(void);
static void GetTowerData(void);
static void SetTowerData(void);
static void SetNextFacilityOpponent(void);
static void SetTowerBattleWon(void);
static void AwardBattleTowerRibbons(void);
static void SaveTowerChallenge(void);
static void GetOpponentIntroSpeech(void);
static void LoadMultiPartnerCandidatesData(void);
static void ShowPartnerCandidateMessage(void);
static void LoadLinkMultiOpponentsData(void);
static void TowerTryCloseLink(void);
static void SetMultiPartnerGfx(void);
static void SetTowerInterviewData(void);
static void ValidateApprenticesChecksums(void);
static void SetNextBattleTentOpponent(void);
static void CopyEReaderTrainerFarewellMessage(void);
static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount);
static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount);
static void FillFactoryFrontierTrainerParty(u16 trainerId, u8 firstMonId);
static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId);
static u8 GetFrontierTrainerFixedIvs(u16 trainerId);
static void FillPartnerParty(u16 trainerId);
static u8 SetTentPtrsGetLevel(void);

#include "data/battle_frontier/battle_frontier_trainer_mons.h"
#include "data/battle_frontier/battle_frontier_mons.h"

const u16 gTowerMaleTrainerGfxIds[30] =
{
    OBJ_EVENT_GFX_HIKER,
    OBJ_EVENT_GFX_TUBER_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_RICH_BOY,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_BLACK_BELT,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_PSYCHIC_M,
    OBJ_EVENT_GFX_GENTLEMAN,
    OBJ_EVENT_GFX_SCHOOL_KID_M,
    OBJ_EVENT_GFX_POKEFAN_M,
    OBJ_EVENT_GFX_EXPERT_M,
    OBJ_EVENT_GFX_YOUNGSTER,
    OBJ_EVENT_GFX_FISHERMAN,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M,
    OBJ_EVENT_GFX_MAN_3,
    OBJ_EVENT_GFX_MAN_5,
    OBJ_EVENT_GFX_NINJA_BOY,
    OBJ_EVENT_GFX_SAILOR,
    OBJ_EVENT_GFX_MANIAC,
    OBJ_EVENT_GFX_MAN_4,
    OBJ_EVENT_GFX_CAMPER,
    OBJ_EVENT_GFX_BUG_CATCHER,
    OBJ_EVENT_GFX_HIKER
};

const u16 gTowerFemaleTrainerGfxIds[20] =
{
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_TUBER_F,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_HEX_MANIAC,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_BEAUTY,
    OBJ_EVENT_GFX_LASS,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_POKEFAN_F,
    OBJ_EVENT_GFX_EXPERT_F,
    OBJ_EVENT_GFX_CYCLING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_GIRL_3,
    OBJ_EVENT_GFX_WOMAN_5,
    OBJ_EVENT_GFX_RUNNING_TRIATHLETE_F,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_PICNICKER,
    OBJ_EVENT_GFX_LASS
};

#define PARTNER_TEXTS(name)                                             \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Intro,      \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Mon1,       \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Mon2Ask,    \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Accept,     \
    BattleFrontier_BattleTowerMultiPartnerRoom_Text_##name##Reject

static const u8 *const sPartnerApprenticeTexts1[] =
{
    PARTNER_TEXTS(Apprentice1)
};

static const u8 *const sPartnerApprenticeTexts2[] =
{
    PARTNER_TEXTS(Apprentice2)
};

static const u8 *const sPartnerApprenticeTexts3[] =
{
    PARTNER_TEXTS(Apprentice3)
};

static const u8 *const sPartnerApprenticeTexts4[] =
{
    PARTNER_TEXTS(Apprentice4)
};

static const u8 *const sPartnerApprenticeTexts5[] =
{
    PARTNER_TEXTS(Apprentice5)
};

static const u8 *const sPartnerApprenticeTexts6[] =
{
     PARTNER_TEXTS(Apprentice6)
};

static const u8 *const sPartnerApprenticeTexts7[] =
{
     PARTNER_TEXTS(Apprentice7)
};

static const u8 *const sPartnerApprenticeTexts8[] =
{
     PARTNER_TEXTS(Apprentice8)
};

static const u8 *const sPartnerApprenticeTexts9[] =
{
     PARTNER_TEXTS(Apprentice9)
};

static const u8 *const sPartnerApprenticeTexts10[] =
{
     PARTNER_TEXTS(Apprentice10)
};

static const u8 *const sPartnerApprenticeTexts11[] =
{
     PARTNER_TEXTS(Apprentice11)
};

static const u8 *const sPartnerApprenticeTexts12[] =
{
     PARTNER_TEXTS(Apprentice12)
};

static const u8 *const sPartnerApprenticeTexts13[] =
{
     PARTNER_TEXTS(Apprentice13)
};

static const u8 *const sPartnerApprenticeTexts14[] =
{
     PARTNER_TEXTS(Apprentice14)
};

static const u8 *const sPartnerApprenticeTexts15[] =
{
     PARTNER_TEXTS(Apprentice15)
};

static const u8 *const sPartnerApprenticeTexts16[] =
{
     PARTNER_TEXTS(Apprentice16)
};

static const u8 *const sPartnerTextsLass[] =
{
    PARTNER_TEXTS(Lass)
};

static const u8 *const sPartnerTextsYoungster[] =
{
    PARTNER_TEXTS(Youngster)
};

static const u8 *const sPartnerTextsHiker[] =
{
    PARTNER_TEXTS(Hiker)
};

static const u8 *const sPartnerTextsBeauty[] =
{
    PARTNER_TEXTS(Beauty)
};

static const u8 *const sPartnerTextsFisherman[] =
{
    PARTNER_TEXTS(Fisherman)
};

static const u8 *const sPartnerTextsLady[] =
{
    PARTNER_TEXTS(Lady)
};

static const u8 *const sPartnerTextsCyclingTriathleteF[] =
{
    PARTNER_TEXTS(CyclingTriathleteF)
};

static const u8 *const sPartnerTextsBugCatcher[] =
{
    PARTNER_TEXTS(BugCatcher)
};

static const u8 *const sPartnerTextsSchoolKidM[] =
{
    PARTNER_TEXTS(SchoolKidM)
};

static const u8 *const sPartnerTextsRichBoy[] =
{
    PARTNER_TEXTS(RichBoy)
};

static const u8 *const sPartnerTextsBlackBelt[] =
{
    PARTNER_TEXTS(BlackBelt)
};

static const u8 *const sPartnerTextsTuberF[] =
{
    PARTNER_TEXTS(TuberF)
};

static const u8 *const sPartnerTextsHexManiac[] =
{
    PARTNER_TEXTS(HexManiac)
};

static const u8 *const sPartnerTextsPkmnBreederM[] =
{
    PARTNER_TEXTS(PkmnBreederM)
};

static const u8 *const sPartnerTextsRunningTriathleteF[] =
{
    PARTNER_TEXTS(RunningTriathleteF)
};

static const u8 *const sPartnerTextsRunningTriathleteM[] =
{
    PARTNER_TEXTS(RunningTriathleteM)
};

static const u8 *const sPartnerTextsBattleGirl[] =
{
    PARTNER_TEXTS(BattleGirl)
};

static const u8 *const sPartnerTextsCyclingTriathleteM[] =
{
    PARTNER_TEXTS(CyclingTriathleteM)
};

static const u8 *const sPartnerTextsTuberM[] =
{
    PARTNER_TEXTS(TuberM)
};

static const u8 *const sPartnerTextsGuitarist[] =
{
    PARTNER_TEXTS(Guitarist)
};

static const u8 *const sPartnerTextsGentleman[] =
{
    PARTNER_TEXTS(Gentleman)
};

static const u8 *const sPartnerTextsPokefanM[] =
{
    PARTNER_TEXTS(PokefanM)
};

static const u8 *const sPartnerTextsExpertM[] =
{
    PARTNER_TEXTS(ExpertM)
};

static const u8 *const sPartnerTextsExpertF[] =
{
    PARTNER_TEXTS(ExpertF)
};

static const u8 *const sPartnerTextsDragonTamer[] =
{
    PARTNER_TEXTS(DragonTamer)
};

static const u8 *const sPartnerTextsBirdKeeper[] =
{
    PARTNER_TEXTS(BirdKeeper)
};

static const u8 *const sPartnerTextsNinjaBoy[] =
{
    PARTNER_TEXTS(NinjaBoy)
};

static const u8 *const sPartnerTextsParasolLady[] =
{
    PARTNER_TEXTS(ParasolLady)
};

static const u8 *const sPartnerTextsBugManiac[] =
{
    PARTNER_TEXTS(BugManiac)
};

static const u8 *const sPartnerTextsSailor[] =
{
    PARTNER_TEXTS(Sailor)
};

static const u8 *const sPartnerTextsCollector[] =
{
    PARTNER_TEXTS(Collector)
};

static const u8 *const sPartnerTextsPkmnRangerM[] =
{
    PARTNER_TEXTS(PkmnRangerM)
};

static const u8 *const sPartnerTextsPkmnRangerF[] =
{
    PARTNER_TEXTS(PkmnRangerF)
};

static const u8 *const sPartnerTextsAromaLady[] =
{
    PARTNER_TEXTS(AromaLady)
};

static const u8 *const sPartnerTextsRuinManiac[] =
{
    PARTNER_TEXTS(RuinManiac)
};

static const u8 *const sPartnerTextsCoolTrainerM[] =
{
    PARTNER_TEXTS(CoolTrainerM)
};

static const u8 *const sPartnerTextsCoolTrainerF[] =
{
    PARTNER_TEXTS(CoolTrainerF)
};

static const u8 *const sPartnerTextsPokemaniac[] =
{
    PARTNER_TEXTS(Pokemaniac)
};

static const u8 *const sPartnerTextsKindler[] =
{
    PARTNER_TEXTS(Kindler)
};

static const u8 *const sPartnerTextsCamper[] =
{
    PARTNER_TEXTS(Camper)
};

static const u8 *const sPartnerTextsPicnicker[] =
{
    PARTNER_TEXTS(Picnicker)
};

static const u8 *const sPartnerTextsPsychicM[] =
{
    PARTNER_TEXTS(PsychicM)
};

static const u8 *const sPartnerTextsPsychicF[] =
{
    PARTNER_TEXTS(PsychicF)
};

static const u8 *const sPartnerTextsSchoolKidF[] =
{
    PARTNER_TEXTS(SchoolKidF)
};

static const u8 *const sPartnerTextsPkmnBreederF[] =
{
    PARTNER_TEXTS(PkmnBreederF)
};

static const u8 *const sPartnerTextsPokefanF[] =
{
    PARTNER_TEXTS(PokefanF)
};

static const u8 *const sPartnerTextsSwimmerF[] =
{
    PARTNER_TEXTS(SwimmerF)
};

static const u8 *const sPartnerTextsSwimmingTriathleteM[] =
{
    PARTNER_TEXTS(SwimmingTriathleteM)
};

static const u8 *const sPartnerTextsSwimmingTriathleteF[] =
{
    PARTNER_TEXTS(SwimmingTriathleteF)
};

static const u8 *const sPartnerTextsSwimmerM[] =
{
    PARTNER_TEXTS(SwimmerM)
};

static const u8 *const *const sPartnerApprenticeTextTables[NUM_APPRENTICES] =
{
    sPartnerApprenticeTexts1,
    sPartnerApprenticeTexts2,
    sPartnerApprenticeTexts3,
    sPartnerApprenticeTexts4,
    sPartnerApprenticeTexts5,
    sPartnerApprenticeTexts6,
    sPartnerApprenticeTexts7,
    sPartnerApprenticeTexts8,
    sPartnerApprenticeTexts9,
    sPartnerApprenticeTexts10,
    sPartnerApprenticeTexts11,
    sPartnerApprenticeTexts12,
    sPartnerApprenticeTexts13,
    sPartnerApprenticeTexts14,
    sPartnerApprenticeTexts15,
    sPartnerApprenticeTexts16
};

#include "data/battle_frontier/battle_tent.h"

const struct Trainer gBattlePartners[] =
{
#include "data/battle_partners.h"
};

static void (* const sBattleTowerFuncs[])(void) =
{
    [BATTLE_TOWER_FUNC_INIT]                = InitTowerChallenge,
    [BATTLE_TOWER_FUNC_GET_DATA]            = GetTowerData,
    [BATTLE_TOWER_FUNC_SET_DATA]            = SetTowerData,
    [BATTLE_TOWER_FUNC_SET_OPPONENT]        = SetNextFacilityOpponent,
    [BATTLE_TOWER_FUNC_SET_BATTLE_WON]      = SetTowerBattleWon,
    [BATTLE_TOWER_FUNC_GIVE_RIBBONS]        = AwardBattleTowerRibbons,
    [BATTLE_TOWER_FUNC_SAVE]                = SaveTowerChallenge,
    [BATTLE_TOWER_FUNC_GET_OPPONENT_INTRO]  = GetOpponentIntroSpeech,
    [BATTLE_TOWER_FUNC_LOAD_PARTNERS]       = LoadMultiPartnerCandidatesData,
    [BATTLE_TOWER_FUNC_PARTNER_MSG]         = ShowPartnerCandidateMessage,
    [BATTLE_TOWER_FUNC_LOAD_LINK_OPPONENTS] = LoadLinkMultiOpponentsData,
    [BATTLE_TOWER_FUNC_TRY_CLOSE_LINK]      = TowerTryCloseLink,
    [BATTLE_TOWER_FUNC_SET_PARTNER_GFX]     = SetMultiPartnerGfx,
    [BATTLE_TOWER_FUNC_SET_INTERVIEW_DATA]  = SetTowerInterviewData,
};

static const u32 sWinStreakFlags[][2] =
{
    {STREAK_TOWER_SINGLES_50,     STREAK_TOWER_SINGLES_OPEN},
    {STREAK_TOWER_DOUBLES_50,     STREAK_TOWER_DOUBLES_OPEN},
    {STREAK_TOWER_MULTIS_50,      STREAK_TOWER_MULTIS_OPEN},
    {STREAK_TOWER_LINK_MULTIS_50, STREAK_TOWER_LINK_MULTIS_OPEN},
};

static const u32 sWinStreakMasks[][2] =
{
    {~(STREAK_TOWER_SINGLES_50),     ~(STREAK_TOWER_SINGLES_OPEN)},
    {~(STREAK_TOWER_DOUBLES_50),     ~(STREAK_TOWER_DOUBLES_OPEN)},
    {~(STREAK_TOWER_MULTIS_50),      ~(STREAK_TOWER_MULTIS_OPEN)},
    {~(STREAK_TOWER_LINK_MULTIS_50), ~(STREAK_TOWER_LINK_MULTIS_OPEN)},
};

// The challenge number at which an Apprentice can appear, depending on how many of their questions were answered
static const u8 sApprenticeChallengeThreshold[MAX_APPRENTICE_QUESTIONS] =
{
    1, 2, 3, 4, 5, 8, 9, 10, 11, 12
};

// Unclear why this was duplicated
static const u8 sBattleTowerPartySizes2[] =
{
    [FRONTIER_MODE_SINGLES]     = FRONTIER_PARTY_SIZE,
    [FRONTIER_MODE_DOUBLES]     = FRONTIER_DOUBLES_PARTY_SIZE,
    [FRONTIER_MODE_MULTIS]      = FRONTIER_MULTI_PARTY_SIZE,
    [FRONTIER_MODE_LINK_MULTIS] = FRONTIER_MULTI_PARTY_SIZE,
};

// Trainer ID ranges for possible frontier trainers to encounter on particular challenges
// Trainers are scaled by difficulty, so higher trainer IDs have better teams
static const u16 sFrontierTrainerIdRanges[][2] =
{
    {FRONTIER_TRAINER_BRADY,   FRONTIER_TRAINER_JILL},   //   0 -  99
    {FRONTIER_TRAINER_TREVIN,  FRONTIER_TRAINER_CHLOE},  //  80 - 119
    {FRONTIER_TRAINER_ERIK,    FRONTIER_TRAINER_SOFIA},  // 100 - 139
    {FRONTIER_TRAINER_NORTON,  FRONTIER_TRAINER_JAZLYN}, // 120 - 159
    {FRONTIER_TRAINER_BRADEN,  FRONTIER_TRAINER_ALISON}, // 140 - 179
    {FRONTIER_TRAINER_ZACHERY, FRONTIER_TRAINER_LAMAR},  // 160 - 199
    {FRONTIER_TRAINER_HANK,    FRONTIER_TRAINER_TESS},   // 180 - 219
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_GRETEL}, // 200 - 299
};

static const u16 sFrontierTrainerIdRangesHard[][2] =
{
    {FRONTIER_TRAINER_ERIK,    FRONTIER_TRAINER_CHLOE},  // 100 - 119
    {FRONTIER_TRAINER_NORTON,  FRONTIER_TRAINER_SOFIA},  // 120 - 139
    {FRONTIER_TRAINER_BRADEN,  FRONTIER_TRAINER_JAZLYN}, // 140 - 159
    {FRONTIER_TRAINER_ZACHERY, FRONTIER_TRAINER_ALISON}, // 160 - 179
    {FRONTIER_TRAINER_HANK,    FRONTIER_TRAINER_LAMAR},  // 180 - 199
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_TESS},   // 200 - 219
    {FRONTIER_TRAINER_LEON,    FRONTIER_TRAINER_RAUL},   // 220 - 239
    {FRONTIER_TRAINER_JAXON,   FRONTIER_TRAINER_GRETEL}, // 200 - 299
};

static const u8 sBattleTowerPartySizes[FRONTIER_MODE_COUNT] =
{
    [FRONTIER_MODE_SINGLES]     = FRONTIER_PARTY_SIZE,
    [FRONTIER_MODE_DOUBLES]     = FRONTIER_DOUBLES_PARTY_SIZE,
    [FRONTIER_MODE_MULTIS]      = FRONTIER_MULTI_PARTY_SIZE,
    [FRONTIER_MODE_LINK_MULTIS] = FRONTIER_MULTI_PARTY_SIZE,
};

static const u16 sRecordTrainerSpeechWon[] =
{
    EC_WORD_YAY, EC_WORD_YAY, EC_WORD_EXCL_EXCL, EC_WORD_I_VE, EC_WORD_WON, EC_WORD_EXCL_EXCL
};

static const u16 sRecordTrainerSpeechLost[] =
{
    EC_WORD_TOO, EC_WORD_BAD, EC_WORD_ELLIPSIS, EC_WORD_WE, EC_WORD_LOST, EC_WORD_ELLIPSIS
};

// code
void CallBattleTowerFunc(void)
{
    sBattleTowerFuncs[gSpecialVar_4]();
}

static void InitTowerChallenge(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    gSaveBlock2Ptr->frontier.challengeStatus = CHALLENGE_STATUS_SAVING;
    gSaveBlock2Ptr->frontier.curChallengeBattleNum = 0;
    gSaveBlock2Ptr->frontier.challengePaused = FALSE;
    gSaveBlock2Ptr->frontier.disableRecordBattle = FALSE;
    ResetFrontierTrainerIds();
    if (!(gSaveBlock2Ptr->frontier.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]))
        gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] = 0;

    SetDynamicWarp(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE);
    gTrainerBattleOpponent_A = 0;
}

static void GetTowerData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_5)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSpecialVar_Result = GetCurrentBattleTowerWinStreak(lvlMode, battleMode);
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        gSpecialVar_Result = ((gSaveBlock2Ptr->frontier.winStreakActiveFlags & sWinStreakFlags[battleMode][lvlMode]) != 0);
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->frontier.towerLvlMode = gSaveBlock2Ptr->frontier.lvlMode;
        break;
    }
}

static void SetTowerData(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);

    switch (gSpecialVar_5)
    {
    case 0:
        break;
    case TOWER_DATA_WIN_STREAK:
        gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] = gSpecialVar_6;
        break;
    case TOWER_DATA_WIN_STREAK_ACTIVE:
        if (gSpecialVar_6)
            gSaveBlock2Ptr->frontier.winStreakActiveFlags |= sWinStreakFlags[battleMode][lvlMode];
        else
            gSaveBlock2Ptr->frontier.winStreakActiveFlags &= sWinStreakMasks[battleMode][lvlMode];
        break;
    case TOWER_DATA_LVL_MODE:
        gSaveBlock2Ptr->frontier.towerLvlMode = gSaveBlock2Ptr->frontier.lvlMode;
        break;
    }
}

static void SetTowerBattleWon(void)
{

}

static void SetNextFacilityOpponent(void)
{
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    if (lvlMode == FRONTIER_LVL_TENT)
    {
        SetNextBattleTentOpponent();
    }
    else
    {
        u16 id;
        u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
        u16 winStreak = GetCurrentFacilityWinStreak();
        u32 challengeNum = winStreak / FRONTIER_STAGES_PER_CHALLENGE;
        SetFacilityPtrsGetLevel();

        if (battleMode == FRONTIER_MODE_MULTIS || battleMode == FRONTIER_MODE_LINK_MULTIS)
        {
            id = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->frontier.trainerIds[id * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->frontier.trainerIds[id * 2 + 1];
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
        }
        else
        {
            s32 i;
            while (1)
            {
                id = GetRandomScaledFrontierTrainerId(challengeNum, gSaveBlock2Ptr->frontier.curChallengeBattleNum);

                // Ensure trainer wasn't previously fought in this challenge.
                for (i = 0; i < gSaveBlock2Ptr->frontier.curChallengeBattleNum; i++)
                {
                    if (gSaveBlock2Ptr->frontier.trainerIds[i] == id)
                        break;
                }
                if (i == gSaveBlock2Ptr->frontier.curChallengeBattleNum)
                    break;
            }

            gTrainerBattleOpponent_A = id;
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            if (gSaveBlock2Ptr->frontier.curChallengeBattleNum + 1 < FRONTIER_STAGES_PER_CHALLENGE)
                gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum] = gTrainerBattleOpponent_A;
        }
    }
}

u16 GetRandomScaledFrontierTrainerId(u8 challengeNum, u8 battleNum)
{
    u16 trainerId;

    if (challengeNum <= 7)
    {
        if (battleNum == FRONTIER_STAGES_PER_CHALLENGE - 1)
        {
            // The last battle in each challenge has a jump in difficulty, pulls from a table with higher ranges
            trainerId = (sFrontierTrainerIdRangesHard[challengeNum][1] - sFrontierTrainerIdRangesHard[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRangesHard[challengeNum][0] + (Random() % trainerId);
        }
        else
        {
            trainerId = (sFrontierTrainerIdRanges[challengeNum][1] - sFrontierTrainerIdRanges[challengeNum][0]) + 1;
            trainerId = sFrontierTrainerIdRanges[challengeNum][0] + (Random() % trainerId);
        }
    }
    else
    {
        // After challenge 7, trainer IDs always come from the last, hardest range, which is the same for both trainer ID tables
        trainerId = (sFrontierTrainerIdRanges[7][1] - sFrontierTrainerIdRanges[7][0]) + 1;
        trainerId = sFrontierTrainerIdRanges[7][0] + (Random() % trainerId);
    }

    return trainerId;
}

void SetBattleFacilityTrainerGfxId(u16 trainerId, u8 tempVarId)
{
    SetFacilityPtrsGetLevel();
    if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        SetFrontierBrainObjEventGfx_2();
        return;
    }

    switch (tempVarId)
    {
    case 0:
    default:
        VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1);
        return;
    case 1:
        VarSet(VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1);
        return;
    case 15:
        VarSet(VAR_OBJ_GFX_ID_E, OBJ_EVENT_GFX_BOY_1);
        return;
    }
}

void SetEReaderTrainerGfxId(void)
{
    SetBattleFacilityTrainerGfxId(TRAINER_EREADER, 0);
}

u16 GetBattleFacilityTrainerGfxId(u16 trainerId)
{
    SetFacilityPtrsGetLevel();
    return OBJ_EVENT_GFX_BOY_1;
}

u8 GetFrontierTrainerFrontSpriteId(u16 trainerId)
{
    return 0;
}

u8 GetFrontierOpponentClass(u16 trainerId)
{
    return 0;
}

void GetFrontierTrainerName(u8 *dst, u16 trainerId)
{
    s32 i = 0;
    SetFacilityPtrsGetLevel();

    if (trainerId == TRAINER_EREADER)
    {
    #if FREE_BATTLE_TOWER_E_READER == FALSE
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gSaveBlock2Ptr->frontier.ereaderTrainer.name[i];
    #endif //FREE_BATTLE_TOWER_E_READER
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CopyFrontierBrainTrainerName(dst);
        return;
    }
    else if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        for (i = 0; gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName[i] != EOS; i++)
            dst[i] = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName[i];
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        for (i = 0; i < PLAYER_NAME_LENGTH; i++)
            dst[i] = gFacilityTrainers[trainerId].trainerName[i];
    }

    dst[i] = EOS;
}

void FillFrontierTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
}

void FillFrontierTrainersParties(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTrainerParty(gTrainerBattleOpponent_A, 0, monsCount);
    FillTrainerParty(gTrainerBattleOpponent_B, 3, monsCount);
}

static void FillTentTrainerParty(u8 monsCount)
{
    ZeroEnemyPartyMons();
    FillTentTrainerParty_(gTrainerBattleOpponent_A, 0, monsCount);
}

void CreateFacilityMon(const struct TrainerMon *fmon, u16 level, u8 fixedIV, u32 otID, u32 flags, struct Pokemon *dst)
{
    u8 ball = (fmon->ball == 0xFF) ? Random() % POKEBALL_COUNT : fmon->ball;
    u16 move;
    u32 personality, ability, friendship, j;

    if (fmon->gender == TRAINER_MON_MALE)
    {
        personality = GeneratePersonalityForGender(MON_MALE, fmon->species);
    }
    else if (fmon->gender == TRAINER_MON_FEMALE)
    {
        personality = GeneratePersonalityForGender(MON_FEMALE, fmon->species);
    }

    ModifyPersonalityForNature(&personality, fmon->nature);
    CreateMon(dst, fmon->species, level, fixedIV, TRUE, personality, otID, OT_ID_PRESET);

    friendship = MAX_FRIENDSHIP;
    // Give the chosen Pokémon its specified moves.
    for (j = 0; j < MAX_MON_MOVES; j++)
    {
        move = fmon->moves[j];
        if (flags & FLAG_FRONTIER_MON_FACTORY && move == MOVE_RETURN)
            move = MOVE_FRUSTRATION;

        SetMonMoveSlot(dst, move, j);
        if (gMovesInfo[move].effect == EFFECT_FRUSTRATION)
            friendship = 0;  // Frustration is more powerful the lower the pokemon's friendship is.
    }

    SetMonData(dst, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(dst, MON_DATA_HELD_ITEM, &fmon->heldItem);

    // try to set ability. Otherwise, random of non-hidden as per vanilla
    if (fmon->ability != ABILITY_NONE)
    {
        const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[fmon->species];
        u32 maxAbilities = ARRAY_COUNT(speciesInfo->abilities);
        for (ability = 0; ability < maxAbilities; ++ability)
        {
            if (speciesInfo->abilities[ability] == fmon->ability)
                break;
        }
        if (ability >= maxAbilities)
            ability = 0;
        SetMonData(dst, MON_DATA_ABILITY_NUM, &ability);
    }

    if (fmon->ev != NULL)
    {
        SetMonData(dst, MON_DATA_HP_EV, &(fmon->ev[0]));
        SetMonData(dst, MON_DATA_ATK_EV, &(fmon->ev[1]));
        SetMonData(dst, MON_DATA_DEF_EV, &(fmon->ev[2]));
        SetMonData(dst, MON_DATA_SPATK_EV, &(fmon->ev[3]));
        SetMonData(dst, MON_DATA_SPDEF_EV, &(fmon->ev[4]));
        SetMonData(dst, MON_DATA_SPEED_EV, &(fmon->ev[5]));
    }

    if (fmon->iv)
        SetMonData(dst, MON_DATA_IVS, &(fmon->iv));

    if (fmon->isShiny)
    {
        u32 data = TRUE;
        SetMonData(dst, MON_DATA_IS_SHINY, &data);
    }
    if (fmon->dynamaxLevel > 0)
    {
        u32 data = fmon->dynamaxLevel;
        SetMonData(dst, MON_DATA_DYNAMAX_LEVEL, &data);
    }
    if (fmon->gigantamaxFactor)
    {
        u32 data = fmon->gigantamaxFactor;
        SetMonData(dst, MON_DATA_GIGANTAMAX_FACTOR, &data);
    }
    if (fmon->teraType)
    {
        u32 data = fmon->teraType;
        SetMonData(dst, MON_DATA_TERA_TYPE, &data);
    }


    SetMonData(dst, MON_DATA_POKEBALL, &ball);
    CalculateMonStats(dst);
}

static void FillTrainerParty(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[MAX_FRONTIER_PARTY_SIZE];
    u8 level = SetFacilityPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;

    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        // Normal battle frontier trainer.
        fixedIV = GetFrontierTrainerFixedIvs(trainerId);
        monSet = gFacilityTrainers[gTrainerBattleOpponent_A].monSet;
    }
    else if (trainerId == TRAINER_EREADER)
    {
    #if FREE_BATTLE_TOWER_E_READER == FALSE
        for (i = firstMonId; i < firstMonId + FRONTIER_PARTY_SIZE; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i - firstMonId]);
    #endif //FREE_BATTLE_TOWER_E_READER
        return;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        CreateFrontierBrainPokemon();
        return;
    }

    // Regular battle frontier trainer.
    // Attempt to fill the trainer's party with random Pokémon until 3 have been
    // successfully chosen. The trainer's party may not have duplicate Pokémon species
    // or duplicate held items.
    for (bfMonCount = 0; monSet[bfMonCount] != 0xFFFF; bfMonCount++)
        ;
    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];

        // "High tier" Pokémon are only allowed on open level mode
        // 20 is not a possible value for level here
        if ((level == FRONTIER_MAX_LEVEL_50 || level == 20) && monId > FRONTIER_MONS_HIGH_TIER)
            continue;

        // Ensure this Pokémon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gFacilityTrainerMons[monId].heldItem)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact Pokémon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;

        // Place the chosen Pokémon into the trainer's party.
        CreateFacilityMon(&gFacilityTrainerMons[monId], level, fixedIV, otID, 0, &gEnemyParty[i + firstMonId]);

        // The Pokémon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

u16 GetRandomFrontierMonFromSet(u16 trainerId)
{
    u8 level = SetFacilityPtrsGetLevel();
    const u16 *monSet = gFacilityTrainers[trainerId].monSet;
    u8 numMons = 0;
    u32 monId = monSet[numMons];

    while (monId != 0xFFFF)
    {
        numMons++;
        monId = monSet[numMons];
        if (monId == 0xFFFF)
            break;
    }

    do
    {
        // "High tier" Pokémon are only allowed on open level mode
        // 20 is not a possible value for level here
        monId = monSet[Random() % numMons];
    } while((level == FRONTIER_MAX_LEVEL_50 || level == 20) && monId > FRONTIER_MONS_HIGH_TIER);

    return monId;
}

static void FillFactoryTrainerParty(void)
{
    ZeroEnemyPartyMons();
    if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
        FillFactoryFrontierTrainerParty(gTrainerBattleOpponent_A, 0);
    else
        FillFactoryTentTrainerParty(gTrainerBattleOpponent_A, 0);
}

static void FillFactoryFrontierTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i;
    u8 level;
    u8 fixedIV;
    u32 otID;

    if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
    // By mistake Battle Tower's Level 50 challenge number is used to determine the IVs for Battle Factory.
    #ifdef BUGFIX
        u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
        u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
        u8 challengeNum = gSaveBlock2Ptr->frontier.factoryWinStreaks[battleMode][lvlMode] / FRONTIER_STAGES_PER_CHALLENGE;
    #else
        u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
        u8 challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][FRONTIER_LVL_50] / FRONTIER_STAGES_PER_CHALLENGE;
    #endif
        if (gSaveBlock2Ptr->frontier.curChallengeBattleNum < FRONTIER_STAGES_PER_CHALLENGE - 1)
            fixedIV = GetFactoryMonFixedIV(challengeNum, FALSE);
        else
            fixedIV = GetFactoryMonFixedIV(challengeNum, TRUE); // Last trainer in challenge uses higher IVs
    }
    else if (trainerId == TRAINER_EREADER)
    {
    #if FREE_BATTLE_TOWER_E_READER == FALSE
        for (i = firstMonId; i < firstMonId + FRONTIER_PARTY_SIZE; i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i - firstMonId]);
    #endif //FREE_BATTLE_TOWER_E_READER
        return;
    }
    else if (trainerId == TRAINER_FRONTIER_BRAIN)
    {
        FillFactoryBrainParty();
        return;
    }
    else
    {
        fixedIV = MAX_PER_STAT_IVS;
    }

    level = SetFacilityPtrsGetLevel();
    otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);
    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        u16 monId = gFrontierTempParty[i];
        CreateFacilityMon(&gFacilityTrainerMons[monId],
                level, fixedIV, otID, FLAG_FRONTIER_MON_FACTORY,
                &gEnemyParty[firstMonId + i]);
    }
}

static void FillFactoryTentTrainerParty(u16 trainerId, u8 firstMonId)
{
    u8 i;
    u8 level = TENT_MIN_LEVEL;
    u8 fixedIV = 0;
    u32 otID = T1_READ_32(gSaveBlock2Ptr->playerTrainerId);

    for (i = 0; i < FRONTIER_PARTY_SIZE; i++)
    {
        u16 monId = gFrontierTempParty[i];
        CreateFacilityMon(&gFacilityTrainerMons[monId],
                level, fixedIV, otID, 0,
                &gEnemyParty[firstMonId + i]);
    }
}

void FrontierSpeechToString(const u16 *words)
{
    ConvertEasyChatWordsToString(gStringVar4, words, 3, 2);
    if (GetStringWidth(FONT_NORMAL, gStringVar4, -1) > 204u)
    {
        s32 i = 0;

        ConvertEasyChatWordsToString(gStringVar4, words, 2, 3);
        while (gStringVar4[i++] != CHAR_NEWLINE)
            ;
        while (gStringVar4[i] != CHAR_NEWLINE)
            i++;

        gStringVar4[i] = CHAR_PROMPT_SCROLL;
    }
}

static void GetOpponentIntroSpeech(void)
{
    u16 trainerId;
    SetFacilityPtrsGetLevel();

    if (gSpecialVar_5)
        trainerId = gTrainerBattleOpponent_B;
    else
        trainerId = gTrainerBattleOpponent_A;

#if FREE_BATTLE_TOWER_E_READER == FALSE
    if (trainerId == TRAINER_EREADER)
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.greeting);
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
#else
    if (trainerId < FRONTIER_TRAINERS_COUNT)
#endif //FREE_BATTLE_TOWER_E_READER
        FrontierSpeechToString(gFacilityTrainers[trainerId].speechBefore);
    else
        BufferApprenticeChallengeText(trainerId);
}

static void HandleSpecialTrainerBattleEnd(void)
{
    s32 i;

    RecordedBattle_SaveBattleOutcome();
    switch (gBattleScripting.specialTrainerBattleType)
    {
    case SPECIAL_BATTLE_TOWER:
    case SPECIAL_BATTLE_DOME:
    case SPECIAL_BATTLE_PALACE:
    case SPECIAL_BATTLE_ARENA:
    case SPECIAL_BATTLE_FACTORY:
    case SPECIAL_BATTLE_PIKE_SINGLE:
    case SPECIAL_BATTLE_PIKE_DOUBLE:
    case SPECIAL_BATTLE_PYRAMID:
        if (gSaveBlock2Ptr->frontier.battlesCount < 0xFFFFFF)
        {
            gSaveBlock2Ptr->frontier.battlesCount++;
            if (gSaveBlock2Ptr->frontier.battlesCount % 20 == 0)
                UpdateGymLeaderRematch();
        }
        else
        {
            gSaveBlock2Ptr->frontier.battlesCount = 0xFFFFFF;
        }
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        break;
    case SPECIAL_BATTLE_EREADER:
        CopyEReaderTrainerFarewellMessage();
        break;
    case SPECIAL_BATTLE_MULTI:
        for (i = 0; i < 3; i++)
        {
            if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES))
                gSaveBlock1Ptr->playerParty[i] = gPlayerParty[i];
        }
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

static void Task_StartBattleAfterTransition(u8 taskId)
{
    if (IsBattleTransitionDone() == TRUE)
    {
        gMain.savedCallback = HandleSpecialTrainerBattleEnd;
        SetMainCallback2(CB2_InitBattle);
        DestroyTask(taskId);
    }
}

void DoSpecialTrainerBattle(void)
{
    s32 i;

    gBattleScripting.specialTrainerBattleType = gSpecialVar_4;
    switch (gSpecialVar_4)
    {
    case SPECIAL_BATTLE_TOWER:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        switch (VarGet(VAR_FRONTIER_BATTLE_MODE))
        {
        case FRONTIER_MODE_SINGLES:
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
            break;
        case FRONTIER_MODE_DOUBLES:
            FillFrontierTrainerParty(FRONTIER_DOUBLES_PARTY_SIZE);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
            break;
        case FRONTIER_MODE_MULTIS:
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            gPartnerTrainerId = gSaveBlock2Ptr->frontier.trainerIds[17];
            FillPartnerParty(gPartnerTrainerId);
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_MULTI | BATTLE_TYPE_TWO_OPPONENTS;
            break;
        case FRONTIER_MODE_LINK_MULTIS:
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE | BATTLE_TYPE_LINK | BATTLE_TYPE_MULTI | BATTLE_TYPE_TOWER_LINK_MULTI;
            FillFrontierTrainersParties(FRONTIER_MULTI_PARTY_SIZE);
            break;
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_TOWER));
        break;
    case SPECIAL_BATTLE_SECRET_BASE:
        for (i = 0; i < PARTY_SIZE; i++)
        {
            u16 itemBefore = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);
            SetMonData(&gSaveBlock1Ptr->playerParty[i], MON_DATA_HELD_ITEM, &itemBefore);
        }
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_SECRET_BASE));
        break;
    case SPECIAL_BATTLE_EREADER:
    #if FREE_BATTLE_TOWER_E_READER == FALSE
        ZeroEnemyPartyMons();
        for (i = 0; i < (int)ARRAY_COUNT(gSaveBlock2Ptr->frontier.ereaderTrainer.party); i++)
            CreateBattleTowerMon(&gEnemyParty[i], &gSaveBlock2Ptr->frontier.ereaderTrainer.party[i]);
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_EREADER_TRAINER;
        gTrainerBattleOpponent_A = 0;
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_E_READER));
    #endif //FREE_BATTLE_TOWER_E_READER
        break;
    case SPECIAL_BATTLE_DOME:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOME;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
            FillFrontierTrainerParty(DOME_BATTLE_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        CreateTask_PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_DOME));
        break;
    case SPECIAL_BATTLE_PALACE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PALACE;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
            FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PALACE));
        break;
    case SPECIAL_BATTLE_ARENA:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_ARENA;
        if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_TENT)
            FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        else
            FillTentTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_ARENA));
        break;
    case SPECIAL_BATTLE_FACTORY:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_FACTORY;
        if (VarGet(VAR_FRONTIER_BATTLE_MODE) == FRONTIER_MODE_DOUBLES)
            gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
        FillFactoryTrainerParty();
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_FACTORY));
        break;
    case SPECIAL_BATTLE_PIKE_SINGLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case SPECIAL_BATTLE_PYRAMID:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_PYRAMID;
        FillFrontierTrainerParty(FRONTIER_PARTY_SIZE);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PYRAMID));
        break;
    case SPECIAL_BATTLE_PIKE_DOUBLE:
        gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS;
        FillFrontierTrainersParties(1);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        BattleTransition_StartOnField(GetSpecialBattleTransition(B_TRANSITION_GROUP_B_PIKE));
        break;
    case SPECIAL_BATTLE_MULTI:
        if (gSpecialVar_5 & MULTI_BATTLE_2_VS_WILD) // Player + AI against wild mon
        {
            gBattleTypeFlags = BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }
        else if (gSpecialVar_5 & MULTI_BATTLE_2_VS_1) // Player + AI against one trainer
        {
            gTrainerBattleOpponent_B = 0xFFFF;
            gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }
        else // MULTI_BATTLE_2_VS_2
        {
            gBattleTypeFlags = BATTLE_TYPE_TRAINER | BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_MULTI | BATTLE_TYPE_INGAME_PARTNER;
        }

        gPartnerTrainerId = VarGet(gSpecialVar_6) + TRAINER_PARTNER(PARTNER_NONE);
        FillPartnerParty(gPartnerTrainerId);
        CreateTask(Task_StartBattleAfterTransition, 1);
        PlayMapChosenOrBattleBGM(0);
        if (gSpecialVar_5 & MULTI_BATTLE_2_VS_WILD)
            BattleTransition_StartOnField(GetWildBattleTransition());
        else
            BattleTransition_StartOnField(GetTrainerBattleTransition());

        if (gSpecialVar_5 & MULTI_BATTLE_CHOOSE_MONS) // Skip mons restoring(done in the script)
            gBattleScripting.specialTrainerBattleType = 0xFF;
        break;
    }
}

static void SaveTowerChallenge(void)
{
    gSaveBlock2Ptr->frontier.challengeStatus = gSpecialVar_5;
    VarSet(VAR_TEMP_CHALLENGE_STATUS, 0);
    gSaveBlock2Ptr->frontier.challengePaused = TRUE;
    SaveGameFrontier();
}

static void GetApprenticeMultiPartnerParty(u16 trainerId)
{
    s32 i, count;
    u32 validSpecies[MULTI_PARTY_SIZE];
    u16 species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    u16 species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    count = 0;
    for (i = 0; i < MULTI_PARTY_SIZE; i++)
    {
        u16 apprenticeSpecies = gSaveBlock2Ptr->apprentices[trainerId].party[i].species;
        if (apprenticeSpecies != species1 && apprenticeSpecies != species2)
        {
            validSpecies[count] = i;
            count++;
        }
    }

    gFrontierTempParty[0] = validSpecies[Random() % count];
    do
    {
        gFrontierTempParty[1] = validSpecies[Random() % count];
    } while (gFrontierTempParty[0] == gFrontierTempParty[1]);
}

static void LoadMultiPartnerCandidatesData(void)
{
    s32 i, j, k;
    u32 spArray[5];
    s32 r10;
    u16 trainerId;
    u16 monId;
    u32 lvlMode, battleMode;
    s32 challengeNum;
    u32 species1, species2;
    struct ObjectEventTemplate *objEventTemplates;

    objEventTemplates = gSaveBlock1Ptr->objectEventTemplates;
    lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] / FRONTIER_STAGES_PER_CHALLENGE;
    species1 = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES, NULL);
    species2 = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);

    j = 0;
    do
    {
        do
        {
            trainerId = GetRandomScaledFrontierTrainerId(challengeNum, 0);
            for (i = 0; i < j; i++)
            {
                if (gSaveBlock2Ptr->frontier.trainerIds[i] == trainerId)
                    break;
            }
        } while (i != j);
        gSaveBlock2Ptr->frontier.trainerIds[j] = trainerId;
        j++;
    } while (j < 6);

    r10 = 8;
    for (i = 0; i < 6; i++)
    {
        trainerId = gSaveBlock2Ptr->frontier.trainerIds[i];
        objEventTemplates[i + 1].graphicsId = GetBattleFacilityTrainerGfxId(trainerId);
        for (j = 0; j < 2; j++)
        {
            while (1)
            {
                monId = GetRandomFrontierMonFromSet(trainerId);
                if (j % 2 != 0 && gFacilityTrainerMons[gSaveBlock2Ptr->frontier.trainerIds[r10 - 1]].heldItem == gFacilityTrainerMons[monId].heldItem)
                    continue;

                for (k = 8; k < r10; k++)
                {
                    if (gFacilityTrainerMons[gSaveBlock2Ptr->frontier.trainerIds[k]].species == gFacilityTrainerMons[monId].species)
                        break;
                    if (species1 == gFacilityTrainerMons[monId].species)
                        break;
                    if (species2 == gFacilityTrainerMons[monId].species)
                        break;
                }
                if (k == r10)
                    break;
            }

            gSaveBlock2Ptr->frontier.trainerIds[r10] = monId;
            r10++;
        }
    }

    r10 = 0;
    ValidateApprenticesChecksums();
    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        if (gSaveBlock2Ptr->apprentices[i].lvlMode != 0
            && sApprenticeChallengeThreshold[gSaveBlock2Ptr->apprentices[i].numQuestions] / FRONTIER_STAGES_PER_CHALLENGE <= challengeNum
            && gSaveBlock2Ptr->apprentices[i].lvlMode - 1 == lvlMode)
        {
            k = 0;
            for (j = 0; j < MULTI_PARTY_SIZE; j++)
            {
                if (species1 != gSaveBlock2Ptr->apprentices[i].party[j].species
                    && species2 != gSaveBlock2Ptr->apprentices[i].party[j].species)
                {
                    k++;
                }
            }
            if (k > 2)
            {
                spArray[r10] = i;
                r10++;
            }
        }
    }
    if (r10 != 0)
    {
        gSaveBlock2Ptr->frontier.trainerIds[6] = spArray[Random() % r10];
        objEventTemplates[7].graphicsId = GetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[6]);
        FlagClear(FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1);
        GetApprenticeMultiPartnerParty(gSaveBlock2Ptr->frontier.trainerIds[6]);
    }

    r10 = 0;
    if (r10 != 0)
    {
        gSaveBlock2Ptr->frontier.trainerIds[7] = spArray[Random() % r10];
        objEventTemplates[8].graphicsId = GetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[7]);
        FlagClear(FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2);
    }
}

static void GetPotentialPartnerMoveAndSpecies(u16 trainerId, u16 monId)
{
    u16 move = 0;
    u16 species = 0;
    SetFacilityPtrsGetLevel();

    if (trainerId != TRAINER_EREADER)
    {
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            move = gFacilityTrainerMons[monId].moves[0];
            species = gFacilityTrainerMons[monId].species;
        }
    }

    StringCopy(gStringVar1, GetMoveName(move));
    StringCopy(gStringVar2, GetSpeciesName(species));
}

// For multi battles in the Battle Tower, the player may choose a partner by talking to them
// These partners can be an NPC or a former/record-mixed Apprentice
// When talked to, their response consists of:
// PARTNER_MSGID_INTRO - A greeting
// PARTNER_MSGID_MON1 - Naming one Pokémon on their team, and a move it has
// PARTNER_MSGID_MON2_ASK - Naming a second Pokémon on their team, a move it has, and asking if they'd like to be their partner
// PARTNER_MSGID_ACCEPT - If the player agrees to be their partner
// PARTNER_MSGID_REJECT - If the player declines to be their partner
static void ShowPartnerCandidateMessage(void)
{
    s32 i, j;
    s32 monId;
    u16 winStreak = GetCurrentFacilityWinStreak();
    s32 challengeNum = winStreak / FRONTIER_STAGES_PER_CHALLENGE;
    s32 k = gSpecialVar_LastTalked - 2;
    s32 trainerId = gSaveBlock2Ptr->frontier.trainerIds[k];

    switch (gSpecialVar_5)
    {
    case PARTNER_MSGID_INTRO:
        if (trainerId == TRAINER_EREADER)
            return;
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            GetFrontierTrainerName(gStringVar1, trainerId);
        }
        break;
    case PARTNER_MSGID_MON1:
        monId = gSaveBlock2Ptr->frontier.trainerIds[8 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_MON2_ASK:
        monId = gSaveBlock2Ptr->frontier.trainerIds[9 + k * 2];
        GetPotentialPartnerMoveAndSpecies(trainerId, monId);
        break;
    case PARTNER_MSGID_ACCEPT:
        gPartnerTrainerId = trainerId;
        if (trainerId < FRONTIER_TRAINERS_COUNT)
        {
            gSaveBlock2Ptr->frontier.trainerIds[18] = gSaveBlock2Ptr->frontier.trainerIds[8 + k * 2];
            gSaveBlock2Ptr->frontier.trainerIds[19] = gSaveBlock2Ptr->frontier.trainerIds[9 + k * 2];
        }
        else
        {
            gSaveBlock2Ptr->frontier.trainerIds[18] = gFrontierTempParty[0];
            gSaveBlock2Ptr->frontier.trainerIds[19] = gFrontierTempParty[1];
        }
        for (k = 0; k < FRONTIER_STAGES_PER_CHALLENGE * 2; k++)
        {
            while (1)
            {
                i = GetRandomScaledFrontierTrainerId(challengeNum, k / 2);
                if (gPartnerTrainerId == i)
                    continue;

                for (j = 0; j < k; j++)
                {
                    if (gSaveBlock2Ptr->frontier.trainerIds[j] == i)
                        break;
                }
                if (j == k)
                    break;
            }
            gSaveBlock2Ptr->frontier.trainerIds[k] = i;
        }
        gSaveBlock2Ptr->frontier.trainerIds[17] = trainerId;
        break;
    case PARTNER_MSGID_REJECT:
        break;
    }

    if (trainerId == TRAINER_EREADER)
        return;
}

static void LoadLinkMultiOpponentsData(void)
{
    s32 challengeNum;
    u32 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u32 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u32 battleNum = gSaveBlock2Ptr->frontier.curChallengeBattleNum;
    GetMultiplayerId(); // Yet another pointless function call.

    switch (gSpecialVar_Result)
    {
    case 0:
        if (battleMode == FRONTIER_MODE_LINK_MULTIS)
        {
            challengeNum = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode] / FRONTIER_STAGES_PER_CHALLENGE;
            if (IsLinkTaskFinished())
            {
                SendBlock(BitmaskAllOtherLinkPlayers(), &challengeNum, sizeof(challengeNum));
                gSpecialVar_Result = 1;
            }
        }
        else
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 1:
        break;
    case 2:
        if (IsLinkTaskFinished())
        {
            SendBlock(BitmaskAllOtherLinkPlayers(), &gSaveBlock2Ptr->frontier.trainerIds, sizeof(gSaveBlock2Ptr->frontier.trainerIds));
            gSpecialVar_Result = 3;
        }
        break;
    case 3:
        if ((GetBlockReceivedStatus() & 3) == 3)
        {
            gTrainerBattleOpponent_A = gSaveBlock2Ptr->frontier.trainerIds[battleNum * 2];
            gTrainerBattleOpponent_B = gSaveBlock2Ptr->frontier.trainerIds[battleNum * 2 + 1];
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
            SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_B, 1);
            if (gReceivedRemoteLinkPlayers)
                gSpecialVar_Result = 4;
            else
                gSpecialVar_Result = 6;
        }
        break;
    case 4:
        SetCloseLinkCallback();
        gSpecialVar_Result = 5;
        break;
    case 5:
        if (gReceivedRemoteLinkPlayers == 0)
        {
            gSpecialVar_Result = 6;
        }
        break;
    case 6:
        return;
    }
}

static void TowerTryCloseLink(void)
{

}

static void SetMultiPartnerGfx(void)
{
    // 0xF below means use VAR_OBJ_GFX_ID_E
    SetBattleFacilityTrainerGfxId(gSaveBlock2Ptr->frontier.trainerIds[17], 0xF);
}

static void SetTowerInterviewData(void)
{
    s32 i;
    u8 text[32];

    if (VarGet(VAR_FRONTIER_BATTLE_MODE) != FRONTIER_MODE_SINGLES)
        return;

    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
    StripExtCtrlCodes(text);
    StringCopy(gSaveBlock2Ptr->frontier.towerInterview.opponentName, text);
    GetBattleTowerTrainerLanguage(&gSaveBlock2Ptr->frontier.towerInterview.opponentLanguage, gTrainerBattleOpponent_A);
    gSaveBlock2Ptr->frontier.towerInterview.opponentSpecies = GetMonData(&gEnemyParty[gBattlerPartyIndexes[1]], MON_DATA_SPECIES, NULL);
    gSaveBlock2Ptr->frontier.towerInterview.playerSpecies = GetMonData(&gPlayerParty[gBattlerPartyIndexes[0]], MON_DATA_SPECIES, NULL);
    for (i = 0; i < VANILLA_POKEMON_NAME_LENGTH + 1; i++)
        gSaveBlock2Ptr->frontier.towerInterview.opponentMonNickname[i] = gBattleMons[0].nickname[i];
    gSaveBlock2Ptr->frontier.towerBattleOutcome = gBattleOutcome;
}

u16 GetCurrentBattleTowerWinStreak(u8 lvlMode, u8 battleMode)
{
    u16 winStreak = gSaveBlock2Ptr->frontier.towerWinStreaks[battleMode][lvlMode];

    if (winStreak > MAX_STREAK)
        return MAX_STREAK;
    else
        return winStreak;
}

static u8 GetMonCountForBattleMode(u8 battleMode)
{
    u8 partySizes[ARRAY_COUNT(sBattleTowerPartySizes)];
    memcpy(partySizes, sBattleTowerPartySizes, sizeof(sBattleTowerPartySizes));

    if (battleMode < ARRAY_COUNT(sBattleTowerPartySizes))
        return partySizes[battleMode];
    else
        return FRONTIER_PARTY_SIZE;
}

struct RibbonCounter
{
    u8 partyIndex;
    u8 count;
};

static void AwardBattleTowerRibbons(void)
{
    s32 i;
    u32 partyIndex;
#ifdef BUGFIX
    struct RibbonCounter ribbons[MAX_FRONTIER_PARTY_SIZE];
#else
    struct RibbonCounter ribbons[3]; // BUG: 4 Pokémon can receive ribbons in a double battle mode.
#endif
    u8 ribbonType = 0;
    u8 lvlMode = gSaveBlock2Ptr->frontier.lvlMode;
    u8 battleMode = VarGet(VAR_FRONTIER_BATTLE_MODE);
    u8 monCount = GetMonCountForBattleMode(battleMode);

    if (lvlMode != FRONTIER_LVL_50)
        ribbonType = MON_DATA_VICTORY_RIBBON;
    else
        ribbonType = MON_DATA_WINNING_RIBBON;

    gSpecialVar_Result = FALSE;

    if (GetCurrentBattleTowerWinStreak(lvlMode, battleMode) > 55)
    {
        for (i = 0; i < monCount; i++)
        {
            partyIndex = gSaveBlock2Ptr->frontier.selectedPartyMons[i] - 1;
            ribbons[i].partyIndex = partyIndex;
            ribbons[i].count = 0;
            if (!GetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType))
            {
                gSpecialVar_Result = TRUE;
                SetMonData(&gSaveBlock1Ptr->playerParty[partyIndex], ribbonType, &gSpecialVar_Result);
            }
        }
    }

    if (gSpecialVar_Result)
    {
        IncrementGameStat(GAME_STAT_RECEIVED_RIBBONS);
        for (i = 1; i < monCount; i++)
        {
            if (ribbons[i].count > ribbons[0].count)
            {
                struct RibbonCounter prevBest = ribbons[0];
                ribbons[0] = ribbons[i];
                ribbons[i] = prevBest;
            }
        }
    }
}

u8 GetEreaderTrainerFrontSpriteId(void)
{
    return 0;
}

u8 GetEreaderTrainerClassId(void)
{
    return 0;
}

void GetEreaderTrainerName(u8 *dst)
{
    dst[0] = EOS;
}

// Checks if the saved E-Reader trainer is valid.
void ValidateEReaderTrainer(void)
{

}

void CopyEReaderTrainerGreeting(void)
{

}

static void CopyEReaderTrainerFarewellMessage(void)
{
#if FREE_BATTLE_TOWER_E_READER == FALSE
    if (gBattleOutcome == B_OUTCOME_DREW)
        gStringVar4[0] = EOS;
    else if (gBattleOutcome == B_OUTCOME_WON)
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.farewellPlayerWon);
    else
        FrontierSpeechToString(gSaveBlock2Ptr->frontier.ereaderTrainer.farewellPlayerLost);
#endif //FREE_BATTLE_TOWER_E_READER
}

#define STEVEN_OTID 61226

static void FillPartnerParty(u16 trainerId)
{
    s32 i, j, k;
    u32 firstIdPart = 0, secondIdPart = 0, thirdIdPart = 0;
    u32 ivs, level, personality;
    u16 monId;
    u32 otID;
    u8 trainerName[(PLAYER_NAME_LENGTH * 3) + 1];
    s32 ball = -1;
    SetFacilityPtrsGetLevel();

    if (trainerId > TRAINER_PARTNER(PARTNER_NONE))
    {
        for (i = 0; i < 3; i++)
            ZeroMonData(&gPlayerParty[i + 3]);

        for (i = 0; i < 3 && i < gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].partySize; i++)
        {
            const struct TrainerMon *partyData = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].party;
            const u8 *partnerName = gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName;

            for (k = 0; partnerName[k] != EOS && k < 3; k++)
            {
                if (k == 0)
                {
                    firstIdPart = partnerName[k];
                    secondIdPart = partnerName[k];
                    thirdIdPart = partnerName[k];
                }
                else if (k == 1)
                {
                    secondIdPart = partnerName[k];
                    thirdIdPart = partnerName[k];
                }
                else if (k == 2)
                {
                    thirdIdPart = partnerName[k];
                }
            }
            if (trainerId == TRAINER_PARTNER(PARTNER_STEVEN))
                otID = STEVEN_OTID;
            else
                otID = ((firstIdPart % 72) * 1000) + ((secondIdPart % 23) * 10) + (thirdIdPart % 37) % 65536;

            personality = Random32();
            if (partyData[i].gender == TRAINER_MON_MALE)
                personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_MALE, partyData[i].species);
            else if (partyData[i].gender == TRAINER_MON_FEMALE)
                personality = (personality & 0xFFFFFF00) | GeneratePersonalityForGender(MON_FEMALE, partyData[i].species);
            ModifyPersonalityForNature(&personality, partyData[i].nature);
            CreateMon(&gPlayerParty[i + 3], partyData[i].species, partyData[i].lvl, 0, TRUE, personality, OT_ID_PRESET, otID);
            j = partyData[i].isShiny;
            SetMonData(&gPlayerParty[i + 3], MON_DATA_IS_SHINY, &j);
            SetMonData(&gPlayerParty[i + 3], MON_DATA_HELD_ITEM, &partyData[i].heldItem);
            CustomTrainerPartyAssignMoves(&gPlayerParty[i + 3], &partyData[i]);

            SetMonData(&gPlayerParty[i + 3], MON_DATA_IVS, &(partyData[i].iv));
            if (partyData[i].ev != NULL)
            {
                SetMonData(&gPlayerParty[i + 3], MON_DATA_HP_EV, &(partyData[i].ev[0]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_ATK_EV, &(partyData[i].ev[1]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_DEF_EV, &(partyData[i].ev[2]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPATK_EV, &(partyData[i].ev[3]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPDEF_EV, &(partyData[i].ev[4]));
                SetMonData(&gPlayerParty[i + 3], MON_DATA_SPEED_EV, &(partyData[i].ev[5]));
            }
            if (partyData[i].ability != ABILITY_NONE)
            {
                const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[partyData[i].species];
                u32 maxAbilities = ARRAY_COUNT(speciesInfo->abilities);
                for (j = 0; j < maxAbilities; j++)
                {
                    if (speciesInfo->abilities[j] == partyData[i].ability)
                        break;
                }
                if (j < maxAbilities)
                    SetMonData(&gPlayerParty[i + 3], MON_DATA_ABILITY_NUM, &j);
            }
            SetMonData(&gPlayerParty[i + 3], MON_DATA_FRIENDSHIP, &(partyData[i].friendship));
            if (partyData[i].ball != ITEM_NONE)
            {
                ball = partyData[i].ball;
                SetMonData(&gPlayerParty[i + 3], MON_DATA_POKEBALL, &ball);
            }
            if (partyData[i].nickname != NULL)
            {
                SetMonData(&gPlayerParty[i + 3], MON_DATA_NICKNAME, partyData[i].nickname);
            }
            CalculateMonStats(&gPlayerParty[i + 3]);

            StringCopy(trainerName, gBattlePartners[trainerId - TRAINER_PARTNER(PARTNER_NONE)].trainerName);
            SetMonData(&gPlayerParty[i + 3], MON_DATA_OT_NAME, trainerName);
        }
    }
    else if (trainerId == TRAINER_EREADER)
    {
        // Scrapped, lol.
        trainerName[0] = gGameLanguage;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        level = SetFacilityPtrsGetLevel();
        ivs = GetFrontierTrainerFixedIvs(trainerId);
        otID = Random32();
        for (i = 0; i < FRONTIER_MULTI_PARTY_SIZE; i++)
        {
            monId = gSaveBlock2Ptr->frontier.trainerIds[i + 18];
            CreateFacilityMon(&gFacilityTrainerMons[monId], level, ivs, otID, 0, &gPlayerParty[MULTI_PARTY_SIZE + i]);
            for (j = 0; j < PLAYER_NAME_LENGTH + 1; j++)
                trainerName[j] = gFacilityTrainers[trainerId].trainerName[j];
            SetMonData(&gPlayerParty[MULTI_PARTY_SIZE + i], MON_DATA_OT_NAME, &trainerName);
        }
    }
}

void CalcApprenticeChecksum(struct Apprentice *apprentice)
{
    s32 i;

    apprentice->checksum = 0;
    for (i = 0; i < offsetof(struct Apprentice, checksum) / sizeof(u32); i++)
        apprentice->checksum += ((u32 *)apprentice)[i];
}

static void ClearApprentice(struct Apprentice *apprentice)
{
    s32 i;

    for (i = 0; i < sizeof(struct Apprentice) / sizeof(u32); i++)
        ((u32 *)apprentice)[i] = 0;
    ResetApprenticeStruct(apprentice);
}

static void ValidateApprenticesChecksums(void)
{
    s32 i, j;

    for (i = 0; i < APPRENTICE_COUNT; i++)
    {
        u32 *data = (u32 *) &gSaveBlock2Ptr->apprentices[i];
        u32 checksum = 0;
        for (j = 0; j < offsetof(struct Apprentice, checksum) / sizeof(u32); j++)
            checksum += data[j];
        if (gSaveBlock2Ptr->apprentices[i].checksum != checksum)
            ClearApprentice(&gSaveBlock2Ptr->apprentices[i]);
    }
}

void GetBattleTowerTrainerLanguage(u8 *dst, u16 trainerId)
{
    if (trainerId == TRAINER_EREADER)
    {
        *dst = gGameLanguage;
    }
    else if (trainerId < FRONTIER_TRAINERS_COUNT)
    {
        *dst = gGameLanguage;
    }
    else
    {
        if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            *dst = GetRecordedBattleApprenticeLanguage();
    }
}

u8 SetFacilityPtrsGetLevel(void)
{
    if (gSaveBlock2Ptr->frontier.lvlMode == FRONTIER_LVL_TENT)
    {
        return SetTentPtrsGetLevel();
    }
    else
    {
        gFacilityTrainers = 0;
        gFacilityTrainerMons = gBattleFrontierMons;
        return GetFrontierEnemyMonLevel(gSaveBlock2Ptr->frontier.lvlMode);
    }
}

u8 GetFrontierEnemyMonLevel(u8 lvlMode)
{
    u8 level;

    switch (lvlMode)
    {
    default:
    case FRONTIER_LVL_50:
        level = FRONTIER_MAX_LEVEL_50;
        break;
    case FRONTIER_LVL_OPEN:
        level = GetHighestLevelInPlayerParty();
        if (level < FRONTIER_MIN_LEVEL_OPEN)
            level = FRONTIER_MIN_LEVEL_OPEN;
        break;
    }

    return level;
}

s32 GetHighestLevelInPlayerParty(void)
{
    s32 highestLevel = 0;
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL)
            && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG)
        {
            s32 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL);
            if (level > highestLevel)
                highestLevel = level;
        }
    }

    return highestLevel;
}

// Frontier Trainer parties are roughly scaled in difficulty with higher trainer IDs, so scale IVs as well
// Duplicated in Battle Dome as GetDomeTrainerMonIvs
static u8 GetFrontierTrainerFixedIvs(u16 trainerId)
{
    u8 fixedIv;

    if (trainerId <= FRONTIER_TRAINER_JILL)         // 0 - 99
        fixedIv = 3;
    else if (trainerId <= FRONTIER_TRAINER_CHLOE)   // 100 - 119
        fixedIv = 6;
    else if (trainerId <= FRONTIER_TRAINER_SOFIA)   // 120 - 139
        fixedIv = 9;
    else if (trainerId <= FRONTIER_TRAINER_JAZLYN)  // 140 - 159
        fixedIv = 12;
    else if (trainerId <= FRONTIER_TRAINER_ALISON)  // 160 - 179
        fixedIv = 15;
    else if (trainerId <= FRONTIER_TRAINER_LAMAR)   // 180 - 199
        fixedIv = 18;
    else if (trainerId <= FRONTIER_TRAINER_TESS)    // 200 - 219
        fixedIv = 21;
    else                                            // 220+ (- 299)
        fixedIv = MAX_PER_STAT_IVS;

    return fixedIv;
}

static u16 GetBattleTentTrainerId(void)
{
    u32 facility = VarGet(VAR_FRONTIER_FACILITY);

    if (facility == FRONTIER_FACILITY_PALACE)       // Verdanturf Tent; uses Palace mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_ARENA)   // Fallarbor Tent; uses Arena mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_FACTORY) // Slateport Tent; uses Factory mechanics
        return Random() % NUM_BATTLE_TENT_TRAINERS;
    else if (facility == FRONTIER_FACILITY_TOWER)
        return 0;
    else
        return 0;
}

static u8 SetTentPtrsGetLevel(void)
{
    u8 level = TENT_MIN_LEVEL;
    u32 facility = VarGet(VAR_FRONTIER_FACILITY);

    if (facility == FRONTIER_FACILITY_FACTORY)
    {
        gFacilityTrainers = 0;
        gFacilityTrainerMons = gSlateportBattleTentMons;
    }
    else if (facility == FRONTIER_FACILITY_PALACE)
    {
        gFacilityTrainers = 0;
        gFacilityTrainerMons = gVerdanturfBattleTentMons;
    }
    else if (facility == FRONTIER_FACILITY_ARENA)
    {
        gFacilityTrainers = 0;
        gFacilityTrainerMons = gFallarborBattleTentMons;
    }
    else
    {
        gFacilityTrainers = 0;
        gFacilityTrainerMons = gBattleFrontierMons;
    }

    level = GetHighestLevelInPlayerParty();
    if (level < TENT_MIN_LEVEL)
        level = TENT_MIN_LEVEL;

    return level;
}

static void SetNextBattleTentOpponent(void)
{
    s32 i;
    u16 trainerId;

    do
    {
        trainerId = GetBattleTentTrainerId();
        for (i = 0; i < gSaveBlock2Ptr->frontier.curChallengeBattleNum; i++)
        {
            if (gSaveBlock2Ptr->frontier.trainerIds[i] == trainerId)
                break;
        }
    } while (i != gSaveBlock2Ptr->frontier.curChallengeBattleNum);

    gTrainerBattleOpponent_A = trainerId;
    SetBattleFacilityTrainerGfxId(gTrainerBattleOpponent_A, 0);
    if (gSaveBlock2Ptr->frontier.curChallengeBattleNum + 1 < TENT_STAGES_PER_CHALLENGE)
       gSaveBlock2Ptr->frontier.trainerIds[gSaveBlock2Ptr->frontier.curChallengeBattleNum] = gTrainerBattleOpponent_A;
}

static void FillTentTrainerParty_(u16 trainerId, u8 firstMonId, u8 monCount)
{
    s32 i, j;
    u16 chosenMonIndices[MAX_FRONTIER_PARTY_SIZE];
    u8 level = SetTentPtrsGetLevel();
    u8 fixedIV = 0;
    u8 bfMonCount;
    const u16 *monSet = NULL;
    u32 otID = 0;
    u16 monId;

    monSet = gFacilityTrainers[gTrainerBattleOpponent_A].monSet;

    bfMonCount = 0;
    monId = monSet[bfMonCount];
    while (monId != 0xFFFF)
    {
        bfMonCount++;
        monId = monSet[bfMonCount];
        if (monId == 0xFFFF)
            break;
    }

    i = 0;
    otID = Random32();
    while (i != monCount)
    {
        u16 monId = monSet[Random() % bfMonCount];

        // Ensure this Pokémon species isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_SPECIES, NULL) == gFacilityTrainerMons[monId].species)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this Pokemon's held item isn't a duplicate.
        for (j = 0; j < i + firstMonId; j++)
        {
            if (GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE
             && GetMonData(&gEnemyParty[j], MON_DATA_HELD_ITEM, NULL) == gFacilityTrainerMons[monId].heldItem)
                break;
        }
        if (j != i + firstMonId)
            continue;

        // Ensure this exact Pokémon index isn't a duplicate. This check doesn't seem necessary
        // because the species and held items were already checked directly above.
        for (j = 0; j < i; j++)
        {
            if (chosenMonIndices[j] == monId)
                break;
        }
        if (j != i)
            continue;

        chosenMonIndices[i] = monId;
        CreateFacilityMon(&gFacilityTrainerMons[monId],
                level, fixedIV, otID, 0,
                &gEnemyParty[i + firstMonId]);

        // The Pokémon was successfully added to the trainer's party, so it's safe to move on to
        // the next party slot.
        i++;
    }
}

void TrySetLinkBattleTowerEnemyPartyLevel(void)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        s32 i;
        u8 enemyLevel = SetFacilityPtrsGetLevel();

        for (i = 0; i < PARTY_SIZE; i++)
        {
            u32 species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, NULL);
            if (species)
            {
                SetMonData(&gEnemyParty[i], MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[species].growthRate][enemyLevel]);
                CalculateMonStats(&gEnemyParty[i]);
            }
        }
    }
}
