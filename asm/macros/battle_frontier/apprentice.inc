	@ TRUE if the player has talked to the Apprentice and answered their level mode question
	.macro apprentice_gavelvlmode
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_GAVE_LVLMODE
	special CallApprenticeFunction
	.endm

	@ Set the level mode the Apprentice should battle in
	.macro apprentice_setlvlmode lvlmode:req
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SET_LVLMODE
	setorcopyvar SPECIAL_VAR_5, \lvlmode
	addvar SPECIAL_VAR_5, 1  @ Apprentice lvl mode is +1 from regular lvl mode value
	special CallApprenticeFunction
	.endm

	@ Question was answered, increment the number of questions answered
	.macro apprentice_answeredquestion
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_ANSWERED_QUESTION
	special CallApprenticeFunction
	.endm

	@ Show the response selection box to answer the Apprentice question. Menus are defined as APPRENTICE_ASK_*
	.macro apprentice_menu  which:req
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_MENU
	setvar SPECIAL_VAR_5, \which
	special CallApprenticeFunction
	waitstate
	.endm

	@ Shuffle and set the Apprentice party mons to pick between from their list of possible party species
	.macro apprentice_shufflespecies
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SHUFFLE_SPECIES
	special CallApprenticeFunction
	.endm

	@ Randomize the question data (e.g. moves to pick between) and shuffle the order to ask them in
	.macro apprentice_randomizequestions
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_RANDOMIZE_QUESTIONS
	special CallApprenticeFunction
	.endm

	@ Print the APPRENTICE_MSG_* text for the current Apprentice
	.macro apprentice_msg  waitbuttonpress:req, which:req
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_PRINT_MSG
	setvar SPECIAL_VAR_5, \waitbuttonpress
	setvar SPECIAL_VAR_6, \which
	special CallApprenticeFunction
	waitstate
	.endm

	@ Clear the data for the current Player Apprentice
	.macro apprentice_reset
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_RESET
	special CallApprenticeFunction
	.endm

	@ Always returns TRUE. No side effect. May have been for debug or dummied for some other reason
	.macro apprentice_shouldcheckgone
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_CHECK_GONE
	special CallApprenticeFunction
	.endm

	@ Return the APPRENTICE_QUESTION_* value for the current question to ask
	.macro apprentice_getquestion
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_GET_QUESTION
	special CallApprenticeFunction
	.endm

	@ Get the number of mons that have been chosen for the Apprentice's party so far
	.macro apprentice_getnumpartymons
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_GET_NUM_PARTY_MONS
	special CallApprenticeFunction
	.endm

	@ Set the Apprentice party mon at the given slot. SPECIAL_VAR_5 is used implicitly as which of the 2 mons was selected
	.macro apprentice_setpartymon  slot:req
	copyvar SPECIAL_VAR_6, \slot
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SET_PARTY_MON
	special CallApprenticeFunction
	.endm

	@ Allocate and set up data to track about the question
	.macro apprentice_initquestion  which:req
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_INIT_QUESTION_DATA
	setvar SPECIAL_VAR_5, \which
	special CallApprenticeFunction
	.endm

	@ Free allocated question data
	.macro apprentice_freequestion
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_FREE_QUESTION_DATA
	special CallApprenticeFunction
	.endm

	@ Buffer some APPRENTICE_BUFF_* string to the given stringvar (0 for STR_VAR_1, 1 for STR_VAR_2, 2 for STR_VAR_3)
	.macro apprentice_buff  stringvar:req, tobuff:req
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_BUFFER_STRING
	.if \stringvar == STR_VAR_1
		setvar SPECIAL_VAR_5, 0
	.elseif \stringvar == STR_VAR_2
		setvar SPECIAL_VAR_5, 1
	.elseif \stringvar == STR_VAR_3
		setvar SPECIAL_VAR_5, 2
	.else
		setvar SPECIAL_VAR_5, \stringvar
	.endif
	.if \tobuff >= VARS_START
		copyvar SPECIAL_VAR_6, \tobuff
	.else
		setvar SPECIAL_VAR_6, \tobuff
	.endif
	special CallApprenticeFunction
	.endm

	@ Set which move to use that the player chose (implicitly SPECIAL_VAR_5)
	.macro apprentice_setmove
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SET_MOVE
	special CallApprenticeFunction
	.endm

	@ Set which mon the Apprentice should lead with
	.macro apprentice_setleadmon  monId:req
	copyvar SPECIAL_VAR_5, \monId
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SET_LEAD_MON
	special CallApprenticeFunction
	.endm

	@ Open the Bag Menu for the player to choose an item to recommend as a held item
	.macro apprentice_openbag
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_OPEN_BAG
	special CallApprenticeFunction
	waitstate
	.endm

	@ Try and set the recommended held item. FALSE if the item has been recommended before, as Battle Frontier forbids using the same held item for multiple party mons
	.macro apprentice_trysetitem
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_TRY_SET_HELD_ITEM
	special CallApprenticeFunction
	.endm

	@ Save the current Player Apprentice to the saveblock to make room for a new Apprentice
	.macro apprentice_save
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SAVE
	special CallApprenticeFunction
	.endm

	@ Set the object event gfx for the Apprentice based on their trainer class
	.macro apprentice_setgfx
	special CallApprenticeFunction
	.endm

	@ Always returns TRUE. No side effect. May have been for debug or dummied for some other reason
	.macro apprentice_shouldleave
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SHOULD_LEAVE
	special CallApprenticeFunction
	.endm

	@ Shift the other saved Apprentices over to make room for saving a new Apprentice
	.macro apprentice_shiftsaved
	setvar SPECIAL_VAR_4, APPRENTICE_FUNC_SHIFT_SAVED
	special CallApprenticeFunction
	.endm
