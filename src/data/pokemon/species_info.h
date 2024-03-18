#include "constants/abilities.h"
#include "species_info/shared_dex_text.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }

#define FRONT_PIC(sprite, width, height)                    \
        .frontPic = gMonFrontPic_## sprite,                 \
        .frontPicSize = MON_COORDS_SIZE(width, height)

#define FRONT_PIC_FEMALE(sprite, width, height)             \
        .frontPicFemale = gMonFrontPic_## sprite##F,        \
        .frontPicSizeFemale = MON_COORDS_SIZE(width, height)

#define BACK_PIC(sprite, width, height)                     \
        .backPic = gMonBackPic_## sprite,                   \
        .backPicSize = MON_COORDS_SIZE(width, height)

#define BACK_PIC_FEMALE(sprite, width, height)              \
        .backPicFemale = gMonBackPic_## sprite##F,          \
        .backPicSizeFemale = MON_COORDS_SIZE(width, height)

#define PALETTES(pal)                                       \
        .palette = gMonPalette_## pal,                      \
        .shinyPalette = gMonShinyPalette_## pal

#define PALETTE_FEMALE(pal)                                 \
        .paletteFemale = gMonPalette_## pal##F,             \
        .shinyPaletteFemale = gMonShinyPalette_## pal##F

#define ICON(sprite, palId)                                 \
        .iconSprite = gObjectEventPic_## sprite,            \
        .iconPalIndex = palId

#define ICON_FEMALE(sprite, palId)                          \
        .iconSpriteFemale = gObjectEventPic_## sprite##F,   \
        .iconPalIndexFemale = palId

#define LEARNSETS(learn)                                    \
        .levelUpLearnset = s ## learn##LevelUpLearnset,     \
        .teachableLearnset = s ## learn##TeachableLearnset

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if P_FOLLOWERS
#define FOLLOWER(name, _size, shadow, _tracks)                                              \
.followerData = {                                                                           \
    .tileTag = TAG_NONE,                                                                    \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                         \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                             \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                               \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                              \
    .paletteSlot = PALSLOT_NPC_1,                                                           \
    .shadowSize = shadow,                                                                   \
    .inanimate = FALSE,                                                                     \
    .compressed = COMP,                                                                     \
    .tracks = _tracks,                                                                      \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64), \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),         \
    .anims = sAnimTable_Following,                                                          \
    .images = sPicTable_##name,                                                             \
    .affineAnims = gDummySpriteAffineAnimTable,                                             \
},                                                                                          
#else
#define FOLLOWER(name, _size, shadow, _tracks)
#endif

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        FRONT_PIC(CircledQuestionMark, 40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_None,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        BACK_PIC(CircledQuestionMark, 40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        PALETTES(CircledQuestionMark),
        ICON(Bulbasaur, 0),
        .followerData = {TAG_NONE, OBJ_EVENT_PAL_TAG_DYNAMIC, OBJ_EVENT_PAL_TAG_NONE, 512, 32, 32, 2, SHADOW_SIZE_M, FALSE, COMP, TRACKS_FOOT, &gObjectEventBaseOam_32x32, sOamTables_32x32, sAnimTable_Following, sPicTable_None, gDummySpriteAffineAnimTable},
        LEARNSETS(None),
    },

    #include "species_info/gen_1.h"
    #include "species_info/gen_2.h"
    #include "species_info/gen_3.h"
    #include "species_info/gen_4.h"
    #include "species_info/gen_5.h"
    #include "species_info/gen_6.h"
    #include "species_info/gen_7.h"
    #include "species_info/gen_8.h"
    #include "species_info/gen_9.h"

    [SPECIES_EGG] =
    {
        FRONT_PIC(Egg, 24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        ICON(Bulbasaur, 1),
    },

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        FRONT_PIC(CircledQuestionMark, 64, 64),
        //FRONT_PIC_FEMALE(CircledQuestionMark, 64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 0,
        BACK_PIC(CircledQuestionMark, 64, 64),
        //BACK_PIC_FEMALE(CircledQuestionMark, 64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        PALETTES(CircledQuestionMark),
        //PALETTE_FEMALE(CircledQuestionMark),
        ICON(QuestionMark, 0),
        //ICON_FEMALE(QuestionMark, 1),
        //FOOTPRINT(None)
        LEARNSETS(None),
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        .allPerfectIVs = TRUE,
    },
    */
};
