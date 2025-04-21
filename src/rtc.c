#include "global.h"
#include "rtc.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"

static struct SiiRtcInfo sRtc;
static u16 sSavedIme;

COMMON_DATA struct Tiempo gHoraJuego = {0};

static const s32 sDiasPorMes[NUMERO_MESES] =
{
    [ENERO] = 31,
    [FEBRERO] = 28,
    [MARZO] = 31,
    [ABRIL] = 30,
    [MAYO] = 31,
    [JUNIO] = 30,
    [JULIO] = 31,
    [AGOSTO] = 31,
    [SEPTIEMBRE] = 30,
    [OCTUBRE] = 31,
    [NOVIEMBRE] = 30,
    [DICIEMBRE] = 31,
};

bool32 EsAnioBisiesto(u32 anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
        return TRUE;

    return FALSE;
}

void QueFechaEs(struct SiiRtcInfo *rtc)
{
    struct Tiempo* tiempo = HoraActual();
    rtc->second = tiempo->segundos;
    rtc->minute = tiempo->minutos;
    rtc->hour = tiempo->horas;
    rtc->day = tiempo->dias;
}

void ReinicioTiempo(void)
{
    memset(HoraActual(), 0, sizeof(struct Tiempo));
    return;
}

void CalculaDiferenciaTiempo(struct SiiRtcInfo *rtc, struct Tiempo *resultado, struct Tiempo *t)
{
    u16 dias = rtc->day;
    resultado->segundos = rtc->second - t->segundos;
    resultado->minutos = rtc->minute - t->minutos;
    resultado->horas = rtc->hour - t->horas;
    resultado->dias = dias - t->dias;

    if (resultado->segundos < 0)
    {
        result->segundos += SEGUNDOS_POR_MINUTO;
        --result->minutos;
    }

    if (resultado->minutos < 0)
    {
        result->minutos += MINUTOS_POR_HORA;
        --result->horas;
    }

    if (resultado->horas < 0)
    {
        resultado->horas += HORAS_POR_DIA;
        --resultado->dias;
    }
}

void RtcCalcLocalTime(void)
{
    QueFechaEs(&sRtc);
    CalculaDiferenciaTiempo(&sRtc, &gHoraJuego, &gSaveBlockPtr->horaReferenciaJuego);
}

bool32 EsEntreHoras(s32 horas, s32 inicio, s32 fin)
{
    if (fin < inicio)
        return horas >= inicio || horas < fin;
    else
        return horas >= inicio && horas < fin;
}

u32 QueParteDeDiaEs(void)
{
    RtcCalcLocalTime();
    if (EsEntreHoras(gHoraJuego.hours, HORA_INICIO_MANANA, HORA_FINAL_MANANA))
        return TIEMPO_MANANA;
    else if (EsEntreHoras(gHoraJuego.hours, HORA_INICIO_TARDE, HORA_FINAL_TARDE))
        return TIEMPO_TARDE;
    else if (EsEntreHoras(gHoraJuego.hours, HORA_INICIO_NOCHE, HORA_FINAL_NOCHE))
        return TIEMPO_NOCHE;
    return TIEMPO_DIA;
}

void IniciaHoraReferenciaJuego(s32 horas, s32 minutos)
{
    CalculaHoraReferenciaJuego(0, horas, minutos, 0);
}

void CalculaHoraReferenciaJuego(s32 dias, s32 horas, s32 minutos, s32 segundos)
{
    gHoraJuego.days = dias;
    gHoraJuego.hours = horas;
    gHoraJuego.minutes = minutos;
    gHoraJuego.seconds = segundos;
    QueFechaEs(&sRtc);
    CalculaDiferenciaTiempo(&sRtc, &gSaveBlockPtr->horaReferenciaJuego, &gHoraJuego);
}

void ConvierteTiempoDecimalSinSegundos(u8 *txtPtr, s8 hour, s8 minute, bool32 is24Hour)
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
