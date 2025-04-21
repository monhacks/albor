#ifndef GUARD_FAKE_RTC_UTIL_H
#define GUARD_FAKE_RTC_UTIL_H

struct Tiempo* HoraActual(void);
void QueFechaEs(struct SiiRtcInfo *rtc);
void AvanzaSegundos(void);

#endif // GUARD_FAKE_RTC_UTIL_H
