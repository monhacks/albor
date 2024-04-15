Common_EventScript_PkmnCenterNurse::
	lock
	faceplayer
	setvar VAR_0x8004, 0
	incrementgamestat GAME_STAT_USED_POKECENTER
	message gText_BienvenidoAlCentroPokemon
	waitmessage
	call EventScript_PkmnCenterNurse_TakeAndHealPkmn
	end

EventScript_PkmnCenterNurse_TakeAndHealPkmn::
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	dofieldeffect FLDEFF_POKECENTER_HEAL
	waitfieldeffect FLDEFF_POKECENTER_HEAL
	applymovement VAR_0x800B, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	message gText_VuelveCuandoQuieras
	waitmessage
	delay 3
	closemessage
	end
