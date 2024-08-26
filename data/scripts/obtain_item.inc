.set ITEMID, SPECIAL_VAR_0
.set AMOUNT, SPECIAL_VAR_1

Std_ObtainItem::
	additem ITEMID, AMOUNT
	copyvar SPECIAL_VAR_7, SPECIAL_VAR_RESULT
	call EventScript_ObtainItemMessage
	return

EventScript_ObtainItemMessage::
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call EventScript_BufferPocketNameAndTryFanfare
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_ObtainedItem
	call_if_eq SPECIAL_VAR_7, FALSE, EventScript_NoRoomForItem
	return

EventScript_BufferPocketNameAndTryFanfare::
	switch SPECIAL_VAR_RESULT
	case POCKET_ITEMS,      EventScript_BufferItemsPocket
	case POCKET_KEY_ITEMS,  EventScript_BufferKeyItemsPocket
	case POCKET_POKE_BALLS, EventScript_BufferPokeballsPocket
	case POCKET_TM_HM,      EventScript_BufferTMHMsPocket
	case POCKET_BERRIES,    EventScript_BufferBerriesPocket
	end

EventScript_BufferItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_ITEMS
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferKeyItemsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_KEYITEMS
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferPokeballsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_POKEBALLS
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PlayFanfareObtainedItem
	return

EventScript_BufferTMHMsPocket::
	bufferstdstring STR_VAR_3, STDSTRING_TMHMS
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PlayFanfareObtainedTMHM
	return

EventScript_BufferBerriesPocket::
	bufferstdstring STR_VAR_3, STDSTRING_BERRIES
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PlayFanfareObtainedItem
	return

EventScript_ObtainedItem::
	compare SPECIAL_VAR_1, TRUE
	goto_if_eq EventScript_ObtainedItemMessage
	buffernumberstring 0, SPECIAL_VAR_1
	message gText_ObtainedTheItems
	goto EventScript_ContinueObtainedItem
EventScript_ObtainedItemMessage:
	message gText_ObtainedTheItem
EventScript_ContinueObtainedItem:
	waitfanfare
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	setvar SPECIAL_VAR_RESULT, TRUE
	return

EventScript_NoRoomForItem::
	setvar SPECIAL_VAR_RESULT, FALSE
	return

EventScript_PlayFanfareObtainedItem::
	playfanfare MUS_OBTAIN_ITEM
	return

EventScript_PlayFanfareObtainedTMHM::
	playfanfare MUS_OBTAIN_TMHM
	return

Std_ObtainDecoration::
	adddecoration ITEMID
	copyvar SPECIAL_VAR_7, SPECIAL_VAR_RESULT
	call EventScript_ObtainDecorationMessage
	return

EventScript_ObtainDecorationMessage::
	bufferdecorationname STR_VAR_2, ITEMID
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_ObtainedDecor
	call_if_eq SPECIAL_VAR_7, FALSE, EventScript_NoRoomForDecor
	return

EventScript_ObtainedDecor::
	playfanfare MUS_OBTAIN_ITEM
	message gText_ObtainedTheDecor
	waitfanfare
	msgbox gText_TheDecorWasTransferredToThePC, MSGBOX_DEFAULT
	setvar SPECIAL_VAR_RESULT, TRUE
	return

EventScript_NoRoomForDecor::
	setvar SPECIAL_VAR_RESULT, FALSE
	return

Std_FindItem::
	lock
	faceplayer
	waitse
	copyvar SPECIAL_VAR_4, ITEMID
	copyvar SPECIAL_VAR_5, AMOUNT
	checkitemspace ITEMID, AMOUNT
	copyvar SPECIAL_VAR_7, SPECIAL_VAR_RESULT
	bufferitemnameplural STR_VAR_2, ITEMID, AMOUNT
	checkitemtype ITEMID
	call EventScript_BufferPocketNameAndTryFanfare
	call_if_eq SPECIAL_VAR_7, TRUE, EventScript_PickUpItem
	call_if_eq SPECIAL_VAR_7, FALSE, EventScript_NoRoomToPickUpItem
	release
	return

