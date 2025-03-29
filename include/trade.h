#ifndef GUARD_TRADE_H
#define GUARD_TRADE_H

#include "constants/trade.h"

extern struct Mail gTradeMail[PARTY_SIZE];
extern u8 gSelectedTradeMonPositions[2];

extern const struct WindowTemplate gTradeEvolutionSceneYesNoWindowTemplate;

s32 GetGameProgressForLinkTrade(void);
void CB2_StartCreateTradeMenu(void);
void CB2_LinkTrade(void);
void InitTradeSequenceBgGpuRegs(void);
void LinkTradeDrawWindow(void);
void LoadTradeAnimGfx(void);
void DrawTextOnTradeWindow(u8, const u8 *, u8);

#endif //GUARD_TRADE_H
