#include "battle_anim/ov12_02235E94.h"

#include "nitro/hw/common/lcd.h"
#include <nitro.h>
#include <string.h>

#include "constants/battle.h"
#include "generated/items.h"

#include "struct_defs/seal_case.h"

#include "battle_anim/battle_anim_helpers.h"
#include "battle_anim/battle_anim_system.h"
#include "battle_anim/battle_anim_util.h"
#include "battle_anim/battle_particle_util.h"
#include "battle_anim/ov12_02237E54.h"
#include "battle_anim/struct_ov12_02223764.h"
#include "battle_anim/struct_ov12_02236030.h"
#include "battle_anim/struct_ov12_02236690.h"
#include "battle_anim/struct_ov12_02237728.h"

#include "heap.h"
#include "math_util.h"
#include "narc.h"
#include "palette.h"
#include "particle_system.h"
#include "pokemon.h"
#include "sound_playback.h"
#include "spl.h"
#include "sprite.h"
#include "sprite_resource.h"
#include "sprite_system.h"
#include "sprite_util.h"
#include "sys_task.h"
#include "sys_task_manager.h"
#include "unk_0202C9F4.h"
#include "unk_02097B18.h"

#include "res/graphics/battle/sprites.naix"

#define POKEBALL_ANIM_MAX_SPRITES   10
#define POKEBALL_ANIM_MAX_RESOURCES 10
#define POKEBALL_ANIM_BASE_RES_ID   6000

typedef struct {
    int unk_00;
    int unk_04;
    int unk_08;
    BOOL *unk_0C;
    ParticleSystem *unk_10;
    BallSeal *unk_14;
    SPLEmitterCallback unk_18;
} UnkStruct_02236430;

typedef struct BallCapsuleSealEffect_t {
    enum HeapID heapID;
    BallCapsuleConfig ballCapCfg;
    int sealCount;
    ParticleSystem *sealParticleSystems[9];
    BallSeal *seals[9];
    BOOL sealActiveFlags[9];
    SPLEmitter *emitter;
    SysTask *task;
    BOOL isActive;
    NARC *particleNarc;
    int state;
    int hasCapsule;
    int ballType;
    int capsuleID;
    BallCapsule capsule;
} BallCapsuleSealEffect;

typedef struct UnkStruct_ov12_02236648_t {
    UnkStruct_ov12_02236690 unk_00;
    SPLEmitter *unk_14;
    ParticleSystem *unk_18;
    int unk_1C;
    int unk_20;
} UnkStruct_ov12_02236648;

typedef struct BallThrowDesc {
    s16 startX;
    s16 startY;
    s16 endX;
    s16 endY;
    int frames;
    int curFrame;
    int radius;
} BallThrowDesc;

typedef struct PokeballAnim {
    int unk_00;
    int unk_04;
    int state;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    BOOL active;
    u8 unk_20;
    u8 unk_21;
    s8 unused;
    BOOL animate;
    BOOL unk_28;
    SpriteManager *spriteMan;
    ManagedSprite *sprite;
    ValueLerpContext unk_34;
    XYTransformContext pos[2];
    BallThrow ballThrow;
    BallThrowDesc desc;
    SysTask *unk_CC;
    UnkStruct_ov12_02236648 *unk_D0;
    PaletteFadeContext *unk_D4;
    BattleMonOBJData *unk_D8;
    int pauseTimer;
} PokeballAnim;

static void ov12_022363CC(SysTask *param0, void *param1);
static void ov12_0223646C(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1);
static void ov12_02236598(SPLEmitter *param0);
static void ov12_022365D4(SPLEmitter *param0);
static void PokeballAnim_LoadResources(PokeballAnim *param0);
static void PokeballAnim_CreateSprite(PokeballAnim *param0);
static void ov12_022378A0(PokeballAnim *param0);
static void PokeballAnim_GetBallStartPosition(PokeballAnim *param0, s16 *param1, s16 *param2);
static BOOL PokeballAnim_Task_SendOut(PokeballAnim *param0);
static BOOL ov12_022371E4(PokeballAnim *param0);
static BOOL ov12_02237608(PokeballAnim *param0);
static BOOL ov12_02236F10(PokeballAnim *param0);
static BOOL ov12_02237694(PokeballAnim *param0);
static BOOL ov12_02237474(PokeballAnim *param0);

// clang-format off
static const int sBallThrowGraphics[][4] = {
    { ball_throws_master_ball_NCGR_lz,  ball_throws_master_ball_NCLR,  ball_throws_shared_cell_NCER_lz_2,  ball_throws_shared_anim_NANR_lz_1          },
    { ball_throws_ultra_ball_NCGR_lz,   ball_throws_ultra_ball_NCLR,   ball_throws_shared_cell_NCER_lz_3,  ball_throws_shared_anim_NANR_lz_2          },
    { ball_throws_great_ball_NCGR_lz,   ball_throws_great_ball_NCLR,   ball_throws_shared_cell_NCER_lz_4,  ball_throws_shared_anim_NANR_lz_3          },
    { ball_throws_poke_ball_NCGR_lz,    ball_throws_poke_ball_NCLR,    ball_throws_shared_cell_NCER_lz_1,  ball_throws_shared_anim_NANR_lz            },
    { ball_throws_safari_ball_NCGR_lz,  ball_throws_safari_ball_NCLR,  ball_throws_shared_cell_NCER_lz_5,  ball_throws_shared_anim_NANR_lz_4          },
    { ball_throws_net_ball_NCGR_lz,     ball_throws_net_ball_NCLR,     ball_throws_shared_cell_NCER_lz_6,  ball_throws_shared_anim_NANR_lz_5          },
    { ball_throws_dive_ball_NCGR_lz,    ball_throws_dive_ball_NCLR,    ball_throws_shared_cell_NCER_lz_7,  ball_throws_shared_anim_NANR_lz_6          },
    { ball_throws_nest_ball_NCGR_lz,    ball_throws_nest_ball_NCLR,    ball_throws_shared_cell_NCER_lz_8,  ball_throws_shared_anim_NANR_lz_7          },
    { ball_throws_repeat_ball_NCGR_lz,  ball_throws_repeat_ball_NCLR,  ball_throws_shared_cell_NCER_lz_9,  ball_throws_shared_anim_NANR_lz_8          },
    { ball_throws_timer_ball_NCGR_lz,   ball_throws_timer_ball_NCLR,   ball_throws_shared_cell_NCER_lz_10, ball_throws_shared_anim_NANR_lz_9          },
    { ball_throws_luxury_ball_NCGR_lz,  ball_throws_luxury_ball_NCLR,  ball_throws_shared_cell_NCER_lz_11, ball_throws_shared_anim_NANR_lz_10         },
    { ball_throws_premier_ball_NCGR_lz, ball_throws_premier_ball_NCLR, ball_throws_shared_cell_NCER_lz_12, ball_throws_shared_anim_NANR_lz_11         },
    { ball_throws_dusk_ball_NCGR_lz,    ball_throws_dusk_ball_NCLR,    ball_throws_shared_cell_NCER_lz_14, ball_throws_quick_dusk_heal_anim_NANR_lz_1 },
    { ball_throws_heal_ball_NCGR_lz,    ball_throws_heal_ball_NCLR,    ball_throws_shared_cell_NCER_lz_15, ball_throws_quick_dusk_heal_anim_NANR_lz_2 },
    { ball_throws_quick_ball_NCGR_lz,   ball_throws_quick_ball_NCLR,   ball_throws_shared_cell_NCER_lz_13, ball_throws_quick_dusk_heal_anim_NANR_lz   },
    { ball_throws_cherish_ball_NCGR_lz, ball_throws_cherish_ball_NCLR, ball_throws_shared_cell_NCER_lz_16, ball_throws_shared_anim_NANR_lz_12         },
    { ball_throws_park_ball_NCGR_lz,    ball_throws_park_ball_NCLR,    ball_throws_shared_cell_NCER_lz_17, ball_throws_shared_anim_NANR_lz_13         },
    { ball_throws_mud_NCGR_lz,          ball_throws_mud_NCLR,          ball_throws_mud_cell_NCER_lz,       ball_throws_mud_anim_NANR_lz               },
    { ball_throws_bait_NCGR_lz,         ball_throws_bait_NCLR,         ball_throws_shared_cell_NCER_lz_18, ball_throws_bait_anim_NANR_lz              },
    { ball_throws_bait_NCGR_lz,         ball_throws_bait_NCLR,         ball_throws_shared_cell_NCER_lz_18, ball_throws_bait_anim_NANR_lz              },
};
// clang-format on

