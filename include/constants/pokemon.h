#ifndef GUARD_CONSTANTS_POKEMON_H
#define GUARD_CONSTANTS_POKEMON_H

enum PokemonTypes
{
    TYPE_NONE,
    TYPE_NORMAL,
    TYPE_FIGHTING,
    TYPE_FLYING,
    TYPE_POISON,
    TYPE_GROUND,
    TYPE_ROCK,
    TYPE_BUG,
    TYPE_GHOST,
    TYPE_STEEL,
    TYPE_MYSTERY,
    TYPE_FIRE,
    TYPE_WATER,
    TYPE_GRASS,
    TYPE_ELECTRIC,
    TYPE_PSYCHIC,
    TYPE_ICE,
    TYPE_DRAGON,
    TYPE_DARK,
    TYPE_FAIRY,
    TYPE_STELLAR,

    NUMBER_OF_MON_TYPES,
};

enum PokemonEggGroups
{
    EGG_GROUP_NONE,
    EGG_GROUP_MONSTER,
    EGG_GROUP_AMPHIBIOUS,
    EGG_GROUP_BUG,
    EGG_GROUP_FLYING,
    EGG_GROUP_FIELD,
    EGG_GROUP_FAIRY,
    EGG_GROUP_GRASS,
    EGG_GROUP_HUMAN_LIKE,
    EGG_GROUP_INVERTEBRATE,
    EGG_GROUP_MINERAL,
    EGG_GROUP_AMORPHOUS,
    EGG_GROUP_FISH,
    EGG_GROUP_UNIVERSAL,
    EGG_GROUP_DRAGON,
    EGG_GROUP_BABY,
};

#define GRUPOS_HUEVO_POR_POKEMON            2

enum NaturalezasPokemon
{
    NATURALEZA_OFENSIVA,
    NATURALEZA_DEFENSIVA,
    NATURALEZA_OFENSIVA_ESPECIAL,
    NATURALEZA_DEFENSIVA_ESPECIAL,
    NATURALEZA_RAPIDA,

    NATURALEZAS_TOTALES
};

enum PokemonStats
{
    STAT_HP,
    STAT_ATK,
    STAT_DEF,
    STAT_SPEED,
    STAT_SPATK,
    STAT_SPDEF,

    NUM_STATS
};

#define STAT_ACC     6 // Only in battles.
#define STAT_EVASION 7 // Only in battles.

#define NUM_NATURE_STATS (NUM_STATS - 1) // excludes HP
#define NUM_BATTLE_STATS (NUM_STATS + 2) // includes Accuracy and Evasion

#define MIN_STAT_STAGE     0
#define DEFAULT_STAT_STAGE 6
#define MAX_STAT_STAGE    12

// Shiny odds
#define SHINY_ODDS 128 //Probabilidad de 1/4096

//Limpiar
// Ribbon IDs used by TV and Pokénav
#define CHAMPION_RIBBON       0
#define COOL_RIBBON_NORMAL    1
#define COOL_RIBBON_SUPER     2
#define COOL_RIBBON_HYPER     3
#define COOL_RIBBON_MASTER    4
#define BEAUTY_RIBBON_NORMAL  5
#define BEAUTY_RIBBON_SUPER   6
#define BEAUTY_RIBBON_HYPER   7
#define BEAUTY_RIBBON_MASTER  8
#define CUTE_RIBBON_NORMAL    9
#define CUTE_RIBBON_SUPER    10
#define CUTE_RIBBON_HYPER    11
#define CUTE_RIBBON_MASTER   12
#define SMART_RIBBON_NORMAL  13
#define SMART_RIBBON_SUPER   14
#define SMART_RIBBON_HYPER   15
#define SMART_RIBBON_MASTER  16
#define TOUGH_RIBBON_NORMAL  17
#define TOUGH_RIBBON_SUPER   18
#define TOUGH_RIBBON_HYPER   19
#define TOUGH_RIBBON_MASTER  20
#define WINNING_RIBBON       21
#define VICTORY_RIBBON       22
#define ARTIST_RIBBON        23
#define EFFORT_RIBBON        24
#define MARINE_RIBBON        25
#define LAND_RIBBON          26
#define SKY_RIBBON           27
#define COUNTRY_RIBBON       28
#define NATIONAL_RIBBON      29
#define EARTH_RIBBON         30
#define WORLD_RIBBON         31

