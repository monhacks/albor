@ Verdanturf Tent

	@ Initialize the Verdanturf Battle Tent challenge
	.macro verdanturftent_init
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_INIT
	special CallVerdanturfTentFunction
	.endm

	@ Get the current prize item id
	.macro verdanturftent_getprize
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_GET_PRIZE
	special CallVerdanturfTentFunction
	.endm

	@ Unused. Set the prize item to be given
	.macro verdanturftent_setprize unusedArg:req, itemId:req
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_SET_PRIZE
	setvar SPECIAL_VAR_5, \unusedArg
	setvar SPECIAL_VAR_6, \itemId
	special CallVerdanturfTentFunction
	.endm

	@ Unused. Set the opponent trainer and gfx. SetNextBattleTentOpponent is used through tower_setopponent instead
	.macro verdanturftent_setopponentgfx
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_SET_OPPONENT_GFX
	special CallVerdanturfTentFunction
	.endm

	@ Buffers the opponents intro speech to STR_VAR_4. Despite being a Verdanturf Tent function, it serves the same purpose for all 3 tents.
	.macro battletent_getopponentintro
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_GET_OPPONENT_INTRO
	special CallVerdanturfTentFunction
	.endm

	@ Save the game and set the challenge status
	.macro verdanturftent_save challengeStatus:req
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallVerdanturfTentFunction
	.endm

	@ Set the prize item as randomly selected from a list. Randomness unnecessary, as the list is only 1 item
	.macro verdanturftent_setrandomprize
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_SET_RANDOM_PRIZE
	special CallVerdanturfTentFunction
	.endm

	@ Give the current prize item. FALSE if no room for prize
	.macro verdanturftent_giveprize
	setvar SPECIAL_VAR_4, VERDANTURF_TENT_FUNC_GIVE_PRIZE
	special CallVerdanturfTentFunction
	.endm


@ Fallarbor Tent

	@ Initialize the Fallarbor Battle Tent challenge
	.macro fallarbortent_init
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_INIT
	special CallFallarborTentFunction
	.endm

	@ Get the current prize item id
	.macro fallarbortent_getprize
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_GET_PRIZE
	special CallFallarborTentFunction
	.endm

	@ Unused. Set the prize item to be given
	.macro fallarbortent_setprize unusedArg:req, itemId:req
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_SET_PRIZE
	setvar SPECIAL_VAR_5, \unusedArg
	setvar SPECIAL_VAR_6, \itemId
	special CallFallarborTentFunction
	.endm

	@ Save the game and set the challenge status
	.macro fallarbortent_save challengeStatus:req
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallFallarborTentFunction
	.endm

	@ Set the prize item as randomly selected from a list. Randomness unnecessary, as the list is only 1 item
	.macro fallarbortent_setrandomprize
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_SET_RANDOM_PRIZE
	special CallFallarborTentFunction
	.endm

	@ Give the current prize item. FALSE if no room for prize
	.macro fallarbortent_giveprize
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_GIVE_PRIZE
	special CallFallarborTentFunction
	.endm

	@ Buffer the opponent trainers name to STR_VAR_1
	.macro fallarbortent_getopponentname
	setvar SPECIAL_VAR_4, FALLARBOR_TENT_FUNC_GET_OPPONENT_NAME
	special CallFallarborTentFunction
	.endm


@ Slateport Tent

	@ Initialize the Slateport Battle Tent challenge
	.macro slateporttent_init
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_INIT
	special CallSlateportTentFunction
	.endm

	@ Get the current prize item id
	.macro slateporttent_getprize
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_GET_PRIZE
	special CallSlateportTentFunction
	.endm

	@ Unused. Set the prize item to be given
	.macro slateporttent_setprize unusedArg:req, itemId:req
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_SET_PRIZE
	setvar SPECIAL_VAR_5, \unusedArg
	setvar SPECIAL_VAR_6, \itemId
	special CallSlateportTentFunction
	.endm

	@ Save the game and set the challenge status
	.macro slateporttent_save challengeStatus:req
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_SAVE
	setvar SPECIAL_VAR_5, \challengeStatus
	special CallSlateportTentFunction
	.endm

	@ Set the prize item as randomly selected from a list. Randomness unnecessary, as the list is only 1 item
	.macro slateporttent_setrandomprize
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_SET_RANDOM_PRIZE
	special CallSlateportTentFunction
	.endm

	@ Give the current prize item. FALSE if no room for prize
	.macro slateporttent_giveprize
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_GIVE_PRIZE
	special CallSlateportTentFunction
	.endm

	@ Slateport Tent's version of factory_rentmons
	.macro slateporttent_rentmons
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_SELECT_RENT_MONS
	special CallSlateportTentFunction
	.endm

	@ Slateport Tent's version of factory_swapmons
	.macro slateporttent_swapmons
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_SWAP_RENT_MONS
	special CallSlateportTentFunction
	.endm

	@ Slateport Tent's version of factory_generateopponentmons
	.macro slateporttent_generateopponentmons
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_GENERATE_OPPONENT_MONS
	special CallSlateportTentFunction
	.endm

	@ Slateport Tent's version of factory_generaterentalmons
	.macro slateporttent_generaterentalmons
	setvar SPECIAL_VAR_4, SLATEPORT_TENT_FUNC_GENERATE_RENTAL_MONS
	special CallSlateportTentFunction
	.endm

