Route120_EventScript_Kecleon1::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 1
	goto EventScript_Kecleon
	end

Route120_EventScript_Kecleon2::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 2
	goto EventScript_Kecleon
	end

Route120_EventScript_Kecleon3::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 3
	goto EventScript_Kecleon
	end

Route120_EventScript_Kecleon4::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 4
	goto EventScript_Kecleon
	end

Route120_EventScript_Kecleon5::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 5
	goto EventScript_Kecleon
	end

Route119_EventScript_Kecleon1::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 6
	goto EventScript_Kecleon
	end

Route119_EventScript_Kecleon2::
	lock
	faceplayer
	setvar SPECIAL_VAR_9, 7
	goto EventScript_Kecleon
	end

EventScript_Kecleon::
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq SPECIAL_VAR_RESULT, TRUE, EventScript_AskUseDevonScope
	msgbox Kecleon_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

EventScript_AskUseDevonScope::
	msgbox Kecleon_Text_WantToUseDevonScope, MSGBOX_YESNO
	goto_if_eq SPECIAL_VAR_RESULT, YES, EventScript_BattleKecleon
	release
	end

EventScript_BattleKecleon::
	msgbox Kecleon_Text_UseDevonScopeMonAttacked, MSGBOX_DEFAULT
	closemessage
	applymovement SPECIAL_VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	applymovement SPECIAL_VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar SPECIAL_VAR_RESULT, GetBattleOutcome
	goto_if_eq SPECIAL_VAR_RESULT, B_OUTCOME_WON, EventScript_RemoveKecleon
	goto_if_eq SPECIAL_VAR_RESULT, B_OUTCOME_RAN, EventScript_RemoveKecleon
	goto_if_eq SPECIAL_VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, EventScript_RemoveKecleon
	release
	end

EventScript_RemoveKecleon::
	goto Common_EventScript_RemoveStaticPokemon
	end

Movement_KecleonAppears:
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_8
	set_invisible
	delay_8
	set_visible
	delay_16
	set_invisible
	delay_16
	set_visible
	step_end
