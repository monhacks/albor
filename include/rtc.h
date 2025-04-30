#ifndef GUARD_RTC_UTIL_H
#define GUARD_RTC_UTIL_H

enum DiasSemana
{
    LUNES,
    MARTES,
    MIERCOLES,
    JUEVES,
    VIERNES,
    SABADO,
    DOMINGO,

    DIAS_SEMANA
};

enum Meses
{
    ENERO,
    FEBRERO,
    MARZO,
    ABRIL,
    MAYO,
    JUNIO,
    JULIO,
    AGOSTO,
    SEPTIEMBRE,
    OCTUBRE,
    NOVIEMBRE,
    DICIEMBRE,
    NUMERO_MESES
};

enum TiemposDia
{
    TIEMPO_MANANA,
    TIEMPO_DIA,
    TIEMPO_TARDE,
    TIEMPO_NOCHE,

    NUMERO_TIEMPOS_DIA
};

enum Estaciones
{
    PRIMAVERA,
    VERANO,
    OTONO,
    INVIERNO,

    NUMERO_ESTACIONES
}
#define HORAS_POR_DIA               24
#define MINUTOS_POR_HORA            60
#define SEGUNDOS_POR_MINUTO         60
#define FRAMES_POR_SEGUNDO          20

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

extern struct Tiempo gHoraJuego;

struct Tiempo *HoraActual(void);
void AvanzaSegundos(void);
bool32 EsAnioBisiesto(u32 anio);
void ReinicioTiempo(void);
void CalculaDiferenciaTiempo(struct SiiRtcInfo *rtc, struct Tiempo *result, struct Tiempo *t);
void RtcCalcLocalTime(void);
bool32 EsEntreHoras(s32 horas, s32 inicio, s32 fin);
u32 QueParteDeDiaEs(void);
void IniciaHoraReferenciaJuego(s32 horas, s32 minutos);
void CalculaHoraReferenciaJuego(s32 dias, s32 horas, s32 minutos, s32 segundos);
void ConvierteTiempoDecimalSinSegundos(u8 *dest, s8 hour, s8 minute, bool32 is24Hour);

#endif // GUARD_RTC_UTIL_H
