// NOTE: Each of these macros turn data into one byte. Therefore ranges for all arguments is 0-15
// See struct TrainerHillFloorMap for more info about each
#define COORDS_XY(x,y)      ((y<<4)|(x))
#define TRAINER_DIRS(a, b)  (((a-1)<<4)|(b-1))
#define TRAINER_RANGE(a, b) ((a<<4)|(b))

// WARNING: While not referenced directly, the floor data in this file is referenced by virtue
//          of coming after its corresponding challenge (see SetUpDataStruct in trainer_hill.c).
//          Do not insert data between a pair of 'sChallenge_Mode' and 'sFloors_Mode'.

static const struct TrainerHillChallenge sChallenge_Normal =
{
    .numTrainers = NUM_TRAINER_HILL_TRAINERS,
    .numFloors = NUM_TRAINER_HILL_FLOORS,
    .checksum = 0x00051E05
};

static const struct TrainerHillChallenge sChallenge_Variety =
{
    .numTrainers = NUM_TRAINER_HILL_TRAINERS,
    .numFloors = NUM_TRAINER_HILL_FLOORS,
    .checksum = 0x00054C15
};

static const struct TrainerHillChallenge sChallenge_Unique =
{
    .numTrainers = NUM_TRAINER_HILL_TRAINERS,
    .numFloors = NUM_TRAINER_HILL_FLOORS,
    .checksum = 0x000652F3
};

static const struct TrainerHillChallenge sChallenge_Expert =
{
    .numTrainers = NUM_TRAINER_HILL_TRAINERS,
    .numFloors = NUM_TRAINER_HILL_FLOORS,
    .checksum = 0x00061F3F
};

#undef COORDS_XY
#undef TRAINER_DIRS
#undef TRAINER_RANGE
