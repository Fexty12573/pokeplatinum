#ifndef POKEPLATINUM_OV12_02235E94_H
#define POKEPLATINUM_OV12_02235E94_H

#include "battle_anim/struct_ball_rotation_decl.h"
#include "battle_anim/struct_ov12_02235FE0_decl.h"
#include "battle_anim/struct_ov12_02236030.h"
#include "battle_anim/struct_ov12_02236648_decl.h"
#include "battle_anim/struct_ov12_02236690.h"
#include "battle_anim/struct_ov12_02237728.h"

#include "spl.h"

BallCapsuleSealEffect *ov12_02235FE0(enum HeapID heapID);
BallCapsuleSealEffect *ov12_02236004(enum HeapID heapID, const BallCapsuleConfig *ballCapCfg);
void ov12_02236030(BallCapsuleSealEffect *ballCapSealEff, const BallCapsuleConfig *ballCapCfg);
void ov12_02236320(BallCapsuleSealEffect *ballCapSealEff);
BOOL ov12_02236374(BallCapsuleSealEffect *ballCapSealEff);
void ov12_02236384(BallCapsuleSealEffect *ballCapSealEff, SPLEmitterCallback param1);
void ov12_022363B4(BallCapsuleSealEffect *ballCapSealEff);
BOOL ov12_022363C4(BallCapsuleSealEffect *ballCapSealEff);
void ov12_02236428(BallCapsuleSealEffect *ballCapSealEff);
UnkStruct_ov12_02236648 *ov12_02236690(UnkStruct_ov12_02236690 *param0);
void ov12_022366F0(UnkStruct_ov12_02236648 *param0);
BOOL ov12_02236764(UnkStruct_ov12_02236648 *param0);
void ov12_02236780(UnkStruct_ov12_02236648 *param0);
void ov12_022368C8(PokeballAnim *param0, int param1);
BOOL ov12_022368D0(PokeballAnim *param0, int param1);
PokeballAnim *PokeballAnim_New(BallThrow *ballThrow);
BOOL ov12_022377F8(PokeballAnim *param0);
BOOL ov12_02237810(PokeballAnim *param0);
void ov12_02237828(PokeballAnim *param0, int param1);
BOOL ov12_0223782C(PokeballAnim *param0, int param1);
void ov12_0223783C(PokeballAnim *param0);
void ov12_0223786C(PokeballAnim *param0, int param1);
int ov12_02237890(PokeballAnim *param0);
void ov12_02237E0C(PokeballAnim *param0, int param1);
void ov12_02237E18(PokeballAnim *param0, s16 param1, s16 param2);
void ov12_02237E24(PokeballAnim *param0, u16 param1);
void ov12_02237E30(PokeballAnim *param0, BOOL param1);
void ov12_02237E34(PokeballAnim *param0, int param1);
void ov12_02237E40(PokeballAnim *param0, int param1);
void ov12_02237E4C(PokeballAnim *param0, int param1);

#endif // POKEPLATINUM_OV12_02235E94_H
