#ifndef GUARD_RTC_UTIL_H
#define GUARD_RTC_UTIL_H

#include "siirtc.h"

#define HORA_INICIO_MANANA          6
#define HORA_MEDIA_MANANA           8
#define HORA_FINAL_MANANA           10

#define HORA_INICIO_DIA             10
#define HORA_FINAL_DIA              18

#define HORA_INICIO_TARDE           18
#define HORA_MEDIA_TARDE            20
#define HORA_FINAL_TARDE            22

#define HORA_INICIO_NOCHE           22
#define HORA_FINAL_NOCHE            6

enum TiemposDia
{
    TIEMPO_MANANA,
    TIEMPO_DIA,
    TIEMPO_TARDE,
    TIEMPO_NOCHE
};

extern struct Time gLocalTime;

void RtcDisableInterrupts(void);
void RtcRestoreInterrupts(void);
bool8 IsLeapYear(u32 year);
void RtcGetInfo(struct SiiRtcInfo *rtc);
void RtcGetDateTime(struct SiiRtcInfo *rtc);
void RtcGetStatus(struct SiiRtcInfo *rtc);
void RtcReset(void);
void FormatDecimalTime(u8 *dest, s32 hour, s32 minute, s32 second);
void FormatDecimalDate(u8 *dest, s32 year, s32 month, s32 day);
void RtcCalcTimeDifference(struct SiiRtcInfo *rtc, struct Time *result, struct Time *t);
void RtcCalcLocalTime(void);
bool8 IsBetweenHours(s32 hours, s32 begin, s32 end);
u8 GetTimeOfDay(void);
void RtcInitLocalTimeOffset(s32 hour, s32 minute);
void RtcCalcLocalTimeOffset(s32 days, s32 hours, s32 minutes, s32 seconds);
void CalcTimeDifference(struct Time *result, struct Time *t1, struct Time *t2);
u32 RtcGetMinuteCount(void);
void FormatDecimalTimeWithoutSeconds(u8 *dest, s8 hour, s8 minute, bool32 is24Hour);

#endif // GUARD_RTC_UTIL_H
