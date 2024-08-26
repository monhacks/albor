EventScript_PC::
	lockall
	setvar SPECIAL_VAR_4, PC_LOCATION_OTHER
	special DoPCTurnOnEffect
	playse SE_PC_ON
	goto EventScript_AccessPokemonStorage
	end

EventScript_TV::
	msgbox Text_EsteProgramaLeEncantaAMama, MSGBOX_DEFAULT
	closemessage
	end

EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	special ShowPokemonStorageSystemPC
	end

EventScript_TurnOffPC::
	setvar SPECIAL_VAR_4, PC_LOCATION_OTHER
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

Text_EsteProgramaLeEncantaAMama:
	.string "Este programa le encanta a mamá.$"
