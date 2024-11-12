TrainerHill_OnResume:
	end

TrainerHill_OnWarp:
	end

TrainerHill_OnFrame:
	end

EventScript_TrainerHillTimer::
	end

TrainerHill_EventScript_WarpToEntranceCounter::
	end

@ TRAINER_PHILLIP is an actual Trainer on the SS Tidal, but is used as a placeholder here
TrainerHill_EventScript_TrainerBattle::
	trainerbattle TRAINER_BATTLE_HILL, TRAINER_PHILLIP, 0, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	trainerhill_postbattletext
	waitmessage
	waitbuttonpress
	closemessage
	end
