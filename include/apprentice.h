#ifndef GUARD_APPRENTICE_H
#define GUARD_APPRENTICE_H

#include "constants/apprentice.h"

void BufferApprenticeChallengeText(u8 saveApprenticeId);
void Apprentice_ScriptContext_Enable(void);
void ResetApprenticeStruct(struct Apprentice *apprentice);
void ResetAllApprenticeData(void);
void CallApprenticeFunction(void);
const u8 *GetApprenticeNameInLanguage(u32 apprenticeId, s32 language);

#endif // GUARD_APPRENTICE_H