#define FIRST_GIFT_RIBBON MARINE_RIBBON
#define LAST_GIFT_RIBBON  WORLD_RIBBON
#define NUM_GIFT_RIBBONS  (1 + LAST_GIFT_RIBBON - FIRST_GIFT_RIBBON)

// The above gift ribbons (Marine - World) are
// special distribution ribbons that correspond to
// 1 bit each in the Pokémon struct. Gen 4 hard-codes
// each of these to the given name. In Gen 3 they're
// used to get an index into giftRibbons in the save block,
// which can have a value 0-64 (0 is 'no ribbon') that
// corresponds to one of the special ribbons listed
// in gGiftRibbonDescriptionPointers. Most of these were
// never distributed
#define MAX_GIFT_RIBBON 64

#define MIN_LEVEL 1
#define MAX_LEVEL 100

#define MAX_DYNAMAX_LEVEL 10

enum OtIds
{
    OT_ID_PLAYER_ID,
    OT_ID_PRESET,
    OT_ID_RANDOM_NO_SHINY,
};

enum MonReceivedWhereToGo
{
    MON_GIVEN_TO_PARTY,
    MON_GIVEN_TO_PC,
    MON_CANT_GIVE,
};

enum PlayerHasHowManyMons
{
    PLAYER_HAS_TWO_USABLE_MONS,
    PLAYER_HAS_ONE_MON,
    PLAYER_HAS_ONE_USABLE_MON,
};

#define MON_ALREADY_KNOWS_MOVE  0xFFFE
#define MON_HAS_MAX_MOVES       0xFFFF

#define LEVEL_UP_MOVE_ID   0x01FF
#define LEVEL_UP_MOVE_LV   0xFE00
#define LEVEL_UP_MOVE_END  0xFFFF

#define MAX_LEVEL_UP_MOVES       20

#define MON_MALE       0
#define MON_FEMALE     254
#define MON_GENDERLESS 255

enum FriendshipEvents
{
    FRIENDSHIP_EVENT_GROW_LEVEL,
    FRIENDSHIP_EVENT_LEAGUE_BATTLE,
    FRIENDSHIP_EVENT_LEARN_TMHM,
    FRIENDSHIP_EVENT_WALKING,
    FRIENDSHIP_EVENT_FAINT_SMALL,
    FRIENDSHIP_EVENT_FAINT_FIELD_PSN,
    FRIENDSHIP_EVENT_FAINT_LARGE,
};

// Constants for GetLeadMonFriendshipScore
enum Friendship
{
    FRIENDSHIP_NONE,
    FRIENDSHIP_1_TO_49,
    FRIENDSHIP_50_TO_99,
    FRIENDSHIP_100_TO_149,
    FRIENDSHIP_150_TO_199,
    FRIENDSHIP_200_TO_254,
    FRIENDSHIP_MAX,
};

//Fuera
// Constants for GetBattlerAffectionHearts (based on friendship value)
#define AFFECTION_NO_HEARTS     0 // 0-79 friendship
#define AFFECTION_ONE_HEART     1 // 80-129 friendship
#define AFFECTION_TWO_HEARTS    2 // 130-179 friendship
#define AFFECTION_THREE_HEARTS  3 // 180-219 friendship
#define AFFECTION_FOUR_HEARTS   4 // 220-254 friendship
#define AFFECTION_FIVE_HEARTS   5 // Max friendship

// Friendship value that the majority of species use.
#define STANDARD_FRIENDSHIP 50

#define MAX_FRIENDSHIP  255
#define MAX_SHEEN       255
#define MAX_CONDITION   255

#define MAX_PER_STAT_IVS 31
#define MAX_IV_MASK 31
#define USE_RANDOM_IVS (MAX_PER_STAT_IVS + 1)
#define MAX_PER_STAT_EVS 252
#define MAX_TOTAL_EVS 504
#define EV_ITEM_RAISE_LIMIT MAX_PER_STAT_EVS

