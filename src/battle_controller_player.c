#include "global.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_arena.h"
#include "battle_controllers.h"
#include "battle_dome.h"
#include "battle_interface.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_z_move.h"
#include "battle_gimmick.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "link.h"
#include "main.h"
#include "m4a.h"
#include "palette.h"
#include "party_menu.h"
#include "pokeball.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "random.h"
#include "reshow_battle_screen.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"
#include "constants/battle_anim.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_partner.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/party_menu.h"
#include "constants/pokemon_icon.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/rgb.h"
#include "menu.h"
#include "pokemon_summary_screen.h"

static void PlayerBufferExecCompleted(u32 battler);
static void PlayerHandleLoadMonSprite(u32 battler);
static void PlayerHandleSwitchInAnim(u32 battler);
static void PlayerHandleDrawTrainerPic(u32 battler);
static void PlayerHandleTrainerSlide(u32 battler);
static void PlayerHandleTrainerSlideBack(u32 battler);
static void PlayerHandlePaletteFade(u32 battler);
static void PlayerHandleSuccessBallThrowAnim(u32 battler);
static void PlayerHandlePause(u32 battler);
static void PlayerHandleMoveAnimation(u32 battler);
static void PlayerHandlePrintString(u32 battler);
static void PlayerHandlePrintSelectionString(u32 battler);
static void PlayerHandleChooseAction(u32 battler);
static void PlayerHandleYesNoBox(u32 battler);
static void PlayerHandleChooseItem(u32 battler);
static void PlayerHandleChoosePokemon(u32 battler);
static void PlayerHandleHealthBarUpdate(u32 battler);
static void PlayerHandleStatusXor(u32 battler);
static void PlayerHandleDMA3Transfer(u32 battler);
static void PlayerHandlePlayBGM(u32 battler);
static void PlayerHandleTwoReturnValues(u32 battler);
static void PlayerHandleChosenMonReturnValue(u32 battler);
static void PlayerHandleOneReturnValue(u32 battler);
static void PlayerHandleIntroTrainerBallThrow(u32 battler);
static void PlayerHandleDrawPartyStatusSummary(u32 battler);
static void PlayerHandleEndBounceEffect(u32 battler);
static void PlayerHandleBattleAnimation(u32 battler);
static void PlayerHandleLinkStandbyMsg(u32 battler);
static void PlayerHandleResetActionMoveSelection(u32 battler);
static void PlayerHandleBattleDebug(u32 battler);

static void PlayerBufferRunCommand(u32 battler);
static void MoveSelectionDisplayPpNumber(u32 battler);
static void MoveSelectionDisplayMoveType(u32 battler);
static void MoveSelectionDisplayMoveNames(u32 battler);
static void SwitchIn_HandleSoundAndEnd(u32 battler);
static void WaitForMonSelection(u32 battler);
static void CompleteWhenChoseItem(u32 battler);
static void Task_LaunchLvlUpAnim(u8);
static void Task_PrepareToGiveExpWithExpBar(u8);
static void Task_SetControllerToWaitForString(u8);
static void Task_GiveExpWithExpBar(u8);
static void Task_UpdateLvlInHealthbox(u8);
static void PrintLinkStandbyMsg(void);

static void ReloadMoveNames(u32 battler);

#define TAG_ICON_TYPES 30005

static EWRAM_DATA u8 monIconData;
static EWRAM_DATA u8 sIconTypeId[MAX_MON_MOVES] = {0};

static void (*const sPlayerBufferCommands[CONTROLLER_CMDS_COUNT])(u32 battler) =
{
    [CONTROLLER_GETMONDATA]               = BtlController_HandleGetMonData,
    [CONTROLLER_GETRAWMONDATA]            = BtlController_HandleGetRawMonData,
    [CONTROLLER_SETMONDATA]               = BtlController_HandleSetMonData,
    [CONTROLLER_SETRAWMONDATA]            = BtlController_HandleSetRawMonData,
    [CONTROLLER_LOADMONSPRITE]            = PlayerHandleLoadMonSprite,
    [CONTROLLER_SWITCHINANIM]             = PlayerHandleSwitchInAnim,
    [CONTROLLER_RETURNMONTOBALL]          = BtlController_HandleReturnMonToBall,
    [CONTROLLER_DRAWTRAINERPIC]           = PlayerHandleDrawTrainerPic,
    [CONTROLLER_TRAINERSLIDE]             = PlayerHandleTrainerSlide,
    [CONTROLLER_TRAINERSLIDEBACK]         = PlayerHandleTrainerSlideBack,
    [CONTROLLER_FAINTANIMATION]           = BtlController_HandleFaintAnimation,
    [CONTROLLER_PALETTEFADE]              = PlayerHandlePaletteFade,
    [CONTROLLER_SUCCESSBALLTHROWANIM]     = PlayerHandleSuccessBallThrowAnim,
    [CONTROLLER_BALLTHROWANIM]            = PlayerHandleBallThrowAnim,
    [CONTROLLER_PAUSE]                    = PlayerHandlePause,
    [CONTROLLER_MOVEANIMATION]            = PlayerHandleMoveAnimation,
    [CONTROLLER_PRINTSTRING]              = PlayerHandlePrintString,
    [CONTROLLER_PRINTSTRINGPLAYERONLY]    = PlayerHandlePrintSelectionString,
    [CONTROLLER_CHOOSEACTION]             = PlayerHandleChooseAction,
    [CONTROLLER_YESNOBOX]                 = PlayerHandleYesNoBox,
    [CONTROLLER_CHOOSEMOVE]               = PlayerHandleChooseMove,
    [CONTROLLER_OPENBAG]                  = PlayerHandleChooseItem,
    [CONTROLLER_CHOOSEPOKEMON]            = PlayerHandleChoosePokemon,
    [CONTROLLER_HEALTHBARUPDATE]          = PlayerHandleHealthBarUpdate,
    [CONTROLLER_EXPUPDATE]                = PlayerHandleExpUpdate,
    [CONTROLLER_STATUSICONUPDATE]         = BtlController_HandleStatusIconUpdate,
    [CONTROLLER_STATUSANIMATION]          = BtlController_HandleStatusAnimation,
    [CONTROLLER_STATUSXOR]                = PlayerHandleStatusXor,
    [CONTROLLER_DATATRANSFER]             = BtlController_Empty,
    [CONTROLLER_DMA3TRANSFER]             = PlayerHandleDMA3Transfer,
    [CONTROLLER_PLAYBGM]                  = PlayerHandlePlayBGM,
    [CONTROLLER_TWORETURNVALUES]          = PlayerHandleTwoReturnValues,
    [CONTROLLER_CHOSENMONRETURNVALUE]     = PlayerHandleChosenMonReturnValue,
    [CONTROLLER_ONERETURNVALUE]           = PlayerHandleOneReturnValue,
    [CONTROLLER_HITANIMATION]             = BtlController_HandleHitAnimation,
    [CONTROLLER_CANTSWITCH]               = BtlController_Empty,
    [CONTROLLER_PLAYSE]                   = BtlController_HandlePlaySE,
    [CONTROLLER_PLAYFANFAREORBGM]         = BtlController_HandlePlayFanfareOrBGM,
    [CONTROLLER_FAINTINGCRY]              = BtlController_HandleFaintingCry,
    [CONTROLLER_INTROSLIDE]               = BtlController_HandleIntroSlide,
    [CONTROLLER_INTROTRAINERBALLTHROW]    = PlayerHandleIntroTrainerBallThrow,
    [CONTROLLER_DRAWPARTYSTATUSSUMMARY]   = PlayerHandleDrawPartyStatusSummary,
    [CONTROLLER_HIDEPARTYSTATUSSUMMARY]   = BtlController_HandleHidePartyStatusSummary,
    [CONTROLLER_ENDBOUNCE]                = PlayerHandleEndBounceEffect,
    [CONTROLLER_SPRITEINVISIBILITY]       = BtlController_HandleSpriteInvisibility,
    [CONTROLLER_BATTLEANIMATION]          = PlayerHandleBattleAnimation,
    [CONTROLLER_LINKSTANDBYMSG]           = PlayerHandleLinkStandbyMsg,
    [CONTROLLER_RESETACTIONMOVESELECTION] = PlayerHandleResetActionMoveSelection,
    [CONTROLLER_DEBUGMENU]                = PlayerHandleBattleDebug,
    [CONTROLLER_TERMINATOR_NOP]           = BtlController_TerminatorNop
};

void SetControllerToPlayer(u32 battler)
{
    sIconTypeId[0] = 0xFF;
    sIconTypeId[1] = 0xFF;
    sIconTypeId[2] = 0xFF;
    sIconTypeId[3] = 0xFF;
    gBattlerControllerEndFuncs[battler] = PlayerBufferExecCompleted;
    gBattlerControllerFuncs[battler] = PlayerBufferRunCommand;
    gDoingBattleAnim = FALSE;
    gPlayerDpadHoldFrames = 0;
}

static void PlayerBufferExecCompleted(u32 battler)
{
    gBattlerControllerFuncs[battler] = PlayerBufferRunCommand;
    gBattleControllerExecFlags &= ~(1u << battler);
}

static void PlayerBufferRunCommand(u32 battler)
{
    if (gBattleControllerExecFlags & (1u << battler))
    {
        if (gBattleResources->bufferA[battler][0] < ARRAY_COUNT(sPlayerBufferCommands))
            sPlayerBufferCommands[gBattleResources->bufferA[battler][0]](battler);
        else
            PlayerBufferExecCompleted(battler);
    }
}

static void CompleteOnBattlerSpritePosX_0(u32 battler)
{
    if (gSprites[gBattlerSpriteIds[battler]].x2 == 0)
        PlayerBufferExecCompleted(battler);
}

static u16 GetPrevBall(u16 ballId)
{
    u16 ballPrev;
    s32 i, j;
    CompactItemsInBagPocket(&gBagPockets[BALLS_POCKET]);
    for (i = 0; i < gBagPockets[BALLS_POCKET].capacity; i++)
    {
        if (ballId == gBagPockets[BALLS_POCKET].itemSlots[i].itemId)
        {
            if (i <= 0)
            {
                for (j = gBagPockets[BALLS_POCKET].capacity - 1; j >= 0; j--)
                {
                    ballPrev = gBagPockets[BALLS_POCKET].itemSlots[j].itemId;
                    if (ballPrev != ITEM_NONE)
                        return ballPrev;
                }
            }
            i--;
            break;
        }
    }
    return gBagPockets[BALLS_POCKET].itemSlots[i].itemId;
}