static const int Unk_ov12_0223AD70[][2] = {
    { 0x1, 0x5 },
    { 0x2, 0x4 },
    { 0x3, 0x3 },
    { 0x4, 0x3 },
    { 0x5, 0x3 },
    { 0x6, 0x4 },
    { 0x7, 0x3 },
    { 0x8, 0x4 },
    { 0x9, 0x3 },
    { 0xA, 0x5 },
    { 0xB, 0x4 },
    { 0xC, 0x3 },
    { 0xD, 0x3 },
    { 0xE, 0x3 },
    { 0xF, 0x4 },
    { 0x10, 0x4 },
    { 0x11, 0x3 },
    { 0x1, 0x5 },
    { 0x1, 0x5 },
    { 0x24, 0x2 }
};

static const int Unk_ov12_0223AE10[][3] = {
    { 0x13, 0x0, 0x5 },
    { 0x14, 0x2, 0x5 },
    { 0x15, 0x1, 0x5 },
    { 0x16, 0x3, 0x5 },
    { 0x17, 0x1, 0x5 },
    { 0x18, 0x1, 0x6 },
    { 0x19, 0x1, 0x5 },
    { 0x1A, 0x1, 0x5 },
    { 0x1B, 0x2, 0x5 },
    { 0x1C, 0x3, 0x7 },
    { 0x1D, 0x1, 0x6 },
    { 0x1E, 0x0, 0x5 },
    { 0x1F, 0x1, 0x5 },
    { 0x20, 0x0, 0x5 },
    { 0x21, 0x1, 0x6 },
    { 0x22, 0x1, 0x6 },
    { 0x23, 0x3, 0x5 },
    { 0x13, 0x0, 0x5 },
    { 0x13, 0x0, 0x5 },
    { 0x24, 0xFF, 0x2 }
};

static int ConvertItemIDToResourceIndex(enum Item item)
{
    enum Item converted;

    if (item < ITEM_MASTER_BALL || (item > ITEM_FOCUS_SASH)) {
        converted = ITEM_POKE_BALL;
    } else if (item >= ITEM_LAX_INCENSE) {
        converted = item - ITEM_LAX_INCENSE;
    } else {
        converted = item;
    }

    return converted - ITEM_MASTER_BALL;
}

static BOOL BallShouldRotate(enum BallThrowType throwType)
{
    enum BallThrowType throwTypes[] = {
        BALL_THROW_TYPE_6,
        BALL_THROW_TYPE_7,
        BALL_THROW_TYPE_8,
        BALL_THROW_TYPE_9,
        BALL_THROW_TYPE_10,
        BALL_THROW_TYPE_11,
        BALL_THROW_TYPE_12,
        BALL_THROW_TYPE_13,
        BALL_THROW_TYPE_15,
        BALL_THROW_TYPE_16,
        BALL_THROW_TYPE_17,
    };

    BOOL hasRandomRotation = FALSE;

    for (int i = 0; i < NELEMS(throwTypes); i++) {
        if (throwTypes[i] != throwType) {
            continue;
        }

        hasRandomRotation = TRUE;
        break;
    }

    return hasRandomRotation;
}

static BOOL ov12_02235EF0(enum BallThrowType throwType)
{
    enum BallThrowType throwTypes[] = {
        BALL_THROW_TYPE_6,
        BALL_THROW_TYPE_7,
        BALL_THROW_TYPE_8,
        BALL_THROW_TYPE_9,
        BALL_THROW_TYPE_10,
        BALL_THROW_TYPE_11,
    };

    BOOL v1 = FALSE;

    for (int i = 0; i < NELEMS(throwTypes); i++) {
        if (throwTypes[i] != throwType) {
            continue;
        }

        v1 = TRUE;
        break;
    }

    return v1;
}

static BOOL ShouldAnimatePokeball(enum BallThrowType throwType)
{
    enum BallThrowType throwTypes[] = {
        BALL_THROW_TYPE_ENEMY_SLOT_1,
        BALL_THROW_TYPE_ENEMY_SLOT_2,
        BALL_THROW_TYPE_SOLO_ENEMY,
    };

    BOOL animate = TRUE;

    for (int i = 0; i < NELEMS(throwTypes); i++) {
        if (throwTypes[i] != throwType) {
            continue;
        }

        animate = FALSE;
        break;
    }

    return animate;
}

static int ov12_02235F64(int param0)
{
    int v0 = ConvertItemIDToResourceIndex(param0);
    return Unk_ov12_0223AD70[v0][0];
}

static int ov12_02235F78(int param0)
{
    int v0 = ConvertItemIDToResourceIndex(param0);
    return Unk_ov12_0223AD70[v0][1];
}

static int ov12_02235F8C(int param0)
{
    int v0 = ConvertItemIDToResourceIndex(param0);
    return Unk_ov12_0223AE10[v0][0];
}

static int ov12_02235FA0(int param0)
{
    int v0 = ConvertItemIDToResourceIndex(param0);
    return Unk_ov12_0223AE10[v0][2];
}

static int ov12_02235FB4(int param0)
{
    int v0 = ConvertItemIDToResourceIndex(param0);
    return Unk_ov12_0223AE10[v0][1];
}

static int GetPokeballGraphics(enum Item item, enum SpriteResourceType type)
{
    int index = ConvertItemIDToResourceIndex(item);
    return sBallThrowGraphics[index][type];
}

BallCapsuleSealEffect *ov12_02235FE0(enum HeapID heapID)
{
    BallCapsuleSealEffect *ballCapSealEff = NULL;

    ballCapSealEff = Heap_Alloc(heapID, sizeof(BallCapsuleSealEffect));

    if (ballCapSealEff == NULL) {
        GF_ASSERT(FALSE);
        return NULL;
    }

    ballCapSealEff->heapID = heapID;
    ballCapSealEff->isActive = 0;

    return ballCapSealEff;
}

BallCapsuleSealEffect *ov12_02236004(enum HeapID heapID, const BallCapsuleConfig *ballCapCfg)
{
    BallCapsuleSealEffect *ballCapSealEff = NULL;

    ballCapSealEff = ov12_02235FE0(heapID);
    ov12_02236030(ballCapSealEff, ballCapCfg);

    {
        int v1;

        ballCapSealEff->sealCount = 0;

        for (v1 = 0; v1 < 9; v1++) {
            ballCapSealEff->sealParticleSystems[v1] = NULL;
            ballCapSealEff->seals[v1] = NULL;
            ballCapSealEff->sealActiveFlags[v1] = 0;
        }
    }

    return ballCapSealEff;
}

void ov12_02236030(BallCapsuleSealEffect *ballCapSealEff, const BallCapsuleConfig *ballCapCfgPtr)
{
    ballCapSealEff->ballCapCfg = *ballCapCfgPtr;
    ballCapSealEff->capsuleID = Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_BALL_CAPSULE_ID, NULL);

    GF_ASSERT(ballCapSealEff->capsuleID < 12 + 1);

    if (ballCapSealEff->capsuleID == 0) {
        ballCapSealEff->hasCapsule = 0;

        if (ballCapSealEff->ballCapCfg.ballTypeOverride != 0) {
            ballCapSealEff->ballType = ballCapSealEff->ballCapCfg.ballTypeOverride;
        } else {
            ballCapSealEff->ballType = Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_POKEBALL, NULL);
        }
    } else {
        ballCapSealEff->hasCapsule = 1;
        Pokemon_GetValue(ballCapSealEff->ballCapCfg.mon, MON_DATA_BALL_CAPSULE, &ballCapSealEff->capsule);
    }
}

