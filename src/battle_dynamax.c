#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_scripts.h"
#include "battle_script_commands.h"
#include "battle_gimmick.h"
#include "data.h"
#include "event_data.h"
#include "graphics.h"
#include "item.h"
#include "pokemon.h"
#include "random.h"
#include "sprite.h"
#include "string_util.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_string_ids.h"
#include "constants/flags.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"

// Returns whether a battler can Dynamax.
bool32 CanDynamax(u32 battler)
{
    return FALSE;
}

// Applies the HP Multiplier for Dynamaxed Pokemon and Raid Bosses.
void ApplyDynamaxHPMultiplier(u32 battler, struct Pokemon* mon)
{

}

// Sets flags used for Dynamaxing and checks Gigantamax forms.
void ActivateDynamax(u32 battler)
{

}

// Unsets the flags used for Dynamaxing and reverts max HP if needed.
void UndoDynamax(u32 battler)
{
    u8 side = GetBattlerSide(battler);
    u8 monId = gBattlerPartyIndexes[battler];

    // Revert HP if battler is still Dynamaxed.
    if (GetActiveGimmick(battler) == GIMMICK_DYNAMAX)
    {
        struct Pokemon *mon = (side == B_SIDE_PLAYER) ? &gPlayerParty[monId] : &gEnemyParty[monId];
        u16 mult = UQ_4_12(1.0/1.5); // placeholder
        gBattleMons[battler].hp = UQ_4_12_TO_INT((GetMonData(mon, MON_DATA_HP) * mult + 1) + UQ_4_12_ROUND); // round up
        SetMonData(mon, MON_DATA_HP, &gBattleMons[battler].hp);
        CalculateMonStats(mon);
    }

    // Makes sure there are no Dynamax flags set, including on switch / faint.
    SetActiveGimmick(battler, GIMMICK_NONE);
    gBattleStruct->dynamax.dynamaxTurns[battler] = 0;
}

// Certain moves are blocked by Max Guard that normally ignore protection.
bool32 IsMoveBlockedByMaxGuard(u32 move)
{
    switch (move)
    {
        case MOVE_BLOCK:
        case MOVE_FLOWER_SHIELD:
        case MOVE_GEAR_UP:
        case MOVE_MAGNETIC_FLUX:
        case MOVE_PHANTOM_FORCE:
        case MOVE_PSYCH_UP:
        case MOVE_SHADOW_FORCE:
        case MOVE_TEATIME:
        case MOVE_TRANSFORM:
            return TRUE;
    }
    return FALSE;
}

bool32 IsMoveBlockedByDynamax(u32 move)
{
    return FALSE;
}

// Assigns the multistring to use for the "Damage Non- Types" G-Max effect.
void ChooseDamageNonTypesString(u8 type)
{
    switch (type)
    {
        case TIPO_PLANTA:
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_TRAPPED_WITH_VINES;
            break;
        case TIPO_AGUA:
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_CAUGHT_IN_VORTEX;
            break;
        case TIPO_FUEGO:
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SURROUNDED_BY_FIRE;
            break;
        case TIPO_ROCA:
            gBattleCommunication[MULTISTRING_CHOOSER] = B_MSG_SURROUNDED_BY_ROCKS;
            break;
    }
}

// Sets up sharp steel on the target's side.
void BS_SetSteelsurge(void)
{
    NATIVE_ARGS(const u8 *failInstr);
    u8 targetSide = GetBattlerSide(gBattlerTarget);
    if (gSideStatuses[targetSide] & SIDE_STATUS_STEELSURGE)
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
    else
    {
        gSideStatuses[targetSide] |= SIDE_STATUS_STEELSURGE;
        gSideTimers[targetSide].steelsurgeAmount = 1;
        gBattlescriptCurrInstr = cmd->nextInstr;
    }
}

// Heals one-sixth of the target's HP, including for Dynamaxed targets.
void BS_HealOneSixth(void)
{
    NATIVE_ARGS(const u8* failInstr);
    gBattleMoveDamage = gBattleMons[gBattlerTarget].maxHP / 6;
    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1;
    gBattleMoveDamage *= -1;

    if (gBattleMons[gBattlerTarget].hp == gBattleMons[gBattlerTarget].maxHP)
        gBattlescriptCurrInstr = cmd->failInstr;    // fail
    else
        gBattlescriptCurrInstr = cmd->nextInstr;    // can heal
}

// Recycles the target's item if it is specifically holding a berry.
void BS_TryRecycleBerry(void)
{
    NATIVE_ARGS(const u8 *failInstr);
    u16* usedHeldItem = &gBattleStruct->usedHeldItems[gBattlerPartyIndexes[gBattlerTarget]][GetBattlerSide(gBattlerTarget)];
    if (gBattleMons[gBattlerTarget].item == ITEM_NONE
        && gBattleStruct->changedItems[gBattlerTarget] == ITEM_NONE   // Will not inherit an item
        && ItemId_GetPocket(*usedHeldItem) == POCKET_BERRIES)
    {
        gLastUsedItem = *usedHeldItem;
        *usedHeldItem = ITEM_NONE;
        gBattleMons[gBattlerTarget].item = gLastUsedItem;

        BtlController_EmitSetMonData(gBattlerTarget, BUFFER_A, REQUEST_HELDITEM_BATTLE, 0, sizeof(gBattleMons[gBattlerTarget].item), &gBattleMons[gBattlerTarget].item);
        MarkBattlerForControllerExec(gBattlerTarget);

        gBattlescriptCurrInstr = cmd->nextInstr;
    }
    else
    {
        gBattlescriptCurrInstr = cmd->failInstr;
    }
}

// Goes to the jump instruction if the target is Dynamaxed.
void BS_JumpIfDynamaxed(void)
{
    NATIVE_ARGS(const u8 *jumpInstr);
    if ((GetActiveGimmick(gBattlerTarget) == GIMMICK_DYNAMAX))
        gBattlescriptCurrInstr = cmd->jumpInstr;
    else
        gBattlescriptCurrInstr = cmd->nextInstr;
}
