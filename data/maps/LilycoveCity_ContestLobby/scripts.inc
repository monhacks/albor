@ Note: data/scripts/berry_blender.inc is for the same map, so shares local IDs
.set LOCALID_RECEPTIONIST, 1
.set LOCALID_LINK_RECEPTIONIST, 2
.set LOCALID_ARTIST, 4
.set LOCALID_ARTIST_LINK, 11

LilycoveCity_ContestLobby_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_ContestLobby_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LilycoveCity_ContestLobby_OnFrame
	.byte 0

@ Some scripts for this room are split into data/scripts/contest_hall and data/scripts/berry_blender

LilycoveCity_ContestLobby_OnTransition:
	end

LilycoveCity_ContestLobby_EventScript_TryShowBlendMaster::
	return

LilycoveCity_ContestLobby_EventScript_ShowBlendMaster::
	return

LilycoveCity_ContestLobby_OnFrame:
	.2byte 0

LilycoveCity_ContestLobby_EventScript_TryDoContestArtist::
	end

LilycoveCity_ContestLobby_EventScript_ContestArtist::
	end

LilycoveCity_ContestLobby_EventScript_TakePaintingToMuseum::
	end

LilycoveCity_ContestLobby_EventScript_ConfirmDontTakePainting::
	end

LilycoveCity_ContestLobby_EventScript_ReceivedArtistRibbon::
	return

LilycoveCity_ContestLobby_EventScript_UpdateMuseumPatrons::
	return

LilycoveCity_ContestLobby_EventScript_ShowPatron1::
	return

LilycoveCity_ContestLobby_EventScript_ShowPatron2::
	return

LilycoveCity_ContestLobby_EventScript_ShowPatron3::
	return

LilycoveCity_ContestLobby_EventScript_ShowPatron4::
	return

LilycoveCity_ContestLobby_EventScript_ShowTourists::
	return

LilycoveCity_ContestLobby_EventScript_SetPaintingFlag::
	return

LilycoveCity_ContestLobby_EventScript_MadeCoolPainting::
	return

LilycoveCity_ContestLobby_EventScript_MadeBeautyPainting::
	return

LilycoveCity_ContestLobby_EventScript_MadeCutePainting::
	return

LilycoveCity_ContestLobby_EventScript_MadeSmartPainting::
	return

LilycoveCity_ContestLobby_EventScript_MadeToughPainting::
	return

LilycoveCity_ContestLobby_Movement_ArtistApproachPlayer:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LilycoveCity_ContestLobby_Movement_ArtistExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LilycoveCity_ContestLobby_Movement_PlayerFaceArtist:
	walk_in_place_faster_left
	step_end

LilycoveCity_ContestLobby_Movement_ArtistBeginToExit:
	walk_down
	walk_down
	walk_down
	step_end

LilycoveCity_ContestLobby_Movement_ArtistReturnToPlayer:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_right
	step_end

LilycoveCity_ContestLobby_EventScript_TryDoLinkContestArtist::
	end

LilycoveCity_ContestLobby_EventScript_LinkContestArtist::
	end

LilycoveCity_ContestLobby_EventScript_TakePaintingToMuseumLink::
	end

LilycoveCity_ContestLobby_EventScript_ConfirmDontTakePaintingLink::
	end

LilycoveCity_ContestLobby_EventScript_ReceivedLinkArtistRibbon::
	return

LilycoveCity_ContestLobby_Movement_LinkArtistApproachPlayer:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LilycoveCity_ContestLobby_Movement_LinkArtistExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LilycoveCity_ContestLobby_Movement_PlayerFaceLinkArtist:
	walk_in_place_faster_right
	step_end

LilycoveCity_ContestLobby_Movement_LinkArtistBeginExit:
	walk_down
	walk_down
	walk_down
	step_end

LilycoveCity_ContestLobby_Movement_LinkArtistReturnToPlayer:
	delay_16
	delay_16
	delay_16
	delay_16
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_in_place_faster_left
	step_end

LilycoveCity_ContestLobby_EventScript_ContestReceptionist::
	end

LilycoveCity_ContestLobby_EventScript_SetContestType::
	return

LilycoveCity_ContestLobby_EventScript_SetNormalContestType::
	return

LilycoveCity_ContestLobby_EventScript_SetSuperContestType::
	return

LilycoveCity_ContestLobby_EventScript_SetHyperContestType::
	return

LilycoveCity_ContestLobby_EventScript_SetMasterContestType::
	return

LilycoveCity_ContestLobby_EventScript_WarpToContestHall::
	return

LilycoveCity_ContestLobby_EventScript_WarpToCoolContestHall::
	return

LilycoveCity_ContestLobby_EventScript_WarpToBeautyContestHall::
	return

LilycoveCity_ContestLobby_EventScript_WarpToCuteContestHall::
	return

LilycoveCity_ContestLobby_EventScript_WarpToSmartContestHall::
	return

LilycoveCity_ContestLobby_EventScript_WarpToToughContestHall::
	return

LilycoveCity_ContestLobby_EventScript_LeadToContestHall::
	return

