//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 1993-2008 Raven Software
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//
// External definitions for action pointer functions.
//

#ifndef HERETIC_P_ACTION_H
#define HERETIC_P_ACTION_H

#include <d_net.hh>
// in doom
void A_Scream(mobj_t *);
void A_Explode(mobj_t *);
void A_Light0(player_t *, pspdef_t *);
void A_WeaponReady(player_t *, pspdef_t *);
void A_Lower(player_t *, pspdef_t *);
void A_Raise(player_t *, pspdef_t *);
void A_ReFire(player_t *pS, pspdef_t *ptr);
void A_Pain(mobj_t *);
void A_SkullPop(mobj_t *);
void A_FaceTarget(mobj_t *);
void A_Look(mobj_t *);
void A_Chase(mobj_t *);
void A_HeadAttack(mobj_t *);
void A_BossDeath(mobj_t *);

// not in doom
void A_FreeTargMobj(mobj_t *);
void A_RestoreSpecialThing1(mobj_t *);
void A_RestoreSpecialThing2(mobj_t *);
void A_HideThing(mobj_t *);
void A_UnHideThing(mobj_t *);
void A_RestoreArtifact(mobj_t *);
void A_PodPain(mobj_t *);
void A_RemovePod(mobj_t *);
void A_MakePod(mobj_t *);
void A_InitKeyGizmo(mobj_t *);
void A_VolcanoSet(mobj_t *);
void A_VolcanoBlast(mobj_t *);
void A_BeastPuff(mobj_t *);
void A_VolcBallImpact(mobj_t *);
void A_SpawnTeleGlitter(mobj_t *);
void A_SpawnTeleGlitter2(mobj_t *);
void A_AccTeleGlitter(mobj_t *);
void A_StaffAttackPL1(player_t *, pspdef_t *);
void A_StaffAttackPL2(player_t *, pspdef_t *);
void A_BeakReady(player_t *, pspdef_t *);
void A_BeakRaise(player_t *, pspdef_t *);
void A_BeakAttackPL1(player_t *, pspdef_t *);
void A_BeakAttackPL2(player_t *, pspdef_t *);
void A_GauntletAttack(player_t *, pspdef_t *);
void A_FireBlasterPL1(player_t *, pspdef_t *);
void A_FireBlasterPL2(player_t *, pspdef_t *);
void A_SpawnRippers(mobj_t *);
void A_FireMacePL1(player_t *, pspdef_t *);
void A_FireMacePL2(player_t *, pspdef_t *);
void A_MacePL1Check(mobj_t *);
void A_MaceBallImpact(mobj_t *);
void A_MaceBallImpact2(mobj_t *);
void A_DeathBallImpact(mobj_t *);
void A_FireSkullRodPL1(player_t *, pspdef_t *);
void A_FireSkullRodPL2(player_t *, pspdef_t *);
void A_SkullRodPL2Seek(mobj_t *);
void A_AddPlayerRain(mobj_t *);
void A_HideInCeiling(mobj_t *);
void A_SkullRodStorm(mobj_t *);
void A_RainImpact(mobj_t *);
void A_FireGoldWandPL1(player_t *, pspdef_t *);
void A_FireGoldWandPL2(player_t *, pspdef_t *);
void A_FirePhoenixPL1(player_t *, pspdef_t *);
void A_InitPhoenixPL2(player_t *, pspdef_t *);
void A_FirePhoenixPL2(player_t *, pspdef_t *);
void A_ShutdownPhoenixPL2(player_t *, pspdef_t *);
void A_PhoenixPuff(mobj_t *);
void A_RemovedPhoenixFunc(mobj_t *);
void A_FlameEnd(mobj_t *);
void A_FloatPuff(mobj_t *);
void A_FireCrossbowPL1(player_t *, pspdef_t *);
void A_FireCrossbowPL2(player_t *, pspdef_t *);
void A_BoltSpark(mobj_t *);
void A_NoBlocking(mobj_t *);
void A_AddPlayerCorpse(mobj_t *);
void A_FlameSnd(mobj_t *);
void A_CheckBurnGone(mobj_t *);
void A_CheckSkullFloor(mobj_t *);
void A_CheckSkullDone(mobj_t *);
void A_Feathers(mobj_t *);
void A_ChicLook(mobj_t *);
void A_ChicChase(mobj_t *);
void A_ChicPain(mobj_t *);
void A_ChicAttack(mobj_t *);
void A_MummyAttack(mobj_t *);
void A_MummyAttack2(mobj_t *);
void A_MummySoul(mobj_t *);
void A_ContMobjSound(mobj_t *);
void A_MummyFX1Seek(mobj_t *);
void A_BeastAttack(mobj_t *);
void A_SnakeAttack(mobj_t *);
void A_SnakeAttack2(mobj_t *);
void A_HeadIceImpact(mobj_t *);
void A_HeadFireGrow(mobj_t *);
void A_WhirlwindSeek(mobj_t *);
void A_ClinkAttack(mobj_t *);
void A_WizAtk1(mobj_t *);
void A_WizAtk2(mobj_t *);
void A_WizAtk3(mobj_t *);
void A_GhostOff(mobj_t *);
void A_ImpMeAttack(mobj_t *);
void A_ImpMsAttack(mobj_t *);
void A_ImpMsAttack2(mobj_t *);
void A_ImpDeath(mobj_t *);
void A_ImpXDeath1(mobj_t *);
void A_ImpXDeath2(mobj_t *);
void A_ImpExplode(mobj_t *);
void A_KnightAttack(mobj_t *);
void A_DripBlood(mobj_t *);
void A_Sor1Chase(mobj_t *);
void A_Sor1Pain(mobj_t *);
void A_Srcr1Attack(mobj_t *);
void A_SorZap(mobj_t *);
void A_SorcererRise(mobj_t *);
void A_SorRise(mobj_t *);
void A_SorSightSnd(mobj_t *);
void A_Srcr2Decide(mobj_t *);
void A_Srcr2Attack(mobj_t *);
void A_Sor2DthInit(mobj_t *);
void A_SorDSph(mobj_t *);
void A_Sor2DthLoop(mobj_t *);
void A_SorDExp(mobj_t *);
void A_SorDBon(mobj_t *);
void A_BlueSpark(mobj_t *);
void A_GenWizard(mobj_t *);
void A_MinotaurAtk1(mobj_t *);
void A_MinotaurDecide(mobj_t *);
void A_MinotaurAtk2(mobj_t *);
void A_MinotaurAtk3(mobj_t *);
void A_MinotaurCharge(mobj_t *);
void A_MntrFloorFire(mobj_t *);
void A_ESound(mobj_t *);

#endif
