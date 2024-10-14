#ifndef GUARD_CONFIG_SPECIES_ENABLED_H
#define GUARD_CONFIG_SPECIES_ENABLED_H

// WARNING: For some reason, using 1/0 instead of TRUE/FALSE causes cry IDs to be shifted.
// Please use TRUE/FALSE when using the family toggles.

// Modifying the latest generation WILL change the saveblock due to Dex flags and will require a new save file.
// Generations of Pokémon are defined by the first member introduced,
// so Pikachu depends on the Gen 1 setting despite Pichu being the lowest member of the evolution tree.
// Eg: If P_GEN_2_POKEMON is set to FALSE, all members of the Sneasel Family will be disabled
// (Sneasel + Hisuian, Weavile and Sneasler).
#define P_GEN_2_POKEMON                  TRUE // Generation 2 Pokémon (GSC)
#define P_GEN_3_POKEMON                  TRUE // Generation 3 Pokémon (RSE, FRLG)
#define P_GEN_4_POKEMON                  FALSE // Generation 4 Pokémon (DPPt, HGSS)
#define P_GEN_5_POKEMON                  FALSE // Generation 5 Pokémon (BW, B2W2)
#define P_GEN_6_POKEMON                  FALSE // Generation 6 Pokémon (XY, ORAS)
#define P_GEN_7_POKEMON                  FALSE // Generation 7 Pokémon (SM, USUM, LGPE)
#define P_GEN_8_POKEMON                  FALSE // Generation 8 Pokémon (SwSh, BDSP, LA)
#define P_GEN_9_POKEMON                  FALSE // Generation 9 Pokémon (SV)

// Regional Forms. Includes Regional Form evolutions, like Sirfetch'd.
#define P_REGIONAL_FORMS                 TRUE
#define P_HISUIAN_FORMS                  P_REGIONAL_FORMS

#define P_FAMILY_WOOPER                  P_GEN_2_POKEMON //H-Wooper + Clodsire
#define P_FAMILY_MISDREAVUS              P_GEN_2_POKEMON
#define P_FAMILY_GIRAFARIG               P_GEN_2_POKEMON
#define P_FAMILY_PINECO                  P_GEN_2_POKEMON
#define P_FAMILY_GLIGAR                  P_GEN_2_POKEMON
#define P_FAMILY_SNUBBULL                P_GEN_2_POKEMON
#define P_FAMILY_HERACROSS               P_GEN_2_POKEMON
#define P_FAMILY_SNEASEL                 P_GEN_2_POKEMON
#define P_FAMILY_TEDDIURSA               P_GEN_2_POKEMON
#define P_FAMILY_SLUGMA                  P_GEN_2_POKEMON
#define P_FAMILY_SWINUB                  P_GEN_2_POKEMON
#define P_FAMILY_CORSOLA                 P_GEN_2_POKEMON
#define P_FAMILY_REMORAID                P_GEN_2_POKEMON
#define P_FAMILY_DELIBIRD                P_GEN_2_POKEMON
#define P_FAMILY_HOUNDOUR                P_GEN_2_POKEMON
#define P_FAMILY_PHANPY                  P_GEN_2_POKEMON
#define P_FAMILY_STANTLER                P_GEN_2_POKEMON
#define P_FAMILY_MILTANK                 P_GEN_2_POKEMON
#define P_FAMILY_RAIKOU                  P_GEN_2_POKEMON
#define P_FAMILY_ENTEI                   P_GEN_2_POKEMON
#define P_FAMILY_SUICUNE                 P_GEN_2_POKEMON
#define P_FAMILY_LARVITAR                P_GEN_2_POKEMON
#define P_FAMILY_LUGIA                   P_GEN_2_POKEMON
#define P_FAMILY_HO_OH                   P_GEN_2_POKEMON
#define P_FAMILY_CELEBI                  P_GEN_2_POKEMON