static void ov12_022360A0(SysTask *param0, void *ballCapSealEffPtr)
{
    BallCapsuleSealEffect *ballCapSealEff = ballCapSealEffPtr;
    int i;
    int v2;
    int v3;
    int v4;
    BallSeal *v5;

    switch (ballCapSealEff->state) {
    case 0:
        ballCapSealEff->particleNarc = NARC_ctor(NARC_INDEX_WAZAEFFECT__EFFECTDATA__BALL_PARTICLE, ballCapSealEff->heapID);

        for (i = 0; i < 2; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= SEAL_ID_MAX) {
                continue;
            }

            v3 = sub_02098188(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 1:
        for (i = 2; i < 4; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = sub_02098188(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 2:
        for (i = 4; i < 6; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = sub_02098188(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state++;
        break;
    case 3:
        for (i = 6; i < 8; i++) {
            v5 = BallCapsule_GetBallSeals(&ballCapSealEff->capsule, i);

            if (v5 == NULL) {
                continue;
            }

            v2 = BallSeal_GetSealType(v5);

            if (v2 == 0) {
                continue;
            }

            if (v2 >= (80 + 1)) {
                continue;
            }

            v3 = sub_02098188(v2);

            ballCapSealEff->seals[ballCapSealEff->sealCount] = v5;
            GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL);
            ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] = BattleParticleUtil_CreateParticleSystemFromOpenNarc(ballCapSealEff->particleNarc, ballCapSealEff->heapID, v3, 0);

            if (ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] == NULL) {
                GF_ASSERT(ballCapSealEff->sealParticleSystems[ballCapSealEff->sealCount] != NULL);
                continue;
            }

            ballCapSealEff->sealCount++;
        }

        ballCapSealEff->state = 0xFF;

        NARC_dtor(ballCapSealEff->particleNarc);
        SysTask_Done(param0);
        break;
    default:
        break;
    }
}

void ov12_02236320(BallCapsuleSealEffect *ballCapSealEff)
{
    int v0;
    int v1;
    int v2;
    int v3;
    BallSeal *v4;

    if (ballCapSealEff->hasCapsule == 0) {
        v3 = ov12_02235F64(ballCapSealEff->ballType);

        ballCapSealEff->sealCount = 1;
        ballCapSealEff->sealParticleSystems[0] = BattleParticleUtil_CreateParticleSystemEx(ballCapSealEff->heapID, 99, v3, 0);
        ballCapSealEff->state = 0xFF;
    } else {
        ballCapSealEff->sealCount = 0;
        ballCapSealEff->state = 0;

        {
            SysTask *v5;

            v5 = SysTask_Start(ov12_022360A0, ballCapSealEff, 1000);
            ov12_022360A0(v5, ballCapSealEff);
        }
    }
}

BOOL ov12_02236374(BallCapsuleSealEffect *ballCapSealEff)
{
    if (ballCapSealEff->state == 0xFF) {
        return 1;
    }

    return 0;
}

void ov12_02236384(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1)
{
    ballCapSealEff->isActive = 1;

    BattleAnimSystem_SetDefaultAlphaBlending();
    ov12_0223646C(ballCapSealEff, param1);

    ballCapSealEff->task = SysTask_Start(ov12_022363CC, ballCapSealEff, 1000);
}

void ov12_022363B4(BallCapsuleSealEffect *ballCapSealEff)
{
    ov12_02236384(ballCapSealEff, ov12_02236598);
}

BOOL ov12_022363C4(BallCapsuleSealEffect *ballCapSealEff)
{
    return ballCapSealEff->isActive;
}

static void ov12_022363CC(SysTask *param0, void *ballCapSealEffPtr)
{
    int v0;
    BOOL v1;
    BallCapsuleSealEffect *ballCapSealEff = (BallCapsuleSealEffect *)ballCapSealEffPtr;

    v1 = 0;

    GF_ASSERT(ballCapSealEff->sealCount <= 9);

    for (v0 = 0; v0 < ballCapSealEff->sealCount; v0++) {
        if (ballCapSealEff->sealParticleSystems[v0] == NULL) {
            continue;
        }

        if ((ParticleSystem_GetActiveEmitterCount(ballCapSealEff->sealParticleSystems[v0]) == 0) && (ballCapSealEff->sealActiveFlags[v0] != 0)) {
            BattleParticleUtil_FreeParticleSystem(ballCapSealEff->sealParticleSystems[v0]);
            ballCapSealEff->sealParticleSystems[v0] = NULL;
            ballCapSealEff->sealActiveFlags[v0] = 0;
            continue;
        }

        v1 = 1;
    }

    if (v1 == 0) {
        ballCapSealEff->isActive = 0;
        SysTask_Done(param0);
    }
}

void ov12_02236428(BallCapsuleSealEffect *ballCapSealEff)
{
    Heap_Free(ballCapSealEff);
}

static void ov12_02236430(SysTask *param0, void *param1)
{
    UnkStruct_02236430 *v0 = (UnkStruct_02236430 *)param1;

    if (v0->unk_04 == 0) {
        *(v0->unk_0C) = 1;
        ParticleSystem_CreateEmitterWithCallback(v0->unk_10, 0, v0->unk_18, v0);
        ParticleSystem_SetCameraProjection(v0->unk_10, 1);
        SysTask_Done(param0);
        Heap_Free(v0);
    } else {
        v0->unk_04--;
    }
}

static void ov12_0223646C(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1)
{
    int v0, v1;
    int v2;
    int v3;

    if (ballCapSealEff->hasCapsule == 0) {
        v3 = ov12_02235F78(ballCapSealEff->ballType);

        for (v0 = 0; v0 < v3; v0++) {
            ParticleSystem_CreateEmitterWithCallback(ballCapSealEff->sealParticleSystems[0], v0, param1, ballCapSealEff);
        }

        ballCapSealEff->sealActiveFlags[0] = 1;
        ParticleSystem_SetCameraProjection(ballCapSealEff->sealParticleSystems[0], 1);
    } else {
        for (v0 = 0; v0 < ballCapSealEff->sealCount; v0++) {
            UnkStruct_02236430 *v4 = Heap_Alloc(ballCapSealEff->heapID, sizeof(UnkStruct_02236430));

            GF_ASSERT(v4 != NULL);

            v4->unk_00 = v0;
            v4->unk_08 = ballCapSealEff->ballCapCfg.battlerType;
            v4->unk_18 = ov12_022365D4;

            ballCapSealEff->sealActiveFlags[v0] = 0;

            v4->unk_0C = &ballCapSealEff->sealActiveFlags[v0];
            v4->unk_10 = ballCapSealEff->sealParticleSystems[v0];
            v4->unk_14 = ballCapSealEff->seals[v0];

            GF_ASSERT(v4->unk_14 != NULL);
            v4->unk_04 = ov12_02237EA0(v4->unk_14);

            SysTask_Start(ov12_02236430, v4, 1001);
        }
    }
}

static void ov12_02236520(int param0, VecFx32 *param1)
{
    BattleAnimUtil_GetBattlerTypeWorldPos(param0, param1, 0, 1);

    {
        int v0;
        int v1;
        s16 v2;
        s16 v3;
        VecFx32 v4;

        switch (param0) {
        case 0:
            v2 = 0;
            v3 = -16;
            break;
        case 1:
            v2 = -15;
            v3 = -25;
            break;
        case 2:
            v2 = -8;
            v3 = -12;
            break;
        case 3:
            v2 = -14;
            v3 = -25;
            break;
        case 4:
            v2 = -8;
            v3 = -12;
            break;
        case 5:
        default:
            v2 = -16;
            v3 = -29;
            break;
        }

        v0 = 172 * ((+10) + v2);
        v1 = 172 * (32 + v3);

        VEC_Set(&v4, v0, v1, 0);

        param1->x -= v4.x;
        param1->y -= v4.y;
    }
}

static void ov12_02236598(SPLEmitter *param0)
{
    int v0;
    BallCapsuleSealEffect *ballCapSealEff = ParticleSystem_GetEmitterCallbackParam();
    v0 = ballCapSealEff->ballCapCfg.battlerType;

    {
        VecFx32 v2;

        ov12_02236520(v0, &v2);
        SPLEmitter_SetPos(param0, &v2);
    }
}

static void ov12_022365D4(SPLEmitter *param0)
{
    VecFx32 v0;
    int v1;
    BallCapsuleSealEffect *unused;
    UnkStruct_02236430 *v3 = ParticleSystem_GetEmitterCallbackParam();
    v1 = v3->unk_08;

    ov12_02236520(v1, &v0);

    {
        u8 v4;
        u8 v5, v6;
        s16 v7, v8;
        int v9, v10;
        VecFx32 v11;

        v4 = BallSeal_GetSealType(v3->unk_14);

        if (sub_020981AC(v4) == 1) {
            v5 = BallSeal_GetX(v3->unk_14);
            v6 = BallSeal_GetY(v3->unk_14);
            v7 = (v5 - 190);
            v8 = (70 - v6 + (+30));
            v9 = v7 * 172;
            v10 = v8 * 172;

            VEC_Set(&v11, v9, v10, 0);

            v0.x += v11.x;
            v0.y += v11.y;
            v0.z += v11.z;
        } else {
            v5 = BallSeal_GetX(v3->unk_14);
            v6 = BallSeal_GetY(v3->unk_14);
            v7 = (v5 - 190);
            v8 = (70 - v6 + (+30));
            v9 = v7 * 172;
            v10 = v8 * 172;

            VEC_Set(&v11, v9, v10, 0);

            v0.x += v11.x;
            v0.y += v11.y;
            v0.z += v11.z;
        }
    }

    SPLEmitter_SetPos(param0, &v0);
}

static void ov12_02236648(SPLEmitter *param0)
{
    UnkStruct_ov12_02236648 *v0 = ParticleSystem_GetEmitterCallbackParam();

    {
        VecFx32 v1;
        int v2, v3;
        s16 v4, v5;

        v4 = (v0->unk_00.unk_00 - 190 + 61);
        v5 = (70 - v0->unk_00.unk_02 + (+30));
        v2 = v4 * 172;
        v3 = v5 * 172;

        VEC_Set(&v1, v2, v3, 0);
        SPLEmitter_SetPos(param0, &v1);
    }
}

UnkStruct_ov12_02236648 *ov12_02236690(UnkStruct_ov12_02236690 *param0)
{
    UnkStruct_ov12_02236648 *v0 = Heap_Alloc(param0->heapID, sizeof(UnkStruct_ov12_02236648));
    GF_ASSERT(v0 != NULL);

    v0->unk_00 = *param0;

    if (v0->unk_00.unk_10) {
        v0->unk_20 = ov12_02235F8C(0xFF + 20);
        v0->unk_1C = ov12_02235FA0(0xFF + 20);
    } else {
        v0->unk_20 = ov12_02235F8C(v0->unk_00.unk_04);
        v0->unk_1C = ov12_02235FA0(v0->unk_00.unk_04);
    }

    v0->unk_18 = BattleParticleUtil_CreateParticleSystemEx(v0->unk_00.heapID, 99, v0->unk_20, 0);

    return v0;
}

void ov12_022366F0(UnkStruct_ov12_02236648 *param0)
{
    int v0;
    int v1;
    UnkStruct_ov12_02236648 *v2 = param0;

    if (v2->unk_00.unk_0C == 0xFF) {
        if (v2->unk_00.unk_10) {
            for (v0 = 0; v0 < v2->unk_1C; v0++) {
                ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v0, ov12_02236648, v2);
            }
        } else {
            for (v0 = 0; v0 < v2->unk_1C; v0++) {
                if (v0 == ov12_02235FB4(v2->unk_00.unk_04)) {
                    continue;
                }

                ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v0, ov12_02236648, v2);
            }
        }
    } else {
        v1 = v2->unk_00.unk_0C;
        ParticleSystem_CreateEmitterWithCallback(v2->unk_18, v1, ov12_02236648, v2);
    }

    ParticleSystem_SetCameraProjection(v2->unk_18, 1);
}

