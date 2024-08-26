	@ Initialize the Battle Arena challenge
	.macro arena_init
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_INIT
	special CallBattleArenaFunction
	.endm

	@ Unused. Get the value of some ARENA_DATA_*. See GetArenaData for the data types that can be retrieved
	.macro arena_get data:req
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_GET_DATA
	setvar SPECIAL_VAR_5, \data
	special CallBattleArenaFunction
	.endm

	@ Set some ARENA_DATA_* to val. See SetArenaData for the data types that can be set
	.macro arena_set data:req, val:req
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_SET_DATA
	setvar SPECIAL_VAR_5, \data
	.if \val >= VARS_START
	copyvar SPECIAL_VAR_6, \val
	.else
	setvar SPECIAL_VAR_6, \val
	.endif
	special CallBattleArenaFunction
	.endm

	@ Save the game and set the challenge status
	.macro arena_save challengeStatus:req
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallBattleArenaFunction
	.endm

	@ Unused. Set the prize item to give from one of two lists of possible prizes, depending on streak.
	.macro arena_setprize
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_SET_PRIZE
	special CallBattleArenaFunction
	.endm

	@ Unused. Give the set prize item to the player. TRUE if room in Bag for prize, FALSE otherwise
	.macro arena_giveprize
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_GIVE_PRIZE
	special CallBattleArenaFunction
	.endm

	@ Buffer the opponents name to STR_VAR_1
	.macro arena_gettrainername
	setvar SPECIAL_VAR_4, BATTLE_ARENA_FUNC_GET_TRAINER_NAME
	special CallBattleArenaFunction
	.endm
