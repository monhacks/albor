@ Note: LOCALID_UNION_ROOM_PLAYER_# are local ids for this map used elsewhere. They're defined in event_objects.h

UnionRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, UnionRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, UnionRoom_OnTransition
	.byte 0

UnionRoom_OnResume:
	end

UnionRoom_OnTransition:
	setflag FLAG_TEMP_HIDE_FOLLOWER
	end

UnionRoom_EventScript_Player1::
	end

UnionRoom_EventScript_Player2::
	end

UnionRoom_EventScript_Player3::
	end

UnionRoom_EventScript_Player4::
	end

UnionRoom_EventScript_Player5::
	end

UnionRoom_EventScript_Player6::
	end

UnionRoom_EventScript_Player7::
	end

UnionRoom_EventScript_Player8::
	end

UnionRoom_EventScript_Attendant::
	end
