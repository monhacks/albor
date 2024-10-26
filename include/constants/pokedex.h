#ifndef GUARD_CONSTANTS_POKEDEX_H
#define GUARD_CONSTANTS_POKEDEX_H

// National Pokédex order
enum {
    NATIONAL_DEX_NONE,
    NATIONAL_DEX_BULBASAUR,
    NATIONAL_DEX_IVYSAUR,
    NATIONAL_DEX_VENUSAUR,
    NATIONAL_DEX_CHARMANDER,
    NATIONAL_DEX_CHARMELEON,
    NATIONAL_DEX_CHARIZARD,
    NATIONAL_DEX_SQUIRTLE,
    NATIONAL_DEX_WARTORTLE,
    NATIONAL_DEX_BLASTOISE,
    NATIONAL_DEX_CATERPIE,
    NATIONAL_DEX_METAPOD,
    NATIONAL_DEX_BUTTERFREE,
    NATIONAL_DEX_WEEDLE,
    NATIONAL_DEX_KAKUNA,
    NATIONAL_DEX_BEEDRILL,
    NATIONAL_DEX_PIDGEY,
    NATIONAL_DEX_PIDGEOTTO,
    NATIONAL_DEX_PIDGEOT,
    NATIONAL_DEX_RATTATA,
    NATIONAL_DEX_RATICATE,
    //NATIONAL_DEX_RATTATA_ALOLAN,
    //NATIONAL_DEX_RATICATE_ALOLAN,
    NATIONAL_DEX_SPEAROW,
    NATIONAL_DEX_FEAROW,
    NATIONAL_DEX_EKANS,
    NATIONAL_DEX_ARBOK,
    NATIONAL_DEX_PICHU,
    NATIONAL_DEX_PIKACHU,
    NATIONAL_DEX_RAICHU,
    NATIONAL_DEX_SANDSHREW,
    NATIONAL_DEX_SANDSLASH,
    //NATIONAL_DEX_SANDSHREW_ALOLAN,
    //NATIONAL_DEX_SANDSHREW_ALOLAN,
    NATIONAL_DEX_NIDORAN_F,
    NATIONAL_DEX_NIDORINA,
    NATIONAL_DEX_NIDOQUEEN,
    NATIONAL_DEX_NIDORAN_M,
    NATIONAL_DEX_NIDORINO,
    NATIONAL_DEX_NIDOKING,
    NATIONAL_DEX_CLEFFA,
    NATIONAL_DEX_CLEFAIRY,
    NATIONAL_DEX_CLEFABLE,
    NATIONAL_DEX_VULPIX,
    NATIONAL_DEX_NINETALES,
    //NATIONAL_DEX_VULPIX_ALOLAN,
    //NATIONAL_DEX_NINETALES_ALOLAN,
    NATIONAL_DEX_IGGLYBUFF,
    NATIONAL_DEX_JIGGLYPUFF,
    NATIONAL_DEX_WIGGLYTUFF,
    NATIONAL_DEX_ZUBAT,
    NATIONAL_DEX_GOLBAT,
    NATIONAL_DEX_CROBAT,
    NATIONAL_DEX_ODDISH,
    NATIONAL_DEX_GLOOM,
    NATIONAL_DEX_VILEPLUME,
    NATIONAL_DEX_BELLOSSOM,
    NATIONAL_DEX_PARAS,
    NATIONAL_DEX_PARASECT,
    NATIONAL_DEX_VENONAT,
    NATIONAL_DEX_VENOMOTH,
    NATIONAL_DEX_DIGLETT,
    NATIONAL_DEX_DUGTRIO,
    NATIONAL_DEX_MEOWTH,
    NATIONAL_DEX_PERSIAN,
    //NATIONAL_DEX_MEOWTH_ALOLAN,
    //NATIONAL_DEX_PERSIAN_ALOLAN,
    NATIONAL_DEX_PSYDUCK,
    NATIONAL_DEX_GOLDUCK,
    NATIONAL_DEX_MANKEY,
    NATIONAL_DEX_PRIMEAPE,
    NATIONAL_DEX_ANNIHILAPE,
    NATIONAL_DEX_GROWLITHE,
    NATIONAL_DEX_ARCANINE,
    //NATIONAL_DEX_GROWLITHE_HISUIAN,
    //NATIONAL_DEX_ARCANINE_HISUIAN,
    NATIONAL_DEX_POLIWAG,
    NATIONAL_DEX_POLIWHIRL,
    NATIONAL_DEX_POLIWRATH,
    NATIONAL_DEX_POLITOED,
    NATIONAL_DEX_ABRA,
    NATIONAL_DEX_KADABRA,
    NATIONAL_DEX_ALAKAZAM,
    NATIONAL_DEX_MACHOP,
    NATIONAL_DEX_MACHOKE,
    NATIONAL_DEX_MACHAMP,
    NATIONAL_DEX_BELLSPROUT,
    NATIONAL_DEX_WEEPINBELL,
    NATIONAL_DEX_VICTREEBEL,
    NATIONAL_DEX_TENTACOOL,
    NATIONAL_DEX_TENTACRUEL,
    NATIONAL_DEX_GEODUDE,
    NATIONAL_DEX_GRAVELER,
    NATIONAL_DEX_GOLEM,
    //NATIONAL_DEX_GEODUDE_ALOLAN,
    //NATIONAL_DEX_GRAVELER_ALOLAN,
    //NATIONAL_DEX_GOLEM_ALOLAN,
    NATIONAL_DEX_PONYTA,
    NATIONAL_DEX_RAPIDASH,
    //NATIONAL_DEX_PONYTA_GALARIAN,
    //NATIONAL_DEX_RAPIDASH_GALARIAN,
    NATIONAL_DEX_SLOWPOKE,
    NATIONAL_DEX_SLOWBRO,
    NATIONAL_DEX_SLOWKING,
    //NATIONAL_DEX_SLOWPOKE_GALARIAN,
    //NATIONAL_DEX_SLOWBRO_GALARIAN,
    //NATIONAL_DEX_SLOWKING_GALARIAN,
    NATIONAL_DEX_MAGNEMITE,
    NATIONAL_DEX_MAGNETON,
    NATIONAL_DEX_MAGNEZONE,
    NATIONAL_DEX_DODUO,
    NATIONAL_DEX_DODRIO,
    NATIONAL_DEX_SEEL,
    NATIONAL_DEX_DEWGONG,
    NATIONAL_DEX_GRIMER,
    NATIONAL_DEX_MUK,
    NATIONAL_DEX_SHELLDER,
    NATIONAL_DEX_CLOYSTER,
    NATIONAL_DEX_GASTLY,
    NATIONAL_DEX_HAUNTER,
    NATIONAL_DEX_GENGAR,
    NATIONAL_DEX_ONIX,
    NATIONAL_DEX_STEELIX,
    NATIONAL_DEX_DROWZEE,
    NATIONAL_DEX_HYPNO,
    NATIONAL_DEX_KRABBY,
    NATIONAL_DEX_KINGLER,
    NATIONAL_DEX_VOLTORB,
    NATIONAL_DEX_ELECTRODE,
    //NATIONAL_DEX_VOLTORB_HISUIAN,
    //NATIONAL_DEX_ELECTRODE_HISUIAN,
    NATIONAL_DEX_EXEGGCUTE,
    NATIONAL_DEX_EXEGGUTOR,
    NATIONAL_DEX_CUBONE,
    NATIONAL_DEX_MAROWAK,
    //NATIONAL_DEX_MAROWAK_ALOLAN,
    NATIONAL_DEX_TYROGUE,
    NATIONAL_DEX_HITMONLEE,
    NATIONAL_DEX_HITMONCHAN,
    NATIONAL_DEX_HITMONTOP,
    NATIONAL_DEX_LICKITUNG,
    NATIONAL_DEX_LICKILICKY,
    NATIONAL_DEX_KOFFING,
    NATIONAL_DEX_WEEZING,
    //NATIONAL_DEX_WEEZING_GALARIAN,
    NATIONAL_DEX_RHYHORN,
    NATIONAL_DEX_RHYDON,
    NATIONAL_DEX_RHYPERIOR,
    NATIONAL_DEX_TANGELA,
    NATIONAL_DEX_TANGROWTH,
    NATIONAL_DEX_KANGASKHAN,
    NATIONAL_DEX_HORSEA,
    NATIONAL_DEX_SEADRA,
    NATIONAL_DEX_KINGDRA,
    NATIONAL_DEX_GOLDEEN,
    NATIONAL_DEX_SEAKING,
    NATIONAL_DEX_STARYU,
    NATIONAL_DEX_STARMIE,
    NATIONAL_DEX_MIME_JR,
    NATIONAL_DEX_MR_MIME,
    NATIONAL_DEX_SCYTHER,
    NATIONAL_DEX_SCIZOR,
    NATIONAL_DEX_KLEAVOR,
    NATIONAL_DEX_SMOOCHUM,
    NATIONAL_DEX_JYNX,
    NATIONAL_DEX_ELEKID,
    NATIONAL_DEX_ELECTABUZZ,
    NATIONAL_DEX_ELECTIVIRE,
    NATIONAL_DEX_MAGBY,
    NATIONAL_DEX_MAGMAR,
    NATIONAL_DEX_MAGMORTAR,
    NATIONAL_DEX_PINSIR,
    NATIONAL_DEX_TAUROS,
    NATIONAL_DEX_MAGIKARP,
    NATIONAL_DEX_GYARADOS,
    NATIONAL_DEX_LAPRAS,
    NATIONAL_DEX_EEVEE,
    NATIONAL_DEX_VAPOREON,
    NATIONAL_DEX_JOLTEON,
    NATIONAL_DEX_FLAREON,
    NATIONAL_DEX_ESPEON,
    NATIONAL_DEX_UMBREON,
    NATIONAL_DEX_LEAFEON,
    NATIONAL_DEX_GLACEON,
    NATIONAL_DEX_SYLVEON,
    NATIONAL_DEX_PORYGON,
    NATIONAL_DEX_PORYGON2,
    NATIONAL_DEX_PORYGON_Z,
    NATIONAL_DEX_OMANYTE,
    NATIONAL_DEX_OMASTAR,
    NATIONAL_DEX_KABUTO,
    NATIONAL_DEX_KABUTOPS,
    NATIONAL_DEX_AERODACTYL,
    NATIONAL_DEX_MUNCHLAX,
    NATIONAL_DEX_SNORLAX,
    NATIONAL_DEX_ARTICUNO,
    //NATIONAL_DEX_ARTICUNO_GALARIAN,
    NATIONAL_DEX_ZAPDOS,
    //NATIONAL_DEX_ZAPDOS_GALARIAN,
    NATIONAL_DEX_MOLTRES,
    //NATIONAL_DEX_MOLTRES_GALARIAN,
    NATIONAL_DEX_DRATINI,
    NATIONAL_DEX_DRAGONAIR,
    NATIONAL_DEX_DRAGONITE,
    NATIONAL_DEX_MEW,
    NATIONAL_DEX_MEWTWO,
    NATIONAL_DEX_CHIKORITA,
    NATIONAL_DEX_BAYLEEF,
    NATIONAL_DEX_MEGANIUM,
    NATIONAL_DEX_CYNDAQUIL,
    NATIONAL_DEX_QUILAVA,
    NATIONAL_DEX_TYPHLOSION,
    //NATIONAL_DEX_TYPHLOSION_HISUIAN,
    NATIONAL_DEX_TOTODILE,
    NATIONAL_DEX_CROCONAW,
    NATIONAL_DEX_FERALIGATR,
    NATIONAL_DEX_SENTRET,
    NATIONAL_DEX_FURRET,
    NATIONAL_DEX_HOOTHOOT,
    NATIONAL_DEX_NOCTOWL,
    NATIONAL_DEX_LEDYBA,
    NATIONAL_DEX_LEDIAN,
    NATIONAL_DEX_SPINARAK,
    NATIONAL_DEX_ARIADOS,
    NATIONAL_DEX_CHINCHOU,
    NATIONAL_DEX_LANTURN,
    NATIONAL_DEX_TOGEPI,
    NATIONAL_DEX_TOGETIC,
    NATIONAL_DEX_TOGEKISS,
    NATIONAL_DEX_NATU,
    NATIONAL_DEX_XATU,
    NATIONAL_DEX_MAREEP,
    NATIONAL_DEX_FLAAFFY,
    NATIONAL_DEX_AMPHAROS,
    NATIONAL_DEX_AZURILL,
    NATIONAL_DEX_MARILL,
    NATIONAL_DEX_AZUMARILL,
    NATIONAL_DEX_BONSLY,
    NATIONAL_DEX_SUDOWOODO,
    NATIONAL_DEX_HOPPIP,
    NATIONAL_DEX_SKIPLOOM,
    NATIONAL_DEX_JUMPLUFF,
    NATIONAL_DEX_AIPOM,
    NATIONAL_DEX_AMBIPOM,
    NATIONAL_DEX_SUNKERN,
    NATIONAL_DEX_SUNFLORA,
    NATIONAL_DEX_YANMA,
    NATIONAL_DEX_YANMEGA,
    NATIONAL_DEX_WOOPER,
    //NATIONAL_DEX_WOOPER_HISUIAN,
    NATIONAL_DEX_QUAGSIRE,
    NATIONAL_DEX_CLODSIRE,
    NATIONAL_DEX_MURKROW,
    NATIONAL_DEX_HONCHKROW,
    NATIONAL_DEX_MISDREAVUS,
    NATIONAL_DEX_MISMAGIUS,
    NATIONAL_DEX_GIRAFARIG,
    NATIONAL_DEX_PINECO,
    NATIONAL_DEX_FORRETRESS,
    NATIONAL_DEX_GLIGAR,
    NATIONAL_DEX_GLISCOR,
    NATIONAL_DEX_SNUBBULL,
    NATIONAL_DEX_GRANBULL,
    NATIONAL_DEX_HERACROSS,
    NATIONAL_DEX_SNEASEL,
    NATIONAL_DEX_WEAVILE,
    NATIONAL_DEX_SNEASLER,
    NATIONAL_DEX_TEDDIURSA,
    NATIONAL_DEX_URSARING,
    NATIONAL_DEX_SLUGMA,
    NATIONAL_DEX_MAGCARGO,
    NATIONAL_DEX_SWINUB,
    NATIONAL_DEX_PILOSWINE,
    NATIONAL_DEX_MAMOSWINE,
    NATIONAL_DEX_CORSOLA,
    NATIONAL_DEX_REMORAID,
    NATIONAL_DEX_OCTILLERY,
    NATIONAL_DEX_DELIBIRD,
    NATIONAL_DEX_MANTYKE,
    NATIONAL_DEX_MANTINE,
    NATIONAL_DEX_SKARMORY,
    NATIONAL_DEX_HOUNDOUR,
    NATIONAL_DEX_HOUNDOOM,
    NATIONAL_DEX_PHANPY,
    NATIONAL_DEX_DONPHAN,
    NATIONAL_DEX_STANTLER,
    NATIONAL_DEX_WYRDEER,
    NATIONAL_DEX_MILTANK,
    NATIONAL_DEX_RAIKOU,
    NATIONAL_DEX_ENTEI,
    NATIONAL_DEX_SUICUNE,
    NATIONAL_DEX_LARVITAR,
    NATIONAL_DEX_PUPITAR,
    NATIONAL_DEX_TYRANITAR,
    NATIONAL_DEX_LUGIA,
    NATIONAL_DEX_HO_OH,
    NATIONAL_DEX_CELEBI,
    NATIONAL_DEX_TREECKO,
    NATIONAL_DEX_GROVYLE,
    NATIONAL_DEX_SCEPTILE,
    NATIONAL_DEX_TORCHIC,
    NATIONAL_DEX_COMBUSKEN,
    NATIONAL_DEX_BLAZIKEN,
    NATIONAL_DEX_MUDKIP,
    NATIONAL_DEX_MARSHTOMP,
    NATIONAL_DEX_SWAMPERT,
    NATIONAL_DEX_POOCHYENA,
    NATIONAL_DEX_MIGHTYENA,
    NATIONAL_DEX_ZIGZAGOON,
    NATIONAL_DEX_LINOONE,
    //NATIONAL_DEX_ZIGZAGOON,
    //NATIONAL_DEX_LINOONE,
    NATIONAL_DEX_OBSTAGOON,
    NATIONAL_DEX_WURMPLE,
    NATIONAL_DEX_SILCOON,
    NATIONAL_DEX_BEAUTIFLY,
    NATIONAL_DEX_CASCOON,
    NATIONAL_DEX_DUSTOX,
    NATIONAL_DEX_LOTAD,
    NATIONAL_DEX_LOMBRE,
    NATIONAL_DEX_LUDICOLO,
    NATIONAL_DEX_SEEDOT,
    NATIONAL_DEX_NUZLEAF,
    NATIONAL_DEX_SHIFTRY,
    NATIONAL_DEX_TAILLOW,
    NATIONAL_DEX_SWELLOW,
    NATIONAL_DEX_WINGULL,
    NATIONAL_DEX_PELIPPER,
    NATIONAL_DEX_RALTS,
    NATIONAL_DEX_KIRLIA,
    NATIONAL_DEX_GARDEVOIR,
    NATIONAL_DEX_GALLADE,
    NATIONAL_DEX_SURSKIT,
    NATIONAL_DEX_MASQUERAIN,
    NATIONAL_DEX_SHROOMISH,
    NATIONAL_DEX_BRELOOM,
    NATIONAL_DEX_SLAKOTH,
    NATIONAL_DEX_VIGOROTH,
    NATIONAL_DEX_SLAKING,
    NATIONAL_DEX_NINCADA,
    NATIONAL_DEX_NINJASK,
    NATIONAL_DEX_SHEDINJA,
    NATIONAL_DEX_WHISMUR,
    NATIONAL_DEX_LOUDRED,
    NATIONAL_DEX_EXPLOUD,
    NATIONAL_DEX_MAKUHITA,
    NATIONAL_DEX_HARIYAMA,
    NATIONAL_DEX_NOSEPASS,
    NATIONAL_DEX_PROBOPASS,
    NATIONAL_DEX_SABLEYE,
    NATIONAL_DEX_MAWILE,
    NATIONAL_DEX_ARON,
    NATIONAL_DEX_LAIRON,
    NATIONAL_DEX_AGGRON,
    NATIONAL_DEX_MEDITITE,
    NATIONAL_DEX_MEDICHAM,
    NATIONAL_DEX_ELECTRIKE,
    NATIONAL_DEX_MANECTRIC,
    NATIONAL_DEX_BUDEW,
    NATIONAL_DEX_ROSELIA,
    NATIONAL_DEX_ROSERADE,
    NATIONAL_DEX_CARVANHA,
    NATIONAL_DEX_SHARPEDO,
    NATIONAL_DEX_WAILMER,
    NATIONAL_DEX_WAILORD,
    NATIONAL_DEX_NUMEL,
    NATIONAL_DEX_CAMERUPT,
    NATIONAL_DEX_TORKOAL,
    NATIONAL_DEX_TRAPINCH,
    NATIONAL_DEX_VIBRAVA,
    NATIONAL_DEX_FLYGON,
    NATIONAL_DEX_CACNEA,
    NATIONAL_DEX_CACTURNE,
    NATIONAL_DEX_SWABLU,
    NATIONAL_DEX_ALTARIA,
    NATIONAL_DEX_LUNATONE,
    NATIONAL_DEX_SOLROCK,
    NATIONAL_DEX_BALTOY,
    NATIONAL_DEX_CLAYDOL,
    NATIONAL_DEX_LILEEP,
    NATIONAL_DEX_CRADILY,
    NATIONAL_DEX_ANORITH,
    NATIONAL_DEX_ARMALDO,
    NATIONAL_DEX_FEEBAS,
    NATIONAL_DEX_MILOTIC,
    NATIONAL_DEX_CASTFORM,
    NATIONAL_DEX_KECLEON,
    NATIONAL_DEX_SHUPPET,
    NATIONAL_DEX_BANETTE,
    NATIONAL_DEX_DUSKULL,
    NATIONAL_DEX_DUSCLOPS,
    NATIONAL_DEX_DUSKNOIR,
    NATIONAL_DEX_TROPIUS,
    NATIONAL_DEX_CHINGLING,
    NATIONAL_DEX_CHIMECHO,
    NATIONAL_DEX_ABSOL,
    NATIONAL_DEX_SNORUNT,
    NATIONAL_DEX_GLALIE,
    NATIONAL_DEX_FROSLASS,
    NATIONAL_DEX_SPHEAL,
    NATIONAL_DEX_SEALEO,
    NATIONAL_DEX_WALREIN,
    NATIONAL_DEX_CLAMPERL,
    NATIONAL_DEX_HUNTAIL,
    NATIONAL_DEX_GOREBYSS,
    NATIONAL_DEX_RELICANTH,
    NATIONAL_DEX_LUVDISC,
    NATIONAL_DEX_BAGON,
    NATIONAL_DEX_SHELGON,
    NATIONAL_DEX_SALAMENCE,
    NATIONAL_DEX_BELDUM,
    NATIONAL_DEX_METANG,
    NATIONAL_DEX_METAGROSS,
    NATIONAL_DEX_LATIAS,
    NATIONAL_DEX_LATIOS,
    NATIONAL_DEX_KYOGRE,
    NATIONAL_DEX_GROUDON,
    NATIONAL_DEX_RAYQUAZA,
    NATIONAL_DEX_JIRACHI,
    NATIONAL_DEX_DEOXYS,
    NATIONAL_DEX_TURTWIG,
    NATIONAL_DEX_GROTLE,
    NATIONAL_DEX_TORTERRA,
    NATIONAL_DEX_CHIMCHAR,
    NATIONAL_DEX_MONFERNO,
    NATIONAL_DEX_INFERNAPE,
    NATIONAL_DEX_PIPLUP,
    NATIONAL_DEX_PRINPLUP,
    NATIONAL_DEX_EMPOLEON,
    NATIONAL_DEX_STARLY,
    NATIONAL_DEX_STARAVIA,
    NATIONAL_DEX_STARAPTOR,
    NATIONAL_DEX_BIDOOF,
    NATIONAL_DEX_BIBAREL,
    NATIONAL_DEX_KRICKETOT,
    NATIONAL_DEX_KRICKETUNE,
    NATIONAL_DEX_SHINX,
    NATIONAL_DEX_LUXIO,
    NATIONAL_DEX_LUXRAY,
    NATIONAL_DEX_CRANIDOS,
    NATIONAL_DEX_RAMPARDOS,
    NATIONAL_DEX_SHIELDON,
    NATIONAL_DEX_BASTIODON,
    NATIONAL_DEX_COMBEE,
    NATIONAL_DEX_VESPIQUEN,
    NATIONAL_DEX_BUIZEL,
    NATIONAL_DEX_FLOATZEL,
    NATIONAL_DEX_CHERUBI,
    NATIONAL_DEX_CHERRIM,
    NATIONAL_DEX_SHELLOS,
    NATIONAL_DEX_GASTRODON,
    NATIONAL_DEX_DRIFLOON,
    NATIONAL_DEX_DRIFBLIM,
    NATIONAL_DEX_BUNEARY,
    NATIONAL_DEX_LOPUNNY,
    NATIONAL_DEX_BRONZOR,
    NATIONAL_DEX_BRONZONG,
    NATIONAL_DEX_GIBLE,
    NATIONAL_DEX_GABITE,
    NATIONAL_DEX_GARCHOMP,
    NATIONAL_DEX_RIOLU,
    NATIONAL_DEX_LUCARIO,
    NATIONAL_DEX_HIPPOPOTAS,
    NATIONAL_DEX_HIPPOWDON,
    NATIONAL_DEX_SKORUPI,
    NATIONAL_DEX_DRAPION,
    NATIONAL_DEX_CROAGUNK,
    NATIONAL_DEX_TOXICROAK,
    NATIONAL_DEX_SNOVER,
    NATIONAL_DEX_ABOMASNOW,
    NATIONAL_DEX_ROTOM,
    NATIONAL_DEX_HEATRAN,
    NATIONAL_DEX_SNIVY,
    NATIONAL_DEX_SERVINE,
    NATIONAL_DEX_SERPERIOR,
    NATIONAL_DEX_TEPIG,
    NATIONAL_DEX_PIGNITE,
    NATIONAL_DEX_EMBOAR,
    NATIONAL_DEX_OSHAWOTT,
    NATIONAL_DEX_DEWOTT,
    NATIONAL_DEX_SAMUROTT,
    //NATIONAL_DEX_SAMUROTT_HISUIAN,
    NATIONAL_DEX_BLITZLE,
    NATIONAL_DEX_ZEBSTRIKA,
    NATIONAL_DEX_DRILBUR,
    NATIONAL_DEX_EXCADRILL,
    NATIONAL_DEX_TIMBURR,
    NATIONAL_DEX_GURDURR,
    NATIONAL_DEX_CONKELDURR,
    NATIONAL_DEX_COTTONEE,
    NATIONAL_DEX_WHIMSICOTT,
    NATIONAL_DEX_SANDILE,
    NATIONAL_DEX_KROKOROK,
    NATIONAL_DEX_KROOKODILE,
    NATIONAL_DEX_DARUMAKA,
    NATIONAL_DEX_DARMANITAN,
    //NATIONAL_DEX_DARUMAKA_GALARIAN,
    //NATIONAL_DEX_DARMANITAN_GALARIAN,
    NATIONAL_DEX_SCRAGGY,
    NATIONAL_DEX_SCRAFTY,
    NATIONAL_DEX_YAMASK,
    NATIONAL_DEX_COFAGRIGUS,
    NATIONAL_DEX_ZORUA,
    NATIONAL_DEX_ZOROARK,
    //NATIONAL_DEX_ZORUA_HISUIAN,
    //NATIONAL_DEX_ZOROARK_HISUIAN,
    NATIONAL_DEX_GOTHITA,
    NATIONAL_DEX_GOTHORITA,
    NATIONAL_DEX_GOTHITELLE,
    NATIONAL_DEX_VANILLITE,
    NATIONAL_DEX_VANILLISH,
    NATIONAL_DEX_VANILLUXE,
    NATIONAL_DEX_FOONGUS,
    NATIONAL_DEX_AMOONGUSS,
    NATIONAL_DEX_FRILLISH,
    NATIONAL_DEX_JELLICENT,
    NATIONAL_DEX_JOLTIK,
    NATIONAL_DEX_GALVANTULA,
    NATIONAL_DEX_FERROSEED,
    NATIONAL_DEX_FERROTHORN,
    NATIONAL_DEX_ELGYEM,
    NATIONAL_DEX_BEHEEYEM,
    NATIONAL_DEX_LITWICK,
    NATIONAL_DEX_LAMPENT,
    NATIONAL_DEX_CHANDELURE,
    NATIONAL_DEX_AXEW,
    NATIONAL_DEX_FRAXURE,
    NATIONAL_DEX_HAXORUS,
    NATIONAL_DEX_CUBCHOO,
    NATIONAL_DEX_BEARTIC,
    NATIONAL_DEX_CRYOGONAL,
    NATIONAL_DEX_GOLETT,
    NATIONAL_DEX_GOLURK,
    NATIONAL_DEX_PAWNIARD,
    NATIONAL_DEX_BISHARP,
    NATIONAL_DEX_RUFFLET,
    NATIONAL_DEX_BRAVIARY,
    //NATIONAL_DEX_BRAVIARY_HISUIAN,
    NATIONAL_DEX_VULLABY,
    NATIONAL_DEX_MANDIBUZZ,
    NATIONAL_DEX_DEINO,
    NATIONAL_DEX_ZWEILOUS,
    NATIONAL_DEX_HYDREIGON,
    NATIONAL_DEX_LARVESTA,
    NATIONAL_DEX_VOLCARONA,
    NATIONAL_DEX_CHESPIN,
    NATIONAL_DEX_QUILLADIN,
    NATIONAL_DEX_CHESNAUGHT,
    NATIONAL_DEX_FENNEKIN,
    NATIONAL_DEX_BRAIXEN,
    NATIONAL_DEX_DELPHOX,
    NATIONAL_DEX_FROAKIE,
    NATIONAL_DEX_FROGADIER,
    NATIONAL_DEX_GRENINJA,
    NATIONAL_DEX_BUNNELBY,
    NATIONAL_DEX_DIGGERSBY,
    NATIONAL_DEX_FLETCHLING,
    NATIONAL_DEX_FLETCHINDER,
    NATIONAL_DEX_TALONFLAME,
    NATIONAL_DEX_LITLEO,
    NATIONAL_DEX_PYROAR,
    NATIONAL_DEX_SKIDDO,
    NATIONAL_DEX_GOGOAT,
    NATIONAL_DEX_PANCHAM,
    NATIONAL_DEX_PANGORO,
    NATIONAL_DEX_HONEDGE,
    NATIONAL_DEX_DOUBLADE,
    NATIONAL_DEX_AEGISLASH,
    NATIONAL_DEX_TYRUNT,
    NATIONAL_DEX_TYRANTRUM,
    NATIONAL_DEX_AMAURA,
    NATIONAL_DEX_AURORUS,
    NATIONAL_DEX_CARBINK,
    NATIONAL_DEX_DIANCIE,
    NATIONAL_DEX_GOOMY,
    NATIONAL_DEX_SLIGGOO,
    NATIONAL_DEX_GOODRA,
    NATIONAL_DEX_PHANTUMP,
    NATIONAL_DEX_TREVENANT,
    NATIONAL_DEX_BERGMITE,
    NATIONAL_DEX_AVALUGG,
    NATIONAL_DEX_VOLCANION,
    NATIONAL_DEX_ROWLET,
    NATIONAL_DEX_DARTRIX,
    NATIONAL_DEX_DECIDUEYE,
    //NATIONAL_DEX_DECIDUEYE_HISUIAN,
    NATIONAL_DEX_LITTEN,
    NATIONAL_DEX_TORRACAT,
    NATIONAL_DEX_INCINEROAR,
    NATIONAL_DEX_POPPLIO,
    NATIONAL_DEX_BRIONNE,
    NATIONAL_DEX_PRIMARINA,
    NATIONAL_DEX_ROCKRUFF,
    NATIONAL_DEX_LYCANROC,
    //NATIONAL_DEX_LYCANROC_DUSK,
    //NATIONAL_DEX_LYCANROC_MIDNIGHT,
    NATIONAL_DEX_SALANDIT,
    NATIONAL_DEX_SALAZZLE,
    NATIONAL_DEX_SANDYGAST,
    NATIONAL_DEX_PALOSSAND,
    NATIONAL_DEX_MIMIKYU,
    NATIONAL_DEX_DRAMPA,
    NATIONAL_DEX_JANGMO_O,
    NATIONAL_DEX_HAKAMO_O,
    NATIONAL_DEX_KOMMO_O,
    NATIONAL_DEX_ROOKIDEE,
    NATIONAL_DEX_CORVISQUIRE,
    NATIONAL_DEX_CORVIKNIGHT,
    NATIONAL_DEX_BLIPBUG,
    NATIONAL_DEX_DOTTLER,
    NATIONAL_DEX_ORBEETLE,
    NATIONAL_DEX_WOOLOO,
    NATIONAL_DEX_DUBWOOL,
    NATIONAL_DEX_TOXEL,
    NATIONAL_DEX_TOXTRICITY,
    //NATIONAL_DEX_TOXTRICITY_LOW_KEY,
    NATIONAL_DEX_SNOM,
    NATIONAL_DEX_FROSMOTH,
    NATIONAL_DEX_CUFANT,
    NATIONAL_DEX_COPPERAJAH,
    NATIONAL_DEX_DREEPY,
    NATIONAL_DEX_DRAKLOAK,
    NATIONAL_DEX_DRAGAPULT,
    NATIONAL_DEX_CHARCADET,
    NATIONAL_DEX_ARMAROUGE,
    NATIONAL_DEX_CERULEDGE,
    NATIONAL_DEX_SHROODLE,
    NATIONAL_DEX_GRAFAIAI,
    NATIONAL_DEX_VAROOM,
    NATIONAL_DEX_REVAVROOM,
    NATIONAL_DEX_GLIMMET,
    NATIONAL_DEX_GLIMMORA,
    NATIONAL_DEX_GREAVARD,
    NATIONAL_DEX_HOUNDSTONE,
    NATIONAL_DEX_REGIROCK,
    NATIONAL_DEX_REGICE,
    NATIONAL_DEX_REGISTEEL,
    NATIONAL_DEX_REGIELEKI,
    NATIONAL_DEX_REGIDRAGO,
    NATIONAL_DEX_REGIGIGAS,
};