#define P_FAMILY_TREECKO                 P_GEN_3_POKEMON
#define P_FAMILY_TORCHIC                 P_GEN_3_POKEMON
#define P_FAMILY_MUDKIP                  P_GEN_3_POKEMON
#define P_FAMILY_POOCHYENA               P_GEN_3_POKEMON
#define P_FAMILY_ZIGZAGOON               P_GEN_3_POKEMON
#define P_FAMILY_WURMPLE                 P_GEN_3_POKEMON
#define P_FAMILY_LOTAD                   P_GEN_3_POKEMON
#define P_FAMILY_SEEDOT                  P_GEN_3_POKEMON
#define P_FAMILY_TAILLOW                 P_GEN_3_POKEMON
#define P_FAMILY_WINGULL                 P_GEN_3_POKEMON
#define P_FAMILY_RALTS                   P_GEN_3_POKEMON
#define P_FAMILY_SURSKIT                 P_GEN_3_POKEMON
#define P_FAMILY_SHROOMISH               P_GEN_3_POKEMON
#define P_FAMILY_SLAKOTH                 P_GEN_3_POKEMON
#define P_FAMILY_NINCADA                 P_GEN_3_POKEMON
#define P_FAMILY_WHISMUR                 P_GEN_3_POKEMON
#define P_FAMILY_MAKUHITA                P_GEN_3_POKEMON
#define P_FAMILY_NOSEPASS                P_GEN_3_POKEMON
#define P_FAMILY_SKITTY                  FALSE
#define P_FAMILY_SABLEYE                 P_GEN_3_POKEMON
#define P_FAMILY_MAWILE                  P_GEN_3_POKEMON
#define P_FAMILY_ARON                    P_GEN_3_POKEMON
#define P_FAMILY_MEDITITE                P_GEN_3_POKEMON
#define P_FAMILY_ELECTRIKE               P_GEN_3_POKEMON
#define P_FAMILY_PLUSLE                  FALSE
#define P_FAMILY_MINUN                   FALSE
#define P_FAMILY_VOLBEAT_ILLUMISE        FALSE
#define P_FAMILY_ROSELIA                 P_GEN_3_POKEMON
#define P_FAMILY_GULPIN                  FALSE
#define P_FAMILY_CARVANHA                P_GEN_3_POKEMON
#define P_FAMILY_WAILMER                 P_GEN_3_POKEMON
#define P_FAMILY_NUMEL                   P_GEN_3_POKEMON
#define P_FAMILY_TORKOAL                 P_GEN_3_POKEMON
#define P_FAMILY_SPOINK                  FALSE
#define P_FAMILY_SPINDA                  FALSE
#define P_FAMILY_TRAPINCH                P_GEN_3_POKEMON
#define P_FAMILY_CACNEA                  P_GEN_3_POKEMON
#define P_FAMILY_SWABLU                  P_GEN_3_POKEMON
#define P_FAMILY_ZANGOOSE                FALSE
#define P_FAMILY_SEVIPER                 FALSE
#define P_FAMILY_LUNATONE_SOLROCK        P_GEN_3_POKEMON
#define P_FAMILY_BARBOACH                FALSE
#define P_FAMILY_CORPHISH                FALSE
#define P_FAMILY_BALTOY                  P_GEN_3_POKEMON
#define P_FAMILY_LILEEP                  P_GEN_3_POKEMON
#define P_FAMILY_ANORITH                 P_GEN_3_POKEMON
#define P_FAMILY_FEEBAS                  P_GEN_3_POKEMON
#define P_FAMILY_CASTFORM                P_GEN_3_POKEMON
#define P_FAMILY_KECLEON                 P_GEN_3_POKEMON
#define P_FAMILY_SHUPPET                 P_GEN_3_POKEMON
#define P_FAMILY_DUSKULL                 P_GEN_3_POKEMON
#define P_FAMILY_TROPIUS                 P_GEN_3_POKEMON
#define P_FAMILY_CHIMECHO                P_GEN_3_POKEMON
#define P_FAMILY_ABSOL                   P_GEN_3_POKEMON
#define P_FAMILY_SNORUNT                 P_GEN_3_POKEMON
#define P_FAMILY_SPHEAL                  P_GEN_3_POKEMON
#define P_FAMILY_CLAMPERL                P_GEN_3_POKEMON
#define P_FAMILY_RELICANTH               P_GEN_3_POKEMON
#define P_FAMILY_LUVDISC                 P_GEN_3_POKEMON
#define P_FAMILY_BAGON                   P_GEN_3_POKEMON
#define P_FAMILY_BELDUM                  P_GEN_3_POKEMON
#define P_FAMILY_REGIROCK                P_GEN_3_POKEMON
#define P_FAMILY_REGICE                  P_GEN_3_POKEMON
#define P_FAMILY_REGISTEEL               P_GEN_3_POKEMON
#define P_FAMILY_LATIAS                  P_GEN_3_POKEMON
#define P_FAMILY_LATIOS                  P_GEN_3_POKEMON
#define P_FAMILY_KYOGRE                  P_GEN_3_POKEMON
#define P_FAMILY_GROUDON                 P_GEN_3_POKEMON
#define P_FAMILY_RAYQUAZA                P_GEN_3_POKEMON
#define P_FAMILY_JIRACHI                 P_GEN_3_POKEMON
#define P_FAMILY_DEOXYS                  P_GEN_3_POKEMON

