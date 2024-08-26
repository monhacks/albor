	@ Initialize the Battle Tower challenge
	.macro tower_init
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_INIT
	special CallBattleTowerFunc
	.endm

	@ Get the value of some TOWER_DATA_*. See GetTowerData for the data types that can be retrieved
	.macro tower_get data:req
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_GET_DATA
	setvar SPECIAL_VAR_5, \data
	special CallBattleTowerFunc
	.endm

	@ Set some TOWER_DATA_* to val. See SetTowerData for the data types that can be set
	.macro tower_set data:req, val=0xFFFF
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SET_DATA
	setvar SPECIAL_VAR_5, \data
	.if \val != 0xFFFF
	setvar SPECIAL_VAR_6, \val
	.endif
	special CallBattleTowerFunc
	.endm

	@ Choose and set the gfx for the next opponent. Also used by Battle Tents
	.macro tower_setopponent
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SET_OPPONENT
	special CallBattleTowerFunc
	.endm

	@ Increments the battle number and returns the new one. Also clears E-Reader trainer if defeated, and saves the current win streak
	.macro tower_setbattlewon
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SET_BATTLE_WON
	special CallBattleTowerFunc
	.endm

	@ Try to award ribbons for completing 56th straight Battle Tower win. SPECIAL_VAR_RESULT is TRUE if ribbons were awarded.
	.macro tower_giveribbons
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_GIVE_RIBBONS
	special CallBattleTowerFunc
	.endm

	@ Save the game and set the challenge status
	.macro tower_save challengeStatus:req
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallBattleTowerFunc
	.endm

	@ Buffer the opponent's easy chat intro speech to STR_VAR_4
	.macro tower_getopponentintro opponent:req
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_GET_OPPONENT_INTRO
	setvar SPECIAL_VAR_5, \opponent
	special CallBattleTowerFunc
	.endm

	@ Load the parties, gfx, and other data (like Apprentice id) for the multi partner candidates
	.macro tower_loadpartners
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_LOAD_PARTNERS
	special CallBattleTowerFunc
	.endm

	@ Print message from potential multi partner. msgId is any PARTNER_MSGID_*
	.macro tower_dopartnermsg msgId:req
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_PARTNER_MSG
	setvar SPECIAL_VAR_5, \msgId
	special CallBattleTowerFunc
	.endm

	@ Receives/loads the opponent data for a link multi challenge. Returns 6 when finished, and finishes immediately if not doing a link multi battle.
	.macro tower_loadlinkopponents
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_LOAD_LINK_OPPONENTS
	special CallBattleTowerFunc
	.endm

	@ Attempts to close link connection. Used when finishing a link multi challenge.
	.macro tower_closelink
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_TRY_CLOSE_LINK
	special CallBattleTowerFunc
	.endm

	@ Set VAR_OBJ_GFX_ID_E to the gfx id of the selected multi partner
	.macro tower_setpartnergfx
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SET_PARTNER_GFX
	special CallBattleTowerFunc
	.endm

	@ Set the data used for the post-challenge Battle Tower interview
	.macro tower_setinterviewdata
	setvar SPECIAL_VAR_4, BATTLE_TOWER_FUNC_SET_INTERVIEW_DATA
	special CallBattleTowerFunc
	.endm

	@Custom multi-battle commands

	.macro choose_mons
	fadescreen 1
	special ChooseHalfPartyForBattle @ choose 3 mons for battle
	waitstate
	.endm

	.macro multi_do type:req, partnerId:req
	special ReducePlayerPartyToSelectedMons
	setvar SPECIAL_VAR_4, FRONTIER_UTIL_FUNC_SET_DATA
	setvar SPECIAL_VAR_5, FRONTIER_DATA_SELECTED_MON_ORDER
	special CallFrontierUtilFunc @ saves the mon order, so the non-selected mons get restored afterwards
	setvar SPECIAL_VAR_4, SPECIAL_BATTLE_MULTI
	setvar SPECIAL_VAR_5, \type | MULTI_BATTLE_CHOOSE_MONS
	setvar SPECIAL_VAR_6, \partnerId
	special DoSpecialTrainerBattle
	waitstate
	setvar SPECIAL_VAR_4, FRONTIER_UTIL_FUNC_SAVE_PARTY
	special CallFrontierUtilFunc
	special LoadPlayerParty
	.endm

	.macro multi_2_vs_2 trainer1Id:req, trainer1LoseText:req, trainer2Id:req, trainer2LoseText:req, partnerId:req
	special SavePlayerParty
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, \trainer1Id, 0, NULL, \trainer1LoseText @ set first trainer mons
	trainerbattle TRAINER_BATTLE_SET_TRAINER_B, \trainer2Id, 0, NULL, \trainer2LoseText @ set second trainer mons
	multi_do MULTI_BATTLE_2_VS_2, \partnerId
	.endm

	.macro multi_2_vs_1 trainer1Id:req, trainer1LoseText:req, partnerId:req
	special SavePlayerParty
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, \trainer1Id, 0, NULL, \trainer1LoseText @ set first trainer mons
	multi_do MULTI_BATTLE_2_VS_1, \partnerId
	.endm

	@ Wild mons need to be assigned to gEnemyParty 0 and 3 slots, other slots need to be cleared out.
	.macro multi_wild partnerId:req
	special SavePlayerParty
	multi_do MULTI_BATTLE_2_VS_WILD, \partnerId
	.endm

	.macro multi_do_fixed type:req, partnerId:req
	setvar SPECIAL_VAR_4, SPECIAL_BATTLE_MULTI
	setvar SPECIAL_VAR_5, \type
	setvar SPECIAL_VAR_6, \partnerId
	special DoSpecialTrainerBattle
	waitstate
	setvar SPECIAL_VAR_4, FRONTIER_UTIL_FUNC_SAVE_PARTY
	special CallFrontierUtilFunc
	special LoadPlayerParty
	.endm

	.macro multi_fixed_2_vs_2 trainer1Id:req, trainer1LoseText:req, trainer2Id:req, trainer2LoseText:req, partnerId:req
	special SavePlayerParty
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, \trainer1Id, 0, NULL, \trainer1LoseText @ set first trainer mons
	trainerbattle TRAINER_BATTLE_SET_TRAINER_B, \trainer2Id, 0, NULL, \trainer2LoseText @ set second trainer mons
	multi_do_fixed MULTI_BATTLE_2_VS_2, \partnerId
	.endm

	.macro multi_fixed_2_vs_1 trainer1Id:req, trainer1LoseText:req, partnerId:req
	special SavePlayerParty
	trainerbattle TRAINER_BATTLE_SET_TRAINER_A, \trainer1Id, 0, NULL, \trainer1LoseText @ set first trainer mons
	multi_do_fixed MULTI_BATTLE_2_VS_1, \partnerId
	.endm

	@ Wild mons need to be assigned to gEnemyParty 0 and 3 slots, other slots need to be cleared out.
	.macro multi_fixed_wild partnerId:req
	special SavePlayerParty
	multi_do_fixed MULTI_BATTLE_2_VS_WILD, \partnerId
	.endm