static u32 GetNextBall(u32 ballId)
{
    u32 ballNext = ITEM_NONE;
    s32 i;
    CompactItemsInBagPocket(&gBagPockets[BALLS_POCKET]);
    for (i = 1; i < gBagPockets[BALLS_POCKET].capacity; i++)
    {
        if (ballId == gBagPockets[BALLS_POCKET].itemSlots[i-1].itemId)
        {
            ballNext = gBagPockets[BALLS_POCKET].itemSlots[i].itemId;
            break;
        }
    }
    if (ballNext == ITEM_NONE)
        return gBagPockets[BALLS_POCKET].itemSlots[0].itemId; // Zeroth slot
    else
        return ballNext;
}

static void HandleInputChooseAction(u32 battler)
{
    DoBounceEffect(battler, BOUNCE_HEALTHBOX, 7, 1);
    DoBounceEffect(battler, BOUNCE_MON, 7, 1);

    if (sIconTypeId[0] != 0xFF)
    {
        DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
        sIconTypeId[0] = 0xFF;
    }
    if (sIconTypeId[1] != 0xFF)
    {
        DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
        sIconTypeId[1] = 0xFF;
    }
    if (sIconTypeId[2] != 0xFF)
    {
        DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
        sIconTypeId[2] = 0xFF;
    }
    if (sIconTypeId[3] != 0xFF)
    {
        DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
        sIconTypeId[3] = 0xFF;
    }
    gPlayerDpadHoldFrames = 0;

    if (B_LAST_USED_BALL == TRUE && B_LAST_USED_BALL_CYCLE == TRUE)
    {
        if (!gLastUsedBallMenuPresent)
        {
            gBattleStruct->ackBallUseBtn = FALSE;
        }
        else if (JOY_NEW(B_LAST_USED_BALL_BUTTON))
        {
            gBattleStruct->ackBallUseBtn = TRUE;
            gBattleStruct->ballSwapped = FALSE;
            ArrowsChangeColorLastBallCycle(TRUE);
        }

        if (gBattleStruct->ackBallUseBtn)
        {
            if (JOY_HELD(B_LAST_USED_BALL_BUTTON) && (JOY_NEW(DPAD_DOWN) || JOY_NEW(DPAD_RIGHT)))
            {
                bool32 sameBall = FALSE;
                u32 nextBall = GetNextBall(gBallToDisplay);
                gBattleStruct->ballSwapped = TRUE;
                if (gBallToDisplay == nextBall)
                    sameBall = TRUE;
                else
                    gBallToDisplay = nextBall;
                SwapBallToDisplay(sameBall);
                PlaySE(SE_SELECT);
            }
            else if (JOY_HELD(B_LAST_USED_BALL_BUTTON) && (JOY_NEW(DPAD_UP) || JOY_NEW(DPAD_LEFT)))
            {
                bool32 sameBall = FALSE;
                u32 prevBall = GetPrevBall(gBallToDisplay);
                gBattleStruct->ballSwapped = TRUE;
                if (gBallToDisplay == prevBall)
                    sameBall = TRUE;
                else
                    gBallToDisplay = prevBall;
                SwapBallToDisplay(sameBall);
                PlaySE(SE_SELECT);
            }
            else if (JOY_NEW(B_BUTTON) || (!JOY_HELD(B_LAST_USED_BALL_BUTTON) && gBattleStruct->ballSwapped))
            {
                gBattleStruct->ackBallUseBtn = FALSE;
                gBattleStruct->ballSwapped = FALSE;
                ArrowsChangeColorLastBallCycle(FALSE);
            }
            else if (!JOY_HELD(B_LAST_USED_BALL_BUTTON) && CanThrowLastUsedBall())
            {
                gBattleStruct->ackBallUseBtn = FALSE;
                PlaySE(SE_SELECT);
                ArrowsChangeColorLastBallCycle(FALSE);
                TryHideLastUsedBall();
                BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_THROW_BALL, 0);
                PlayerBufferExecCompleted(battler);
            }
            return;
        }
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        TryHideLastUsedBall();

        switch (gActionSelectionCursor[battler])
        {
        case 0:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_MOVE, 0);
            break;
        case 1:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_SWITCH, 0);
            break;
        case 2:
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_RUN, 0);
            break;
        }
        PlayerBufferExecCompleted(battler);
    }
    else if (JOY_NEW(DPAD_LEFT))
    {
        if (gActionSelectionCursor[battler] & 1) // De Pokémon a Luchar
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] -= 1;
            LoadCompressedPalette(gBattleActionsPalFight, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        else if (gActionSelectionCursor[battler] & 2)// De Huir a Pokémon
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] -= 1;
            LoadCompressedPalette(gBattleActionsPalPokemon, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        else // De Luchar a Huir
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] += 2;
            LoadCompressedPalette(gBattleActionsPalRun, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        if (gActionSelectionCursor[battler] & 2) // De Huir a Luchar
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] -= 2;
            LoadCompressedPalette(gBattleActionsPalFight, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        else if (gActionSelectionCursor[battler] & 1) // De Pokémon a Huir
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] += 1;
            LoadCompressedPalette(gBattleActionsPalRun, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
        else // De Luchar a Pokémon
        {
            PlaySE(SE_SELECT);
            gActionSelectionCursor[battler] += 1;
            LoadCompressedPalette(gBattleActionsPalPokemon, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
        }
    }
    else if (JOY_NEW(B_BUTTON) || gPlayerDpadHoldFrames > 59)
    {
        if (IsDoubleBattle()
         && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT
         && !(gAbsentBattlerFlags & (1u << GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)))
         && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
        {
            PlaySE(SE_SELECT);
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_CANCEL_PARTNER, 0);
            PlayerBufferExecCompleted(battler);
            DestroySpriteAndFreeResources(&gSprites[monIconData]);
            MoveSelectionDestroyCursor();
        }
        else if (B_QUICK_MOVE_CURSOR_TO_RUN)
        {
            if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER)) // If wild battle, pressing B moves cursor to "Run".
            {
                PlaySE(SE_SELECT);
                gActionSelectionCursor[battler] = 2;
                LoadCompressedPalette(gBattleActionsPalRun, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
            }
        }
    }
    else if (JOY_NEW(START_BUTTON))
    {
        SwapHpBarsWithHpText();
    }
    else if (DEBUG_BATTLE_MENU == TRUE && JOY_NEW(SELECT_BUTTON))
    {
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_DEBUG, 0);
        PlayerBufferExecCompleted(battler);
    }
    else if (B_LAST_USED_BALL == TRUE && B_LAST_USED_BALL_CYCLE == FALSE
             && JOY_NEW(B_LAST_USED_BALL_BUTTON) && CanThrowLastUsedBall())
    {
        PlaySE(SE_SELECT);
        TryHideLastUsedBall();
        BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_THROW_BALL, 0);
        PlayerBufferExecCompleted(battler);
        DestroySpriteAndFreeResources(&gSprites[monIconData]);
    }
}

void HandleInputChooseTarget(u32 battler)
{
    s32 i;
    static const u8 identities[MAX_BATTLERS_COUNT] = {B_POSITION_PLAYER_LEFT, B_POSITION_PLAYER_RIGHT, B_POSITION_OPPONENT_RIGHT, B_POSITION_OPPONENT_LEFT};
    u16 move = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_MOVE1 + gMoveSelectionCursor[battler]);
    u16 moveTarget = GetBattlerMoveTargetType(battler, move);

    DoBounceEffect(gMultiUsePlayerCursor, BOUNCE_HEALTHBOX, 15, 1);
    for (i = 0; i < gBattlersCount; i++)
    {
        if (i != gMultiUsePlayerCursor)
            EndBounceEffect(i, BOUNCE_HEALTHBOX);
    }

    gPlayerDpadHoldFrames = 0;

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_HideAsMoveTarget;
        if (gBattleStruct->gimmick.playerSelect)
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | RET_GIMMICK | (gMultiUsePlayerCursor << 8));
        else
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | (gMultiUsePlayerCursor << 8));
        EndBounceEffect(gMultiUsePlayerCursor, BOUNCE_HEALTHBOX);
        TryHideLastUsedBall();
        HideGimmickTriggerSprite();
        PlayerBufferExecCompleted(battler);
        if (sIconTypeId[0] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
            sIconTypeId[0] = 0xFF;
        }
        if (sIconTypeId[1] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
            sIconTypeId[1] = 0xFF;
        }
        if (sIconTypeId[2] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
            sIconTypeId[2] = 0xFF;
        }
        if (sIconTypeId[3] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
            sIconTypeId[3] = 0xFF;
        }
        MoveSelectionDestroyCursor();
    }
    else if (JOY_NEW(B_BUTTON) || gPlayerDpadHoldFrames > 59)
    {
        PlaySE(SE_SELECT);
        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_HideAsMoveTarget;
        gBattlerControllerFuncs[battler] = HandleInputChooseMove;
        DoBounceEffect(battler, BOUNCE_HEALTHBOX, 7, 1);
        DoBounceEffect(battler, BOUNCE_MON, 7, 1);
        EndBounceEffect(gMultiUsePlayerCursor, BOUNCE_HEALTHBOX);
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_UP))
    {
        PlaySE(SE_SELECT);
        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_HideAsMoveTarget;

        if (moveTarget == (MOVE_TARGET_USER | MOVE_TARGET_ALLY))
        {
            gMultiUsePlayerCursor ^= BIT_FLANK;
        }
        else
        {
            do
            {
                u8 currSelIdentity = GetBattlerPosition(gMultiUsePlayerCursor);

                for (i = 0; i < MAX_BATTLERS_COUNT; i++)
                {
                    if (currSelIdentity == identities[i])
                        break;
                }
                do
                {
                    if (--i < 0)
                        i = MAX_BATTLERS_COUNT - 1;
                    gMultiUsePlayerCursor = GetBattlerAtPosition(identities[i]);
                } while (gMultiUsePlayerCursor == gBattlersCount);

                i = 0;
                switch (GetBattlerPosition(gMultiUsePlayerCursor))
                {
                case B_POSITION_PLAYER_LEFT:
                case B_POSITION_PLAYER_RIGHT:
                    if (battler != gMultiUsePlayerCursor)
                        i++;
                    else if (moveTarget & MOVE_TARGET_USER_OR_SELECTED)
                        i++;
                    break;
                case B_POSITION_OPPONENT_LEFT:
                case B_POSITION_OPPONENT_RIGHT:
                    i++;
                    break;
                }

                if (gAbsentBattlerFlags & (1u << gMultiUsePlayerCursor)
                 || !CanTargetBattler(battler, gMultiUsePlayerCursor, move))
                    i = 0;
            } while (i == 0);
        }
        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_ShowAsMoveTarget;
    }
    else if (JOY_NEW(DPAD_RIGHT | DPAD_DOWN))
    {
        PlaySE(SE_SELECT);
        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_HideAsMoveTarget;

        if (moveTarget == (MOVE_TARGET_USER | MOVE_TARGET_ALLY))
        {
            gMultiUsePlayerCursor ^= BIT_FLANK;
        }
        else
        {
            do
            {
                u8 currSelIdentity = GetBattlerPosition(gMultiUsePlayerCursor);

                for (i = 0; i < MAX_BATTLERS_COUNT; i++)
                {
                    if (currSelIdentity == identities[i])
                        break;
                }
                do
                {
                    if (++i > 3)
                        i = 0;
                    gMultiUsePlayerCursor = GetBattlerAtPosition(identities[i]);
                } while (gMultiUsePlayerCursor == gBattlersCount);

                i = 0;
                switch (GetBattlerPosition(gMultiUsePlayerCursor))
                {
                case B_POSITION_PLAYER_LEFT:
                case B_POSITION_PLAYER_RIGHT:
                    if (battler != gMultiUsePlayerCursor)
                        i++;
                    else if (moveTarget & MOVE_TARGET_USER_OR_SELECTED)
                        i++;
                    break;
                case B_POSITION_OPPONENT_LEFT:
                case B_POSITION_OPPONENT_RIGHT:
                    i++;
                    break;
                }

                if (gAbsentBattlerFlags & (1u << gMultiUsePlayerCursor)
                 || !CanTargetBattler(battler, gMultiUsePlayerCursor, move))
                    i = 0;
            } while (i == 0);
        }

        gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_ShowAsMoveTarget;
    }
}

