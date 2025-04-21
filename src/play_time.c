#include "global.h"
#include "play_time.h"

void ContadorTiempoJuego_Reset(void)
{
    gSaveBlockPtr->playTimeHours = 0;
    gSaveBlockPtr->playTimeMinutes = 0;
    gSaveBlockPtr->playTimeSeconds = 0;
    gSaveBlockPtr->playTimeVBlanks = 0;
}

void ContadorTiempoJuego_Actualizar(void)
{
    gSaveBlockPtr->playTimeVBlanks++;

    if (gSaveBlockPtr->playTimeVBlanks < 60)
        return;

    gSaveBlockPtr->playTimeVBlanks = 0;
    gSaveBlockPtr->playTimeSeconds++;
    AvanzaSegundos();

    if (gSaveBlockPtr->playTimeSeconds < 60)
        return;

    gSaveBlockPtr->playTimeSeconds = 0;
    gSaveBlockPtr->playTimeMinutes++;

    if (gSaveBlockPtr->playTimeMinutes < 60)
        return;

    gSaveBlockPtr->playTimeMinutes = 0;
    gSaveBlockPtr->playTimeHours++;

    if (gSaveBlockPtr->playTimeHours > 999)
        ContadorTiempoJuego_PonerMaximo();
}

void ContadorTiempoJuego_PonerMaximo(void)
{
    gSaveBlockPtr->playTimeHours = 999;
    gSaveBlockPtr->playTimeMinutes = 59;
    gSaveBlockPtr->playTimeSeconds = 59;
    gSaveBlockPtr->playTimeVBlanks = 59;
}
