#include "global.h"
#include "new_game.h"
#include "random.h"
#include "pokemon.h"
#include "roamer.h"
#include "pokemon_size_record.h"
#include "script.h"
#include "lottery_corner.h"
#include "mauville_old_man.h"
#include "match_call.h"
#include "lilycove_lady.h"
#include "load_save.h"
#include "pokeblock.h"
#include "dewford_trend.h"
#include "berry.h"
#include "rtc.h"
#include "easy_chat.h"
#include "event_data.h"
#include "money.h"
#include "trainer_hill.h"
#include "coins.h"
#include "text.h"
#include "overworld.h"
#include "mail.h"
#include "battle_records.h"
#include "item.h"
#include "pokedex.h"
#include "frontier_util.h"
#include "pokedex.h"
#include "save.h"
#include "main.h"
#include "contest.h"
#include "item_menu.h"
#include "pokemon_storage_system.h"
#include "decoration_inventory.h"
#include "secret_base.h"
#include "field_specials.h"
#include "constants/items.h"

extern const u8 EventScript_ResetAllMapFlags[];

static void WarpToTruck(void);
static void ResetItemFlags(void);

EWRAM_DATA bool8 gDiferentePartidaGuardada = FALSE;

void SetTrainerId(u32 trainerId, u8 *dst)
{
    dst[0] = trainerId;
    dst[1] = trainerId >> 8;
    dst[2] = trainerId >> 16;
    dst[3] = trainerId >> 24;
}

static void InitPlayerTrainerId(void)
{
    u32 trainerId = (Random() << 16) | sTrainerId;
    SetTrainerId(trainerId, gSaveBlockPtr->playerTrainerId);
}

// L=A isnt set here for some reason.
void SetDefaultOptions(void)
{
    gSaveBlockPtr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    gSaveBlockPtr->optionsWindowFrameType = 0;
    gSaveBlockPtr->optionsSound = OPTIONS_SOUND_STEREO;
    gSaveBlockPtr->optionsBattleSceneOff = FALSE;
    gSaveBlockPtr->regionMapZoom = FALSE;
}

static void ClearPokedexFlags(void)
{
    memset(&gSaveBlockPtr->dexCaught, 0, sizeof(gSaveBlockPtr->dexCaught));
    memset(&gSaveBlockPtr->dexSeen, 0, sizeof(gSaveBlockPtr->dexSeen));
}

void ClearAllContestWinnerPics(void)
{

}

static void WarpToTruck(void)
{
    SetWarpDestination(MAP_GROUP(TEST), MAP_NUM(TEST), WARP_ID_NONE, -1, -1);
    WarpIntoMap();
}

void ResetMenuAndMonGlobals(void)
{
    gDiferentePartidaGuardada = FALSE;
    ResetPokedexScrollPositions();
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetBagScrollPositions();
}

void NewGameInitData(void)
{
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        ReinicioTiempo();

    gDiferentePartidaGuardada = TRUE;
    ZeroPlayerPartyMons();
    ZeroEnemyPartyMons();
    ResetPokedex();
    gSaveBlockPtr->specialSaveWarpFlags = 0;
    InitPlayerTrainerId();
    ContadorTiempoJuego_Reset();
    ClearPokedexFlags();
    InitEventData();
    ClearBerryTrees();
    SetMoney(&gSaveBlockPtr->money, 3000);
    SetCoins(0);
    ResetGameStats();
    gPlayerPartyCount = 0;
    ZeroPlayerPartyMons();
    ResetPokemonStorageSystem();
    gSaveBlockPtr->registeredItem = ITEM_NONE;
    ClearBag();
    WarpToTruck();
    RunScriptImmediately(EventScript_ResetAllMapFlags);
    ResetItemFlags();
}

static void ResetItemFlags(void)
{
#if OW_SHOW_ITEM_DESCRIPTIONS == OW_ITEM_DESCRIPTIONS_FIRST_TIME
    memset(&gSaveBlockPtr->itemFlags, 0, sizeof(gSaveBlockPtr->itemFlags));
#endif
}
