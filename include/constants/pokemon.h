#ifndef GUARD_CONSTANTS_POKEMON_H
#define GUARD_CONSTANTS_POKEMON_H

// Pokémon types
enum TiposPokemon
{
    TIPO_NINGUNO,
    TIPO_NORMAL,
    TIPO_LUCHA,
    TIPO_VOLADOR,
    TIPO_VENENO,
    TIPO_TIERRA,
    TIPO_ROCA,
    TIPO_BICHO,
    TIPO_FANTASMA,
    TIPO_ACERO,
    TIPO_MISTERIO,
    TIPO_FUEGO,
    TIPO_AGUA,
    TIPO_PLANTA,
    TIPO_ELECTRICO,
    TIPO_PSIQUICO,
    TIPO_HIELO,
    TIPO_DRAGON,
    TIPO_SINIESTRO,
    TIPO_HADA,
    NUMERO_DE_TIPOS
};

enum GruposHuevo
{
    GRUPO_HUEVO_NINGUNO,
    GRUPO_HUEVO_MONSTRUO,
    GRUPO_HUEVO_ANFIBIO,
    GRUPO_HUEVO_BICHO,
    GRUPO_HUEVO_PAJARO,
    GRUPO_HUEVO_CAMPESTRE,
    GRUPO_HUEVO_HADA,
    GRUPO_HUEVO_PLANTA,
    GRUPO_HUEVO_HUMANOIDE,
    GRUPO_HUEVO_INVERTEBRADO,
    GRUPO_HUEVO_MINERAL,
    GRUPO_HUEVO_AMORFO,
    GRUPO_HUEVO_PEZ,
    GRUPO_HUEVO_DRAGON,
    GRUPO_HUEVO_BEBE,
};

#define GRUPOS_HUEVO_POR_POKEMON    2

#define PASOS_POR_CICLO_HUEVO       255

enum CiclosHuevo
{
    CICLO_HUEVO_NORMAL = 40,
    CICLO_HUEVO_ESPECIAL = 80,
    CICLO_HUEVO_SEMILEGENDARIO = 120,
    CICLO_HUEVO_LEGENDARIO_MENOR = 160,
    CICLO_HUEVO_LEGENDARIO_MAYOR = 200,
};

enum RatiosCaptura
{
    RATIO_CAPTURA_NORMAL_1_EVO          = 255,
    RATIO_CAPTURA_NORMAL_2_EVO          = 127,
    RATIO_CAPTURA_ESPECIAL_1_EVO        = RATIO_CAPTURA_NORMAL_2_EVO,
    RATIO_CAPTURA_NORMAL_3_EVO          = 63,
    RATIO_CAPTURA_ESPECIAL_2_EVO        = RATIO_CAPTURA_NORMAL_3_EVO,
    RATIO_CAPTURA_SEMILEGENDARIO_1_EVO  = RATIO_CAPTURA_NORMAL_3_EVO,
    RATIO_CAPTURA_ESPECIAL_3_EVO        = 31,
    RATIO_CAPTURA_SEMILEGENDARIO_2_EVO  = RATIO_CAPTURA_ESPECIAL_3_EVO,
    RATIO_CAPTURA_SEMILEGENDARIO_3_EVO  = 15,
    RATIO_CAPTURA_LEGENDARIO_MENOR      = 7,
    RATIO_CAPTURA_LEGENDARIO_MAYOR      = 3,
};

enum CampoExperiencia
{
    CAMPO_EXPERIENCIA_NORMAL_1_EVO          = 50,
    CAMPO_EXPERIENCIA_NORMAL_2_EVO          = 100,
    CAMPO_EXPERIENCIA_NORMAL_3_EVO          = 150,
    CAMPO_EXPERIENCIA_ESPECIAL_1_EVO        = 75,
    CAMPO_EXPERIENCIA_ESPECIAL_2_EVO        = 125,
    CAMPO_EXPERIENCIA_ESPECIAL_3_EVO        = 175,
    CAMPO_EXPERIENCIA_SEMILEGENDARIO_1_EVO  = 100,
    CAMPO_EXPERIENCIA_SEMILEGENDARIO_2_EVO  = 150,
    CAMPO_EXPERIENCIA_SEMILEGENDARIO_3_EVO  = 200,
    CAMPO_EXPERIENCIA_LEGENDARIO_MENOR      = 225,
    CAMPO_EXPERIENCIA_LEGENDARIO_MAYOR      = 250,
};

enum Naturalezas
{
    NATURALEZA_OFENSIVA,
    NATURALEZA_DEFENSIVA,
    NATURALEZA_OFENSIVA_ESPECIAL,
    NATURALEZA_DEFENSIVA_ESPECIAL,
    NATURALEZA_RAPIDA,
    NUMERO_NATURALEZAS
};

// Pokémon Stats
#define STAT_HP      0
#define STAT_ATK     1
#define STAT_DEF     2
#define STAT_SPEED   3
#define STAT_SPATK   4
#define STAT_SPDEF   5
#define NUM_STATS    6

#define STAT_ACC     6 // Only in battles.
#define STAT_EVASION 7 // Only in battles.

#define NUM_NATURE_STATS (NUM_STATS - 1) // excludes HP
#define NUM_BATTLE_STATS (NUM_STATS + 2) // includes Accuracy and Evasion

#define MIN_STAT_STAGE     0
#define DEFAULT_STAT_STAGE 6
#define MAX_STAT_STAGE    12

// Shiny odds
#define SHINY_ODDS 128 //Probabilidad de 1/4096

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

#define OT_ID_PLAYER_ID       0
#define OT_ID_PRESET          1
#define OT_ID_RANDOM_NO_SHINY 2

#define MON_GIVEN_TO_PARTY      0
#define MON_GIVEN_TO_PC         1
#define MON_CANT_GIVE           2

