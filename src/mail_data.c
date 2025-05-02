#include "global.h"
#include "mail.h"
#include "constants/items.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "text.h"
#include "international_string_util.h"

#define UNOWN_OFFSET 30000

void ClearAllMail(void)
{
    u8 i;

    for (i = 0; i < MAIL_COUNT; i++)
        ClearMail(&gSaveBlockPtr->mail[i]);
}

void ClearMail(struct Mail *mail)
{
    s32 i;

    for (i = 0; i < MAIL_WORDS_COUNT; i++)
        mail->words[i] = EC_EMPTY_WORD;

    for (i = 0; i < PLAYER_NAME_LENGTH + 1; i++)
        mail->playerName[i] = EOS;

    for (i = 0; i < TRAINER_ID_LENGTH; i++)
        mail->trainerId[i] = 0;

    mail->species = SPECIES_BULBASAUR;
    mail->itemId = ITEM_NONE;
}

bool8 MonHasMail(struct Pokemon *mon)
{
    return FALSE;
}

u8 GiveMailToMonByItemId(struct Pokemon *mon, u16 itemId)
{
    return 0;
}

u16 SpeciesToMailSpecies(u16 species, u32 personality)
{
    return species;
}

u16 MailSpeciesToSpecies(u16 mailSpecies, u16 *buffer)
{
    return 0;
}

u8 GiveMailToMon(struct Pokemon *mon, struct Mail *mail)
{
    return 0;
}

void TakeMailFromMon(struct Pokemon *mon)
{

}

void ClearMailItemId(u8 mailId)
{
    gSaveBlockPtr->mail[mailId].itemId = ITEM_NONE;
}

u8 TakeMailFromMonAndSave(struct Pokemon *mon)
{
    return MAIL_NONE;
}

bool8 ItemIsMail(u16 itemId)
{
    return FALSE;
}