enum DamageCategories
{
    DAMAGE_CATEGORY_PHYSICAL,
    DAMAGE_CATEGORY_SPECIAL,
    DAMAGE_CATEGORY_STATUS,
};

enum GrowthRates
{
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW,
};

//Fuera
// Body colors for Pokédex search
#define BODY_COLOR_RED      0
#define BODY_COLOR_BLUE     1
#define BODY_COLOR_YELLOW   2
#define BODY_COLOR_GREEN    3
#define BODY_COLOR_BLACK    4
#define BODY_COLOR_BROWN    5
#define BODY_COLOR_PURPLE   6
#define BODY_COLOR_GRAY     7
#define BODY_COLOR_WHITE    8
#define BODY_COLOR_PINK     9

#define F_SUMMARY_SCREEN_FLIP_SPRITE 128

#define EVOLUTIONS_END                    0xFFFF // Not an actual evolution, used to mark the end of an evolution array.
#define EVO_NONE                          0xFFFE // Not an actual evolution, used to generate offspring that can't evolve into the specified species, like regional forms.

//Chequear, y los que no se usen, fuera
enum EvolutionMethods
{
    EVO_FRIENDSHIP,                      // Pokémon levels up with friendship ≥ 220
    EVO_FRIENDSHIP_DAY,                  // Pokémon levels up during the day with friendship ≥ 220
    EVO_FRIENDSHIP_NIGHT,                // Pokémon levels up at night with friendship ≥ 220
    EVO_LEVEL,                           // Pokémon reaches the specified level
    EVO_TRADE,                           // Pokémon is traded
    EVO_TRADE_ITEM,                      // Pokémon is traded while it's holding the specified item
    EVO_ITEM,                            // specified item is used on Pokémon
    EVO_LEVEL_ATK_GT_DEF,                // Pokémon reaches the specified level with attack > defense
    EVO_LEVEL_ATK_EQ_DEF,                // Pokémon reaches the specified level with attack = defense
    EVO_LEVEL_ATK_LT_DEF,                // Pokémon reaches the specified level with attack < defense
    EVO_LEVEL_SILCOON,                   // Pokémon reaches the specified level with a Silcoon personality value
    EVO_LEVEL_CASCOON,                   // Pokémon reaches the specified level with a Cascoon personality value
    EVO_LEVEL_NINJASK,                   // Pokémon reaches the specified level (special value for Ninjask)
    EVO_LEVEL_SHEDINJA,                  // Pokémon reaches the specified level (special value for Shedinja)
    EVO_BEAUTY,                          // Pokémon levels up with beauty ≥ specified value
    EVO_LEVEL_FEMALE,                    // Pokémon reaches the specified level, is female
    EVO_LEVEL_MALE,                      // Pokémon reaches the specified level, is male
    EVO_LEVEL_NIGHT,                     // Pokémon reaches the specified level, is night
    EVO_LEVEL_DAY,                       // Pokémon reaches the specified level, is day
    EVO_LEVEL_DUSK,                      // Pokémon reaches the specified level, is dusk (5-6 P.M)
    EVO_ITEM_HOLD_DAY,                   // Pokémon levels up, holds specified item at day
    EVO_ITEM_HOLD_NIGHT,                 // Pokémon levels up, holds specified item at night
    EVO_MOVE,                            // Pokémon levels up, knows specified move
    EVO_FRIENDSHIP_MOVE_TYPE,            // Pokémon levels up with friendship ≥ 220, knows move with specified type
    EVO_MAPSEC,                          // Pokémon levels up on specified mapsec
    EVO_ITEM_MALE,                       // specified item is used on a male Pokémon
    EVO_ITEM_FEMALE,                     // specified item is used on a female Pokémon
    EVO_LEVEL_RAIN,                      // Pokémon reaches the specified level during rain in the overworld
    EVO_SPECIFIC_MON_IN_PARTY,           // Pokémon levels up with a specified Pokémon in party
    EVO_LEVEL_DARK_TYPE_MON_IN_PARTY,    // Pokémon reaches the specified level with a Dark Type Pokémon in party
    EVO_TRADE_SPECIFIC_MON,              // Pokémon is traded for a specified Pokémon
    EVO_SPECIFIC_MAP,                    // Pokémon levels up on specified map
    EVO_LEVEL_NATURE_AMPED,              // Pokémon reaches the specified level, it has a Hardy, Brave, Adamant, Naughty, Docile, Impish, Lax, Hasty, Jolly, Naive, Rash, Sassy, or Quirky nature.
    EVO_LEVEL_NATURE_LOW_KEY,            // Pokémon reaches the specified level, it has a Lonely, Bold, Relaxed, Timid, Serious, Modest, Mild, Quiet, Bashful, Calm, Gentle, or Careful nature.
    EVO_CRITICAL_HITS,                   // Pokémon performs specified number of critical hits in one battle
    EVO_SCRIPT_TRIGGER_DMG,              // Pokémon has specified HP below max, then player interacts trigger
    EVO_DARK_SCROLL,                     // interacts with Scroll of Darkness
    EVO_WATER_SCROLL,                    // interacts with Scroll of Waters
    EVO_ITEM_NIGHT,                      // specified item is used on Pokémon, is night
    EVO_ITEM_DAY,                        // specified item is used on Pokémon, is day
    EVO_ITEM_HOLD,                       // Pokémon levels up, holds specified item
    EVO_LEVEL_FOG,                       // Pokémon reaches the specified level during fog in the overworld
    EVO_MOVE_TWO_SEGMENT,                // Pokémon levels up, knows specified move, has a personality value with a modulus of 0
    EVO_MOVE_THREE_SEGMENT,              // Pokémon levels up, knows specified move, has a personality value with a modulus of 1-99
    EVO_LEVEL_FAMILY_OF_THREE,           // Pokémon reaches the specified level in battle with a personality value with a modulus of 0
    EVO_LEVEL_FAMILY_OF_FOUR,            // Pokémon reaches the specified level in battle with a personality value with a modulus of 1-99
    EVO_USE_MOVE_TWENTY_TIMES,           // Pokémon levels up after having used a move for at least 20 times
    EVO_RECOIL_DAMAGE_MALE,              // Pokémon levels up after having suffered specified amount of non-fainting recoil damage as a male
    EVO_RECOIL_DAMAGE_FEMALE,            // Pokémon levels up after having suffered specified amount of non-fainting recoil damage as a female
    EVO_ITEM_COUNT_999,                  // Pokémon levels up after trainer has collected 999 of a specific item
    EVO_DEFEAT_THREE_WITH_ITEM,          // Pokémon levels up after having defeat 3 Pokémon of the same species holding the specified item
    EVO_OVERWORLD_STEPS,                 // Pokémon levels up after having taken a specific amount of steps in the overworld
};

