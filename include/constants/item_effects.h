#ifndef GUARD_CONSTANTS_ITEM_EFFECTS_H
#define GUARD_CONSTANTS_ITEM_EFFECTS_H

enum ItemEffects
{
    ITEM_EFFECT_NONE,
    ITEM_EFFECT_X_ITEM,
    ITEM_EFFECT_RAISE_LEVEL,
    ITEM_EFFECT_HEAL_HP,
    ITEM_EFFECT_CURE_POISON,
    ITEM_EFFECT_CURE_SLEEP,
    ITEM_EFFECT_CURE_BURN,
    ITEM_EFFECT_CURE_FREEZE_FROSTBITE,
    ITEM_EFFECT_CURE_PARALYSIS,
    ITEM_EFFECT_CURE_CONFUSION,
    ITEM_EFFECT_CURE_INFATUATION,
    ITEM_EFFECT_SACRED_ASH,
    ITEM_EFFECT_CURE_ALL_STATUS,
    ITEM_EFFECT_ATK_EV,
    ITEM_EFFECT_HP_EV,
    ITEM_EFFECT_SPATK_EV,
    ITEM_EFFECT_SPDEF_EV,
    ITEM_EFFECT_SPEED_EV,
    ITEM_EFFECT_DEF_EV,
    ITEM_EFFECT_EVO_STONE,
    ITEM_EFFECT_PP_UP,
    ITEM_EFFECT_PP_MAX,
    ITEM_EFFECT_HEAL_PP,
};

// field 0 masks
#define ITEM0_DIRE_HIT          48 // Works the same way as the move Focus Energy.
#define ITEM0_SACRED_ASH        64
#define ITEM0_INFATUATION       128

// new field 1 masks
#define ITEM1_X_ATTACK          STAT_ATK
#define ITEM1_X_DEFENSE         STAT_DEF
#define ITEM1_X_SPEED           STAT_SPEED
#define ITEM1_X_SPATK           STAT_SPATK
#define ITEM1_X_SPDEF           STAT_SPDEF
#define ITEM1_X_ACCURACY        STAT_ACC

// field 3 masks
#define ITEM3_CONFUSION         1
#define ITEM3_PARALYSIS         2
#define ITEM3_FREEZE            4
#define ITEM3_BURN              8
#define ITEM3_POISON            16
#define ITEM3_SLEEP             32
#define ITEM3_LEVEL_UP          64
#define ITEM3_GUARD_SPEC        128 // Works the same way as the move Mist.

#define ITEM3_STATUS_ALL        (ITEM3_CONFUSION | ITEM3_PARALYSIS | ITEM3_FREEZE | ITEM3_BURN | ITEM3_POISON | ITEM3_SLEEP)

// field 4 masks
#define ITEM4_EV_HP             1
#define ITEM4_EV_ATK            2
#define ITEM4_HEAL_HP           4
#define ITEM4_HEAL_PP           8
#define ITEM4_HEAL_PP_ONE       16
#define ITEM4_PP_UP             32
#define ITEM4_REVIVE            64
#define ITEM4_EVO_STONE         128

// field 5 masks
#define ITEM5_EV_DEF            1
#define ITEM5_EV_SPEED          2
#define ITEM5_EV_SPDEF          4
#define ITEM5_EV_SPATK          8
#define ITEM5_PP_MAX            16
#define ITEM5_FRIENDSHIP_LOW    32
#define ITEM5_FRIENDSHIP_MID    64
#define ITEM5_FRIENDSHIP_HIGH   128

#define ITEM5_FRIENDSHIP_ALL    (ITEM5_FRIENDSHIP_LOW | ITEM5_FRIENDSHIP_MID | ITEM5_FRIENDSHIP_HIGH)

#define ITEM10_IS_VITAMIN       1

// fields 6 and onwards (except field 10) are item-specific arguments
#define ITEM_EFFECT_ARG_START 6

// Special HP recovery amounts for ITEM4_HEAL_HP
#define ITEM6_HEAL_HP_FULL    ((u8) -1)
#define ITEM6_HEAL_HP_HALF    ((u8) -2)
#define ITEM6_HEAL_HP_LVL_UP  ((u8) -3)
#define ITEM6_HEAL_HP_QUARTER ((u8) -4)

// Special PP recovery amounts for ITEM4_HEAL_PP
#define ITEM6_HEAL_PP_FULL   127

// Amount of EV modified by ITEM4_EV_HP, ITEM4_EV_ATK, ITEM5_EV_DEF, ITEM5_EV_SPEED, ITEM5_EV_SPDEF and ITEM5_EV_SPATK
#define ITEM6_ADD_EV       10
#define ITEM6_SUBTRACT_EV -10
#define ITEM6_ADD_ONE_EV    1
#define ITEM6_RESET_EV      0

#endif // GUARD_CONSTANTS_ITEM_EFFECTS_H
