extern const u8 EventScript_FollowerIsShivering[];
extern const u8 EventScript_FollowerNostalgia[];
extern const u8 EventScript_FollowerHopping[];
extern const u8 EventScript_FollowerJumpOnPlayer[];
extern const u8 EventScript_FollowerCuddling[];
extern const u8 EventScript_FollowerShiverCuddling[];
extern const u8 EventScript_FollowerGetCloser[];
extern const u8 EventScript_FollowerPokingPlayer[];
extern const u8 EventScript_FollowerLookAround[];
extern const u8 EventScript_FollowerLookAway[];
extern const u8 EventScript_FollowerLookAwayBark[];
extern const u8 EventScript_FollowerLookAwayPoke[];
extern const u8 EventScript_FollowerPokeGround[];
extern const u8 EventScript_FollowerStartled[];
extern const u8 EventScript_FollowerFastHopping[];
extern const u8 EventScript_FollowerDizzy[];
extern const u8 EventScript_FollowerLookAroundScared[];
extern const u8 EventScript_FollowerDance[];
extern const u8 EventScript_FollowerLookUp[];

// 'Generic', unconditional happy messages
static const u8 sHappyMsg00[] = _("¡{STR_VAR_1} te hace cosquillas\nen la tripa!");
static const u8 sHappyMsg01[] = _("{STR_VAR_1} está feliz, pero se esconde.");
static const u8 sHappyMsg02[] = _("{STR_VAR_1} va genial.");
static const u8 sHappyMsg03[] = _("{STR_VAR_1} va tan serenamente.");
static const u8 sHappyMsg04[] = _("¡Se nota que a {STR_VAR_1} le\nencanta pasear contigo!");
static const u8 sHappyMsg05[] = _("{STR_VAR_1} está radiante.");
static const u8 sHappyMsg06[] = _("{STR_VAR_1} parece muy feliz.");
static const u8 sHappyMsg07[] = _("{STR_VAR_1} se está esforzando.");
static const u8 sHappyMsg08[] = _("{STR_VAR_1} está olisqueando\nlos alrededores.");
static const u8 sHappyMsg09[] = _("¡{STR_VAR_1} da saltos de alegría!");
static const u8 sHappyMsg10[] = _("¡{STR_VAR_1} sigue muy alegre!");
static const u8 sHappyMsg11[] = _("{STR_VAR_1} ha captado un\nolor especial.");
static const u8 sHappyMsg12[] = _("{STR_VAR_1} te hurga por \nla camiseta.");
static const u8 sHappyMsg13[] = _("Tu {STR_VAR_1} se está\nestirando y relajándose.");
static const u8 sHappyMsg14[] = _("¡A {STR_VAR_1} le gusta liderar!");
static const u8 sHappyMsg15[] = _("{STR_VAR_1} lo está dando\ntodo para seguir contigo.");
static const u8 sHappyMsg16[] = _("¡{STR_VAR_1} está felizmente\nabrazándose contigo!");
static const u8 sHappyMsg17[] = _("¡{STR_VAR_1} es todo energía!");
static const u8 sHappyMsg18[] = _("¡{STR_VAR_1} está muy feliz!");
static const u8 sHappyMsg19[] = _("¡{STR_VAR_1} está tan feliz\nque brincotea!");
static const u8 sHappyMsg20[] = _("{STR_VAR_1} nodded slowly.");
static const u8 sHappyMsg21[] = _("{STR_VAR_1} is very eager!");
static const u8 sHappyMsg22[] = _("{STR_VAR_1} is wandering around and\nlistening to the different sounds.");
static const u8 sHappyMsg23[] = _("{STR_VAR_1} parece con interés\npor algo.");
static const u8 sHappyMsg24[] = _("{STR_VAR_1} is somehow forcing\nitself to keep going.");
static const u8 sHappyMsg25[] = _("¡{STR_VAR_1} te mira radiante!");
static const u8 sHappyMsg26[] = _("{STR_VAR_1} te mira feliz\ny parece sonreír.");
static const u8 sHappyMsg27[] = _("{STR_VAR_1} disfruta del olor\nde las flores.");
static const u8 sHappyMsg28[] = _("¡A {STR_VAR_1} le encanta\nverte a su lado!");
static const u8 sHappyMsg29[] = _("{STR_VAR_1} faced this way and\ngrinned.");
static const u8 sHappyMsg30[] = _("{STR_VAR_1} se acurruca contigo…");
// Conditional messages begin here, index 31
static const u8 sHappyMsg31[] = _("Tu {STR_VAR_1} parece disfrutar\ndel buen tiempo.");
static const u8 sHappyMsg32[] = _("¡{STR_VAR_1} confía en ti!");

