#ifndef POKEPLATINUM_STRUCT_OV12_02237728_H
#define POKEPLATINUM_STRUCT_OV12_02237728_H

#include "struct_decls/battle_system.h"

#include "palette.h"
#include "sprite_system.h"

enum BallThrowMode {
    BALL_THROW_MODE_SEND_OUT = 0,
    BALL_THROW_MODE_SEND_OUT_QUICK,
    BALL_THROW_MODE_UNUSED,
    BALL_THROW_MODE_THROW,
    BALL_THROW_MODE_TRAINER_SEND_OUT,
    BALL_THROW_MODE_RECALL,
};

enum BallThrowType {
    BALL_THROW_TYPE_SOLO_PLAYER = 0,
    BALL_THROW_TYPE_SOLO_ENEMY,
    BALL_THROW_TYPE_PLAYER_SLOT_1,
    BALL_THROW_TYPE_ENEMY_SLOT_1,
    BALL_THROW_TYPE_PLAYER_SLOT_2,
    BALL_THROW_TYPE_ENEMY_SLOT_2,
    BALL_THROW_TYPE_6,
    BALL_THROW_TYPE_7,
    BALL_THROW_TYPE_8,
    BALL_THROW_TYPE_9,
    BALL_THROW_TYPE_10,
    BALL_THROW_TYPE_11,
    BALL_THROW_TYPE_12,
    BALL_THROW_TYPE_13,
    BALL_THROW_TYPE_14,
    BALL_THROW_TYPE_15,
    BALL_THROW_TYPE_16,
    BALL_THROW_TYPE_17,
};

typedef struct BallThrow {
    enum BallThrowType type;
    enum HeapID heapID;
    enum BallThrowMode mode;
    int target;
    int ballID;
    int bgPrio;
    int surface;
    SpriteSystem *spriteSys;
    PaletteData *paletteSys;
    BattleSystem *battleSys;
} BallThrow;

#endif // POKEPLATINUM_STRUCT_OV12_02237728_H