static void HideAllTargets(void)
{
    s32 i;
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && gBattleSpritesDataPtr->healthBoxesData[i].healthboxIsBouncing)
        {
            gSprites[gBattlerSpriteIds[i]].callback = SpriteCB_HideAsMoveTarget;
            EndBounceEffect(i, BOUNCE_HEALTHBOX);
        }
    }
}

static void HideShownTargets(u32 battler)
{
    s32 i;
    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        if (IsBattlerAlive(i) && gBattleSpritesDataPtr->healthBoxesData[i].healthboxIsBouncing && i != battler)
        {
            gSprites[gBattlerSpriteIds[i]].callback = SpriteCB_HideAsMoveTarget;
            EndBounceEffect(i, BOUNCE_HEALTHBOX);
        }
    }
}

void HandleInputShowEntireFieldTargets(u32 battler)
{
    gPlayerDpadHoldFrames = 0;

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        HideAllTargets();
        if (gBattleStruct->gimmick.playerSelect)
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | RET_GIMMICK | (gMultiUsePlayerCursor << 8));
        else
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | (gMultiUsePlayerCursor << 8));
        HideGimmickTriggerSprite();
        PlayerBufferExecCompleted(battler);
        if (sIconTypeId[0] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
            sIconTypeId[0] = 0xFF;
        }
        if (sIconTypeId[1] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
            sIconTypeId[1] = 0xFF;
        }
        if (sIconTypeId[2] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
            sIconTypeId[2] = 0xFF;
        }
        if (sIconTypeId[3] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
            sIconTypeId[3] = 0xFF;
        }
        MoveSelectionDestroyCursor();
    }
    else if (JOY_NEW(B_BUTTON) || gPlayerDpadHoldFrames > 59)
    {
        PlaySE(SE_SELECT);
        HideAllTargets();
        gBattlerControllerFuncs[battler] = HandleInputChooseMove;
        DoBounceEffect(battler, BOUNCE_HEALTHBOX, 7, 1);
        DoBounceEffect(battler, BOUNCE_MON, 7, 1);
    }
}

void HandleInputShowTargets(u32 battler)
{
    gPlayerDpadHoldFrames = 0;

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        HideShownTargets(battler);
        if (gBattleStruct->gimmick.playerSelect)
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | RET_GIMMICK | (gMultiUsePlayerCursor << 8));
        else
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | (gMultiUsePlayerCursor << 8));
        HideGimmickTriggerSprite();
        TryHideLastUsedBall();
        PlayerBufferExecCompleted(battler);
        if (sIconTypeId[0] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
            sIconTypeId[0] = 0xFF;
        }
        if (sIconTypeId[1] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
            sIconTypeId[1] = 0xFF;
        }
        if (sIconTypeId[2] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
            sIconTypeId[2] = 0xFF;
        }
        if (sIconTypeId[3] != 0xFF)
        {
            DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
            sIconTypeId[3] = 0xFF;
        }
        MoveSelectionDestroyCursor();
    }
    else if (JOY_NEW(B_BUTTON) || gPlayerDpadHoldFrames > 59)
    {
        PlaySE(SE_SELECT);
        HideShownTargets(battler);
        gBattlerControllerFuncs[battler] = HandleInputChooseMove;
        DoBounceEffect(battler, BOUNCE_HEALTHBOX, 7, 1);
        DoBounceEffect(battler, BOUNCE_MON, 7, 1);
    }
}

static void TryShowAsTarget(u32 battler)
{
    if (IsBattlerAlive(battler))
    {
        DoBounceEffect(battler, BOUNCE_HEALTHBOX, 15, 1);
        gSprites[gBattlerSpriteIds[battler]].callback = SpriteCB_ShowAsMoveTarget;
    }
}