BOOL ov12_02236764(UnkStruct_ov12_02236648 *param0)
{
    UnkStruct_ov12_02236648 *v0 = param0;

    if (ParticleSystem_GetActiveEmitterCount(v0->unk_18) == 0) {
        BattleParticleUtil_FreeParticleSystem(v0->unk_18);
        return 0;
    }

    return 1;
}

void ov12_02236780(UnkStruct_ov12_02236648 *param0)
{
    Heap_Free(param0);
}

static BOOL (*const sBallThrowTaskFuncs[])(PokeballAnim *) = {
    [BALL_THROW_MODE_SEND_OUT] = PokeballAnim_Task_SendOut,
    [BALL_THROW_MODE_SEND_OUT_QUICK] = ov12_022371E4,
    [BALL_THROW_MODE_UNUSED] = ov12_02237608,
    [BALL_THROW_MODE_THROW] = ov12_02236F10,
    [BALL_THROW_MODE_TRAINER_SEND_OUT] = ov12_02237694,
    [BALL_THROW_MODE_RECALL] = ov12_02237474
};

static BOOL ov12_02236788(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 1);
    }

    v0 = ov12_0223782C(param0, 2);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_022367B0(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 3);
    }

    v0 = ov12_0223782C(param0, 4);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_022367D8(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 5);
    }

    v0 = ov12_0223782C(param0, 6);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_02236800(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 7);
    }

    v0 = ov12_0223782C(param0, 14);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_02236828(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 15);
    }

    v0 = ov12_0223782C(param0, 18);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_02236850(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 19);
    }

    v0 = ov12_0223782C(param0, 27);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_02236878(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 21);
    }

    v0 = ov12_0223782C(param0, 22);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL ov12_022368A0(PokeballAnim *param0)
{
    BOOL v0;

    if (param0->unk_04 == 0) {
        param0->unk_04++;
        ov12_02237828(param0, 23);
    }

    v0 = ov12_0223782C(param0, 27);

    if (v0 == 1) {
        return 0;
    }

    return 1;
}

static BOOL (*const Unk_ov12_0223AB9C[])(PokeballAnim *) = {
    ov12_02236788,
    ov12_022367B0,
    ov12_022367D8,
    ov12_02236800,
    ov12_02236828,
    ov12_02236850,
    ov12_02236878,
    ov12_022368A0
};

void ov12_022368C8(PokeballAnim *param0, int param1)
{
    param0->unk_00 = param1;
    param0->unk_04 = 0;
}

BOOL ov12_022368D0(PokeballAnim *param0, int param1)
{
    BOOL v0 = Unk_ov12_0223AB9C[param0->unk_00](param0);
    return v0;
}

static void ov12_022368E4(PokeballAnim *param0, int param1)
{
    param0->unk_14 = param1;
    param0->state = 0;
    param0->unk_0C = 0;
    param0->unk_10 = 0;
}

static BOOL ov12_022368F0(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_022368F4(PokeballAnim *param0)
{
    BOOL v0 = PokeballAnim_Task_SendOut(param0);

    if (v0 == 0) {
        ov12_022368E4(param0, 2);
    }

    return 1;
}

static BOOL ov12_0223690C(PokeballAnim *param0)
{
    ov12_022368E4(param0, 3);
    return 1;
}

static BOOL ov12_02236918(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        ManagedSprite_SetAnim(param0->sprite, 1);
        {
            UnkStruct_ov12_02236690 v0;

            v0.unk_04 = param0->ballThrow.ballID;
            v0.heapID = param0->ballThrow.heapID;
            v0.unk_0C = 0xFF;
            v0.unk_10 = 0;

            ManagedSprite_GetPositionXY(param0->sprite, &v0.unk_00, &v0.unk_02);

            param0->unk_D8 = BattleMonOBJData_NewAll(param0->ballThrow.battleSys, param0->ballThrow.heapID);
            param0->unk_D0 = ov12_02236690(&v0);
        }
        param0->state++;
        break;
    case 1: {
        int v1 = ManagedSprite_GetAnimationFrame(param0->sprite);

        if (v1 >= 2) {
            param0->animate = 0;
            param0->state++;
        }
    } break;
    case 2:
        ov12_022366F0(param0->unk_D0);
        BattleMonOBJData_Free(param0->unk_D8);
        param0->state++;
        break;
    case 3: {
        if (ov12_02236764(param0->unk_D0) == 0) {
            ManagedSprite_SetAnimationFrame(param0->sprite, 0);
            ov12_02236780(param0->unk_D0);
            param0->state++;
        }
    } break;
    default:
        ov12_022368E4(param0, 4);
        break;
    }

    return 1;
}

static BOOL ov12_022369F8(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_022369FC(PokeballAnim *param0)
{
    BOOL v0;

    switch (param0->unk_0C) {
    case 0:
        ManagedSprite_GetPositionXY(param0->sprite, &param0->desc.startX, &param0->desc.startY);
        param0->desc.endX = 60;
        param0->desc.endY = 180;
        param0->desc.frames = 10;
        param0->desc.radius = 12;
        param0->unk_0C++;
        break;
    default: {
        v0 = PokeballAnim_Task_SendOut(param0);

        if (v0 == 0) {
            ov12_022368E4(param0, 6);
        }
    } break;
    }

    return 1;
}

static BOOL ov12_02236A50(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_02236A54(PokeballAnim *param0)
{
    ov12_022368E4(param0, 8);
    return 1;
}

static BOOL ov12_02236A60(PokeballAnim *param0)
{
    ov12_022368E4(param0, 9);
    return 1;
}

static BOOL ov12_02236A6C(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:

    {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
        PaletteData_StartFade(param0->ballThrow.paletteSys, 0x4, 1 << v0, -1, 0, 12, 0x37F);

        param0->state++;
    } break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->ballThrow.paletteSys) != 0) {
            break;
        }

        {
            int v1;

            v1 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
            PaletteData_StartFade(param0->ballThrow.paletteSys, 0x4, 1 << v1, -1, 12, 0, 0x37F);
        }

        param0->state++;
        break;
    default:
        if (PaletteData_GetSelectedBuffersMask(param0->ballThrow.paletteSys) != 0) {
            break;
        }

        ov12_022368E4(param0, 10);
        break;
    }

    return 1;
}