const struct FollowerMsgInfo gFollowerHappyMessages[] = {
    {sHappyMsg00, EventScript_FollowerPokingPlayer},
    {sHappyMsg01}, {sHappyMsg02}, {sHappyMsg03}, {sHappyMsg04}, {sHappyMsg05}, {sHappyMsg06}, {sHappyMsg07},
    {sHappyMsg08, EventScript_FollowerLookAround},
    {sHappyMsg09, EventScript_FollowerHopping},
    {sHappyMsg10}, {sHappyMsg11},
    {sHappyMsg12, EventScript_FollowerPokingPlayer},
    {sHappyMsg13, EventScript_FollowerLookAround},
    {sHappyMsg14}, {sHappyMsg15},
    {sHappyMsg16, EventScript_FollowerCuddling},
    {sHappyMsg17}, {sHappyMsg18},
    {sHappyMsg19, EventScript_FollowerFastHopping},
    {sHappyMsg20}, {sHappyMsg21}, {sHappyMsg22}, {sHappyMsg23}, {sHappyMsg24}, {sHappyMsg25}, {sHappyMsg26}, {sHappyMsg27}, {sHappyMsg28}, {sHappyMsg29},
    {sHappyMsg30, EventScript_FollowerCuddling},
    {sHappyMsg31}, {sHappyMsg32},
};

// Unconditional neutral messages
static const u8 sNeutralMsg00[] = _("{STR_VAR_1} is steadily poking at\nthe ground.");
static const u8 sNeutralMsg01[] = _("{STR_VAR_1} is standing guard.");
static const u8 sNeutralMsg02[] = _("{STR_VAR_1} is staring patiently at\nnothing at all.");
static const u8 sNeutralMsg03[] = _("{STR_VAR_1} is wandering around.");
static const u8 sNeutralMsg04[] = _("¡{STR_VAR_1} bosteza haciendo\nmucho ruido!");
static const u8 sNeutralMsg05[] = _("{STR_VAR_1} mira a todos\nlados sin descanso.");
static const u8 sNeutralMsg06[] = _("{STR_VAR_1} is looking this way and\nsmiling.");
static const u8 sNeutralMsg07[] = _("{STR_VAR_1} is gazing around\nrestlessly.");
static const u8 sNeutralMsg08[] = _("{STR_VAR_1} let out a battle cry.");
static const u8 sNeutralMsg09[] = _("{STR_VAR_1} danced a wonderful\ndance!");
static const u8 sNeutralMsg10[] = _("{STR_VAR_1} is very eager.");
static const u8 sNeutralMsg11[] = _("{STR_VAR_1} is staring intently into\nthe distance.");
static const u8 sNeutralMsg12[] = _("{STR_VAR_1} is on the lookout!");
static const u8 sNeutralMsg13[] = _("{STR_VAR_1} looked off into the\ndistance and barked!");

const struct FollowerMsgInfo gFollowerNeutralMessages[] = {
    {sNeutralMsg00, EventScript_FollowerPokeGround},
    {sNeutralMsg01},
    {sNeutralMsg02, EventScript_FollowerLookAway},
    {sNeutralMsg03, EventScript_FollowerLookAround},
    {sNeutralMsg04},
    {sNeutralMsg05, EventScript_FollowerLookAround},
    {sNeutralMsg06}, {sNeutralMsg07}, {sNeutralMsg08},
    {sNeutralMsg09, EventScript_FollowerDance},
    {sNeutralMsg10},
    {sNeutralMsg11, EventScript_FollowerLookAway},
    {sNeutralMsg12},
    {sNeutralMsg13, EventScript_FollowerLookAwayBark},
};

// Unconditional sad messages
static const u8 sSadMsg00[] = _("{STR_VAR_1} se ha mareado.");
static const u8 sSadMsg01[] = _("{STR_VAR_1} is stepping on your\nfeet!");
static const u8 sSadMsg02[] = _("{STR_VAR_1} parece que se cansa.");
// Conditional messages begin, index 3
static const u8 sSadMsg03[] = _("{STR_VAR_1} no está feliz.");
static const u8 sSadMsg04[] = _("¡{STR_VAR_1} está dando tumbos!\n");
static const u8 sSadMsg05[] = _("¡Parece que {STR_VAR_1}\nestá a punto de caerse!");
static const u8 sSadMsg06[] = _("{STR_VAR_1} hace un gran esfuerzo\n para seguirte el ritmo…");
static const u8 sSadMsg07[] = _("{STR_VAR_1} parece un manojo\nde nervios.");