void HandleInputChooseMove(u32 battler)
{
    u16 moveTarget;
    u32 canSelectTarget = 0;
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);

    gPlayerDpadHoldFrames = 0;

    if (JOY_NEW(A_BUTTON) && !gBattleStruct->descriptionSubmenu)
    {
        PlaySE(SE_SELECT);

        moveTarget = GetBattlerMoveTargetType(battler, moveInfo->moves[gMoveSelectionCursor[battler]]);

        if (gBattleStruct->zmove.viewing)
        {
            gBattleStruct->zmove.viewing = FALSE;
            if (gMovesInfo[moveInfo->moves[gMoveSelectionCursor[battler]]].category != CATEGORIA_ESTADO)
                moveTarget = MOVE_TARGET_SELECTED;  //damaging z moves always have selected target
        }

        // Status moves turn into Max Guard when Dynamaxed, targets user.
        if (GetActiveGimmick(battler) == GIMMICK_DYNAMAX || IsGimmickSelected(battler, GIMMICK_DYNAMAX))
            moveTarget = gMovesInfo[GetMaxMove(battler, moveInfo->moves[gMoveSelectionCursor[battler]])].target;

        if (moveTarget & MOVE_TARGET_USER)
            gMultiUsePlayerCursor = battler;
        else
            gMultiUsePlayerCursor = GetBattlerAtPosition(BATTLE_OPPOSITE(GetBattlerSide(battler)));

        if (!gBattleResources->bufferA[battler][1]) // not a double battle
        {
            if (moveTarget & MOVE_TARGET_USER_OR_SELECTED && !gBattleResources->bufferA[battler][2])
                canSelectTarget = 1;
        }
        else // double battle
        {
            if (!(moveTarget & (MOVE_TARGET_RANDOM | MOVE_TARGET_BOTH | MOVE_TARGET_DEPENDS | MOVE_TARGET_FOES_AND_ALLY | MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_USER | MOVE_TARGET_ALLY)))
                canSelectTarget = 1; // either selected or user
            if (moveTarget == (MOVE_TARGET_USER | MOVE_TARGET_ALLY) && IsBattlerAlive(BATTLE_PARTNER(battler)))
                canSelectTarget = 1;

            if (moveInfo->currentPp[gMoveSelectionCursor[battler]] == 0)
            {
                canSelectTarget = 0;
            }
            else if (!(moveTarget & (MOVE_TARGET_USER | MOVE_TARGET_USER_OR_SELECTED)) && CountAliveMonsInBattle(BATTLE_ALIVE_EXCEPT_BATTLER, battler) <= 1)
            {
                gMultiUsePlayerCursor = GetDefaultMoveTarget(battler);
                canSelectTarget = 0;
            }

            if (B_SHOW_TARGETS == TRUE)
            {
                // Show all available targets for multi-target moves
                if ((moveTarget & MOVE_TARGET_ALL_BATTLERS) == MOVE_TARGET_ALL_BATTLERS)
                {
                    u32 i = 0;
                    for (i = 0; i < gBattlersCount; i++)
                        TryShowAsTarget(i);

                    canSelectTarget = 3;
                }
                else if (moveTarget & (MOVE_TARGET_OPPONENTS_FIELD | MOVE_TARGET_BOTH | MOVE_TARGET_FOES_AND_ALLY))
                {
                    TryShowAsTarget(gMultiUsePlayerCursor);
                    TryShowAsTarget(BATTLE_PARTNER(gMultiUsePlayerCursor));
                    if (moveTarget & MOVE_TARGET_FOES_AND_ALLY)
                        TryShowAsTarget(BATTLE_PARTNER(battler));
                    canSelectTarget = 2;
                }
            }
        }

        switch (canSelectTarget)
        {
        case 0:
        default:
            if (gBattleStruct->gimmick.playerSelect)
                BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | RET_GIMMICK | (gMultiUsePlayerCursor << 8));
            else
                BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, gMoveSelectionCursor[battler] | (gMultiUsePlayerCursor << 8));
            HideGimmickTriggerSprite();
            TryHideLastUsedBall();
            PlayerBufferExecCompleted(battler);
            if (sIconTypeId[0] != 0xFF)
            {
                DestroySpriteAndFreeResources(&gSprites[sIconTypeId[0]]);
                sIconTypeId[0] = 0xFF;
            }
            if (sIconTypeId[1] != 0xFF)
            {
                DestroySpriteAndFreeResources(&gSprites[sIconTypeId[1]]);
                sIconTypeId[1] = 0xFF;
            }
            if (sIconTypeId[2] != 0xFF)
            {
                DestroySpriteAndFreeResources(&gSprites[sIconTypeId[2]]);
                sIconTypeId[2] = 0xFF;
            }
            if (sIconTypeId[3] != 0xFF)
            {
                DestroySpriteAndFreeResources(&gSprites[sIconTypeId[3]]);
                sIconTypeId[3] = 0xFF;
            }
            MoveSelectionDestroyCursor();
            break;
        case 1:
            gBattlerControllerFuncs[battler] = HandleInputChooseTarget;

            if (moveTarget & (MOVE_TARGET_USER | MOVE_TARGET_USER_OR_SELECTED))
                gMultiUsePlayerCursor = battler;
            else if (gAbsentBattlerFlags & (1u << GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)))
                gMultiUsePlayerCursor = GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT);
            else
                gMultiUsePlayerCursor = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);

            gSprites[gBattlerSpriteIds[gMultiUsePlayerCursor]].callback = SpriteCB_ShowAsMoveTarget;
            break;
        case 2:
            gBattlerControllerFuncs[battler] = HandleInputShowTargets;
            break;
        case 3: // Entire field
            gBattlerControllerFuncs[battler] = HandleInputShowEntireFieldTargets;
            break;
        }
    }
    else if ((JOY_NEW(B_BUTTON) || gPlayerDpadHoldFrames > 59)  && !gBattleStruct->descriptionSubmenu)
    {
        PlaySE(SE_SELECT);
        gBattleStruct->gimmick.playerSelect = FALSE;
        if (gBattleStruct->zmove.viewing)
        {
            ReloadMoveNames(battler);
        }
        else
        {
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 10, 0xFFFF);
            HideGimmickTriggerSprite();
            PlayerBufferExecCompleted(battler);
            LoadBattleMenuWindowGfx();
            MoveSelectionDestroyCursor();
        }
    }
    else if (JOY_NEW(DPAD_LEFT) && !gBattleStruct->zmove.viewing)
    {
        if (gMoveSelectionCursor[battler] & 1)
        {
            MoveSelectionDestroyCursor();
            gMoveSelectionCursor[battler] ^= 1;
            PlaySE(SE_SELECT);
            MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
            MoveSelectionDisplayPpNumber(battler);
            MoveSelectionDisplayMoveType(battler);
        }
    }
    else if (JOY_NEW(DPAD_RIGHT) && !gBattleStruct->zmove.viewing)
    {
        if (!(gMoveSelectionCursor[battler] & 1)
         && (gMoveSelectionCursor[battler] ^ 1) < gNumberOfMovesToChoose)
        {
            MoveSelectionDestroyCursor();
            gMoveSelectionCursor[battler] ^= 1;
            PlaySE(SE_SELECT);
            MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
            MoveSelectionDisplayPpNumber(battler);
            MoveSelectionDisplayMoveType(battler);
        }
    }
    else if (JOY_NEW(DPAD_UP) && !gBattleStruct->zmove.viewing)
    {
        if (gMoveSelectionCursor[battler] & 2)
        {
            MoveSelectionDestroyCursor();
            gMoveSelectionCursor[battler] ^= 2;
            PlaySE(SE_SELECT);
            MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
            MoveSelectionDisplayPpNumber(battler);
            MoveSelectionDisplayMoveType(battler);
        }
    }
    else if (JOY_NEW(DPAD_DOWN) && !gBattleStruct->zmove.viewing)
    {
        if (!(gMoveSelectionCursor[battler] & 2)
         && (gMoveSelectionCursor[battler] ^ 2) < gNumberOfMovesToChoose)
        {
            MoveSelectionDestroyCursor();
            gMoveSelectionCursor[battler] ^= 2;
            PlaySE(SE_SELECT);
            MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
            MoveSelectionDisplayPpNumber(battler);
            MoveSelectionDisplayMoveType(battler);
        }
    }
}

static void ReloadMoveNames(u32 battler)
{
    MoveSelectionDestroyCursor();
    MoveSelectionDisplayMoveNames(battler);
    MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
    MoveSelectionDisplayPpNumber(battler);
    MoveSelectionDisplayMoveType(battler);
}

static void Intro_DelayAndEnd(u32 battler)
{
    if (--gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay == (u8)-1)
    {
        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 0;
        PlayerBufferExecCompleted(battler);
    }
}

static void Intro_WaitForShinyAnimAndHealthbox(u32 battler)
{
    bool8 healthboxAnimDone = FALSE;

    // Check if healthbox has finished sliding in
    if (TwoPlayerIntroMons(battler) && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
         && gSprites[gHealthboxSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
            healthboxAnimDone = TRUE;
    }
    else
    {
        if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy)
            healthboxAnimDone = TRUE;
    }

    // If healthbox and shiny anim are done
    if (healthboxAnimDone && gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim
        && gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim)
    {
        // Reset shiny anim (even if it didn't occur)
        gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].finishedShinyMonAnim = FALSE;
        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);

        if (TwoPlayerIntroMons(battler))
            HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], BATTLE_PARTNER(battler));

        gBattleSpritesDataPtr->healthBoxesData[battler].introEndDelay = 3;
        gBattlerControllerFuncs[battler] = Intro_DelayAndEnd;
    }
}

static void Intro_TryShinyAnimShowHealthbox(u32 battler)
{
    bool32 bgmRestored = FALSE;
    bool32 battlerAnimsDone = FALSE;

    // Start shiny animation if applicable for 1st Pokémon
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
        TryShinyAnimation(battler, &gPlayerParty[gBattlerPartyIndexes[battler]]);

    // Start shiny animation if applicable for 2nd Pokémon
    if (!gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].triedShinyMonAnim
     && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
        TryShinyAnimation(BATTLE_PARTNER(battler), &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]]);

    // Show healthbox after ball anim
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive
     && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].ballAnimActive)
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted)
        {
            if (TwoPlayerIntroMons(battler) && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            {
                UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battler)], &gPlayerParty[gBattlerPartyIndexes[BATTLE_PARTNER(battler)]], HEALTHBOX_ALL);
                StartHealthboxSlideIn(BATTLE_PARTNER(battler));
                SetHealthboxSpriteVisible(gHealthboxSpriteIds[BATTLE_PARTNER(battler)]);
            }
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
            StartHealthboxSlideIn(battler);
            SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        }
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = TRUE;
    }

    // Restore bgm after cry has played and healthbox anim is started
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].waitForCry
        && gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted
        && !gBattleSpritesDataPtr->healthBoxesData[BATTLE_PARTNER(battler)].waitForCry
        && !IsCryPlayingOrClearCrySongs())
    {
        if (!gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI && gBattleTypeFlags & BATTLE_TYPE_LINK)
                m4aMPlayContinue(&gMPlayInfo_BGM);
            else
                m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 256);
        }
        gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored = TRUE;
        bgmRestored = TRUE;
    }

    // Wait for battler anims
    if (TwoPlayerIntroMons(battler) && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
    {
        if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[BATTLE_PARTNER(battler)]].callback == SpriteCallbackDummy)
        {
            battlerAnimsDone = TRUE;
        }
    }
    else
    {
        if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
            && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
        {
            battlerAnimsDone = TRUE;
        }
    }

    // Clean up
    if (bgmRestored && battlerAnimsDone)
    {
        if (TwoPlayerIntroMons(battler) && !(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            DestroySprite(&gSprites[gBattleControllerData[BATTLE_PARTNER(battler)]]);
        DestroySprite(&gSprites[gBattleControllerData[battler]]);

        gBattleSpritesDataPtr->animationData->introAnimActive = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].bgmRestored = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].healthboxSlideInStarted = FALSE;

        gBattlerControllerFuncs[battler] = Intro_WaitForShinyAnimAndHealthbox;
    }
}

static void SwitchIn_CleanShinyAnimShowSubstitute(u32 battler)
{
    if (gSprites[gHealthboxSpriteIds[battler]].callback == SpriteCallbackDummy
     && gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim
     && gSprites[gBattlerSpriteIds[battler]].callback == SpriteCallbackDummy)
    {
        CopyBattleSpriteInvisibility(battler);

        // Reset shiny anim (even if it didn't occur)
        gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim = FALSE;
        gBattleSpritesDataPtr->healthBoxesData[battler].finishedShinyMonAnim = FALSE;
        FreeSpriteTilesByTag(ANIM_TAG_GOLD_STARS);
        FreeSpritePaletteByTag(ANIM_TAG_GOLD_STARS);

        // Check if Substitute should be shown
        if (gBattleSpritesDataPtr->battlerData[battler].behindSubstitute)
            InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_MON_TO_SUBSTITUTE);

        gBattlerControllerFuncs[battler] = SwitchIn_HandleSoundAndEnd;
    }
}

static void SwitchIn_HandleSoundAndEnd(u32 battler)
{
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive
        && !IsCryPlayingOrClearCrySongs())
    {
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 256);
        HandleLowHpMusicChange(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
        PlayerBufferExecCompleted(battler);
    }
}

static void SwitchIn_TryShinyAnimShowHealthbox(u32 battler)
{
    // Start shiny animation if applicable
    if (!gBattleSpritesDataPtr->healthBoxesData[battler].triedShinyMonAnim
        && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
        TryShinyAnimation(battler, &gPlayerParty[gBattlerPartyIndexes[battler]]);

    // Wait for ball anim, then show healthbox
    if (gSprites[gBattleControllerData[battler]].callback == SpriteCallbackDummy
     && !gBattleSpritesDataPtr->healthBoxesData[battler].ballAnimActive)
    {
        DestroySprite(&gSprites[gBattleControllerData[battler]]);
        UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[gBattlerPartyIndexes[battler]], HEALTHBOX_ALL);
        StartHealthboxSlideIn(battler);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        gBattlerControllerFuncs[battler] = SwitchIn_CleanShinyAnimShowSubstitute;
    }
}

