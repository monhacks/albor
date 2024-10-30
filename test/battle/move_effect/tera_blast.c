#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(gMovesInfo[MOVE_TERA_BLAST].effect == EFFECT_TERA_BLAST);
}

SINGLE_BATTLE_TEST("Tera Blast changes from Normal-type to the user's Tera Type")
{
    GIVEN {
        ASSUME(gMovesInfo[MOVE_TERA_BLAST].type == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TIPO_SINIESTRO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); }
    } SCENE {
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Tera Blast has correct effectiveness for every Tera Type")
{
    u32 species;
    u32 type;

    PARAMETRIZE { species = SPECIES_CHIKORITA; type = TIPO_VOLADOR;   }
    PARAMETRIZE { species = SPECIES_CHIKORITA; type = TIPO_VENENO;   }
    PARAMETRIZE { species = SPECIES_CHIKORITA; type = TIPO_FUEGO;     }
    PARAMETRIZE { species = SPECIES_CHIKORITA; type = TIPO_BICHO;      }
    PARAMETRIZE { species = SPECIES_CHIKORITA; type = TIPO_HIELO;      }
    PARAMETRIZE { species = SPECIES_CYNDAQUIL; type = TIPO_TIERRA;   }
    PARAMETRIZE { species = SPECIES_CYNDAQUIL; type = TIPO_ROCA;     }
    PARAMETRIZE { species = SPECIES_CYNDAQUIL; type = TIPO_AGUA;    }
    PARAMETRIZE { species = SPECIES_GASTLY;    type = TYPE_NORMAL;   }
    PARAMETRIZE { species = SPECIES_GASTLY;    type = TIPO_FANTASMA;    }
    PARAMETRIZE { species = SPECIES_GASTLY;    type = TIPO_PSIQUICO;  }
    PARAMETRIZE { species = SPECIES_TOTODILE;  type = TIPO_PLANTA;    }
    PARAMETRIZE { species = SPECIES_TOTODILE;  type = TIPO_ELECTRICO; }
    PARAMETRIZE { species = SPECIES_DRATINI;   type = TIPO_DRAGON;   }
    PARAMETRIZE { species = SPECIES_DRATINI;   type = TIPO_HADA;    }
    PARAMETRIZE { species = SPECIES_SNEASEL;   type = TIPO_LUCHA; }
    PARAMETRIZE { species = SPECIES_SNEASEL;   type = TIPO_ACERO;    }
    PARAMETRIZE { species = SPECIES_ABRA;      type = TIPO_SINIESTRO;     }

    GIVEN {
        ASSUME(gSpeciesInfo[SPECIES_CHIKORITA].types[0] == TIPO_PLANTA);
        ASSUME(gSpeciesInfo[SPECIES_CHIKORITA].types[1] == TIPO_PLANTA);
        ASSUME(gSpeciesInfo[SPECIES_CYNDAQUIL].types[0] == TIPO_FUEGO);
        ASSUME(gSpeciesInfo[SPECIES_CYNDAQUIL].types[1] == TIPO_FUEGO);
        ASSUME(gSpeciesInfo[SPECIES_GASTLY].types[0] == TIPO_FANTASMA);
        ASSUME(gSpeciesInfo[SPECIES_GASTLY].types[1] == TIPO_VENENO);
        ASSUME(gSpeciesInfo[SPECIES_TOTODILE].types[0] == TIPO_AGUA);
        ASSUME(gSpeciesInfo[SPECIES_TOTODILE].types[1] == TIPO_AGUA);
        ASSUME(gSpeciesInfo[SPECIES_DRATINI].types[0] == TIPO_DRAGON);
        ASSUME(gSpeciesInfo[SPECIES_DRATINI].types[1] == TIPO_DRAGON);
        ASSUME(gSpeciesInfo[SPECIES_SNEASEL].types[0] == TIPO_SINIESTRO);
        ASSUME(gSpeciesInfo[SPECIES_SNEASEL].types[1] == TIPO_HIELO);
        ASSUME(gSpeciesInfo[SPECIES_ABRA].types[0] == TIPO_PSIQUICO);
        ASSUME(gSpeciesInfo[SPECIES_ABRA].types[1] == TIPO_PSIQUICO);
        PLAYER(SPECIES_WOBBUFFET) { TeraType(type); }
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); }
    } SCENE {
        if (species == SPECIES_GASTLY && type == TYPE_NORMAL)
            MESSAGE("It doesn't affect the opposing Gastly…");
        else
            MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Tera Blast becomes a physical move if the user is Terastallized and has a higher Attack stat", s16 damage)
{
    bool32 tera;
    PARAMETRIZE { tera = GIMMICK_NONE; }
    PARAMETRIZE { tera = GIMMICK_TERA; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TYPE_NORMAL); Attack(100); SpAttack(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Defense(200); SpDefense(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: tera); }
    } SCENE {
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        // Since Wobbuffett has equal defenses, Tera Blast should do 1.5x more damage
        // from gaining STAB and an additional 2.0x damage from using its highest
        // attacking stat.
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(3.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Stellar-type Tera Blast lowers both offensive stats")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TYPE_STELLAR); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); }
    } SCENE {
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        MESSAGE("Wobbuffet's Attack fell!");
        MESSAGE("Wobbuffet's Sp. Atk fell!");
    }
}


SINGLE_BATTLE_TEST("Stellar-type Tera Blast has 100 BP and a one-time 1.2x boost")
{
    s16 damage[3];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TYPE_STELLAR); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST); MOVE(opponent, MOVE_RECOVER); }
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); }
        TURN { MOVE(player, MOVE_WORK_UP); }
        TURN { MOVE(player, MOVE_TERA_BLAST); }
    } SCENE {
        // turn 1
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        // turn 2
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
        // turn 4
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        HP_BAR(opponent, captureDamage: &damage[2]);
    } THEN {
        // 80 BP to 120 BP (100 * 1.2) boost upon Terastallizing
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.50), damage[1]);
        // 120 BP to 100 BP after Stellar boost expended
        EXPECT_MUL_EQ(damage[2], UQ_4_12(1.20), damage[1]);
    }
}

SINGLE_BATTLE_TEST("Stellar-type Tera Blast is super-effective on Stellar-type Pokemon")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TYPE_STELLAR); }
        OPPONENT(SPECIES_WOBBUFFET) { TeraType(TYPE_STELLAR); }
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); MOVE(opponent, MOVE_CELEBRATE, gimmick: GIMMICK_TERA); }
    } SCENE {
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        MESSAGE("It's super effective!");
    }
}

SINGLE_BATTLE_TEST("Stellar-type Tera Blast activates a Stellar-type Pokemon's Weakness Policy")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { TeraType(TYPE_STELLAR); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_WEAKNESS_POLICY); TeraType(TYPE_NORMAL); }
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); MOVE(opponent, MOVE_CELEBRATE, gimmick: GIMMICK_TERA); }
    } SCENE {
        MESSAGE("Wobbuffet used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
        MESSAGE("It's super effective!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, opponent);
    }
}

SINGLE_BATTLE_TEST("Flying-type Tera Blast does not have its priority boosted by Gale Wings")
{
    GIVEN {
        PLAYER(SPECIES_TALONFLAME) { Ability(ABILITY_GALE_WINGS); TeraType(TIPO_VOLADOR); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TERA_BLAST, gimmick: GIMMICK_TERA); MOVE(opponent, MOVE_QUICK_ATTACK); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Quick Attack!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUICK_ATTACK, opponent);
        MESSAGE("Talonflame used Tera Blast!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TERA_BLAST, player);
    }
}
