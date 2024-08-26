Std_RegisteredInMatchCall::
	buffertrainerclassname STR_VAR_1, SPECIAL_VAR_0
	buffertrainername STR_VAR_2, SPECIAL_VAR_0
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox gText_RegisteredTrainerinPokeNav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	return

EventScript_TryGetTrainerScript::
	special ShouldTryGetTrainerScript
	goto_if_eq SPECIAL_VAR_RESULT, TRUE, EventScript_GotoTrainerScript
	releaseall
	end

EventScript_GotoTrainerScript::
	gotobeatenscript
	releaseall
	end