void Task_PlayerController_RestoreBgmAfterCry(u8 taskId)
{
    if (!IsCryPlayingOrClearCrySongs())
    {
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 256);
        DestroyTask(taskId);
    }
}

#define tExpTask_monId          data[0]
#define tExpTask_battler        data[2]
#define tExpTask_gainedExp_1    data[3]
#define tExpTask_gainedExp_2    data[4] // Stored as two half-words containing a word.
#define tExpTask_frames         data[10]

static s32 GetTaskExpValue(u8 taskId)
{
    return (u16)(gTasks[taskId].tExpTask_gainedExp_1) | (gTasks[taskId].tExpTask_gainedExp_2 << 16);
}

static void Task_GiveExpToMon(u8 taskId)
{
    u32 monId = (u8)(gTasks[taskId].tExpTask_monId);
    u8 battler = gTasks[taskId].tExpTask_battler;
    s32 gainedExp = GetTaskExpValue(taskId);

    if (WhichBattleCoords(battler) == MODO_DOBLES || monId != gBattlerPartyIndexes[battler]) // Give exp without moving the expbar.
    {
        struct Pokemon *mon = &gPlayerParty[monId];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        u32 currExp = GetMonData(mon, MON_DATA_EXP);
        u32 nextLvlExp = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1];

        if (currExp + gainedExp >= nextLvlExp)
        {
            SetMonData(mon, MON_DATA_EXP, &nextLvlExp);
            gBattleStruct->dynamax.levelUpHP = GetMonData(mon, MON_DATA_HP) \
                + UQ_4_12_TO_INT((gBattleScripting.levelUpHP * UQ_4_12(1.5)) + UQ_4_12_ROUND);
            CalculateMonStats(mon);

            gainedExp -= nextLvlExp - currExp;
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, RET_VALUE_LEVELED_UP, gainedExp);

            if (IsDoubleBattle() == TRUE
             && (monId == gBattlerPartyIndexes[battler] || monId == gBattlerPartyIndexes[BATTLE_PARTNER(battler)]))
                gTasks[taskId].func = Task_LaunchLvlUpAnim;
            else
                gTasks[taskId].func = Task_SetControllerToWaitForString;
        }
        else
        {
            currExp += gainedExp;
            SetMonData(mon, MON_DATA_EXP, &currExp);
            gBattlerControllerFuncs[battler] = Controller_WaitForString;
            DestroyTask(taskId);
        }
    }
    else
    {
        gTasks[taskId].func = Task_PrepareToGiveExpWithExpBar;
    }
}

static void Task_PrepareToGiveExpWithExpBar(u8 taskId)
{
    u8 monIndex = gTasks[taskId].tExpTask_monId;
    s32 gainedExp = GetTaskExpValue(taskId);
    u8 battler = gTasks[taskId].tExpTask_battler;
    struct Pokemon *mon = &gPlayerParty[monIndex];
    u8 level = GetMonData(mon, MON_DATA_LEVEL);
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 exp = GetMonData(mon, MON_DATA_EXP);
    u32 currLvlExp = gExperienceTables[gSpeciesInfo[species].growthRate][level];
    u32 expToNextLvl;

    exp -= currLvlExp;
    expToNextLvl = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1] - currLvlExp;
    SetBattleBarStruct(battler, gHealthboxSpriteIds[battler], expToNextLvl, exp, -gainedExp);
    PlaySE(SE_EXP);
    gTasks[taskId].func = Task_GiveExpWithExpBar;
}

static void Task_GiveExpWithExpBar(u8 taskId)
{
    u8 level;
    u16 species;
    s32 currExp, expOnNextLvl, newExpPoints;

    if (gTasks[taskId].tExpTask_frames < 13)
    {
        gTasks[taskId].tExpTask_frames++;
    }
    else
    {
        u8 monId = gTasks[taskId].tExpTask_monId;
        s32 gainedExp = GetTaskExpValue(taskId);
        u8 battler = gTasks[taskId].tExpTask_battler;

        newExpPoints = MoveBattleBar(battler, gHealthboxSpriteIds[battler], EXP_BAR);
        SetHealthboxSpriteVisible(gHealthboxSpriteIds[battler]);
        if (newExpPoints == -1) // The bar has been filled with given exp points.
        {
            m4aSongNumStop(SE_EXP);
            level = GetMonData(&gPlayerParty[monId], MON_DATA_LEVEL);
            currExp = GetMonData(&gPlayerParty[monId], MON_DATA_EXP);
            species = GetMonData(&gPlayerParty[monId], MON_DATA_SPECIES);
            expOnNextLvl = gExperienceTables[gSpeciesInfo[species].growthRate][level + 1];

            if (currExp + gainedExp >= expOnNextLvl)
            {
                SetMonData(&gPlayerParty[monId], MON_DATA_EXP, &expOnNextLvl);
                gBattleStruct->dynamax.levelUpHP = GetMonData(&gPlayerParty[monId], MON_DATA_HP) \
                    + UQ_4_12_TO_INT((gBattleScripting.levelUpHP * UQ_4_12(1.5)) + UQ_4_12_ROUND);
                CalculateMonStats(&gPlayerParty[monId]);

                // Reapply Dynamax HP multiplier after stats are recalculated.
                if (GetActiveGimmick(battler) == GIMMICK_DYNAMAX && monId == gBattlerPartyIndexes[battler])
                {
                    ApplyDynamaxHPMultiplier(battler, &gPlayerParty[monId]);
                    gBattleMons[battler].hp = gBattleStruct->dynamax.levelUpHP;
                    SetMonData(&gPlayerParty[monId], MON_DATA_HP, &gBattleMons[battler].hp);
                }

                gainedExp -= expOnNextLvl - currExp;
                BtlController_EmitTwoReturnValues(battler, BUFFER_B, RET_VALUE_LEVELED_UP, gainedExp);
                gTasks[taskId].func = Task_LaunchLvlUpAnim;
            }
            else
            {
                currExp += gainedExp;
                SetMonData(&gPlayerParty[monId], MON_DATA_EXP, &currExp);
                gBattlerControllerFuncs[battler] = Controller_WaitForString;
                DestroyTask(taskId);
            }
        }
    }
}

static void Task_LaunchLvlUpAnim(u8 taskId)
{
    u8 battler = gTasks[taskId].tExpTask_battler;
    u8 monIndex = gTasks[taskId].tExpTask_monId;

    if (IsDoubleBattle() == TRUE && monIndex == gBattlerPartyIndexes[BATTLE_PARTNER(battler)])
        battler ^= BIT_FLANK;

    InitAndLaunchSpecialAnimation(battler, battler, battler, B_ANIM_LVL_UP);
    gTasks[taskId].func = Task_UpdateLvlInHealthbox;
}

static void Task_UpdateLvlInHealthbox(u8 taskId)
{
    u8 battler = gTasks[taskId].tExpTask_battler;

    if (!gBattleSpritesDataPtr->healthBoxesData[battler].specialAnimActive)
    {
        u8 monIndex = gTasks[taskId].tExpTask_monId;

        if (IsDoubleBattle() == TRUE && monIndex == gBattlerPartyIndexes[BATTLE_PARTNER(battler)])
            UpdateHealthboxAttribute(gHealthboxSpriteIds[BATTLE_PARTNER(battler)], &gPlayerParty[monIndex], HEALTHBOX_ALL);
        else
            UpdateHealthboxAttribute(gHealthboxSpriteIds[battler], &gPlayerParty[monIndex], HEALTHBOX_ALL);

        gTasks[taskId].func = Task_SetControllerToWaitForString;
    }
}

static void Task_SetControllerToWaitForString(u8 taskId)
{
    u8 battler = gTasks[taskId].tExpTask_battler;
    gBattlerControllerFuncs[battler] = Controller_WaitForString;
    DestroyTask(taskId);
}

static void OpenPartyMenuToChooseMon(u32 battler)
{
    if (!gPaletteFade.active)
    {
        u8 caseId;

        gBattlerControllerFuncs[battler] = WaitForMonSelection;
        caseId = gTasks[gBattleControllerData[battler]].data[0];
        DestroyTask(gBattleControllerData[battler]);
        FreeAllWindowBuffers();
        OpenPartyMenuInBattle(caseId);
    }
}

static void WaitForMonSelection(u32 battler)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        if (gPartyMenuUseExitCallback == TRUE)
            BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, gSelectedMonPartyId, gBattlePartyCurrentOrder);
        else
            BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, PARTY_SIZE, NULL);

        if ((gBattleResources->bufferA[battler][1] & 0xF) == 1)
            PrintLinkStandbyMsg();

        PlayerBufferExecCompleted(battler);
    }
}

static void OpenBagAndChooseItem(u32 battler)
{
    if (!gPaletteFade.active)
    {
        gBattlerControllerFuncs[battler] = CompleteWhenChoseItem;
        ReshowBattleScreenDummy();
        FreeAllWindowBuffers();
        CB2_BagMenuFromBattle();
    }
}

static void CompleteWhenChoseItem(u32 battler)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        BtlController_EmitOneReturnValue(battler, BUFFER_B, gSpecialVar_ItemId);
        PlayerBufferExecCompleted(battler);
    }
}

static void PlayerHandleYesNoInput(u32 battler)
{
    if (JOY_NEW(DPAD_UP) && gMultiUsePlayerCursor != 0)
    {
        PlaySE(SE_SELECT);
        BattleDestroyYesNoCursorAt(gMultiUsePlayerCursor);
        gMultiUsePlayerCursor = 0;
        BattleCreateYesNoCursorAt(0);
    }
    if (JOY_NEW(DPAD_DOWN) && gMultiUsePlayerCursor == 0)
    {
        PlaySE(SE_SELECT);
        BattleDestroyYesNoCursorAt(gMultiUsePlayerCursor);
        gMultiUsePlayerCursor = 1;
        BattleCreateYesNoCursorAt(1);
    }
    if (JOY_NEW(A_BUTTON))
    {
        HandleBattleWindow(YESNOBOX_X_Y, WINDOW_CLEAR);
        PlaySE(SE_SELECT);

        if (gMultiUsePlayerCursor != 0)
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 0xE, 0);
        else
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, 0xD, 0);

        PlayerBufferExecCompleted(battler);
    }
    if (JOY_NEW(B_BUTTON))
    {
        HandleBattleWindow(YESNOBOX_X_Y, WINDOW_CLEAR);
        PlaySE(SE_SELECT);
        PlayerBufferExecCompleted(battler);
    }
}