static BOOL ov12_02236B14(PokeballAnim *param0)
{
    ov12_022368E4(param0, 11);
    return 1;
}

static BOOL ov12_02236B20(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        if ((++param0->unk_0C) < 1) {
            break;
        }

        {
            s16 v0, v1;

            ManagedSprite_GetPositionXY(param0->sprite, &v0, &v1);
            PosLerpContext_Init(&param0->pos[0], v0, v0, v1, v1 + 32, 32 / 3);

            param0->state++;
        }
        break;
    case 1:
        if (PosLerpContext_UpdateAndApplyToSprite(&param0->pos[0], param0->sprite) == 0) {
            param0->state++;

            ov12_022368E4(param0, 13);
        }
        break;
    default:
        break;
    }

    return 1;
}

static BOOL ov12_02236B94(PokeballAnim *param0)
{
    return 1;
}

static const s16 Unk_ov12_0223ACF0[][3] = {
    { 0x0, -7, 0x1 },
    { 0x1, -5, 0x0 },
    { 0x0, -3, 0x0 },
    { 0x1, -2, 0x0 },
    { 0x1, 0x2, 0x0 },
    { 0x1, 0x3, 0x0 },
    { 0x0, 0x5, 0x0 },
    { 0x1, 0x7, 0x1 },
    { 0x0, -5, 0x1 },
    { 0x0, -3, 0x0 },
    { 0x1, -2, 0x0 },
    { 0x1, 0x2, 0x0 },
    { 0x0, 0x3, 0x0 },
    { 0x0, 0x5, 0x1 },
    { 0x0, -2, 0x0 },
    { 0x1, -1, 0x0 },
    { 0x0, 0x1, 0x0 },
    { 0x0, 0x2, 0x0 },
    { 0x0, -2, 0x1 },
    { 0x0, 0x2, 0x1 },
    { 0xFF, 0xFF, 0x0 }
};

static const int Unk_ov12_0223ABE4[][2] = {
    { 0x1, SEQ_SE_DP_KON },
    { 0x8, SEQ_SE_DP_KON },
    { 0xE, SEQ_SE_DP_KON2 },
    { 0x12, SEQ_SE_DP_KON3 },
    { 0x14, SEQ_SE_DP_KON4 }
};

static BOOL ov12_02236B98(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        ManagedSprite_SetAnim(param0->sprite, 1);
        ManagedSprite_SetAnimationFrame(param0->sprite, 0);
        param0->state++;
    case 1: {
        s16 v0, v1;
        int v2;

        v0 = 0;
        v1 = Unk_ov12_0223ACF0[param0->unk_0C][1];
        v2 = Unk_ov12_0223ACF0[param0->unk_0C][2];

        ManagedSprite_SetAnimationFrame(param0->sprite, v2);

        param0->unk_0C++;

        {
            int v3;

            for (v3 = 0; v3 < 5; v3++) {
                if (Unk_ov12_0223ABE4[v3][0] == param0->unk_0C) {
                    Sound_PlayPannedEffect(Unk_ov12_0223ABE4[v3][1], 117);
                }
            }
        }

        if ((param0->unk_0C > 20) || (v0 == 0xFF) || (v1 == 0xFF)) {
            param0->state++;
        } else {
            ManagedSprite_OffsetPositionXY(param0->sprite, v0, v1);
        }
    } break;
    default:
        ov12_022368E4(param0, 14);
        break;
    }

    return 1;
}

static BOOL ov12_02236C34(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_02236C38(PokeballAnim *param0)
{
    param0->unk_0C++;

    if (param0->unk_0C >= 14) {
        param0->state++;
        param0->unk_0C = 0;
        ov12_022368E4(param0, 16);
    }

    return 1;
}

static BOOL ov12_02236C58(PokeballAnim *param0)
{
    ov12_022368E4(param0, 17);
    return 1;
}

static const s16 Unk_ov12_0223AC38[][12] = {
    { -2, -0, 0x2, 0x2, 0x0, -2, 0xFF, 0xFF, 0xFF },
    { -1, -0, 0x1, 0x1, 0x0, -1, 0xFF, 0xFF, 0xFF },
    { -1, 0x0, 0x1, 0x1, 0x0, -1, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF }
};

static BOOL ov12_02236C64(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        GF_ASSERT(param0->unk_18 < 3);
        param0->state++;
    case 1: {
        s16 v0;

        v0 = Unk_ov12_0223AC38[param0->unk_18][param0->unk_0C];
        param0->unk_0C++;

        if ((param0->unk_0C > 11) || (v0 == 0xFF)) {
            param0->state++;
            param0->unk_18++;
            ManagedSprite_SetAffineZRotation(param0->sprite, 0);
            ov12_022368E4(param0, 18);
            return 1;
        } else {
            if (param0->unk_0C == 5) {
                Sound_PlayPannedEffect(SEQ_SE_DP_BOWA, 117);
            }

            ManagedSprite_OffsetPositionXY(param0->sprite, v0, 0);
            ManagedSprite_OffsetAffineZRotation(param0->sprite, (((v0) * 2) * 0xffff) / 360);
        }
    } break;
    default:
        break;
    }

    return 1;
}

static BOOL ov12_02236CFC(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_02236D00(PokeballAnim *param0)
{
    ov12_022368E4(param0, 20);
    return 1;
}

static BOOL ov12_02236D0C(PokeballAnim *param0)
{
    ov12_022368E4(param0, 27);
    return 1;
}

static BOOL ov12_02236D18(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:

    {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
        PaletteData_StartFade(param0->ballThrow.paletteSys, 0x4, 1 << v0, -5, 0, 10, 0x0);

        param0->state++;
    } break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->ballThrow.paletteSys) != 0) {
            break;
        }

        {
            UnkStruct_ov12_02236690 v1;

            v1.unk_04 = param0->ballThrow.ballID;
            v1.heapID = param0->ballThrow.heapID;
            v1.unk_0C = ov12_02235FB4(v1.unk_04);
            v1.unk_10 = 0;

            ManagedSprite_GetPositionXY(param0->sprite, &v1.unk_00, &v1.unk_02);
            param0->unk_D0 = ov12_02236690(&v1);
        }
        param0->state++;
        break;
    case 2:
        ov12_022366F0(param0->unk_D0);
        param0->state++;
        break;
    case 3: {
        if (ov12_02236764(param0->unk_D0) == 0) {
            ManagedSprite_SetAnimationFrame(param0->sprite, 0);
            ov12_02236780(param0->unk_D0);
            param0->state++;
        }
    } break;
    default:
        if (PaletteData_GetSelectedBuffersMask(param0->ballThrow.paletteSys) != 0) {
            break;
        }

        ov12_022368E4(param0, 22);
        break;
    }

    return 1;
}

static BOOL ov12_02236E08(PokeballAnim *param0)
{
    return 1;
}

static BOOL ov12_02236E0C(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0: {
        int v0;

        v0 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
        PaletteData_StartFade(param0->ballThrow.paletteSys, 0x4, 1 << v0, -5, 10, 0, 0x0);
    }
        param0->state++;
        break;
    case 1:
        if (PaletteData_GetSelectedBuffersMask(param0->ballThrow.paletteSys) != 0) {
            break;
        }

        param0->state++;
        break;
    default:
        ov12_022368E4(param0, 24);
        break;
    }

    return 1;
}

static BOOL ov12_02236E70(PokeballAnim *param0)
{
    ov12_022368E4(param0, 25);
    return 1;
}

static BOOL ov12_02236E7C(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        ManagedSprite_SetExplicitOamMode(param0->sprite, GX_OAM_MODE_XLU);
        param0->state++;
    case 1:
        if (param0->unk_20 > 0) {
            param0->unk_20--;
            param0->unk_21++;
        } else {
            param0->unk_20 = 0;
            param0->unk_21 = 15;
            ManagedSprite_SetDrawFlag(param0->sprite, 0);
            param0->state++;
        }

        G2_ChangeBlendAlpha(param0->unk_20, param0->unk_21);
        break;
    default:
        ov12_022368E4(param0, 26);
        break;
    }

    return 1;
}

static BOOL ov12_02236F00(PokeballAnim *param0)
{
    ov12_022368E4(param0, 27);
    return 1;
}