#define P_FAMILY_TURTWIG                 P_GEN_4_POKEMON
#define P_FAMILY_CHIMCHAR                P_GEN_4_POKEMON
#define P_FAMILY_PIPLUP                  P_GEN_4_POKEMON
#define P_FAMILY_STARLY                  P_GEN_4_POKEMON
#define P_FAMILY_BIDOOF                  P_GEN_4_POKEMON
#define P_FAMILY_KRICKETOT               P_GEN_4_POKEMON
#define P_FAMILY_SHINX                   P_GEN_4_POKEMON
#define P_FAMILY_CRANIDOS                P_GEN_4_POKEMON
#define P_FAMILY_SHIELDON                P_GEN_4_POKEMON
#define P_FAMILY_BURMY                   FALSE
#define P_FAMILY_COMBEE                  P_GEN_4_POKEMON
#define P_FAMILY_PACHIRISU               FALSE
#define P_FAMILY_BUIZEL                  P_GEN_4_POKEMON
#define P_FAMILY_CHERUBI                 P_GEN_4_POKEMON
#define P_FAMILY_SHELLOS                 P_GEN_4_POKEMON
#define P_FAMILY_DRIFLOON                P_GEN_4_POKEMON
#define P_FAMILY_BUNEARY                 P_GEN_4_POKEMON
#define P_FAMILY_GLAMEOW                 FALSE
#define P_FAMILY_STUNKY                  FALSE
#define P_FAMILY_BRONZOR                 P_GEN_4_POKEMON
#define P_FAMILY_CHATOT                  FALSE
#define P_FAMILY_SPIRITOMB               FALSE
#define P_FAMILY_GIBLE                   P_GEN_4_POKEMON
#define P_FAMILY_RIOLU                   P_GEN_4_POKEMON
#define P_FAMILY_HIPPOPOTAS              P_GEN_4_POKEMON
#define P_FAMILY_SKORUPI                 P_GEN_4_POKEMON
#define P_FAMILY_CROAGUNK                P_GEN_4_POKEMON
#define P_FAMILY_CARNIVINE               FALSE
#define P_FAMILY_FINNEON                 FALSE
#define P_FAMILY_SNOVER                  P_GEN_4_POKEMON
#define P_FAMILY_ROTOM                   P_GEN_4_POKEMON
#define P_FAMILY_HEATRAN                 P_GEN_4_POKEMON
#define P_FAMILY_REGIGIGAS               P_GEN_4_POKEMON