static void MoveSelectionDisplayMoveNames(u32 battler)
{
    s32 i;
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    gNumberOfMovesToChoose = 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        MoveSelectionDestroyCursor();
        StringCopy(gDisplayedStringBattle, GetMoveName(moveInfo->moves[i]));
        // Prints on windows B_WIN_MOVE_NAME_1, B_WIN_MOVE_NAME_2, B_WIN_MOVE_NAME_3, B_WIN_MOVE_NAME_4
        BattlePutTextOnWindow(gDisplayedStringBattle, i + B_WIN_MOVE_NAME_1);
        if (moveInfo->moves[i] != MOVE_NONE)
            gNumberOfMovesToChoose++;
    }
}

static void MoveSelectionDisplayPpNumber(u32 battler)
{
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);

    if (gBattleResources->bufferA[battler][2] == TRUE) // check if we didn't want to display pp number
        return;

    for (u8 i = 0; i < 4; i++)
    {
        if (moveInfo->moves[i] != MOVE_NONE)
        {
            ConvertIntToDecimalStringN(gDisplayedStringBattle, moveInfo->currentPp[i], STR_CONV_MODE_RIGHT_ALIGN, 2);
            BattlePutTextOnWindow(gDisplayedStringBattle, B_WIN_PP_1 + i); // B_WIN_PP_1, B_WIN_PP_2, etc.
        }
        else
        {
            BattlePutTextOnWindow(gText_OneDash, B_WIN_PP_1 + i); // B_WIN_PP_1, B_WIN_PP_2, etc.
        }
    }
}

