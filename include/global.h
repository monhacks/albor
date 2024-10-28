#ifndef GUARD_GLOBAL_H
#define GUARD_GLOBAL_H

#include <string.h>
#include <limits.h>
#include "config/general.h" // we need to define config before gba headers as print stuff needs the functions nulled before defines.
#include "gba/gba.h"
#include "fpmath.h"
#include "metaprogram.h"
#include "constants/global.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/species.h"
#include "constants/pokedex.h"
#include "constants/berry.h"
#include "constants/maps.h"
#include "constants/pokemon.h"
#include "constants/easy_chat.h"
#include "constants/trainer_hill.h"
#include "constants/items.h"
#include "config/save.h"

// Prevent cross-jump optimization.
#define BLOCK_CROSS_JUMP asm("");

// to help in decompiling
#define asm_unified(x) asm(".syntax unified\n" x "\n.syntax divided")
#define NAKED __attribute__((naked))

/// IDE support
#if defined(__APPLE__) || defined(__CYGWIN__) || defined(__INTELLISENSE__)
// We define these when using certain IDEs to fool preproc
#define _(x)        {x}
#define __(x)       {x}
#define INCBIN(...) {0}
#define INCBIN_U8   INCBIN
#define INCBIN_U16  INCBIN
#define INCBIN_U32  INCBIN
#define INCBIN_S8   INCBIN
#define INCBIN_S16  INCBIN
#define INCBIN_S32  INCBIN
#define INCBIN_COMP INCBIN
#endif // IDE support

#define ARRAY_COUNT(array) (size_t)(sizeof(array) / sizeof((array)[0]))

// GameFreak used a macro called "NELEMS", as evidenced by
// AgbAssert calls.
#define NELEMS(arr) (sizeof(arr)/sizeof(*(arr)))