LilycoveCity_ContestLobby_Movement_PlayerWalkToContestHall:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

LilycoveCity_ContestLobby_Movement_PlayerApproachReceptionist:
	walk_in_place_faster_left
	walk_left
	step_end

LilycoveCity_ContestLobby_Movement_ReceptionistApproachCounter:
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LilycoveCity_ContestLobby_Movement_ReceptionistExitCounter:
	walk_down
	walk_down
	walk_in_place_faster_up
	step_end

LilycoveCity_ContestLobby_Movement_ReceptionistWalkToContestHall:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

LilycoveCity_ContestLobby_Movement_ReceptionistFacePlayer:
	walk_in_place_faster_right
	step_end

LilycoveCity_ContestLobby_EventScript_BlackBelt::
	end

LilycoveCity_ContestLobby_EventScript_Girl::
	end

LilycoveCity_ContestLobby_EventScript_Artist::
	end

LilycoveCity_ContestLobby_EventScript_FatMan::
	end

LilycoveCity_ContestLobby_EventScript_Fisherman::
	end

LilycoveCity_ContestLobby_EventScript_NinjaBoy::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner1::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner2::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner3::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner4::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner5::
	end

LilycoveCity_ContestLobby_EventScript_ContestWinner6::
	end

LilycoveCity_ContestLobby_EventScript_Blender3Boy::
	end

LilycoveCity_ContestLobby_EventScript_Blender3Girl::
	end

LilycoveCity_ContestLobby_EventScript_BerryBlenderSpeedRecords::
	end

LilycoveCity_ContestLobby_EventScript_LinkContestResults::
	end

LilycoveCity_ContestLobby_EventScript_BlendMaster::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker1::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker2::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker3::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker4::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker5::
	end

LilycoveCity_ContestLobby_EventScript_BlendMasterOnlooker6::
	end

LilycoveCity_ContestLobby_EventScript_FaceOriginalDirection::
	end

LilycoveCity_ContestLobby_EventScript_LinkContestReceptionist::
	end

LilycoveCity_ContestLobby_EventScript_AskEnterLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_TryEnterLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_EmeraldMode::
	end

LilycoveCity_ContestLobby_EventScript_GlobalMode::
	end

LilycoveCity_ContestLobby_EventScript_ChooseLinkContestType::
	end

LilycoveCity_ContestLobby_EventScript_LinkContestInfo::
	end

LilycoveCity_ContestLobby_EventScript_ExplainLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_ExplainEMode::
	end

LilycoveCity_ContestLobby_EventScript_ExplainGMode::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_ChooseLinkContestMon::
	end

LilycoveCity_ContestLobby_EventScript_LinkCantEnterLowRank::
	end

LilycoveCity_ContestLobby_EventScript_LinkCantEnterEgg::
	end

LilycoveCity_ContestLobby_EventScript_LinkCantEnterFainted::
	end

LilycoveCity_ContestLobby_EventScript_EnterMonForLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_TrySetUpLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_TryLinkEMode::
	return

LilycoveCity_ContestLobby_EventScript_TryLinkGMode::
	return

LilycoveCity_ContestLobby_EventScript_CancelLinkDifferentContest::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkDifferentChoices::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkModeDifference::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkError::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkNoWirelessGMode::
	end

LilycoveCity_ContestLobby_EventScript_CancelLinkTransmissionError::
	end

LilycoveCity_ContestLobby_EventScript_StartLinkContest::
	end

LilycoveCity_ContestLobby_EventScript_SetLinkGroupType::
	end

LilycoveCity_ContestLobby_EventScript_SetLinkGroupCoolContest::
	return

LilycoveCity_ContestLobby_EventScript_SetLinkGroupBeautyContest::
	return

LilycoveCity_ContestLobby_EventScript_SetLinkGroupCuteContest::
	return

LilycoveCity_ContestLobby_EventScript_SetLinkGroupSmartContest::
	return

LilycoveCity_ContestLobby_EventScript_SetLinkGroupToughContest::
	return

LilycoveCity_ContestLobby_EventScript_DecideLinkLeader::
	end

LilycoveCity_ContestLobby_EventScript_TryLeadGroup::
	end

LilycoveCity_ContestLobby_EventScript_TryJoinGroup::
	end

LilycoveCity_ContestLobby_EventScript_TryBecomeLinkLeader::
	return

LilycoveCity_ContestLobby_EventScript_TryJoinLinkGroup::
	return

LilycoveCity_ContestLobby_EventScript_LinkLeaderDecided::
	end

LilycoveCity_ContestLobby_EventScript_LeadToLinkContestHall::
	return

LilycoveCity_ContestLobby_Movement_PlayerWalkToLinkContestHall:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

LilycoveCity_ContestLobby_Movement_PlayerApproachLinkReceptionist:
	walk_right
	step_end

LilycoveCity_ContestLobby_Movement_LinkReceptionistApproachCounter:
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

LilycoveCity_ContestLobby_Movement_LinkReceptionistExitCounter:
	walk_down
	walk_down
	walk_in_place_faster_up
	step_end

