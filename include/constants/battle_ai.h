#ifndef GUARD_CONSTANTS_BATTLE_AI_H
#define GUARD_CONSTANTS_BATTLE_AI_H

enum AIBattlers
{
    AI_TARGET,
    AI_USER,
    AI_TARGET_PARTNER,
    AI_USER_PARTNER,
};

enum AITypes
{
    AI_TYPE1_TARGET,
    AI_TYPE1_USER,
    AI_TYPE2_TARGET,
    AI_TYPE2_USER,
    AI_TYPE_MOVE,
};

enum AIEffectiveness
{
    AI_EFFECTIVENESS_x0,
    AI_EFFECTIVENESS_x0_125,
    AI_EFFECTIVENESS_x0_25,
    AI_EFFECTIVENESS_x0_5,
    AI_EFFECTIVENESS_x1,
    AI_EFFECTIVENESS_x2,
    AI_EFFECTIVENESS_x4,
    AI_EFFECTIVENESS_x8,
};

//Comprobar cada flag, unificar las que se pueda, eliminar las que no se vayan a usar, crear interesantes
enum AIFlags
{
    AI_FLAG_CHECK_BAD_MOVE,
    AI_FLAG_TRY_TO_FAINT,
    AI_FLAG_CHECK_VIABILITY,
    AI_FLAG_SETUP_FIRST_TURN,
    AI_FLAG_RISKY,
    AI_FLAG_PREFER_STRONGEST_MOVE,
    AI_FLAG_PREFER_BATON_PASS,
    AI_FLAG_DOUBLE_BATTLE, //Set automático si es doble batalla.
    AI_FLAG_HP_AWARE,
    AI_FLAG_POWERFUL_STATUS, //Prefiere status incluso si puede debilitar (???)
    AI_FLAG_NEGATE_UNAWARE, //Eliminar
    AI_FLAG_WILL_SUICIDE, //Eliminar
    AI_FLAG_PREFER_STATUS_MOVES,
    AI_FLAG_STALL, //Sin terminar
    AI_FLAG_SMART_SWITCHING, //Interesante
    AI_FLAG_ACE_POKEMON, //Interesante
    AI_FLAG_OMNISCIENT, //Eliminar?
    AI_FLAG_SMART_MON_CHOICES, //Interesante
    AI_FLAG_CONSERVATIVE, //???
    AI_FLAG_SEQUENCE_SWITCHING,
    AI_FLAG_DYNAMIC_FUNC, //???

    AI_FLAG_COUNT
};

#define AI_SCORE_DEFAULT 100 // Default score for all AI moves.

#endif // GUARD_CONSTANTS_BATTLE_AI_H
