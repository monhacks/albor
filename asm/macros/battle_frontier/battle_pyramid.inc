	@ Initialize the Battle Pyramid challenge
	.macro pyramid_init
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_INIT
	special CallBattlePyramidFunction
	.endm

	@ Get the value of some PYRAMID_DATA_*. See GetBattlePyramidData for the data types that can be retrieved
	.macro pyramid_get data:req
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_GET_DATA
	setvar SPECIAL_VAR_5, \data
	special CallBattlePyramidFunction
	.endm

	@ Set some PYRAMID_DATA_* to val. See SetBattlePyramidData for the data types that can be set
	.macro pyramid_set data:req, val:req
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SET_DATA
	setvar SPECIAL_VAR_5, \data
	setvar SPECIAL_VAR_6, \val
	special CallBattlePyramidFunction
	.endm

	@ Save the game and set the challenge status
	.macro pyramid_save challengeStatus:req
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallBattlePyramidFunction
	.endm

	@ Set the prize item to give from one of two lists of possible prizes, depending on streak.
	.macro pyramid_setprize
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SET_PRIZE
	special CallBattlePyramidFunction
	.endm

	@ Unused. Give the set prize item to the player. TRUE if room in Bag for prize, FALSE otherwise
	.macro pyramid_giveprize
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_GIVE_PRIZE
	special CallBattlePyramidFunction
	.endm

	@ Set the random values for the floor (used to determine object positions, e.g.), and clear trainer flags
	.macro pyramid_seedfloor
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SEED_FLOOR
	special CallBattlePyramidFunction
	.endm

	@ Set the item to pick up depending on the random seed and quantity (always 1) to the arguments for STD_FIND_ITEM
	.macro pyramid_setitem
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SET_ITEM
	special CallBattlePyramidFunction
	.endm

	@ Hide the picked-up item (technically it moves the item far offscreen)
	.macro pyramid_hideitem
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_HIDE_ITEM
	special CallBattlePyramidFunction
	.endm

	@ Set the facility trainers to gBattleFrontierTrainers
	.macro pyramid_settrainers
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SET_TRAINERS
	special CallBattlePyramidFunction
	.endm

	@ Show the post-battle hint text
	.macro pyramid_showhint
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SHOW_HINT_TEXT
	special CallBattlePyramidFunction
	.endm

	@ SPECIAL_VAR_RESULT is 1 if player is on a Pyramid floor, 2 if on the Pyramid peak, 0 otherwise
	.macro pyramid_inchallenge
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_IS_IN
	special CallBattlePyramidFunction
	.endm

	@ Update the light around the player. 2 different modes, for setting or incrementing light. See PYRAMID_LIGHT_*
	.macro pyramid_updatelight radius:req, mode:req, sound=0xFFFF
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar SPECIAL_VAR_5, \radius
	setvar SPECIAL_VAR_6, \mode
	.if \sound != 0xFFFF
	setvar SPECIAL_VAR_7, \sound
	.endif
	special CallBattlePyramidFunction
	.endm

	@ Reset the held items to what they were at the start of the challenge
	.macro pyramid_clearhelditems
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_CLEAR_HELD_ITEMS
	special CallBattlePyramidFunction
	.endm

	@ Set the palette depending on current floor number
	.macro pyramid_setfloorpal
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_SET_FLOOR_PALETTE
	special CallBattlePyramidFunction
	.endm

	@ Reset sketched moves and update the party order in the saveblock
	.macro pyramid_resetparty
	setvar SPECIAL_VAR_4, BATTLE_PYRAMID_FUNC_RESTORE_PARTY
	special CallBattlePyramidFunction
	.endm