static const struct OamData sOamData_IconTypes =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_IconTypeNone[] = {
    ANIMCMD_FRAME(TIPO_NINGUNO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeNormal[] = {
    ANIMCMD_FRAME(TIPO_NORMAL * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeFighting[] = {
    ANIMCMD_FRAME(TIPO_LUCHA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeFlying[] = {
    ANIMCMD_FRAME(TIPO_VOLADOR * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypePoison[] = {
    ANIMCMD_FRAME(TIPO_VENENO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeGround[] = {
    ANIMCMD_FRAME(TIPO_TIERRA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeRock[] = {
    ANIMCMD_FRAME(TIPO_ROCA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeBug[] = {
    ANIMCMD_FRAME(TIPO_BICHO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeGhost[] = {
    ANIMCMD_FRAME(TIPO_FANTASMA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeSteel[] = {
    ANIMCMD_FRAME(TIPO_ACERO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeMystery[] = {
    ANIMCMD_FRAME(TIPO_MISTERIO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeFire[] = {
    ANIMCMD_FRAME(TIPO_FUEGO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeWater[] = {
    ANIMCMD_FRAME(TIPO_AGUA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeGrass[] = {
    ANIMCMD_FRAME(TIPO_PLANTA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeElectric[] = {
    ANIMCMD_FRAME(TIPO_ELECTRICO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypePsychic[] = {
    ANIMCMD_FRAME(TIPO_PSIQUICO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeIce[] = {
    ANIMCMD_FRAME(TIPO_HIELO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeDragon[] = {
    ANIMCMD_FRAME(TIPO_DRAGON * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeDark[] = {
    ANIMCMD_FRAME(TIPO_SINIESTRO * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_IconTypeFairy[] = {
    ANIMCMD_FRAME(TIPO_HADA * 4, 0, FALSE, FALSE),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_IconTypes[NUMERO_DE_TIPOS] = {
    sSpriteAnim_IconTypeNone,
    sSpriteAnim_IconTypeNormal,
    sSpriteAnim_IconTypeFighting,
    sSpriteAnim_IconTypeFlying,
    sSpriteAnim_IconTypePoison,
    sSpriteAnim_IconTypeGround,
    sSpriteAnim_IconTypeRock,
    sSpriteAnim_IconTypeBug,
    sSpriteAnim_IconTypeGhost,
    sSpriteAnim_IconTypeSteel,
    sSpriteAnim_IconTypeMystery,
    sSpriteAnim_IconTypeFire,
    sSpriteAnim_IconTypeWater,
    sSpriteAnim_IconTypeGrass,
    sSpriteAnim_IconTypeElectric,
    sSpriteAnim_IconTypePsychic,
    sSpriteAnim_IconTypeIce,
    sSpriteAnim_IconTypeDragon,
    sSpriteAnim_IconTypeDark,
    sSpriteAnim_IconTypeFairy,
};

const struct CompressedSpriteSheet sSpriteSheet_IconTypes =
{
    .data = gIconTypes_Gfx,
    .size = (NUMERO_DE_TIPOS) * 128,
    .tag = TAG_ICON_TYPES
};
const struct SpriteTemplate sSpriteTemplate_IconTypes =
{
    .tileTag = TAG_ICON_TYPES,
    .paletteTag = TAG_ICON_TYPES,
    .oam = &sOamData_IconTypes,
    .anims = sSpriteAnimTable_IconTypes,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};
static const u8 sMoveTypeToOamPaletteNum[NUMERO_DE_TIPOS] =
{
    [TIPO_NINGUNO] = 14,
    [TIPO_NORMAL] = 14,
    [TIPO_LUCHA] = 13,
    [TIPO_VOLADOR] = 14,
    [TIPO_VENENO] = 15,
    [TIPO_TIERRA] = 14,
    [TIPO_ROCA] = 15,
    [TIPO_BICHO] = 13,
    [TIPO_FANTASMA] = 14,
    [TIPO_ACERO] = 15,
    [TIPO_MISTERIO] = 15,
    [TIPO_FUEGO] = 14,
    [TIPO_AGUA] = 14,
    [TIPO_PLANTA] = 13,
    [TIPO_ELECTRICO] = 13,
    [TIPO_PSIQUICO] = 15,
    [TIPO_HIELO] = 14,
    [TIPO_DRAGON] = 13,
    [TIPO_SINIESTRO] = 13,
    [TIPO_HADA] = 13,
};

void LoadPalettesTypes(u32 battler)
{
    u32 pal1, pal2, pal3, pal4;
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);

    pal1 = gMovesInfo[moveInfo->moves[0]].type;
    pal2 = gMovesInfo[moveInfo->moves[1]].type;
    pal3 = gMovesInfo[moveInfo->moves[2]].type;
    pal4 = gMovesInfo[moveInfo->moves[3]].type;

    switch (pal1)
    {
    case TIPO_BICHO:
        LoadCompressedPalette(gMoveTypePalBug, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_SINIESTRO:
        LoadCompressedPalette(gMoveTypePalDark, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_DRAGON:
        LoadCompressedPalette(gMoveTypePalDragon, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_ELECTRICO:
        LoadCompressedPalette(gMoveTypePalElectric, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_HADA:
        LoadCompressedPalette(gMoveTypePalFairy, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_LUCHA:
        LoadCompressedPalette(gMoveTypePalFight, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_FUEGO:
        LoadCompressedPalette(gMoveTypePalFire, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_VOLADOR:
        LoadCompressedPalette(gMoveTypePalFlying, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_FANTASMA:
        LoadCompressedPalette(gMoveTypePalGhost, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_PLANTA:
        LoadCompressedPalette(gMoveTypePalGrass, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_TIERRA:
        LoadCompressedPalette(gMoveTypePalGround, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_HIELO:
        LoadCompressedPalette(gMoveTypePalIce, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_MISTERIO:
        LoadCompressedPalette(gMoveTypePalMystery, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_NORMAL:
        LoadCompressedPalette(gMoveTypePalNormal, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_VENENO:
        LoadCompressedPalette(gMoveTypePalPoison, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_PSIQUICO:
        LoadCompressedPalette(gMoveTypePalPsychic, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_ROCA:
        LoadCompressedPalette(gMoveTypePalRock, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_ACERO:
        LoadCompressedPalette(gMoveTypePalSteel, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    case TIPO_AGUA:
        LoadCompressedPalette(gMoveTypePalWater, BG_PLTT_ID(12), PLTT_SIZE_4BPP);
        break;
    }
    switch (pal2)
    {
    case TIPO_BICHO:
        LoadCompressedPalette(gMoveTypePalBug, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_SINIESTRO:
        LoadCompressedPalette(gMoveTypePalDark, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_DRAGON:
        LoadCompressedPalette(gMoveTypePalDragon, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_ELECTRICO:
        LoadCompressedPalette(gMoveTypePalElectric, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_HADA:
        LoadCompressedPalette(gMoveTypePalFairy, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_LUCHA:
        LoadCompressedPalette(gMoveTypePalFight, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_FUEGO:
        LoadCompressedPalette(gMoveTypePalFire, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_VOLADOR:
        LoadCompressedPalette(gMoveTypePalFlying, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_FANTASMA:
        LoadCompressedPalette(gMoveTypePalGhost, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_PLANTA:
        LoadCompressedPalette(gMoveTypePalGrass, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_TIERRA:
        LoadCompressedPalette(gMoveTypePalGround, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_HIELO:
        LoadCompressedPalette(gMoveTypePalIce, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_MISTERIO:
        LoadCompressedPalette(gMoveTypePalMystery, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_NORMAL:
        LoadCompressedPalette(gMoveTypePalNormal, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_VENENO:
        LoadCompressedPalette(gMoveTypePalPoison, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_PSIQUICO:
        LoadCompressedPalette(gMoveTypePalPsychic, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_ROCA:
        LoadCompressedPalette(gMoveTypePalRock, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_ACERO:
        LoadCompressedPalette(gMoveTypePalSteel, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    case TIPO_AGUA:
        LoadCompressedPalette(gMoveTypePalWater, BG_PLTT_ID(13), PLTT_SIZE_4BPP);
        break;
    }
    switch (pal3)
    {
    case TIPO_BICHO:
        LoadCompressedPalette(gMoveTypePalBug, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_SINIESTRO:
        LoadCompressedPalette(gMoveTypePalDark, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_DRAGON:
        LoadCompressedPalette(gMoveTypePalDragon, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_ELECTRICO:
        LoadCompressedPalette(gMoveTypePalElectric, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_HADA:
        LoadCompressedPalette(gMoveTypePalFairy, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_LUCHA:
        LoadCompressedPalette(gMoveTypePalFight, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_FUEGO:
        LoadCompressedPalette(gMoveTypePalFire, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_VOLADOR:
        LoadCompressedPalette(gMoveTypePalFlying, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_FANTASMA:
        LoadCompressedPalette(gMoveTypePalGhost, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_PLANTA:
        LoadCompressedPalette(gMoveTypePalGrass, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_TIERRA:
        LoadCompressedPalette(gMoveTypePalGround, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_HIELO:
        LoadCompressedPalette(gMoveTypePalIce, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_MISTERIO:
        LoadCompressedPalette(gMoveTypePalMystery, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_NORMAL:
        LoadCompressedPalette(gMoveTypePalNormal, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_VENENO:
        LoadCompressedPalette(gMoveTypePalPoison, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_PSIQUICO:
        LoadCompressedPalette(gMoveTypePalPsychic, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_ROCA:
        LoadCompressedPalette(gMoveTypePalRock, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_ACERO:
        LoadCompressedPalette(gMoveTypePalSteel, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    case TIPO_AGUA:
        LoadCompressedPalette(gMoveTypePalWater, BG_PLTT_ID(14), PLTT_SIZE_4BPP);
        break;
    }
    switch (pal4)
    {
    case TIPO_BICHO:
        LoadCompressedPalette(gMoveTypePalBug, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_SINIESTRO:
        LoadCompressedPalette(gMoveTypePalDark, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_DRAGON:
        LoadCompressedPalette(gMoveTypePalDragon, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_ELECTRICO:
        LoadCompressedPalette(gMoveTypePalElectric, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_HADA:
        LoadCompressedPalette(gMoveTypePalFairy, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_LUCHA:
        LoadCompressedPalette(gMoveTypePalFight, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_FUEGO:
        LoadCompressedPalette(gMoveTypePalFire, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_VOLADOR:
        LoadCompressedPalette(gMoveTypePalFlying, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_FANTASMA:
        LoadCompressedPalette(gMoveTypePalGhost, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_PLANTA:
        LoadCompressedPalette(gMoveTypePalGrass, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_TIERRA:
        LoadCompressedPalette(gMoveTypePalGround, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_HIELO:
        LoadCompressedPalette(gMoveTypePalIce, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_MISTERIO:
        LoadCompressedPalette(gMoveTypePalMystery, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_NORMAL:
        LoadCompressedPalette(gMoveTypePalNormal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_VENENO:
        LoadCompressedPalette(gMoveTypePalPoison, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_PSIQUICO:
        LoadCompressedPalette(gMoveTypePalPsychic, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_ROCA:
        LoadCompressedPalette(gMoveTypePalRock, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_ACERO:
        LoadCompressedPalette(gMoveTypePalSteel, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    case TIPO_AGUA:
        LoadCompressedPalette(gMoveTypePalWater, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        break;
    }
}

static void MoveSelectionDisplayMoveType(u32 battler)
{
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    struct Sprite *sprite1, *sprite2, *sprite3, *sprite4;

    LoadPalettesTypes(battler);
    LoadCompressedSpriteSheet(&sSpriteSheet_IconTypes);
    LoadCompressedPalette(gIconTypes_Pal, OBJ_PLTT_ID(13), 3 * PLTT_SIZE_4BPP);

    if (sIconTypeId[0] == 0xFF && moveInfo->moves[0] != MOVE_NONE)
    {
        sIconTypeId[0] = CreateSprite(&sSpriteTemplate_IconTypes, 9, 124, 0);
        sprite1 = &gSprites[sIconTypeId[0]];
		StartSpriteAnim(sprite1, gMovesInfo[moveInfo->moves[0]].type);
	    sprite1->oam.paletteNum = sMoveTypeToOamPaletteNum[gMovesInfo[moveInfo->moves[0]].type];
		sprite1->oam.priority = 0;
		sprite1->subpriority = 1;
    }
    if (sIconTypeId[1] == 0xFF && moveInfo->moves[1] != MOVE_NONE)
    {
        sIconTypeId[1] = CreateSprite(&sSpriteTemplate_IconTypes, 129, 124, 0);
        sprite2 = &gSprites[sIconTypeId[1]];
		StartSpriteAnim(sprite2, gMovesInfo[moveInfo->moves[1]].type);
	    sprite2->oam.paletteNum = sMoveTypeToOamPaletteNum[gMovesInfo[moveInfo->moves[1]].type];
		sprite2->oam.priority = 0;
		sprite2->subpriority = 1;
    }
    if (sIconTypeId[2] == 0xFF && moveInfo->moves[2] != MOVE_NONE)
    {
        sIconTypeId[2] = CreateSprite(&sSpriteTemplate_IconTypes, 9, 148, 0);
        sprite3 = &gSprites[sIconTypeId[2]];
		StartSpriteAnim(sprite3, gMovesInfo[moveInfo->moves[2]].type);
	    sprite3->oam.paletteNum = sMoveTypeToOamPaletteNum[gMovesInfo[moveInfo->moves[2]].type];
		sprite3->oam.priority = 0;
		sprite3->subpriority = 1;
    }
    if (sIconTypeId[3] == 0xFF && moveInfo->moves[3] != MOVE_NONE)
    {
        sIconTypeId[3] = CreateSprite(&sSpriteTemplate_IconTypes, 129, 148, 0);
        sprite4 = &gSprites[sIconTypeId[3]];
		StartSpriteAnim(sprite4, gMovesInfo[moveInfo->moves[3]].type);
	    sprite4->oam.paletteNum = sMoveTypeToOamPaletteNum[gMovesInfo[moveInfo->moves[3]].type];
		sprite4->oam.priority = 0;
		sprite4->subpriority = 1;
    }
}

void CB2_SetUpReshowBattleScreenAfterMenu(void)
{
    SetMainCallback2(ReshowBattleScreenAfterMenu);
}

void CB2_SetUpReshowBattleScreenAfterMenu2(void)
{
    SetMainCallback2(ReshowBattleScreenAfterMenu);
}

static void PrintLinkStandbyMsg(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LINK)
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = 0;
        BattlePutTextOnWindow(gText_LinkStandby, B_WIN_MSG);
    }
}

static void PlayerHandleLoadMonSprite(u32 battler)
{
    BattleLoadMonSpriteGfx(&gPlayerParty[gBattlerPartyIndexes[battler]], battler);
    gSprites[gBattlerSpriteIds[battler]].oam.paletteNum = battler;
    gBattlerControllerFuncs[battler] = CompleteOnBattlerSpritePosX_0;
}

static void PlayerHandleSwitchInAnim(u32 battler)
{
    gActionSelectionCursor[battler] = 0;
    gMoveSelectionCursor[battler] = 0;
    BtlController_HandleSwitchInAnim(battler, TRUE, SwitchIn_TryShinyAnimShowHealthbox);
}

u32 LinkPlayerGetTrainerPicId(u32 multiplayerId)
{
    u32 trainerPicId;

    u8 gender = gLinkPlayers[multiplayerId].gender;
    u8 version = gLinkPlayers[multiplayerId].version & 0xFF;

    if (version == VERSION_FIRE_RED || version == VERSION_LEAF_GREEN)
        trainerPicId = gender + TRAINER_BACK_PIC_RED;
    else if (version == VERSION_RUBY || version == VERSION_SAPPHIRE)
        trainerPicId = gender + TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN;
    else
        trainerPicId = gender + TRAINER_BACK_PIC_BRENDAN;

    return trainerPicId;
}

static u32 PlayerGetTrainerBackPicId(void)
{
    u32 trainerPicId = gSaveBlockPtr->playerGender + TRAINER_BACK_PIC_BRENDAN;

    return trainerPicId;
}

// In emerald it's possible to have a tag battle in the battle frontier facilities with AI
// which use the front sprite for both the player and the partner as opposed to any other battles (including the one with Steven)
// that use an animated back pic.
static void PlayerHandleDrawTrainerPic(u32 battler)
{
    bool32 isFrontPic;
    s16 xPos, yPos;
    u32 trainerPicId;

    trainerPicId = PlayerGetTrainerBackPicId();
    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
    {
        if ((GetBattlerPosition(battler) & BIT_FLANK) != B_FLANK_LEFT) // Second mon, on the right.
            xPos = 90;
        else // First mon, on the left.
            xPos = 32;

        yPos = (8 - gTrainerBacksprites[trainerPicId].coordinates.size) * 4 + 80;

    }
    else
    {
        xPos = 80;
        yPos = (8 - gTrainerBacksprites[trainerPicId].coordinates.size) * 4 + 80;
    }

    isFrontPic = FALSE;

    BtlController_HandleDrawTrainerPic(battler, trainerPicId, isFrontPic, xPos, yPos, -1);
}

static void PlayerHandleTrainerSlide(u32 battler)
{
    u32 trainerPicId = PlayerGetTrainerBackPicId();
    BtlController_HandleTrainerSlide(battler, trainerPicId);
}

static void PlayerHandleTrainerSlideBack(u32 battler)
{
    BtlController_HandleTrainerSlideBack(battler, 50, TRUE);
}

static void PlayerHandlePaletteFade(u32 battler)
{
    BeginNormalPaletteFade(PALETTES_ALL, 2, 0, 16, RGB_BLACK);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleSuccessBallThrowAnim(u32 battler)
{
    BtlController_HandleSuccessBallThrowAnim(battler, gBattlerTarget, B_ANIM_BALL_THROW);
}

void PlayerHandleBallThrowAnim(u32 battler)
{
    BtlController_HandleBallThrowAnim(battler, gBattlerTarget, B_ANIM_BALL_THROW);
}

static void PlayerHandlePause(u32 battler)
{
    u8 timer = gBattleResources->bufferA[battler][1];

    while (timer != 0)
        timer--;

    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleMoveAnimation(u32 battler)
{
    BtlController_HandleMoveAnimation(battler);
}

static void PlayerHandlePrintString(u32 battler)
{
    BtlController_HandlePrintString(battler, TRUE);
}

static void PlayerHandlePrintSelectionString(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
        PlayerHandlePrintString(battler);
    else
        PlayerBufferExecCompleted(battler);
}

static void HandleChooseActionAfterDma3(u32 battler)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = DISPLAY_HEIGHT;
        gBattlerControllerFuncs[battler] = HandleInputChooseAction;
    }
}

#define sMonIconStill data[3]

static void SpriteCb_MonIcon(struct Sprite *sprite)
{
    if (!sprite->sMonIconStill)
        UpdateMonIconFrame(sprite);
}

#undef sMonIconStill

static void PlayerHandleChooseAction(u32 battler)
{
    gBattlerControllerFuncs[battler] = HandleChooseActionAfterDma3;

    TryRestoreLastUsedBall();
    PREPARE_MON_NICK_BUFFER(gBattleTextBuff1, battler, gBattlerPartyIndexes[battler]);

    //LoadMonIconPalettes();
    u16 species = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_SPECIES);
    u32 personality = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_PERSONALITY);
    monIconData = CreateMonIcon(species, SpriteCb_MonIcon, 20, 132, 1, personality);
    u8 index = IndexOfSpritePaletteTag(POKE_ICON_BASE_PAL_TAG);
    SetMonIconPalette(&gPlayerParty[gBattlerPartyIndexes[battler]], &gSprites[monIconData], index);
    gSprites[monIconData].oam.priority = 0;
    StartSpriteAnim(&gSprites[monIconData], 0);
}

static void PlayerHandleYesNoBox(u32 battler)
{
    if (GetBattlerSide(battler) == B_SIDE_PLAYER)
    {
        HandleBattleWindow(YESNOBOX_X_Y, 0);
        BattlePutTextOnWindow(gText_BattleYesNoChoice, B_WIN_YESNO);
        gMultiUsePlayerCursor = 1;
        BattleCreateYesNoCursorAt(1);
        gBattlerControllerFuncs[battler] = PlayerHandleYesNoInput;
    }
    else
    {
        PlayerBufferExecCompleted(battler);
    }
}

void HandleChooseMoveAfterDma3(u32 battler)
{
    if (!IsDma3ManagerBusyWithBgCopy())
    {
        gBattle_BG0_X = 0;
        gBattle_BG0_Y = DISPLAY_HEIGHT * 2;
        gBattlerControllerFuncs[battler] = HandleInputChooseMove;
    }
}

void PlayerHandleChooseMove(u32 battler)
{
    InitMoveSelectionsVarsAndStrings(battler);
    gBattleStruct->gimmick.playerSelect = FALSE;
    gBattlerControllerFuncs[battler] = HandleChooseMoveAfterDma3;
}

void InitMoveSelectionsVarsAndStrings(u32 battler)
{
    DestroySpriteAndFreeResources(&gSprites[monIconData]);
    MoveSelectionDisplayMoveNames(battler);
    gMultiUsePlayerCursor = 0xFF;
    MoveSelectionCreateCursorAt(gMoveSelectionCursor[battler]);
    MoveSelectionDisplayPpNumber(battler);
    MoveSelectionDisplayMoveType(battler);
}

static void PlayerHandleChooseItem(u32 battler)
{
    s32 i;

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[battler] = OpenBagAndChooseItem;
    gBattlerInMenuId = battler;

    for (i = 0; i < ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
        gBattlePartyCurrentOrder[i] = gBattleResources->bufferA[battler][1 + i];
}

static void PlayerHandleChoosePokemon(u32 battler)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBattlePartyCurrentOrder); i++)
        gBattlePartyCurrentOrder[i] = gBattleResources->bufferA[battler][4 + i];

    gBattleControllerData[battler] = CreateTask(TaskDummy, 0xFF);
    gTasks[gBattleControllerData[battler]].data[0] = gBattleResources->bufferA[battler][1] & 0xF;
    *(&gBattleStruct->battlerPreventingSwitchout) = gBattleResources->bufferA[battler][1] >> 4;
    *(&gBattleStruct->prevSelectedPartySlot) = gBattleResources->bufferA[battler][2];
    *(&gBattleStruct->abilityPreventingSwitchout) = (gBattleResources->bufferA[battler][3] & 0xFF) | (gBattleResources->bufferA[battler][7] << 8);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, RGB_BLACK);
    gBattlerControllerFuncs[battler] = OpenPartyMenuToChooseMon;
    gBattlerInMenuId = battler;
}

static void PlayerHandleHealthBarUpdate(u32 battler)
{
    BtlController_HandleHealthBarUpdate(battler, TRUE);
}

void PlayerHandleExpUpdate(u32 battler)
{
    u8 monId = gBattleResources->bufferA[battler][1];
    s32 taskId, expPointsToGive;

    if (GetMonData(&gPlayerParty[monId], MON_DATA_LEVEL) >= MAX_LEVEL)
    {
        PlayerBufferExecCompleted(battler);
    }
    else
    {
        LoadBattleBarGfx();
        expPointsToGive = T1_READ_32(&gBattleResources->bufferA[battler][2]);
        taskId = CreateTask(Task_GiveExpToMon, 10);
        gTasks[taskId].tExpTask_monId = monId;
        gTasks[taskId].tExpTask_gainedExp_1 = expPointsToGive;
        gTasks[taskId].tExpTask_gainedExp_2 = expPointsToGive >> 16;
        gTasks[taskId].tExpTask_battler = battler;
        gBattlerControllerFuncs[battler] = BattleControllerDummy;
    }
}

#undef tExpTask_monId
#undef tExpTask_battler
#undef tExpTask_gainedExp_1
#undef tExpTask_gainedExp_2
#undef tExpTask_frames

static void PlayerHandleStatusXor(u32 battler)
{
    u8 val = GetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_STATUS) ^ gBattleResources->bufferA[battler][1];

    SetMonData(&gPlayerParty[gBattlerPartyIndexes[battler]], MON_DATA_STATUS, &val);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleDMA3Transfer(u32 battler)
{
    u32 dstArg = gBattleResources->bufferA[battler][1]
            | (gBattleResources->bufferA[battler][2] << 8)
            | (gBattleResources->bufferA[battler][3] << 16)
            | (gBattleResources->bufferA[battler][4] << 24);
    u16 sizeArg = gBattleResources->bufferA[battler][5] | (gBattleResources->bufferA[battler][6] << 8);

    const u8 *src = &gBattleResources->bufferA[battler][7];
    u8 *dst = (u8 *)(dstArg);
    u32 size = sizeArg;

    while (1)
    {
        if (size <= 0x1000)
        {
            DmaCopy16(3, src, dst, size);
            break;
        }
        DmaCopy16(3, src, dst, 0x1000);
        src += 0x1000;
        dst += 0x1000;
        size -= 0x1000;
    }
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandlePlayBGM(u32 battler)
{
    PlayBGM(gBattleResources->bufferA[battler][1] | (gBattleResources->bufferA[battler][2] << 8));
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleTwoReturnValues(u32 battler)
{
    BtlController_EmitTwoReturnValues(battler, BUFFER_B, 0, 0);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleChosenMonReturnValue(u32 battler)
{
    BtlController_EmitChosenMonReturnValue(battler, BUFFER_B, 0, NULL);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleOneReturnValue(u32 battler)
{
    BtlController_EmitOneReturnValue(battler, BUFFER_B, 0);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleIntroTrainerBallThrow(u32 battler)
{
    const u32 *trainerPal = gTrainerBacksprites[gSaveBlockPtr->playerGender].palette.data;
    BtlController_HandleIntroTrainerBallThrow(battler, 0xD6F8, trainerPal, 31, Intro_TryShinyAnimShowHealthbox);
}

static void PlayerHandleDrawPartyStatusSummary(u32 battler)
{
    BtlController_HandleDrawPartyStatusSummary(battler, B_SIDE_PLAYER, TRUE);
}

static void PlayerHandleEndBounceEffect(u32 battler)
{
    EndBounceEffect(battler, BOUNCE_HEALTHBOX);
    EndBounceEffect(battler, BOUNCE_MON);
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleBattleAnimation(u32 battler)
{
    BtlController_HandleBattleAnimation(battler, TRUE);
}

static void PlayerHandleLinkStandbyMsg(u32 battler)
{
    switch (gBattleResources->bufferA[battler][1])
    {
    case LINK_STANDBY_MSG_STOP_BOUNCE:
        PrintLinkStandbyMsg();
        // fall through
    case LINK_STANDBY_STOP_BOUNCE_ONLY:
        EndBounceEffect(battler, BOUNCE_HEALTHBOX);
        EndBounceEffect(battler, BOUNCE_MON);
        break;
    case LINK_STANDBY_MSG_ONLY:
        PrintLinkStandbyMsg();
        break;
    }
    PlayerBufferExecCompleted(battler);
}

static void PlayerHandleResetActionMoveSelection(u32 battler)
{
    switch (gBattleResources->bufferA[battler][1])
    {
    case RESET_ACTION_MOVE_SELECTION:
        gActionSelectionCursor[battler] = 0;
        gMoveSelectionCursor[battler] = 0;
        break;
    case RESET_ACTION_SELECTION:
        gActionSelectionCursor[battler] = 0;
        break;
    case RESET_MOVE_SELECTION:
        gMoveSelectionCursor[battler] = 0;
        break;
    }
    PlayerBufferExecCompleted(battler);
}

static void Controller_WaitForDebug(u32 battler)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
    {
        PlayerBufferExecCompleted(battler);
    }
}

static void PlayerHandleBattleDebug(u32 battler)
{
    BeginNormalPaletteFade(-1, 0, 0, 0x10, 0);
    SetMainCallback2(CB2_BattleDebugMenu);
    gBattlerControllerFuncs[battler] = Controller_WaitForDebug;
}
