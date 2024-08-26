@ Seems this was superseded by the Record Center, and the below scripts are now unused
EventScript_MixRecordsPrompt::
	lock
	faceplayer
	msgbox Text_WouldYouLikeToMixRecords, MSGBOX_YESNO
	goto_if_eq SPECIAL_VAR_RESULT, YES, EventScript_MixRecords
	goto_if_eq SPECIAL_VAR_RESULT, NO, EventScript_EndMixRecords
	goto EventScript_EndMixRecords

EventScript_MixRecords::
	waitstate
	lock
	faceplayer
EventScript_EndMixRecords::
	message Text_WeHopeToSeeYouAgain
	waitmessage
	waitbuttonpress
	release
	end