#define PLAYER_HAS_TWO_USABLE_MONS     0
#define PLAYER_HAS_ONE_MON             1
#define PLAYER_HAS_ONE_USABLE_MON      2

#define MON_ALREADY_KNOWS_MOVE  0xFFFE
#define MON_HAS_MAX_MOVES       0xFFFF

#define LEVEL_UP_MOVE_ID   0x01FF
#define LEVEL_UP_MOVE_LV   0xFE00
#define LEVEL_UP_MOVE_END  0xFFFF

#define MAX_LEVEL_UP_MOVES       20

#define MON_MALE       0x00
#define MON_FEMALE     0xFE
#define MON_GENDERLESS 0xFF

// Constants for AdjustFriendship
#define FRIENDSHIP_EVENT_GROW_LEVEL       0
#define FRIENDSHIP_EVENT_VITAMIN          1 // unused, handled by PokemonUseItemEffects
#define FRIENDSHIP_EVENT_BATTLE_ITEM      2 // unused, handled by PokemonUseItemEffects
#define FRIENDSHIP_EVENT_LEAGUE_BATTLE    3
#define FRIENDSHIP_EVENT_LEARN_TMHM       4
#define FRIENDSHIP_EVENT_WALKING          5
#define FRIENDSHIP_EVENT_FAINT_SMALL      6
#define FRIENDSHIP_EVENT_FAINT_FIELD_PSN  7
#define FRIENDSHIP_EVENT_FAINT_LARGE      8 // If opponent was >= 30 levels higher. See AdjustFriendshipOnBattleFaint

// Constants for GetLeadMonFriendshipScore
#define FRIENDSHIP_NONE        0
#define FRIENDSHIP_1_TO_49     1
#define FRIENDSHIP_50_TO_99    2
#define FRIENDSHIP_100_TO_149  3
#define FRIENDSHIP_150_TO_199  4
#define FRIENDSHIP_200_TO_254  5
#define FRIENDSHIP_MAX         6

enum Amistad
{
    AMISTAD_LEGENDARIO_MAYOR    = 10,
    AMISTAD_LEGENDARIO_MENOR    = 20,
    AMISTAD_SEMILEGENDARIO      = 30,
    AMISTAD_ESPECIAL            = 40,
    AMISTAD_NORMAL              = 50,
};

#define MAX_FRIENDSHIP  255
#define MAX_SHEEN       255
#define MAX_CONDITION   255

#define MAX_PER_STAT_IVS 31
#define MAX_IV_MASK 31
#define USE_RANDOM_IVS (MAX_PER_STAT_IVS + 1)
#define MAX_PER_STAT_EVS 252
#define MAX_TOTAL_EVS 504

enum CategoriasAtaque
{
    CATEGORIA_FISICA,
    CATEGORIA_ESPECIAL,
    CATEGORIA_ESTADO,
};

enum Crecimiento
{
    CRECIMIENTO_NORMAL,
    CRECIMIENTO_ESPECIAL,
    CRECIMIENTO_SEMILEGENDARIO,
    CRECIMIENTO_LEGENDARIO_MENOR,
    CRECIMIENTO_LEGENDARIO_MAYOR,
    TIPOS_DE_CRECIMIENTO
};

#define F_SUMMARY_SCREEN_FLIP_SPRITE 128

enum MetodosEvolutivos {
    EVO_NO,
    EVO_AMISTAD,
    EVO_NIVEL,
    EVO_ITEM,
    EVO_NIVEL_MAS_ATAQUE,
    EVO_NIVEL_IGUAL_ATAQUE,
    EVO_NIVEL_MENOS_ATAQUE,
    EVO_NIVEL_SILCOON,
    EVO_NIVEL_CASCOON,
    EVO_NIVEL_NINJASK,
    EVO_NIVEL_SHEDINJA,
    EVO_NIVEL_HEMBRA,
    EVO_NIVEL_MACHO,
    EVO_NIVEL_NOCHE,
    EVO_NIVEL_DIA,
    EVO_MOVIMIENTO,
    EVO_NIVEL_LLUVIA,
    EVO_NIVEL_NIEBLA,
    EVO_NIVEL_NIEVE,
    EVO_NIVEL_SINIESTRO_EQUIPO,
    EVO_MAPSEC,
    EVO_FIN
};

#define MON_PIC_WIDTH 64
#define MON_PIC_HEIGHT 64
#define MON_PIC_SIZE (MON_PIC_WIDTH * MON_PIC_HEIGHT / 2)

// Most Pokémon have 2 frames (a default and an alternate for their animation).
// There are 4 exceptions:
// - Deoxys has 2 frames, 1 for each form
// - Spinda has 1 frame, presumably to avoid the work of animating its spots
// - Unown has 1 frame, presumably to avoid the work of animating all 28 of its forms
#define MAX_MON_PIC_FRAMES 2

#define BATTLE_ALIVE_EXCEPT_BATTLER  0
#define BATTLE_ALIVE_SIDE            1

#define SKIP_FRONT_ANIM (1 << 7)

#define NUM_ABILITY_SLOTS (NUM_NORMAL_ABILITY_SLOTS + NUM_HIDDEN_ABILITY_SLOTS)
#define NUM_NORMAL_ABILITY_SLOTS 2
#define NUM_HIDDEN_ABILITY_SLOTS 1

enum SlotsHabilidades
{
    SLOT_HABILIDAD_1,
    SLOT_HABILIDAD_2,
    SLOT_HABILIDAD_OCULTA,
    SLOTS_HABILIDADES
};

// Used as a signal for givemon to generate a default ability by personality.
#define NUM_ABILITY_PERSONALITY 0xFF

#endif // GUARD_CONSTANTS_POKEMON_H
