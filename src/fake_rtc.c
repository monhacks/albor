#include "global.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "rtc.h"
#include "event_data.h"

struct Tiempo *HoraActual(void)
{
    return &gSaveBlockPtr->horaActual;
}

void AvanzaSegundos(void)
{
    struct Tiempo* tiempo = HoraActual();
    u32 segundos = tiempo->seconds + FRAMES_POR_SEGUNDO;

    while (segundos >= SEGUNDOS_POR_MINUTO)
    {
        tiempo->minutes++;
        segundos -= SEGUNDOS_POR_MINUTO;
    }

    while (tiempo->minutes >= MINUTOS_POR_HORA)
    {
        tiempo->hours++;
        tiempo->minutes -= MINUTOS_POR_HORA;
    }

    while (tiempo->hours >= HORAS_POR_DIA)
    {
        tiempo->days++;
        tiempo->hours -= HORAS_POR_DIA;
    }

    tiempo->seconds = segundos;
}
