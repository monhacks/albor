FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar SPECIAL_VAR_8, INGAME_TRADE_PLUSLE
	copyvar SPECIAL_VAR_4, SPECIAL_VAR_8
	specialvar SPECIAL_VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar SPECIAL_VAR_9, SPECIAL_VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq SPECIAL_VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar SPECIAL_VAR_10, SPECIAL_VAR_4
	goto_if_eq SPECIAL_VAR_4, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar SPECIAL_VAR_5, SPECIAL_VAR_10
	specialvar SPECIAL_VAR_RESULT, GetTradeSpecies
	copyvar SPECIAL_VAR_11, SPECIAL_VAR_RESULT
	goto_if_ne SPECIAL_VAR_RESULT, SPECIAL_VAR_9, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar SPECIAL_VAR_4, SPECIAL_VAR_8
	copyvar SPECIAL_VAR_5, SPECIAL_VAR_10
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, SPECIAL_VAR_9
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, SPECIAL_VAR_9
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "Wrooooaaar! I need it!\n"
	.string "I have to get me a {STR_VAR_1}!\l"
	.string "I'll do anything for it!\p"
	.string "…Uh… Did you hear that?\n"
	.string "My shout from the bottom of my heart?\p"
	.string "Having heard that, you will trade\n"
	.string "your {STR_VAR_1} for my {STR_VAR_2},\l"
	.string "won't you?$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "Oh, yeah, right on!\p"
	.string "{STR_VAR_1}, welcome!\n"
	.string "{STR_VAR_2}, you take care!$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Uh, no, I don't think so.\n"
	.string "That isn't a {STR_VAR_1}.$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "No? You won't trade me?\n"
	.string "Even after I bared my heart to you?$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "I'm going to make VOLBEAT super\n"
	.string "strong from this moment on!\p"
	.string "I hope you do the same with PLUSLE!$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "Trading POKéMON with others…\p"
	.string "It's as if you're trading your own\n"
	.string "memories with other people.$"

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Gumomoh?$"