const struct FollowerMsgInfo gFollowerSadMessages[] = {
    {sSadMsg00, EventScript_FollowerDizzy},
    {sSadMsg01}, {sSadMsg02},
    {sSadMsg03}, {sSadMsg04}, {sSadMsg05}, {sSadMsg06}, {sSadMsg07},
};

// Unconditional upset messages
static const u8 sUpsetMsg00[] = _("{STR_VAR_1} parece triste…");
static const u8 sUpsetMsg01[] = _("{STR_VAR_1} está haciendo pucheros…");
static const u8 sUpsetMsg02[] = _("{STR_VAR_1} está helándose…");
// Conditional messages, index 3
static const u8 sUpsetMsg03[] = _("{STR_VAR_1} se está cubriendo de la lluvia\ncon la hierba.");

const struct FollowerMsgInfo gFollowerUpsetMessages[] = {
    {sUpsetMsg00}, {sUpsetMsg01},
    {sUpsetMsg02, EventScript_FollowerIsShivering},
    {sUpsetMsg03},
};

// Unconditional angry messages
static const u8 sAngryMsg00[] = _("¡{STR_VAR_1} está rugiendo!");
static const u8 sAngryMsg01[] = _("¡{STR_VAR_1} está poniendo\ncara de enfado!");
static const u8 sAngryMsg02[] = _("A {STR_VAR_1} parece que\nalgo le enfada.");
static const u8 sAngryMsg03[] = _("{STR_VAR_1} te aparta la cara,\ndesafiante.");
static const u8 sAngryMsg04[] = _("{STR_VAR_1} está lloriqueando.");

const struct FollowerMsgInfo gFollowerAngryMessages[] = {
    {sAngryMsg00}, {sAngryMsg01}, {sAngryMsg02},
    {sAngryMsg03, EventScript_FollowerLookAway},
    {sAngryMsg04},
};

// Unconditional pensive messages
static const u8 sPensiveMsg00[] = _("{STR_VAR_1} is looking down\nsteadily.");
static const u8 sPensiveMsg01[] = _("{STR_VAR_1} is surveying the area.");
static const u8 sPensiveMsg02[] = _("{STR_VAR_1} is peering down.");
static const u8 sPensiveMsg03[] = _("{STR_VAR_1} is somehow fighting off\nsleep…");
static const u8 sPensiveMsg04[] = _("{STR_VAR_1} seems to be wandering\naround.");
static const u8 sPensiveMsg05[] = _("{STR_VAR_1} is looking around\nabsentmindedly.");
static const u8 sPensiveMsg06[] = _("{STR_VAR_1} yawned very loudly!");
static const u8 sPensiveMsg07[] = _("{STR_VAR_1} is relaxing comfortably.");
static const u8 sPensiveMsg08[] = _("{STR_VAR_1} is staring steadfastly\nat your face.");
static const u8 sPensiveMsg09[] = _("{STR_VAR_1} is staring intently at\nyour face.");
static const u8 sPensiveMsg10[] = _("{STR_VAR_1} is focusing its\nattention on you.");
static const u8 sPensiveMsg11[] = _("{STR_VAR_1} is staring into the\ndepths.");
static const u8 sPensiveMsg12[] = _("{STR_VAR_1} is sniffing at the\nground.");
static const u8 sPensiveMsg13[] = _("Your POKéMON is staring intently at\nnothing.");
static const u8 sPensiveMsg14[] = _("{STR_VAR_1} focused with a sharp\ngaze!");
static const u8 sPensiveMsg15[] = _("{STR_VAR_1} está concentrado.");
static const u8 sPensiveMsg16[] = _("{STR_VAR_1} faced this way and\nnodded.");
static const u8 sPensiveMsg17[] = _("{STR_VAR_1} parece nervioso…");
static const u8 sPensiveMsg18[] = _("{STR_VAR_1} mira tus pisadas.");
static const u8 sPensiveMsg19[] = _("{STR_VAR_1} te mira fijamente.");

const struct FollowerMsgInfo gFollowerPensiveMessages[] = {
    {sPensiveMsg00},
    {sPensiveMsg01, EventScript_FollowerLookAround},
    {sPensiveMsg02}, {sPensiveMsg03}, {sPensiveMsg04},
    {sPensiveMsg05, EventScript_FollowerLookAround},
    {sPensiveMsg06}, {sPensiveMsg07}, {sPensiveMsg08}, {sPensiveMsg09}, {sPensiveMsg10},
    {sPensiveMsg11, EventScript_FollowerLookAway},
    {sPensiveMsg12, EventScript_FollowerPokeGround},
    {sPensiveMsg13, EventScript_FollowerLookAway},
    {sPensiveMsg14}, {sPensiveMsg15}, {sPensiveMsg16}, {sPensiveMsg17}, {sPensiveMsg18}, {sPensiveMsg19},
};

