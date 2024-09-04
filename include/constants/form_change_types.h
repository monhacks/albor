#ifndef GUARD_CONSTANTS_FORM_CHANGE_TYPES_H
#define GUARD_CONSTANTS_FORM_CHANGE_TYPES_H

enum FormChanges
{
    FORM_CHANGE_BATTLE_WEATHER, // Form change that activates when a specific weather is set during battle. param1: weather to check. param2: (optional) revert if specified ability is lost.
    FORM_CHANGE_ITEM_USE, // Form change that activates when the item is used on the selected Pokémon. param1: item to use.
    FORM_CHANGE_ITEM_USE_MULTICHOICE, // Form change that depends on a multichoice (e.g. Rotom Catalog). param1: multichoice list (starting at 0).
    FORM_CHANGE_BATTLE_HP_PERCENT, // Form change that activates when the Pokémon's HP % passes a certain threshold. param1: Ability to check. param2: HP comparer: - HP_HIGHER_THAN if the form triggers when the current HP is higher than the specified threshold. - HP_LOWER_EQ_THAN if the form triggers when the current HP is lower or equal than the specified threshold. param3: HP percentage threshold.
    FORM_CHANGE_FAINT, // Form change that activates when the Pokémon faints, either in battle or in the overworld by poison. If species is not specified and it's on the player's side, it will try to use the value saved in gBattleStruct->changedSpecies from a previous form change. No parameters.
    FORM_CHANGE_END_BATTLE, // Form change that activates at the end of a battle. If species is not specified and it's on the player's side, it will try to use the value saved in gBattleStruct->changedSpecies from a previous form change.
    FORM_CHANGE_BATTLE_SWITCH, // Form change that activates when the Pokémon is switched out in battle. param1: ability to check, optional.

    FORM_CHANGE_TERMINATOR,
};

// FORM_CHANGE_BATTLE_HP_PERCENT param2 arguments
#define HP_HIGHER_THAN      1
#define HP_LOWER_EQ_THAN    2

#endif // GUARD_CONSTANTS_FORM_CHANGE_TYPES_H
