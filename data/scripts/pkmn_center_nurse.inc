Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar SPECIAL_VAR_4, 0
	incrementgamestat GAME_STAT_USED_POKECENTER
	message gText_BienvenidoAlCentroPokemon
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	end

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	applymovement SPECIAL_VAR_11, Movement_PkmnCenterNurse_Turn @ Changed from Common_Movement_WalkInPlaceFasterLeft to force the follower to enter their Poké Ball
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement SPECIAL_VAR_11, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	msgbox gText_VuelveCuandoQuieras, MSGBOX_DEFAULT
	release
	end

Movement_PkmnCenterNurse_Turn:
	walk_in_place_faster_left
	step_end
