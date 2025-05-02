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

static void ActualizaPorDia(struct Tiempo *horaJuego);
static void ActualizaPorMinuto(struct Tiempo *horaJuego);

void IniciaEventosTemporales(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlockPtr->ultimaActualizacionBaya = gHoraJuego;
}

void HaceEventosTemporales(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET) && !InPokemonCenter())
    {
        RtcCalcLocalTime();
        ActualizaPorDia(&gHoraJuego);
        ActualizaPorMinuto(&gHoraJuego);
    }
}

static void ActualizaPorDia(struct Tiempo *horaJuego)
{
    u16 *dias = gHoraJuego.days;
    u16 diasDesde;

    if (*dias != horaJuego->dias && *dias <= horaJuego->dias)
    {
        diasDesde = horaJuego->dias - *dias;
        LimpiaFlagsDiarias();
        UpdateWeatherPerDay(diasDesde);
        SetRandomLotteryNumber(diasDesde);
        *dias = horaJuego->dias;
    }
}

static void ActualizaPorMinuto(struct Tiempo *horaJuego)
{
    struct Tiempo diferencia;
    int minutos;

    CalculaDiferenciaTiempo(horaJuego, &diferencia, &gSaveBlockPtr->ultimaActualizacionBaya);

    minutos = HORAS_POR_DIA * MINUTOS_POR_HORA * diferencia.dias
            + MINUTOS_POR_HORA * diferencia.horas
            + diferencia.minutos;

    if (minutos > 0)
    {
        BerryTreeTimeUpdate(minutos);
        gSaveBlockPtr->ultimaActualizacionBaya = *horaJuego;
    }
}

static void ReturnFromStartWallClock(void)
{
    IniciaEventosTemporales();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void StartWallClock(void)
{
    SetMainCallback2(CB2_StartWallClock);
    gMain.savedCallback = ReturnFromStartWallClock;
}