// All 'love' messages are unconditional
static const u8 sLoveMsg00[] = _("{STR_VAR_1} suddenly started walking\ncloser!");
static const u8 sLoveMsg01[] = _("{STR_VAR_1} cheeks are becoming\nrosy!");
static const u8 sLoveMsg02[] = _("Woah! {STR_VAR_1} suddenly hugged\nyou!");
static const u8 sLoveMsg03[] = _("Woah! {STR_VAR_1} is suddenly\nplayful!");
static const u8 sLoveMsg04[] = _("{STR_VAR_1} is rubbing against your\nlegs!");
static const u8 sLoveMsg05[] = _("{STR_VAR_1} blushes.");
static const u8 sLoveMsg06[] = _("Ah! {STR_VAR_1} cuddles you!");
static const u8 sLoveMsg07[] = _("{STR_VAR_1} is regarding you with\nadoration!");
static const u8 sLoveMsg08[] = _("{STR_VAR_1} got closer to you.");
static const u8 sLoveMsg09[] = _("{STR_VAR_1} is keeping close to your\nfeet.");

const struct FollowerMsgInfo gFollowerLoveMessages[] = {
    {sLoveMsg00, EventScript_FollowerGetCloser},
    {sLoveMsg01},
    {sLoveMsg02, EventScript_FollowerCuddling},
    {sLoveMsg03},
    {sLoveMsg04, EventScript_FollowerCuddling},
    {sLoveMsg05},
    {sLoveMsg06, EventScript_FollowerCuddling},
    {sLoveMsg07},
    {sLoveMsg08, EventScript_FollowerGetCloser},
    {sLoveMsg09},
};

// Unconditional surprised messages
static const u8 sSurpriseMsg00[] = _("{STR_VAR_1} is in danger of falling\nover!");
static const u8 sSurpriseMsg01[] = _("{STR_VAR_1} bumped into you!");
static const u8 sSurpriseMsg02[] = _("{STR_VAR_1} no se acostumbra\na su nombre.");
static const u8 sSurpriseMsg03[] = _("{STR_VAR_1} is peering down.");
static const u8 sSurpriseMsg04[] = _("Your POKéMON stumbled and nearly\nfell!");
static const u8 sSurpriseMsg05[] = _("¡{STR_VAR_1} ha percibido algo\ny aúlla!");
static const u8 sSurpriseMsg06[] = _("¡{STR_VAR_1} parece revitalizado!");
static const u8 sSurpriseMsg07[] = _("{STR_VAR_1} suddenly turned around\nand started barking!");
static const u8 sSurpriseMsg08[] = _("{STR_VAR_1} suddenly turned around!");
static const u8 sSurpriseMsg09[] = _("Your POKéMON was surprised that you\nsuddenly spoke to it!");
static const u8 sSurpriseMsg10[] = _("Sniff sniff, something smells really\ngood!");
static const u8 sSurpriseMsg11[] = _("¡{STR_VAR_1} tiene energías\nrenovadas!");
static const u8 sSurpriseMsg12[] = _("{STR_VAR_1} is wobbling and seems\nabout to fall over.");
static const u8 sSurpriseMsg13[] = _("{STR_VAR_1} is in danger of falling\nover.");
static const u8 sSurpriseMsg14[] = _("{STR_VAR_1} is walking along\ncautiously.");
static const u8 sSurpriseMsg15[] = _("{STR_VAR_1} is getting tense with\nnervous energy.");
static const u8 sSurpriseMsg16[] = _("¡{STR_VAR_1} percibió algo extraño\ny le sorprendió!");
static const u8 sSurpriseMsg17[] = _("{STR_VAR_1} is scared and snuggled\nup to you!");
static const u8 sSurpriseMsg18[] = _("{STR_VAR_1} is feeling an unusual\npresence…");
static const u8 sSurpriseMsg19[] = _("{STR_VAR_1} is getting tense with\nnervous energy.");
// Conditional messages, index 20
static const u8 sSurpriseMsg20[] = _("¡{STR_VAR_1} parece sorprenderse\npor la lluvia!");