static BOOL ov12_02236F0C(PokeballAnim *param0)
{
    return 0;
}

static BOOL (*const Unk_ov12_0223AC80[])(PokeballAnim *) = {
    ov12_022368F0,
    ov12_022368F4,
    ov12_0223690C,
    ov12_02236918,
    ov12_022369F8,
    ov12_022369FC,
    ov12_02236A50,
    ov12_02236A54,
    ov12_02236A60,
    ov12_02236A6C,
    ov12_02236B14,
    ov12_02236B20,
    ov12_02236B94,
    ov12_02236B98,
    ov12_02236C34,
    ov12_02236C38,
    ov12_02236C58,
    ov12_02236C64,
    ov12_02236CFC,
    ov12_02236D00,
    ov12_02236D0C,
    ov12_02236D18,
    ov12_02236E08,
    ov12_02236E0C,
    ov12_02236E70,
    ov12_02236E7C,
    ov12_02236F00,
    ov12_02236F0C
};

static BOOL ov12_02236F10(PokeballAnim *param0)
{
    BOOL v0 = Unk_ov12_0223AC80[param0->unk_14](param0);
    return v0;
}

static BOOL PokeballAnim_Task_SendOut(PokeballAnim *anim)
{
    switch (anim->state) {
    case 0:
        XYTransformContext_InitParabolic(
            &anim->pos[0],
            &anim->pos[1],
            anim->desc.startX,
            anim->desc.endX,
            anim->desc.startY,
            anim->desc.endY,
            anim->desc.frames,
            anim->desc.radius * FX32_ONE);

        anim->desc.curFrame = 0;
        anim->state++;
        anim->unk_D4 = NULL;

        if (BallShouldRotate(anim->ballThrow.type) == TRUE) {
            int v0 = (LCRNG_Next() % 20) + 10;
            ManagedSprite_OffsetAffineZRotation(anim->sprite, (DEG_TO_IDX(45) + 1) * v0);
        }
        break;
    case 1:
        if (BallShouldRotate(anim->ballThrow.type) == TRUE) {
            ManagedSprite_OffsetAffineZRotation(anim->sprite, DEG_TO_IDX(45) + 1);

            if (anim->desc.curFrame > ((anim->desc.frames / 2) + 10)) {
                ManagedSprite_OffsetAffineZRotation(anim->sprite, DEG_TO_IDX(45) + 1);
            }

            if (ov12_02235EF0(anim->ballThrow.type) == TRUE) {
                if (anim->desc.curFrame == ((anim->desc.frames / 2) + 10)) {
                    int paletteOffset = ManagedSprite_GetExplicitPaletteOffset(anim->sprite);
                    anim->unk_D4 = PaletteFadeContext_New(
                        anim->ballThrow.paletteSys,
                        anim->ballThrow.heapID,
                        2,
                        paletteOffset * 16,
                        16,
                        -2,
                        2,
                        0,
                        14,
                        RGBA_WHITE,
                        1002);
                }
            }
        }

        anim->desc.curFrame++;

        if ((anim->ballThrow.type >= 6) && (anim->ballThrow.type <= 8)) {
            if ((anim->desc.curFrame > (anim->desc.frames / 2)) && (anim->desc.curFrame < ((anim->desc.frames / 2) + 5))) {
                break;
            }
        }

        if (XYTransformContext_UpdateAndApplyParabolic(&anim->pos[0], &anim->pos[1], anim->sprite) == FALSE) {
            ov12_02237E24(anim, 0);
            anim->state++;
        }
        break;
    case 2:
        if ((ov12_02235EF0(anim->ballThrow.type) == 1) && (anim->unk_D4 != NULL)) {
            if (PaletteFadeContext_IsActive(anim->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(anim->unk_D4);
            anim->unk_28 = 1;

            return 0;
        } else {
            if (anim->ballThrow.type >= 15) {
                anim->unk_28 = 1;
                return 0;
            }

            if (anim->ballThrow.ballID == (0xFF + 18)) {
                Sound_PlayPannedEffect(SEQ_SE_DP_W202B, 117);
            }

            anim->state++;
        }
        break;
    case 3:
        ManagedSprite_SetAnim(anim->sprite, 1);
        ov12_02237E30(anim, 1);
        anim->desc.curFrame = 0;
        anim->state++;
        break;
    default:
        if (anim->desc.curFrame == 5) {
            {
                int v2;

                if ((anim->ballThrow.type != 12) && (anim->ballThrow.type != 13)) {
                    v2 = ManagedSprite_GetExplicitPaletteOffset(anim->sprite);
                    anim->unk_D4 = PaletteFadeContext_New(anim->ballThrow.paletteSys, anim->ballThrow.heapID, 2, v2 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
                }
            }
            anim->unk_28 = 1;
        }

        if ((++anim->desc.curFrame) <= 15) {
            break;
        }

        if ((anim->ballThrow.type != 12) && (anim->ballThrow.type != 13)) {
            if (PaletteFadeContext_IsActive(anim->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(anim->unk_D4);
        }

        return 0;
    }

    return 1;
}

static BOOL ov12_022371E4(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        XYTransformContext_InitParabolic(&param0->pos[0], &param0->pos[1], param0->desc.startX, param0->desc.endX, param0->desc.startY, param0->desc.endY, param0->desc.frames, param0->desc.radius * FX32_ONE);

        param0->desc.curFrame = 0;
        param0->state++;
        param0->unk_D4 = NULL;

        {
            int v0;

            if (BallShouldRotate(param0->ballThrow.type) == 1) {
                v0 = (LCRNG_Next() % 20) + 10;

                ManagedSprite_OffsetAffineZRotation(param0->sprite, 0x2000 * v0);
            }
        }
        break;
    case 1:
        if (BallShouldRotate(param0->ballThrow.type) == 1) {
            ManagedSprite_OffsetAffineZRotation(param0->sprite, 0x2000);

            if (param0->desc.curFrame > ((param0->desc.frames / 2) + 10)) {
                ManagedSprite_OffsetAffineZRotation(param0->sprite, 0x2000);
            }

            if (ov12_02235EF0(param0->ballThrow.type) == 1) {
                if (param0->desc.curFrame == ((param0->desc.frames / 2) + 10)) {
                    int v1;

                    v1 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
                    param0->unk_D4 = PaletteFadeContext_New(param0->ballThrow.paletteSys, param0->ballThrow.heapID, 2, v1 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
                }
            }
        }

        param0->desc.curFrame++;

        if ((param0->ballThrow.type >= 6) && (param0->ballThrow.type <= 8)) {
            if ((param0->desc.curFrame > (param0->desc.frames / 2)) && (param0->desc.curFrame < ((param0->desc.frames / 2) + 5))) {
                break;
            }
        }

        if (XYTransformContext_UpdateAndApplyParabolic(&param0->pos[0], &param0->pos[1], param0->sprite) == 0) {
            ov12_02237E24(param0, 0);
            param0->state++;
        }
        break;
    case 2:
        if ((ov12_02235EF0(param0->ballThrow.type) == 1) && (param0->unk_D4 != NULL)) {
            if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
                break;
            }

            PaletteFadeContext_Free(param0->unk_D4);
            param0->unk_28 = 1;

            return 0;
        } else {
            if (param0->ballThrow.type >= 15) {
                param0->unk_28 = 1;

                return 0;
            }

            param0->state++;
        }
        break;
    case 3:
        ManagedSprite_SetAnim(param0->sprite, 1);
        ov12_02237E30(param0, 0);
        param0->desc.curFrame = 0;
        param0->state++;
        break;
    default:
        if (param0->desc.curFrame == 5) {
            ManagedSprite_SetAnimationFrame(param0->sprite, 2);

            {
                int v2;

                v2 = ManagedSprite_GetExplicitPaletteOffset(param0->sprite);
                param0->unk_D4 = PaletteFadeContext_New(param0->ballThrow.paletteSys, param0->ballThrow.heapID, 2, v2 * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
            }

            param0->unk_28 = 1;
        }

        if ((++param0->desc.curFrame) <= 15) {
            break;
        }

        if (PaletteFadeContext_IsActive(param0->unk_D4) == 1) {
            break;
        }

        PaletteFadeContext_Free(param0->unk_D4);

        return 0;
    }

    return 1;
}

static const int Unk_ov12_0223ABBC[][2] = {
    { 0x0, 0x2 },
    { 0x2, 0x2 },
    { 0x2, 0x6 },
    { 0x1, 0x6 },
    { 0x0, 0x6 }
};

static BOOL ov12_02237474(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0:
        ov12_02237E30(param0, 0);
        ManagedSprite_SetAnim(param0->sprite, 1);
        param0->desc.curFrame++;

        if (param0->desc.curFrame >= Unk_ov12_0223ABBC[0][1]) {
            ManagedSprite_SetAnimationFrame(param0->sprite, Unk_ov12_0223ABBC[0][0]);
            param0->desc.curFrame = 0;
            param0->state++;
        }
        break;
    case 1:
        param0->desc.curFrame++;

        if (param0->desc.curFrame >= Unk_ov12_0223ABBC[1][1]) {
            ManagedSprite_SetAnimationFrame(param0->sprite, Unk_ov12_0223ABBC[1][0]);
            param0->desc.curFrame = 0;
            param0->state++;
        }
        break;
    case 2: {
        UnkStruct_ov12_02236690 v0;

        v0.unk_04 = param0->ballThrow.ballID;
        v0.heapID = param0->ballThrow.heapID;
        v0.unk_0C = 0xFF;
        v0.unk_10 = 1;

        ManagedSprite_GetPositionXY(param0->sprite, &v0.unk_00, &v0.unk_02);
        param0->unk_D0 = ov12_02236690(&v0);
    }
        param0->state++;
        break;
    case 3:
        ov12_022366F0(param0->unk_D0);
        param0->state++;
        break;
    case 4:
        param0->desc.curFrame++;

        if (param0->desc.curFrame >= Unk_ov12_0223ABBC[2][1]) {
            ManagedSprite_SetAnimationFrame(param0->sprite, Unk_ov12_0223ABBC[2][0]);
            param0->desc.curFrame = 0;
            param0->state++;
        }
        break;
    case 5:
        param0->desc.curFrame++;

        if (param0->desc.curFrame >= Unk_ov12_0223ABBC[3][1]) {
            ManagedSprite_SetAnimationFrame(param0->sprite, Unk_ov12_0223ABBC[3][0]);
            param0->desc.curFrame = 0;
            param0->state++;
        }
        break;
    case 6:
        param0->desc.curFrame++;

        if (param0->desc.curFrame >= Unk_ov12_0223ABBC[4][1]) {
            ManagedSprite_SetAnimationFrame(param0->sprite, Unk_ov12_0223ABBC[4][0]);
            param0->desc.curFrame = 0;
            param0->state++;
        }
        break;
    case 7:
        if (ov12_02236764(param0->unk_D0) == 0) {
            ov12_02236780(param0->unk_D0);
            param0->state++;
        }
        break;
    default:
        return 0;
        break;
    }

    return 1;
}

static BOOL ov12_02237608(PokeballAnim *param0)
{
    switch (param0->state) {
    case 0: {
        if (param0->unk_10 == 0) {
            ValueLerpContext_Init(&param0->unk_34, -((45 * 0xffff) / 360), +((45 * 0xffff) / 360), 10);
        } else {
            ValueLerpContext_Init(&param0->unk_34, +((45 * 0xffff) / 360), -((45 * 0xffff) / 360), 10);
        }

        param0->unk_10 ^= 1;
    }
        param0->state++;
        break;
    case 1:
        ManagedSprite_SetAffineZRotation(param0->sprite, param0->unk_34.value);

        if (ValueLerpContext_Update(&param0->unk_34) == 0) {
            if (param0->unk_0C >= 1) {
                param0->state++;
            } else {
                param0->unk_0C++;
                param0->state--;
            }
        }
        break;
    default:
        param0->desc.curFrame = 0;
        return 0;
        break;
    }

    return 1;
}

static BOOL ov12_02237694(PokeballAnim *param0)
{
    if (param0->state == 0xFF) {
        return 0;
    }

    if (param0->sprite != NULL) {
        s16 v0, v1;

        ManagedSprite_GetPositionXY(param0->sprite, &v0, &v1);

        param0->desc.startX = v0;
        param0->desc.startY = v1;
    }

    return 1;
}

static void Task_PokeballAnim(SysTask *task, void *param)
{
    PokeballAnim *anim = param;

    if (anim->active == FALSE) {
        return;
    }

    if (anim->pauseTimer > 0) {
        anim->pauseTimer--;
        SpriteSystem_DrawSprites(anim->spriteMan);
        return;
    }

    BOOL active = sBallThrowTaskFuncs[anim->ballThrow.mode](anim);
    if (active == FALSE) {
        anim->active = FALSE;
    }

    if (anim->animate == TRUE) {
        ManagedSprite_TickFrame(anim->sprite);
    }

    SpriteSystem_DrawSprites(anim->spriteMan);
}

PokeballAnim *PokeballAnim_New(BallThrow *ballThrow)
{
    PokeballAnim *anim = Heap_Alloc(ballThrow->heapID, sizeof(PokeballAnim));
    MI_CpuClear8(anim, sizeof(PokeballAnim));

    GF_ASSERT(anim != NULL);

    anim->ballThrow = *ballThrow;
    anim->state = 0;
    anim->unk_10 = 0;
    anim->unk_0C = 0;
    anim->unk_14 = 0;
    anim->unk_18 = 0;
    anim->unk_00 = 0;
    anim->unk_04 = 0;
    anim->spriteMan = SpriteManager_New(anim->ballThrow.spriteSys);
    anim->pauseTimer = 0;
    anim->animate = ShouldAnimatePokeball(anim->ballThrow.type);
    anim->desc.curFrame = 0;
    anim->unk_20 = 16;
    anim->unk_21 = 0;

    BattleAnimSystem_SetDefaultAlphaBlending();

    int v1 = LCRNG_Next() % 2;
    if (v1) {
        anim->unused = +1;
    } else {
        anim->unused = -1;
    }

    PokeballAnim_LoadResources(anim);
    PokeballAnim_CreateSprite(anim);
    ov12_022378A0(anim);

    anim->active = 1;
    anim->unk_28 = 0;
    anim->unk_CC = SysTask_Start(Task_PokeballAnim, anim, 1000);

    return anim;
}

BOOL PokeballAnim_IsActive(PokeballAnim *anim)
{
    GF_ASSERT(anim != NULL);
    return anim->active ? TRUE : FALSE;
}

BOOL ov12_02237810(PokeballAnim *param0)
{
    GF_ASSERT(param0 != NULL);
    return param0->unk_28 ? 1 : 0;
}

void ov12_02237828(PokeballAnim *param0, int param1)
{
    param0->unk_14 = param1;
}

BOOL ov12_0223782C(PokeballAnim *param0, int param1)
{
    return (param0->unk_14 == param1) ? 1 : 0;
}

void ov12_0223783C(PokeballAnim *param0)
{
    int v0 = param0->ballThrow.heapID;

    GF_ASSERT(param0 != NULL);

    SpriteSystem_FreeResourcesAndManager(param0->ballThrow.spriteSys, param0->spriteMan);
    Sprite_DeleteAndFreeResources(param0->sprite);
    SysTask_Done(param0->unk_CC);
    Heap_Free(param0);
}

void ov12_0223786C(PokeballAnim *param0, int param1)
{
    param0->ballThrow.mode = param1;
    param0->state = 0;
    param0->unk_0C = 0;
    param0->unk_10 = 0;
    param0->active = 1;

    ManagedSprite_GetPositionXY(param0->sprite, &param0->desc.startX, &param0->desc.startY);
}

int ov12_02237890(PokeballAnim *param0)
{
    GF_ASSERT(param0 != NULL);

    return param0->ballThrow.mode;
}

static void ov12_022378A0(PokeballAnim *anim)
{
    ManagedSprite_GetPositionXY(anim->sprite, &anim->desc.startX, &anim->desc.startY);

    switch (anim->ballThrow.type) {
    case BALL_THROW_TYPE_SOLO_PLAYER:
    case BALL_THROW_TYPE_SOLO_ENEMY:
    case BALL_THROW_TYPE_PLAYER_SLOT_1:
    case BALL_THROW_TYPE_ENEMY_SLOT_1:
    case BALL_THROW_TYPE_PLAYER_SLOT_2:
    case BALL_THROW_TYPE_ENEMY_SLOT_2:
        ManagedSprite_GetPositionXY(anim->sprite, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 0;
        anim->desc.frames = 12;
        return;
    case BALL_THROW_TYPE_6:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_7:
        ManagedSprite_GetPositionXY(anim->sprite, &anim->desc.startX, &anim->desc.startY);
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_PLAYER_SIDE_SLOT_2, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_8:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_PLAYER_SIDE_SLOT_1, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_9:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_ENEMY, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_10:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_1, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_11:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_2, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 48;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_12:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_ENEMY, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 16;
        anim->desc.endY += 16;
        anim->desc.frames = 12;
        return;
    case BALL_THROW_TYPE_13:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_ENEMY, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 32;
        anim->desc.endX -= 20;
        anim->desc.endY += 38;
        anim->desc.frames = 16;
        return;
    case BALL_THROW_TYPE_14:
        anim->desc.endX = 128;
        anim->desc.endY = (96 - 32);
        anim->desc.radius = 32;
        anim->desc.endY += 32;
        break;
    case BALL_THROW_TYPE_15:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_ENEMY, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 64;
        anim->desc.endY += 8;
        anim->desc.frames = 16;
        return;
    case BALL_THROW_TYPE_16:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_1, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 64;
        anim->desc.endY += 8;
        anim->desc.frames = 16;
        return;
    case BALL_THROW_TYPE_17:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_2, &anim->desc.endX, &anim->desc.endY);
        anim->desc.radius = 64;
        anim->desc.endY += 8;
        anim->desc.frames = 16;
        return;
    default:
        break;
    }

    anim->desc.frames = 20;
}

static void PokeballAnim_GetBallStartPosition(PokeballAnim *anim, s16 *px, s16 *py)
{
    switch (anim->ballThrow.type) {
    case BALL_THROW_TYPE_SOLO_PLAYER:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        *py += 32 + 8;
        break;
    case BALL_THROW_TYPE_SOLO_ENEMY:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_ENEMY, px, py);
        *py += 38;
        break;
    case BALL_THROW_TYPE_PLAYER_SLOT_1:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_PLAYER_SIDE_SLOT_1, px, py);
        *py += 32 + 8;
        break;
    case BALL_THROW_TYPE_PLAYER_SLOT_2:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_PLAYER_SIDE_SLOT_2, px, py);
        *py += 32 + 8;
        break;
    case BALL_THROW_TYPE_ENEMY_SLOT_1:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_1, px, py);
        *py += 38;
        break;
    case BALL_THROW_TYPE_ENEMY_SLOT_2:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(TRUE, BATTLER_TYPE_ENEMY_SIDE_SLOT_2, px, py);
        *py += 38;
        break;
    case BALL_THROW_TYPE_6:
        *px = 10;
        *py = 100;
        break;
    case BALL_THROW_TYPE_7:
        *px = 10;
        *py = 100;
        break;
    case BALL_THROW_TYPE_8:
        *px = 10;
        *py = 100;
        break;
    case BALL_THROW_TYPE_9:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        break;
    case BALL_THROW_TYPE_10:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        break;
    case BALL_THROW_TYPE_11:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        break;
    case BALL_THROW_TYPE_12:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        break;
    case BALL_THROW_TYPE_13:
        BattleAnimUtil_GetBattlerTypeDefaultPos2(FALSE, BATTLER_TYPE_SOLO_PLAYER, px, py);
        break;
    case BALL_THROW_TYPE_14:
        *px = 230;
        *py = 32;
        break;
    case BALL_THROW_TYPE_15:
    case BALL_THROW_TYPE_16:
    case BALL_THROW_TYPE_17:
        *px = -30;
        *py = 160;
        break;
    default:
        break;
    }
}