#define NATIONAL_DEX_COUNT  NATIONAL_DEX_REGIGIGAS

#define POKEMON_SLOTS_NUMBER (NATIONAL_DEX_COUNT + 1)

#define DECAGRAMS_IN_POUND             4536
#define CM_PER_INCH                    2.54
#define CM_PER_INCH_FACTOR             (CM_PER_INCH * 100)
#define INCHES_IN_FOOT                 12
#define INCHES_IN_ONE_AND_HALF_FOOT    (INCHES_IN_FOOT * 1.5)
#define INCHES_IN_FOOT_FACTOR          (INCHES_IN_FOOT * 10)

#define WEIGHT_HEIGHT_STR_LEN          16
#define WEIGHT_HEIGHT_STR_MEM          (WEIGHT_HEIGHT_STR_LEN * sizeof(u8))

#define DEX_HEADER_X                   96
#define DEX_Y_TOP                      57
#define DEX_Y_BOTTOM                   73
#define DEX_MEASUREMENT_X              129

#define DEX_HGSS_HEADER_X_PADDING      59
#define DEX_HGSS_Y_TOP_PADDING         7
#define DEX_HGSS_Y_BOTTOM_PADDING      4
#define DEX_HGSS_MEASUREMENT_X_PADDING 51

enum
{
    FLAG_GET_SEEN,
    FLAG_GET_CAUGHT,
    FLAG_SET_SEEN,
    FLAG_SET_CAUGHT
};

#endif // GUARD_CONSTANTS_POKEDEX_H
