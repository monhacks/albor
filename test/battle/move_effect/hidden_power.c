#include "global.h"
#include "test/battle.h"

// IV combinations sourced from https://www.smogon.com/forums/threads/hidden-power-iv-combinations.78083/
SINGLE_BATTLE_TEST("Hidden Power's type is determined by IVs")
{
    u32 type, j, foeType, foeSpecies;
    u32 hp, atk, def, spAtk, spDef, speed;
    bool32 hidden;

    PARAMETRIZE { type = TYPE_NONE;     hidden = FALSE; }
    PARAMETRIZE { type = TYPE_NORMAL;   hidden = FALSE; }
    PARAMETRIZE { type = TIPO_LUCHA; hidden = TRUE;  foeType = TIPO_PSIQUICO;   foeSpecies = SPECIES_WOBBUFFET; hp = 30; atk =  2; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_LUCHA; hidden = TRUE;  foeType = TIPO_PSIQUICO;   foeSpecies = SPECIES_WOBBUFFET; hp = 31; atk = 15; def = 30; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_LUCHA; hidden = TRUE;  foeType = TIPO_PSIQUICO;   foeSpecies = SPECIES_WOBBUFFET; hp = 30; atk = 22; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_LUCHA; hidden = TRUE;  foeType = TIPO_PSIQUICO;   foeSpecies = SPECIES_WOBBUFFET; hp = 31; atk = 31; def = 30; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_VOLADOR;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_REGISTEEL; hp = 31; atk =  2; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_VOLADOR;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_REGISTEEL; hp = 31; atk = 15; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_VOLADOR;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_REGISTEEL; hp = 31; atk = 22; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_VOLADOR;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_REGISTEEL; hp = 31; atk = 31; def = 31; spAtk = 30; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_VENENO;   hidden = TRUE;  foeType = TIPO_VENENO;    foeSpecies = SPECIES_ARBOK;     hp = 30; atk =  2; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_VENENO;   hidden = TRUE;  foeType = TIPO_VENENO;    foeSpecies = SPECIES_ARBOK;     hp = 31; atk = 15; def = 30; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_VENENO;   hidden = TRUE;  foeType = TIPO_VENENO;    foeSpecies = SPECIES_ARBOK;     hp = 30; atk = 22; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_VENENO;   hidden = TRUE;  foeType = TIPO_VENENO;    foeSpecies = SPECIES_ARBOK;     hp = 31; atk = 31; def = 30; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_TIERRA;   hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk =  2; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_TIERRA;   hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk = 15; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_TIERRA;   hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk = 22; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_TIERRA;   hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk = 31; def = 31; spAtk = 30; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_ROCA;     hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk =  2; def = 30; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_ROCA;     hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 15; def = 30; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_ROCA;     hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 22; def = 30; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_ROCA;     hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 31; def = 30; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_BICHO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk =  2; def = 31; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_BICHO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 15; def = 31; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_BICHO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 22; def = 31; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_BICHO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 31; def = 31; spAtk = 31; spDef = 30; speed = 30; }
    PARAMETRIZE { type = TIPO_FANTASMA;    hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk =  2; def = 31; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_FANTASMA;    hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 15; def = 30; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_FANTASMA;    hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 22; def = 31; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_FANTASMA;    hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 31; def = 30; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_ACERO;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk =  2; def = 30; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_ACERO;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 15; def = 31; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_ACERO;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 22; def = 30; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_ACERO;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 31; def = 31; spAtk = 31; spDef = 30; speed = 31; }
    PARAMETRIZE { type = TIPO_FUEGO;     hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk =  2; def = 31; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_FUEGO;     hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 15; def = 30; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_FUEGO;     hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 22; def = 31; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_FUEGO;     hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 31; def = 30; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_AGUA;    hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk =  2; def = 30; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_AGUA;    hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 15; def = 31; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_AGUA;    hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 22; def = 30; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_AGUA;    hidden = TRUE;  foeType = TIPO_AGUA;     foeSpecies = SPECIES_BLASTOISE; hp = 31; atk = 31; def = 31; spAtk = 30; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_PLANTA;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk =  2; def = 31; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_PLANTA;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 15; def = 31; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_PLANTA;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 22; def = 31; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_PLANTA;    hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 31; def = 31; spAtk = 30; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_ELECTRICO; hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk =  2; def = 30; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_ELECTRICO; hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 30; atk = 15; def = 30; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_ELECTRICO; hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 31; atk = 22; def = 30; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_ELECTRICO; hidden = TRUE;  foeType = TIPO_PLANTA;     foeSpecies = SPECIES_TANGELA;   hp = 30; atk = 31; def = 30; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_PSIQUICO;  hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk =  2; def = 31; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_PSIQUICO;  hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 15; def = 31; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_PSIQUICO;  hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 31; atk = 22; def = 31; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_PSIQUICO;  hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 31; def = 31; spAtk = 31; spDef = 31; speed = 30; }
    PARAMETRIZE { type = TIPO_HIELO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk =  2; def = 30; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_HIELO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 15; def = 30; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_HIELO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 22; def = 30; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_HIELO;      hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 31; def = 30; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_MISTERIO;  hidden = FALSE; }
    PARAMETRIZE { type = TIPO_DRAGON;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk =  2; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_DRAGON;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 15; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_DRAGON;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 22; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_DRAGON;   hidden = TRUE;  foeType = TIPO_ACERO;     foeSpecies = SPECIES_KLINK;     hp = 30; atk = 31; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_SINIESTRO;     hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk =  3; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_SINIESTRO;     hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 15; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_SINIESTRO;     hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 23; def = 31; spAtk = 31; spDef = 31; speed = 31; }
    PARAMETRIZE { type = TIPO_SINIESTRO;     hidden = TRUE;  foeType = TIPO_SINIESTRO;      foeSpecies = SPECIES_UMBREON;   hp = 31; atk = 31; def = 31; spAtk = 31; spDef = 31; speed = 31; }

    // Any type after Dark shouldn't be part of Hidden Power officially.
    for (j = TIPO_SINIESTRO + 1; j < NUMERO_DE_TIPOS; j++) {
        PARAMETRIZE { type = j; hidden = FALSE; }
    }

    GIVEN {
        if (hidden) {
            ASSUME(gTypeEffectivenessTable[type][foeType] == UQ_4_12(0.5));                 // Foe's Type resists
            ASSUME(gSpeciesInfo[foeSpecies].types[0] == gSpeciesInfo[foeSpecies].types[1]); // Foe's pure type
            ASSUME(gSpeciesInfo[foeSpecies].types[0] == foeType);                           // Foe is the resisted type
            PLAYER(SPECIES_DUNSPARCE) { HPIV(hp); AttackIV(atk); DefenseIV(def); SpAttackIV(spAtk); SpDefenseIV(spDef); SpeedIV(speed); }
        } else {
            PLAYER(SPECIES_DUNSPARCE);
        }
        OPPONENT(foeSpecies);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        // Only test valid Hidden Power types
        if (hidden) {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
            HP_BAR(opponent);
            MESSAGE("It's not very effective…");
        }
    }
}

TO_DO_BATTLE_TEST("Hidden Power's power is determined by IVs before Gen6");
