#ifndef GUARD_GLOBAL_BERRY_H
#define GUARD_GLOBAL_BERRY_H

#define BERRY_NAME_LENGTH 6
#define BERRY_ITEM_EFFECT_COUNT 18

//Limpiar
struct Berry
{
    const u8 name[BERRY_NAME_LENGTH + 1];
    u8 firmness:4;
    u8 color:4;
    u16 size:10;
    u16 weedsBonus:3;
    u16 pestsBonus:3;
    u8 maxYield;
    u8 minYield:4;
    u8 waterBonus:4;
    const u8 *description1;
    const u8 *description2;
    u8 growthDuration;
    u8 spicy;
    u8 dry;
    u8 sweet;
    u8 bitter;
    u8 sour;
    u8 smoothness;
    u8 drainRate;
};

struct BerryTree
{
    u8 berry:7;
    u8 weeds:1;
    u8 stage:3;
    u8 mulch:4;
    u8 stopGrowth:1;
    u16 minutesUntilNextStage:14;
    u16 mutationA:2;
    u8 berryYield:5;
    u8 pests:1;
    u8 mutationB:2;
    u8 regrowthCount:4;
    u8 watered:4; // Used to keep track of bonuses in case of gradient watering
    u16 moistureLevel:7;
    u16 moistureClock:7;
    u16 padding:2;
};

#endif // GUARD_GLOBAL_BERRY_H