static void PokeballAnim_LoadResources(PokeballAnim *anim)
{
    SpriteSystem_InitSprites(anim->ballThrow.spriteSys, anim->spriteMan, POKEBALL_ANIM_MAX_SPRITES);

    if (anim->ballThrow.surface == 0) {
        SetSubScreenViewRect(SpriteSystem_GetRenderer(anim->ballThrow.spriteSys), 0, FX32_CONST(HW_LCD_HEIGHT + 80));
    }

    SpriteResourceCapacities caps;
    for (int i = 0; i < SPRITE_RESOURCE_MAX; i++) {
        caps.asArray[i] = POKEBALL_ANIM_MAX_RESOURCES;
    }

    caps.asArray[SPRITE_RESOURCE_MULTI_CELL] = 0;
    caps.asArray[SPRITE_RESOURCE_MULTI_ANIM] = 0;

    SpriteSystem_InitManagerWithCapacities(anim->ballThrow.spriteSys, anim->spriteMan, &caps);

    int ncgrIndex = GetPokeballGraphics(anim->ballThrow.ballID, SPRITE_RESOURCE_CHAR);
    int nclrIndex = GetPokeballGraphics(anim->ballThrow.ballID, SPRITE_RESOURCE_PLTT);
    int ncerIndex = GetPokeballGraphics(anim->ballThrow.ballID, SPRITE_RESOURCE_CELL);
    int nanrIndex = GetPokeballGraphics(anim->ballThrow.ballID, SPRITE_RESOURCE_ANIM);

    NARC *narc = NARC_ctor(NARC_INDEX_BATTLE__GRAPHIC__PL_BATT_OBJ, anim->ballThrow.heapID);

    SpriteSystem_LoadCharResObjFromOpenNarc(
        anim->ballThrow.spriteSys,
        anim->spriteMan,
        narc,
        ncgrIndex,
        TRUE,
        NNS_G2D_VRAM_TYPE_2DMAIN,
        anim->ballThrow.target + POKEBALL_ANIM_BASE_RES_ID);

    SpriteSystem_LoadPaletteBufferFromOpenNarc(
        anim->ballThrow.paletteSys,
        PLTTBUF_MAIN_OBJ,
        anim->ballThrow.spriteSys,
        anim->spriteMan,
        narc,
        nclrIndex,
        FALSE,
        1,
        NNS_G2D_VRAM_TYPE_2DMAIN,
        anim->ballThrow.target + POKEBALL_ANIM_BASE_RES_ID);

    SpriteSystem_LoadCellResObjFromOpenNarc(
        anim->ballThrow.spriteSys,
        anim->spriteMan,
        narc,
        ncerIndex,
        TRUE,
        anim->ballThrow.target + POKEBALL_ANIM_BASE_RES_ID);

    SpriteSystem_LoadAnimResObjFromOpenNarc(
        anim->ballThrow.spriteSys,
        anim->spriteMan,
        narc,
        nanrIndex,
        TRUE,
        anim->ballThrow.target + POKEBALL_ANIM_BASE_RES_ID);

    NARC_dtor(narc);
}