LilycoveCity_ContestLobby_Movement_LinkReceptionistWalkToContestHall:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	delay_8
	set_invisible
	step_end

LilycoveCity_ContestLobby_Movement_LinkReceptionistFacePlayer:
	walk_in_place_faster_left
	step_end

LilycoveCity_ContestLobby_EventScript_LittleGirl::
	end

LilycoveCity_ContestLobby_EventScript_LittleGirlHaveCase::
	end

LilycoveCity_ContestLobby_Text_LadyGaveMePokeblockCase:
	.string "Yippee!\p"
	.string "The lady at the reception counter\n"
	.string "gave me a case for {POKEBLOCK}S!$"

LilycoveCity_ContestLobby_Text_MakePokeblocksDifferentBerries:
	.string "Make {POKEBLOCK}S and put them in there.\p"
	.string "When you make a {POKEBLOCK}, everyone\n"
	.string "has to put in a different BERRY.$"

LilycoveCity_ContestLobby_Text_YourPokemonSpurredMeToPaint:
	.string "Congratulations!\p"
	.string "I did a painting of your POKéMON to\n"
	.string "commemorate its victory…\p"
	.string "Well, your POKéMON's appeals were\n"
	.string "so fantastic, it spurred me into\l"
	.string "painting better than I usually do.\l"
	.string "Look, see?$"

LilycoveCity_ContestLobby_Text_ShouldITakePaintingToMuseum:
	.string "What do you think? I'm confident in\n"
	.string "what I've done, but do you like it?\p"
	.string "A work of this caliber, it wouldn't look\n"
	.string "out of place in an art museum.\p"
	.string "Huh? An art museum really is looking\n"
	.string "for paintings?\p"
	.string "Do you think I should take this there?$"

LilycoveCity_ContestLobby_Text_IllTakePaintingToMuseum:
	.string "What, really? Then, sure, I will take\n"
	.string "this painting there right now.\p"
	.string "I'll give it a proper title, too.\p"
	.string "I hope they'll like it and consider\n"
	.string "exhibiting this.\p"
	.string "Please check if they did accept this.\n"
	.string "Thank you!$"

LilycoveCity_ContestLobby_Text_TakeMementoOfPainting:
	.string "Oh, that's right!\p"
	.string "As a memento of me painting your\n"
	.string "POKéMON, please take this.$"

LilycoveCity_ContestLobby_Text_ReceivedARibbon:
	.string "{PLAYER} received a RIBBON.$"

LilycoveCity_ContestLobby_Text_PutTheRibbonOnMon:
	.string "{PLAYER} put the RIBBON on\n"
	.string "{STR_VAR_1}.$"

LilycoveCity_ContestLobby_Text_OkaySeeYou:
	.string "Okay, see you!$"

LilycoveCity_ContestLobby_Text_TakeHomeButIdLikeToTakeToMuseum:
	.string "Oh… Then, I guess I'll just take\n"
	.string "this home with me…\p"
	.string "But, you know, I would like to take\n"
	.string "this to the art museum… Okay?$"

LilycoveCity_ContestLobby_Text_FineThatsTheWayItIs:
	.string "Oh, fine, that's the way it is.\n"
	.string "I will hang this in my own house.\p"
	.string "I'll just have to try harder next time.\n"
	.string "Well, be seeing you.$"

LilycoveCity_ContestLobby_Text_MasterRankHereICome:
	.string "Hoo, boy… Master Rank CONTESTS,\n"
	.string "here I come.\p"
	.string "The world will know that my dearest\n"
	.string "POKéMON is the cutest being in all\l"
	.string "existence. The time has come!\l"
	.string "Uheheheh.$"

LilycoveCity_ContestLobby_Text_WholeVarietyOfPokemonHere:
	.string "You can see a whole variety of\n"
	.string "POKéMON here.\p"
	.string "That's why I make this place a regular\n"
	.string "part of my daily stroll.$"

LilycoveCity_ContestLobby_Text_ContestFeastForEyes:
	.string "Wow, coming out to a CONTEST is\n"
	.string "a feast for these eyes!\p"
	.string "Would you look at all the POKéMON\n"
	.string "that just scream to be painted?$"

LilycoveCity_ContestLobby_Text_ToughContestIsExtreme:
	.string "The TOUGHNESS CONTEST is like\n"
	.string "extreme, man!\p"
	.string "Those muscular appeals…\n"
	.string "Cascading sweat… I swoon!$"

LilycoveCity_ContestLobby_Text_LavishedCareOnMon:
	.string "Day in and day out, I lavished my care\n"
	.string "on this POKéMON.\p"
	.string "Its condition is peaking.\n"
	.string "Today, victory is mine!$"

LilycoveCity_ContestLobby_Text_MadePokeblocksWithFamily:
	.string "I made {POKEBLOCK}S with Mom, Dad, and\n"
	.string "Big Sister. They turned out great!\p"
	.string "I bet you can make smoother, better\n"
	.string "{POKEBLOCK}S if you have more people.$"

