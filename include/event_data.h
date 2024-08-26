#ifndef GUARD_EVENT_DATA_H
#define GUARD_EVENT_DATA_H

void InitEventData(void);
void ClearTempFieldEventData(void);
void ClearDailyFlags(void);
void DisableResetRTC(void);
void EnableResetRTC(void);
bool32 CanResetRTC(void);
u16 *GetVarPointer(u16 id);
u16 VarGet(u16 id);
u16 VarGetIfExist(u16 id);
bool8 VarSet(u16 id, u16 value);
u16 VarGetObjectEventGraphicsId(u8 id);
u8 *GetFlagPointer(u16 id);
u8 FlagSet(u16 id);
u8 FlagToggle(u16 id);
u8 FlagClear(u16 id);
bool8 FlagGet(u16 id);

extern u16 gSpecialVar_0;
extern u16 gSpecialVar_1;
extern u16 gSpecialVar_2;
extern u16 gSpecialVar_3;
extern u16 gSpecialVar_4;
extern u16 gSpecialVar_5;
extern u16 gSpecialVar_6;
extern u16 gSpecialVar_7;
extern u16 gSpecialVar_8;
extern u16 gSpecialVar_9;
extern u16 gSpecialVar_10;
extern u16 gSpecialVar_11;
extern u16 gSpecialVar_Facing;
extern u16 gSpecialVar_Result;
extern u16 gSpecialVar_ItemID;
extern u16 gSpecialVar_LastTalked;
extern u16 gSpecialVar_ContestRank;
extern u16 gSpecialVar_ContestCategory;
extern u16 gSpecialVar_MonBoxId;
extern u16 gSpecialVar_MonBoxPos;

#endif // GUARD_EVENT_DATA_H