#define P_FAMILY_SNIVY                   FALSE //TRUE
#define P_FAMILY_TEPIG                   FALSE //TRUE
#define P_FAMILY_BLITZLE                 FALSE //TRUE
#define P_FAMILY_ROGGENROLA              P_GEN_5_POKEMON
#define P_FAMILY_WOOBAT                  P_GEN_5_POKEMON
#define P_FAMILY_DRILBUR                 FALSE //TRUE
#define P_FAMILY_AUDINO                  P_GEN_5_POKEMON
#define P_FAMILY_TIMBURR                 FALSE //TRUE
#define P_FAMILY_COTTONEE                FALSE //TRUE
#define P_FAMILY_PETILIL                 P_GEN_5_POKEMON
#define P_FAMILY_SANDILE                 FALSE //TRUE
#define P_FAMILY_DARUMAKA                FALSE //TRUE
#define P_FAMILY_MARACTUS                P_GEN_5_POKEMON
#define P_FAMILY_DWEBBLE                 P_GEN_5_POKEMON
#define P_FAMILY_SCRAGGY                 FALSE //TRUE
#define P_FAMILY_SIGILYPH                P_GEN_5_POKEMON
#define P_FAMILY_YAMASK                  FALSE //TRUE
#define P_FAMILY_TIRTOUGA                P_GEN_5_POKEMON
#define P_FAMILY_ARCHEN                  P_GEN_5_POKEMON
#define P_FAMILY_TRUBBISH                P_GEN_5_POKEMON
#define P_FAMILY_ZORUA                   FALSE //TRUE
#define P_FAMILY_MINCCINO                P_GEN_5_POKEMON
#define P_FAMILY_GOTHITA                 FALSE //TRUE
#define P_FAMILY_SOLOSIS                 P_GEN_5_POKEMON
#define P_FAMILY_DUCKLETT                P_GEN_5_POKEMON
#define P_FAMILY_VANILLITE               FALSE //TRUE
#define P_FAMILY_KARRABLAST              P_GEN_5_POKEMON
#define P_FAMILY_FOONGUS                 FALSE //TRUE
#define P_FAMILY_FRILLISH                FALSE //TRUE
#define P_FAMILY_JOLTIK                  FALSE //TRUE
#define P_FAMILY_FERROSEED               FALSE //TRUE
#define P_FAMILY_KLINK                   P_GEN_5_POKEMON
#define P_FAMILY_TYNAMO                  P_GEN_5_POKEMON
#define P_FAMILY_ELGYEM                  FALSE //TRUE
#define P_FAMILY_LITWICK                 FALSE //TRUE
#define P_FAMILY_AXEW                    FALSE //TRUE
#define P_FAMILY_CUBCHOO                 FALSE //TRUE
#define P_FAMILY_CRYOGONAL               FALSE //TRUE
#define P_FAMILY_GOLETT                  FALSE //TRUE
#define P_FAMILY_PAWNIARD                FALSE //TRUE
#define P_FAMILY_BOUFFALANT              P_GEN_5_POKEMON
#define P_FAMILY_RUFFLET                 FALSE //TRUE
#define P_FAMILY_VULLABY                 FALSE //TRUE
#define P_FAMILY_DEINO                   FALSE //TRUE
#define P_FAMILY_LARVESTA                FALSE //TRUE

#define P_FAMILY_CHESPIN                 FALSE //TRUE
#define P_FAMILY_FENNEKIN                TRUE
#define P_FAMILY_FROAKIE                 FALSE //TRUE
#define P_FAMILY_BUNNELBY                FALSE //TRUE
#define P_FAMILY_FLETCHLING              FALSE //TRUE
#define P_FAMILY_SCATTERBUG              P_GEN_6_POKEMON
#define P_FAMILY_FLABEBE                 P_GEN_6_POKEMON
#define P_FAMILY_SKIDDO                  FALSE //TRUE
#define P_FAMILY_PANCHAM                 FALSE //TRUE
#define P_FAMILY_ESPURR                  P_GEN_6_POKEMON
#define P_FAMILY_HONEDGE                 FALSE //TRUE
#define P_FAMILY_TYRUNT                  FALSE //TRUE
#define P_FAMILY_AMAURA                  FALSE //TRUE
#define P_FAMILY_HAWLUCHA                P_GEN_6_POKEMON
#define P_FAMILY_DEDENNE                 P_GEN_6_POKEMON
#define P_FAMILY_CARBINK                 FALSE //TRUE
#define P_FAMILY_DIANCIE                 FALSE //TRUE
#define P_FAMILY_GOOMY                   FALSE //TRUE
#define P_FAMILY_PHANTUMP                FALSE //TRUE

