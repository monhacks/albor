#ifndef GUARD_CONSTANTS_FIELD_WEATHER_H
#define GUARD_CONSTANTS_FIELD_WEATHER_H

// Controls how the weather should be changing the screen palettes.
enum WeatherPalStates
{
    WEATHER_PAL_STATE_CHANGING_WEATHER,
    WEATHER_PAL_STATE_SCREEN_FADING_IN,
    WEATHER_PAL_STATE_SCREEN_FADING_OUT,
    WEATHER_PAL_STATE_IDLE,
};

enum ModesFadeScreen
{
    FADE_FROM_BLACK,
    FADE_TO_BLACK,
    FADE_FROM_WHITE,
    FADE_TO_WHITE,
};

#define MAX_RAIN_SPRITES             24
#define NUM_CLOUD_SPRITES            3
#define NUM_FOG_HORIZONTAL_SPRITES   20
#define NUM_ASH_SPRITES              20
#define NUM_FOG_DIAGONAL_SPRITES     20
#define NUM_SANDSTORM_SPRITES        20
#define NUM_SWIRL_SANDSTORM_SPRITES  5
#define NUM_SNOWFLAKE_SPRITES        16

// Within the weather palette, shadow sprites' color index
#define SHADOW_COLOR_INDEX 9

#endif // GUARD_CONSTANTS_FIELD_WEATHER_H
