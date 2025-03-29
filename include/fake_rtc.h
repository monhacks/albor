#ifndef GUARD_FAKE_RTC_UTIL_H
#define GUARD_FAKE_RTC_UTIL_H

#include "siirtc.h"

struct Time* HoraActual(void);
void FakeRtc_GetRawInfo(struct SiiRtcInfo *rtc);
void FakeRtc_AdvanceTimeBy(u32 hours, u32 minutes, u32 seconds);
void FakeRtc_TickTimeForward(void);
u32 FakeRtc_GetSecondsRatio(void);

#endif // GUARD_FAKE_RTC_UTIL_H