#define P_FAMILY_ROWLET                  FALSE //TRUE
#define P_FAMILY_LITTEN                  FALSE //TRUE
#define P_FAMILY_POPPLIO                 FALSE //TRUE
#define P_FAMILY_ROCKRUFF                FALSE //TRUE
#define P_FAMILY_SANDYGAST               FALSE //TRUE
#define P_FAMILY_PYUKUMUKU               P_GEN_7_POKEMON
#define P_FAMILY_TYPE_NULL               P_GEN_7_POKEMON
#define P_FAMILY_MINIOR                  P_GEN_7_POKEMON
#define P_FAMILY_KOMALA                  P_GEN_7_POKEMON
#define P_FAMILY_TURTONATOR              P_GEN_7_POKEMON
#define P_FAMILY_TOGEDEMARU              P_GEN_7_POKEMON
#define P_FAMILY_MIMIKYU                 FALSE //TRUE
#define P_FAMILY_BRUXISH                 P_GEN_7_POKEMON
#define P_FAMILY_DRAMPA                  FALSE //TRUE
#define P_FAMILY_DHELMISE                P_GEN_7_POKEMON
#define P_FAMILY_JANGMO_O                FALSE //TRUE
#define P_FAMILY_ROOKIDEE                FALSE //TRUE
#define P_FAMILY_BLIPBUG                 FALSE //TRUE
#define P_FAMILY_WOOLOO                  FALSE //TRUE
#define P_FAMILY_CHEWTLE                 P_GEN_8_POKEMON
#define P_FAMILY_YAMPER                  P_GEN_8_POKEMON
#define P_FAMILY_ROLYCOLY                P_GEN_8_POKEMON
#define P_FAMILY_APPLIN                  P_GEN_8_POKEMON
#define P_FAMILY_SILICOBRA               P_GEN_8_POKEMON
#define P_FAMILY_CRAMORANT               P_GEN_8_POKEMON
#define P_FAMILY_ARROKUDA                P_GEN_8_POKEMON
#define P_FAMILY_TOXEL                   FALSE //TRUE
#define P_FAMILY_SIZZLIPEDE              P_GEN_8_POKEMON
#define P_FAMILY_IMPIDIMP                P_GEN_8_POKEMON
#define P_FAMILY_PINCURCHIN              P_GEN_8_POKEMON
#define P_FAMILY_SNOM                    FALSE //TRUE
#define P_FAMILY_CUFANT                  FALSE //TRUE
#define P_FAMILY_DURALUDON               P_GEN_8_POKEMON
#define P_FAMILY_DREEPY                  FALSE //TRUE
#define P_FAMILY_ZACIAN                  P_GEN_8_POKEMON
#define P_FAMILY_ZAMAZENTA               P_GEN_8_POKEMON
#define P_FAMILY_ETERNATUS               P_GEN_8_POKEMON
#define P_FAMILY_KUBFU                   P_GEN_8_POKEMON
#define P_FAMILY_ZARUDE                  P_GEN_8_POKEMON
#define P_FAMILY_REGIELEKI               FALSE //TRUE
#define P_FAMILY_REGIDRAGO               FALSE //TRUE

#define P_FAMILY_SPRIGATITO              P_GEN_9_POKEMON
#define P_FAMILY_FUECOCO                 P_GEN_9_POKEMON
#define P_FAMILY_TAROUNTULA              P_GEN_9_POKEMON
#define P_FAMILY_NYMBLE                  P_GEN_9_POKEMON
#define P_FAMILY_SQUAWKABILLY            P_GEN_9_POKEMON
#define P_FAMILY_CHARCADET               P_GEN_9_POKEMON
#define P_FAMILY_TADBULB                 P_GEN_9_POKEMON
#define P_FAMILY_WATTREL                 P_GEN_9_POKEMON
#define P_FAMILY_MASCHIFF                P_GEN_9_POKEMON
#define P_FAMILY_SHROODLE                P_GEN_9_POKEMON
#define P_FAMILY_BRAMBLIN                P_GEN_9_POKEMON
#define P_FAMILY_TOEDSCOOL               P_GEN_9_POKEMON
#define P_FAMILY_KLAWF                   P_GEN_9_POKEMON
#define P_FAMILY_CAPSAKID                P_GEN_9_POKEMON
#define P_FAMILY_RELLOR                  P_GEN_9_POKEMON
#define P_FAMILY_FLITTLE                 P_GEN_9_POKEMON
#define P_FAMILY_ORTHWORM                P_GEN_9_POKEMON
#define P_FAMILY_GLIMMET                 TRUE
#define P_FAMILY_GREAVARD                TRUE

#endif // GUARD_CONFIG_SPECIES_ENABLED_H
