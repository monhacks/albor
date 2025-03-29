#include "global.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "rtc.h"
#include "event_data.h"

struct Time *HoraActual(void)
{
    return &gSaveBlockPtr->fakeRTC;
}

void FakeRtc_GetRawInfo(struct SiiRtcInfo *rtc)
{
    struct Time* time = HoraActual();
    rtc->second = time->seconds;
    rtc->minute = time->minutes;
    rtc->hour = time->hours;
    rtc->day = time->days;
}

void FakeRtc_TickTimeForward(void)
{
    FakeRtc_AdvanceTimeBy(0, 0, FakeRtc_GetSecondsRatio());
}

void FakeRtc_AdvanceTimeBy(u32 hours, u32 minutes, u32 seconds)
{
    struct Time* time = HoraActual();
    seconds += time->seconds;
    minutes += time->minutes;
    hours += time->hours;

    while(seconds >= SEGUNDOS_POR_MINUTO)
    {
        minutes++;
        seconds -= SEGUNDOS_POR_MINUTO;
    }

    while(minutes >= MINUTOS_POR_HORA)
    {
        hours++;
        minutes -= MINUTOS_POR_HORA;
    }

    while(hours >= HORAS_POR_DIA)
    {
        time->days++;
        hours -= HORAS_POR_DIA;
    }

    time->seconds = seconds;
    time->minutes = minutes;
    time->hours = hours;
}

u32 FakeRtc_GetSecondsRatio(void)
{
    return 20;
}
