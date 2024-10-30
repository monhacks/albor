#ifndef GUARD_TEST_RUNNER_H
#define GUARD_TEST_RUNNER_H

extern const bool8 gTestRunnerEnabled;
extern const bool8 gTestRunnerHeadless;
extern const bool8 gTestRunnerSkipIsFail;

#define TestRunner_Battle_RecordAbilityPopUp(...) (void)0
#define TestRunner_Battle_RecordAnimation(...) (void)0
#define TestRunner_Battle_RecordHP(...) (void)0
#define TestRunner_Battle_RecordExp(...) (void)0
#define TestRunner_Battle_RecordMessage(...) (void)0
#define TestRunner_Battle_RecordStatus1(...) (void)0
#define TestRunner_Battle_AfterLastTurn(...) (void)0
#define TestRunner_Battle_CheckChosenMove(...) (void)0
#define TestRunner_Battle_CheckSwitch(...) (void)0
#define TestRunner_Battle_CheckAiMoveScores(...) (void)0
#define TestRunner_Battle_AISetScore(...) (void)0
#define TestRunner_Battle_AIAdjustScore(...) (void)0
#define TestRunner_Battle_InvalidNoHPMon(...) (void)0

#define TestRunner_Battle_CheckBattleRecordActionType(...) (void)0

#define TestRunner_Battle_GetForcedAbility(...) (u32)0

#define TestRunner_Battle_GetChosenGimmick(...) (u32)0

#endif
