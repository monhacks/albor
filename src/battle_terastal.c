#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_interface.h"
#include "battle_terastal.h"
#include "battle_gimmick.h"
#include "battle_scripts.h"
#include "event_data.h"
#include "item.h"
#include "palette.h"
#include "pokemon.h"
#include "safari_zone.h"
#include "sprite.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/hold_effects.h"
#include "constants/rgb.h"

// Sets flags and variables upon a battler's Terastallization.
void ActivateTera(u32 battler)
{
    u32 side = GetBattlerSide(battler);

    // Set appropriate flags.
    SetActiveGimmick(battler, GIMMICK_TERA);
    SetGimmickAsActivated(battler, GIMMICK_TERA);

    // Remove Tera Orb charge.
    if (B_FLAG_TERA_ORB_CHARGED != 0
        && (B_FLAG_TERA_ORB_NO_COST == 0 || !FlagGet(B_FLAG_TERA_ORB_NO_COST))
        && side == B_SIDE_PLAYER
        && !(IsDoubleBattle() && !IsPartnerMonFromSameTrainer(battler)))
    {
        FlagClear(B_FLAG_TERA_ORB_CHARGED);
    }

    // Execute battle script.
    PREPARE_TYPE_BUFFER(gBattleTextBuff1, GetBattlerTeraType(battler));
    if (TryBattleFormChange(gBattlerAttacker, FORM_CHANGE_BATTLE_TERASTALLIZATION))
        BattleScriptExecute(BattleScript_TeraFormChange);
    else
        BattleScriptExecute(BattleScript_Terastallization);
}

// Applies palette blend and enables UI indicator after animation has played
void ApplyBattlerVisualsForTeraAnim(u32 battler)
{
    struct Pokemon *party = GetBattlerParty(battler);
    u32 index = gBattlerPartyIndexes[battler];

    // Show indicator and do palette blend.
    UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &party[index], HEALTHBOX_ALL);
    BlendPalette(OBJ_PLTT_ID(battler), 16, 8, GetTeraTypeRGB(GetBattlerTeraType(battler)));
    CpuCopy32(gPlttBufferFaded + OBJ_PLTT_ID(battler), gPlttBufferUnfaded + OBJ_PLTT_ID(battler), PLTT_SIZEOF(16));

    // We apply the animation behind a white screen, so restore the blended color here to avoid a pop
    BlendPalette(OBJ_PLTT_ID(battler), 16, 16, RGB_WHITEALPHA);
}

// Returns whether a battler can Terastallize.
bool32 CanTerastallize(u32 battler)
{
    return FALSE;
}

// Returns a battler's Tera type.
u32 GetBattlerTeraType(u32 battler)
{
    return GetMonData(&GetBattlerParty(battler)[gBattlerPartyIndexes[battler]], MON_DATA_TERA_TYPE);
}

// Uses up a type's Stellar boost.
void ExpendTypeStellarBoost(u32 battler, u32 type)
{

}

// Checks whether a type's Stellar boost has been expended.
bool32 IsTypeStellarBoosted(u32 battler, u32 type)
{
    if (type < 32) // avoid OOB access
        return !(gBattleStruct->stellarBoostFlags[GetBattlerSide(battler)] & (1u << type));
    else
        return FALSE;
}

// Returns the STAB power multiplier to use when Terastallized.
// Power multipliers from Smogon Research thread.
uq4_12_t GetTeraMultiplier(u32 battler, u32 type)
{
    return UQ_4_12(1.0);
}

u16 GetTeraTypeRGB(u32 type)
{
    return 0;
}
