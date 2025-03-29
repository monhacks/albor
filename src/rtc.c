#include "global.h"
#include "rtc.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"

static struct SiiRtcInfo sRtc;
static u16 sSavedIme;

COMMON_DATA struct Time gLocalTime = {0};

static const s32 sNumDaysInMonths[MONTH_COUNT] =
{
    [ENERO - 1] = 31,
    [FEBRERO - 1] = 28,
    [MARZO - 1] = 31,
    [ABRIL - 1] = 30,
    [MONTH_MAY - 1] = 31,
    [MONTH_JUN - 1] = 30,
    [MONTH_JUL - 1] = 31,
    [MONTH_AUG - 1] = 31,
    [MONTH_SEP - 1] = 30,
    [MONTH_OCT - 1] = 31,
    [MONTH_NOV - 1] = 30,
    [MONTH_DEC - 1] = 31,
};

void RtcDisableInterrupts(void)
{
    sSavedIme = REG_IME;
    REG_IME = 0;
}

void RtcRestoreInterrupts(void)
{
    REG_IME = sSavedIme;
}

bool8 IsLeapYear(u32 year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return TRUE;

    return FALSE;
}

void RtcGetInfo(struct SiiRtcInfo *rtc)
{
    FakeRtc_GetRawInfo(rtc);
}

void RtcGetDateTime(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetDateTime(rtc);
    RtcRestoreInterrupts();
}

void RtcGetStatus(struct SiiRtcInfo *rtc)
{
    RtcDisableInterrupts();
    SiiRtcGetStatus(rtc);
    RtcRestoreInterrupts();
}

void RtcReset(void)
{
    if (OW_USE_FAKE_RTC)
    {
        memset(HoraActual(), 0, sizeof(struct Time));
        return;
    }

    RtcDisableInterrupts();
    SiiRtcReset();
    RtcRestoreInterrupts();
}

void FormatDecimalTime(u8 *dest, s32 hour, s32 minute, s32 second)
{
    dest = ConvertIntToDecimalStringN(dest, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_COLON;
    dest = ConvertIntToDecimalStringN(dest, second, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void FormatDecimalDate(u8 *dest, s32 year, s32 month, s32 day)
{
    dest = ConvertIntToDecimalStringN(dest, year, STR_CONV_MODE_LEADING_ZEROS, 4);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, month, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest++ = CHAR_HYPHEN;
    dest = ConvertIntToDecimalStringN(dest, day, STR_CONV_MODE_LEADING_ZEROS, 2);
    *dest = EOS;
}

void RtcCalcTimeDifference(struct SiiRtcInfo *rtc, struct Time *result, struct Time *t)
{
    u16 days = rtc->day;
    result->seconds = rtc->second - t->seconds;
    result->minutes = rtc->minute - t->minutes;
    result->hours = rtc->hour - t->hours;
    result->days = days - t->days;

    if (result->seconds < 0)
    {
        result->seconds += SEGUNDOS_POR_MINUTO;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += MINUTOS_POR_HORA;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += HORAS_POR_DIA;
        --result->days;
    }
}

void RtcCalcLocalTime(void)
{
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gLocalTime, &gSaveBlockPtr->localTimeOffset);
}

bool8 IsBetweenHours(s32 hours, s32 begin, s32 end)
{
    if (end < begin)
        return hours >= begin || hours < end;
    else
        return hours >= begin && hours < end;
}

u8 GetTimeOfDay(void)
{
    RtcCalcLocalTime();
    if (IsBetweenHours(gLocalTime.hours, HORA_INICIO_MANANA, HORA_FINAL_MANANA))
        return TIEMPO_MANANA;
    else if (IsBetweenHours(gLocalTime.hours, HORA_INICIO_TARDE, HORA_FINAL_TARDE))
        return TIEMPO_TARDE;
    else if (IsBetweenHours(gLocalTime.hours, HORA_INICIO_NOCHE, HORA_FINAL_NOCHE))
        return TIEMPO_NOCHE;
    return TIEMPO_DIA;
}

void RtcInitLocalTimeOffset(s32 hour, s32 minute)
{
    RtcCalcLocalTimeOffset(0, hour, minute, 0);
}

void RtcCalcLocalTimeOffset(s32 days, s32 hours, s32 minutes, s32 seconds)
{
    gLocalTime.days = days;
    gLocalTime.hours = hours;
    gLocalTime.minutes = minutes;
    gLocalTime.seconds = seconds;
    RtcGetInfo(&sRtc);
    RtcCalcTimeDifference(&sRtc, &gSaveBlockPtr->localTimeOffset, &gLocalTime);
}

void CalcTimeDifference(struct Time *result, struct Time *t1, struct Time *t2)
{
    result->seconds = t2->seconds - t1->seconds;
    result->minutes = t2->minutes - t1->minutes;
    result->hours = t2->hours - t1->hours;
    result->days = t2->days - t1->days;

    if (result->seconds < 0)
    {
        result->seconds += SEGUNDOS_POR_MINUTO;
        --result->minutes;
    }

    if (result->minutes < 0)
    {
        result->minutes += MINUTOS_POR_HORA;
        --result->hours;
    }

    if (result->hours < 0)
    {
        result->hours += HORAS_POR_DIA;
        --result->days;
    }
}

u32 RtcGetMinuteCount(void)
{
    RtcGetInfo(&sRtc);
    return (HORAS_POR_DIA * MINUTOS_POR_HORA) * sRtc.day + MINUTOS_POR_HORA * sRtc.hour + sRtc.minute;
}

void FormatDecimalTimeWithoutSeconds(u8 *txtPtr, s8 hour, s8 minute, bool32 is24Hour)
{
    if (is24Hour)
    {
        txtPtr = ConvertIntToDecimalStringN(txtPtr, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
        *txtPtr++ = CHAR_COLON;
        txtPtr = ConvertIntToDecimalStringN(txtPtr, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
    }
    else
    {
        if (hour == 0)
            txtPtr = ConvertIntToDecimalStringN(txtPtr, 12, STR_CONV_MODE_LEADING_ZEROS, 2);
        else if (hour < 13)
            txtPtr = ConvertIntToDecimalStringN(txtPtr, hour, STR_CONV_MODE_LEADING_ZEROS, 2);
        else
            txtPtr = ConvertIntToDecimalStringN(txtPtr, hour - 12, STR_CONV_MODE_LEADING_ZEROS, 2);

        *txtPtr++ = CHAR_COLON;
        txtPtr = ConvertIntToDecimalStringN(txtPtr, minute, STR_CONV_MODE_LEADING_ZEROS, 2);
        txtPtr = StringAppend(txtPtr, gText_Space);
        if (hour < 12)
            txtPtr = StringAppend(txtPtr, gText_AM);
        else
            txtPtr = StringAppend(txtPtr, gText_PM);
    }

    *txtPtr++ = EOS;
    *txtPtr = EOS;
}