static void PokeballAnim_CreateSprite(PokeballAnim *anim)
{
    SpriteTemplate template;
    PokeballAnim_GetBallStartPosition(anim, &template.x, &template.y);

    template.z = 0;
    template.animIdx = 0;
    template.priority = 0;
    template.plttIdx = 0;
    template.vramType = NNS_G2D_VRAM_TYPE_2DMAIN;
    template.bgPriority = anim->ballThrow.bgPrio;
    template.vramTransfer = FALSE;

    for (int i = 0; i < SPRITE_RESOURCE_MAX; i++) {
        template.resources[i] = anim->ballThrow.target + POKEBALL_ANIM_BASE_RES_ID;
    }

    anim->sprite = SpriteSystem_NewSprite(anim->ballThrow.spriteSys, anim->spriteMan, &template);

    ManagedSprite_SetDrawFlag(anim->sprite, TRUE);
    ManagedSprite_SetAffineOverwriteMode(anim->sprite, AFFINE_OVERWRITE_MODE_DOUBLE);
    ManagedSprite_SetAnimationFrame(anim->sprite, 0);
    ManagedSprite_SetAnim(anim->sprite, 0);
    ManagedSprite_TickFrame(anim->sprite);

    BattleAnimSystem_SetDefaultAlphaBlending();
}

void ov12_02237E0C(PokeballAnim *param0, int param1)
{
    ManagedSprite_SetDrawFlag(param0->sprite, param1);
}

void ov12_02237E18(PokeballAnim *param0, s16 param1, s16 param2)
{
    ManagedSprite_SetPositionXY(param0->sprite, param1, param2);
}

void ov12_02237E24(PokeballAnim *param0, u16 param1)
{
    ManagedSprite_SetAffineZRotation(param0->sprite, param1);
}

void ov12_02237E30(PokeballAnim *param0, BOOL param1)
{
    param0->animate = param1;
}

void ov12_02237E34(PokeballAnim *param0, int param1)
{
    ManagedSprite_SetPriority(param0->sprite, param1);
}

void ov12_02237E40(PokeballAnim *param0, int param1)
{
    ManagedSprite_SetExplicitPriority(param0->sprite, param1);
}

void ov12_02237E4C(PokeballAnim *param0, int param1)
{
    param0->pauseTimer = param1;
}
