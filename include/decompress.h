#ifndef GUARD_DECOMPRESS_H
#define GUARD_DECOMPRESS_H

#include "sprite.h"

#define MAX_DECOMPRESSION_BUFFER_SIZE 16384

void LZDecompressWram(const u32 *src, void *dest);
void LZDecompressVram(const u32 *src, void *dest);

u32 IsLZ77Data(const void *ptr, u32 minSize, u32 maxSize);

u32 LoadCompressedSpriteSheet(const struct CompressedSpriteSheet *src);
u32 LoadCompressedSpriteSheetOverrideBuffer(const struct CompressedSpriteSheet *src, void *buffer);
bool32 LoadCompressedSpriteSheetUsingHeap(const struct CompressedSpriteSheet *src);

u32 LoadCompressedSpritePalette(const struct CompressedSpritePalette *src);
u32 LoadCompressedSpritePaletteWithTag(const u32 *pal, u16 tag);
u32 LoadCompressedSpritePaletteWithTagHueShifted(const u32 *pal, u16 tag, u32 personality);
u32 LoadCompressedSpritePaletteOverrideBuffer(const struct CompressedSpritePalette *src, void *buffer);
bool32 LoadCompressedSpritePaletteUsingHeap(const struct CompressedSpritePalette *src);
u32 LoadCompressedEggSpritePalette(const struct CompressedSpritePalette *src1, const struct CompressedSpritePalette *src2);
u32 LoadCompressedEggHatchSpritePalette(const struct CompressedSpritePalette *src1, const struct CompressedSpritePalette *src2);

void DecompressPicFromTable(const struct CompressedSpriteSheet *src, void *buffer);

void HandleLoadSpecialPokePic(bool32 isFrontPic, void *dest, s32 species, u32 personality);

void LoadSpecialPokePic(void *dest, s32 species, u32 personality, bool8 isFrontPic);

u32 GetDecompressedDataSize(const u32 *ptr);

#endif // GUARD_DECOMPRESS_H