EventScript_PickUpItem::
	removeobject SPECIAL_VAR_LAST_TALKED
	additem SPECIAL_VAR_4, SPECIAL_VAR_5
	specialvar SPECIAL_VAR_RESULT, BufferTMHMMoveName
	copyvar SPECIAL_VAR_8, SPECIAL_VAR_RESULT
	call_if_eq SPECIAL_VAR_8, TRUE, EventScript_FoundTMHM
	call_if_eq SPECIAL_VAR_8, FALSE, EventScript_FoundItem
	waitfanfare
	waitmessage
	bufferitemnameplural STR_VAR_2, SPECIAL_VAR_4, SPECIAL_VAR_5
	pyramid_inchallenge
	goto_if_eq SPECIAL_VAR_RESULT, TRUE, EventScript_PutBattlePyramidItemInBag
	msgbox gText_PutItemInPocket, MSGBOX_DEFAULT
	return

EventScript_PutBattlePyramidItemInBag::
	msgbox gText_PlayerPutItemInBag, MSGBOX_DEFAULT
	return

EventScript_FoundTMHM::
	bufferitemnameplural STR_VAR_1, SPECIAL_VAR_4, SPECIAL_VAR_5
	compare SPECIAL_VAR_5, 2
	goto_if_lt EventScript_FoundTMHMMessage
	buffernumberstring STR_VAR_3, SPECIAL_VAR_5
	message gText_PlayerFoundTMHMs
	goto EventScript_BufferTMHMsPocket
	return
EventScript_FoundTMHMMessage::
	message gText_PlayerFoundOneTMHM
	return

EventScript_FoundItem::
	compare SPECIAL_VAR_1, TRUE
	goto_if_eq EventScript_FoundItemMessage
	buffernumberstring 0, SPECIAL_VAR_1
	message gText_PlayerFoundItems
	return
EventScript_FoundItemMessage::
	message gText_PlayerFoundOneItem
	return

EventScript_NoRoomToPickUpItem::
	msgbox gText_ObtainedTheItem, MSGBOX_DEFAULT
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar SPECIAL_VAR_RESULT, FALSE
	return

EventScript_HiddenItemScript::
	lockall
	waitse
	additem SPECIAL_VAR_5
	copyvar SPECIAL_VAR_7, SPECIAL_VAR_RESULT
	bufferitemnameplural STR_VAR_2, SPECIAL_VAR_5, 1
	checkitemtype SPECIAL_VAR_5
	call EventScript_BufferPocketNameAndTryFanfare
	goto_if_eq SPECIAL_VAR_7, TRUE, EventScript_PickUpHiddenItem
	goto_if_eq SPECIAL_VAR_7, FALSE, EventScript_NoRoomForHiddenItem
	end

EventScript_PickUpHiddenItem::
	copyvar SPECIAL_VAR_8, SPECIAL_VAR_4
	copyvar SPECIAL_VAR_4, SPECIAL_VAR_5
	specialvar SPECIAL_VAR_RESULT, BufferTMHMMoveName
	goto_if_eq SPECIAL_VAR_RESULT, TRUE, EventScript_FoundHiddenTMHM
	goto_if_eq SPECIAL_VAR_RESULT, FALSE, EventScript_FoundHiddenItem
	end

EventScript_FoundHiddenTMHM::
	bufferitemnameplural STR_VAR_1, SPECIAL_VAR_4, 1
	message gText_PlayerFoundOneTMHM
	goto EventScript_PutHiddenItemInPocket
	end

EventScript_FoundHiddenItem::
	message gText_PlayerFoundOneItem
	goto EventScript_PutHiddenItemInPocket
	end

EventScript_PutHiddenItemInPocket::
	end

EventScript_NoRoomForHiddenItem::
	msgbox gText_PlayerFoundOneItem, MSGBOX_DEFAULT
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	setvar SPECIAL_VAR_RESULT, 0
	releaseall
	end
