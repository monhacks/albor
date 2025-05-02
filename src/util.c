#include "global.h"
#include "util.h"
#include "sprite.h"
#include "palette.h"
#include "pokemon.h"
#include "constants/rgb.h"

static const struct SpriteTemplate sInvisibleSpriteTemplate =
{
    .tileTag = 0,
    .paletteTag = 0,
    .oam = &gDummyOamData,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const u8 gMiscBlank_Gfx[] = INCBIN_U8("graphics/interface/blank.4bpp");

u8 CreateInvisibleSpriteWithCallback(void (*callback)(struct Sprite *))
{
    u8 sprite = CreateSprite(&sInvisibleSpriteTemplate, DISPLAY_WIDTH + 8, DISPLAY_HEIGHT + 8, 14);
    gSprites[sprite].invisible = TRUE;
    gSprites[sprite].callback = callback;
    return sprite;
}

void StoreWordInTwoHalfwords(u16 *h, u32 w)
{
    h[0] = (u16)(w);
    h[1] = (u16)(w >> 16);
}

void LoadWordFromTwoHalfwords(u16 *h, u32 *w)
{
    *w = h[0] | (s16)h[1] << 16;
}

int CountTrailingZeroBits(u32 value)
{
    u8 i;

    for (i = 0; i < 32; i++)
    {
        if ((value & 1) == 0)
            value >>= 1;
        else
            return i;
    }
    return 0;
}

void BlendPalette(u16 palOffset, u16 numEntries, u8 coeff, u32 blendColor)
{
    u16 i;
    struct PlttData *data2 = (struct PlttData *)&blendColor;
    for (i = 0; i < numEntries; i++)
    {
        u16 index = i + palOffset;
        struct PlttData *data1 = (struct PlttData *)&gPlttBufferUnfaded[index];
        s8 r = data1->r;
        s8 g = data1->g;
        s8 b = data1->b;

        gPlttBufferFaded[index] = RGB(r + (((data2->r - r) * coeff) >> 4),
                                      g + (((data2->g - g) * coeff) >> 4),
                                      b + (((data2->b - b) * coeff) >> 4));
    }
}
#define CONSTANTE_PALETAS_UNICAS 30

// Macro para convertir de RGB5 (0-31) a RGB8 (0-255)
#define RGB5_TO_RGB8(c) ((c) * 255 / 31)

// Macro para convertir de RGB8 (0-255) a RGB5 (0-31)
#define RGB8_TO_RGB5(c) ((c) * 31 / 255)

// Macro para convertir de RGB a HSV (H en [0, 360], S y V en [0, 255])
#define RGB_TO_HSV(r, g, b, h, s, v) \
{ \
    u8 maxv = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b); \
    u8 minv = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b); \
    u8 delta = maxv - minv; \
    v = maxv; \
    s = (maxv == 0) ? 0 : (255 * delta / maxv); \
    if (delta == 0) h = 0; \
    else if (maxv == r) h = (43 * (g - b) / delta + 256) % 256; \
    else if (maxv == g) h = (43 * (b - r) / delta + 85) % 256; \
    else h = (43 * (r - g) / delta + 171) % 256; \
    h = (h * 360) / 256; \
}

// Macro para convertir de HSV a RGB
#define HSV_TO_RGB(h, s, v, r, g, b) \
{ \
    u8 region = h / 60; \
    u8 remainder = (h % 60) * 255 / 60; \
    u8 p = (v * (255 - s)) / 255; \
    u8 q = (v * (255 - (s * remainder) / 255)) / 255; \
    u8 t = (v * (255 - (s * (255 - remainder)) / 255)) / 255; \
    if (region == 0)      { r = v; g = t; b = p; } \
    else if (region == 1) { r = q; g = v; b = p; } \
    else if (region == 2) { r = p; g = v; b = t; } \
    else if (region == 3) { r = p; g = q; b = v; } \
    else if (region == 4) { r = t; g = p; b = v; } \
    else                  { r = v; g = p; b = q; } \
}

void UniquePalette(u16 palOffset, u32 personality)
{
    u32 i;
    s32 hueShift = (personality % (2 * CONSTANTE_PALETAS_UNICAS)) - CONSTANTE_PALETAS_UNICAS;

    for (i = 0; i < 16; i++)
    {
        u32 index = i + palOffset;
        struct PlttData *data = (struct PlttData *)&gPlttBufferUnfaded[index];
        
        u8 r = RGB5_TO_RGB8(data->r);
        u8 g = RGB5_TO_RGB8(data->g);
        u8 b = RGB5_TO_RGB8(data->b);
        
        u16 h, s, v;
        RGB_TO_HSV(r, g, b, h, s, v);

        // Aplicar el desplazamiento de tono
        h = (h + hueShift + 360) % 360;
        
        HSV_TO_RGB(h, s, v, r, g, b);
        
        data->r = RGB8_TO_RGB5(r);
        data->g = RGB8_TO_RGB5(g);
        data->b = RGB8_TO_RGB5(b);

        gPlttBufferFaded[index] = RGB(data->r, data->g, data->b);
    }
}

void UniquePaletteBuffered(u16 *buffer, u32 personality)
{
    u32 i;
    s32 hueShift = (personality % (2 * CONSTANTE_PALETAS_UNICAS)) - CONSTANTE_PALETAS_UNICAS;

    for (i = 0; i < 16; i++)
    {
        struct PlttData *data = (struct PlttData *)&buffer[i];
        
        u8 r = RGB5_TO_RGB8(data->r);
        u8 g = RGB5_TO_RGB8(data->g);
        u8 b = RGB5_TO_RGB8(data->b);
        
        u16 h, s, v;
        RGB_TO_HSV(r, g, b, h, s, v);
        
        h = (h + hueShift + 360) % 360;
        
        HSV_TO_RGB(h, s, v, r, g, b);
        
        data->r = RGB8_TO_RGB5(r);
        data->g = RGB8_TO_RGB5(g);
        data->b = RGB8_TO_RGB5(b);

        buffer[i] = RGB(data->r, data->g, data->b);
    }
}
