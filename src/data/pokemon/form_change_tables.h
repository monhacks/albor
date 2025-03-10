static const struct FormChange sCastformFormChangeTable[] = {
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CASTFORM_SUNNY, B_WEATHER_SUN, ABILITY_FORECAST},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CASTFORM_RAINY, B_WEATHER_RAIN, ABILITY_FORECAST},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CASTFORM_SNOWY, B_WEATHER_HAIL | B_WEATHER_SNOW, ABILITY_FORECAST},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CASTFORM_NORMAL, ~(B_WEATHER_SUN | B_WEATHER_RAIN | B_WEATHER_HAIL | B_WEATHER_SNOW), ABILITY_FORECAST},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CASTFORM_NORMAL, B_WEATHER_NONE, ABILITY_FORECAST},
};

static const struct FormChange sDeoxysNormalFormChangeTable[] = {
    {FORM_CHANGE_ITEM_USE, SPECIES_DEOXYS_ATTACK,  ITEM_METEORITE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sDeoxysAttackFormChangeTable[] = {
    {FORM_CHANGE_ITEM_USE, SPECIES_DEOXYS_DEFENSE,  ITEM_METEORITE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sDeoxysDefenseFormChangeTable[] = {
    {FORM_CHANGE_ITEM_USE, SPECIES_DEOXYS_SPEED,  ITEM_METEORITE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sDeoxysSpeedFormChangeTable[] = {
    {FORM_CHANGE_ITEM_USE, SPECIES_DEOXYS_NORMAL,  ITEM_METEORITE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sCherrimFormChangeTable[] = {
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CHERRIM_SUNSHINE, B_WEATHER_SUN, ABILITY_FLOWER_GIFT},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CHERRIM_OVERCAST, ~B_WEATHER_SUN, ABILITY_FLOWER_GIFT},
    {FORM_CHANGE_BATTLE_WEATHER,                SPECIES_CHERRIM_OVERCAST, B_WEATHER_NONE, ABILITY_FLOWER_GIFT},
};

static const struct FormChange sRotomFormChangeTable[] = {
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM,       ITEM_ROTOM_CATALOG, 0},
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM_HEAT,  ITEM_ROTOM_CATALOG, 1},
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM_WASH,  ITEM_ROTOM_CATALOG, 2},
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM_FROST, ITEM_ROTOM_CATALOG, 3},
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM_FAN,   ITEM_ROTOM_CATALOG, 4},
    {FORM_CHANGE_ITEM_USE_MULTICHOICE, SPECIES_ROTOM_MOW,   ITEM_ROTOM_CATALOG, 5},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sDarmanitanFormChangeTable[] = {
    {FORM_CHANGE_BATTLE_HP_PERCENT, SPECIES_DARMANITAN_STANDARD_MODE, ABILITY_ZEN_MODE, HP_HIGHER_THAN,   50},
    {FORM_CHANGE_BATTLE_HP_PERCENT, SPECIES_DARMANITAN_ZEN_MODE,      ABILITY_ZEN_MODE, HP_LOWER_EQ_THAN, 50},
    {FORM_CHANGE_FAINT,             SPECIES_DARMANITAN_STANDARD_MODE},
    {FORM_CHANGE_END_BATTLE,        SPECIES_DARMANITAN_STANDARD_MODE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sDarmanitanGalarianFormChangeTable[] = {
    {FORM_CHANGE_BATTLE_HP_PERCENT, SPECIES_DARMANITAN_GALARIAN_STANDARD_MODE, ABILITY_ZEN_MODE, HP_HIGHER_THAN,   50},
    {FORM_CHANGE_BATTLE_HP_PERCENT, SPECIES_DARMANITAN_GALARIAN_ZEN_MODE,      ABILITY_ZEN_MODE, HP_LOWER_EQ_THAN, 50},
    {FORM_CHANGE_FAINT,             SPECIES_DARMANITAN_GALARIAN_STANDARD_MODE},
    {FORM_CHANGE_END_BATTLE,        SPECIES_DARMANITAN_GALARIAN_STANDARD_MODE},
    {FORM_CHANGE_TERMINATOR},
};

static const struct FormChange sAegislashFormChangeTable[] = {
    {FORM_CHANGE_BATTLE_SWITCH, SPECIES_AEGISLASH_SHIELD},
    {FORM_CHANGE_FAINT,         SPECIES_AEGISLASH_SHIELD},
    {FORM_CHANGE_END_BATTLE,    SPECIES_AEGISLASH_SHIELD},
    {FORM_CHANGE_TERMINATOR},
};
