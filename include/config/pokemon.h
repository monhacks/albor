#ifndef GUARD_CONFIG_POKEMON_H
#define GUARD_CONFIG_POKEMON_H

// Evolution settings
#define P_FRIENDSHIP_EVO_THRESHOLD   GEN_LATEST  // Since Gen 8, Pokémon that evolve by friendship evolve at or above 160 friendship instead of 220.

// Breeding settings
#define P_NIDORAN_M_DITTO_BREED         GEN_LATEST  // Since Gen 5, when Nidoran♂ breeds with Ditto it can produce Nidoran♀ offspring. Before, it would only yield male offspring. This change also applies to Volbeat.
#define P_EGG_HATCH_LEVEL               GEN_LATEST  // Since Gen 4, Pokémon will hatch from eggs at level 1 instead of 5.
#define P_BALL_INHERITING               GEN_LATEST  // Since Gen 6, Eggs from the Daycare will inherit the Poké Ball from their mother. From Gen 7 onwards, the father can pass it down as well, as long as it's of the same species as the mother.
#define P_TM_INHERITANCE                GEN_LATEST  // Since Gen 6, the father no longer passes down TMs to the baby.
#define P_MOTHER_EGG_MOVE_INHERITANCE   GEN_LATEST  // Since Gen 6, the mother can also pass down Egg Moves.
#define P_NATURE_INHERITANCE            GEN_LATEST  // In Gen 3, Everstone grants Ditto and mothers a 50% chance to pass on Nature. Since Gen 4, anyone can pass on nature. Since Gen 5, the chance is 100%.
#define P_ABILITY_INHERITANCE           GEN_LATEST  // In B2W2, a female Pokémon has an 80% chance of passing down their ability if bred with a male. Since Gen 6, the chance is 80% for normal ability and 60% for Hidden Ability, and anyone can pass down their abilities if bred with Ditto. NOTE: BW's effect: 60% chance to pass down HA and random for normal ability has been omitted.
#define P_EGG_MOVE_TRANSFER             GEN_8       // Starting in Gen 8, if two Pokémon of the same species are together in the Daycare, one knows an Egg Move, and the other has an empty slot, the other Pokémon will receive the Egg Move in the empty slot. In Gen 9, if a Pokémon holds a Mirror Herb, it will receive Egg Moves from the other regardless of species.

// Species-specific settings
#define P_SHEDINJA_BALL             GEN_LATEST  // Since Gen 4, Shedinja requires a Poké Ball for its evolution. In Gen 3, Shedinja inherits Nincada's Ball.

// Other settings
#define P_LEGENDARY_PERFECT_IVS          GEN_LATEST  // Since Gen 6, Legendaries, Mythicals and Ultra Beasts found in the wild or given through gifts have at least 3 perfect IVs.
#define P_EV_CAP                         GEN_LATEST  // Since Gen 6, the max EVs per stat is 252 instead of 255.
#define P_TM_LITERACY                    GEN_LATEST  // Since Gen 6, TM illiterate Pokémon can learn TMs that teach moves that are in their level-up learnsets.
#define P_CAN_FORGET_HIDDEN_MOVE         FALSE       // If TRUE, Pokémon can forget any move, even if it is a Hidden Move.
#define P_ONLY_OBTAINABLE_SHINIES        FALSE       // If TRUE, Pokémon encountered in the Battle Pyramid won't be shiny.
#define P_NO_SHINIES_WITHOUT_POKEBALLS   FALSE       // If TRUE, Pokémon encountered when the player is out of Poké Balls won't be shiny
#define P_SHOW_DYNAMIC_TYPES             FALSE       // If TRUE, moves with dynamic type changes will be reflected as their current type in battle/summary screens.
#define P_SUMMARY_SCREEN_MOVE_RELEARNER  TRUE        // If TRUE, shows an option for Pokémon to relearn moves on the summary screen moves page.
#define P_SUMMARY_MOVE_RELEARNER_FULL_PP TRUE        // If TRUE, the move relearner in the summary screen restores relearned moves' PP to full.
#define P_SUMMARY_SCREEN_RENAME          TRUE        // If TRUE, an option to change Pokémon nicknames replaces the cancel prompt on the summary screen info page.

// Flag settings
// To use the following features in scripting, replace the 0s with the flag ID you're assigning it to.
// Eg: Replace with FLAG_UNUSED_0x264 so you can use that flag to toggle the feature.
#define P_FLAG_FORCE_SHINY      0     // If this flag is set, all wild and gift Pokémon will forced into being Shiny.
#define P_FLAG_FORCE_NO_SHINY   0     // If this flag is set, all wild and gift Pokémon will forced into NOT being Shiny.

#endif // GUARD_CONFIG_POKEMON_H
