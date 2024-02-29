- Implementar repartir experiencia/buscapelea como opciones de menú.
- Implementar animación de subir de nivel no usada.
- Arreglar formas/evos +3 en Pokédex.

static void SetTypeIconPosAndPal(u8 typeId, u8 x, u8 y, u8 spriteArrayId)
{
    struct Sprite *sprite;

    sprite = &gSprites[gTypeIconSpriteId[spriteArrayId]];
    StartSpriteAnim(sprite, typeId);
    sprite->oam.paletteNum = sMoveTypeToOamPaletteNum[typeId];
    sprite->oam.priority = 0;
    sprite->x = x + 16;
    sprite->y = y + 8;
}

static void MoveSelectionDisplayMoveType(u32 battler)
{
    s32 i;
    struct ChooseMoveStruct *moveInfo = (struct ChooseMoveStruct *)(&gBattleResources->bufferA[battler][4]);
    u8 type1, type2, type3, type4;

    LoadCompressedSpriteSheet(&gSpriteSheet_BattleTypes);
    LoadCompressedPalette(gMoveTypes_Pal, OBJ_PLTT_ID(14), 2 * PLTT_SIZE_4BPP);

    type1 = gMovesInfo[moveInfo->moves[0]].type;
    type2 = gMovesInfo[moveInfo->moves[1]].type;
    type3 = gMovesInfo[moveInfo->moves[2]].type;
    type4 = gMovesInfo[moveInfo->moves[3]].type;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moveInfo->moves[i] != MOVE_NONE)
        {
            if (gTypeIconSpriteId[i] == 0xFF)
                gTypeIconSpriteId[i] = CreateSprite(&gSpriteTemplate_BattleTypes, 10, 10, 2);

            SetTypeIconPosAndPal(type1, 147, 47, 0);
            SetTypeIconPosAndPal(type2, 147 + 11, 47, 1);
            SetTypeIconPosAndPal(type3, 147 + 22, 47, 2);
            SetTypeIconPosAndPal(type4, 147 + 33, 47, 3);
        }
    }
}
