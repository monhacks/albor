#include "global.h"
#include "event_data.h"
#include "rtc.h"
#include "time_events.h"
#include "field_specials.h"
#include "lottery_corner.h"
#include "field_weather.h"
#include "berry.h"
#include "main.h"
#include "overworld.h"
#include "wallclock.h"

static void UpdatePerDay(struct Tiempo *localTime);
static void ActualizaPorMinuto(struct Tiempo *localTime);

void InitTimeBasedEvents(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlockPtr->lastBerryTreeUpdate = gHoraJuego;
    VarSet(VAR_DAYS, gHoraJuego.days);
}

void DoTimeBasedEvents(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET) && !InPokemonCenter())
    {
        RtcCalcLocalTime();
        UpdatePerDay(&gHoraJuego);
        ActualizaPorMinuto(&gHoraJuego);
    }
}

static void UpdatePerDay(struct Tiempo *localTime)
{
    u16 *days = GetVarPointer(VAR_DAYS);
    u16 daysSince;

    if (*days != localTime->days && *days <= localTime->days)
    {
        daysSince = localTime->days - *days;
        ClearDailyFlags();
        UpdateWeatherPerDay(daysSince);
        SetRandomLotteryNumber(daysSince);
        *days = localTime->days;
    }
}

static void ActualizaPorMinuto(struct Tiempo *localTime)
{
    struct Tiempo difference;
    int minutes;
    struct SiiRtcInfo currentRtc;

    currentRtc.day = localTime->days;
    currentRtc.hour = localTime->hours;
    currentRtc.minute = localTime->minutes;
    currentRtc.second = localTime->seconds;

    CalculaDiferenciaTiempo(&currentRtc, &difference, &gSaveBlockPtr->lastBerryTreeUpdate);

    minutes = HORAS_POR_DIA * MINUTOS_POR_HORA * difference.days + SEGUNDOS_POR_MINUTO * difference.hours + difference.minutes;

    if (minutes > 0)
    {
        BerryTreeTimeUpdate(minutes);
        gSaveBlockPtr->lastBerryTreeUpdate = *localTime;
    }
}

static void ReturnFromStartWallClock(void)
{
    InitTimeBasedEvents();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void StartWallClock(void)
{
    SetMainCallback2(CB2_StartWallClock);
    gMain.savedCallback = ReturnFromStartWallClock;
}
