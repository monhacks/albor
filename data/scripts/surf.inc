EventScript_UseSurf::
	checkpartymove MOVE_SURF
	goto_if_eq SPECIAL_VAR_RESULT, PARTY_SIZE, EventScript_EndUseSurf
	bufferpartymonnick STR_VAR_1, SPECIAL_VAR_RESULT
	setfieldeffectargument 0, SPECIAL_VAR_RESULT
	lockall
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
	releaseall
EventScript_EndUseSurf::
	end