#define SWAP(a, b, temp)    \
{                           \
    temp = a;               \
    a = b;                  \
    b = temp;               \
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

#if MODERN
#define abs(x) (((x) < 0) ? -(x) : (x))
#endif

// Used in cases where division by 0 can occur in the retail version.
// Avoids invalid opcodes on some emulators, and the otherwise UB.
#ifdef UBFIX
#define SAFE_DIV(a, b) (((b) != 0) ? (a) / (b) : 0)
#else
#define SAFE_DIV(a, b) ((a) / (b))
#endif

#define IS_POW_OF_TWO(n) (((n) & ((n)-1)) == 0)

// The below macro does a%n, but (to match) will switch to a&(n-1) if n is a power of 2.
// There are cases where GF does a&(n-1) where we would really like to have a%n, because
// if n is changed to a value that isn't a power of 2 then a&(n-1) is unlikely to work as
// intended, and a%n for powers of 2 isn't always optimized to use &.
#define MOD(a, n) (((n) & ((n)-1)) ? ((a) % (n)) : ((a) & ((n)-1)))

// Extracts the upper 16 bits of a 32-bit number
#define HIHALF(n) (((n) & 0xFFFF0000) >> 16)

// Extracts the lower 16 bits of a 32-bit number
#define LOHALF(n) ((n) & 0xFFFF)

// There are many quirks in the source code which have overarching behavioral differences from
// a number of other files. For example, diploma.c seems to declare rodata before each use while
// other files declare out of order and must be at the beginning. There are also a number of
// macros which differ from one file to the next due to the method of obtaining the result, such
// as these below. Because of this, there is a theory (Two Team Theory) that states that these
// programming projects had more than 1 "programming team" which utilized different macros for
// each of the files that were worked on.
#define T1_READ_8(ptr)  ((ptr)[0])
#define T1_READ_16(ptr) ((ptr)[0] | ((ptr)[1] << 8))
#define T1_READ_32(ptr) ((ptr)[0] | ((ptr)[1] << 8) | ((ptr)[2] << 16) | ((ptr)[3] << 24))
#define T1_READ_PTR(ptr) (u8 *) T1_READ_32(ptr)

// T2_READ_8 is a duplicate to remain consistent with each group.
#define T2_READ_8(ptr)  ((ptr)[0])
#define T2_READ_16(ptr) ((ptr)[0] + ((ptr)[1] << 8))
#define T2_READ_32(ptr) ((ptr)[0] + ((ptr)[1] << 8) + ((ptr)[2] << 16) + ((ptr)[3] << 24))
#define T2_READ_PTR(ptr) (void *) T2_READ_32(ptr)

// Macros for checking the joypad
#define TEST_BUTTON(field, button) ((field) & (button))
#define JOY_NEW(button) TEST_BUTTON(gMain.newKeys,  button)
#define JOY_HELD(button)  TEST_BUTTON(gMain.heldKeys, button)
#define JOY_HELD_RAW(button) TEST_BUTTON(gMain.heldKeysRaw, button)
#define JOY_REPEAT(button) TEST_BUTTON(gMain.newAndRepeatedKeys, button)

#define S16TOPOSFLOAT(val)   \
({                           \
    s16 v = (val);           \
    float f = (float)v;      \
    if(v < 0) f += 65536.0f; \
    f;                       \
})

#define DIV_ROUND_UP(val, roundBy) (((val) / (roundBy)) + (((val) % (roundBy)) ? 1 : 0))

#define ROUND_BITS_TO_BYTES(numBits) DIV_ROUND_UP(numBits, 8)

#define NUM_DEX_FLAG_BYTES ROUND_BITS_TO_BYTES(DEX_COUNT)
#define NUM_FLAG_BYTES ROUND_BITS_TO_BYTES(FLAGS_COUNT)
#define NUM_TRENDY_SAYING_BYTES ROUND_BITS_TO_BYTES(NUM_TRENDY_SAYINGS)

// This produces an error at compile-time if expr is zero.
// It looks like file.c:line: size of array `id' is negative
#define STATIC_ASSERT(expr, id) typedef char id[(expr) ? 1 : -1];

#define FEATURE_FLAG_ASSERT(flag, id) STATIC_ASSERT(flag > TEMP_FLAGS_END || flag == 0, id)

#ifndef NDEBUG
static inline void CycleCountStart()
{
    REG_TM2CNT_H = 0;
    REG_TM3CNT_H = 0;

    REG_TM2CNT_L = 0;
    REG_TM3CNT_L = 0;

    // init timers (tim3 count up mode, tim2 every clock cycle)
    REG_TM3CNT_H = TIMER_ENABLE | TIMER_COUNTUP;
    REG_TM2CNT_H = TIMER_1CLK | TIMER_ENABLE;
}

static inline u32 CycleCountEnd()
{
    // stop timers
    REG_TM2CNT_H = 0;
    REG_TM3CNT_H = 0;

    // return result
    return REG_TM2CNT_L | (REG_TM3CNT_L << 16u);
}
#endif

struct Coords8
{
    s8 x;
    s8 y;
};

struct UCoords8
{
    u8 x;
    u8 y;
};

struct Coords16
{
    s16 x;
    s16 y;
};

struct UCoords16
{
    u16 x;
    u16 y;
};

struct UCoords32
{
    u32 x;
    u32 y;
};

struct Time
{
    /*0x00*/ s16 days;
    /*0x02*/ s8 hours;
    /*0x03*/ s8 minutes;
    /*0x04*/ s8 seconds;
};

struct Pokedex
{
    /*0x00*/ u32 order;
};

struct PyramidBag
{
    u16 itemId[FRONTIER_LVL_MODE_COUNT][PYRAMID_BAG_ITEMS_COUNT];
#if MAX_PYRAMID_BAG_ITEM_CAPACITY > 255
    u16 quantity[FRONTIER_LVL_MODE_COUNT][PYRAMID_BAG_ITEMS_COUNT];
#else
    u8 quantity[FRONTIER_LVL_MODE_COUNT][PYRAMID_BAG_ITEMS_COUNT];
#endif
};

struct ApprenticeMon
{
    u16 species;
    u16 moves[MAX_MON_MOVES];
    u16 item;
};

// This is for past players Apprentices or Apprentices received via Record Mix.
// For the current Apprentice, see struct PlayersApprentice
struct Apprentice
{
    u8 id:5;
    u8 lvlMode:2;
    u8 numQuestions;
    u8 number;
    struct ApprenticeMon party[MULTI_PARTY_SIZE];
    u16 speechWon[EASY_CHAT_BATTLE_WORDS_COUNT];
    u8 playerId[TRAINER_ID_LENGTH];
    u8 playerName[PLAYER_NAME_LENGTH];
    u8 language;
    u32 checksum;
};

struct BattleTowerPokemon
{
    u16 species;
    u16 heldItem;
    u16 moves[MAX_MON_MOVES];
    u8 level;
    u8 ppBonuses;
    u8 hpEV;
    u8 attackEV;
    u8 defenseEV;
    u8 speedEV;
    u8 spAttackEV;
    u8 spDefenseEV;
    u32 otId;
    u32 hpIV:5;
    u32 attackIV:5;
    u32 defenseIV:5;
    u32 speedIV:5;
    u32 spAttackIV:5;
    u32 spDefenseIV:5;
    u32 gap:1;
    u32 abilityNum:1;
    u32 personality;
    u8 nickname[VANILLA_POKEMON_NAME_LENGTH + 1];
    u8 friendship;
};

struct BattleTowerInterview
{
    u16 playerSpecies;
    u16 opponentSpecies;
    u8 opponentName[PLAYER_NAME_LENGTH + 1];
    u8 opponentMonNickname[VANILLA_POKEMON_NAME_LENGTH + 1];
    u8 opponentLanguage;
};

struct BattleTowerEReaderTrainer
{
    /*0x00*/ u8 unk0;
    /*0x01*/ u8 facilityClass;
    /*0x02*/ u16 winStreak;
    /*0x04*/ u8 name[PLAYER_NAME_LENGTH + 1];
    /*0x0C*/ u8 trainerId[TRAINER_ID_LENGTH];
    /*0x10*/ u16 greeting[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x1C*/ u16 farewellPlayerLost[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x28*/ u16 farewellPlayerWon[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x34*/ struct BattleTowerPokemon party[FRONTIER_PARTY_SIZE];
    /*0xB8*/ u32 checksum;
};

// For displaying party information on the player's Battle Dome tourney page
struct DomeMonData
{
    u16 moves[MAX_MON_MOVES];
    u8 evs[NUM_STATS];
    u8 nature;
};

struct RentalMon
{
    u16 monId;
    u32 personality;
    u8 ivs;
    u8 abilityNum;
};

struct BattleDomeTrainer
{
    u16 trainerId:10;
    u16 isEliminated:1;
    u16 eliminatedAt:2;
    u16 forfeited:3;
};

#define DOME_TOURNAMENT_TRAINERS_COUNT 16

struct BattleFrontier
{
    /*0xBEB*/ struct BattleTowerInterview towerInterview;
    /*0xCA8*/ u8 challengeStatus;
    /*0xCA9*/ u8 lvlMode:2;
              u8 challengePaused:1;
              u8 disableRecordBattle:1;
    /*0xCAA*/ u16 selectedPartyMons[MAX_FRONTIER_PARTY_SIZE];
    /*0xCB2*/ u16 curChallengeBattleNum; // Battle number / room number (Pike) / floor number (Pyramid)
    /*0xCB4*/ u16 trainerIds[20];
    /*0xCDC*/ u32 winStreakActiveFlags;
    /*0xCE0*/ u16 towerWinStreaks[4][FRONTIER_LVL_MODE_COUNT];
    /*0xCF0*/ u16 towerRecordWinStreaks[4][FRONTIER_LVL_MODE_COUNT];
    /*0xD00*/ u16 battledBrainFlags;
    /*0xD06*/ u8 towerBattleOutcome;
    /*0xD07*/ u8 towerLvlMode;
    /*0xD08*/ u8 domeAttemptedSingles50:1;
    /*0xD08*/ u8 domeAttemptedSinglesOpen:1;
    /*0xD08*/ u8 domeHasWonSingles50:1;
    /*0xD08*/ u8 domeHasWonSinglesOpen:1;
    /*0xD08*/ u8 domeAttemptedDoubles50:1;
    /*0xD08*/ u8 domeAttemptedDoublesOpen:1;
    /*0xD08*/ u8 domeHasWonDoubles50:1;
    /*0xD08*/ u8 domeHasWonDoublesOpen:1;
    /*0xD0A*/ u8 domeLvlMode;
    /*0xD0B*/ u8 domeBattleMode;
    /*0xD0C*/ u16 domeWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xD14*/ u16 domeRecordWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xD1C*/ u16 domeTotalChampionships[2][FRONTIER_LVL_MODE_COUNT];
    /*0xD24*/ struct BattleDomeTrainer domeTrainers[DOME_TOURNAMENT_TRAINERS_COUNT];
    /*0xD64*/ u16 domeMonIds[DOME_TOURNAMENT_TRAINERS_COUNT][FRONTIER_PARTY_SIZE];
    /*0xDC6*/ u16 palacePrize;
    /*0xDC8*/ u16 palaceWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xDD0*/ u16 palaceRecordWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xDD8*/ u16 arenaPrize;
    /*0xDDA*/ u16 arenaWinStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xDDE*/ u16 arenaRecordStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xDE2*/ u16 factoryWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xDEA*/ u16 factoryRecordWinStreaks[2][FRONTIER_LVL_MODE_COUNT];
    /*0xDF6*/ u16 factoryRentsCount[2][FRONTIER_LVL_MODE_COUNT];
    /*0xDFA*/ u16 factoryRecordRentsCount[2][FRONTIER_LVL_MODE_COUNT];
    /*0xE02*/ u16 pikePrize;
    /*0xE04*/ u16 pikeWinStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xE08*/ u16 pikeRecordStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xE0C*/ u16 pikeTotalStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xE10*/ u8 pikeHintedRoomIndex:3;
              u8 pikeHintedRoomType:4;
              u8 pikeHealingRoomsDisabled:1;
    /*0xE12*/ u16 pikeHeldItemsBackup[FRONTIER_PARTY_SIZE];
    /*0xE18*/ u16 pyramidPrize;
    /*0xE1A*/ u16 pyramidWinStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xE1E*/ u16 pyramidRecordStreaks[FRONTIER_LVL_MODE_COUNT];
    /*0xE22*/ u16 pyramidRandoms[4];
    /*0xE2A*/ u8 pyramidTrainerFlags; // 1 bit for each trainer (MAX_PYRAMID_TRAINERS)
    /*0xE2C*/ struct PyramidBag pyramidBag;
    /*0xE68*/ u8 pyramidLightRadius;
    /*0xE6A*/ u16 verdanturfTentPrize;
    /*0xE6C*/ u16 fallarborTentPrize;
    /*0xE6E*/ u16 slateportTentPrize;
    /*0xE70*/ struct RentalMon rentalMons[FRONTIER_PARTY_SIZE * 2];
    /*0xEB8*/ u16 battlePoints;
    /*0xEBA*/ u16 cardBattlePoints;
    /*0xEBC*/ u32 battlesCount;
    /*0xEC0*/ u16 domeWinningMoves[DOME_TOURNAMENT_TRAINERS_COUNT];
    /*0xEE0*/ u8 trainerFlags;
    /*0xEE1*/ u8 opponentNames[FRONTIER_LVL_MODE_COUNT][PLAYER_NAME_LENGTH + 1];
    /*0xEF1*/ u8 opponentTrainerIds[FRONTIER_LVL_MODE_COUNT][TRAINER_ID_LENGTH];
    /*0xEF9*/ u8 savedGame:1;
    /*0xEFC*/ struct DomeMonData domePlayerPartyData[FRONTIER_PARTY_SIZE];
};

struct ApprenticeQuestion
{
    u8 questionId:2;
    u8 monId:2;
    u8 moveSlot:2;
    u8 suggestedChange:2; // TRUE if told to use held item or second move, FALSE if told to use no item or first move
    u16 data; // used both as an itemId and a moveId
};

struct PlayersApprentice
{
    /*0xB0*/ u8 id;
    /*0xB1*/ u8 lvlMode:2;  //0: Unassigned, 1: Lv 50, 2: Open Lv
    /*0xB1*/ u8 questionsAnswered:4;
    /*0xB1*/ u8 leadMonId:2;
    /*0xB2*/ u8 party:3;
             u8 saveId:2;
    /*0xB4*/ u8 speciesIds[MULTI_PARTY_SIZE];
    /*0xB8*/ struct ApprenticeQuestion questions[APPRENTICE_MAX_QUESTIONS];
};

#include "constants/items.h"
#define ITEM_FLAGS_COUNT ((ITEMS_COUNT / 8) + ((ITEMS_COUNT % 8) ? 1 : 0))

struct SaveBlock2
{
    /*0x00*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x08*/ u8 playerGender; // MALE, FEMALE
    /*0x09*/ u8 specialSaveWarpFlags;
    /*0x0A*/ u8 playerTrainerId[TRAINER_ID_LENGTH];
    /*0x0E*/ u16 playTimeHours;
    /*0x10*/ u8 playTimeMinutes;
    /*0x11*/ u8 playTimeSeconds;
    /*0x12*/ u8 playTimeVBlanks;
    /*0x13*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A] //modificar
    /*0x14*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
             u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
             u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
             u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
             u16 optionsBattleSceneOff:1; // whether battle animations are disabled
             u16 regionMapZoom:1; // whether the map is zoomed in
    /*0x18*/ struct Pokedex pokedex;
    /*0x98*/ struct Time localTimeOffset;
    /*0xA0*/ struct Time lastBerryTreeUpdate;
    /*0xB0*/ struct PlayersApprentice playerApprentice; //eliminar
    /*0xDC*/ struct Apprentice apprentices[APPRENTICE_COUNT]; //eliminar
    /*0x64C*/ struct BattleFrontier frontier; //eliminar
    struct Time fakeRTC;
    u8 itemFlags[ITEM_FLAGS_COUNT];
};

extern struct SaveBlock2 *gSaveBlock2Ptr;

extern u8 UpdateSpritePaletteWithTime(u8);

struct SecretBaseParty
{
    u32 personality[PARTY_SIZE];
    u16 moves[PARTY_SIZE * MAX_MON_MOVES];
    u16 species[PARTY_SIZE];
    u16 heldItems[PARTY_SIZE];
    u8 levels[PARTY_SIZE];
    u8 EVs[PARTY_SIZE];
};

struct SecretBase
{
    /*0x1A9C*/ u8 secretBaseId;
    /*0x1A9D*/ bool8 toRegister:4;
    /*0x1A9D*/ u8 gender:1;
    /*0x1A9D*/ u8 battledOwnerToday:1;
    /*0x1A9D*/ u8 registryStatus:2;
    /*0x1A9E*/ u8 trainerName[PLAYER_NAME_LENGTH];
    /*0x1AA5*/ u8 trainerId[TRAINER_ID_LENGTH]; // byte 0 is used for determining trainer class
    /*0x1AA9*/ u8 language;
    /*0x1AAA*/ u16 numSecretBasesReceived;
    /*0x1AAC*/ u8 numTimesEntered;
    /*0x1AAE*/ u8 decorations[DECOR_MAX_SECRET_BASE];
    /*0x1ABE*/ u8 decorationPositions[DECOR_MAX_SECRET_BASE];
    /*0x1AD0*/ struct SecretBaseParty party;
};

#include "constants/game_stat.h"
#include "global.fieldmap.h"
#include "global.berry.h"
#include "pokemon.h"

struct WarpData
{
    s8 mapGroup;
    s8 mapNum;
    s8 warpId;
    s16 x, y;
};

struct ItemSlot
{
    u16 itemId;
    u16 quantity;
};

struct Pokeblock
{
    u8 color;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 feel;
};

struct Roamer
{
    /*0x00*/ u32 ivs;
    /*0x04*/ u32 personality;
    /*0x08*/ u16 species;
    /*0x0A*/ u16 hp;
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 statusA;
    /*0x0E*/ u8 cool;
    /*0x0F*/ u8 beauty;
    /*0x10*/ u8 cute;
    /*0x11*/ u8 smart;
    /*0x12*/ u8 tough;
    /*0x13*/ bool8 active;
    /*0x14*/ u8 statusB; // Stores frostbite
    /*0x14*/ u8 filler[0x7];
};

// See dewford_trend.c
struct DewfordTrend
{
    u16 trendiness:7;
    u16 maxTrendiness:7;
    u16 gainingTrendiness:1;
    u16 rand;
    u16 words[2];
}; /*size = 0x8*/

struct MauvilleManCommon
{
    u8 id;
};

struct MauvilleManBard
{
    /*0x00*/ u8 id;
    /*0x02*/ u16 songLyrics[BARD_SONG_LENGTH];
    /*0x0E*/ u16 temporaryLyrics[BARD_SONG_LENGTH];
    /*0x1A*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x25*/ u8 playerTrainerId[TRAINER_ID_LENGTH];
    /*0x29*/ bool8 hasChangedSong;
    /*0x2A*/ u8 language;
}; /*size = 0x2C*/

struct MauvilleManStoryteller
{
    u8 id;
    bool8 alreadyRecorded;
    u8 gameStatIDs[NUM_STORYTELLER_TALES];
    u8 trainerNames[NUM_STORYTELLER_TALES][PLAYER_NAME_LENGTH];
    u8 statValues[NUM_STORYTELLER_TALES][4];
    u8 language[NUM_STORYTELLER_TALES];
};

struct MauvilleManGiddy
{
    /*0x00*/ u8 id;
    /*0x01*/ u8 taleCounter;
    /*0x02*/ u8 questionNum;
    /*0x04*/ u16 randomWords[GIDDY_MAX_TALES];
    /*0x18*/ u8 questionList[GIDDY_MAX_QUESTIONS];
    /*0x20*/ u8 language;
}; /*size = 0x2C*/

struct MauvilleManHipster
{
    u8 id;
    bool8 taughtWord;
    u8 language;
};

struct MauvilleOldManTrader
{
    u8 id;
    u8 decorations[NUM_TRADER_ITEMS];
    u8 playerNames[NUM_TRADER_ITEMS][11];
    u8 alreadyTraded;
    u8 language[NUM_TRADER_ITEMS];
};

typedef union OldMan
{
    struct MauvilleManCommon common;
    struct MauvilleManBard bard;
    struct MauvilleManGiddy giddy;
    struct MauvilleManHipster hipster;
    struct MauvilleOldManTrader trader;
    struct MauvilleManStoryteller storyteller;
} OldMan;

struct ContestWinner
{
    u32 personality;
    u32 trainerId;
    u16 species;
    u8 contestCategory;
    u8 monName[VANILLA_POKEMON_NAME_LENGTH + 1];
    u8 trainerName[PLAYER_NAME_LENGTH + 1];
    u8 contestRank:7;
    bool8 isShiny:1;
};

struct Mail
{
    /*0x00*/ u16 words[MAIL_WORDS_COUNT];
    /*0x12*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x1A*/ u8 trainerId[TRAINER_ID_LENGTH];
    /*0x1E*/ u16 species;
    /*0x20*/ u16 itemId;
};

struct DaycareMail
{
    struct Mail message;
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u8 monName[VANILLA_POKEMON_NAME_LENGTH + 1];
    u8 gameLanguage:4;
    u8 monLanguage:4;
};

struct DaycareMon
{
    struct BoxPokemon mon;
    struct DaycareMail mail;
    u32 steps;
};

struct DayCare
{
    struct DaycareMon mons[DAYCARE_MON_COUNT];
    u32 offspringPersonality;
    u8 stepCounter;
};

struct LilycoveLadyQuiz
{
    /*0x000*/ u8 id;
    /*0x001*/ u8 state;
    /*0x002*/ u16 question[QUIZ_QUESTION_LEN];
    /*0x014*/ u16 correctAnswer;
    /*0x016*/ u16 playerAnswer;
    /*0x018*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x020*/ u16 playerTrainerId[TRAINER_ID_LENGTH];
    /*0x028*/ u16 prize;
    /*0x02A*/ bool8 waitingForChallenger;
    /*0x02B*/ u8 questionId;
    /*0x02C*/ u8 prevQuestionId;
    /*0x02D*/ u8 language;
};

struct LilycoveLadyFavor
{
    /*0x000*/ u8 id;
    /*0x001*/ u8 state;
    /*0x002*/ bool8 likedItem;
    /*0x003*/ u8 numItemsGiven;
    /*0x004*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x00C*/ u8 favorId;
    /*0x00E*/ u16 itemId;
    /*0x010*/ u16 bestItem;
    /*0x012*/ u8 language;
};

struct LilycoveLadyContest
{
    /*0x000*/ u8 id;
    /*0x001*/ bool8 givenPokeblock;
    /*0x002*/ u8 numGoodPokeblocksGiven;
    /*0x003*/ u8 numOtherPokeblocksGiven;
    /*0x004*/ u8 playerName[PLAYER_NAME_LENGTH + 1];
    /*0x00C*/ u8 maxSheen;
    /*0x00D*/ u8 category;
    /*0x00E*/ u8 language;
};

typedef union // 3b58
{
    struct LilycoveLadyQuiz quiz;
    struct LilycoveLadyFavor favor;
    struct LilycoveLadyContest contest;
    u8 id;
} LilycoveLady;

struct TrainerNameRecord
{
    u32 trainerId;
    u8 ALIGNED(2) trainerName[PLAYER_NAME_LENGTH + 1];
};

struct TrainerHillSave
{
    /*0x3D64*/ u32 timer;
    /*0x3D68*/ u32 bestTime;
    /*0x3D6E*/ u16 receivedPrize:1;
               u16 checkedFinalTime:1;
               u16 spokeToOwner:1;
               u16 hasLost:1;
               u16 maybeECardScanDuringChallenge:1;
               u16 field_3D6E_0f:1;
               u16 mode:2; // HILL_MODE_*
};

struct SaveBlock1
{
    /*0x00*/ struct Coords16 pos;
    /*0x04*/ struct WarpData location;
    /*0x0C*/ struct WarpData continueGameWarp;
    /*0x14*/ struct WarpData dynamicWarp;
    /*0x1C*/ struct WarpData lastHealLocation; // used by white-out and teleport
    /*0x24*/ struct WarpData escapeWarp; // used by Dig and Escape Rope
    /*0x2C*/ u16 savedMusic;
    /*0x2E*/ u8 weather;
    /*0x2F*/ u8 weatherCycleStage;
    /*0x30*/ u8 flashLevel;
    /*0x32*/ u16 mapLayoutId;
    /*0x34*/ u16 mapView[0x100];
    /*0x234*/ u8 playerPartyCount;
    /*0x238*/ struct Pokemon playerParty[PARTY_SIZE];
    /*0x490*/ u32 money;
    /*0x494*/ u16 coins; //eliminar?
    /*0x496*/ u16 registeredItem; // registered for use with SELECT button //eliminar?
    /*0x560*/ struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    /*0x5D8*/ struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT]; //modificar
    /*0x650*/ struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    /*0x690*/ struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT]; //modificar
    /*0x790*/ struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    /*0x848*/ struct Pokeblock pokeblocks[POKEBLOCKS_COUNT]; //eliminar
    /*0xA30*/ struct ObjectEvent objectEvents[OBJECT_EVENTS_COUNT];
    /*0xC70*/ struct ObjectEventTemplate objectEventTemplates[OBJECT_EVENT_TEMPLATES_COUNT];
    /*0x1270*/ u8 flags[NUM_FLAG_BYTES];
    /*0x139C*/ u16 vars[VARS_COUNT];
    /*0x159C*/ u32 gameStats[NUM_GAME_STATS];
    /*0x169C*/ struct BerryTree berryTrees[BERRY_TREES_COUNT];
    /*0x1A9C*/ struct SecretBase secretBases[SECRET_BASES_COUNT]; //eliminar
    /*0x271C*/ u8 playerRoomDecorations[DECOR_MAX_PLAYERS_HOUSE]; //eliminar
    /*0x2728*/ u8 playerRoomDecorationPositions[DECOR_MAX_PLAYERS_HOUSE]; //eliminar
    /*0x2734*/ u8 decorationDesks[10]; //eliminar
    /*0x273E*/ u8 decorationChairs[10]; //eliminar
    /*0x2748*/ u8 decorationPlants[10]; //eliminar
    /*0x2752*/ u8 decorationOrnaments[30]; //eliminar
    /*0x2770*/ u8 decorationMats[30]; //eliminar
    /*0x278E*/ u8 decorationPosters[10]; //eliminar
    /*0x2798*/ u8 decorationDolls[40]; //eliminar
    /*0x27C0*/ u8 decorationCushions[10]; //eliminar
    /*0x2B90*/ u16 outbreakPokemonSpecies;
    /*0x2B92*/ u8 outbreakLocationMapNum;
    /*0x2B93*/ u8 outbreakLocationMapGroup;
    /*0x2B94*/ u8 outbreakPokemonLevel;
    /*0x2B98*/ u16 outbreakPokemonMoves[MAX_MON_MOVES]; //???
    /*0x2BA1*/ u8 outbreakPokemonProbability; //???
    /*0x2BA2*/ u16 outbreakDaysLeft; //???
    /*0x2BB0*/ u16 easyChatProfile[EASY_CHAT_BATTLE_WORDS_COUNT]; //eliminar
    /*0x2BBC*/ u16 easyChatBattleStart[EASY_CHAT_BATTLE_WORDS_COUNT]; //eliminar
    /*0x2BC8*/ u16 easyChatBattleWon[EASY_CHAT_BATTLE_WORDS_COUNT]; //eliminar
    /*0x2BD4*/ u16 easyChatBattleLost[EASY_CHAT_BATTLE_WORDS_COUNT]; //eliminar
    /*0x2BE0*/ struct Mail mail[MAIL_COUNT]; //eliminar
    /*0x2E20*/ u8 unlockedTrendySayings[NUM_TRENDY_SAYING_BYTES]; //eliminar
    /*0x2E28*/ OldMan oldMan; //eliminar
    /*0x2e64*/ struct DewfordTrend dewfordTrends[SAVED_TRENDS_COUNT]; //eliminar
    /*0x2e90*/ struct ContestWinner contestWinners[NUM_CONTEST_WINNERS];  //eliminar
    /*0x3030*/ struct DayCare daycare;
    /*0x31A8*/ u8 giftRibbons[GIFT_RIBBONS_COUNT]; //eliminar
    /*0x31DC*/ struct Roamer roamer[ROAMER_COUNT]; //eliminar
    /*0x3???*/ u8 dexSeen[NUM_DEX_FLAG_BYTES];
    /*0x3???*/ u8 dexCaught[NUM_DEX_FLAG_BYTES];
    /*0x3???*/ LilycoveLady lilycoveLady; //eliminar
    /*0x3???*/ struct TrainerNameRecord trainerNameRecords[20]; //eliminar
    // sizeof: 0x3???
};

extern struct SaveBlock1* gSaveBlock1Ptr;

struct MapPosition
{
    s16 x;
    s16 y;
    s8 elevation;
};

#endif // GUARD_GLOBAL_H