enum EvolutionMode
{
    EVO_MODE_NORMAL,
    EVO_MODE_CANT_STOP,
    EVO_MODE_TRADE,
    EVO_MODE_ITEM_USE,
    EVO_MODE_ITEM_CHECK,         // If an Everstone is being held, still want to show that the stone *could* be used on that Pokémon to evolve
    EVO_MODE_BATTLE_SPECIAL,
    EVO_MODE_OVERWORLD_SPECIAL,
    EVO_MODE_BATTLE_ONLY,        // This mode is only used in battles to support Tandemaus' unique requirement
};

#define MON_PIC_WIDTH 64
#define MON_PIC_HEIGHT 64
#define MON_PIC_SIZE (MON_PIC_WIDTH * MON_PIC_HEIGHT / 2)
#define MAX_MON_PIC_FRAMES 2

#define BATTLE_ALIVE_EXCEPT_BATTLER  0
#define BATTLE_ALIVE_SIDE            1

#define SKIP_FRONT_ANIM (1 << 7)

#define NUM_ABILITY_SLOTS (NUM_NORMAL_ABILITY_SLOTS + NUM_HIDDEN_ABILITY_SLOTS)
#define NUM_NORMAL_ABILITY_SLOTS 2
#define NUM_HIDDEN_ABILITY_SLOTS 1

// Used as a signal for givemon to generate a default ability by personality.
#define NUM_ABILITY_PERSONALITY 0xFF

#endif // GUARD_CONSTANTS_POKEMON_H
