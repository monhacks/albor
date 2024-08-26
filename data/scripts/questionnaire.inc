EventScript_Questionnaire::
	lockall
	msgbox Questionnaire_Text_FillOut, MSGBOX_YESNO
	goto_if_eq SPECIAL_VAR_RESULT, NO, Questionnaire_EventScript_Release
	setvar SPECIAL_VAR_4, EASY_CHAT_TYPE_QUESTIONNAIRE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	specialvar SPECIAL_VAR_8, GetMartEmployeeObjectEventId
	goto_if_eq SPECIAL_VAR_4, 1, Questionnaire_EventScript_PlayerInputMysteryEventPhrase
	goto_if_eq SPECIAL_VAR_RESULT, 0, Questionnaire_EventScript_Release
	goto_if_eq SPECIAL_VAR_RESULT, 1, Questionnaire_EventScript_ThankYou
	end

Questionnaire_EventScript_PlayerInputMysteryEventPhrase::
	end

Questionnaire_EventScript_Release::
	releaseall
	end

Questionnaire_EventScript_ThankYou::
	applymovement SPECIAL_VAR_8, Common_Movement_FaceDown
	waitmovement 0
	msgbox Questionnaire_Text_ThankYou, MSGBOX_DEFAULT
	releaseall
	end
