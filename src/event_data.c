#include "global.h"
#include "event_data.h"
#include "pokedex.h"

#define TEMP_FLAGS_SIZE     (TEMP_FLAGS_COUNT / 8)
#define DAILY_FLAGS_SIZE    (DAILY_FLAGS_COUNT / 8)
#define TRAINER_FLAGS_SIZE  (TRAINERS_COUNT / 8)
#define TEMP_VARS_SIZE      (NUM_TEMP_VARS * 2)      // 1/2 var per byte

EWRAM_DATA u16 gSpecialVar_0 = 0;
EWRAM_DATA u16 gSpecialVar_1 = 0;
EWRAM_DATA u16 gSpecialVar_2 = 0;
EWRAM_DATA u16 gSpecialVar_3 = 0;
EWRAM_DATA u16 gSpecialVar_4 = 0;
EWRAM_DATA u16 gSpecialVar_5 = 0;
EWRAM_DATA u16 gSpecialVar_6 = 0;
EWRAM_DATA u16 gSpecialVar_7 = 0;
EWRAM_DATA u16 gSpecialVar_8 = 0;
EWRAM_DATA u16 gSpecialVar_9 = 0;
EWRAM_DATA u16 gSpecialVar_10 = 0;
EWRAM_DATA u16 gSpecialVar_11 = 0;

EWRAM_DATA u16 gSpecialVar_Result = 0;
EWRAM_DATA u16 gSpecialVar_LastTalked = 0;
EWRAM_DATA u16 gSpecialVar_Facing = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxId = 0;
EWRAM_DATA u16 gSpecialVar_MonBoxPos = 0;

extern u16 *const gSpecialVars[];

void InitEventData(void)
{
    memset(gSaveBlock1Ptr->tempFlags, 0, sizeof(gSaveBlock1Ptr->tempFlags));
    memset(gSaveBlock1Ptr->normalFlags, 0, sizeof(gSaveBlock1Ptr->normalFlags));
    memset(gSaveBlock1Ptr->dailyFlags, 0, sizeof(gSaveBlock1Ptr->dailyFlags));
    memset(gSaveBlock1Ptr->trainerFlags, 0, sizeof(gSaveBlock1Ptr->trainerFlags));
    memset(gSaveBlock1Ptr->vars, 0, sizeof(gSaveBlock1Ptr->vars));
}

void ClearTempFieldEventData(void)
{
    memset(gSaveBlock1Ptr->tempFlags, 0, sizeof(gSaveBlock1Ptr->tempFlags));
    memset(&gSaveBlock1Ptr->vars[TEMP_VARS_START - VARS_START], 0, TEMP_VARS_SIZE);
    FlagClear(FLAG_SYS_ENC_UP_ITEM);
    FlagClear(FLAG_SYS_ENC_DOWN_ITEM);
    FlagClear(FLAG_SYS_USE_STRENGTH);
    FlagClear(FLAG_SYS_CTRL_OBJ_DELETE);
}

void ClearDailyFlags(void)
{
    memset(gSaveBlock1Ptr->dailyFlags, 0, sizeof(gSaveBlock1Ptr->dailyFlags));
    memset(gSaveBlock1Ptr->trainerFlags, 0, sizeof(gSaveBlock1Ptr->trainerFlags));
}

void DisableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 0);
    FlagClear(FLAG_SYS_RESET_RTC_ENABLE);
}

void EnableResetRTC(void)
{
    VarSet(VAR_RESET_RTC_ENABLE, 2336);
    FlagSet(FLAG_SYS_RESET_RTC_ENABLE);
}

bool32 CanResetRTC(void)
{
    if (FlagGet(FLAG_SYS_RESET_RTC_ENABLE) && VarGet(VAR_RESET_RTC_ENABLE) == 2336)
        return TRUE;
    else
        return FALSE;
}

u16 *GetVarPointer(u16 id)
{
    if (id < VARS_START)
        return NULL;
    else if (id < SPECIAL_VARS_START)
        return &gSaveBlock1Ptr->vars[id - VARS_START];
    else
        return gSpecialVars[id - SPECIAL_VARS_START];
}

u16 VarGet(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return id;
    return *ptr;
}

u16 VarGetIfExist(u16 id)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return 65535;
    return *ptr;
}

bool8 VarSet(u16 id, u16 value)
{
    u16 *ptr = GetVarPointer(id);
    if (!ptr)
        return FALSE;
    *ptr = value;
    return TRUE;
}

u16 VarGetObjectEventGraphicsId(u8 id)
{
    return VarGet(VAR_OBJ_GFX_ID_0 + id);
}

u8 *GetFlagPointer(u16 id)
{
    if (id == 0)
        return NULL;
    else
        return &gSaveBlock1Ptr->normalFlags[id / 8];
}

u8 FlagSet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr |= 1 << (id & 7);
    return 0;
}

u8 FlagToggle(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr ^= 1 << (id & 7);
    return 0;
}

u8 FlagClear(u16 id)
{
    u8 *ptr = GetFlagPointer(id);
    if (ptr)
        *ptr &= ~(1 << (id & 7));
    return 0;
}

bool8 FlagGet(u16 id)
{
    u8 *ptr = GetFlagPointer(id);

    if (!ptr)
        return FALSE;

    if (!(((*ptr) >> (id & 7)) & 1))
        return FALSE;

    return TRUE;
}