const struct FollowerMsgInfo gFollowerSurpriseMessages[] = {
    {sSurpriseMsg00},
    {sSurpriseMsg01, EventScript_FollowerPokingPlayer},
    {sSurpriseMsg02}, {sSurpriseMsg03}, {sSurpriseMsg04}, {sSurpriseMsg05}, {sSurpriseMsg06},
    {sSurpriseMsg07, EventScript_FollowerLookAwayBark},
    {sSurpriseMsg08, EventScript_FollowerLookAway},
    {sSurpriseMsg09},
    {sSurpriseMsg10, EventScript_FollowerLookAround},
    {sSurpriseMsg11}, {sSurpriseMsg12}, {sSurpriseMsg13}, {sSurpriseMsg14}, {sSurpriseMsg15}, {sSurpriseMsg16},
    {sSurpriseMsg17, EventScript_FollowerCuddling},
    {sSurpriseMsg18},
    {sSurpriseMsg19, EventScript_FollowerLookAround},
    {sSurpriseMsg20},
};

// Unconditional curious messages
static const u8 sCuriousMsg00[] = _("¡Parece que {STR_VAR_1}\nbusca algo desesperadamente!");
static const u8 sCuriousMsg01[] = _("Your POKéMON wasn't watching where\nit was going and ran into you!");
static const u8 sCuriousMsg02[] = _("{STR_VAR_1} no deja de olisquear\n¿Es que hay algo cerca?");
static const u8 sCuriousMsg03[] = _("{STR_VAR_1} is rolling a pebble\naround playfully.");
static const u8 sCuriousMsg04[] = _("{STR_VAR_1} mira alrededor\nbuscando algo…");
static const u8 sCuriousMsg05[] = _("{STR_VAR_1} te está olfateando.");
static const u8 sCuriousMsg06[] = _("{STR_VAR_1} seems to be a little\nhesitant…");

const struct FollowerMsgInfo gFollowerCuriousMessages[] = {
    {sCuriousMsg00, EventScript_FollowerLookAround},
    {sCuriousMsg01, EventScript_FollowerPokingPlayer},
    {sCuriousMsg02}, {sCuriousMsg03},
    {sCuriousMsg04, EventScript_FollowerLookAround},
    {sCuriousMsg05}, {sCuriousMsg06},
};

// Unconditional music messages
static const u8 sMusicMsg00[] = _("{STR_VAR_1} is showing off its\nagility!");
static const u8 sMusicMsg01[] = _("{STR_VAR_1} is moving around\nhappily!");
static const u8 sMusicMsg02[] = _("Woah! {STR_VAR_1} suddenly started\ndancing in happiness!");
static const u8 sMusicMsg03[] = _("{STR_VAR_1} is steadily keeping up\nwith you!");
static const u8 sMusicMsg04[] = _("{STR_VAR_1} seems to want to play\nwith you.");
static const u8 sMusicMsg05[] = _("{STR_VAR_1} is happy skipping about.");
static const u8 sMusicMsg06[] = _("{STR_VAR_1} is singing and humming.");
static const u8 sMusicMsg07[] = _("{STR_VAR_1} is nipping at your feet!");
static const u8 sMusicMsg08[] = _("{STR_VAR_1} turns around and looks\nat you.");
static const u8 sMusicMsg09[] = _("{STR_VAR_1} is working hard to show\noff its mighty power!");
static const u8 sMusicMsg10[] = _("Whoa! {STR_VAR_1} suddenly danced in\nhappiness!");
static const u8 sMusicMsg11[] = _("{STR_VAR_1} is cheerful!");
static const u8 sMusicMsg12[] = _("{STR_VAR_1} is jumping around in a\ncarefree way!");
static const u8 sMusicMsg13[] = _("Parece que a {STR_VAR_1} le\nha venido un olor familiar…");
// Conditional music messages, index 14
static const u8 sMusicMsg14[] = _("{STR_VAR_1} ama la lluvia.");

const struct FollowerMsgInfo gFollowerMusicMessages[] = {
    {sMusicMsg00, EventScript_FollowerLookAround},
    {sMusicMsg01},
    {sMusicMsg02, EventScript_FollowerDance},
    {sMusicMsg03},
    {sMusicMsg04, EventScript_FollowerHopping},
    {sMusicMsg05, EventScript_FollowerHopping},
    {sMusicMsg06}, {sMusicMsg07}, {sMusicMsg08}, {sMusicMsg09},
    {sMusicMsg10, EventScript_FollowerDance},
    {sMusicMsg11},
    {sMusicMsg12, EventScript_FollowerHopping},
    {sMusicMsg13, EventScript_FollowerNostalgia},
    {sMusicMsg14}
};


static const u8 sPoisonedMsg00[] = _("{STR_VAR_1} está temblando por los\nefectos del veneno.");

const struct FollowerMsgInfo gFollowerPoisonedMessages[] = {
    {sPoisonedMsg00, EventScript_FollowerIsShivering},
};
