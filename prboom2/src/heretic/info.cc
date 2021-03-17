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
#include "p_mobj.hh"
#include "p_action.hh"
#include "sounds.hh"
#include "info.hh"

const char *heretic_sprnames[HERETIC_NUMSPRITES + 1] = {
    "IMPX", "ACLO", "PTN1", "SHLD", "SHD2", "BAGH", "SPMP", "INVS", "PTN2",
    "SOAR", "INVU", "PWBK", "EGGC", "EGGM", "FX01", "SPHL", "TRCH", "FBMB",
    "XPL1", "ATLP", "PPOD", "AMG1", "SPSH", "LVAS", "SLDG", "SKH1", "SKH2",
    "SKH3", "SKH4", "CHDL", "SRTC", "SMPL", "STGS", "STGL", "STCS", "STCL",
    "KFR1", "BARL", "BRPL", "MOS1", "MOS2", "WTRH", "HCOR", "KGZ1", "KGZB",
    "KGZG", "KGZY", "VLCO", "VFBL", "VTFB", "SFFI", "TGLT", "TELE", "STFF",
    "PUF3", "PUF4", "BEAK", "WGNT", "GAUN", "PUF1", "WBLS", "BLSR", "FX18",
    "FX17", "WMCE", "MACE", "FX02", "WSKL", "HROD", "FX00", "FX20", "FX21",
    "FX22", "FX23", "GWND", "PUF2", "WPHX", "PHNX", "FX04", "FX08", "FX09",
    "WBOW", "CRBW", "FX03", "BLOD", "PLAY", "FDTH", "BSKL", "CHKN", "MUMM",
    "FX15", "BEAS", "FRB1", "SNKE", "SNFX", "HEAD", "FX05", "FX06", "FX07",
    "CLNK", "WZRD", "FX11", "FX10", "KNIG", "SPAX", "RAXE", "SRCR", "FX14",
    "SOR2", "SDTH", "FX16", "MNTR", "FX12", "FX13", "AKYY", "BKYY", "CKYY",
    "AMG2", "AMM1", "AMM2", "AMC1", "AMC2", "AMS1", "AMS2", "AMP1", "AMP2",
    "AMB1", "AMB2", nullptr};

state_t heretic_states[HERETIC_NUMSTATES] = {
    {HERETIC_SPR_IMPX, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_NULL
    {HERETIC_SPR_ACLO, 4, 1050, A_FreeTargMobj, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_FREETARGMOBJ
    {HERETIC_SPR_PTN1,
     0,
     3,
     {},
     HERETIC_S_ITEM_PTN1_2,
     0,
     0}, // HERETIC_S_ITEM_PTN1_1
    {HERETIC_SPR_PTN1,
     1,
     3,
     {},
     HERETIC_S_ITEM_PTN1_3,
     0,
     0}, // HERETIC_S_ITEM_PTN1_2
    {HERETIC_SPR_PTN1,
     2,
     3,
     {},
     HERETIC_S_ITEM_PTN1_1,
     0,
     0}, // HERETIC_S_ITEM_PTN1_3
    {HERETIC_SPR_SHLD, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_ITEM_SHLD1
    {HERETIC_SPR_SHD2,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_ITEM_SHD2_1
    {HERETIC_SPR_BAGH, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_ITEM_BAGH1
    {HERETIC_SPR_SPMP, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_ITEM_SPMP1
    {HERETIC_SPR_ACLO,
     4,
     1400,
     {},
     HERETIC_S_HIDESPECIAL2,
     0,
     0}, // HERETIC_S_HIDESPECIAL1
    {HERETIC_SPR_ACLO, 0, 4, A_RestoreSpecialThing1, HERETIC_S_HIDESPECIAL3, 0,
     0}, // HERETIC_S_HIDESPECIAL2
    {HERETIC_SPR_ACLO,
     1,
     4,
     {},
     HERETIC_S_HIDESPECIAL4,
     0,
     0}, // HERETIC_S_HIDESPECIAL3
    {HERETIC_SPR_ACLO,
     0,
     4,
     {},
     HERETIC_S_HIDESPECIAL5,
     0,
     0}, // HERETIC_S_HIDESPECIAL4
    {HERETIC_SPR_ACLO,
     1,
     4,
     {},
     HERETIC_S_HIDESPECIAL6,
     0,
     0}, // HERETIC_S_HIDESPECIAL5
    {HERETIC_SPR_ACLO,
     2,
     4,
     {},
     HERETIC_S_HIDESPECIAL7,
     0,
     0}, // HERETIC_S_HIDESPECIAL6
    {HERETIC_SPR_ACLO,
     1,
     4,
     {},
     HERETIC_S_HIDESPECIAL8,
     0,
     0}, // HERETIC_S_HIDESPECIAL7
    {HERETIC_SPR_ACLO,
     2,
     4,
     {},
     HERETIC_S_HIDESPECIAL9,
     0,
     0}, // HERETIC_S_HIDESPECIAL8
    {HERETIC_SPR_ACLO,
     3,
     4,
     {},
     HERETIC_S_HIDESPECIAL10,
     0,
     0}, // HERETIC_S_HIDESPECIAL9
    {HERETIC_SPR_ACLO,
     2,
     4,
     {},
     HERETIC_S_HIDESPECIAL11,
     0,
     0}, // HERETIC_S_HIDESPECIAL10
    {HERETIC_SPR_ACLO, 3, 4, A_RestoreSpecialThing2, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_HIDESPECIAL11
    {HERETIC_SPR_ACLO,
     3,
     3,
     {},
     HERETIC_S_DORMANTARTI2,
     0,
     0}, // HERETIC_S_DORMANTARTI1
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI3,
     0,
     0}, // HERETIC_S_DORMANTARTI2
    {HERETIC_SPR_ACLO,
     3,
     3,
     {},
     HERETIC_S_DORMANTARTI4,
     0,
     0}, // HERETIC_S_DORMANTARTI3
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI5,
     0,
     0}, // HERETIC_S_DORMANTARTI4
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI6,
     0,
     0}, // HERETIC_S_DORMANTARTI5
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI7,
     0,
     0}, // HERETIC_S_DORMANTARTI6
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI8,
     0,
     0}, // HERETIC_S_DORMANTARTI7
    {HERETIC_SPR_ACLO,
     0,
     3,
     {},
     HERETIC_S_DORMANTARTI9,
     0,
     0}, // HERETIC_S_DORMANTARTI8
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI10,
     0,
     0}, // HERETIC_S_DORMANTARTI9
    {HERETIC_SPR_ACLO,
     0,
     3,
     {},
     HERETIC_S_DORMANTARTI11,
     0,
     0}, // HERETIC_S_DORMANTARTI10
    {HERETIC_SPR_ACLO, 0, 1400, A_HideThing, HERETIC_S_DORMANTARTI12, 0,
     0}, // HERETIC_S_DORMANTARTI11
    {HERETIC_SPR_ACLO, 0, 3, A_UnHideThing, HERETIC_S_DORMANTARTI13, 0,
     0}, // HERETIC_S_DORMANTARTI12
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI14,
     0,
     0}, // HERETIC_S_DORMANTARTI13
    {HERETIC_SPR_ACLO,
     0,
     3,
     {},
     HERETIC_S_DORMANTARTI15,
     0,
     0}, // HERETIC_S_DORMANTARTI14
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI16,
     0,
     0}, // HERETIC_S_DORMANTARTI15
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI17,
     0,
     0}, // HERETIC_S_DORMANTARTI16
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DORMANTARTI18,
     0,
     0}, // HERETIC_S_DORMANTARTI17
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI19,
     0,
     0}, // HERETIC_S_DORMANTARTI18
    {HERETIC_SPR_ACLO,
     3,
     3,
     {},
     HERETIC_S_DORMANTARTI20,
     0,
     0}, // HERETIC_S_DORMANTARTI19
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DORMANTARTI21,
     0,
     0}, // HERETIC_S_DORMANTARTI20
    {HERETIC_SPR_ACLO, 3, 3, A_RestoreArtifact, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_DORMANTARTI21
    {HERETIC_SPR_ACLO,
     3,
     3,
     {},
     HERETIC_S_DEADARTI2,
     0,
     0}, // HERETIC_S_DEADARTI1
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DEADARTI3,
     0,
     0}, // HERETIC_S_DEADARTI2
    {HERETIC_SPR_ACLO,
     3,
     3,
     {},
     HERETIC_S_DEADARTI4,
     0,
     0}, // HERETIC_S_DEADARTI3
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DEADARTI5,
     0,
     0}, // HERETIC_S_DEADARTI4
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DEADARTI6,
     0,
     0}, // HERETIC_S_DEADARTI5
    {HERETIC_SPR_ACLO,
     2,
     3,
     {},
     HERETIC_S_DEADARTI7,
     0,
     0}, // HERETIC_S_DEADARTI6
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DEADARTI8,
     0,
     0}, // HERETIC_S_DEADARTI7
    {HERETIC_SPR_ACLO,
     0,
     3,
     {},
     HERETIC_S_DEADARTI9,
     0,
     0}, // HERETIC_S_DEADARTI8
    {HERETIC_SPR_ACLO,
     1,
     3,
     {},
     HERETIC_S_DEADARTI10,
     0,
     0},                                                // HERETIC_S_DEADARTI9
    {HERETIC_SPR_ACLO, 0, 3, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_DEADARTI10
    {HERETIC_SPR_INVS,
     32768,
     350,
     {},
     HERETIC_S_ARTI_INVS1,
     0,
     0}, // HERETIC_S_ARTI_INVS1
    {HERETIC_SPR_PTN2,
     0,
     4,
     {},
     HERETIC_S_ARTI_PTN2_2,
     0,
     0}, // HERETIC_S_ARTI_PTN2_1
    {HERETIC_SPR_PTN2,
     1,
     4,
     {},
     HERETIC_S_ARTI_PTN2_3,
     0,
     0}, // HERETIC_S_ARTI_PTN2_2
    {HERETIC_SPR_PTN2,
     2,
     4,
     {},
     HERETIC_S_ARTI_PTN2_1,
     0,
     0}, // HERETIC_S_ARTI_PTN2_3
    {HERETIC_SPR_SOAR,
     0,
     5,
     {},
     HERETIC_S_ARTI_SOAR2,
     0,
     0}, // HERETIC_S_ARTI_SOAR1
    {HERETIC_SPR_SOAR,
     1,
     5,
     {},
     HERETIC_S_ARTI_SOAR3,
     0,
     0}, // HERETIC_S_ARTI_SOAR2
    {HERETIC_SPR_SOAR,
     2,
     5,
     {},
     HERETIC_S_ARTI_SOAR4,
     0,
     0}, // HERETIC_S_ARTI_SOAR3
    {HERETIC_SPR_SOAR,
     1,
     5,
     {},
     HERETIC_S_ARTI_SOAR1,
     0,
     0}, // HERETIC_S_ARTI_SOAR4
    {HERETIC_SPR_INVU,
     0,
     3,
     {},
     HERETIC_S_ARTI_INVU2,
     0,
     0}, // HERETIC_S_ARTI_INVU1
    {HERETIC_SPR_INVU,
     1,
     3,
     {},
     HERETIC_S_ARTI_INVU3,
     0,
     0}, // HERETIC_S_ARTI_INVU2
    {HERETIC_SPR_INVU,
     2,
     3,
     {},
     HERETIC_S_ARTI_INVU4,
     0,
     0}, // HERETIC_S_ARTI_INVU3
    {HERETIC_SPR_INVU,
     3,
     3,
     {},
     HERETIC_S_ARTI_INVU1,
     0,
     0}, // HERETIC_S_ARTI_INVU4
    {HERETIC_SPR_PWBK,
     0,
     350,
     {},
     HERETIC_S_ARTI_PWBK1,
     0,
     0}, // HERETIC_S_ARTI_PWBK1
    {HERETIC_SPR_EGGC,
     0,
     6,
     {},
     HERETIC_S_ARTI_EGGC2,
     0,
     0}, // HERETIC_S_ARTI_EGGC1
    {HERETIC_SPR_EGGC,
     1,
     6,
     {},
     HERETIC_S_ARTI_EGGC3,
     0,
     0}, // HERETIC_S_ARTI_EGGC2
    {HERETIC_SPR_EGGC,
     2,
     6,
     {},
     HERETIC_S_ARTI_EGGC4,
     0,
     0}, // HERETIC_S_ARTI_EGGC3
    {HERETIC_SPR_EGGC,
     1,
     6,
     {},
     HERETIC_S_ARTI_EGGC1,
     0,
     0}, // HERETIC_S_ARTI_EGGC4
    {HERETIC_SPR_EGGM, 0, 4, {}, HERETIC_S_EGGFX2, 0, 0}, // HERETIC_S_EGGFX1
    {HERETIC_SPR_EGGM, 1, 4, {}, HERETIC_S_EGGFX3, 0, 0}, // HERETIC_S_EGGFX2
    {HERETIC_SPR_EGGM, 2, 4, {}, HERETIC_S_EGGFX4, 0, 0}, // HERETIC_S_EGGFX3
    {HERETIC_SPR_EGGM, 3, 4, {}, HERETIC_S_EGGFX5, 0, 0}, // HERETIC_S_EGGFX4
    {HERETIC_SPR_EGGM, 4, 4, {}, HERETIC_S_EGGFX1, 0, 0}, // HERETIC_S_EGGFX5
    {HERETIC_SPR_FX01,
     32772,
     3,
     {},
     HERETIC_S_EGGFXI1_2,
     0,
     0}, // HERETIC_S_EGGFXI1_1
    {HERETIC_SPR_FX01,
     32773,
     3,
     {},
     HERETIC_S_EGGFXI1_3,
     0,
     0}, // HERETIC_S_EGGFXI1_2
    {HERETIC_SPR_FX01,
     32774,
     3,
     {},
     HERETIC_S_EGGFXI1_4,
     0,
     0}, // HERETIC_S_EGGFXI1_3
    {HERETIC_SPR_FX01,
     32775,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_EGGFXI1_4
    {HERETIC_SPR_SPHL,
     0,
     350,
     {},
     HERETIC_S_ARTI_SPHL1,
     0,
     0}, // HERETIC_S_ARTI_SPHL1
    {HERETIC_SPR_TRCH,
     32768,
     3,
     {},
     HERETIC_S_ARTI_TRCH2,
     0,
     0}, // HERETIC_S_ARTI_TRCH1
    {HERETIC_SPR_TRCH,
     32769,
     3,
     {},
     HERETIC_S_ARTI_TRCH3,
     0,
     0}, // HERETIC_S_ARTI_TRCH2
    {HERETIC_SPR_TRCH,
     32770,
     3,
     {},
     HERETIC_S_ARTI_TRCH1,
     0,
     0}, // HERETIC_S_ARTI_TRCH3
    {HERETIC_SPR_FBMB,
     4,
     350,
     {},
     HERETIC_S_ARTI_FBMB1,
     0,
     0}, // HERETIC_S_ARTI_FBMB1
    {HERETIC_SPR_FBMB,
     0,
     10,
     {},
     HERETIC_S_FIREBOMB2,
     0,
     0}, // HERETIC_S_FIREBOMB1
    {HERETIC_SPR_FBMB,
     1,
     10,
     {},
     HERETIC_S_FIREBOMB3,
     0,
     0}, // HERETIC_S_FIREBOMB2
    {HERETIC_SPR_FBMB,
     2,
     10,
     {},
     HERETIC_S_FIREBOMB4,
     0,
     0}, // HERETIC_S_FIREBOMB3
    {HERETIC_SPR_FBMB,
     3,
     10,
     {},
     HERETIC_S_FIREBOMB5,
     0,
     0}, // HERETIC_S_FIREBOMB4
    {HERETIC_SPR_FBMB, 4, 6, A_Scream, HERETIC_S_FIREBOMB6, 0,
     0}, // HERETIC_S_FIREBOMB5
    {HERETIC_SPR_XPL1, 32768, 4, A_Explode, HERETIC_S_FIREBOMB7, 0,
     0}, // HERETIC_S_FIREBOMB6
    {HERETIC_SPR_XPL1,
     32769,
     4,
     {},
     HERETIC_S_FIREBOMB8,
     0,
     0}, // HERETIC_S_FIREBOMB7
    {HERETIC_SPR_XPL1,
     32770,
     4,
     {},
     HERETIC_S_FIREBOMB9,
     0,
     0}, // HERETIC_S_FIREBOMB8
    {HERETIC_SPR_XPL1,
     32771,
     4,
     {},
     HERETIC_S_FIREBOMB10,
     0,
     0}, // HERETIC_S_FIREBOMB9
    {HERETIC_SPR_XPL1,
     32772,
     4,
     {},
     HERETIC_S_FIREBOMB11,
     0,
     0}, // HERETIC_S_FIREBOMB10
    {HERETIC_SPR_XPL1,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_FIREBOMB11
    {HERETIC_SPR_ATLP,
     0,
     4,
     {},
     HERETIC_S_ARTI_ATLP2,
     0,
     0}, // HERETIC_S_ARTI_ATLP1
    {HERETIC_SPR_ATLP,
     1,
     4,
     {},
     HERETIC_S_ARTI_ATLP3,
     0,
     0}, // HERETIC_S_ARTI_ATLP2
    {HERETIC_SPR_ATLP,
     2,
     4,
     {},
     HERETIC_S_ARTI_ATLP4,
     0,
     0}, // HERETIC_S_ARTI_ATLP3
    {HERETIC_SPR_ATLP,
     1,
     4,
     {},
     HERETIC_S_ARTI_ATLP1,
     0,
     0}, // HERETIC_S_ARTI_ATLP4
    {HERETIC_SPR_PPOD,
     0,
     10,
     {},
     HERETIC_S_POD_WAIT1,
     0,
     0}, // HERETIC_S_POD_WAIT1
    {HERETIC_SPR_PPOD, 1, 14, A_PodPain, HERETIC_S_POD_WAIT1, 0,
     0}, // HERETIC_S_POD_PAIN1
    {HERETIC_SPR_PPOD, 32770, 5, A_RemovePod, HERETIC_S_POD_DIE2, 0,
     0}, // HERETIC_S_POD_DIE1
    {HERETIC_SPR_PPOD, 32771, 5, A_Scream, HERETIC_S_POD_DIE3, 0,
     0}, // HERETIC_S_POD_DIE2
    {HERETIC_SPR_PPOD, 32772, 5, A_Explode, HERETIC_S_POD_DIE4, 0,
     0}, // HERETIC_S_POD_DIE3
    {HERETIC_SPR_PPOD,
     32773,
     10,
     {},
     HERETIC_S_FREETARGMOBJ,
     0,
     0}, // HERETIC_S_POD_DIE4
    {HERETIC_SPR_PPOD,
     8,
     3,
     {},
     HERETIC_S_POD_GROW2,
     0,
     0}, // HERETIC_S_POD_GROW1
    {HERETIC_SPR_PPOD,
     9,
     3,
     {},
     HERETIC_S_POD_GROW3,
     0,
     0}, // HERETIC_S_POD_GROW2
    {HERETIC_SPR_PPOD,
     10,
     3,
     {},
     HERETIC_S_POD_GROW4,
     0,
     0}, // HERETIC_S_POD_GROW3
    {HERETIC_SPR_PPOD,
     11,
     3,
     {},
     HERETIC_S_POD_GROW5,
     0,
     0}, // HERETIC_S_POD_GROW4
    {HERETIC_SPR_PPOD,
     12,
     3,
     {},
     HERETIC_S_POD_GROW6,
     0,
     0}, // HERETIC_S_POD_GROW5
    {HERETIC_SPR_PPOD,
     13,
     3,
     {},
     HERETIC_S_POD_GROW7,
     0,
     0}, // HERETIC_S_POD_GROW6
    {HERETIC_SPR_PPOD,
     14,
     3,
     {},
     HERETIC_S_POD_GROW8,
     0,
     0}, // HERETIC_S_POD_GROW7
    {HERETIC_SPR_PPOD,
     15,
     3,
     {},
     HERETIC_S_POD_WAIT1,
     0,
     0}, // HERETIC_S_POD_GROW8
    {HERETIC_SPR_PPOD, 6, 8, {}, HERETIC_S_PODGOO2, 0, 0}, // HERETIC_S_PODGOO1
    {HERETIC_SPR_PPOD, 7, 8, {}, HERETIC_S_PODGOO1, 0, 0}, // HERETIC_S_PODGOO2
    {HERETIC_SPR_PPOD, 6, 10, {}, HERETIC_S_NULL, 0, 0},   // HERETIC_S_PODGOOX
    {HERETIC_SPR_AMG1, 0, 35, A_MakePod, HERETIC_S_PODGENERATOR, 0,
     0}, // HERETIC_S_PODGENERATOR
    {HERETIC_SPR_SPSH, 0, 8, {}, HERETIC_S_SPLASH2, 0, 0}, // HERETIC_S_SPLASH1
    {HERETIC_SPR_SPSH, 1, 8, {}, HERETIC_S_SPLASH3, 0, 0}, // HERETIC_S_SPLASH2
    {HERETIC_SPR_SPSH, 2, 8, {}, HERETIC_S_SPLASH4, 0, 0}, // HERETIC_S_SPLASH3
    {HERETIC_SPR_SPSH, 3, 16, {}, HERETIC_S_NULL, 0, 0},   // HERETIC_S_SPLASH4
    {HERETIC_SPR_SPSH, 3, 10, {}, HERETIC_S_NULL, 0, 0},   // HERETIC_S_SPLASHX
    {HERETIC_SPR_SPSH,
     4,
     5,
     {},
     HERETIC_S_SPLASHBASE2,
     0,
     0}, // HERETIC_S_SPLASHBASE1
    {HERETIC_SPR_SPSH,
     5,
     5,
     {},
     HERETIC_S_SPLASHBASE3,
     0,
     0}, // HERETIC_S_SPLASHBASE2
    {HERETIC_SPR_SPSH,
     6,
     5,
     {},
     HERETIC_S_SPLASHBASE4,
     0,
     0}, // HERETIC_S_SPLASHBASE3
    {HERETIC_SPR_SPSH,
     7,
     5,
     {},
     HERETIC_S_SPLASHBASE5,
     0,
     0}, // HERETIC_S_SPLASHBASE4
    {HERETIC_SPR_SPSH,
     8,
     5,
     {},
     HERETIC_S_SPLASHBASE6,
     0,
     0}, // HERETIC_S_SPLASHBASE5
    {HERETIC_SPR_SPSH,
     9,
     5,
     {},
     HERETIC_S_SPLASHBASE7,
     0,
     0}, // HERETIC_S_SPLASHBASE6
    {HERETIC_SPR_SPSH,
     10,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SPLASHBASE7
    {HERETIC_SPR_LVAS,
     32768,
     5,
     {},
     HERETIC_S_LAVASPLASH2,
     0,
     0}, // HERETIC_S_LAVASPLASH1
    {HERETIC_SPR_LVAS,
     32769,
     5,
     {},
     HERETIC_S_LAVASPLASH3,
     0,
     0}, // HERETIC_S_LAVASPLASH2
    {HERETIC_SPR_LVAS,
     32770,
     5,
     {},
     HERETIC_S_LAVASPLASH4,
     0,
     0}, // HERETIC_S_LAVASPLASH3
    {HERETIC_SPR_LVAS,
     32771,
     5,
     {},
     HERETIC_S_LAVASPLASH5,
     0,
     0}, // HERETIC_S_LAVASPLASH4
    {HERETIC_SPR_LVAS,
     32772,
     5,
     {},
     HERETIC_S_LAVASPLASH6,
     0,
     0}, // HERETIC_S_LAVASPLASH5
    {HERETIC_SPR_LVAS,
     32773,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_LAVASPLASH6
    {HERETIC_SPR_LVAS,
     32774,
     5,
     {},
     HERETIC_S_LAVASMOKE2,
     0,
     0}, // HERETIC_S_LAVASMOKE1
    {HERETIC_SPR_LVAS,
     32775,
     5,
     {},
     HERETIC_S_LAVASMOKE3,
     0,
     0}, // HERETIC_S_LAVASMOKE2
    {HERETIC_SPR_LVAS,
     32776,
     5,
     {},
     HERETIC_S_LAVASMOKE4,
     0,
     0}, // HERETIC_S_LAVASMOKE3
    {HERETIC_SPR_LVAS,
     32777,
     5,
     {},
     HERETIC_S_LAVASMOKE5,
     0,
     0}, // HERETIC_S_LAVASMOKE4
    {HERETIC_SPR_LVAS,
     32778,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_LAVASMOKE5
    {HERETIC_SPR_SLDG,
     0,
     8,
     {},
     HERETIC_S_SLUDGECHUNK2,
     0,
     0}, // HERETIC_S_SLUDGECHUNK1
    {HERETIC_SPR_SLDG,
     1,
     8,
     {},
     HERETIC_S_SLUDGECHUNK3,
     0,
     0}, // HERETIC_S_SLUDGECHUNK2
    {HERETIC_SPR_SLDG,
     2,
     8,
     {},
     HERETIC_S_SLUDGECHUNK4,
     0,
     0}, // HERETIC_S_SLUDGECHUNK3
    {HERETIC_SPR_SLDG,
     3,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SLUDGECHUNK4
    {HERETIC_SPR_SLDG,
     3,
     6,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SLUDGECHUNKX
    {HERETIC_SPR_SLDG,
     4,
     5,
     {},
     HERETIC_S_SLUDGESPLASH2,
     0,
     0}, // HERETIC_S_SLUDGESPLASH1
    {HERETIC_SPR_SLDG,
     5,
     5,
     {},
     HERETIC_S_SLUDGESPLASH3,
     0,
     0}, // HERETIC_S_SLUDGESPLASH2
    {HERETIC_SPR_SLDG,
     6,
     5,
     {},
     HERETIC_S_SLUDGESPLASH4,
     0,
     0}, // HERETIC_S_SLUDGESPLASH3
    {HERETIC_SPR_SLDG,
     7,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SLUDGESPLASH4
    {HERETIC_SPR_SKH1,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SKULLHANG70_1
    {HERETIC_SPR_SKH2,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SKULLHANG60_1
    {HERETIC_SPR_SKH3,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SKULLHANG45_1
    {HERETIC_SPR_SKH4,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SKULLHANG35_1
    {HERETIC_SPR_CHDL,
     0,
     4,
     {},
     HERETIC_S_CHANDELIER2,
     0,
     0}, // HERETIC_S_CHANDELIER1
    {HERETIC_SPR_CHDL,
     1,
     4,
     {},
     HERETIC_S_CHANDELIER3,
     0,
     0}, // HERETIC_S_CHANDELIER2
    {HERETIC_SPR_CHDL,
     2,
     4,
     {},
     HERETIC_S_CHANDELIER1,
     0,
     0}, // HERETIC_S_CHANDELIER3
    {HERETIC_SPR_SRTC,
     0,
     4,
     {},
     HERETIC_S_SERPTORCH2,
     0,
     0}, // HERETIC_S_SERPTORCH1
    {HERETIC_SPR_SRTC,
     1,
     4,
     {},
     HERETIC_S_SERPTORCH3,
     0,
     0}, // HERETIC_S_SERPTORCH2
    {HERETIC_SPR_SRTC,
     2,
     4,
     {},
     HERETIC_S_SERPTORCH1,
     0,
     0}, // HERETIC_S_SERPTORCH3
    {HERETIC_SPR_SMPL,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SMALLPILLAR
    {HERETIC_SPR_STGS,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_STALAGMITESMALL
    {HERETIC_SPR_STGL,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_STALAGMITELARGE
    {HERETIC_SPR_STCS,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_STALACTITESMALL
    {HERETIC_SPR_STCL,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_STALACTITELARGE
    {HERETIC_SPR_KFR1,
     32768,
     3,
     {},
     HERETIC_S_FIREBRAZIER2,
     0,
     0}, // HERETIC_S_FIREBRAZIER1
    {HERETIC_SPR_KFR1,
     32769,
     3,
     {},
     HERETIC_S_FIREBRAZIER3,
     0,
     0}, // HERETIC_S_FIREBRAZIER2
    {HERETIC_SPR_KFR1,
     32770,
     3,
     {},
     HERETIC_S_FIREBRAZIER4,
     0,
     0}, // HERETIC_S_FIREBRAZIER3
    {HERETIC_SPR_KFR1,
     32771,
     3,
     {},
     HERETIC_S_FIREBRAZIER5,
     0,
     0}, // HERETIC_S_FIREBRAZIER4
    {HERETIC_SPR_KFR1,
     32772,
     3,
     {},
     HERETIC_S_FIREBRAZIER6,
     0,
     0}, // HERETIC_S_FIREBRAZIER5
    {HERETIC_SPR_KFR1,
     32773,
     3,
     {},
     HERETIC_S_FIREBRAZIER7,
     0,
     0}, // HERETIC_S_FIREBRAZIER6
    {HERETIC_SPR_KFR1,
     32774,
     3,
     {},
     HERETIC_S_FIREBRAZIER8,
     0,
     0}, // HERETIC_S_FIREBRAZIER7
    {HERETIC_SPR_KFR1,
     32775,
     3,
     {},
     HERETIC_S_FIREBRAZIER1,
     0,
     0}, // HERETIC_S_FIREBRAZIER8
    {HERETIC_SPR_BARL, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_BARREL
    {HERETIC_SPR_BRPL, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_BRPILLAR
    {HERETIC_SPR_MOS1, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_MOSS1
    {HERETIC_SPR_MOS2, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_MOSS2
    {HERETIC_SPR_WTRH,
     32768,
     6,
     {},
     HERETIC_S_WALLTORCH2,
     0,
     0}, // HERETIC_S_WALLTORCH1
    {HERETIC_SPR_WTRH,
     32769,
     6,
     {},
     HERETIC_S_WALLTORCH3,
     0,
     0}, // HERETIC_S_WALLTORCH2
    {HERETIC_SPR_WTRH,
     32770,
     6,
     {},
     HERETIC_S_WALLTORCH1,
     0,
     0}, // HERETIC_S_WALLTORCH3
    {HERETIC_SPR_HCOR,
     0,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_HANGINGCORPSE
    {HERETIC_SPR_KGZ1,
     0,
     1,
     {},
     HERETIC_S_KEYGIZMO2,
     0,
     0}, // HERETIC_S_KEYGIZMO1
    {HERETIC_SPR_KGZ1, 0, 1, A_InitKeyGizmo, HERETIC_S_KEYGIZMO3, 0,
     0},                                                 // HERETIC_S_KEYGIZMO2
    {HERETIC_SPR_KGZ1, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_KEYGIZMO3
    {HERETIC_SPR_KGZB,
     0,
     1,
     {},
     HERETIC_S_KGZ_START,
     0,
     0}, // HERETIC_S_KGZ_START
    {HERETIC_SPR_KGZB,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_KGZ_BLUEFLOAT1
    {HERETIC_SPR_KGZG,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_KGZ_GREENFLOAT1
    {HERETIC_SPR_KGZY,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_KGZ_YELLOWFLOAT1
    {HERETIC_SPR_VLCO,
     0,
     350,
     {},
     HERETIC_S_VOLCANO2,
     0,
     0}, // HERETIC_S_VOLCANO1
    {HERETIC_SPR_VLCO, 0, 35, A_VolcanoSet, HERETIC_S_VOLCANO3, 0,
     0}, // HERETIC_S_VOLCANO2
    {HERETIC_SPR_VLCO,
     1,
     3,
     {},
     HERETIC_S_VOLCANO4,
     0,
     0}, // HERETIC_S_VOLCANO3
    {HERETIC_SPR_VLCO,
     2,
     3,
     {},
     HERETIC_S_VOLCANO5,
     0,
     0}, // HERETIC_S_VOLCANO4
    {HERETIC_SPR_VLCO,
     3,
     3,
     {},
     HERETIC_S_VOLCANO6,
     0,
     0}, // HERETIC_S_VOLCANO5
    {HERETIC_SPR_VLCO,
     1,
     3,
     {},
     HERETIC_S_VOLCANO7,
     0,
     0}, // HERETIC_S_VOLCANO6
    {HERETIC_SPR_VLCO,
     2,
     3,
     {},
     HERETIC_S_VOLCANO8,
     0,
     0}, // HERETIC_S_VOLCANO7
    {HERETIC_SPR_VLCO,
     3,
     3,
     {},
     HERETIC_S_VOLCANO9,
     0,
     0}, // HERETIC_S_VOLCANO8
    {HERETIC_SPR_VLCO, 4, 10, A_VolcanoBlast, HERETIC_S_VOLCANO2, 0,
     0}, // HERETIC_S_VOLCANO9
    {HERETIC_SPR_VFBL, 0, 4, A_BeastPuff, HERETIC_S_VOLCANOBALL2, 0,
     0}, // HERETIC_S_VOLCANOBALL1
    {HERETIC_SPR_VFBL, 1, 4, A_BeastPuff, HERETIC_S_VOLCANOBALL1, 0,
     0}, // HERETIC_S_VOLCANOBALL2
    {HERETIC_SPR_XPL1, 0, 4, A_VolcBallImpact, HERETIC_S_VOLCANOBALLX2, 0,
     0}, // HERETIC_S_VOLCANOBALLX1
    {HERETIC_SPR_XPL1,
     1,
     4,
     {},
     HERETIC_S_VOLCANOBALLX3,
     0,
     0}, // HERETIC_S_VOLCANOBALLX2
    {HERETIC_SPR_XPL1,
     2,
     4,
     {},
     HERETIC_S_VOLCANOBALLX4,
     0,
     0}, // HERETIC_S_VOLCANOBALLX3
    {HERETIC_SPR_XPL1,
     3,
     4,
     {},
     HERETIC_S_VOLCANOBALLX5,
     0,
     0}, // HERETIC_S_VOLCANOBALLX4
    {HERETIC_SPR_XPL1,
     4,
     4,
     {},
     HERETIC_S_VOLCANOBALLX6,
     0,
     0}, // HERETIC_S_VOLCANOBALLX5
    {HERETIC_SPR_XPL1,
     5,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_VOLCANOBALLX6
    {HERETIC_SPR_VTFB,
     0,
     4,
     {},
     HERETIC_S_VOLCANOTBALL2,
     0,
     0}, // HERETIC_S_VOLCANOTBALL1
    {HERETIC_SPR_VTFB,
     1,
     4,
     {},
     HERETIC_S_VOLCANOTBALL1,
     0,
     0}, // HERETIC_S_VOLCANOTBALL2
    {HERETIC_SPR_SFFI,
     2,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX2,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX1
    {HERETIC_SPR_SFFI,
     1,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX3,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX2
    {HERETIC_SPR_SFFI,
     0,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX4,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX3
    {HERETIC_SPR_SFFI,
     1,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX5,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX4
    {HERETIC_SPR_SFFI,
     2,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX6,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX5
    {HERETIC_SPR_SFFI,
     3,
     4,
     {},
     HERETIC_S_VOLCANOTBALLX7,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX6
    {HERETIC_SPR_SFFI,
     4,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_VOLCANOTBALLX7
    {HERETIC_SPR_TGLT, 0, 8, A_SpawnTeleGlitter, HERETIC_S_TELEGLITGEN1, 0,
     0}, // HERETIC_S_TELEGLITGEN1
    {HERETIC_SPR_TGLT, 5, 8, A_SpawnTeleGlitter2, HERETIC_S_TELEGLITGEN2, 0,
     0}, // HERETIC_S_TELEGLITGEN2
    {HERETIC_SPR_TGLT,
     32768,
     2,
     {},
     HERETIC_S_TELEGLITTER1_2,
     0,
     0}, // HERETIC_S_TELEGLITTER1_1
    {HERETIC_SPR_TGLT, 32769, 2, A_AccTeleGlitter, HERETIC_S_TELEGLITTER1_3, 0,
     0}, // HERETIC_S_TELEGLITTER1_2
    {HERETIC_SPR_TGLT,
     32770,
     2,
     {},
     HERETIC_S_TELEGLITTER1_4,
     0,
     0}, // HERETIC_S_TELEGLITTER1_3
    {HERETIC_SPR_TGLT, 32771, 2, A_AccTeleGlitter, HERETIC_S_TELEGLITTER1_5, 0,
     0}, // HERETIC_S_TELEGLITTER1_4
    {HERETIC_SPR_TGLT,
     32772,
     2,
     {},
     HERETIC_S_TELEGLITTER1_1,
     0,
     0}, // HERETIC_S_TELEGLITTER1_5
    {HERETIC_SPR_TGLT,
     32773,
     2,
     {},
     HERETIC_S_TELEGLITTER2_2,
     0,
     0}, // HERETIC_S_TELEGLITTER2_1
    {HERETIC_SPR_TGLT, 32774, 2, A_AccTeleGlitter, HERETIC_S_TELEGLITTER2_3, 0,
     0}, // HERETIC_S_TELEGLITTER2_2
    {HERETIC_SPR_TGLT,
     32775,
     2,
     {},
     HERETIC_S_TELEGLITTER2_4,
     0,
     0}, // HERETIC_S_TELEGLITTER2_3
    {HERETIC_SPR_TGLT, 32776, 2, A_AccTeleGlitter, HERETIC_S_TELEGLITTER2_5, 0,
     0}, // HERETIC_S_TELEGLITTER2_4
    {HERETIC_SPR_TGLT,
     32777,
     2,
     {},
     HERETIC_S_TELEGLITTER2_1,
     0,
     0}, // HERETIC_S_TELEGLITTER2_5
    {HERETIC_SPR_TELE, 32768, 6, {}, HERETIC_S_TFOG2, 0, 0},  // HERETIC_S_TFOG1
    {HERETIC_SPR_TELE, 32769, 6, {}, HERETIC_S_TFOG3, 0, 0},  // HERETIC_S_TFOG2
    {HERETIC_SPR_TELE, 32770, 6, {}, HERETIC_S_TFOG4, 0, 0},  // HERETIC_S_TFOG3
    {HERETIC_SPR_TELE, 32771, 6, {}, HERETIC_S_TFOG5, 0, 0},  // HERETIC_S_TFOG4
    {HERETIC_SPR_TELE, 32772, 6, {}, HERETIC_S_TFOG6, 0, 0},  // HERETIC_S_TFOG5
    {HERETIC_SPR_TELE, 32773, 6, {}, HERETIC_S_TFOG7, 0, 0},  // HERETIC_S_TFOG6
    {HERETIC_SPR_TELE, 32774, 6, {}, HERETIC_S_TFOG8, 0, 0},  // HERETIC_S_TFOG7
    {HERETIC_SPR_TELE, 32775, 6, {}, HERETIC_S_TFOG9, 0, 0},  // HERETIC_S_TFOG8
    {HERETIC_SPR_TELE, 32774, 6, {}, HERETIC_S_TFOG10, 0, 0}, // HERETIC_S_TFOG9
    {HERETIC_SPR_TELE,
     32773,
     6,
     {},
     HERETIC_S_TFOG11,
     0,
     0}, // HERETIC_S_TFOG10
    {HERETIC_SPR_TELE,
     32772,
     6,
     {},
     HERETIC_S_TFOG12,
     0,
     0}, // HERETIC_S_TFOG11
    {HERETIC_SPR_TELE,
     32771,
     6,
     {},
     HERETIC_S_TFOG13,
     0,
     0},                                                    // HERETIC_S_TFOG12
    {HERETIC_SPR_TELE, 32770, 6, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_TFOG13
    {HERETIC_SPR_STFF, 0, 0, A_Light0, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_LIGHTDONE
    {HERETIC_SPR_STFF, 0, 1, A_WeaponReady, HERETIC_S_STAFFREADY, 0,
     0}, // HERETIC_S_STAFFREADY
    {HERETIC_SPR_STFF, 0, 1, A_Lower, HERETIC_S_STAFFDOWN, 0,
     0}, // HERETIC_S_STAFFDOWN
    {HERETIC_SPR_STFF, 0, 1, A_Raise, HERETIC_S_STAFFUP, 0,
     0}, // HERETIC_S_STAFFUP
    {HERETIC_SPR_STFF, 3, 4, A_WeaponReady, HERETIC_S_STAFFREADY2_2, 0,
     0}, // HERETIC_S_STAFFREADY2_1
    {HERETIC_SPR_STFF, 4, 4, A_WeaponReady, HERETIC_S_STAFFREADY2_3, 0,
     0}, // HERETIC_S_STAFFREADY2_2
    {HERETIC_SPR_STFF, 5, 4, A_WeaponReady, HERETIC_S_STAFFREADY2_1, 0,
     0}, // HERETIC_S_STAFFREADY2_3
    {HERETIC_SPR_STFF, 3, 1, A_Lower, HERETIC_S_STAFFDOWN2, 0,
     0}, // HERETIC_S_STAFFDOWN2
    {HERETIC_SPR_STFF, 3, 1, A_Raise, HERETIC_S_STAFFUP2, 0,
     0}, // HERETIC_S_STAFFUP2
    {HERETIC_SPR_STFF,
     1,
     6,
     {},
     HERETIC_S_STAFFATK1_2,
     0,
     0}, // HERETIC_S_STAFFATK1_1
    {HERETIC_SPR_STFF, 2, 8, A_StaffAttackPL1, HERETIC_S_STAFFATK1_3, 0,
     0}, // HERETIC_S_STAFFATK1_2
    {HERETIC_SPR_STFF, 1, 8, A_ReFire, HERETIC_S_STAFFREADY, 0,
     0}, // HERETIC_S_STAFFATK1_3
    {HERETIC_SPR_STFF,
     6,
     6,
     {},
     HERETIC_S_STAFFATK2_2,
     0,
     0}, // HERETIC_S_STAFFATK2_1
    {HERETIC_SPR_STFF, 7, 8, A_StaffAttackPL2, HERETIC_S_STAFFATK2_3, 0,
     0}, // HERETIC_S_STAFFATK2_2
    {HERETIC_SPR_STFF, 6, 8, A_ReFire, HERETIC_S_STAFFREADY2_1, 0,
     0}, // HERETIC_S_STAFFATK2_3
    {HERETIC_SPR_PUF3,
     32768,
     4,
     {},
     HERETIC_S_STAFFPUFF2,
     0,
     0}, // HERETIC_S_STAFFPUFF1
    {HERETIC_SPR_PUF3,
     1,
     4,
     {},
     HERETIC_S_STAFFPUFF3,
     0,
     0}, // HERETIC_S_STAFFPUFF2
    {HERETIC_SPR_PUF3,
     2,
     4,
     {},
     HERETIC_S_STAFFPUFF4,
     0,
     0},                                                // HERETIC_S_STAFFPUFF3
    {HERETIC_SPR_PUF3, 3, 4, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_STAFFPUFF4
    {HERETIC_SPR_PUF4,
     32768,
     4,
     {},
     HERETIC_S_STAFFPUFF2_2,
     0,
     0}, // HERETIC_S_STAFFPUFF2_1
    {HERETIC_SPR_PUF4,
     32769,
     4,
     {},
     HERETIC_S_STAFFPUFF2_3,
     0,
     0}, // HERETIC_S_STAFFPUFF2_2
    {HERETIC_SPR_PUF4,
     32770,
     4,
     {},
     HERETIC_S_STAFFPUFF2_4,
     0,
     0}, // HERETIC_S_STAFFPUFF2_3
    {HERETIC_SPR_PUF4,
     32771,
     4,
     {},
     HERETIC_S_STAFFPUFF2_5,
     0,
     0}, // HERETIC_S_STAFFPUFF2_4
    {HERETIC_SPR_PUF4,
     32772,
     4,
     {},
     HERETIC_S_STAFFPUFF2_6,
     0,
     0}, // HERETIC_S_STAFFPUFF2_5
    {HERETIC_SPR_PUF4,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_STAFFPUFF2_6
    {HERETIC_SPR_BEAK, 0, 1, A_BeakReady, HERETIC_S_BEAKREADY, 0,
     0}, // HERETIC_S_BEAKREADY
    {HERETIC_SPR_BEAK, 0, 1, A_Lower, HERETIC_S_BEAKDOWN, 0,
     0}, // HERETIC_S_BEAKDOWN
    {HERETIC_SPR_BEAK, 0, 1, A_BeakRaise, HERETIC_S_BEAKUP, 0,
     0}, // HERETIC_S_BEAKUP
    {HERETIC_SPR_BEAK, 0, 18, A_BeakAttackPL1, HERETIC_S_BEAKREADY, 0,
     0}, // HERETIC_S_BEAKATK1_1
    {HERETIC_SPR_BEAK, 0, 12, A_BeakAttackPL2, HERETIC_S_BEAKREADY, 0,
     0},                                                 // HERETIC_S_BEAKATK2_1
    {HERETIC_SPR_WGNT, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_WGNT
    {HERETIC_SPR_GAUN, 0, 1, A_WeaponReady, HERETIC_S_GAUNTLETREADY, 0,
     0}, // HERETIC_S_GAUNTLETREADY
    {HERETIC_SPR_GAUN, 0, 1, A_Lower, HERETIC_S_GAUNTLETDOWN, 0,
     0}, // HERETIC_S_GAUNTLETDOWN
    {HERETIC_SPR_GAUN, 0, 1, A_Raise, HERETIC_S_GAUNTLETUP, 0,
     0}, // HERETIC_S_GAUNTLETUP
    {HERETIC_SPR_GAUN, 6, 4, A_WeaponReady, HERETIC_S_GAUNTLETREADY2_2, 0,
     0}, // HERETIC_S_GAUNTLETREADY2_1
    {HERETIC_SPR_GAUN, 7, 4, A_WeaponReady, HERETIC_S_GAUNTLETREADY2_3, 0,
     0}, // HERETIC_S_GAUNTLETREADY2_2
    {HERETIC_SPR_GAUN, 8, 4, A_WeaponReady, HERETIC_S_GAUNTLETREADY2_1, 0,
     0}, // HERETIC_S_GAUNTLETREADY2_3
    {HERETIC_SPR_GAUN, 6, 1, A_Lower, HERETIC_S_GAUNTLETDOWN2, 0,
     0}, // HERETIC_S_GAUNTLETDOWN2
    {HERETIC_SPR_GAUN, 6, 1, A_Raise, HERETIC_S_GAUNTLETUP2, 0,
     0}, // HERETIC_S_GAUNTLETUP2
    {HERETIC_SPR_GAUN,
     1,
     4,
     {},
     HERETIC_S_GAUNTLETATK1_2,
     0,
     0}, // HERETIC_S_GAUNTLETATK1_1
    {HERETIC_SPR_GAUN,
     2,
     4,
     {},
     HERETIC_S_GAUNTLETATK1_3,
     0,
     0}, // HERETIC_S_GAUNTLETATK1_2
    {HERETIC_SPR_GAUN, 32771, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK1_4, 0,
     0}, // HERETIC_S_GAUNTLETATK1_3
    {HERETIC_SPR_GAUN, 32772, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK1_5, 0,
     0}, // HERETIC_S_GAUNTLETATK1_4
    {HERETIC_SPR_GAUN, 32773, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK1_6, 0,
     0}, // HERETIC_S_GAUNTLETATK1_5
    {HERETIC_SPR_GAUN, 2, 4, A_ReFire, HERETIC_S_GAUNTLETATK1_7, 0,
     0}, // HERETIC_S_GAUNTLETATK1_6
    {HERETIC_SPR_GAUN, 1, 4, A_Light0, HERETIC_S_GAUNTLETREADY, 0,
     0}, // HERETIC_S_GAUNTLETATK1_7
    {HERETIC_SPR_GAUN,
     9,
     4,
     {},
     HERETIC_S_GAUNTLETATK2_2,
     0,
     0}, // HERETIC_S_GAUNTLETATK2_1
    {HERETIC_SPR_GAUN,
     10,
     4,
     {},
     HERETIC_S_GAUNTLETATK2_3,
     0,
     0}, // HERETIC_S_GAUNTLETATK2_2
    {HERETIC_SPR_GAUN, 32779, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK2_4, 0,
     0}, // HERETIC_S_GAUNTLETATK2_3
    {HERETIC_SPR_GAUN, 32780, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK2_5, 0,
     0}, // HERETIC_S_GAUNTLETATK2_4
    {HERETIC_SPR_GAUN, 32781, 4, A_GauntletAttack, HERETIC_S_GAUNTLETATK2_6, 0,
     0}, // HERETIC_S_GAUNTLETATK2_5
    {HERETIC_SPR_GAUN, 10, 4, A_ReFire, HERETIC_S_GAUNTLETATK2_7, 0,
     0}, // HERETIC_S_GAUNTLETATK2_6
    {HERETIC_SPR_GAUN, 9, 4, A_Light0, HERETIC_S_GAUNTLETREADY2_1, 0,
     0}, // HERETIC_S_GAUNTLETATK2_7
    {HERETIC_SPR_PUF1,
     32768,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF1_2,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF1_1
    {HERETIC_SPR_PUF1,
     32769,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF1_3,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF1_2
    {HERETIC_SPR_PUF1,
     32770,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF1_4,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF1_3
    {HERETIC_SPR_PUF1,
     32771,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF1_4
    {HERETIC_SPR_PUF1,
     32772,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF2_2,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF2_1
    {HERETIC_SPR_PUF1,
     32773,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF2_3,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF2_2
    {HERETIC_SPR_PUF1,
     32774,
     4,
     {},
     HERETIC_S_GAUNTLETPUFF2_4,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF2_3
    {HERETIC_SPR_PUF1,
     32775,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_GAUNTLETPUFF2_4
    {HERETIC_SPR_WBLS, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_BLSR
    {HERETIC_SPR_BLSR, 0, 1, A_WeaponReady, HERETIC_S_BLASTERREADY, 0,
     0}, // HERETIC_S_BLASTERREADY
    {HERETIC_SPR_BLSR, 0, 1, A_Lower, HERETIC_S_BLASTERDOWN, 0,
     0}, // HERETIC_S_BLASTERDOWN
    {HERETIC_SPR_BLSR, 0, 1, A_Raise, HERETIC_S_BLASTERUP, 0,
     0}, // HERETIC_S_BLASTERUP
    {HERETIC_SPR_BLSR,
     1,
     3,
     {},
     HERETIC_S_BLASTERATK1_2,
     0,
     0}, // HERETIC_S_BLASTERATK1_1
    {HERETIC_SPR_BLSR,
     2,
     3,
     {},
     HERETIC_S_BLASTERATK1_3,
     0,
     0}, // HERETIC_S_BLASTERATK1_2
    {HERETIC_SPR_BLSR, 3, 2, A_FireBlasterPL1, HERETIC_S_BLASTERATK1_4, 0,
     0}, // HERETIC_S_BLASTERATK1_3
    {HERETIC_SPR_BLSR,
     2,
     2,
     {},
     HERETIC_S_BLASTERATK1_5,
     0,
     0}, // HERETIC_S_BLASTERATK1_4
    {HERETIC_SPR_BLSR,
     1,
     2,
     {},
     HERETIC_S_BLASTERATK1_6,
     0,
     0}, // HERETIC_S_BLASTERATK1_5
    {HERETIC_SPR_BLSR, 0, 0, A_ReFire, HERETIC_S_BLASTERREADY, 0,
     0}, // HERETIC_S_BLASTERATK1_6
    {HERETIC_SPR_BLSR,
     1,
     0,
     {},
     HERETIC_S_BLASTERATK2_2,
     0,
     0}, // HERETIC_S_BLASTERATK2_1
    {HERETIC_SPR_BLSR,
     2,
     0,
     {},
     HERETIC_S_BLASTERATK2_3,
     0,
     0}, // HERETIC_S_BLASTERATK2_2
    {HERETIC_SPR_BLSR, 3, 3, A_FireBlasterPL2, HERETIC_S_BLASTERATK2_4, 0,
     0}, // HERETIC_S_BLASTERATK2_3
    {HERETIC_SPR_BLSR,
     2,
     4,
     {},
     HERETIC_S_BLASTERATK2_5,
     0,
     0}, // HERETIC_S_BLASTERATK2_4
    {HERETIC_SPR_BLSR,
     1,
     4,
     {},
     HERETIC_S_BLASTERATK2_6,
     0,
     0}, // HERETIC_S_BLASTERATK2_5
    {HERETIC_SPR_BLSR, 0, 0, A_ReFire, HERETIC_S_BLASTERREADY, 0,
     0}, // HERETIC_S_BLASTERATK2_6
    {HERETIC_SPR_ACLO,
     4,
     200,
     {},
     HERETIC_S_BLASTERFX1_1,
     0,
     0}, // HERETIC_S_BLASTERFX1_1
    {HERETIC_SPR_FX18, 32768, 3, A_SpawnRippers, HERETIC_S_BLASTERFXI1_2, 0,
     0}, // HERETIC_S_BLASTERFXI1_1
    {HERETIC_SPR_FX18,
     32769,
     3,
     {},
     HERETIC_S_BLASTERFXI1_3,
     0,
     0}, // HERETIC_S_BLASTERFXI1_2
    {HERETIC_SPR_FX18,
     32770,
     4,
     {},
     HERETIC_S_BLASTERFXI1_4,
     0,
     0}, // HERETIC_S_BLASTERFXI1_3
    {HERETIC_SPR_FX18,
     32771,
     4,
     {},
     HERETIC_S_BLASTERFXI1_5,
     0,
     0}, // HERETIC_S_BLASTERFXI1_4
    {HERETIC_SPR_FX18,
     32772,
     4,
     {},
     HERETIC_S_BLASTERFXI1_6,
     0,
     0}, // HERETIC_S_BLASTERFXI1_5
    {HERETIC_SPR_FX18,
     32773,
     4,
     {},
     HERETIC_S_BLASTERFXI1_7,
     0,
     0}, // HERETIC_S_BLASTERFXI1_6
    {HERETIC_SPR_FX18,
     32774,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLASTERFXI1_7
    {HERETIC_SPR_FX18,
     7,
     4,
     {},
     HERETIC_S_BLASTERSMOKE2,
     0,
     0}, // HERETIC_S_BLASTERSMOKE1
    {HERETIC_SPR_FX18,
     8,
     4,
     {},
     HERETIC_S_BLASTERSMOKE3,
     0,
     0}, // HERETIC_S_BLASTERSMOKE2
    {HERETIC_SPR_FX18,
     9,
     4,
     {},
     HERETIC_S_BLASTERSMOKE4,
     0,
     0}, // HERETIC_S_BLASTERSMOKE3
    {HERETIC_SPR_FX18,
     10,
     4,
     {},
     HERETIC_S_BLASTERSMOKE5,
     0,
     0}, // HERETIC_S_BLASTERSMOKE4
    {HERETIC_SPR_FX18,
     11,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLASTERSMOKE5
    {HERETIC_SPR_FX18, 12, 4, {}, HERETIC_S_RIPPER2, 0, 0}, // HERETIC_S_RIPPER1
    {HERETIC_SPR_FX18, 13, 5, {}, HERETIC_S_RIPPER1, 0, 0}, // HERETIC_S_RIPPER2
    {HERETIC_SPR_FX18,
     32782,
     4,
     {},
     HERETIC_S_RIPPERX2,
     0,
     0}, // HERETIC_S_RIPPERX1
    {HERETIC_SPR_FX18,
     32783,
     4,
     {},
     HERETIC_S_RIPPERX3,
     0,
     0}, // HERETIC_S_RIPPERX2
    {HERETIC_SPR_FX18,
     32784,
     4,
     {},
     HERETIC_S_RIPPERX4,
     0,
     0}, // HERETIC_S_RIPPERX3
    {HERETIC_SPR_FX18,
     32785,
     4,
     {},
     HERETIC_S_RIPPERX5,
     0,
     0}, // HERETIC_S_RIPPERX4
    {HERETIC_SPR_FX18,
     32786,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RIPPERX5
    {HERETIC_SPR_FX17,
     32768,
     4,
     {},
     HERETIC_S_BLASTERPUFF1_2,
     0,
     0}, // HERETIC_S_BLASTERPUFF1_1
    {HERETIC_SPR_FX17,
     32769,
     4,
     {},
     HERETIC_S_BLASTERPUFF1_3,
     0,
     0}, // HERETIC_S_BLASTERPUFF1_2
    {HERETIC_SPR_FX17,
     32770,
     4,
     {},
     HERETIC_S_BLASTERPUFF1_4,
     0,
     0}, // HERETIC_S_BLASTERPUFF1_3
    {HERETIC_SPR_FX17,
     32771,
     4,
     {},
     HERETIC_S_BLASTERPUFF1_5,
     0,
     0}, // HERETIC_S_BLASTERPUFF1_4
    {HERETIC_SPR_FX17,
     32772,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLASTERPUFF1_5
    {HERETIC_SPR_FX17,
     32773,
     3,
     {},
     HERETIC_S_BLASTERPUFF2_2,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_1
    {HERETIC_SPR_FX17,
     32774,
     3,
     {},
     HERETIC_S_BLASTERPUFF2_3,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_2
    {HERETIC_SPR_FX17,
     32775,
     4,
     {},
     HERETIC_S_BLASTERPUFF2_4,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_3
    {HERETIC_SPR_FX17,
     32776,
     4,
     {},
     HERETIC_S_BLASTERPUFF2_5,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_4
    {HERETIC_SPR_FX17,
     32777,
     4,
     {},
     HERETIC_S_BLASTERPUFF2_6,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_5
    {HERETIC_SPR_FX17,
     32778,
     4,
     {},
     HERETIC_S_BLASTERPUFF2_7,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_6
    {HERETIC_SPR_FX17,
     32779,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLASTERPUFF2_7
    {HERETIC_SPR_WMCE, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_WMCE
    {HERETIC_SPR_MACE, 0, 1, A_WeaponReady, HERETIC_S_MACEREADY, 0,
     0}, // HERETIC_S_MACEREADY
    {HERETIC_SPR_MACE, 0, 1, A_Lower, HERETIC_S_MACEDOWN, 0,
     0}, // HERETIC_S_MACEDOWN
    {HERETIC_SPR_MACE, 0, 1, A_Raise, HERETIC_S_MACEUP, 0,
     0}, // HERETIC_S_MACEUP
    {HERETIC_SPR_MACE,
     1,
     4,
     {},
     HERETIC_S_MACEATK1_2,
     0,
     0}, // HERETIC_S_MACEATK1_1
    {HERETIC_SPR_MACE, 2, 3, A_FireMacePL1, HERETIC_S_MACEATK1_3, 0,
     0}, // HERETIC_S_MACEATK1_2
    {HERETIC_SPR_MACE, 3, 3, A_FireMacePL1, HERETIC_S_MACEATK1_4, 0,
     0}, // HERETIC_S_MACEATK1_3
    {HERETIC_SPR_MACE, 4, 3, A_FireMacePL1, HERETIC_S_MACEATK1_5, 0,
     0}, // HERETIC_S_MACEATK1_4
    {HERETIC_SPR_MACE, 5, 3, A_FireMacePL1, HERETIC_S_MACEATK1_6, 0,
     0}, // HERETIC_S_MACEATK1_5
    {HERETIC_SPR_MACE, 2, 4, A_ReFire, HERETIC_S_MACEATK1_7, 0,
     0}, // HERETIC_S_MACEATK1_6
    {HERETIC_SPR_MACE,
     3,
     4,
     {},
     HERETIC_S_MACEATK1_8,
     0,
     0}, // HERETIC_S_MACEATK1_7
    {HERETIC_SPR_MACE,
     4,
     4,
     {},
     HERETIC_S_MACEATK1_9,
     0,
     0}, // HERETIC_S_MACEATK1_8
    {HERETIC_SPR_MACE,
     5,
     4,
     {},
     HERETIC_S_MACEATK1_10,
     0,
     0}, // HERETIC_S_MACEATK1_9
    {HERETIC_SPR_MACE,
     1,
     4,
     {},
     HERETIC_S_MACEREADY,
     0,
     0}, // HERETIC_S_MACEATK1_10
    {HERETIC_SPR_MACE,
     1,
     4,
     {},
     HERETIC_S_MACEATK2_2,
     0,
     0}, // HERETIC_S_MACEATK2_1
    {HERETIC_SPR_MACE, 3, 4, A_FireMacePL2, HERETIC_S_MACEATK2_3, 0,
     0}, // HERETIC_S_MACEATK2_2
    {HERETIC_SPR_MACE,
     1,
     4,
     {},
     HERETIC_S_MACEATK2_4,
     0,
     0}, // HERETIC_S_MACEATK2_3
    {HERETIC_SPR_MACE, 0, 8, A_ReFire, HERETIC_S_MACEREADY, 0,
     0}, // HERETIC_S_MACEATK2_4
    {HERETIC_SPR_FX02, 0, 4, A_MacePL1Check, HERETIC_S_MACEFX1_2, 0,
     0}, // HERETIC_S_MACEFX1_1
    {HERETIC_SPR_FX02, 1, 4, A_MacePL1Check, HERETIC_S_MACEFX1_1, 0,
     0}, // HERETIC_S_MACEFX1_2
    {HERETIC_SPR_FX02, 32773, 4, A_MaceBallImpact, HERETIC_S_MACEFXI1_2, 0,
     0}, // HERETIC_S_MACEFXI1_1
    {HERETIC_SPR_FX02,
     32774,
     4,
     {},
     HERETIC_S_MACEFXI1_3,
     0,
     0}, // HERETIC_S_MACEFXI1_2
    {HERETIC_SPR_FX02,
     32775,
     4,
     {},
     HERETIC_S_MACEFXI1_4,
     0,
     0}, // HERETIC_S_MACEFXI1_3
    {HERETIC_SPR_FX02,
     32776,
     4,
     {},
     HERETIC_S_MACEFXI1_5,
     0,
     0}, // HERETIC_S_MACEFXI1_4
    {HERETIC_SPR_FX02,
     32777,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MACEFXI1_5
    {HERETIC_SPR_FX02,
     2,
     4,
     {},
     HERETIC_S_MACEFX2_2,
     0,
     0}, // HERETIC_S_MACEFX2_1
    {HERETIC_SPR_FX02,
     3,
     4,
     {},
     HERETIC_S_MACEFX2_1,
     0,
     0}, // HERETIC_S_MACEFX2_2
    {HERETIC_SPR_FX02, 32773, 4, A_MaceBallImpact2, HERETIC_S_MACEFXI1_2, 0,
     0}, // HERETIC_S_MACEFXI2_1
    {HERETIC_SPR_FX02,
     0,
     4,
     {},
     HERETIC_S_MACEFX3_2,
     0,
     0}, // HERETIC_S_MACEFX3_1
    {HERETIC_SPR_FX02,
     1,
     4,
     {},
     HERETIC_S_MACEFX3_1,
     0,
     0}, // HERETIC_S_MACEFX3_2
    {HERETIC_SPR_FX02,
     4,
     99,
     {},
     HERETIC_S_MACEFX4_1,
     0,
     0}, // HERETIC_S_MACEFX4_1
    {HERETIC_SPR_FX02, 32770, 4, A_DeathBallImpact, HERETIC_S_MACEFXI1_2, 0,
     0},                                                 // HERETIC_S_MACEFXI4_1
    {HERETIC_SPR_WSKL, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_WSKL
    {HERETIC_SPR_HROD, 0, 1, A_WeaponReady, HERETIC_S_HORNRODREADY, 0,
     0}, // HERETIC_S_HORNRODREADY
    {HERETIC_SPR_HROD, 0, 1, A_Lower, HERETIC_S_HORNRODDOWN, 0,
     0}, // HERETIC_S_HORNRODDOWN
    {HERETIC_SPR_HROD, 0, 1, A_Raise, HERETIC_S_HORNRODUP, 0,
     0}, // HERETIC_S_HORNRODUP
    {HERETIC_SPR_HROD, 0, 4, A_FireSkullRodPL1, HERETIC_S_HORNRODATK1_2, 0,
     0}, // HERETIC_S_HORNRODATK1_1
    {HERETIC_SPR_HROD, 1, 4, A_FireSkullRodPL1, HERETIC_S_HORNRODATK1_3, 0,
     0}, // HERETIC_S_HORNRODATK1_2
    {HERETIC_SPR_HROD, 1, 0, A_ReFire, HERETIC_S_HORNRODREADY, 0,
     0}, // HERETIC_S_HORNRODATK1_3
    {HERETIC_SPR_HROD,
     2,
     2,
     {},
     HERETIC_S_HORNRODATK2_2,
     0,
     0}, // HERETIC_S_HORNRODATK2_1
    {HERETIC_SPR_HROD,
     3,
     3,
     {},
     HERETIC_S_HORNRODATK2_3,
     0,
     0}, // HERETIC_S_HORNRODATK2_2
    {HERETIC_SPR_HROD,
     4,
     2,
     {},
     HERETIC_S_HORNRODATK2_4,
     0,
     0}, // HERETIC_S_HORNRODATK2_3
    {HERETIC_SPR_HROD,
     5,
     3,
     {},
     HERETIC_S_HORNRODATK2_5,
     0,
     0}, // HERETIC_S_HORNRODATK2_4
    {HERETIC_SPR_HROD, 6, 4, A_FireSkullRodPL2, HERETIC_S_HORNRODATK2_6, 0,
     0}, // HERETIC_S_HORNRODATK2_5
    {HERETIC_SPR_HROD,
     5,
     2,
     {},
     HERETIC_S_HORNRODATK2_7,
     0,
     0}, // HERETIC_S_HORNRODATK2_6
    {HERETIC_SPR_HROD,
     4,
     3,
     {},
     HERETIC_S_HORNRODATK2_8,
     0,
     0}, // HERETIC_S_HORNRODATK2_7
    {HERETIC_SPR_HROD,
     3,
     2,
     {},
     HERETIC_S_HORNRODATK2_9,
     0,
     0}, // HERETIC_S_HORNRODATK2_8
    {HERETIC_SPR_HROD, 2, 2, A_ReFire, HERETIC_S_HORNRODREADY, 0,
     0}, // HERETIC_S_HORNRODATK2_9
    {HERETIC_SPR_FX00,
     32768,
     6,
     {},
     HERETIC_S_HRODFX1_2,
     0,
     0}, // HERETIC_S_HRODFX1_1
    {HERETIC_SPR_FX00,
     32769,
     6,
     {},
     HERETIC_S_HRODFX1_1,
     0,
     0}, // HERETIC_S_HRODFX1_2
    {HERETIC_SPR_FX00,
     32775,
     5,
     {},
     HERETIC_S_HRODFXI1_2,
     0,
     0}, // HERETIC_S_HRODFXI1_1
    {HERETIC_SPR_FX00,
     32776,
     5,
     {},
     HERETIC_S_HRODFXI1_3,
     0,
     0}, // HERETIC_S_HRODFXI1_2
    {HERETIC_SPR_FX00,
     32777,
     4,
     {},
     HERETIC_S_HRODFXI1_4,
     0,
     0}, // HERETIC_S_HRODFXI1_3
    {HERETIC_SPR_FX00,
     32778,
     4,
     {},
     HERETIC_S_HRODFXI1_5,
     0,
     0}, // HERETIC_S_HRODFXI1_4
    {HERETIC_SPR_FX00,
     32779,
     3,
     {},
     HERETIC_S_HRODFXI1_6,
     0,
     0}, // HERETIC_S_HRODFXI1_5
    {HERETIC_SPR_FX00,
     32780,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_HRODFXI1_6
    {HERETIC_SPR_FX00,
     32770,
     3,
     {},
     HERETIC_S_HRODFX2_2,
     0,
     0}, // HERETIC_S_HRODFX2_1
    {HERETIC_SPR_FX00, 32771, 3, A_SkullRodPL2Seek, HERETIC_S_HRODFX2_3, 0,
     0}, // HERETIC_S_HRODFX2_2
    {HERETIC_SPR_FX00,
     32772,
     3,
     {},
     HERETIC_S_HRODFX2_4,
     0,
     0}, // HERETIC_S_HRODFX2_3
    {HERETIC_SPR_FX00, 32773, 3, A_SkullRodPL2Seek, HERETIC_S_HRODFX2_1, 0,
     0}, // HERETIC_S_HRODFX2_4
    {HERETIC_SPR_FX00, 32775, 5, A_AddPlayerRain, HERETIC_S_HRODFXI2_2, 0,
     0}, // HERETIC_S_HRODFXI2_1
    {HERETIC_SPR_FX00,
     32776,
     5,
     {},
     HERETIC_S_HRODFXI2_3,
     0,
     0}, // HERETIC_S_HRODFXI2_2
    {HERETIC_SPR_FX00,
     32777,
     4,
     {},
     HERETIC_S_HRODFXI2_4,
     0,
     0}, // HERETIC_S_HRODFXI2_3
    {HERETIC_SPR_FX00,
     32778,
     3,
     {},
     HERETIC_S_HRODFXI2_5,
     0,
     0}, // HERETIC_S_HRODFXI2_4
    {HERETIC_SPR_FX00,
     32779,
     3,
     {},
     HERETIC_S_HRODFXI2_6,
     0,
     0}, // HERETIC_S_HRODFXI2_5
    {HERETIC_SPR_FX00,
     32780,
     3,
     {},
     HERETIC_S_HRODFXI2_7,
     0,
     0}, // HERETIC_S_HRODFXI2_6
    {HERETIC_SPR_FX00, 6, 1, A_HideInCeiling, HERETIC_S_HRODFXI2_8, 0,
     0}, // HERETIC_S_HRODFXI2_7
    {HERETIC_SPR_FX00, 6, 1, A_SkullRodStorm, HERETIC_S_HRODFXI2_8, 0,
     0}, // HERETIC_S_HRODFXI2_8
    {HERETIC_SPR_FX20,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR1_1
    {HERETIC_SPR_FX21,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR2_1
    {HERETIC_SPR_FX22,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR3_1
    {HERETIC_SPR_FX23,
     32768,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR4_1
    {HERETIC_SPR_FX20, 32769, 4, A_RainImpact, HERETIC_S_RAINPLR1X_2, 0,
     0}, // HERETIC_S_RAINPLR1X_1
    {HERETIC_SPR_FX20,
     32770,
     4,
     {},
     HERETIC_S_RAINPLR1X_3,
     0,
     0}, // HERETIC_S_RAINPLR1X_2
    {HERETIC_SPR_FX20,
     32771,
     4,
     {},
     HERETIC_S_RAINPLR1X_4,
     0,
     0}, // HERETIC_S_RAINPLR1X_3
    {HERETIC_SPR_FX20,
     32772,
     4,
     {},
     HERETIC_S_RAINPLR1X_5,
     0,
     0}, // HERETIC_S_RAINPLR1X_4
    {HERETIC_SPR_FX20,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR1X_5
    {HERETIC_SPR_FX21, 32769, 4, A_RainImpact, HERETIC_S_RAINPLR2X_2, 0,
     0}, // HERETIC_S_RAINPLR2X_1
    {HERETIC_SPR_FX21,
     32770,
     4,
     {},
     HERETIC_S_RAINPLR2X_3,
     0,
     0}, // HERETIC_S_RAINPLR2X_2
    {HERETIC_SPR_FX21,
     32771,
     4,
     {},
     HERETIC_S_RAINPLR2X_4,
     0,
     0}, // HERETIC_S_RAINPLR2X_3
    {HERETIC_SPR_FX21,
     32772,
     4,
     {},
     HERETIC_S_RAINPLR2X_5,
     0,
     0}, // HERETIC_S_RAINPLR2X_4
    {HERETIC_SPR_FX21,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR2X_5
    {HERETIC_SPR_FX22, 32769, 4, A_RainImpact, HERETIC_S_RAINPLR3X_2, 0,
     0}, // HERETIC_S_RAINPLR3X_1
    {HERETIC_SPR_FX22,
     32770,
     4,
     {},
     HERETIC_S_RAINPLR3X_3,
     0,
     0}, // HERETIC_S_RAINPLR3X_2
    {HERETIC_SPR_FX22,
     32771,
     4,
     {},
     HERETIC_S_RAINPLR3X_4,
     0,
     0}, // HERETIC_S_RAINPLR3X_3
    {HERETIC_SPR_FX22,
     32772,
     4,
     {},
     HERETIC_S_RAINPLR3X_5,
     0,
     0}, // HERETIC_S_RAINPLR3X_4
    {HERETIC_SPR_FX22,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR3X_5
    {HERETIC_SPR_FX23, 32769, 4, A_RainImpact, HERETIC_S_RAINPLR4X_2, 0,
     0}, // HERETIC_S_RAINPLR4X_1
    {HERETIC_SPR_FX23,
     32770,
     4,
     {},
     HERETIC_S_RAINPLR4X_3,
     0,
     0}, // HERETIC_S_RAINPLR4X_2
    {HERETIC_SPR_FX23,
     32771,
     4,
     {},
     HERETIC_S_RAINPLR4X_4,
     0,
     0}, // HERETIC_S_RAINPLR4X_3
    {HERETIC_SPR_FX23,
     32772,
     4,
     {},
     HERETIC_S_RAINPLR4X_5,
     0,
     0}, // HERETIC_S_RAINPLR4X_4
    {HERETIC_SPR_FX23,
     32773,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINPLR4X_5
    {HERETIC_SPR_FX20,
     32774,
     4,
     {},
     HERETIC_S_RAINAIRXPLR1_2,
     0,
     0}, // HERETIC_S_RAINAIRXPLR1_1
    {HERETIC_SPR_FX21,
     32774,
     4,
     {},
     HERETIC_S_RAINAIRXPLR2_2,
     0,
     0}, // HERETIC_S_RAINAIRXPLR2_1
    {HERETIC_SPR_FX22,
     32774,
     4,
     {},
     HERETIC_S_RAINAIRXPLR3_2,
     0,
     0}, // HERETIC_S_RAINAIRXPLR3_1
    {HERETIC_SPR_FX23,
     32774,
     4,
     {},
     HERETIC_S_RAINAIRXPLR4_2,
     0,
     0}, // HERETIC_S_RAINAIRXPLR4_1
    {HERETIC_SPR_FX20,
     32775,
     4,
     {},
     HERETIC_S_RAINAIRXPLR1_3,
     0,
     0}, // HERETIC_S_RAINAIRXPLR1_2
    {HERETIC_SPR_FX21,
     32775,
     4,
     {},
     HERETIC_S_RAINAIRXPLR2_3,
     0,
     0}, // HERETIC_S_RAINAIRXPLR2_2
    {HERETIC_SPR_FX22,
     32775,
     4,
     {},
     HERETIC_S_RAINAIRXPLR3_3,
     0,
     0}, // HERETIC_S_RAINAIRXPLR3_2
    {HERETIC_SPR_FX23,
     32775,
     4,
     {},
     HERETIC_S_RAINAIRXPLR4_3,
     0,
     0}, // HERETIC_S_RAINAIRXPLR4_2
    {HERETIC_SPR_FX20,
     32776,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINAIRXPLR1_3
    {HERETIC_SPR_FX21,
     32776,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINAIRXPLR2_3
    {HERETIC_SPR_FX22,
     32776,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINAIRXPLR3_3
    {HERETIC_SPR_FX23,
     32776,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_RAINAIRXPLR4_3
    {HERETIC_SPR_GWND, 0, 1, A_WeaponReady, HERETIC_S_GOLDWANDREADY, 0,
     0}, // HERETIC_S_GOLDWANDREADY
    {HERETIC_SPR_GWND, 0, 1, A_Lower, HERETIC_S_GOLDWANDDOWN, 0,
     0}, // HERETIC_S_GOLDWANDDOWN
    {HERETIC_SPR_GWND, 0, 1, A_Raise, HERETIC_S_GOLDWANDUP, 0,
     0}, // HERETIC_S_GOLDWANDUP
    {HERETIC_SPR_GWND,
     1,
     3,
     {},
     HERETIC_S_GOLDWANDATK1_2,
     0,
     0}, // HERETIC_S_GOLDWANDATK1_1
    {HERETIC_SPR_GWND, 2, 5, A_FireGoldWandPL1, HERETIC_S_GOLDWANDATK1_3, 0,
     0}, // HERETIC_S_GOLDWANDATK1_2
    {HERETIC_SPR_GWND,
     3,
     3,
     {},
     HERETIC_S_GOLDWANDATK1_4,
     0,
     0}, // HERETIC_S_GOLDWANDATK1_3
    {HERETIC_SPR_GWND, 3, 0, A_ReFire, HERETIC_S_GOLDWANDREADY, 0,
     0}, // HERETIC_S_GOLDWANDATK1_4
    {HERETIC_SPR_GWND,
     1,
     3,
     {},
     HERETIC_S_GOLDWANDATK2_2,
     0,
     0}, // HERETIC_S_GOLDWANDATK2_1
    {HERETIC_SPR_GWND, 2, 4, A_FireGoldWandPL2, HERETIC_S_GOLDWANDATK2_3, 0,
     0}, // HERETIC_S_GOLDWANDATK2_2
    {HERETIC_SPR_GWND,
     3,
     3,
     {},
     HERETIC_S_GOLDWANDATK2_4,
     0,
     0}, // HERETIC_S_GOLDWANDATK2_3
    {HERETIC_SPR_GWND, 3, 0, A_ReFire, HERETIC_S_GOLDWANDREADY, 0,
     0}, // HERETIC_S_GOLDWANDATK2_4
    {HERETIC_SPR_FX01,
     32768,
     6,
     {},
     HERETIC_S_GWANDFX1_2,
     0,
     0}, // HERETIC_S_GWANDFX1_1
    {HERETIC_SPR_FX01,
     32769,
     6,
     {},
     HERETIC_S_GWANDFX1_1,
     0,
     0}, // HERETIC_S_GWANDFX1_2
    {HERETIC_SPR_FX01,
     32772,
     3,
     {},
     HERETIC_S_GWANDFXI1_2,
     0,
     0}, // HERETIC_S_GWANDFXI1_1
    {HERETIC_SPR_FX01,
     32773,
     3,
     {},
     HERETIC_S_GWANDFXI1_3,
     0,
     0}, // HERETIC_S_GWANDFXI1_2
    {HERETIC_SPR_FX01,
     32774,
     3,
     {},
     HERETIC_S_GWANDFXI1_4,
     0,
     0}, // HERETIC_S_GWANDFXI1_3
    {HERETIC_SPR_FX01,
     32775,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_GWANDFXI1_4
    {HERETIC_SPR_FX01,
     32770,
     6,
     {},
     HERETIC_S_GWANDFX2_2,
     0,
     0}, // HERETIC_S_GWANDFX2_1
    {HERETIC_SPR_FX01,
     32771,
     6,
     {},
     HERETIC_S_GWANDFX2_1,
     0,
     0}, // HERETIC_S_GWANDFX2_2
    {HERETIC_SPR_PUF2,
     32768,
     3,
     {},
     HERETIC_S_GWANDPUFF1_2,
     0,
     0}, // HERETIC_S_GWANDPUFF1_1
    {HERETIC_SPR_PUF2,
     32769,
     3,
     {},
     HERETIC_S_GWANDPUFF1_3,
     0,
     0}, // HERETIC_S_GWANDPUFF1_2
    {HERETIC_SPR_PUF2,
     32770,
     3,
     {},
     HERETIC_S_GWANDPUFF1_4,
     0,
     0}, // HERETIC_S_GWANDPUFF1_3
    {HERETIC_SPR_PUF2,
     32771,
     3,
     {},
     HERETIC_S_GWANDPUFF1_5,
     0,
     0}, // HERETIC_S_GWANDPUFF1_4
    {HERETIC_SPR_PUF2,
     32772,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_GWANDPUFF1_5
    {HERETIC_SPR_WPHX, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_WPHX
    {HERETIC_SPR_PHNX, 0, 1, A_WeaponReady, HERETIC_S_PHOENIXREADY, 0,
     0}, // HERETIC_S_PHOENIXREADY
    {HERETIC_SPR_PHNX, 0, 1, A_Lower, HERETIC_S_PHOENIXDOWN, 0,
     0}, // HERETIC_S_PHOENIXDOWN
    {HERETIC_SPR_PHNX, 0, 1, A_Raise, HERETIC_S_PHOENIXUP, 0,
     0}, // HERETIC_S_PHOENIXUP
    {HERETIC_SPR_PHNX,
     1,
     5,
     {},
     HERETIC_S_PHOENIXATK1_2,
     0,
     0}, // HERETIC_S_PHOENIXATK1_1
    {HERETIC_SPR_PHNX, 2, 7, A_FirePhoenixPL1, HERETIC_S_PHOENIXATK1_3, 0,
     0}, // HERETIC_S_PHOENIXATK1_2
    {HERETIC_SPR_PHNX,
     3,
     4,
     {},
     HERETIC_S_PHOENIXATK1_4,
     0,
     0}, // HERETIC_S_PHOENIXATK1_3
    {HERETIC_SPR_PHNX,
     1,
     4,
     {},
     HERETIC_S_PHOENIXATK1_5,
     0,
     0}, // HERETIC_S_PHOENIXATK1_4
    {HERETIC_SPR_PHNX, 1, 0, A_ReFire, HERETIC_S_PHOENIXREADY, 0,
     0}, // HERETIC_S_PHOENIXATK1_5
    {HERETIC_SPR_PHNX, 1, 3, A_InitPhoenixPL2, HERETIC_S_PHOENIXATK2_2, 0,
     0}, // HERETIC_S_PHOENIXATK2_1
    {HERETIC_SPR_PHNX, 32770, 1, A_FirePhoenixPL2, HERETIC_S_PHOENIXATK2_3, 0,
     0}, // HERETIC_S_PHOENIXATK2_2
    {HERETIC_SPR_PHNX, 1, 4, A_ReFire, HERETIC_S_PHOENIXATK2_4, 0,
     0}, // HERETIC_S_PHOENIXATK2_3
    {HERETIC_SPR_PHNX, 1, 4, A_ShutdownPhoenixPL2, HERETIC_S_PHOENIXREADY, 0,
     0}, // HERETIC_S_PHOENIXATK2_4
    {HERETIC_SPR_FX04, 32768, 4, A_PhoenixPuff, HERETIC_S_PHOENIXFX1_1, 0,
     0}, // HERETIC_S_PHOENIXFX1_1
    {HERETIC_SPR_FX08, 32768, 6, A_Explode, HERETIC_S_PHOENIXFXI1_2, 0,
     0}, // HERETIC_S_PHOENIXFXI1_1
    {HERETIC_SPR_FX08,
     32769,
     5,
     {},
     HERETIC_S_PHOENIXFXI1_3,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_2
    {HERETIC_SPR_FX08,
     32770,
     5,
     {},
     HERETIC_S_PHOENIXFXI1_4,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_3
    {HERETIC_SPR_FX08,
     32771,
     4,
     {},
     HERETIC_S_PHOENIXFXI1_5,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_4
    {HERETIC_SPR_FX08,
     32772,
     4,
     {},
     HERETIC_S_PHOENIXFXI1_6,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_5
    {HERETIC_SPR_FX08,
     32773,
     4,
     {},
     HERETIC_S_PHOENIXFXI1_7,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_6
    {HERETIC_SPR_FX08,
     32774,
     4,
     {},
     HERETIC_S_PHOENIXFXI1_8,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_7
    {HERETIC_SPR_FX08,
     32775,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_PHOENIXFXI1_8
    {HERETIC_SPR_FX08,
     32776,
     8,
     {},
     HERETIC_S_PHOENIXFXIX_1,
     0,
     0}, // HERETIC_S_PHOENIXFXIX_1
    {HERETIC_SPR_FX08, 32777, 8, A_RemovedPhoenixFunc, HERETIC_S_PHOENIXFXIX_2,
     0, 0}, // HERETIC_S_PHOENIXFXIX_2
    {HERETIC_SPR_FX08,
     32778,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_PHOENIXFXIX_3
    {HERETIC_SPR_FX04,
     1,
     4,
     {},
     HERETIC_S_PHOENIXPUFF2,
     0,
     0}, // HERETIC_S_PHOENIXPUFF1
    {HERETIC_SPR_FX04,
     2,
     4,
     {},
     HERETIC_S_PHOENIXPUFF3,
     0,
     0}, // HERETIC_S_PHOENIXPUFF2
    {HERETIC_SPR_FX04,
     3,
     4,
     {},
     HERETIC_S_PHOENIXPUFF4,
     0,
     0}, // HERETIC_S_PHOENIXPUFF3
    {HERETIC_SPR_FX04,
     4,
     4,
     {},
     HERETIC_S_PHOENIXPUFF5,
     0,
     0}, // HERETIC_S_PHOENIXPUFF4
    {HERETIC_SPR_FX04,
     5,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_PHOENIXPUFF5
    {HERETIC_SPR_FX09,
     32768,
     2,
     {},
     HERETIC_S_PHOENIXFX2_2,
     0,
     0}, // HERETIC_S_PHOENIXFX2_1
    {HERETIC_SPR_FX09,
     32769,
     2,
     {},
     HERETIC_S_PHOENIXFX2_3,
     0,
     0}, // HERETIC_S_PHOENIXFX2_2
    {HERETIC_SPR_FX09,
     32768,
     2,
     {},
     HERETIC_S_PHOENIXFX2_4,
     0,
     0}, // HERETIC_S_PHOENIXFX2_3
    {HERETIC_SPR_FX09,
     32769,
     2,
     {},
     HERETIC_S_PHOENIXFX2_5,
     0,
     0}, // HERETIC_S_PHOENIXFX2_4
    {HERETIC_SPR_FX09,
     32768,
     2,
     {},
     HERETIC_S_PHOENIXFX2_6,
     0,
     0}, // HERETIC_S_PHOENIXFX2_5
    {HERETIC_SPR_FX09, 32769, 2, A_FlameEnd, HERETIC_S_PHOENIXFX2_7, 0,
     0}, // HERETIC_S_PHOENIXFX2_6
    {HERETIC_SPR_FX09,
     32770,
     2,
     {},
     HERETIC_S_PHOENIXFX2_8,
     0,
     0}, // HERETIC_S_PHOENIXFX2_7
    {HERETIC_SPR_FX09,
     32771,
     2,
     {},
     HERETIC_S_PHOENIXFX2_9,
     0,
     0}, // HERETIC_S_PHOENIXFX2_8
    {HERETIC_SPR_FX09,
     32772,
     2,
     {},
     HERETIC_S_PHOENIXFX2_10,
     0,
     0}, // HERETIC_S_PHOENIXFX2_9
    {HERETIC_SPR_FX09,
     32773,
     2,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_PHOENIXFX2_10
    {HERETIC_SPR_FX09,
     32774,
     3,
     {},
     HERETIC_S_PHOENIXFXI2_2,
     0,
     0}, // HERETIC_S_PHOENIXFXI2_1
    {HERETIC_SPR_FX09, 32775, 3, A_FloatPuff, HERETIC_S_PHOENIXFXI2_3, 0,
     0}, // HERETIC_S_PHOENIXFXI2_2
    {HERETIC_SPR_FX09,
     32776,
     4,
     {},
     HERETIC_S_PHOENIXFXI2_4,
     0,
     0}, // HERETIC_S_PHOENIXFXI2_3
    {HERETIC_SPR_FX09,
     32777,
     5,
     {},
     HERETIC_S_PHOENIXFXI2_5,
     0,
     0}, // HERETIC_S_PHOENIXFXI2_4
    {HERETIC_SPR_FX09,
     32778,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_PHOENIXFXI2_5
    {HERETIC_SPR_WBOW, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_WBOW
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW2, 0,
     0}, // HERETIC_S_CRBOW1
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW3, 0,
     0}, // HERETIC_S_CRBOW2
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW4, 0,
     0}, // HERETIC_S_CRBOW3
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW5, 0,
     0}, // HERETIC_S_CRBOW4
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW6, 0,
     0}, // HERETIC_S_CRBOW5
    {HERETIC_SPR_CRBW, 0, 1, A_WeaponReady, HERETIC_S_CRBOW7, 0,
     0}, // HERETIC_S_CRBOW6
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW8, 0,
     0}, // HERETIC_S_CRBOW7
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW9, 0,
     0}, // HERETIC_S_CRBOW8
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW10, 0,
     0}, // HERETIC_S_CRBOW9
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW11, 0,
     0}, // HERETIC_S_CRBOW10
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW12, 0,
     0}, // HERETIC_S_CRBOW11
    {HERETIC_SPR_CRBW, 1, 1, A_WeaponReady, HERETIC_S_CRBOW13, 0,
     0}, // HERETIC_S_CRBOW12
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW14, 0,
     0}, // HERETIC_S_CRBOW13
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW15, 0,
     0}, // HERETIC_S_CRBOW14
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW16, 0,
     0}, // HERETIC_S_CRBOW15
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW17, 0,
     0}, // HERETIC_S_CRBOW16
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW18, 0,
     0}, // HERETIC_S_CRBOW17
    {HERETIC_SPR_CRBW, 2, 1, A_WeaponReady, HERETIC_S_CRBOW1, 0,
     0}, // HERETIC_S_CRBOW18
    {HERETIC_SPR_CRBW, 0, 1, A_Lower, HERETIC_S_CRBOWDOWN, 0,
     0}, // HERETIC_S_CRBOWDOWN
    {HERETIC_SPR_CRBW, 0, 1, A_Raise, HERETIC_S_CRBOWUP, 0,
     0}, // HERETIC_S_CRBOWUP
    {HERETIC_SPR_CRBW, 3, 6, A_FireCrossbowPL1, HERETIC_S_CRBOWATK1_2, 0,
     0}, // HERETIC_S_CRBOWATK1_1
    {HERETIC_SPR_CRBW,
     4,
     3,
     {},
     HERETIC_S_CRBOWATK1_3,
     0,
     0}, // HERETIC_S_CRBOWATK1_2
    {HERETIC_SPR_CRBW,
     5,
     3,
     {},
     HERETIC_S_CRBOWATK1_4,
     0,
     0}, // HERETIC_S_CRBOWATK1_3
    {HERETIC_SPR_CRBW,
     6,
     3,
     {},
     HERETIC_S_CRBOWATK1_5,
     0,
     0}, // HERETIC_S_CRBOWATK1_4
    {HERETIC_SPR_CRBW,
     7,
     3,
     {},
     HERETIC_S_CRBOWATK1_6,
     0,
     0}, // HERETIC_S_CRBOWATK1_5
    {HERETIC_SPR_CRBW,
     0,
     4,
     {},
     HERETIC_S_CRBOWATK1_7,
     0,
     0}, // HERETIC_S_CRBOWATK1_6
    {HERETIC_SPR_CRBW,
     1,
     4,
     {},
     HERETIC_S_CRBOWATK1_8,
     0,
     0}, // HERETIC_S_CRBOWATK1_7
    {HERETIC_SPR_CRBW, 2, 5, A_ReFire, HERETIC_S_CRBOW1, 0,
     0}, // HERETIC_S_CRBOWATK1_8
    {HERETIC_SPR_CRBW, 3, 5, A_FireCrossbowPL2, HERETIC_S_CRBOWATK2_2, 0,
     0}, // HERETIC_S_CRBOWATK2_1
    {HERETIC_SPR_CRBW,
     4,
     3,
     {},
     HERETIC_S_CRBOWATK2_3,
     0,
     0}, // HERETIC_S_CRBOWATK2_2
    {HERETIC_SPR_CRBW,
     5,
     2,
     {},
     HERETIC_S_CRBOWATK2_4,
     0,
     0}, // HERETIC_S_CRBOWATK2_3
    {HERETIC_SPR_CRBW,
     6,
     3,
     {},
     HERETIC_S_CRBOWATK2_5,
     0,
     0}, // HERETIC_S_CRBOWATK2_4
    {HERETIC_SPR_CRBW,
     7,
     2,
     {},
     HERETIC_S_CRBOWATK2_6,
     0,
     0}, // HERETIC_S_CRBOWATK2_5
    {HERETIC_SPR_CRBW,
     0,
     3,
     {},
     HERETIC_S_CRBOWATK2_7,
     0,
     0}, // HERETIC_S_CRBOWATK2_6
    {HERETIC_SPR_CRBW,
     1,
     3,
     {},
     HERETIC_S_CRBOWATK2_8,
     0,
     0}, // HERETIC_S_CRBOWATK2_7
    {HERETIC_SPR_CRBW, 2, 4, A_ReFire, HERETIC_S_CRBOW1, 0,
     0}, // HERETIC_S_CRBOWATK2_8
    {HERETIC_SPR_FX03,
     32769,
     1,
     {},
     HERETIC_S_CRBOWFX1,
     0,
     0}, // HERETIC_S_CRBOWFX1
    {HERETIC_SPR_FX03,
     32775,
     8,
     {},
     HERETIC_S_CRBOWFXI1_2,
     0,
     0}, // HERETIC_S_CRBOWFXI1_1
    {HERETIC_SPR_FX03,
     32776,
     8,
     {},
     HERETIC_S_CRBOWFXI1_3,
     0,
     0}, // HERETIC_S_CRBOWFXI1_2
    {HERETIC_SPR_FX03,
     32777,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_CRBOWFXI1_3
    {HERETIC_SPR_FX03, 32769, 1, A_BoltSpark, HERETIC_S_CRBOWFX2, 0,
     0}, // HERETIC_S_CRBOWFX2
    {HERETIC_SPR_FX03,
     32768,
     1,
     {},
     HERETIC_S_CRBOWFX3,
     0,
     0}, // HERETIC_S_CRBOWFX3
    {HERETIC_SPR_FX03,
     32770,
     8,
     {},
     HERETIC_S_CRBOWFXI3_2,
     0,
     0}, // HERETIC_S_CRBOWFXI3_1
    {HERETIC_SPR_FX03,
     32771,
     8,
     {},
     HERETIC_S_CRBOWFXI3_3,
     0,
     0}, // HERETIC_S_CRBOWFXI3_2
    {HERETIC_SPR_FX03,
     32772,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_CRBOWFXI3_3
    {HERETIC_SPR_FX03,
     32773,
     8,
     {},
     HERETIC_S_CRBOWFX4_2,
     0,
     0}, // HERETIC_S_CRBOWFX4_1
    {HERETIC_SPR_FX03,
     32774,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_CRBOWFX4_2
    {HERETIC_SPR_BLOD, 2, 8, {}, HERETIC_S_BLOOD2, 0, 0}, // HERETIC_S_BLOOD1
    {HERETIC_SPR_BLOD, 1, 8, {}, HERETIC_S_BLOOD3, 0, 0}, // HERETIC_S_BLOOD2
    {HERETIC_SPR_BLOD, 0, 8, {}, HERETIC_S_NULL, 0, 0},   // HERETIC_S_BLOOD3
    {HERETIC_SPR_BLOD,
     2,
     8,
     {},
     HERETIC_S_BLOODSPLATTER2,
     0,
     0}, // HERETIC_S_BLOODSPLATTER1
    {HERETIC_SPR_BLOD,
     1,
     8,
     {},
     HERETIC_S_BLOODSPLATTER3,
     0,
     0}, // HERETIC_S_BLOODSPLATTER2
    {HERETIC_SPR_BLOD,
     0,
     8,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLOODSPLATTER3
    {HERETIC_SPR_BLOD,
     0,
     6,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLOODSPLATTERX
    {HERETIC_SPR_PLAY, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_PLAY
    {HERETIC_SPR_PLAY,
     0,
     4,
     {},
     HERETIC_S_PLAY_RUN2,
     0,
     0}, // HERETIC_S_PLAY_RUN1
    {HERETIC_SPR_PLAY,
     1,
     4,
     {},
     HERETIC_S_PLAY_RUN3,
     0,
     0}, // HERETIC_S_PLAY_RUN2
    {HERETIC_SPR_PLAY,
     2,
     4,
     {},
     HERETIC_S_PLAY_RUN4,
     0,
     0}, // HERETIC_S_PLAY_RUN3
    {HERETIC_SPR_PLAY,
     3,
     4,
     {},
     HERETIC_S_PLAY_RUN1,
     0,
     0},                                                 // HERETIC_S_PLAY_RUN4
    {HERETIC_SPR_PLAY, 4, 12, {}, HERETIC_S_PLAY, 0, 0}, // HERETIC_S_PLAY_ATK1
    {HERETIC_SPR_PLAY,
     32773,
     6,
     {},
     HERETIC_S_PLAY_ATK1,
     0,
     0}, // HERETIC_S_PLAY_ATK2
    {HERETIC_SPR_PLAY,
     6,
     4,
     {},
     HERETIC_S_PLAY_PAIN2,
     0,
     0}, // HERETIC_S_PLAY_PAIN
    {HERETIC_SPR_PLAY, 6, 4, A_Pain, HERETIC_S_PLAY, 0,
     0}, // HERETIC_S_PLAY_PAIN2
    {HERETIC_SPR_PLAY,
     7,
     6,
     {},
     HERETIC_S_PLAY_DIE2,
     0,
     0}, // HERETIC_S_PLAY_DIE1
    {HERETIC_SPR_PLAY, 8, 6, A_Scream, HERETIC_S_PLAY_DIE3, 0,
     0}, // HERETIC_S_PLAY_DIE2
    {HERETIC_SPR_PLAY,
     9,
     6,
     {},
     HERETIC_S_PLAY_DIE4,
     0,
     0}, // HERETIC_S_PLAY_DIE3
    {HERETIC_SPR_PLAY,
     10,
     6,
     {},
     HERETIC_S_PLAY_DIE5,
     0,
     0}, // HERETIC_S_PLAY_DIE4
    {HERETIC_SPR_PLAY, 11, 6, A_NoBlocking, HERETIC_S_PLAY_DIE6, 0,
     0}, // HERETIC_S_PLAY_DIE5
    {HERETIC_SPR_PLAY,
     12,
     6,
     {},
     HERETIC_S_PLAY_DIE7,
     0,
     0}, // HERETIC_S_PLAY_DIE6
    {HERETIC_SPR_PLAY,
     13,
     6,
     {},
     HERETIC_S_PLAY_DIE8,
     0,
     0}, // HERETIC_S_PLAY_DIE7
    {HERETIC_SPR_PLAY,
     14,
     6,
     {},
     HERETIC_S_PLAY_DIE9,
     0,
     0}, // HERETIC_S_PLAY_DIE8
    {HERETIC_SPR_PLAY, 15, -1, A_AddPlayerCorpse, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_PLAY_DIE9
    {HERETIC_SPR_PLAY, 16, 5, A_Scream, HERETIC_S_PLAY_XDIE2, 0,
     0}, // HERETIC_S_PLAY_XDIE1
    {HERETIC_SPR_PLAY, 17, 5, A_SkullPop, HERETIC_S_PLAY_XDIE3, 0,
     0}, // HERETIC_S_PLAY_XDIE2
    {HERETIC_SPR_PLAY, 18, 5, A_NoBlocking, HERETIC_S_PLAY_XDIE4, 0,
     0}, // HERETIC_S_PLAY_XDIE3
    {HERETIC_SPR_PLAY,
     19,
     5,
     {},
     HERETIC_S_PLAY_XDIE5,
     0,
     0}, // HERETIC_S_PLAY_XDIE4
    {HERETIC_SPR_PLAY,
     20,
     5,
     {},
     HERETIC_S_PLAY_XDIE6,
     0,
     0}, // HERETIC_S_PLAY_XDIE5
    {HERETIC_SPR_PLAY,
     21,
     5,
     {},
     HERETIC_S_PLAY_XDIE7,
     0,
     0}, // HERETIC_S_PLAY_XDIE6
    {HERETIC_SPR_PLAY,
     22,
     5,
     {},
     HERETIC_S_PLAY_XDIE8,
     0,
     0}, // HERETIC_S_PLAY_XDIE7
    {HERETIC_SPR_PLAY,
     23,
     5,
     {},
     HERETIC_S_PLAY_XDIE9,
     0,
     0}, // HERETIC_S_PLAY_XDIE8
    {HERETIC_SPR_PLAY, 24, -1, A_AddPlayerCorpse, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_PLAY_XDIE9
    {HERETIC_SPR_FDTH, 32768, 5, A_FlameSnd, HERETIC_S_PLAY_FDTH2, 0,
     0}, // HERETIC_S_PLAY_FDTH1
    {HERETIC_SPR_FDTH,
     32769,
     4,
     {},
     HERETIC_S_PLAY_FDTH3,
     0,
     0}, // HERETIC_S_PLAY_FDTH2
    {HERETIC_SPR_FDTH,
     32770,
     5,
     {},
     HERETIC_S_PLAY_FDTH4,
     0,
     0}, // HERETIC_S_PLAY_FDTH3
    {HERETIC_SPR_FDTH, 32771, 4, A_Scream, HERETIC_S_PLAY_FDTH5, 0,
     0}, // HERETIC_S_PLAY_FDTH4
    {HERETIC_SPR_FDTH,
     32772,
     5,
     {},
     HERETIC_S_PLAY_FDTH6,
     0,
     0}, // HERETIC_S_PLAY_FDTH5
    {HERETIC_SPR_FDTH,
     32773,
     4,
     {},
     HERETIC_S_PLAY_FDTH7,
     0,
     0}, // HERETIC_S_PLAY_FDTH6
    {HERETIC_SPR_FDTH, 32774, 5, A_FlameSnd, HERETIC_S_PLAY_FDTH8, 0,
     0}, // HERETIC_S_PLAY_FDTH7
    {HERETIC_SPR_FDTH,
     32775,
     4,
     {},
     HERETIC_S_PLAY_FDTH9,
     0,
     0}, // HERETIC_S_PLAY_FDTH8
    {HERETIC_SPR_FDTH,
     32776,
     5,
     {},
     HERETIC_S_PLAY_FDTH10,
     0,
     0}, // HERETIC_S_PLAY_FDTH9
    {HERETIC_SPR_FDTH,
     32777,
     4,
     {},
     HERETIC_S_PLAY_FDTH11,
     0,
     0}, // HERETIC_S_PLAY_FDTH10
    {HERETIC_SPR_FDTH,
     32778,
     5,
     {},
     HERETIC_S_PLAY_FDTH12,
     0,
     0}, // HERETIC_S_PLAY_FDTH11
    {HERETIC_SPR_FDTH,
     32779,
     4,
     {},
     HERETIC_S_PLAY_FDTH13,
     0,
     0}, // HERETIC_S_PLAY_FDTH12
    {HERETIC_SPR_FDTH,
     32780,
     5,
     {},
     HERETIC_S_PLAY_FDTH14,
     0,
     0}, // HERETIC_S_PLAY_FDTH13
    {HERETIC_SPR_FDTH,
     32781,
     4,
     {},
     HERETIC_S_PLAY_FDTH15,
     0,
     0}, // HERETIC_S_PLAY_FDTH14
    {HERETIC_SPR_FDTH, 32782, 5, A_NoBlocking, HERETIC_S_PLAY_FDTH16, 0,
     0}, // HERETIC_S_PLAY_FDTH15
    {HERETIC_SPR_FDTH,
     32783,
     4,
     {},
     HERETIC_S_PLAY_FDTH17,
     0,
     0}, // HERETIC_S_PLAY_FDTH16
    {HERETIC_SPR_FDTH,
     32784,
     5,
     {},
     HERETIC_S_PLAY_FDTH18,
     0,
     0}, // HERETIC_S_PLAY_FDTH17
    {HERETIC_SPR_FDTH,
     32785,
     4,
     {},
     HERETIC_S_PLAY_FDTH19,
     0,
     0}, // HERETIC_S_PLAY_FDTH18
    {HERETIC_SPR_ACLO, 4, 35, A_CheckBurnGone, HERETIC_S_PLAY_FDTH19, 0,
     0},                                                // HERETIC_S_PLAY_FDTH19
    {HERETIC_SPR_ACLO, 4, 8, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_PLAY_FDTH20
    {HERETIC_SPR_BSKL, 0, 5, A_CheckSkullFloor, HERETIC_S_BLOODYSKULL2, 0,
     0}, // HERETIC_S_BLOODYSKULL1
    {HERETIC_SPR_BSKL, 1, 5, A_CheckSkullFloor, HERETIC_S_BLOODYSKULL3, 0,
     0}, // HERETIC_S_BLOODYSKULL2
    {HERETIC_SPR_BSKL, 2, 5, A_CheckSkullFloor, HERETIC_S_BLOODYSKULL4, 0,
     0}, // HERETIC_S_BLOODYSKULL3
    {HERETIC_SPR_BSKL, 3, 5, A_CheckSkullFloor, HERETIC_S_BLOODYSKULL5, 0,
     0}, // HERETIC_S_BLOODYSKULL4
    {HERETIC_SPR_BSKL, 4, 5, A_CheckSkullFloor, HERETIC_S_BLOODYSKULL1, 0,
     0}, // HERETIC_S_BLOODYSKULL5
    {HERETIC_SPR_BSKL, 5, 16, A_CheckSkullDone, HERETIC_S_BLOODYSKULLX1, 0,
     0}, // HERETIC_S_BLOODYSKULLX1
    {HERETIC_SPR_BSKL,
     5,
     1050,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BLOODYSKULLX2
    {HERETIC_SPR_CHKN, 0, -1, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_CHICPLAY
    {HERETIC_SPR_CHKN,
     0,
     3,
     {},
     HERETIC_S_CHICPLAY_RUN2,
     0,
     0}, // HERETIC_S_CHICPLAY_RUN1
    {HERETIC_SPR_CHKN,
     1,
     3,
     {},
     HERETIC_S_CHICPLAY_RUN3,
     0,
     0}, // HERETIC_S_CHICPLAY_RUN2
    {HERETIC_SPR_CHKN,
     0,
     3,
     {},
     HERETIC_S_CHICPLAY_RUN4,
     0,
     0}, // HERETIC_S_CHICPLAY_RUN3
    {HERETIC_SPR_CHKN,
     1,
     3,
     {},
     HERETIC_S_CHICPLAY_RUN1,
     0,
     0}, // HERETIC_S_CHICPLAY_RUN4
    {HERETIC_SPR_CHKN,
     2,
     12,
     {},
     HERETIC_S_CHICPLAY,
     0,
     0}, // HERETIC_S_CHICPLAY_ATK1
    {HERETIC_SPR_CHKN, 3, 4, A_Feathers, HERETIC_S_CHICPLAY_PAIN2, 0,
     0}, // HERETIC_S_CHICPLAY_PAIN
    {HERETIC_SPR_CHKN, 2, 4, A_Pain, HERETIC_S_CHICPLAY, 0,
     0}, // HERETIC_S_CHICPLAY_PAIN2
    {HERETIC_SPR_CHKN, 0, 10, A_ChicLook, HERETIC_S_CHICKEN_LOOK2, 0,
     0}, // HERETIC_S_CHICKEN_LOOK1
    {HERETIC_SPR_CHKN, 1, 10, A_ChicLook, HERETIC_S_CHICKEN_LOOK1, 0,
     0}, // HERETIC_S_CHICKEN_LOOK2
    {HERETIC_SPR_CHKN, 0, 3, A_ChicChase, HERETIC_S_CHICKEN_WALK2, 0,
     0}, // HERETIC_S_CHICKEN_WALK1
    {HERETIC_SPR_CHKN, 1, 3, A_ChicChase, HERETIC_S_CHICKEN_WALK1, 0,
     0}, // HERETIC_S_CHICKEN_WALK2
    {HERETIC_SPR_CHKN, 3, 5, A_Feathers, HERETIC_S_CHICKEN_PAIN2, 0,
     0}, // HERETIC_S_CHICKEN_PAIN1
    {HERETIC_SPR_CHKN, 2, 5, A_ChicPain, HERETIC_S_CHICKEN_WALK1, 0,
     0}, // HERETIC_S_CHICKEN_PAIN2
    {HERETIC_SPR_CHKN, 0, 8, A_FaceTarget, HERETIC_S_CHICKEN_ATK2, 0,
     0}, // HERETIC_S_CHICKEN_ATK1
    {HERETIC_SPR_CHKN, 2, 10, A_ChicAttack, HERETIC_S_CHICKEN_WALK1, 0,
     0}, // HERETIC_S_CHICKEN_ATK2
    {HERETIC_SPR_CHKN, 4, 6, A_Scream, HERETIC_S_CHICKEN_DIE2, 0,
     0}, // HERETIC_S_CHICKEN_DIE1
    {HERETIC_SPR_CHKN, 5, 6, A_Feathers, HERETIC_S_CHICKEN_DIE3, 0,
     0}, // HERETIC_S_CHICKEN_DIE2
    {HERETIC_SPR_CHKN,
     6,
     6,
     {},
     HERETIC_S_CHICKEN_DIE4,
     0,
     0}, // HERETIC_S_CHICKEN_DIE3
    {HERETIC_SPR_CHKN, 7, 6, A_NoBlocking, HERETIC_S_CHICKEN_DIE5, 0,
     0}, // HERETIC_S_CHICKEN_DIE4
    {HERETIC_SPR_CHKN,
     8,
     6,
     {},
     HERETIC_S_CHICKEN_DIE6,
     0,
     0}, // HERETIC_S_CHICKEN_DIE5
    {HERETIC_SPR_CHKN,
     9,
     6,
     {},
     HERETIC_S_CHICKEN_DIE7,
     0,
     0}, // HERETIC_S_CHICKEN_DIE6
    {HERETIC_SPR_CHKN,
     10,
     6,
     {},
     HERETIC_S_CHICKEN_DIE8,
     0,
     0}, // HERETIC_S_CHICKEN_DIE7
    {HERETIC_SPR_CHKN,
     11,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_CHICKEN_DIE8
    {HERETIC_SPR_CHKN,
     12,
     3,
     {},
     HERETIC_S_FEATHER2,
     0,
     0}, // HERETIC_S_FEATHER1
    {HERETIC_SPR_CHKN,
     13,
     3,
     {},
     HERETIC_S_FEATHER3,
     0,
     0}, // HERETIC_S_FEATHER2
    {HERETIC_SPR_CHKN,
     14,
     3,
     {},
     HERETIC_S_FEATHER4,
     0,
     0}, // HERETIC_S_FEATHER3
    {HERETIC_SPR_CHKN,
     15,
     3,
     {},
     HERETIC_S_FEATHER5,
     0,
     0}, // HERETIC_S_FEATHER4
    {HERETIC_SPR_CHKN,
     16,
     3,
     {},
     HERETIC_S_FEATHER6,
     0,
     0}, // HERETIC_S_FEATHER5
    {HERETIC_SPR_CHKN,
     15,
     3,
     {},
     HERETIC_S_FEATHER7,
     0,
     0}, // HERETIC_S_FEATHER6
    {HERETIC_SPR_CHKN,
     14,
     3,
     {},
     HERETIC_S_FEATHER8,
     0,
     0}, // HERETIC_S_FEATHER7
    {HERETIC_SPR_CHKN,
     13,
     3,
     {},
     HERETIC_S_FEATHER1,
     0,
     0},                                                 // HERETIC_S_FEATHER8
    {HERETIC_SPR_CHKN, 13, 6, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_FEATHERX
    {HERETIC_SPR_MUMM, 0, 10, A_Look, HERETIC_S_MUMMY_LOOK2, 0,
     0}, // HERETIC_S_MUMMY_LOOK1
    {HERETIC_SPR_MUMM, 1, 10, A_Look, HERETIC_S_MUMMY_LOOK1, 0,
     0}, // HERETIC_S_MUMMY_LOOK2
    {HERETIC_SPR_MUMM, 0, 4, A_Chase, HERETIC_S_MUMMY_WALK2, 0,
     0}, // HERETIC_S_MUMMY_WALK1
    {HERETIC_SPR_MUMM, 1, 4, A_Chase, HERETIC_S_MUMMY_WALK3, 0,
     0}, // HERETIC_S_MUMMY_WALK2
    {HERETIC_SPR_MUMM, 2, 4, A_Chase, HERETIC_S_MUMMY_WALK4, 0,
     0}, // HERETIC_S_MUMMY_WALK3
    {HERETIC_SPR_MUMM, 3, 4, A_Chase, HERETIC_S_MUMMY_WALK1, 0,
     0}, // HERETIC_S_MUMMY_WALK4
    {HERETIC_SPR_MUMM, 4, 6, A_FaceTarget, HERETIC_S_MUMMY_ATK2, 0,
     0}, // HERETIC_S_MUMMY_ATK1
    {HERETIC_SPR_MUMM, 5, 6, A_MummyAttack, HERETIC_S_MUMMY_ATK3, 0,
     0}, // HERETIC_S_MUMMY_ATK2
    {HERETIC_SPR_MUMM, 6, 6, A_FaceTarget, HERETIC_S_MUMMY_WALK1, 0,
     0}, // HERETIC_S_MUMMY_ATK3
    {HERETIC_SPR_MUMM, 23, 5, A_FaceTarget, HERETIC_S_MUMMYL_ATK2, 0,
     0}, // HERETIC_S_MUMMYL_ATK1
    {HERETIC_SPR_MUMM, 32792, 5, A_FaceTarget, HERETIC_S_MUMMYL_ATK3, 0,
     0}, // HERETIC_S_MUMMYL_ATK2
    {HERETIC_SPR_MUMM, 23, 5, A_FaceTarget, HERETIC_S_MUMMYL_ATK4, 0,
     0}, // HERETIC_S_MUMMYL_ATK3
    {HERETIC_SPR_MUMM, 32792, 5, A_FaceTarget, HERETIC_S_MUMMYL_ATK5, 0,
     0}, // HERETIC_S_MUMMYL_ATK4
    {HERETIC_SPR_MUMM, 23, 5, A_FaceTarget, HERETIC_S_MUMMYL_ATK6, 0,
     0}, // HERETIC_S_MUMMYL_ATK5
    {HERETIC_SPR_MUMM, 32792, 15, A_MummyAttack2, HERETIC_S_MUMMY_WALK1, 0,
     0}, // HERETIC_S_MUMMYL_ATK6
    {HERETIC_SPR_MUMM,
     7,
     4,
     {},
     HERETIC_S_MUMMY_PAIN2,
     0,
     0}, // HERETIC_S_MUMMY_PAIN1
    {HERETIC_SPR_MUMM, 7, 4, A_Pain, HERETIC_S_MUMMY_WALK1, 0,
     0}, // HERETIC_S_MUMMY_PAIN2
    {HERETIC_SPR_MUMM,
     8,
     5,
     {},
     HERETIC_S_MUMMY_DIE2,
     0,
     0}, // HERETIC_S_MUMMY_DIE1
    {HERETIC_SPR_MUMM, 9, 5, A_Scream, HERETIC_S_MUMMY_DIE3, 0,
     0}, // HERETIC_S_MUMMY_DIE2
    {HERETIC_SPR_MUMM, 10, 5, A_MummySoul, HERETIC_S_MUMMY_DIE4, 0,
     0}, // HERETIC_S_MUMMY_DIE3
    {HERETIC_SPR_MUMM,
     11,
     5,
     {},
     HERETIC_S_MUMMY_DIE5,
     0,
     0}, // HERETIC_S_MUMMY_DIE4
    {HERETIC_SPR_MUMM, 12, 5, A_NoBlocking, HERETIC_S_MUMMY_DIE6, 0,
     0}, // HERETIC_S_MUMMY_DIE5
    {HERETIC_SPR_MUMM,
     13,
     5,
     {},
     HERETIC_S_MUMMY_DIE7,
     0,
     0}, // HERETIC_S_MUMMY_DIE6
    {HERETIC_SPR_MUMM,
     14,
     5,
     {},
     HERETIC_S_MUMMY_DIE8,
     0,
     0}, // HERETIC_S_MUMMY_DIE7
    {HERETIC_SPR_MUMM,
     15,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MUMMY_DIE8
    {HERETIC_SPR_MUMM,
     16,
     5,
     {},
     HERETIC_S_MUMMY_SOUL2,
     0,
     0}, // HERETIC_S_MUMMY_SOUL1
    {HERETIC_SPR_MUMM,
     17,
     5,
     {},
     HERETIC_S_MUMMY_SOUL3,
     0,
     0}, // HERETIC_S_MUMMY_SOUL2
    {HERETIC_SPR_MUMM,
     18,
     5,
     {},
     HERETIC_S_MUMMY_SOUL4,
     0,
     0}, // HERETIC_S_MUMMY_SOUL3
    {HERETIC_SPR_MUMM,
     19,
     9,
     {},
     HERETIC_S_MUMMY_SOUL5,
     0,
     0}, // HERETIC_S_MUMMY_SOUL4
    {HERETIC_SPR_MUMM,
     20,
     5,
     {},
     HERETIC_S_MUMMY_SOUL6,
     0,
     0}, // HERETIC_S_MUMMY_SOUL5
    {HERETIC_SPR_MUMM,
     21,
     5,
     {},
     HERETIC_S_MUMMY_SOUL7,
     0,
     0}, // HERETIC_S_MUMMY_SOUL6
    {HERETIC_SPR_MUMM,
     22,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MUMMY_SOUL7
    {HERETIC_SPR_FX15, 32768, 5, A_ContMobjSound, HERETIC_S_MUMMYFX1_2, 0,
     0}, // HERETIC_S_MUMMYFX1_1
    {HERETIC_SPR_FX15, 32769, 5, A_MummyFX1Seek, HERETIC_S_MUMMYFX1_3, 0,
     0}, // HERETIC_S_MUMMYFX1_2
    {HERETIC_SPR_FX15,
     32770,
     5,
     {},
     HERETIC_S_MUMMYFX1_4,
     0,
     0}, // HERETIC_S_MUMMYFX1_3
    {HERETIC_SPR_FX15, 32769, 5, A_MummyFX1Seek, HERETIC_S_MUMMYFX1_1, 0,
     0}, // HERETIC_S_MUMMYFX1_4
    {HERETIC_SPR_FX15,
     32771,
     5,
     {},
     HERETIC_S_MUMMYFXI1_2,
     0,
     0}, // HERETIC_S_MUMMYFXI1_1
    {HERETIC_SPR_FX15,
     32772,
     5,
     {},
     HERETIC_S_MUMMYFXI1_3,
     0,
     0}, // HERETIC_S_MUMMYFXI1_2
    {HERETIC_SPR_FX15,
     32773,
     5,
     {},
     HERETIC_S_MUMMYFXI1_4,
     0,
     0}, // HERETIC_S_MUMMYFXI1_3
    {HERETIC_SPR_FX15,
     32774,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MUMMYFXI1_4
    {HERETIC_SPR_BEAS, 0, 10, A_Look, HERETIC_S_BEAST_LOOK2, 0,
     0}, // HERETIC_S_BEAST_LOOK1
    {HERETIC_SPR_BEAS, 1, 10, A_Look, HERETIC_S_BEAST_LOOK1, 0,
     0}, // HERETIC_S_BEAST_LOOK2
    {HERETIC_SPR_BEAS, 0, 3, A_Chase, HERETIC_S_BEAST_WALK2, 0,
     0}, // HERETIC_S_BEAST_WALK1
    {HERETIC_SPR_BEAS, 1, 3, A_Chase, HERETIC_S_BEAST_WALK3, 0,
     0}, // HERETIC_S_BEAST_WALK2
    {HERETIC_SPR_BEAS, 2, 3, A_Chase, HERETIC_S_BEAST_WALK4, 0,
     0}, // HERETIC_S_BEAST_WALK3
    {HERETIC_SPR_BEAS, 3, 3, A_Chase, HERETIC_S_BEAST_WALK5, 0,
     0}, // HERETIC_S_BEAST_WALK4
    {HERETIC_SPR_BEAS, 4, 3, A_Chase, HERETIC_S_BEAST_WALK6, 0,
     0}, // HERETIC_S_BEAST_WALK5
    {HERETIC_SPR_BEAS, 5, 3, A_Chase, HERETIC_S_BEAST_WALK1, 0,
     0}, // HERETIC_S_BEAST_WALK6
    {HERETIC_SPR_BEAS, 7, 10, A_FaceTarget, HERETIC_S_BEAST_ATK2, 0,
     0}, // HERETIC_S_BEAST_ATK1
    {HERETIC_SPR_BEAS, 8, 10, A_BeastAttack, HERETIC_S_BEAST_WALK1, 0,
     0}, // HERETIC_S_BEAST_ATK2
    {HERETIC_SPR_BEAS,
     6,
     3,
     {},
     HERETIC_S_BEAST_PAIN2,
     0,
     0}, // HERETIC_S_BEAST_PAIN1
    {HERETIC_SPR_BEAS, 6, 3, A_Pain, HERETIC_S_BEAST_WALK1, 0,
     0}, // HERETIC_S_BEAST_PAIN2
    {HERETIC_SPR_BEAS,
     17,
     6,
     {},
     HERETIC_S_BEAST_DIE2,
     0,
     0}, // HERETIC_S_BEAST_DIE1
    {HERETIC_SPR_BEAS, 18, 6, A_Scream, HERETIC_S_BEAST_DIE3, 0,
     0}, // HERETIC_S_BEAST_DIE2
    {HERETIC_SPR_BEAS,
     19,
     6,
     {},
     HERETIC_S_BEAST_DIE4,
     0,
     0}, // HERETIC_S_BEAST_DIE3
    {HERETIC_SPR_BEAS,
     20,
     6,
     {},
     HERETIC_S_BEAST_DIE5,
     0,
     0}, // HERETIC_S_BEAST_DIE4
    {HERETIC_SPR_BEAS,
     21,
     6,
     {},
     HERETIC_S_BEAST_DIE6,
     0,
     0}, // HERETIC_S_BEAST_DIE5
    {HERETIC_SPR_BEAS, 22, 6, A_NoBlocking, HERETIC_S_BEAST_DIE7, 0,
     0}, // HERETIC_S_BEAST_DIE6
    {HERETIC_SPR_BEAS,
     23,
     6,
     {},
     HERETIC_S_BEAST_DIE8,
     0,
     0}, // HERETIC_S_BEAST_DIE7
    {HERETIC_SPR_BEAS,
     24,
     6,
     {},
     HERETIC_S_BEAST_DIE9,
     0,
     0}, // HERETIC_S_BEAST_DIE8
    {HERETIC_SPR_BEAS,
     25,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BEAST_DIE9
    {HERETIC_SPR_BEAS,
     9,
     5,
     {},
     HERETIC_S_BEAST_XDIE2,
     0,
     0}, // HERETIC_S_BEAST_XDIE1
    {HERETIC_SPR_BEAS, 10, 6, A_Scream, HERETIC_S_BEAST_XDIE3, 0,
     0}, // HERETIC_S_BEAST_XDIE2
    {HERETIC_SPR_BEAS,
     11,
     5,
     {},
     HERETIC_S_BEAST_XDIE4,
     0,
     0}, // HERETIC_S_BEAST_XDIE3
    {HERETIC_SPR_BEAS,
     12,
     6,
     {},
     HERETIC_S_BEAST_XDIE5,
     0,
     0}, // HERETIC_S_BEAST_XDIE4
    {HERETIC_SPR_BEAS,
     13,
     5,
     {},
     HERETIC_S_BEAST_XDIE6,
     0,
     0}, // HERETIC_S_BEAST_XDIE5
    {HERETIC_SPR_BEAS, 14, 6, A_NoBlocking, HERETIC_S_BEAST_XDIE7, 0,
     0}, // HERETIC_S_BEAST_XDIE6
    {HERETIC_SPR_BEAS,
     15,
     5,
     {},
     HERETIC_S_BEAST_XDIE8,
     0,
     0}, // HERETIC_S_BEAST_XDIE7
    {HERETIC_SPR_BEAS,
     16,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BEAST_XDIE8
    {HERETIC_SPR_FRB1, 0, 2, A_BeastPuff, HERETIC_S_BEASTBALL2, 0,
     0}, // HERETIC_S_BEASTBALL1
    {HERETIC_SPR_FRB1, 0, 2, A_BeastPuff, HERETIC_S_BEASTBALL3, 0,
     0}, // HERETIC_S_BEASTBALL2
    {HERETIC_SPR_FRB1, 1, 2, A_BeastPuff, HERETIC_S_BEASTBALL4, 0,
     0}, // HERETIC_S_BEASTBALL3
    {HERETIC_SPR_FRB1, 1, 2, A_BeastPuff, HERETIC_S_BEASTBALL5, 0,
     0}, // HERETIC_S_BEASTBALL4
    {HERETIC_SPR_FRB1, 2, 2, A_BeastPuff, HERETIC_S_BEASTBALL6, 0,
     0}, // HERETIC_S_BEASTBALL5
    {HERETIC_SPR_FRB1, 2, 2, A_BeastPuff, HERETIC_S_BEASTBALL1, 0,
     0}, // HERETIC_S_BEASTBALL6
    {HERETIC_SPR_FRB1,
     3,
     4,
     {},
     HERETIC_S_BEASTBALLX2,
     0,
     0}, // HERETIC_S_BEASTBALLX1
    {HERETIC_SPR_FRB1,
     4,
     4,
     {},
     HERETIC_S_BEASTBALLX3,
     0,
     0}, // HERETIC_S_BEASTBALLX2
    {HERETIC_SPR_FRB1,
     5,
     4,
     {},
     HERETIC_S_BEASTBALLX4,
     0,
     0}, // HERETIC_S_BEASTBALLX3
    {HERETIC_SPR_FRB1,
     6,
     4,
     {},
     HERETIC_S_BEASTBALLX5,
     0,
     0},                                                // HERETIC_S_BEASTBALLX4
    {HERETIC_SPR_FRB1, 7, 4, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_BEASTBALLX5
    {HERETIC_SPR_FRB1,
     0,
     4,
     {},
     HERETIC_S_BURNBALL2,
     0,
     0}, // HERETIC_S_BURNBALL1
    {HERETIC_SPR_FRB1,
     1,
     4,
     {},
     HERETIC_S_BURNBALL3,
     0,
     0}, // HERETIC_S_BURNBALL2
    {HERETIC_SPR_FRB1,
     2,
     4,
     {},
     HERETIC_S_BURNBALL4,
     0,
     0}, // HERETIC_S_BURNBALL3
    {HERETIC_SPR_FRB1,
     3,
     4,
     {},
     HERETIC_S_BURNBALL5,
     0,
     0}, // HERETIC_S_BURNBALL4
    {HERETIC_SPR_FRB1,
     4,
     4,
     {},
     HERETIC_S_BURNBALL6,
     0,
     0}, // HERETIC_S_BURNBALL5
    {HERETIC_SPR_FRB1,
     5,
     4,
     {},
     HERETIC_S_BURNBALL7,
     0,
     0}, // HERETIC_S_BURNBALL6
    {HERETIC_SPR_FRB1,
     6,
     4,
     {},
     HERETIC_S_BURNBALL8,
     0,
     0},                                                // HERETIC_S_BURNBALL7
    {HERETIC_SPR_FRB1, 7, 4, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_BURNBALL8
    {HERETIC_SPR_FRB1,
     32768,
     4,
     {},
     HERETIC_S_BURNBALLFB2,
     0,
     0}, // HERETIC_S_BURNBALLFB1
    {HERETIC_SPR_FRB1,
     32769,
     4,
     {},
     HERETIC_S_BURNBALLFB3,
     0,
     0}, // HERETIC_S_BURNBALLFB2
    {HERETIC_SPR_FRB1,
     32770,
     4,
     {},
     HERETIC_S_BURNBALLFB4,
     0,
     0}, // HERETIC_S_BURNBALLFB3
    {HERETIC_SPR_FRB1,
     32771,
     4,
     {},
     HERETIC_S_BURNBALLFB5,
     0,
     0}, // HERETIC_S_BURNBALLFB4
    {HERETIC_SPR_FRB1,
     32772,
     4,
     {},
     HERETIC_S_BURNBALLFB6,
     0,
     0}, // HERETIC_S_BURNBALLFB5
    {HERETIC_SPR_FRB1,
     32773,
     4,
     {},
     HERETIC_S_BURNBALLFB7,
     0,
     0}, // HERETIC_S_BURNBALLFB6
    {HERETIC_SPR_FRB1,
     32774,
     4,
     {},
     HERETIC_S_BURNBALLFB8,
     0,
     0}, // HERETIC_S_BURNBALLFB7
    {HERETIC_SPR_FRB1,
     32775,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_BURNBALLFB8
    {HERETIC_SPR_FRB1, 3, 4, {}, HERETIC_S_PUFFY2, 0, 0}, // HERETIC_S_PUFFY1
    {HERETIC_SPR_FRB1, 4, 4, {}, HERETIC_S_PUFFY3, 0, 0}, // HERETIC_S_PUFFY2
    {HERETIC_SPR_FRB1, 5, 4, {}, HERETIC_S_PUFFY4, 0, 0}, // HERETIC_S_PUFFY3
    {HERETIC_SPR_FRB1, 6, 4, {}, HERETIC_S_PUFFY5, 0, 0}, // HERETIC_S_PUFFY4
    {HERETIC_SPR_FRB1, 7, 4, {}, HERETIC_S_NULL, 0, 0},   // HERETIC_S_PUFFY5
    {HERETIC_SPR_SNKE, 0, 10, A_Look, HERETIC_S_SNAKE_LOOK2, 0,
     0}, // HERETIC_S_SNAKE_LOOK1
    {HERETIC_SPR_SNKE, 1, 10, A_Look, HERETIC_S_SNAKE_LOOK1, 0,
     0}, // HERETIC_S_SNAKE_LOOK2
    {HERETIC_SPR_SNKE, 0, 4, A_Chase, HERETIC_S_SNAKE_WALK2, 0,
     0}, // HERETIC_S_SNAKE_WALK1
    {HERETIC_SPR_SNKE, 1, 4, A_Chase, HERETIC_S_SNAKE_WALK3, 0,
     0}, // HERETIC_S_SNAKE_WALK2
    {HERETIC_SPR_SNKE, 2, 4, A_Chase, HERETIC_S_SNAKE_WALK4, 0,
     0}, // HERETIC_S_SNAKE_WALK3
    {HERETIC_SPR_SNKE, 3, 4, A_Chase, HERETIC_S_SNAKE_WALK1, 0,
     0}, // HERETIC_S_SNAKE_WALK4
    {HERETIC_SPR_SNKE, 5, 5, A_FaceTarget, HERETIC_S_SNAKE_ATK2, 0,
     0}, // HERETIC_S_SNAKE_ATK1
    {HERETIC_SPR_SNKE, 5, 5, A_FaceTarget, HERETIC_S_SNAKE_ATK3, 0,
     0}, // HERETIC_S_SNAKE_ATK2
    {HERETIC_SPR_SNKE, 5, 4, A_SnakeAttack, HERETIC_S_SNAKE_ATK4, 0,
     0}, // HERETIC_S_SNAKE_ATK3
    {HERETIC_SPR_SNKE, 5, 4, A_SnakeAttack, HERETIC_S_SNAKE_ATK5, 0,
     0}, // HERETIC_S_SNAKE_ATK4
    {HERETIC_SPR_SNKE, 5, 4, A_SnakeAttack, HERETIC_S_SNAKE_ATK6, 0,
     0}, // HERETIC_S_SNAKE_ATK5
    {HERETIC_SPR_SNKE, 5, 5, A_FaceTarget, HERETIC_S_SNAKE_ATK7, 0,
     0}, // HERETIC_S_SNAKE_ATK6
    {HERETIC_SPR_SNKE, 5, 5, A_FaceTarget, HERETIC_S_SNAKE_ATK8, 0,
     0}, // HERETIC_S_SNAKE_ATK7
    {HERETIC_SPR_SNKE, 5, 5, A_FaceTarget, HERETIC_S_SNAKE_ATK9, 0,
     0}, // HERETIC_S_SNAKE_ATK8
    {HERETIC_SPR_SNKE, 5, 4, A_SnakeAttack2, HERETIC_S_SNAKE_WALK1, 0,
     0}, // HERETIC_S_SNAKE_ATK9
    {HERETIC_SPR_SNKE,
     4,
     3,
     {},
     HERETIC_S_SNAKE_PAIN2,
     0,
     0}, // HERETIC_S_SNAKE_PAIN1
    {HERETIC_SPR_SNKE, 4, 3, A_Pain, HERETIC_S_SNAKE_WALK1, 0,
     0}, // HERETIC_S_SNAKE_PAIN2
    {HERETIC_SPR_SNKE,
     6,
     5,
     {},
     HERETIC_S_SNAKE_DIE2,
     0,
     0}, // HERETIC_S_SNAKE_DIE1
    {HERETIC_SPR_SNKE, 7, 5, A_Scream, HERETIC_S_SNAKE_DIE3, 0,
     0}, // HERETIC_S_SNAKE_DIE2
    {HERETIC_SPR_SNKE,
     8,
     5,
     {},
     HERETIC_S_SNAKE_DIE4,
     0,
     0}, // HERETIC_S_SNAKE_DIE3
    {HERETIC_SPR_SNKE,
     9,
     5,
     {},
     HERETIC_S_SNAKE_DIE5,
     0,
     0}, // HERETIC_S_SNAKE_DIE4
    {HERETIC_SPR_SNKE,
     10,
     5,
     {},
     HERETIC_S_SNAKE_DIE6,
     0,
     0}, // HERETIC_S_SNAKE_DIE5
    {HERETIC_SPR_SNKE,
     11,
     5,
     {},
     HERETIC_S_SNAKE_DIE7,
     0,
     0}, // HERETIC_S_SNAKE_DIE6
    {HERETIC_SPR_SNKE, 12, 5, A_NoBlocking, HERETIC_S_SNAKE_DIE8, 0,
     0}, // HERETIC_S_SNAKE_DIE7
    {HERETIC_SPR_SNKE,
     13,
     5,
     {},
     HERETIC_S_SNAKE_DIE9,
     0,
     0}, // HERETIC_S_SNAKE_DIE8
    {HERETIC_SPR_SNKE,
     14,
     5,
     {},
     HERETIC_S_SNAKE_DIE10,
     0,
     0}, // HERETIC_S_SNAKE_DIE9
    {HERETIC_SPR_SNKE,
     15,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SNAKE_DIE10
    {HERETIC_SPR_SNFX,
     32768,
     5,
     {},
     HERETIC_S_SNAKEPRO_A2,
     0,
     0}, // HERETIC_S_SNAKEPRO_A1
    {HERETIC_SPR_SNFX,
     32769,
     5,
     {},
     HERETIC_S_SNAKEPRO_A3,
     0,
     0}, // HERETIC_S_SNAKEPRO_A2
    {HERETIC_SPR_SNFX,
     32770,
     5,
     {},
     HERETIC_S_SNAKEPRO_A4,
     0,
     0}, // HERETIC_S_SNAKEPRO_A3
    {HERETIC_SPR_SNFX,
     32771,
     5,
     {},
     HERETIC_S_SNAKEPRO_A1,
     0,
     0}, // HERETIC_S_SNAKEPRO_A4
    {HERETIC_SPR_SNFX,
     32772,
     5,
     {},
     HERETIC_S_SNAKEPRO_AX2,
     0,
     0}, // HERETIC_S_SNAKEPRO_AX1
    {HERETIC_SPR_SNFX,
     32773,
     5,
     {},
     HERETIC_S_SNAKEPRO_AX3,
     0,
     0}, // HERETIC_S_SNAKEPRO_AX2
    {HERETIC_SPR_SNFX,
     32774,
     4,
     {},
     HERETIC_S_SNAKEPRO_AX4,
     0,
     0}, // HERETIC_S_SNAKEPRO_AX3
    {HERETIC_SPR_SNFX,
     32775,
     3,
     {},
     HERETIC_S_SNAKEPRO_AX5,
     0,
     0}, // HERETIC_S_SNAKEPRO_AX4
    {HERETIC_SPR_SNFX,
     32776,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SNAKEPRO_AX5
    {HERETIC_SPR_SNFX,
     32777,
     6,
     {},
     HERETIC_S_SNAKEPRO_B2,
     0,
     0}, // HERETIC_S_SNAKEPRO_B1
    {HERETIC_SPR_SNFX,
     32778,
     6,
     {},
     HERETIC_S_SNAKEPRO_B1,
     0,
     0}, // HERETIC_S_SNAKEPRO_B2
    {HERETIC_SPR_SNFX,
     32779,
     5,
     {},
     HERETIC_S_SNAKEPRO_BX2,
     0,
     0}, // HERETIC_S_SNAKEPRO_BX1
    {HERETIC_SPR_SNFX,
     32780,
     5,
     {},
     HERETIC_S_SNAKEPRO_BX3,
     0,
     0}, // HERETIC_S_SNAKEPRO_BX2
    {HERETIC_SPR_SNFX,
     32781,
     4,
     {},
     HERETIC_S_SNAKEPRO_BX4,
     0,
     0}, // HERETIC_S_SNAKEPRO_BX3
    {HERETIC_SPR_SNFX,
     32782,
     3,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SNAKEPRO_BX4
    {HERETIC_SPR_HEAD, 0, 10, A_Look, HERETIC_S_HEAD_LOOK, 0,
     0}, // HERETIC_S_HEAD_LOOK
    {HERETIC_SPR_HEAD, 0, 4, A_Chase, HERETIC_S_HEAD_FLOAT, 0,
     0}, // HERETIC_S_HEAD_FLOAT
    {HERETIC_SPR_HEAD, 0, 5, A_FaceTarget, HERETIC_S_HEAD_ATK2, 0,
     0}, // HERETIC_S_HEAD_ATK1
    {HERETIC_SPR_HEAD, 1, 20, A_HeadAttack, HERETIC_S_HEAD_FLOAT, 0,
     0}, // HERETIC_S_HEAD_ATK2
    {HERETIC_SPR_HEAD,
     0,
     4,
     {},
     HERETIC_S_HEAD_PAIN2,
     0,
     0}, // HERETIC_S_HEAD_PAIN1
    {HERETIC_SPR_HEAD, 0, 4, A_Pain, HERETIC_S_HEAD_FLOAT, 0,
     0}, // HERETIC_S_HEAD_PAIN2
    {HERETIC_SPR_HEAD,
     2,
     7,
     {},
     HERETIC_S_HEAD_DIE2,
     0,
     0}, // HERETIC_S_HEAD_DIE1
    {HERETIC_SPR_HEAD, 3, 7, A_Scream, HERETIC_S_HEAD_DIE3, 0,
     0}, // HERETIC_S_HEAD_DIE2
    {HERETIC_SPR_HEAD,
     4,
     7,
     {},
     HERETIC_S_HEAD_DIE4,
     0,
     0}, // HERETIC_S_HEAD_DIE3
    {HERETIC_SPR_HEAD,
     5,
     7,
     {},
     HERETIC_S_HEAD_DIE5,
     0,
     0}, // HERETIC_S_HEAD_DIE4
    {HERETIC_SPR_HEAD, 6, 7, A_NoBlocking, HERETIC_S_HEAD_DIE6, 0,
     0}, // HERETIC_S_HEAD_DIE5
    {HERETIC_SPR_HEAD,
     7,
     7,
     {},
     HERETIC_S_HEAD_DIE7,
     0,
     0}, // HERETIC_S_HEAD_DIE6
    {HERETIC_SPR_HEAD, 8, -1, A_BossDeath, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_HEAD_DIE7
    {HERETIC_SPR_FX05,
     0,
     6,
     {},
     HERETIC_S_HEADFX1_2,
     0,
     0}, // HERETIC_S_HEADFX1_1
    {HERETIC_SPR_FX05,
     1,
     6,
     {},
     HERETIC_S_HEADFX1_3,
     0,
     0}, // HERETIC_S_HEADFX1_2
    {HERETIC_SPR_FX05,
     2,
     6,
     {},
     HERETIC_S_HEADFX1_1,
     0,
     0}, // HERETIC_S_HEADFX1_3
    {HERETIC_SPR_FX05, 3, 5, A_HeadIceImpact, HERETIC_S_HEADFXI1_2, 0,
     0}, // HERETIC_S_HEADFXI1_1
    {HERETIC_SPR_FX05,
     4,
     5,
     {},
     HERETIC_S_HEADFXI1_3,
     0,
     0}, // HERETIC_S_HEADFXI1_2
    {HERETIC_SPR_FX05,
     5,
     5,
     {},
     HERETIC_S_HEADFXI1_4,
     0,
     0},                                                // HERETIC_S_HEADFXI1_3
    {HERETIC_SPR_FX05, 6, 5, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_HEADFXI1_4
    {HERETIC_SPR_FX05,
     7,
     6,
     {},
     HERETIC_S_HEADFX2_2,
     0,
     0}, // HERETIC_S_HEADFX2_1
    {HERETIC_SPR_FX05,
     8,
     6,
     {},
     HERETIC_S_HEADFX2_3,
     0,
     0}, // HERETIC_S_HEADFX2_2
    {HERETIC_SPR_FX05,
     9,
     6,
     {},
     HERETIC_S_HEADFX2_1,
     0,
     0}, // HERETIC_S_HEADFX2_3
    {HERETIC_SPR_FX05,
     3,
     5,
     {},
     HERETIC_S_HEADFXI2_2,
     0,
     0}, // HERETIC_S_HEADFXI2_1
    {HERETIC_SPR_FX05,
     4,
     5,
     {},
     HERETIC_S_HEADFXI2_3,
     0,
     0}, // HERETIC_S_HEADFXI2_2
    {HERETIC_SPR_FX05,
     5,
     5,
     {},
     HERETIC_S_HEADFXI2_4,
     0,
     0},                                                // HERETIC_S_HEADFXI2_3
    {HERETIC_SPR_FX05, 6, 5, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_HEADFXI2_4
    {HERETIC_SPR_FX06, 0, 4, A_HeadFireGrow, HERETIC_S_HEADFX3_2, 0,
     0}, // HERETIC_S_HEADFX3_1
    {HERETIC_SPR_FX06, 1, 4, A_HeadFireGrow, HERETIC_S_HEADFX3_3, 0,
     0}, // HERETIC_S_HEADFX3_2
    {HERETIC_SPR_FX06, 2, 4, A_HeadFireGrow, HERETIC_S_HEADFX3_1, 0,
     0}, // HERETIC_S_HEADFX3_3
    {HERETIC_SPR_FX06,
     0,
     5,
     {},
     HERETIC_S_HEADFX3_5,
     0,
     0}, // HERETIC_S_HEADFX3_4
    {HERETIC_SPR_FX06,
     1,
     5,
     {},
     HERETIC_S_HEADFX3_6,
     0,
     0}, // HERETIC_S_HEADFX3_5
    {HERETIC_SPR_FX06,
     2,
     5,
     {},
     HERETIC_S_HEADFX3_4,
     0,
     0}, // HERETIC_S_HEADFX3_6
    {HERETIC_SPR_FX06,
     3,
     5,
     {},
     HERETIC_S_HEADFXI3_2,
     0,
     0}, // HERETIC_S_HEADFXI3_1
    {HERETIC_SPR_FX06,
     4,
     5,
     {},
     HERETIC_S_HEADFXI3_3,
     0,
     0}, // HERETIC_S_HEADFXI3_2
    {HERETIC_SPR_FX06,
     5,
     5,
     {},
     HERETIC_S_HEADFXI3_4,
     0,
     0},                                                // HERETIC_S_HEADFXI3_3
    {HERETIC_SPR_FX06, 6, 5, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_HEADFXI3_4
    {HERETIC_SPR_FX07,
     3,
     3,
     {},
     HERETIC_S_HEADFX4_2,
     0,
     0}, // HERETIC_S_HEADFX4_1
    {HERETIC_SPR_FX07,
     4,
     3,
     {},
     HERETIC_S_HEADFX4_3,
     0,
     0}, // HERETIC_S_HEADFX4_2
    {HERETIC_SPR_FX07,
     5,
     3,
     {},
     HERETIC_S_HEADFX4_4,
     0,
     0}, // HERETIC_S_HEADFX4_3
    {HERETIC_SPR_FX07,
     6,
     3,
     {},
     HERETIC_S_HEADFX4_5,
     0,
     0}, // HERETIC_S_HEADFX4_4
    {HERETIC_SPR_FX07, 0, 3, A_WhirlwindSeek, HERETIC_S_HEADFX4_6, 0,
     0}, // HERETIC_S_HEADFX4_5
    {HERETIC_SPR_FX07, 1, 3, A_WhirlwindSeek, HERETIC_S_HEADFX4_7, 0,
     0}, // HERETIC_S_HEADFX4_6
    {HERETIC_SPR_FX07, 2, 3, A_WhirlwindSeek, HERETIC_S_HEADFX4_5, 0,
     0}, // HERETIC_S_HEADFX4_7
    {HERETIC_SPR_FX07,
     6,
     4,
     {},
     HERETIC_S_HEADFXI4_2,
     0,
     0}, // HERETIC_S_HEADFXI4_1
    {HERETIC_SPR_FX07,
     5,
     4,
     {},
     HERETIC_S_HEADFXI4_3,
     0,
     0}, // HERETIC_S_HEADFXI4_2
    {HERETIC_SPR_FX07,
     4,
     4,
     {},
     HERETIC_S_HEADFXI4_4,
     0,
     0},                                                // HERETIC_S_HEADFXI4_3
    {HERETIC_SPR_FX07, 3, 4, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_HEADFXI4_4
    {HERETIC_SPR_CLNK, 0, 10, A_Look, HERETIC_S_CLINK_LOOK2, 0,
     0}, // HERETIC_S_CLINK_LOOK1
    {HERETIC_SPR_CLNK, 1, 10, A_Look, HERETIC_S_CLINK_LOOK1, 0,
     0}, // HERETIC_S_CLINK_LOOK2
    {HERETIC_SPR_CLNK, 0, 3, A_Chase, HERETIC_S_CLINK_WALK2, 0,
     0}, // HERETIC_S_CLINK_WALK1
    {HERETIC_SPR_CLNK, 1, 3, A_Chase, HERETIC_S_CLINK_WALK3, 0,
     0}, // HERETIC_S_CLINK_WALK2
    {HERETIC_SPR_CLNK, 2, 3, A_Chase, HERETIC_S_CLINK_WALK4, 0,
     0}, // HERETIC_S_CLINK_WALK3
    {HERETIC_SPR_CLNK, 3, 3, A_Chase, HERETIC_S_CLINK_WALK1, 0,
     0}, // HERETIC_S_CLINK_WALK4
    {HERETIC_SPR_CLNK, 4, 5, A_FaceTarget, HERETIC_S_CLINK_ATK2, 0,
     0}, // HERETIC_S_CLINK_ATK1
    {HERETIC_SPR_CLNK, 5, 4, A_FaceTarget, HERETIC_S_CLINK_ATK3, 0,
     0}, // HERETIC_S_CLINK_ATK2
    {HERETIC_SPR_CLNK, 6, 7, A_ClinkAttack, HERETIC_S_CLINK_WALK1, 0,
     0}, // HERETIC_S_CLINK_ATK3
    {HERETIC_SPR_CLNK,
     7,
     3,
     {},
     HERETIC_S_CLINK_PAIN2,
     0,
     0}, // HERETIC_S_CLINK_PAIN1
    {HERETIC_SPR_CLNK, 7, 3, A_Pain, HERETIC_S_CLINK_WALK1, 0,
     0}, // HERETIC_S_CLINK_PAIN2
    {HERETIC_SPR_CLNK,
     8,
     6,
     {},
     HERETIC_S_CLINK_DIE2,
     0,
     0}, // HERETIC_S_CLINK_DIE1
    {HERETIC_SPR_CLNK,
     9,
     6,
     {},
     HERETIC_S_CLINK_DIE3,
     0,
     0}, // HERETIC_S_CLINK_DIE2
    {HERETIC_SPR_CLNK, 10, 5, A_Scream, HERETIC_S_CLINK_DIE4, 0,
     0}, // HERETIC_S_CLINK_DIE3
    {HERETIC_SPR_CLNK, 11, 5, A_NoBlocking, HERETIC_S_CLINK_DIE5, 0,
     0}, // HERETIC_S_CLINK_DIE4
    {HERETIC_SPR_CLNK,
     12,
     5,
     {},
     HERETIC_S_CLINK_DIE6,
     0,
     0}, // HERETIC_S_CLINK_DIE5
    {HERETIC_SPR_CLNK,
     13,
     5,
     {},
     HERETIC_S_CLINK_DIE7,
     0,
     0}, // HERETIC_S_CLINK_DIE6
    {HERETIC_SPR_CLNK,
     14,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_CLINK_DIE7
    {HERETIC_SPR_WZRD, 0, 10, A_Look, HERETIC_S_WIZARD_LOOK2, 0,
     0}, // HERETIC_S_WIZARD_LOOK1
    {HERETIC_SPR_WZRD, 1, 10, A_Look, HERETIC_S_WIZARD_LOOK1, 0,
     0}, // HERETIC_S_WIZARD_LOOK2
    {HERETIC_SPR_WZRD, 0, 3, A_Chase, HERETIC_S_WIZARD_WALK2, 0,
     0}, // HERETIC_S_WIZARD_WALK1
    {HERETIC_SPR_WZRD, 0, 4, A_Chase, HERETIC_S_WIZARD_WALK3, 0,
     0}, // HERETIC_S_WIZARD_WALK2
    {HERETIC_SPR_WZRD, 0, 3, A_Chase, HERETIC_S_WIZARD_WALK4, 0,
     0}, // HERETIC_S_WIZARD_WALK3
    {HERETIC_SPR_WZRD, 0, 4, A_Chase, HERETIC_S_WIZARD_WALK5, 0,
     0}, // HERETIC_S_WIZARD_WALK4
    {HERETIC_SPR_WZRD, 1, 3, A_Chase, HERETIC_S_WIZARD_WALK6, 0,
     0}, // HERETIC_S_WIZARD_WALK5
    {HERETIC_SPR_WZRD, 1, 4, A_Chase, HERETIC_S_WIZARD_WALK7, 0,
     0}, // HERETIC_S_WIZARD_WALK6
    {HERETIC_SPR_WZRD, 1, 3, A_Chase, HERETIC_S_WIZARD_WALK8, 0,
     0}, // HERETIC_S_WIZARD_WALK7
    {HERETIC_SPR_WZRD, 1, 4, A_Chase, HERETIC_S_WIZARD_WALK1, 0,
     0}, // HERETIC_S_WIZARD_WALK8
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk1, HERETIC_S_WIZARD_ATK2, 0,
     0}, // HERETIC_S_WIZARD_ATK1
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk2, HERETIC_S_WIZARD_ATK3, 0,
     0}, // HERETIC_S_WIZARD_ATK2
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk1, HERETIC_S_WIZARD_ATK4, 0,
     0}, // HERETIC_S_WIZARD_ATK3
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk2, HERETIC_S_WIZARD_ATK5, 0,
     0}, // HERETIC_S_WIZARD_ATK4
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk1, HERETIC_S_WIZARD_ATK6, 0,
     0}, // HERETIC_S_WIZARD_ATK5
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk2, HERETIC_S_WIZARD_ATK7, 0,
     0}, // HERETIC_S_WIZARD_ATK6
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk1, HERETIC_S_WIZARD_ATK8, 0,
     0}, // HERETIC_S_WIZARD_ATK7
    {HERETIC_SPR_WZRD, 2, 4, A_WizAtk2, HERETIC_S_WIZARD_ATK9, 0,
     0}, // HERETIC_S_WIZARD_ATK8
    {HERETIC_SPR_WZRD, 3, 12, A_WizAtk3, HERETIC_S_WIZARD_WALK1, 0,
     0}, // HERETIC_S_WIZARD_ATK9
    {HERETIC_SPR_WZRD, 4, 3, A_GhostOff, HERETIC_S_WIZARD_PAIN2, 0,
     0}, // HERETIC_S_WIZARD_PAIN1
    {HERETIC_SPR_WZRD, 4, 3, A_Pain, HERETIC_S_WIZARD_WALK1, 0,
     0}, // HERETIC_S_WIZARD_PAIN2
    {HERETIC_SPR_WZRD, 5, 6, A_GhostOff, HERETIC_S_WIZARD_DIE2, 0,
     0}, // HERETIC_S_WIZARD_DIE1
    {HERETIC_SPR_WZRD, 6, 6, A_Scream, HERETIC_S_WIZARD_DIE3, 0,
     0}, // HERETIC_S_WIZARD_DIE2
    {HERETIC_SPR_WZRD,
     7,
     6,
     {},
     HERETIC_S_WIZARD_DIE4,
     0,
     0}, // HERETIC_S_WIZARD_DIE3
    {HERETIC_SPR_WZRD,
     8,
     6,
     {},
     HERETIC_S_WIZARD_DIE5,
     0,
     0}, // HERETIC_S_WIZARD_DIE4
    {HERETIC_SPR_WZRD, 9, 6, A_NoBlocking, HERETIC_S_WIZARD_DIE6, 0,
     0}, // HERETIC_S_WIZARD_DIE5
    {HERETIC_SPR_WZRD,
     10,
     6,
     {},
     HERETIC_S_WIZARD_DIE7,
     0,
     0}, // HERETIC_S_WIZARD_DIE6
    {HERETIC_SPR_WZRD,
     11,
     6,
     {},
     HERETIC_S_WIZARD_DIE8,
     0,
     0}, // HERETIC_S_WIZARD_DIE7
    {HERETIC_SPR_WZRD,
     12,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_WIZARD_DIE8
    {HERETIC_SPR_FX11,
     32768,
     6,
     {},
     HERETIC_S_WIZFX1_2,
     0,
     0}, // HERETIC_S_WIZFX1_1
    {HERETIC_SPR_FX11,
     32769,
     6,
     {},
     HERETIC_S_WIZFX1_1,
     0,
     0}, // HERETIC_S_WIZFX1_2
    {HERETIC_SPR_FX11,
     32770,
     5,
     {},
     HERETIC_S_WIZFXI1_2,
     0,
     0}, // HERETIC_S_WIZFXI1_1
    {HERETIC_SPR_FX11,
     32771,
     5,
     {},
     HERETIC_S_WIZFXI1_3,
     0,
     0}, // HERETIC_S_WIZFXI1_2
    {HERETIC_SPR_FX11,
     32772,
     5,
     {},
     HERETIC_S_WIZFXI1_4,
     0,
     0}, // HERETIC_S_WIZFXI1_3
    {HERETIC_SPR_FX11,
     32773,
     5,
     {},
     HERETIC_S_WIZFXI1_5,
     0,
     0}, // HERETIC_S_WIZFXI1_4
    {HERETIC_SPR_FX11,
     32774,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_WIZFXI1_5
    {HERETIC_SPR_IMPX, 0, 10, A_Look, HERETIC_S_IMP_LOOK2, 0,
     0}, // HERETIC_S_IMP_LOOK1
    {HERETIC_SPR_IMPX, 1, 10, A_Look, HERETIC_S_IMP_LOOK3, 0,
     0}, // HERETIC_S_IMP_LOOK2
    {HERETIC_SPR_IMPX, 2, 10, A_Look, HERETIC_S_IMP_LOOK4, 0,
     0}, // HERETIC_S_IMP_LOOK3
    {HERETIC_SPR_IMPX, 1, 10, A_Look, HERETIC_S_IMP_LOOK1, 0,
     0}, // HERETIC_S_IMP_LOOK4
    {HERETIC_SPR_IMPX, 0, 3, A_Chase, HERETIC_S_IMP_FLY2, 0,
     0}, // HERETIC_S_IMP_FLY1
    {HERETIC_SPR_IMPX, 0, 3, A_Chase, HERETIC_S_IMP_FLY3, 0,
     0}, // HERETIC_S_IMP_FLY2
    {HERETIC_SPR_IMPX, 1, 3, A_Chase, HERETIC_S_IMP_FLY4, 0,
     0}, // HERETIC_S_IMP_FLY3
    {HERETIC_SPR_IMPX, 1, 3, A_Chase, HERETIC_S_IMP_FLY5, 0,
     0}, // HERETIC_S_IMP_FLY4
    {HERETIC_SPR_IMPX, 2, 3, A_Chase, HERETIC_S_IMP_FLY6, 0,
     0}, // HERETIC_S_IMP_FLY5
    {HERETIC_SPR_IMPX, 2, 3, A_Chase, HERETIC_S_IMP_FLY7, 0,
     0}, // HERETIC_S_IMP_FLY6
    {HERETIC_SPR_IMPX, 1, 3, A_Chase, HERETIC_S_IMP_FLY8, 0,
     0}, // HERETIC_S_IMP_FLY7
    {HERETIC_SPR_IMPX, 1, 3, A_Chase, HERETIC_S_IMP_FLY1, 0,
     0}, // HERETIC_S_IMP_FLY8
    {HERETIC_SPR_IMPX, 3, 6, A_FaceTarget, HERETIC_S_IMP_MEATK2, 0,
     0}, // HERETIC_S_IMP_MEATK1
    {HERETIC_SPR_IMPX, 4, 6, A_FaceTarget, HERETIC_S_IMP_MEATK3, 0,
     0}, // HERETIC_S_IMP_MEATK2
    {HERETIC_SPR_IMPX, 5, 6, A_ImpMeAttack, HERETIC_S_IMP_FLY1, 0,
     0}, // HERETIC_S_IMP_MEATK3
    {HERETIC_SPR_IMPX, 0, 10, A_FaceTarget, HERETIC_S_IMP_MSATK1_2, 0,
     0}, // HERETIC_S_IMP_MSATK1_1
    {HERETIC_SPR_IMPX, 1, 6, A_ImpMsAttack, HERETIC_S_IMP_MSATK1_3, 0,
     0}, // HERETIC_S_IMP_MSATK1_2
    {HERETIC_SPR_IMPX,
     2,
     6,
     {},
     HERETIC_S_IMP_MSATK1_4,
     0,
     0}, // HERETIC_S_IMP_MSATK1_3
    {HERETIC_SPR_IMPX,
     1,
     6,
     {},
     HERETIC_S_IMP_MSATK1_5,
     0,
     0}, // HERETIC_S_IMP_MSATK1_4
    {HERETIC_SPR_IMPX,
     0,
     6,
     {},
     HERETIC_S_IMP_MSATK1_6,
     0,
     0}, // HERETIC_S_IMP_MSATK1_5
    {HERETIC_SPR_IMPX,
     1,
     6,
     {},
     HERETIC_S_IMP_MSATK1_3,
     0,
     0}, // HERETIC_S_IMP_MSATK1_6
    {HERETIC_SPR_IMPX, 3, 6, A_FaceTarget, HERETIC_S_IMP_MSATK2_2, 0,
     0}, // HERETIC_S_IMP_MSATK2_1
    {HERETIC_SPR_IMPX, 4, 6, A_FaceTarget, HERETIC_S_IMP_MSATK2_3, 0,
     0}, // HERETIC_S_IMP_MSATK2_2
    {HERETIC_SPR_IMPX, 5, 6, A_ImpMsAttack2, HERETIC_S_IMP_FLY1, 0,
     0}, // HERETIC_S_IMP_MSATK2_3
    {HERETIC_SPR_IMPX,
     6,
     3,
     {},
     HERETIC_S_IMP_PAIN2,
     0,
     0}, // HERETIC_S_IMP_PAIN1
    {HERETIC_SPR_IMPX, 6, 3, A_Pain, HERETIC_S_IMP_FLY1, 0,
     0}, // HERETIC_S_IMP_PAIN2
    {HERETIC_SPR_IMPX, 6, 4, A_ImpDeath, HERETIC_S_IMP_DIE2, 0,
     0}, // HERETIC_S_IMP_DIE1
    {HERETIC_SPR_IMPX,
     7,
     5,
     {},
     HERETIC_S_IMP_DIE2,
     0,
     0}, // HERETIC_S_IMP_DIE2
    {HERETIC_SPR_IMPX, 18, 5, A_ImpXDeath1, HERETIC_S_IMP_XDIE2, 0,
     0}, // HERETIC_S_IMP_XDIE1
    {HERETIC_SPR_IMPX,
     19,
     5,
     {},
     HERETIC_S_IMP_XDIE3,
     0,
     0}, // HERETIC_S_IMP_XDIE2
    {HERETIC_SPR_IMPX,
     20,
     5,
     {},
     HERETIC_S_IMP_XDIE4,
     0,
     0}, // HERETIC_S_IMP_XDIE3
    {HERETIC_SPR_IMPX, 21, 5, A_ImpXDeath2, HERETIC_S_IMP_XDIE5, 0,
     0}, // HERETIC_S_IMP_XDIE4
    {HERETIC_SPR_IMPX,
     22,
     5,
     {},
     HERETIC_S_IMP_XDIE5,
     0,
     0}, // HERETIC_S_IMP_XDIE5
    {HERETIC_SPR_IMPX, 8, 7, A_ImpExplode, HERETIC_S_IMP_CRASH2, 0,
     0}, // HERETIC_S_IMP_CRASH1
    {HERETIC_SPR_IMPX, 9, 7, A_Scream, HERETIC_S_IMP_CRASH3, 0,
     0}, // HERETIC_S_IMP_CRASH2
    {HERETIC_SPR_IMPX,
     10,
     7,
     {},
     HERETIC_S_IMP_CRASH4,
     0,
     0}, // HERETIC_S_IMP_CRASH3
    {HERETIC_SPR_IMPX,
     11,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_IMP_CRASH4
    {HERETIC_SPR_IMPX,
     23,
     7,
     {},
     HERETIC_S_IMP_XCRASH2,
     0,
     0}, // HERETIC_S_IMP_XCRASH1
    {HERETIC_SPR_IMPX,
     24,
     7,
     {},
     HERETIC_S_IMP_XCRASH3,
     0,
     0}, // HERETIC_S_IMP_XCRASH2
    {HERETIC_SPR_IMPX,
     25,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_IMP_XCRASH3
    {HERETIC_SPR_IMPX,
     12,
     5,
     {},
     HERETIC_S_IMP_CHUNKA2,
     0,
     0}, // HERETIC_S_IMP_CHUNKA1
    {HERETIC_SPR_IMPX,
     13,
     700,
     {},
     HERETIC_S_IMP_CHUNKA3,
     0,
     0}, // HERETIC_S_IMP_CHUNKA2
    {HERETIC_SPR_IMPX,
     14,
     700,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_IMP_CHUNKA3
    {HERETIC_SPR_IMPX,
     15,
     5,
     {},
     HERETIC_S_IMP_CHUNKB2,
     0,
     0}, // HERETIC_S_IMP_CHUNKB1
    {HERETIC_SPR_IMPX,
     16,
     700,
     {},
     HERETIC_S_IMP_CHUNKB3,
     0,
     0}, // HERETIC_S_IMP_CHUNKB2
    {HERETIC_SPR_IMPX,
     17,
     700,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_IMP_CHUNKB3
    {HERETIC_SPR_FX10,
     32768,
     6,
     {},
     HERETIC_S_IMPFX2,
     0,
     0}, // HERETIC_S_IMPFX1
    {HERETIC_SPR_FX10,
     32769,
     6,
     {},
     HERETIC_S_IMPFX3,
     0,
     0}, // HERETIC_S_IMPFX2
    {HERETIC_SPR_FX10,
     32770,
     6,
     {},
     HERETIC_S_IMPFX1,
     0,
     0}, // HERETIC_S_IMPFX3
    {HERETIC_SPR_FX10,
     32771,
     5,
     {},
     HERETIC_S_IMPFXI2,
     0,
     0}, // HERETIC_S_IMPFXI1
    {HERETIC_SPR_FX10,
     32772,
     5,
     {},
     HERETIC_S_IMPFXI3,
     0,
     0}, // HERETIC_S_IMPFXI2
    {HERETIC_SPR_FX10,
     32773,
     5,
     {},
     HERETIC_S_IMPFXI4,
     0,
     0},                                                    // HERETIC_S_IMPFXI3
    {HERETIC_SPR_FX10, 32774, 5, {}, HERETIC_S_NULL, 0, 0}, // HERETIC_S_IMPFXI4
    {HERETIC_SPR_KNIG, 0, 10, A_Look, HERETIC_S_KNIGHT_STND2, 0,
     0}, // HERETIC_S_KNIGHT_STND1
    {HERETIC_SPR_KNIG, 1, 10, A_Look, HERETIC_S_KNIGHT_STND1, 0,
     0}, // HERETIC_S_KNIGHT_STND2
    {HERETIC_SPR_KNIG, 0, 4, A_Chase, HERETIC_S_KNIGHT_WALK2, 0,
     0}, // HERETIC_S_KNIGHT_WALK1
    {HERETIC_SPR_KNIG, 1, 4, A_Chase, HERETIC_S_KNIGHT_WALK3, 0,
     0}, // HERETIC_S_KNIGHT_WALK2
    {HERETIC_SPR_KNIG, 2, 4, A_Chase, HERETIC_S_KNIGHT_WALK4, 0,
     0}, // HERETIC_S_KNIGHT_WALK3
    {HERETIC_SPR_KNIG, 3, 4, A_Chase, HERETIC_S_KNIGHT_WALK1, 0,
     0}, // HERETIC_S_KNIGHT_WALK4
    {HERETIC_SPR_KNIG, 4, 10, A_FaceTarget, HERETIC_S_KNIGHT_ATK2, 0,
     0}, // HERETIC_S_KNIGHT_ATK1
    {HERETIC_SPR_KNIG, 5, 8, A_FaceTarget, HERETIC_S_KNIGHT_ATK3, 0,
     0}, // HERETIC_S_KNIGHT_ATK2
    {HERETIC_SPR_KNIG, 6, 8, A_KnightAttack, HERETIC_S_KNIGHT_ATK4, 0,
     0}, // HERETIC_S_KNIGHT_ATK3
    {HERETIC_SPR_KNIG, 4, 10, A_FaceTarget, HERETIC_S_KNIGHT_ATK5, 0,
     0}, // HERETIC_S_KNIGHT_ATK4
    {HERETIC_SPR_KNIG, 5, 8, A_FaceTarget, HERETIC_S_KNIGHT_ATK6, 0,
     0}, // HERETIC_S_KNIGHT_ATK5
    {HERETIC_SPR_KNIG, 6, 8, A_KnightAttack, HERETIC_S_KNIGHT_WALK1, 0,
     0}, // HERETIC_S_KNIGHT_ATK6
    {HERETIC_SPR_KNIG,
     7,
     3,
     {},
     HERETIC_S_KNIGHT_PAIN2,
     0,
     0}, // HERETIC_S_KNIGHT_PAIN1
    {HERETIC_SPR_KNIG, 7, 3, A_Pain, HERETIC_S_KNIGHT_WALK1, 0,
     0}, // HERETIC_S_KNIGHT_PAIN2
    {HERETIC_SPR_KNIG,
     8,
     6,
     {},
     HERETIC_S_KNIGHT_DIE2,
     0,
     0}, // HERETIC_S_KNIGHT_DIE1
    {HERETIC_SPR_KNIG, 9, 6, A_Scream, HERETIC_S_KNIGHT_DIE3, 0,
     0}, // HERETIC_S_KNIGHT_DIE2
    {HERETIC_SPR_KNIG,
     10,
     6,
     {},
     HERETIC_S_KNIGHT_DIE4,
     0,
     0}, // HERETIC_S_KNIGHT_DIE3
    {HERETIC_SPR_KNIG, 11, 6, A_NoBlocking, HERETIC_S_KNIGHT_DIE5, 0,
     0}, // HERETIC_S_KNIGHT_DIE4
    {HERETIC_SPR_KNIG,
     12,
     6,
     {},
     HERETIC_S_KNIGHT_DIE6,
     0,
     0}, // HERETIC_S_KNIGHT_DIE5
    {HERETIC_SPR_KNIG,
     13,
     6,
     {},
     HERETIC_S_KNIGHT_DIE7,
     0,
     0}, // HERETIC_S_KNIGHT_DIE6
    {HERETIC_SPR_KNIG,
     14,
     -1,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_KNIGHT_DIE7
    {HERETIC_SPR_SPAX, 32768, 3, A_ContMobjSound, HERETIC_S_SPINAXE2, 0,
     0}, // HERETIC_S_SPINAXE1
    {HERETIC_SPR_SPAX,
     32769,
     3,
     {},
     HERETIC_S_SPINAXE3,
     0,
     0}, // HERETIC_S_SPINAXE2
    {HERETIC_SPR_SPAX,
     32770,
     3,
     {},
     HERETIC_S_SPINAXE1,
     0,
     0}, // HERETIC_S_SPINAXE3
    {HERETIC_SPR_SPAX,
     32771,
     6,
     {},
     HERETIC_S_SPINAXEX2,
     0,
     0}, // HERETIC_S_SPINAXEX1
    {HERETIC_SPR_SPAX,
     32772,
     6,
     {},
     HERETIC_S_SPINAXEX3,
     0,
     0}, // HERETIC_S_SPINAXEX2
    {HERETIC_SPR_SPAX,
     32773,
     6,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SPINAXEX3
    {HERETIC_SPR_RAXE, 32768, 5, A_DripBlood, HERETIC_S_REDAXE2, 0,
     0}, // HERETIC_S_REDAXE1
    {HERETIC_SPR_RAXE, 32769, 5, A_DripBlood, HERETIC_S_REDAXE1, 0,
     0}, // HERETIC_S_REDAXE2
    {HERETIC_SPR_RAXE,
     32770,
     6,
     {},
     HERETIC_S_REDAXEX2,
     0,
     0}, // HERETIC_S_REDAXEX1
    {HERETIC_SPR_RAXE,
     32771,
     6,
     {},
     HERETIC_S_REDAXEX3,
     0,
     0}, // HERETIC_S_REDAXEX2
    {HERETIC_SPR_RAXE,
     32772,
     6,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_REDAXEX3
    {HERETIC_SPR_SRCR, 0, 10, A_Look, HERETIC_S_SRCR1_LOOK2, 0,
     0}, // HERETIC_S_SRCR1_LOOK1
    {HERETIC_SPR_SRCR, 1, 10, A_Look, HERETIC_S_SRCR1_LOOK1, 0,
     0}, // HERETIC_S_SRCR1_LOOK2
    {HERETIC_SPR_SRCR, 0, 5, A_Sor1Chase, HERETIC_S_SRCR1_WALK2, 0,
     0}, // HERETIC_S_SRCR1_WALK1
    {HERETIC_SPR_SRCR, 1, 5, A_Sor1Chase, HERETIC_S_SRCR1_WALK3, 0,
     0}, // HERETIC_S_SRCR1_WALK2
    {HERETIC_SPR_SRCR, 2, 5, A_Sor1Chase, HERETIC_S_SRCR1_WALK4, 0,
     0}, // HERETIC_S_SRCR1_WALK3
    {HERETIC_SPR_SRCR, 3, 5, A_Sor1Chase, HERETIC_S_SRCR1_WALK1, 0,
     0}, // HERETIC_S_SRCR1_WALK4
    {HERETIC_SPR_SRCR, 16, 6, A_Sor1Pain, HERETIC_S_SRCR1_WALK1, 0,
     0}, // HERETIC_S_SRCR1_PAIN1
    {HERETIC_SPR_SRCR, 16, 7, A_FaceTarget, HERETIC_S_SRCR1_ATK2, 0,
     0}, // HERETIC_S_SRCR1_ATK1
    {HERETIC_SPR_SRCR, 17, 6, A_FaceTarget, HERETIC_S_SRCR1_ATK3, 0,
     0}, // HERETIC_S_SRCR1_ATK2
    {HERETIC_SPR_SRCR, 18, 10, A_Srcr1Attack, HERETIC_S_SRCR1_WALK1, 0,
     0}, // HERETIC_S_SRCR1_ATK3
    {HERETIC_SPR_SRCR, 18, 10, A_FaceTarget, HERETIC_S_SRCR1_ATK5, 0,
     0}, // HERETIC_S_SRCR1_ATK4
    {HERETIC_SPR_SRCR, 16, 7, A_FaceTarget, HERETIC_S_SRCR1_ATK6, 0,
     0}, // HERETIC_S_SRCR1_ATK5
    {HERETIC_SPR_SRCR, 17, 6, A_FaceTarget, HERETIC_S_SRCR1_ATK7, 0,
     0}, // HERETIC_S_SRCR1_ATK6
    {HERETIC_SPR_SRCR, 18, 10, A_Srcr1Attack, HERETIC_S_SRCR1_WALK1, 0,
     0}, // HERETIC_S_SRCR1_ATK7
    {HERETIC_SPR_SRCR,
     4,
     7,
     {},
     HERETIC_S_SRCR1_DIE2,
     0,
     0}, // HERETIC_S_SRCR1_DIE1
    {HERETIC_SPR_SRCR, 5, 7, A_Scream, HERETIC_S_SRCR1_DIE3, 0,
     0}, // HERETIC_S_SRCR1_DIE2
    {HERETIC_SPR_SRCR,
     6,
     7,
     {},
     HERETIC_S_SRCR1_DIE4,
     0,
     0}, // HERETIC_S_SRCR1_DIE3
    {HERETIC_SPR_SRCR,
     7,
     6,
     {},
     HERETIC_S_SRCR1_DIE5,
     0,
     0}, // HERETIC_S_SRCR1_DIE4
    {HERETIC_SPR_SRCR,
     8,
     6,
     {},
     HERETIC_S_SRCR1_DIE6,
     0,
     0}, // HERETIC_S_SRCR1_DIE5
    {HERETIC_SPR_SRCR,
     9,
     6,
     {},
     HERETIC_S_SRCR1_DIE7,
     0,
     0}, // HERETIC_S_SRCR1_DIE6
    {HERETIC_SPR_SRCR,
     10,
     6,
     {},
     HERETIC_S_SRCR1_DIE8,
     0,
     0}, // HERETIC_S_SRCR1_DIE7
    {HERETIC_SPR_SRCR, 11, 25, A_SorZap, HERETIC_S_SRCR1_DIE9, 0,
     0}, // HERETIC_S_SRCR1_DIE8
    {HERETIC_SPR_SRCR,
     12,
     5,
     {},
     HERETIC_S_SRCR1_DIE10,
     0,
     0}, // HERETIC_S_SRCR1_DIE9
    {HERETIC_SPR_SRCR,
     13,
     5,
     {},
     HERETIC_S_SRCR1_DIE11,
     0,
     0}, // HERETIC_S_SRCR1_DIE10
    {HERETIC_SPR_SRCR,
     14,
     4,
     {},
     HERETIC_S_SRCR1_DIE12,
     0,
     0}, // HERETIC_S_SRCR1_DIE11
    {HERETIC_SPR_SRCR, 11, 20, A_SorZap, HERETIC_S_SRCR1_DIE13, 0,
     0}, // HERETIC_S_SRCR1_DIE12
    {HERETIC_SPR_SRCR,
     12,
     5,
     {},
     HERETIC_S_SRCR1_DIE14,
     0,
     0}, // HERETIC_S_SRCR1_DIE13
    {HERETIC_SPR_SRCR,
     13,
     5,
     {},
     HERETIC_S_SRCR1_DIE15,
     0,
     0}, // HERETIC_S_SRCR1_DIE14
    {HERETIC_SPR_SRCR,
     14,
     4,
     {},
     HERETIC_S_SRCR1_DIE16,
     0,
     0}, // HERETIC_S_SRCR1_DIE15
    {HERETIC_SPR_SRCR,
     11,
     12,
     {},
     HERETIC_S_SRCR1_DIE17,
     0,
     0}, // HERETIC_S_SRCR1_DIE16
    {HERETIC_SPR_SRCR, 15, -1, A_SorcererRise, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_SRCR1_DIE17
    {HERETIC_SPR_FX14,
     32768,
     6,
     {},
     HERETIC_S_SRCRFX1_2,
     0,
     0}, // HERETIC_S_SRCRFX1_1
    {HERETIC_SPR_FX14,
     32769,
     6,
     {},
     HERETIC_S_SRCRFX1_3,
     0,
     0}, // HERETIC_S_SRCRFX1_2
    {HERETIC_SPR_FX14,
     32770,
     6,
     {},
     HERETIC_S_SRCRFX1_1,
     0,
     0}, // HERETIC_S_SRCRFX1_3
    {HERETIC_SPR_FX14,
     32771,
     5,
     {},
     HERETIC_S_SRCRFXI1_2,
     0,
     0}, // HERETIC_S_SRCRFXI1_1
    {HERETIC_SPR_FX14,
     32772,
     5,
     {},
     HERETIC_S_SRCRFXI1_3,
     0,
     0}, // HERETIC_S_SRCRFXI1_2
    {HERETIC_SPR_FX14,
     32773,
     5,
     {},
     HERETIC_S_SRCRFXI1_4,
     0,
     0}, // HERETIC_S_SRCRFXI1_3
    {HERETIC_SPR_FX14,
     32774,
     5,
     {},
     HERETIC_S_SRCRFXI1_5,
     0,
     0}, // HERETIC_S_SRCRFXI1_4
    {HERETIC_SPR_FX14,
     32775,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SRCRFXI1_5
    {HERETIC_SPR_SOR2,
     0,
     4,
     {},
     HERETIC_S_SOR2_RISE2,
     0,
     0}, // HERETIC_S_SOR2_RISE1
    {HERETIC_SPR_SOR2,
     1,
     4,
     {},
     HERETIC_S_SOR2_RISE3,
     0,
     0}, // HERETIC_S_SOR2_RISE2
    {HERETIC_SPR_SOR2, 2, 4, A_SorRise, HERETIC_S_SOR2_RISE4, 0,
     0}, // HERETIC_S_SOR2_RISE3
    {HERETIC_SPR_SOR2,
     3,
     4,
     {},
     HERETIC_S_SOR2_RISE5,
     0,
     0}, // HERETIC_S_SOR2_RISE4
    {HERETIC_SPR_SOR2,
     4,
     4,
     {},
     HERETIC_S_SOR2_RISE6,
     0,
     0}, // HERETIC_S_SOR2_RISE5
    {HERETIC_SPR_SOR2,
     5,
     4,
     {},
     HERETIC_S_SOR2_RISE7,
     0,
     0}, // HERETIC_S_SOR2_RISE6
    {HERETIC_SPR_SOR2, 6, 12, A_SorSightSnd, HERETIC_S_SOR2_WALK1, 0,
     0}, // HERETIC_S_SOR2_RISE7
    {HERETIC_SPR_SOR2, 12, 10, A_Look, HERETIC_S_SOR2_LOOK2, 0,
     0}, // HERETIC_S_SOR2_LOOK1
    {HERETIC_SPR_SOR2, 13, 10, A_Look, HERETIC_S_SOR2_LOOK1, 0,
     0}, // HERETIC_S_SOR2_LOOK2
    {HERETIC_SPR_SOR2, 12, 4, A_Chase, HERETIC_S_SOR2_WALK2, 0,
     0}, // HERETIC_S_SOR2_WALK1
    {HERETIC_SPR_SOR2, 13, 4, A_Chase, HERETIC_S_SOR2_WALK3, 0,
     0}, // HERETIC_S_SOR2_WALK2
    {HERETIC_SPR_SOR2, 14, 4, A_Chase, HERETIC_S_SOR2_WALK4, 0,
     0}, // HERETIC_S_SOR2_WALK3
    {HERETIC_SPR_SOR2, 15, 4, A_Chase, HERETIC_S_SOR2_WALK1, 0,
     0}, // HERETIC_S_SOR2_WALK4
    {HERETIC_SPR_SOR2,
     16,
     3,
     {},
     HERETIC_S_SOR2_PAIN2,
     0,
     0}, // HERETIC_S_SOR2_PAIN1
    {HERETIC_SPR_SOR2, 16, 6, A_Pain, HERETIC_S_SOR2_WALK1, 0,
     0}, // HERETIC_S_SOR2_PAIN2
    {HERETIC_SPR_SOR2, 17, 9, A_Srcr2Decide, HERETIC_S_SOR2_ATK2, 0,
     0}, // HERETIC_S_SOR2_ATK1
    {HERETIC_SPR_SOR2, 18, 9, A_FaceTarget, HERETIC_S_SOR2_ATK3, 0,
     0}, // HERETIC_S_SOR2_ATK2
    {HERETIC_SPR_SOR2, 19, 20, A_Srcr2Attack, HERETIC_S_SOR2_WALK1, 0,
     0}, // HERETIC_S_SOR2_ATK3
    {HERETIC_SPR_SOR2,
     11,
     6,
     {},
     HERETIC_S_SOR2_TELE2,
     0,
     0}, // HERETIC_S_SOR2_TELE1
    {HERETIC_SPR_SOR2,
     10,
     6,
     {},
     HERETIC_S_SOR2_TELE3,
     0,
     0}, // HERETIC_S_SOR2_TELE2
    {HERETIC_SPR_SOR2,
     9,
     6,
     {},
     HERETIC_S_SOR2_TELE4,
     0,
     0}, // HERETIC_S_SOR2_TELE3
    {HERETIC_SPR_SOR2,
     8,
     6,
     {},
     HERETIC_S_SOR2_TELE5,
     0,
     0}, // HERETIC_S_SOR2_TELE4
    {HERETIC_SPR_SOR2,
     7,
     6,
     {},
     HERETIC_S_SOR2_TELE6,
     0,
     0}, // HERETIC_S_SOR2_TELE5
    {HERETIC_SPR_SOR2,
     6,
     6,
     {},
     HERETIC_S_SOR2_WALK1,
     0,
     0}, // HERETIC_S_SOR2_TELE6
    {HERETIC_SPR_SDTH, 0, 8, A_Sor2DthInit, HERETIC_S_SOR2_DIE2, 0,
     0}, // HERETIC_S_SOR2_DIE1
    {HERETIC_SPR_SDTH,
     1,
     8,
     {},
     HERETIC_S_SOR2_DIE3,
     0,
     0}, // HERETIC_S_SOR2_DIE2
    {HERETIC_SPR_SDTH, 2, 8, A_SorDSph, HERETIC_S_SOR2_DIE4, 0,
     0}, // HERETIC_S_SOR2_DIE3
    {HERETIC_SPR_SDTH,
     3,
     7,
     {},
     HERETIC_S_SOR2_DIE5,
     0,
     0}, // HERETIC_S_SOR2_DIE4
    {HERETIC_SPR_SDTH,
     4,
     7,
     {},
     HERETIC_S_SOR2_DIE6,
     0,
     0}, // HERETIC_S_SOR2_DIE5
    {HERETIC_SPR_SDTH, 5, 7, A_Sor2DthLoop, HERETIC_S_SOR2_DIE7, 0,
     0}, // HERETIC_S_SOR2_DIE6
    {HERETIC_SPR_SDTH, 6, 6, A_SorDExp, HERETIC_S_SOR2_DIE8, 0,
     0}, // HERETIC_S_SOR2_DIE7
    {HERETIC_SPR_SDTH,
     7,
     6,
     {},
     HERETIC_S_SOR2_DIE9,
     0,
     0}, // HERETIC_S_SOR2_DIE8
    {HERETIC_SPR_SDTH,
     8,
     18,
     {},
     HERETIC_S_SOR2_DIE10,
     0,
     0}, // HERETIC_S_SOR2_DIE9
    {HERETIC_SPR_SDTH, 9, 6, A_NoBlocking, HERETIC_S_SOR2_DIE11, 0,
     0}, // HERETIC_S_SOR2_DIE10
    {HERETIC_SPR_SDTH, 10, 6, A_SorDBon, HERETIC_S_SOR2_DIE12, 0,
     0}, // HERETIC_S_SOR2_DIE11
    {HERETIC_SPR_SDTH,
     11,
     6,
     {},
     HERETIC_S_SOR2_DIE13,
     0,
     0}, // HERETIC_S_SOR2_DIE12
    {HERETIC_SPR_SDTH,
     12,
     6,
     {},
     HERETIC_S_SOR2_DIE14,
     0,
     0}, // HERETIC_S_SOR2_DIE13
    {HERETIC_SPR_SDTH,
     13,
     6,
     {},
     HERETIC_S_SOR2_DIE15,
     0,
     0}, // HERETIC_S_SOR2_DIE14
    {HERETIC_SPR_SDTH, 14, -1, A_BossDeath, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_SOR2_DIE15
    {HERETIC_SPR_FX16, 32768, 3, A_BlueSpark, HERETIC_S_SOR2FX1_2, 0,
     0}, // HERETIC_S_SOR2FX1_1
    {HERETIC_SPR_FX16, 32769, 3, A_BlueSpark, HERETIC_S_SOR2FX1_3, 0,
     0}, // HERETIC_S_SOR2FX1_2
    {HERETIC_SPR_FX16, 32770, 3, A_BlueSpark, HERETIC_S_SOR2FX1_1, 0,
     0}, // HERETIC_S_SOR2FX1_3
    {HERETIC_SPR_FX16, 32774, 5, A_Explode, HERETIC_S_SOR2FXI1_2, 0,
     0}, // HERETIC_S_SOR2FXI1_1
    {HERETIC_SPR_FX16,
     32775,
     5,
     {},
     HERETIC_S_SOR2FXI1_3,
     0,
     0}, // HERETIC_S_SOR2FXI1_2
    {HERETIC_SPR_FX16,
     32776,
     5,
     {},
     HERETIC_S_SOR2FXI1_4,
     0,
     0}, // HERETIC_S_SOR2FXI1_3
    {HERETIC_SPR_FX16,
     32777,
     5,
     {},
     HERETIC_S_SOR2FXI1_5,
     0,
     0}, // HERETIC_S_SOR2FXI1_4
    {HERETIC_SPR_FX16,
     32778,
     5,
     {},
     HERETIC_S_SOR2FXI1_6,
     0,
     0}, // HERETIC_S_SOR2FXI1_5
    {HERETIC_SPR_FX16,
     32779,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SOR2FXI1_6
    {HERETIC_SPR_FX16,
     32771,
     12,
     {},
     HERETIC_S_SOR2FXSPARK2,
     0,
     0}, // HERETIC_S_SOR2FXSPARK1
    {HERETIC_SPR_FX16,
     32772,
     12,
     {},
     HERETIC_S_SOR2FXSPARK3,
     0,
     0}, // HERETIC_S_SOR2FXSPARK2
    {HERETIC_SPR_FX16,
     32773,
     12,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SOR2FXSPARK3
    {HERETIC_SPR_FX11,
     32768,
     35,
     {},
     HERETIC_S_SOR2FX2_2,
     0,
     0}, // HERETIC_S_SOR2FX2_1
    {HERETIC_SPR_FX11, 32768, 5, A_GenWizard, HERETIC_S_SOR2FX2_3, 0,
     0}, // HERETIC_S_SOR2FX2_2
    {HERETIC_SPR_FX11,
     32769,
     5,
     {},
     HERETIC_S_SOR2FX2_2,
     0,
     0}, // HERETIC_S_SOR2FX2_3
    {HERETIC_SPR_FX11,
     32770,
     5,
     {},
     HERETIC_S_SOR2FXI2_2,
     0,
     0}, // HERETIC_S_SOR2FXI2_1
    {HERETIC_SPR_FX11,
     32771,
     5,
     {},
     HERETIC_S_SOR2FXI2_3,
     0,
     0}, // HERETIC_S_SOR2FXI2_2
    {HERETIC_SPR_FX11,
     32772,
     5,
     {},
     HERETIC_S_SOR2FXI2_4,
     0,
     0}, // HERETIC_S_SOR2FXI2_3
    {HERETIC_SPR_FX11,
     32773,
     5,
     {},
     HERETIC_S_SOR2FXI2_5,
     0,
     0}, // HERETIC_S_SOR2FXI2_4
    {HERETIC_SPR_FX11,
     32774,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SOR2FXI2_5
    {HERETIC_SPR_SOR2,
     6,
     8,
     {},
     HERETIC_S_SOR2TELEFADE2,
     0,
     0}, // HERETIC_S_SOR2TELEFADE1
    {HERETIC_SPR_SOR2,
     7,
     6,
     {},
     HERETIC_S_SOR2TELEFADE3,
     0,
     0}, // HERETIC_S_SOR2TELEFADE2
    {HERETIC_SPR_SOR2,
     8,
     6,
     {},
     HERETIC_S_SOR2TELEFADE4,
     0,
     0}, // HERETIC_S_SOR2TELEFADE3
    {HERETIC_SPR_SOR2,
     9,
     6,
     {},
     HERETIC_S_SOR2TELEFADE5,
     0,
     0}, // HERETIC_S_SOR2TELEFADE4
    {HERETIC_SPR_SOR2,
     10,
     6,
     {},
     HERETIC_S_SOR2TELEFADE6,
     0,
     0}, // HERETIC_S_SOR2TELEFADE5
    {HERETIC_SPR_SOR2,
     11,
     6,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_SOR2TELEFADE6
    {HERETIC_SPR_MNTR, 0, 10, A_Look, HERETIC_S_MNTR_LOOK2, 0,
     0}, // HERETIC_S_MNTR_LOOK1
    {HERETIC_SPR_MNTR, 1, 10, A_Look, HERETIC_S_MNTR_LOOK1, 0,
     0}, // HERETIC_S_MNTR_LOOK2
    {HERETIC_SPR_MNTR, 0, 5, A_Chase, HERETIC_S_MNTR_WALK2, 0,
     0}, // HERETIC_S_MNTR_WALK1
    {HERETIC_SPR_MNTR, 1, 5, A_Chase, HERETIC_S_MNTR_WALK3, 0,
     0}, // HERETIC_S_MNTR_WALK2
    {HERETIC_SPR_MNTR, 2, 5, A_Chase, HERETIC_S_MNTR_WALK4, 0,
     0}, // HERETIC_S_MNTR_WALK3
    {HERETIC_SPR_MNTR, 3, 5, A_Chase, HERETIC_S_MNTR_WALK1, 0,
     0}, // HERETIC_S_MNTR_WALK4
    {HERETIC_SPR_MNTR, 21, 10, A_FaceTarget, HERETIC_S_MNTR_ATK1_2, 0,
     0}, // HERETIC_S_MNTR_ATK1_1
    {HERETIC_SPR_MNTR, 22, 7, A_FaceTarget, HERETIC_S_MNTR_ATK1_3, 0,
     0}, // HERETIC_S_MNTR_ATK1_2
    {HERETIC_SPR_MNTR, 23, 12, A_MinotaurAtk1, HERETIC_S_MNTR_WALK1, 0,
     0}, // HERETIC_S_MNTR_ATK1_3
    {HERETIC_SPR_MNTR, 21, 10, A_MinotaurDecide, HERETIC_S_MNTR_ATK2_2, 0,
     0}, // HERETIC_S_MNTR_ATK2_1
    {HERETIC_SPR_MNTR, 24, 4, A_FaceTarget, HERETIC_S_MNTR_ATK2_3, 0,
     0}, // HERETIC_S_MNTR_ATK2_2
    {HERETIC_SPR_MNTR, 25, 9, A_MinotaurAtk2, HERETIC_S_MNTR_WALK1, 0,
     0}, // HERETIC_S_MNTR_ATK2_3
    {HERETIC_SPR_MNTR, 21, 10, A_FaceTarget, HERETIC_S_MNTR_ATK3_2, 0,
     0}, // HERETIC_S_MNTR_ATK3_1
    {HERETIC_SPR_MNTR, 22, 7, A_FaceTarget, HERETIC_S_MNTR_ATK3_3, 0,
     0}, // HERETIC_S_MNTR_ATK3_2
    {HERETIC_SPR_MNTR, 23, 12, A_MinotaurAtk3, HERETIC_S_MNTR_WALK1, 0,
     0}, // HERETIC_S_MNTR_ATK3_3
    {HERETIC_SPR_MNTR,
     23,
     12,
     {},
     HERETIC_S_MNTR_ATK3_1,
     0,
     0}, // HERETIC_S_MNTR_ATK3_4
    {HERETIC_SPR_MNTR, 20, 2, A_MinotaurCharge, HERETIC_S_MNTR_ATK4_1, 0,
     0}, // HERETIC_S_MNTR_ATK4_1
    {HERETIC_SPR_MNTR,
     4,
     3,
     {},
     HERETIC_S_MNTR_PAIN2,
     0,
     0}, // HERETIC_S_MNTR_PAIN1
    {HERETIC_SPR_MNTR, 4, 6, A_Pain, HERETIC_S_MNTR_WALK1, 0,
     0}, // HERETIC_S_MNTR_PAIN2
    {HERETIC_SPR_MNTR,
     5,
     6,
     {},
     HERETIC_S_MNTR_DIE2,
     0,
     0}, // HERETIC_S_MNTR_DIE1
    {HERETIC_SPR_MNTR,
     6,
     5,
     {},
     HERETIC_S_MNTR_DIE3,
     0,
     0}, // HERETIC_S_MNTR_DIE2
    {HERETIC_SPR_MNTR, 7, 6, A_Scream, HERETIC_S_MNTR_DIE4, 0,
     0}, // HERETIC_S_MNTR_DIE3
    {HERETIC_SPR_MNTR,
     8,
     5,
     {},
     HERETIC_S_MNTR_DIE5,
     0,
     0}, // HERETIC_S_MNTR_DIE4
    {HERETIC_SPR_MNTR,
     9,
     6,
     {},
     HERETIC_S_MNTR_DIE6,
     0,
     0}, // HERETIC_S_MNTR_DIE5
    {HERETIC_SPR_MNTR,
     10,
     5,
     {},
     HERETIC_S_MNTR_DIE7,
     0,
     0}, // HERETIC_S_MNTR_DIE6
    {HERETIC_SPR_MNTR,
     11,
     6,
     {},
     HERETIC_S_MNTR_DIE8,
     0,
     0}, // HERETIC_S_MNTR_DIE7
    {HERETIC_SPR_MNTR, 12, 5, A_NoBlocking, HERETIC_S_MNTR_DIE9, 0,
     0}, // HERETIC_S_MNTR_DIE8
    {HERETIC_SPR_MNTR,
     13,
     6,
     {},
     HERETIC_S_MNTR_DIE10,
     0,
     0}, // HERETIC_S_MNTR_DIE9
    {HERETIC_SPR_MNTR,
     14,
     5,
     {},
     HERETIC_S_MNTR_DIE11,
     0,
     0}, // HERETIC_S_MNTR_DIE10
    {HERETIC_SPR_MNTR,
     15,
     6,
     {},
     HERETIC_S_MNTR_DIE12,
     0,
     0}, // HERETIC_S_MNTR_DIE11
    {HERETIC_SPR_MNTR,
     16,
     5,
     {},
     HERETIC_S_MNTR_DIE13,
     0,
     0}, // HERETIC_S_MNTR_DIE12
    {HERETIC_SPR_MNTR,
     17,
     6,
     {},
     HERETIC_S_MNTR_DIE14,
     0,
     0}, // HERETIC_S_MNTR_DIE13
    {HERETIC_SPR_MNTR,
     18,
     5,
     {},
     HERETIC_S_MNTR_DIE15,
     0,
     0}, // HERETIC_S_MNTR_DIE14
    {HERETIC_SPR_MNTR, 19, -1, A_BossDeath, HERETIC_S_NULL, 0,
     0}, // HERETIC_S_MNTR_DIE15
    {HERETIC_SPR_FX12,
     32768,
     6,
     {},
     HERETIC_S_MNTRFX1_2,
     0,
     0}, // HERETIC_S_MNTRFX1_1
    {HERETIC_SPR_FX12,
     32769,
     6,
     {},
     HERETIC_S_MNTRFX1_1,
     0,
     0}, // HERETIC_S_MNTRFX1_2
    {HERETIC_SPR_FX12,
     32770,
     5,
     {},
     HERETIC_S_MNTRFXI1_2,
     0,
     0}, // HERETIC_S_MNTRFXI1_1
    {HERETIC_SPR_FX12,
     32771,
     5,
     {},
     HERETIC_S_MNTRFXI1_3,
     0,
     0}, // HERETIC_S_MNTRFXI1_2
    {HERETIC_SPR_FX12,
     32772,
     5,
     {},
     HERETIC_S_MNTRFXI1_4,
     0,
     0}, // HERETIC_S_MNTRFXI1_3
    {HERETIC_SPR_FX12,
     32773,
     5,
     {},
     HERETIC_S_MNTRFXI1_5,
     0,
     0}, // HERETIC_S_MNTRFXI1_4
    {HERETIC_SPR_FX12,
     32774,
     5,
     {},
     HERETIC_S_MNTRFXI1_6,
     0,
     0}, // HERETIC_S_MNTRFXI1_5
    {HERETIC_SPR_FX12,
     32775,
     5,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MNTRFXI1_6
    {HERETIC_SPR_FX13, 0, 2, A_MntrFloorFire, HERETIC_S_MNTRFX2_1, 0,
     0}, // HERETIC_S_MNTRFX2_1
    {HERETIC_SPR_FX13, 32776, 4, A_Explode, HERETIC_S_MNTRFXI2_2, 0,
     0}, // HERETIC_S_MNTRFXI2_1
    {HERETIC_SPR_FX13,
     32777,
     4,
     {},
     HERETIC_S_MNTRFXI2_3,
     0,
     0}, // HERETIC_S_MNTRFXI2_2
    {HERETIC_SPR_FX13,
     32778,
     4,
     {},
     HERETIC_S_MNTRFXI2_4,
     0,
     0}, // HERETIC_S_MNTRFXI2_3
    {HERETIC_SPR_FX13,
     32779,
     4,
     {},
     HERETIC_S_MNTRFXI2_5,
     0,
     0}, // HERETIC_S_MNTRFXI2_4
    {HERETIC_SPR_FX13,
     32780,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MNTRFXI2_5
    {HERETIC_SPR_FX13,
     32771,
     4,
     {},
     HERETIC_S_MNTRFX3_2,
     0,
     0}, // HERETIC_S_MNTRFX3_1
    {HERETIC_SPR_FX13,
     32770,
     4,
     {},
     HERETIC_S_MNTRFX3_3,
     0,
     0}, // HERETIC_S_MNTRFX3_2
    {HERETIC_SPR_FX13,
     32769,
     5,
     {},
     HERETIC_S_MNTRFX3_4,
     0,
     0}, // HERETIC_S_MNTRFX3_3
    {HERETIC_SPR_FX13,
     32770,
     5,
     {},
     HERETIC_S_MNTRFX3_5,
     0,
     0}, // HERETIC_S_MNTRFX3_4
    {HERETIC_SPR_FX13,
     32771,
     5,
     {},
     HERETIC_S_MNTRFX3_6,
     0,
     0}, // HERETIC_S_MNTRFX3_5
    {HERETIC_SPR_FX13,
     32772,
     5,
     {},
     HERETIC_S_MNTRFX3_7,
     0,
     0}, // HERETIC_S_MNTRFX3_6
    {HERETIC_SPR_FX13,
     32773,
     4,
     {},
     HERETIC_S_MNTRFX3_8,
     0,
     0}, // HERETIC_S_MNTRFX3_7
    {HERETIC_SPR_FX13,
     32774,
     4,
     {},
     HERETIC_S_MNTRFX3_9,
     0,
     0}, // HERETIC_S_MNTRFX3_8
    {HERETIC_SPR_FX13,
     32775,
     4,
     {},
     HERETIC_S_NULL,
     0,
     0}, // HERETIC_S_MNTRFX3_9
    {HERETIC_SPR_AKYY, 32768, 3, {}, HERETIC_S_AKYY2, 0, 0},  // HERETIC_S_AKYY1
    {HERETIC_SPR_AKYY, 32769, 3, {}, HERETIC_S_AKYY3, 0, 0},  // HERETIC_S_AKYY2
    {HERETIC_SPR_AKYY, 32770, 3, {}, HERETIC_S_AKYY4, 0, 0},  // HERETIC_S_AKYY3
    {HERETIC_SPR_AKYY, 32771, 3, {}, HERETIC_S_AKYY5, 0, 0},  // HERETIC_S_AKYY4
    {HERETIC_SPR_AKYY, 32772, 3, {}, HERETIC_S_AKYY6, 0, 0},  // HERETIC_S_AKYY5
    {HERETIC_SPR_AKYY, 32773, 3, {}, HERETIC_S_AKYY7, 0, 0},  // HERETIC_S_AKYY6
    {HERETIC_SPR_AKYY, 32774, 3, {}, HERETIC_S_AKYY8, 0, 0},  // HERETIC_S_AKYY7
    {HERETIC_SPR_AKYY, 32775, 3, {}, HERETIC_S_AKYY9, 0, 0},  // HERETIC_S_AKYY8
    {HERETIC_SPR_AKYY, 32776, 3, {}, HERETIC_S_AKYY10, 0, 0}, // HERETIC_S_AKYY9
    {HERETIC_SPR_AKYY, 32777, 3, {}, HERETIC_S_AKYY1, 0, 0}, // HERETIC_S_AKYY10
    {HERETIC_SPR_BKYY, 32768, 3, {}, HERETIC_S_BKYY2, 0, 0}, // HERETIC_S_BKYY1
    {HERETIC_SPR_BKYY, 32769, 3, {}, HERETIC_S_BKYY3, 0, 0}, // HERETIC_S_BKYY2
    {HERETIC_SPR_BKYY, 32770, 3, {}, HERETIC_S_BKYY4, 0, 0}, // HERETIC_S_BKYY3
    {HERETIC_SPR_BKYY, 32771, 3, {}, HERETIC_S_BKYY5, 0, 0}, // HERETIC_S_BKYY4
    {HERETIC_SPR_BKYY, 32772, 3, {}, HERETIC_S_BKYY6, 0, 0}, // HERETIC_S_BKYY5
    {HERETIC_SPR_BKYY, 32773, 3, {}, HERETIC_S_BKYY7, 0, 0}, // HERETIC_S_BKYY6
    {HERETIC_SPR_BKYY, 32774, 3, {}, HERETIC_S_BKYY8, 0, 0}, // HERETIC_S_BKYY7
    {HERETIC_SPR_BKYY, 32775, 3, {}, HERETIC_S_BKYY9, 0, 0}, // HERETIC_S_BKYY8
    {HERETIC_SPR_BKYY, 32776, 3, {}, HERETIC_S_BKYY10, 0, 0}, // HERETIC_S_BKYY9
    {HERETIC_SPR_BKYY, 32777, 3, {}, HERETIC_S_BKYY1, 0, 0}, // HERETIC_S_BKYY10
    {HERETIC_SPR_CKYY, 32768, 3, {}, HERETIC_S_CKYY2, 0, 0}, // HERETIC_S_CKYY1
    {HERETIC_SPR_CKYY, 32769, 3, {}, HERETIC_S_CKYY3, 0, 0}, // HERETIC_S_CKYY2
    {HERETIC_SPR_CKYY, 32770, 3, {}, HERETIC_S_CKYY4, 0, 0}, // HERETIC_S_CKYY3
    {HERETIC_SPR_CKYY, 32771, 3, {}, HERETIC_S_CKYY5, 0, 0}, // HERETIC_S_CKYY4
    {HERETIC_SPR_CKYY, 32772, 3, {}, HERETIC_S_CKYY6, 0, 0}, // HERETIC_S_CKYY5
    {HERETIC_SPR_CKYY, 32773, 3, {}, HERETIC_S_CKYY7, 0, 0}, // HERETIC_S_CKYY6
    {HERETIC_SPR_CKYY, 32774, 3, {}, HERETIC_S_CKYY8, 0, 0}, // HERETIC_S_CKYY7
    {HERETIC_SPR_CKYY, 32775, 3, {}, HERETIC_S_CKYY9, 0, 0}, // HERETIC_S_CKYY8
    {HERETIC_SPR_CKYY, 32776, 3, {}, HERETIC_S_CKYY1, 0, 0}, // HERETIC_S_CKYY9
    {HERETIC_SPR_AMG1, 0, -1, {}, HERETIC_S_NULL, 0, 0},     // HERETIC_S_AMG1
    {HERETIC_SPR_AMG2, 0, 4, {}, HERETIC_S_AMG2_2, 0, 0},    // HERETIC_S_AMG2_1
    {HERETIC_SPR_AMG2, 1, 4, {}, HERETIC_S_AMG2_3, 0, 0},    // HERETIC_S_AMG2_2
    {HERETIC_SPR_AMG2, 2, 4, {}, HERETIC_S_AMG2_1, 0, 0},    // HERETIC_S_AMG2_3
    {HERETIC_SPR_AMM1, 0, -1, {}, HERETIC_S_NULL, 0, 0},     // HERETIC_S_AMM1
    {HERETIC_SPR_AMM2, 0, -1, {}, HERETIC_S_NULL, 0, 0},     // HERETIC_S_AMM2
    {HERETIC_SPR_AMC1, 0, -1, {}, HERETIC_S_NULL, 0, 0},     // HERETIC_S_AMC1
    {HERETIC_SPR_AMC2, 0, 5, {}, HERETIC_S_AMC2_2, 0, 0},    // HERETIC_S_AMC2_1
    {HERETIC_SPR_AMC2, 1, 5, {}, HERETIC_S_AMC2_3, 0, 0},    // HERETIC_S_AMC2_2
    {HERETIC_SPR_AMC2, 2, 5, {}, HERETIC_S_AMC2_1, 0, 0},    // HERETIC_S_AMC2_3
    {HERETIC_SPR_AMS1, 0, 5, {}, HERETIC_S_AMS1_2, 0, 0},    // HERETIC_S_AMS1_1
    {HERETIC_SPR_AMS1, 1, 5, {}, HERETIC_S_AMS1_1, 0, 0},    // HERETIC_S_AMS1_2
    {HERETIC_SPR_AMS2, 0, 5, {}, HERETIC_S_AMS2_2, 0, 0},    // HERETIC_S_AMS2_1
    {HERETIC_SPR_AMS2, 1, 5, {}, HERETIC_S_AMS2_1, 0, 0},    // HERETIC_S_AMS2_2
    {HERETIC_SPR_AMP1, 0, 4, {}, HERETIC_S_AMP1_2, 0, 0},    // HERETIC_S_AMP1_1
    {HERETIC_SPR_AMP1, 1, 4, {}, HERETIC_S_AMP1_3, 0, 0},    // HERETIC_S_AMP1_2
    {HERETIC_SPR_AMP1, 2, 4, {}, HERETIC_S_AMP1_1, 0, 0},    // HERETIC_S_AMP1_3
    {HERETIC_SPR_AMP2, 0, 4, {}, HERETIC_S_AMP2_2, 0, 0},    // HERETIC_S_AMP2_1
    {HERETIC_SPR_AMP2, 1, 4, {}, HERETIC_S_AMP2_3, 0, 0},    // HERETIC_S_AMP2_2
    {HERETIC_SPR_AMP2, 2, 4, {}, HERETIC_S_AMP2_1, 0, 0},    // HERETIC_S_AMP2_3
    {HERETIC_SPR_AMB1, 0, 4, {}, HERETIC_S_AMB1_2, 0, 0},    // HERETIC_S_AMB1_1
    {HERETIC_SPR_AMB1, 1, 4, {}, HERETIC_S_AMB1_3, 0, 0},    // HERETIC_S_AMB1_2
    {HERETIC_SPR_AMB1, 2, 4, {}, HERETIC_S_AMB1_1, 0, 0},    // HERETIC_S_AMB1_3
    {HERETIC_SPR_AMB2, 0, 4, {}, HERETIC_S_AMB2_2, 0, 0},    // HERETIC_S_AMB2_1
    {HERETIC_SPR_AMB2, 1, 4, {}, HERETIC_S_AMB2_3, 0, 0},    // HERETIC_S_AMB2_2
    {HERETIC_SPR_AMB2, 2, 4, {}, HERETIC_S_AMB2_1, 0, 0},    // HERETIC_S_AMB2_3
    {HERETIC_SPR_AMG1, 0, 100, A_ESound, HERETIC_S_SND_WIND, 0,
     0}, // HERETIC_S_SND_WIND
    {HERETIC_SPR_AMG1, 0, 85, A_ESound, HERETIC_S_SND_WATERFALL, 0,
     0} // HERETIC_S_SND_WATERFALL
};

heretic_mobjinfo_t heretic_mobjinfo[HERETIC_NUMMOBJTYPES] = {

    {
        // MT_MISC0
        81,                    // doomednum
        HERETIC_S_ITEM_PTN1_1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_SPECIAL,            // flags
        MF2_FLOATBOB           // flags2
    },

    {
        // MT_ITEMSHIELD1
        85,                   // doomednum
        HERETIC_S_ITEM_SHLD1, // spawnstate
        1000,                 // spawnhealth
        HERETIC_S_NULL,       // seestate
        heretic_sfx_None,     // seesound
        8,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_NULL,       // painstate
        0,                    // painchance
        heretic_sfx_None,     // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_NULL,       // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_NULL,       // deathstate
        HERETIC_S_NULL,       // xdeathstate
        heretic_sfx_None,     // deathsound
        0,                    // speed
        20 * FRACUNIT,        // radius
        16 * FRACUNIT,        // height
        100,                  // mass
        0,                    // damage
        heretic_sfx_None,     // activesound
        MF_SPECIAL,           // flags
        MF2_FLOATBOB          // flags2
    },

    {
        // MT_ITEMSHIELD2
        31,                    // doomednum
        HERETIC_S_ITEM_SHD2_1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_SPECIAL,            // flags
        MF2_FLOATBOB           // flags2
    },

    {
        // MT_MISC1
        8,                         // doomednum
        HERETIC_S_ITEM_BAGH1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_MISC2
        35,                        // doomednum
        HERETIC_S_ITEM_SPMP1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_ARTIINVISIBILITY
        75,                                    // doomednum
        HERETIC_S_ARTI_INVS1,                  // spawnstate
        1000,                                  // spawnhealth
        HERETIC_S_NULL,                        // seestate
        heretic_sfx_None,                      // seesound
        8,                                     // reactiontime
        heretic_sfx_None,                      // attacksound
        HERETIC_S_NULL,                        // painstate
        0,                                     // painchance
        heretic_sfx_None,                      // painsound
        HERETIC_S_NULL,                        // meleestate
        HERETIC_S_NULL,                        // missilestate
        HERETIC_S_NULL,                        // crashstate
        HERETIC_S_NULL,                        // deathstate
        HERETIC_S_NULL,                        // xdeathstate
        heretic_sfx_None,                      // deathsound
        0,                                     // speed
        20 * FRACUNIT,                         // radius
        16 * FRACUNIT,                         // height
        100,                                   // mass
        0,                                     // damage
        heretic_sfx_None,                      // activesound
        MF_SPECIAL | MF_SHADOW | MF_COUNTITEM, // flags
        MF2_FLOATBOB                           // flags2
    },

    {
        // MT_MISC3
        82,                        // doomednum
        HERETIC_S_ARTI_PTN2_1,     // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_ARTIFLY
        83,                        // doomednum
        HERETIC_S_ARTI_SOAR1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_ARTIINVULNERABILITY
        84,                        // doomednum
        HERETIC_S_ARTI_INVU1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_ARTITOMEOFPOWER
        86,                        // doomednum
        HERETIC_S_ARTI_PWBK1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_ARTIEGG
        30,                        // doomednum
        HERETIC_S_ARTI_EGGC1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_EGGFX
        -1,                                                     // doomednum
        HERETIC_S_EGGFX1,                                       // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_EGGFXI1_1,                                    // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        18 * FRACUNIT,                                          // speed
        8 * FRACUNIT,                                           // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_ARTISUPERHEAL
        32,                        // doomednum
        HERETIC_S_ARTI_SPHL1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_MISC4
        33,                        // doomednum
        HERETIC_S_ARTI_TRCH1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_MISC5
        34,                        // doomednum
        HERETIC_S_ARTI_FBMB1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_FIREBOMB
        -1,                       // doomednum
        HERETIC_S_FIREBOMB1,      // spawnstate
        1000,                     // spawnhealth
        HERETIC_S_NULL,           // seestate
        heretic_sfx_None,         // seesound
        8,                        // reactiontime
        heretic_sfx_None,         // attacksound
        HERETIC_S_NULL,           // painstate
        0,                        // painchance
        heretic_sfx_None,         // painsound
        HERETIC_S_NULL,           // meleestate
        HERETIC_S_NULL,           // missilestate
        HERETIC_S_NULL,           // crashstate
        HERETIC_S_NULL,           // deathstate
        HERETIC_S_NULL,           // xdeathstate
        heretic_sfx_phohit,       // deathsound
        0,                        // speed
        20 * FRACUNIT,            // radius
        16 * FRACUNIT,            // height
        100,                      // mass
        0,                        // damage
        heretic_sfx_None,         // activesound
        MF_NOGRAVITY | MF_SHADOW, // flags
        0                         // flags2
    },

    {
        // MT_ARTITELEPORT
        36,                        // doomednum
        HERETIC_S_ARTI_ATLP1,      // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_COUNTITEM, // flags
        MF2_FLOATBOB               // flags2
    },

    {
        // MT_POD
        2035,                                              // doomednum
        HERETIC_S_POD_WAIT1,                               // spawnstate
        45,                                                // spawnhealth
        HERETIC_S_NULL,                                    // seestate
        heretic_sfx_None,                                  // seesound
        8,                                                 // reactiontime
        heretic_sfx_None,                                  // attacksound
        HERETIC_S_POD_PAIN1,                               // painstate
        255,                                               // painchance
        heretic_sfx_None,                                  // painsound
        HERETIC_S_NULL,                                    // meleestate
        HERETIC_S_NULL,                                    // missilestate
        HERETIC_S_NULL,                                    // crashstate
        HERETIC_S_POD_DIE1,                                // deathstate
        HERETIC_S_NULL,                                    // xdeathstate
        heretic_sfx_podexp,                                // deathsound
        0,                                                 // speed
        16 * FRACUNIT,                                     // radius
        54 * FRACUNIT,                                     // height
        100,                                               // mass
        0,                                                 // damage
        heretic_sfx_None,                                  // activesound
        MF_SOLID | MF_NOBLOOD | MF_SHOOTABLE | MF_DROPOFF, // flags
        MF2_WINDTHRUST | MF2_PUSHABLE | MF2_SLIDE | MF2_PASSMOBJ |
            MF2_TELESTOMP // flags2
    },

    {
        // MT_PODGOO
        -1,                                          // doomednum
        HERETIC_S_PODGOO1,                           // spawnstate
        1000,                                        // spawnhealth
        HERETIC_S_NULL,                              // seestate
        heretic_sfx_None,                            // seesound
        8,                                           // reactiontime
        heretic_sfx_None,                            // attacksound
        HERETIC_S_NULL,                              // painstate
        0,                                           // painchance
        heretic_sfx_None,                            // painsound
        HERETIC_S_NULL,                              // meleestate
        HERETIC_S_NULL,                              // missilestate
        HERETIC_S_NULL,                              // crashstate
        HERETIC_S_PODGOOX,                           // deathstate
        HERETIC_S_NULL,                              // xdeathstate
        heretic_sfx_None,                            // deathsound
        0,                                           // speed
        2 * FRACUNIT,                                // radius
        4 * FRACUNIT,                                // height
        100,                                         // mass
        0,                                           // damage
        heretic_sfx_None,                            // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF,     // flags
        MF2_NOTELEPORT | MF2_LOGRAV | MF2_CANNOTPUSH // flags2
    },

    {
        // MT_PODGENERATOR
        43,                          // doomednum
        HERETIC_S_PODGENERATOR,      // spawnstate
        1000,                        // spawnhealth
        HERETIC_S_NULL,              // seestate
        heretic_sfx_None,            // seesound
        8,                           // reactiontime
        heretic_sfx_None,            // attacksound
        HERETIC_S_NULL,              // painstate
        0,                           // painchance
        heretic_sfx_None,            // painsound
        HERETIC_S_NULL,              // meleestate
        HERETIC_S_NULL,              // missilestate
        HERETIC_S_NULL,              // crashstate
        HERETIC_S_NULL,              // deathstate
        HERETIC_S_NULL,              // xdeathstate
        heretic_sfx_None,            // deathsound
        0,                           // speed
        20 * FRACUNIT,               // radius
        16 * FRACUNIT,               // height
        100,                         // mass
        0,                           // damage
        heretic_sfx_None,            // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        0                            // flags2
    },

    {
        // MT_SPLASH
        -1,                                          // doomednum
        HERETIC_S_SPLASH1,                           // spawnstate
        1000,                                        // spawnhealth
        HERETIC_S_NULL,                              // seestate
        heretic_sfx_None,                            // seesound
        8,                                           // reactiontime
        heretic_sfx_None,                            // attacksound
        HERETIC_S_NULL,                              // painstate
        0,                                           // painchance
        heretic_sfx_None,                            // painsound
        HERETIC_S_NULL,                              // meleestate
        HERETIC_S_NULL,                              // missilestate
        HERETIC_S_NULL,                              // crashstate
        HERETIC_S_SPLASHX,                           // deathstate
        HERETIC_S_NULL,                              // xdeathstate
        heretic_sfx_None,                            // deathsound
        0,                                           // speed
        2 * FRACUNIT,                                // radius
        4 * FRACUNIT,                                // height
        100,                                         // mass
        0,                                           // damage
        heretic_sfx_None,                            // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF,     // flags
        MF2_NOTELEPORT | MF2_LOGRAV | MF2_CANNOTPUSH // flags2
    },

    {
        // MT_SPLASHBASE
        -1,                    // doomednum
        HERETIC_S_SPLASHBASE1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_NOBLOCKMAP,         // flags
        0                      // flags2
    },

    {
        // MT_LAVASPLASH
        -1,                    // doomednum
        HERETIC_S_LAVASPLASH1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_NOBLOCKMAP,         // flags
        0                      // flags2
    },

    {
        // MT_LAVASMOKE
        -1,                                       // doomednum
        HERETIC_S_LAVASMOKE1,                     // spawnstate
        1000,                                     // spawnhealth
        HERETIC_S_NULL,                           // seestate
        heretic_sfx_None,                         // seesound
        8,                                        // reactiontime
        heretic_sfx_None,                         // attacksound
        HERETIC_S_NULL,                           // painstate
        0,                                        // painchance
        heretic_sfx_None,                         // painsound
        HERETIC_S_NULL,                           // meleestate
        HERETIC_S_NULL,                           // missilestate
        HERETIC_S_NULL,                           // crashstate
        HERETIC_S_NULL,                           // deathstate
        HERETIC_S_NULL,                           // xdeathstate
        heretic_sfx_None,                         // deathsound
        0,                                        // speed
        20 * FRACUNIT,                            // radius
        16 * FRACUNIT,                            // height
        100,                                      // mass
        0,                                        // damage
        heretic_sfx_None,                         // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_SHADOW, // flags
        0                                         // flags2
    },

    {
        // MT_SLUDGECHUNK
        -1,                                          // doomednum
        HERETIC_S_SLUDGECHUNK1,                      // spawnstate
        1000,                                        // spawnhealth
        HERETIC_S_NULL,                              // seestate
        heretic_sfx_None,                            // seesound
        8,                                           // reactiontime
        heretic_sfx_None,                            // attacksound
        HERETIC_S_NULL,                              // painstate
        0,                                           // painchance
        heretic_sfx_None,                            // painsound
        HERETIC_S_NULL,                              // meleestate
        HERETIC_S_NULL,                              // missilestate
        HERETIC_S_NULL,                              // crashstate
        HERETIC_S_SLUDGECHUNKX,                      // deathstate
        HERETIC_S_NULL,                              // xdeathstate
        heretic_sfx_None,                            // deathsound
        0,                                           // speed
        2 * FRACUNIT,                                // radius
        4 * FRACUNIT,                                // height
        100,                                         // mass
        0,                                           // damage
        heretic_sfx_None,                            // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF,     // flags
        MF2_NOTELEPORT | MF2_LOGRAV | MF2_CANNOTPUSH // flags2
    },

    {
        // MT_SLUDGESPLASH
        -1,                      // doomednum
        HERETIC_S_SLUDGESPLASH1, // spawnstate
        1000,                    // spawnhealth
        HERETIC_S_NULL,          // seestate
        heretic_sfx_None,        // seesound
        8,                       // reactiontime
        heretic_sfx_None,        // attacksound
        HERETIC_S_NULL,          // painstate
        0,                       // painchance
        heretic_sfx_None,        // painsound
        HERETIC_S_NULL,          // meleestate
        HERETIC_S_NULL,          // missilestate
        HERETIC_S_NULL,          // crashstate
        HERETIC_S_NULL,          // deathstate
        HERETIC_S_NULL,          // xdeathstate
        heretic_sfx_None,        // deathsound
        0,                       // speed
        20 * FRACUNIT,           // radius
        16 * FRACUNIT,           // height
        100,                     // mass
        0,                       // damage
        heretic_sfx_None,        // activesound
        MF_NOBLOCKMAP,           // flags
        0                        // flags2
    },

    {
        // MT_SKULLHANG70
        17,                             // doomednum
        HERETIC_S_SKULLHANG70_1,        // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        70 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_SKULLHANG60
        24,                             // doomednum
        HERETIC_S_SKULLHANG60_1,        // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        60 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_SKULLHANG45
        25,                             // doomednum
        HERETIC_S_SKULLHANG45_1,        // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        45 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_SKULLHANG35
        26,                             // doomednum
        HERETIC_S_SKULLHANG35_1,        // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        35 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_CHANDELIER
        28,                             // doomednum
        HERETIC_S_CHANDELIER1,          // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        60 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_SERPTORCH
        27,                   // doomednum
        HERETIC_S_SERPTORCH1, // spawnstate
        1000,                 // spawnhealth
        HERETIC_S_NULL,       // seestate
        heretic_sfx_None,     // seesound
        8,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_NULL,       // painstate
        0,                    // painchance
        heretic_sfx_None,     // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_NULL,       // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_NULL,       // deathstate
        HERETIC_S_NULL,       // xdeathstate
        heretic_sfx_None,     // deathsound
        0,                    // speed
        12 * FRACUNIT,        // radius
        54 * FRACUNIT,        // height
        100,                  // mass
        0,                    // damage
        heretic_sfx_None,     // activesound
        MF_SOLID,             // flags
        0                     // flags2
    },

    {
        // MT_SMALLPILLAR
        29,                    // doomednum
        HERETIC_S_SMALLPILLAR, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        16 * FRACUNIT,         // radius
        34 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_SOLID,              // flags
        0                      // flags2
    },

    {
        // MT_STALAGMITESMALL
        37,                        // doomednum
        HERETIC_S_STALAGMITESMALL, // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        8 * FRACUNIT,              // radius
        32 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SOLID,                  // flags
        0                          // flags2
    },

    {
        // MT_STALAGMITELARGE
        38,                        // doomednum
        HERETIC_S_STALAGMITELARGE, // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        12 * FRACUNIT,             // radius
        64 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SOLID,                  // flags
        0                          // flags2
    },

    {
        // MT_STALACTITESMALL
        39,                                        // doomednum
        HERETIC_S_STALACTITESMALL,                 // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        heretic_sfx_None,                          // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_NULL,                            // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        heretic_sfx_None,                          // deathsound
        0,                                         // speed
        8 * FRACUNIT,                              // radius
        36 * FRACUNIT,                             // height
        100,                                       // mass
        0,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                                          // flags2
    },

    {
        // MT_STALACTITELARGE
        40,                                        // doomednum
        HERETIC_S_STALACTITELARGE,                 // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        heretic_sfx_None,                          // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_NULL,                            // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        heretic_sfx_None,                          // deathsound
        0,                                         // speed
        12 * FRACUNIT,                             // radius
        68 * FRACUNIT,                             // height
        100,                                       // mass
        0,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                                          // flags2
    },

    {
        // MT_MISC6
        76,                     // doomednum
        HERETIC_S_FIREBRAZIER1, // spawnstate
        1000,                   // spawnhealth
        HERETIC_S_NULL,         // seestate
        heretic_sfx_None,       // seesound
        8,                      // reactiontime
        heretic_sfx_None,       // attacksound
        HERETIC_S_NULL,         // painstate
        0,                      // painchance
        heretic_sfx_None,       // painsound
        HERETIC_S_NULL,         // meleestate
        HERETIC_S_NULL,         // missilestate
        HERETIC_S_NULL,         // crashstate
        HERETIC_S_NULL,         // deathstate
        HERETIC_S_NULL,         // xdeathstate
        heretic_sfx_None,       // deathsound
        0,                      // speed
        16 * FRACUNIT,          // radius
        44 * FRACUNIT,          // height
        100,                    // mass
        0,                      // damage
        heretic_sfx_None,       // activesound
        MF_SOLID,               // flags
        0                       // flags2
    },

    {
        // MT_BARREL
        44,               // doomednum
        HERETIC_S_BARREL, // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        12 * FRACUNIT,    // radius
        32 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SOLID,         // flags
        0                 // flags2
    },

    {
        // MT_MISC7
        47,                 // doomednum
        HERETIC_S_BRPILLAR, // spawnstate
        1000,               // spawnhealth
        HERETIC_S_NULL,     // seestate
        heretic_sfx_None,   // seesound
        8,                  // reactiontime
        heretic_sfx_None,   // attacksound
        HERETIC_S_NULL,     // painstate
        0,                  // painchance
        heretic_sfx_None,   // painsound
        HERETIC_S_NULL,     // meleestate
        HERETIC_S_NULL,     // missilestate
        HERETIC_S_NULL,     // crashstate
        HERETIC_S_NULL,     // deathstate
        HERETIC_S_NULL,     // xdeathstate
        heretic_sfx_None,   // deathsound
        0,                  // speed
        14 * FRACUNIT,      // radius
        128 * FRACUNIT,     // height
        100,                // mass
        0,                  // damage
        heretic_sfx_None,   // activesound
        MF_SOLID,           // flags
        0                   // flags2
    },

    {
        // MT_MISC8
        48,                             // doomednum
        HERETIC_S_MOSS1,                // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        23 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_MISC9
        49,                             // doomednum
        HERETIC_S_MOSS2,                // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        27 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                               // flags2
    },

    {
        // MT_MISC10
        50,                   // doomednum
        HERETIC_S_WALLTORCH1, // spawnstate
        1000,                 // spawnhealth
        HERETIC_S_NULL,       // seestate
        heretic_sfx_None,     // seesound
        8,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_NULL,       // painstate
        0,                    // painchance
        heretic_sfx_None,     // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_NULL,       // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_NULL,       // deathstate
        HERETIC_S_NULL,       // xdeathstate
        heretic_sfx_None,     // deathsound
        0,                    // speed
        20 * FRACUNIT,        // radius
        16 * FRACUNIT,        // height
        100,                  // mass
        0,                    // damage
        heretic_sfx_None,     // activesound
        MF_NOGRAVITY,         // flags
        0                     // flags2
    },

    {
        // MT_MISC11
        51,                                        // doomednum
        HERETIC_S_HANGINGCORPSE,                   // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        heretic_sfx_None,                          // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_NULL,                            // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        heretic_sfx_None,                          // deathsound
        0,                                         // speed
        8 * FRACUNIT,                              // radius
        104 * FRACUNIT,                            // height
        100,                                       // mass
        0,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY, // flags
        0                                          // flags2
    },

    {
        // MT_KEYGIZMOBLUE
        94,                  // doomednum
        HERETIC_S_KEYGIZMO1, // spawnstate
        1000,                // spawnhealth
        HERETIC_S_NULL,      // seestate
        heretic_sfx_None,    // seesound
        8,                   // reactiontime
        heretic_sfx_None,    // attacksound
        HERETIC_S_NULL,      // painstate
        0,                   // painchance
        heretic_sfx_None,    // painsound
        HERETIC_S_NULL,      // meleestate
        HERETIC_S_NULL,      // missilestate
        HERETIC_S_NULL,      // crashstate
        HERETIC_S_NULL,      // deathstate
        HERETIC_S_NULL,      // xdeathstate
        heretic_sfx_None,    // deathsound
        0,                   // speed
        16 * FRACUNIT,       // radius
        50 * FRACUNIT,       // height
        100,                 // mass
        0,                   // damage
        heretic_sfx_None,    // activesound
        MF_SOLID,            // flags
        0                    // flags2
    },

    {
        // MT_KEYGIZMOGREEN
        95,                  // doomednum
        HERETIC_S_KEYGIZMO1, // spawnstate
        1000,                // spawnhealth
        HERETIC_S_NULL,      // seestate
        heretic_sfx_None,    // seesound
        8,                   // reactiontime
        heretic_sfx_None,    // attacksound
        HERETIC_S_NULL,      // painstate
        0,                   // painchance
        heretic_sfx_None,    // painsound
        HERETIC_S_NULL,      // meleestate
        HERETIC_S_NULL,      // missilestate
        HERETIC_S_NULL,      // crashstate
        HERETIC_S_NULL,      // deathstate
        HERETIC_S_NULL,      // xdeathstate
        heretic_sfx_None,    // deathsound
        0,                   // speed
        16 * FRACUNIT,       // radius
        50 * FRACUNIT,       // height
        100,                 // mass
        0,                   // damage
        heretic_sfx_None,    // activesound
        MF_SOLID,            // flags
        0                    // flags2
    },

    {
        // MT_KEYGIZMOYELLOW
        96,                  // doomednum
        HERETIC_S_KEYGIZMO1, // spawnstate
        1000,                // spawnhealth
        HERETIC_S_NULL,      // seestate
        heretic_sfx_None,    // seesound
        8,                   // reactiontime
        heretic_sfx_None,    // attacksound
        HERETIC_S_NULL,      // painstate
        0,                   // painchance
        heretic_sfx_None,    // painsound
        HERETIC_S_NULL,      // meleestate
        HERETIC_S_NULL,      // missilestate
        HERETIC_S_NULL,      // crashstate
        HERETIC_S_NULL,      // deathstate
        HERETIC_S_NULL,      // xdeathstate
        heretic_sfx_None,    // deathsound
        0,                   // speed
        16 * FRACUNIT,       // radius
        50 * FRACUNIT,       // height
        100,                 // mass
        0,                   // damage
        heretic_sfx_None,    // activesound
        MF_SOLID,            // flags
        0                    // flags2
    },

    {
        // MT_KEYGIZMOFLOAT
        -1,                      // doomednum
        HERETIC_S_KGZ_START,     // spawnstate
        1000,                    // spawnhealth
        HERETIC_S_NULL,          // seestate
        heretic_sfx_None,        // seesound
        8,                       // reactiontime
        heretic_sfx_None,        // attacksound
        HERETIC_S_NULL,          // painstate
        0,                       // painchance
        heretic_sfx_None,        // painsound
        HERETIC_S_NULL,          // meleestate
        HERETIC_S_NULL,          // missilestate
        HERETIC_S_NULL,          // crashstate
        HERETIC_S_NULL,          // deathstate
        HERETIC_S_NULL,          // xdeathstate
        heretic_sfx_None,        // deathsound
        0,                       // speed
        16 * FRACUNIT,           // radius
        16 * FRACUNIT,           // height
        100,                     // mass
        0,                       // damage
        heretic_sfx_None,        // activesound
        MF_SOLID | MF_NOGRAVITY, // flags
        0                        // flags2
    },

    {
        // MT_MISC12
        87,                 // doomednum
        HERETIC_S_VOLCANO1, // spawnstate
        1000,               // spawnhealth
        HERETIC_S_NULL,     // seestate
        heretic_sfx_None,   // seesound
        8,                  // reactiontime
        heretic_sfx_None,   // attacksound
        HERETIC_S_NULL,     // painstate
        0,                  // painchance
        heretic_sfx_None,   // painsound
        HERETIC_S_NULL,     // meleestate
        HERETIC_S_NULL,     // missilestate
        HERETIC_S_NULL,     // crashstate
        HERETIC_S_NULL,     // deathstate
        HERETIC_S_NULL,     // xdeathstate
        heretic_sfx_None,   // deathsound
        0,                  // speed
        12 * FRACUNIT,      // radius
        20 * FRACUNIT,      // height
        100,                // mass
        0,                  // damage
        heretic_sfx_None,   // activesound
        MF_SOLID,           // flags
        0                   // flags2
    },

    {
        // MT_VOLCANOBLAST
        -1,                                          // doomednum
        HERETIC_S_VOLCANOBALL1,                      // spawnstate
        1000,                                        // spawnhealth
        HERETIC_S_NULL,                              // seestate
        heretic_sfx_None,                            // seesound
        8,                                           // reactiontime
        heretic_sfx_None,                            // attacksound
        HERETIC_S_NULL,                              // painstate
        0,                                           // painchance
        heretic_sfx_None,                            // painsound
        HERETIC_S_NULL,                              // meleestate
        HERETIC_S_NULL,                              // missilestate
        HERETIC_S_NULL,                              // crashstate
        HERETIC_S_VOLCANOBALLX1,                     // deathstate
        HERETIC_S_NULL,                              // xdeathstate
        heretic_sfx_volhit,                          // deathsound
        2 * FRACUNIT,                                // speed
        8 * FRACUNIT,                                // radius
        8 * FRACUNIT,                                // height
        100,                                         // mass
        2,                                           // damage
        heretic_sfx_None,                            // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF,     // flags
        MF2_LOGRAV | MF2_NOTELEPORT | MF2_FIREDAMAGE // flags2
    },

    {
        // MT_VOLCANOTBLAST
        -1,                                          // doomednum
        HERETIC_S_VOLCANOTBALL1,                     // spawnstate
        1000,                                        // spawnhealth
        HERETIC_S_NULL,                              // seestate
        heretic_sfx_None,                            // seesound
        8,                                           // reactiontime
        heretic_sfx_None,                            // attacksound
        HERETIC_S_NULL,                              // painstate
        0,                                           // painchance
        heretic_sfx_None,                            // painsound
        HERETIC_S_NULL,                              // meleestate
        HERETIC_S_NULL,                              // missilestate
        HERETIC_S_NULL,                              // crashstate
        HERETIC_S_VOLCANOTBALLX1,                    // deathstate
        HERETIC_S_NULL,                              // xdeathstate
        heretic_sfx_None,                            // deathsound
        2 * FRACUNIT,                                // speed
        8 * FRACUNIT,                                // radius
        6 * FRACUNIT,                                // height
        100,                                         // mass
        1,                                           // damage
        heretic_sfx_None,                            // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF,     // flags
        MF2_LOGRAV | MF2_NOTELEPORT | MF2_FIREDAMAGE // flags2
    },

    {
        // MT_TELEGLITGEN
        74,                                         // doomednum
        HERETIC_S_TELEGLITGEN1,                     // spawnstate
        1000,                                       // spawnhealth
        HERETIC_S_NULL,                             // seestate
        heretic_sfx_None,                           // seesound
        8,                                          // reactiontime
        heretic_sfx_None,                           // attacksound
        HERETIC_S_NULL,                             // painstate
        0,                                          // painchance
        heretic_sfx_None,                           // painsound
        HERETIC_S_NULL,                             // meleestate
        HERETIC_S_NULL,                             // missilestate
        HERETIC_S_NULL,                             // crashstate
        HERETIC_S_NULL,                             // deathstate
        HERETIC_S_NULL,                             // xdeathstate
        heretic_sfx_None,                           // deathsound
        0,                                          // speed
        20 * FRACUNIT,                              // radius
        16 * FRACUNIT,                              // height
        100,                                        // mass
        0,                                          // damage
        heretic_sfx_None,                           // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_NOSECTOR, // flags
        0                                           // flags2
    },

    {
        // MT_TELEGLITGEN2
        52,                                         // doomednum
        HERETIC_S_TELEGLITGEN2,                     // spawnstate
        1000,                                       // spawnhealth
        HERETIC_S_NULL,                             // seestate
        heretic_sfx_None,                           // seesound
        8,                                          // reactiontime
        heretic_sfx_None,                           // attacksound
        HERETIC_S_NULL,                             // painstate
        0,                                          // painchance
        heretic_sfx_None,                           // painsound
        HERETIC_S_NULL,                             // meleestate
        HERETIC_S_NULL,                             // missilestate
        HERETIC_S_NULL,                             // crashstate
        HERETIC_S_NULL,                             // deathstate
        HERETIC_S_NULL,                             // xdeathstate
        heretic_sfx_None,                           // deathsound
        0,                                          // speed
        20 * FRACUNIT,                              // radius
        16 * FRACUNIT,                              // height
        100,                                        // mass
        0,                                          // damage
        heretic_sfx_None,                           // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_NOSECTOR, // flags
        0                                           // flags2
    },

    {
        // MT_TELEGLITTER
        -1,                                        // doomednum
        HERETIC_S_TELEGLITTER1_1,                  // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        heretic_sfx_None,                          // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_NULL,                            // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        heretic_sfx_None,                          // deathsound
        0,                                         // speed
        20 * FRACUNIT,                             // radius
        16 * FRACUNIT,                             // height
        100,                                       // mass
        0,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_MISSILE, // flags
        0                                          // flags2
    },

    {
        // MT_TELEGLITTER2
        -1,                                        // doomednum
        HERETIC_S_TELEGLITTER2_1,                  // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        heretic_sfx_None,                          // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_NULL,                            // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        heretic_sfx_None,                          // deathsound
        0,                                         // speed
        20 * FRACUNIT,                             // radius
        16 * FRACUNIT,                             // height
        100,                                       // mass
        0,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_MISSILE, // flags
        0                                          // flags2
    },

    {
        // MT_TFOG
        -1,                           // doomednum
        HERETIC_S_TFOG1,              // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_TELEPORTMAN
        14,                          // doomednum
        HERETIC_S_NULL,              // spawnstate
        1000,                        // spawnhealth
        HERETIC_S_NULL,              // seestate
        heretic_sfx_None,            // seesound
        8,                           // reactiontime
        heretic_sfx_None,            // attacksound
        HERETIC_S_NULL,              // painstate
        0,                           // painchance
        heretic_sfx_None,            // painsound
        HERETIC_S_NULL,              // meleestate
        HERETIC_S_NULL,              // missilestate
        HERETIC_S_NULL,              // crashstate
        HERETIC_S_NULL,              // deathstate
        HERETIC_S_NULL,              // xdeathstate
        heretic_sfx_None,            // deathsound
        0,                           // speed
        20 * FRACUNIT,               // radius
        16 * FRACUNIT,               // height
        100,                         // mass
        0,                           // damage
        heretic_sfx_None,            // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        0                            // flags2
    },

    {
        // MT_STAFFPUFF
        -1,                           // doomednum
        HERETIC_S_STAFFPUFF1,         // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_stfhit,           // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_STAFFPUFF2
        -1,                           // doomednum
        HERETIC_S_STAFFPUFF2_1,       // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_stfpow,           // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_BEAKPUFF
        -1,                           // doomednum
        HERETIC_S_STAFFPUFF1,         // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_chicatk,          // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_MISC13
        2005,             // doomednum
        HERETIC_S_WGNT,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_GAUNTLETPUFF1
        -1,                                       // doomednum
        HERETIC_S_GAUNTLETPUFF1_1,                // spawnstate
        1000,                                     // spawnhealth
        HERETIC_S_NULL,                           // seestate
        heretic_sfx_None,                         // seesound
        8,                                        // reactiontime
        heretic_sfx_None,                         // attacksound
        HERETIC_S_NULL,                           // painstate
        0,                                        // painchance
        heretic_sfx_None,                         // painsound
        HERETIC_S_NULL,                           // meleestate
        HERETIC_S_NULL,                           // missilestate
        HERETIC_S_NULL,                           // crashstate
        HERETIC_S_NULL,                           // deathstate
        HERETIC_S_NULL,                           // xdeathstate
        heretic_sfx_None,                         // deathsound
        0,                                        // speed
        20 * FRACUNIT,                            // radius
        16 * FRACUNIT,                            // height
        100,                                      // mass
        0,                                        // damage
        heretic_sfx_None,                         // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_SHADOW, // flags
        0                                         // flags2
    },

    {
        // MT_GAUNTLETPUFF2
        -1,                                       // doomednum
        HERETIC_S_GAUNTLETPUFF2_1,                // spawnstate
        1000,                                     // spawnhealth
        HERETIC_S_NULL,                           // seestate
        heretic_sfx_None,                         // seesound
        8,                                        // reactiontime
        heretic_sfx_None,                         // attacksound
        HERETIC_S_NULL,                           // painstate
        0,                                        // painchance
        heretic_sfx_None,                         // painsound
        HERETIC_S_NULL,                           // meleestate
        HERETIC_S_NULL,                           // missilestate
        HERETIC_S_NULL,                           // crashstate
        HERETIC_S_NULL,                           // deathstate
        HERETIC_S_NULL,                           // xdeathstate
        heretic_sfx_None,                         // deathsound
        0,                                        // speed
        20 * FRACUNIT,                            // radius
        16 * FRACUNIT,                            // height
        100,                                      // mass
        0,                                        // damage
        heretic_sfx_None,                         // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_SHADOW, // flags
        0                                         // flags2
    },

    {
        // MT_MISC14
        53,               // doomednum
        HERETIC_S_BLSR,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_BLASTERFX1
        -1,                                                     // doomednum
        HERETIC_S_BLASTERFX1_1,                                 // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_None,                                       // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_BLASTERFXI1_1,                                // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_blshit,                                     // deathsound
        184 * FRACUNIT,                                         // speed
        12 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_BLASTERSMOKE
        -1,                                       // doomednum
        HERETIC_S_BLASTERSMOKE1,                  // spawnstate
        1000,                                     // spawnhealth
        HERETIC_S_NULL,                           // seestate
        heretic_sfx_None,                         // seesound
        8,                                        // reactiontime
        heretic_sfx_None,                         // attacksound
        HERETIC_S_NULL,                           // painstate
        0,                                        // painchance
        heretic_sfx_None,                         // painsound
        HERETIC_S_NULL,                           // meleestate
        HERETIC_S_NULL,                           // missilestate
        HERETIC_S_NULL,                           // crashstate
        HERETIC_S_NULL,                           // deathstate
        HERETIC_S_NULL,                           // xdeathstate
        heretic_sfx_None,                         // deathsound
        0,                                        // speed
        20 * FRACUNIT,                            // radius
        16 * FRACUNIT,                            // height
        100,                                      // mass
        0,                                        // damage
        heretic_sfx_None,                         // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_SHADOW, // flags
        MF2_NOTELEPORT | MF2_CANNOTPUSH           // flags2
    },

    {
        // MT_RIPPER
        -1,                                                     // doomednum
        HERETIC_S_RIPPER1,                                      // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_RIPPERX1,                                     // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        14 * FRACUNIT,                                          // speed
        8 * FRACUNIT,                                           // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_RIP                                // flags2
    },

    {
        // MT_BLASTERPUFF1
        -1,                           // doomednum
        HERETIC_S_BLASTERPUFF1_1,     // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_BLASTERPUFF2
        -1,                           // doomednum
        HERETIC_S_BLASTERPUFF2_1,     // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_WMACE
        2002,             // doomednum
        HERETIC_S_WMCE,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_MACEFX1
        -1,                                                     // doomednum
        HERETIC_S_MACEFX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_lobsht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_MACEFXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        20 * FRACUNIT,                                          // speed
        8 * FRACUNIT,                                           // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_FLOORBOUNCE | MF2_THRUGHOST | MF2_NOTELEPORT        // flags2
    },

    {
        // MT_MACEFX2
        -1,                                      // doomednum
        HERETIC_S_MACEFX2_1,                     // spawnstate
        1000,                                    // spawnhealth
        HERETIC_S_NULL,                          // seestate
        0,                                       // seesound
        8,                                       // reactiontime
        heretic_sfx_None,                        // attacksound
        HERETIC_S_NULL,                          // painstate
        0,                                       // painchance
        heretic_sfx_None,                        // painsound
        HERETIC_S_NULL,                          // meleestate
        HERETIC_S_NULL,                          // missilestate
        HERETIC_S_NULL,                          // crashstate
        HERETIC_S_MACEFXI2_1,                    // deathstate
        HERETIC_S_NULL,                          // xdeathstate
        0,                                       // deathsound
        10 * FRACUNIT,                           // speed
        8 * FRACUNIT,                            // radius
        6 * FRACUNIT,                            // height
        100,                                     // mass
        6,                                       // damage
        heretic_sfx_None,                        // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF, // flags
        MF2_LOGRAV | MF2_FLOORBOUNCE | MF2_THRUGHOST | MF2_NOTELEPORT // flags2
    },

    {
        // MT_MACEFX3
        -1,                                      // doomednum
        HERETIC_S_MACEFX3_1,                     // spawnstate
        1000,                                    // spawnhealth
        HERETIC_S_NULL,                          // seestate
        0,                                       // seesound
        8,                                       // reactiontime
        heretic_sfx_None,                        // attacksound
        HERETIC_S_NULL,                          // painstate
        0,                                       // painchance
        heretic_sfx_None,                        // painsound
        HERETIC_S_NULL,                          // meleestate
        HERETIC_S_NULL,                          // missilestate
        HERETIC_S_NULL,                          // crashstate
        HERETIC_S_MACEFXI1_1,                    // deathstate
        HERETIC_S_NULL,                          // xdeathstate
        0,                                       // deathsound
        7 * FRACUNIT,                            // speed
        8 * FRACUNIT,                            // radius
        6 * FRACUNIT,                            // height
        100,                                     // mass
        4,                                       // damage
        heretic_sfx_None,                        // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF, // flags
        MF2_LOGRAV | MF2_FLOORBOUNCE | MF2_THRUGHOST | MF2_NOTELEPORT // flags2
    },

    {
        // MT_MACEFX4
        -1,                                      // doomednum
        HERETIC_S_MACEFX4_1,                     // spawnstate
        1000,                                    // spawnhealth
        HERETIC_S_NULL,                          // seestate
        0,                                       // seesound
        8,                                       // reactiontime
        heretic_sfx_None,                        // attacksound
        HERETIC_S_NULL,                          // painstate
        0,                                       // painchance
        heretic_sfx_None,                        // painsound
        HERETIC_S_NULL,                          // meleestate
        HERETIC_S_NULL,                          // missilestate
        HERETIC_S_NULL,                          // crashstate
        HERETIC_S_MACEFXI4_1,                    // deathstate
        HERETIC_S_NULL,                          // xdeathstate
        0,                                       // deathsound
        7 * FRACUNIT,                            // speed
        8 * FRACUNIT,                            // radius
        6 * FRACUNIT,                            // height
        100,                                     // mass
        18,                                      // damage
        heretic_sfx_None,                        // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF, // flags
        MF2_LOGRAV | MF2_FLOORBOUNCE | MF2_THRUGHOST | MF2_TELESTOMP // flags2
    },

    {
        // MT_WSKULLROD
        2004,             // doomednum
        HERETIC_S_WSKL,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_HORNRODFX1
        -1,                                                     // doomednum
        HERETIC_S_HRODFX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_hrnsht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_HRODFXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        22 * FRACUNIT,                                          // speed
        12 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        3,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT                         // flags2
    },

    {
        // MT_HORNRODFX2
        -1,                                                     // doomednum
        HERETIC_S_HRODFX2_1,                                    // spawnstate
        4 * 35,                                                 // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_hrnsht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_HRODFXI2_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_ramphit,                                    // deathsound
        22 * FRACUNIT,                                          // speed
        12 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        10,                                                     // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_RAINPLR1
        -1,                                                     // doomednum
        HERETIC_S_RAINPLR1_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_RAINPLR1X_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        12 * FRACUNIT,                                          // speed
        5 * FRACUNIT,                                           // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        5,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_RAINPLR2
        -1,                                                     // doomednum
        HERETIC_S_RAINPLR2_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_RAINPLR2X_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        12 * FRACUNIT,                                          // speed
        5 * FRACUNIT,                                           // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        5,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_RAINPLR3
        -1,                                                     // doomednum
        HERETIC_S_RAINPLR3_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_RAINPLR3X_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        12 * FRACUNIT,                                          // speed
        5 * FRACUNIT,                                           // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        5,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_RAINPLR4
        -1,                                                     // doomednum
        HERETIC_S_RAINPLR4_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_RAINPLR4X_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        12 * FRACUNIT,                                          // speed
        5 * FRACUNIT,                                           // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        5,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_GOLDWANDFX1
        -1,                                                     // doomednum
        HERETIC_S_GWANDFX1_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_GWANDFXI1_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_gldhit,                                     // deathsound
        22 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_GOLDWANDFX2
        -1,                                                     // doomednum
        HERETIC_S_GWANDFX2_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_GWANDFXI1_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        18 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_GOLDWANDPUFF1
        -1,                           // doomednum
        HERETIC_S_GWANDPUFF1_1,       // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_GOLDWANDPUFF2
        -1,                           // doomednum
        HERETIC_S_GWANDFXI1_1,        // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_WPHOENIXROD
        2003,             // doomednum
        HERETIC_S_WPHX,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_PHOENIXFX1
        -1,                                                     // doomednum
        HERETIC_S_PHOENIXFX1_1,                                 // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_phosht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_PHOENIXFXI1_1,                                // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_phohit,                                     // deathsound
        20 * FRACUNIT,                                          // speed
        11 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        20,                                                     // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_THRUGHOST | MF2_NOTELEPORT                          // flags2
    },

    // The following thing is present in the mobjinfo table from Heretic 1.0,
    // but not in Heretic 1.3 (ie. it was removed).  It has been re-inserted
    // here to support HHE patches.

    {
        // MT_PHOENIXFX_REMOVED
        -1,                                                     // doomednum
        HERETIC_S_PHOENIXFXIX_1,                                // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_None,                                       // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_PHOENIXFXIX_3,                                // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_None,                                       // deathsound
        0,                                                      // speed
        2 * FRACUNIT,                                           // radius
        4 * FRACUNIT,                                           // height
        100,                                                    // mass
        0,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_PHOENIXPUFF
        -1,                                       // doomednum
        HERETIC_S_PHOENIXPUFF1,                   // spawnstate
        1000,                                     // spawnhealth
        HERETIC_S_NULL,                           // seestate
        heretic_sfx_None,                         // seesound
        8,                                        // reactiontime
        heretic_sfx_None,                         // attacksound
        HERETIC_S_NULL,                           // painstate
        0,                                        // painchance
        heretic_sfx_None,                         // painsound
        HERETIC_S_NULL,                           // meleestate
        HERETIC_S_NULL,                           // missilestate
        HERETIC_S_NULL,                           // crashstate
        HERETIC_S_NULL,                           // deathstate
        HERETIC_S_NULL,                           // xdeathstate
        heretic_sfx_None,                         // deathsound
        0,                                        // speed
        20 * FRACUNIT,                            // radius
        16 * FRACUNIT,                            // height
        100,                                      // mass
        0,                                        // damage
        heretic_sfx_None,                         // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_SHADOW, // flags
        MF2_NOTELEPORT | MF2_CANNOTPUSH           // flags2
    },

    {
        // MT_PHOENIXFX2
        -1,                                                     // doomednum
        HERETIC_S_PHOENIXFX2_1,                                 // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_PHOENIXFXI2_1,                                // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        10 * FRACUNIT,                                          // speed
        6 * FRACUNIT,                                           // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_FIREDAMAGE                         // flags2
    },

    {
        // MT_MISC15
        2001,             // doomednum
        HERETIC_S_WBOW,   // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_CRBOWFX1
        -1,                                                     // doomednum
        HERETIC_S_CRBOWFX1,                                     // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_bowsht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_CRBOWFXI1_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        30 * FRACUNIT,                                          // speed
        11 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        10,                                                     // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_CRBOWFX2
        -1,                                                     // doomednum
        HERETIC_S_CRBOWFX2,                                     // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        heretic_sfx_bowsht,                                     // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_CRBOWFXI1_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        32 * FRACUNIT,                                          // speed
        11 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        6,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_CRBOWFX3
        -1,                                                     // doomednum
        HERETIC_S_CRBOWFX3,                                     // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_CRBOWFXI3_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        20 * FRACUNIT,                                          // speed
        11 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_THRUGHOST | MF2_NOTELEPORT         // flags2
    },

    {
        // MT_CRBOWFX4
        -1,                   // doomednum
        HERETIC_S_CRBOWFX4_1, // spawnstate
        1000,                 // spawnhealth
        HERETIC_S_NULL,       // seestate
        heretic_sfx_None,     // seesound
        8,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_NULL,       // painstate
        0,                    // painchance
        heretic_sfx_None,     // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_NULL,       // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_NULL,       // deathstate
        HERETIC_S_NULL,       // xdeathstate
        heretic_sfx_None,     // deathsound
        0,                    // speed
        20 * FRACUNIT,        // radius
        16 * FRACUNIT,        // height
        100,                  // mass
        0,                    // damage
        heretic_sfx_None,     // activesound
        MF_NOBLOCKMAP,        // flags
        MF2_LOGRAV            // flags2
    },

    {
        // MT_BLOOD
        -1,               // doomednum
        HERETIC_S_BLOOD1, // spawnstate
        1000,             // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_NOBLOCKMAP,    // flags
        0                 // flags2
    },

    {
        // MT_BLOODSPLATTER
        -1,                                      // doomednum
        HERETIC_S_BLOODSPLATTER1,                // spawnstate
        1000,                                    // spawnhealth
        HERETIC_S_NULL,                          // seestate
        heretic_sfx_None,                        // seesound
        8,                                       // reactiontime
        heretic_sfx_None,                        // attacksound
        HERETIC_S_NULL,                          // painstate
        0,                                       // painchance
        heretic_sfx_None,                        // painsound
        HERETIC_S_NULL,                          // meleestate
        HERETIC_S_NULL,                          // missilestate
        HERETIC_S_NULL,                          // crashstate
        HERETIC_S_BLOODSPLATTERX,                // deathstate
        HERETIC_S_NULL,                          // xdeathstate
        heretic_sfx_None,                        // deathsound
        0,                                       // speed
        2 * FRACUNIT,                            // radius
        4 * FRACUNIT,                            // height
        100,                                     // mass
        0,                                       // damage
        heretic_sfx_None,                        // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF, // flags
        MF2_NOTELEPORT | MF2_CANNOTPUSH          // flags2
    },

    {
        // MT_PLAYER
        -1,                   // doomednum
        HERETIC_S_PLAY,       // spawnstate
        100,                  // spawnhealth
        HERETIC_S_PLAY_RUN1,  // seestate
        heretic_sfx_None,     // seesound
        0,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_PLAY_PAIN,  // painstate
        255,                  // painchance
        heretic_sfx_plrpai,   // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_PLAY_ATK1,  // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_PLAY_DIE1,  // deathstate
        HERETIC_S_PLAY_XDIE1, // xdeathstate
        heretic_sfx_plrdth,   // deathsound
        0,                    // speed
        16 * FRACUNIT,        // radius
        56 * FRACUNIT,        // height
        100,                  // mass
        0,                    // damage
        heretic_sfx_None,     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_DROPOFF | MF_PICKUP |
            MF_NOTDMATCH, // flags
        MF2_WINDTHRUST | MF2_FOOTCLIP | MF2_SLIDE | MF2_PASSMOBJ |
            MF2_TELESTOMP // flags2
    },

    {
        // MT_BLOODYSKULL
        -1,                         // doomednum
        HERETIC_S_BLOODYSKULL1,     // spawnstate
        1000,                       // spawnhealth
        HERETIC_S_NULL,             // seestate
        heretic_sfx_None,           // seesound
        8,                          // reactiontime
        heretic_sfx_None,           // attacksound
        HERETIC_S_NULL,             // painstate
        0,                          // painchance
        heretic_sfx_None,           // painsound
        HERETIC_S_NULL,             // meleestate
        HERETIC_S_NULL,             // missilestate
        HERETIC_S_NULL,             // crashstate
        HERETIC_S_NULL,             // deathstate
        HERETIC_S_NULL,             // xdeathstate
        heretic_sfx_None,           // deathsound
        0,                          // speed
        4 * FRACUNIT,               // radius
        4 * FRACUNIT,               // height
        100,                        // mass
        0,                          // damage
        heretic_sfx_None,           // activesound
        MF_NOBLOCKMAP | MF_DROPOFF, // flags
        MF2_LOGRAV | MF2_CANNOTPUSH // flags2
    },

    {
        // MT_CHICPLAYER
        -1,                                                  // doomednum
        HERETIC_S_CHICPLAY,                                  // spawnstate
        100,                                                 // spawnhealth
        HERETIC_S_CHICPLAY_RUN1,                             // seestate
        heretic_sfx_None,                                    // seesound
        0,                                                   // reactiontime
        heretic_sfx_None,                                    // attacksound
        HERETIC_S_CHICPLAY_PAIN,                             // painstate
        255,                                                 // painchance
        heretic_sfx_chicpai,                                 // painsound
        HERETIC_S_NULL,                                      // meleestate
        HERETIC_S_CHICPLAY_ATK1,                             // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_CHICKEN_DIE1,                              // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        heretic_sfx_chicdth,                                 // deathsound
        0,                                                   // speed
        16 * FRACUNIT,                                       // radius
        24 * FRACUNIT,                                       // height
        100,                                                 // mass
        0,                                                   // damage
        heretic_sfx_None,                                    // activesound
        MF_SOLID | MF_SHOOTABLE | MF_DROPOFF | MF_NOTDMATCH, // flags
        MF2_WINDTHRUST | MF2_SLIDE | MF2_PASSMOBJ | MF2_FOOTCLIP | MF2_LOGRAV |
            MF2_TELESTOMP // flags2
    },

    {
        // MT_CHICKEN
        -1,                                                  // doomednum
        HERETIC_S_CHICKEN_LOOK1,                             // spawnstate
        10,                                                  // spawnhealth
        HERETIC_S_CHICKEN_WALK1,                             // seestate
        heretic_sfx_chicpai,                                 // seesound
        8,                                                   // reactiontime
        heretic_sfx_chicatk,                                 // attacksound
        HERETIC_S_CHICKEN_PAIN1,                             // painstate
        200,                                                 // painchance
        heretic_sfx_chicpai,                                 // painsound
        HERETIC_S_CHICKEN_ATK1,                              // meleestate
        0,                                                   // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_CHICKEN_DIE1,                              // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        heretic_sfx_chicdth,                                 // deathsound
        4,                                                   // speed
        9 * FRACUNIT,                                        // radius
        22 * FRACUNIT,                                       // height
        40,                                                  // mass
        0,                                                   // damage
        heretic_sfx_chicact,                                 // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_DROPOFF, // flags
        MF2_WINDTHRUST | MF2_FOOTCLIP | MF2_PASSMOBJ         // flags2
    },

    {
        // MT_FEATHER
        -1,                                      // doomednum
        HERETIC_S_FEATHER1,                      // spawnstate
        1000,                                    // spawnhealth
        HERETIC_S_NULL,                          // seestate
        heretic_sfx_None,                        // seesound
        8,                                       // reactiontime
        heretic_sfx_None,                        // attacksound
        HERETIC_S_NULL,                          // painstate
        0,                                       // painchance
        heretic_sfx_None,                        // painsound
        HERETIC_S_NULL,                          // meleestate
        HERETIC_S_NULL,                          // missilestate
        HERETIC_S_NULL,                          // crashstate
        HERETIC_S_FEATHERX,                      // deathstate
        HERETIC_S_NULL,                          // xdeathstate
        heretic_sfx_None,                        // deathsound
        0,                                       // speed
        2 * FRACUNIT,                            // radius
        4 * FRACUNIT,                            // height
        100,                                     // mass
        0,                                       // damage
        heretic_sfx_None,                        // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF, // flags
        MF2_NOTELEPORT | MF2_LOGRAV | MF2_CANNOTPUSH | MF2_WINDTHRUST // flags2
    },

    {
        // MT_MUMMY
        68,                                     // doomednum
        HERETIC_S_MUMMY_LOOK1,                  // spawnstate
        80,                                     // spawnhealth
        HERETIC_S_MUMMY_WALK1,                  // seestate
        heretic_sfx_mumsit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_mumat1,                     // attacksound
        HERETIC_S_MUMMY_PAIN1,                  // painstate
        128,                                    // painchance
        heretic_sfx_mumpai,                     // painsound
        HERETIC_S_MUMMY_ATK1,                   // meleestate
        0,                                      // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_MUMMY_DIE1,                   // deathstate
        HERETIC_S_NULL,                         // xdeathstate
        heretic_sfx_mumdth,                     // deathsound
        12,                                     // speed
        22 * FRACUNIT,                          // radius
        62 * FRACUNIT,                          // height
        75,                                     // mass
        0,                                      // damage
        heretic_sfx_mumact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ             // flags2
    },

    {
        // MT_MUMMYLEADER
        45,                                     // doomednum
        HERETIC_S_MUMMY_LOOK1,                  // spawnstate
        100,                                    // spawnhealth
        HERETIC_S_MUMMY_WALK1,                  // seestate
        heretic_sfx_mumsit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_mumat1,                     // attacksound
        HERETIC_S_MUMMY_PAIN1,                  // painstate
        64,                                     // painchance
        heretic_sfx_mumpai,                     // painsound
        HERETIC_S_MUMMY_ATK1,                   // meleestate
        HERETIC_S_MUMMYL_ATK1,                  // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_MUMMY_DIE1,                   // deathstate
        HERETIC_S_NULL,                         // xdeathstate
        heretic_sfx_mumdth,                     // deathsound
        12,                                     // speed
        22 * FRACUNIT,                          // radius
        62 * FRACUNIT,                          // height
        75,                                     // mass
        0,                                      // damage
        heretic_sfx_mumact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ             // flags2
    },

    {
        // MT_MUMMYGHOST
        69,                                                 // doomednum
        HERETIC_S_MUMMY_LOOK1,                              // spawnstate
        80,                                                 // spawnhealth
        HERETIC_S_MUMMY_WALK1,                              // seestate
        heretic_sfx_mumsit,                                 // seesound
        8,                                                  // reactiontime
        heretic_sfx_mumat1,                                 // attacksound
        HERETIC_S_MUMMY_PAIN1,                              // painstate
        128,                                                // painchance
        heretic_sfx_mumpai,                                 // painsound
        HERETIC_S_MUMMY_ATK1,                               // meleestate
        0,                                                  // missilestate
        HERETIC_S_NULL,                                     // crashstate
        HERETIC_S_MUMMY_DIE1,                               // deathstate
        HERETIC_S_NULL,                                     // xdeathstate
        heretic_sfx_mumdth,                                 // deathsound
        12,                                                 // speed
        22 * FRACUNIT,                                      // radius
        62 * FRACUNIT,                                      // height
        75,                                                 // mass
        0,                                                  // damage
        heretic_sfx_mumact,                                 // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_SHADOW, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ                         // flags2
    },

    {
        // MT_MUMMYLEADERGHOST
        46,                                                 // doomednum
        HERETIC_S_MUMMY_LOOK1,                              // spawnstate
        100,                                                // spawnhealth
        HERETIC_S_MUMMY_WALK1,                              // seestate
        heretic_sfx_mumsit,                                 // seesound
        8,                                                  // reactiontime
        heretic_sfx_mumat1,                                 // attacksound
        HERETIC_S_MUMMY_PAIN1,                              // painstate
        64,                                                 // painchance
        heretic_sfx_mumpai,                                 // painsound
        HERETIC_S_MUMMY_ATK1,                               // meleestate
        HERETIC_S_MUMMYL_ATK1,                              // missilestate
        HERETIC_S_NULL,                                     // crashstate
        HERETIC_S_MUMMY_DIE1,                               // deathstate
        HERETIC_S_NULL,                                     // xdeathstate
        heretic_sfx_mumdth,                                 // deathsound
        12,                                                 // speed
        22 * FRACUNIT,                                      // radius
        62 * FRACUNIT,                                      // height
        75,                                                 // mass
        0,                                                  // damage
        heretic_sfx_mumact,                                 // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_SHADOW, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ                         // flags2
    },

    {
        // MT_MUMMYSOUL
        -1,                           // doomednum
        HERETIC_S_MUMMY_SOUL1,        // spawnstate
        1000,                         // spawnhealth
        HERETIC_S_NULL,               // seestate
        heretic_sfx_None,             // seesound
        8,                            // reactiontime
        heretic_sfx_None,             // attacksound
        HERETIC_S_NULL,               // painstate
        0,                            // painchance
        heretic_sfx_None,             // painsound
        HERETIC_S_NULL,               // meleestate
        HERETIC_S_NULL,               // missilestate
        HERETIC_S_NULL,               // crashstate
        HERETIC_S_NULL,               // deathstate
        HERETIC_S_NULL,               // xdeathstate
        heretic_sfx_None,             // deathsound
        0,                            // speed
        20 * FRACUNIT,                // radius
        16 * FRACUNIT,                // height
        100,                          // mass
        0,                            // damage
        heretic_sfx_None,             // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY, // flags
        0                             // flags2
    },

    {
        // MT_MUMMYFX1
        -1,                                                     // doomednum
        HERETIC_S_MUMMYFX1_1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_MUMMYFXI1_1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        9 * FRACUNIT,                                           // speed
        8 * FRACUNIT,                                           // radius
        14 * FRACUNIT,                                          // height
        100,                                                    // mass
        4,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_BEAST
        70,                                     // doomednum
        HERETIC_S_BEAST_LOOK1,                  // spawnstate
        220,                                    // spawnhealth
        HERETIC_S_BEAST_WALK1,                  // seestate
        heretic_sfx_bstsit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_bstatk,                     // attacksound
        HERETIC_S_BEAST_PAIN1,                  // painstate
        100,                                    // painchance
        heretic_sfx_bstpai,                     // painsound
        0,                                      // meleestate
        HERETIC_S_BEAST_ATK1,                   // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_BEAST_DIE1,                   // deathstate
        HERETIC_S_BEAST_XDIE1,                  // xdeathstate
        heretic_sfx_bstdth,                     // deathsound
        14,                                     // speed
        32 * FRACUNIT,                          // radius
        74 * FRACUNIT,                          // height
        200,                                    // mass
        0,                                      // damage
        heretic_sfx_bstact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ             // flags2
    },

    {
        // MT_BEASTBALL
        -1,                                                     // doomednum
        HERETIC_S_BEASTBALL1,                                   // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_BEASTBALLX1,                                  // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        12 * FRACUNIT,                                          // speed
        9 * FRACUNIT,                                           // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        4,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT                         // flags2
    },

    {
        // MT_BURNBALL
        -1,                                        // doomednum
        HERETIC_S_BURNBALL1,                       // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        0,                                         // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_BEASTBALLX1,                     // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        0,                                         // deathsound
        10 * FRACUNIT,                             // speed
        6 * FRACUNIT,                              // radius
        8 * FRACUNIT,                              // height
        100,                                       // mass
        2,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_MISSILE, // flags
        MF2_NOTELEPORT                             // flags2
    },

    {
        // MT_BURNBALLFB
        -1,                                        // doomednum
        HERETIC_S_BURNBALLFB1,                     // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        0,                                         // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_BEASTBALLX1,                     // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        0,                                         // deathsound
        10 * FRACUNIT,                             // speed
        6 * FRACUNIT,                              // radius
        8 * FRACUNIT,                              // height
        100,                                       // mass
        2,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_MISSILE, // flags
        MF2_NOTELEPORT                             // flags2
    },

    {
        // MT_PUFFY
        -1,                                        // doomednum
        HERETIC_S_PUFFY1,                          // spawnstate
        1000,                                      // spawnhealth
        HERETIC_S_NULL,                            // seestate
        0,                                         // seesound
        8,                                         // reactiontime
        heretic_sfx_None,                          // attacksound
        HERETIC_S_NULL,                            // painstate
        0,                                         // painchance
        heretic_sfx_None,                          // painsound
        HERETIC_S_NULL,                            // meleestate
        HERETIC_S_NULL,                            // missilestate
        HERETIC_S_NULL,                            // crashstate
        HERETIC_S_PUFFY1,                          // deathstate
        HERETIC_S_NULL,                            // xdeathstate
        0,                                         // deathsound
        10 * FRACUNIT,                             // speed
        6 * FRACUNIT,                              // radius
        8 * FRACUNIT,                              // height
        100,                                       // mass
        2,                                         // damage
        heretic_sfx_None,                          // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY | MF_MISSILE, // flags
        MF2_NOTELEPORT                             // flags2
    },

    {
        // MT_SNAKE
        92,                                     // doomednum
        HERETIC_S_SNAKE_LOOK1,                  // spawnstate
        280,                                    // spawnhealth
        HERETIC_S_SNAKE_WALK1,                  // seestate
        heretic_sfx_snksit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_snkatk,                     // attacksound
        HERETIC_S_SNAKE_PAIN1,                  // painstate
        48,                                     // painchance
        heretic_sfx_snkpai,                     // painsound
        0,                                      // meleestate
        HERETIC_S_SNAKE_ATK1,                   // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_SNAKE_DIE1,                   // deathstate
        HERETIC_S_NULL,                         // xdeathstate
        heretic_sfx_snkdth,                     // deathsound
        10,                                     // speed
        22 * FRACUNIT,                          // radius
        70 * FRACUNIT,                          // height
        100,                                    // mass
        0,                                      // damage
        heretic_sfx_snkact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ             // flags2
    },

    {
        // MT_SNAKEPRO_A
        -1,                                                     // doomednum
        HERETIC_S_SNAKEPRO_A1,                                  // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SNAKEPRO_AX1,                                 // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        14 * FRACUNIT,                                          // speed
        12 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT                         // flags2
    },

    {
        // MT_SNAKEPRO_B
        -1,                                                     // doomednum
        HERETIC_S_SNAKEPRO_B1,                                  // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SNAKEPRO_BX1,                                 // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        14 * FRACUNIT,                                          // speed
        12 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        3,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_HEAD
        6,                                                   // doomednum
        HERETIC_S_HEAD_LOOK,                                 // spawnstate
        700,                                                 // spawnhealth
        HERETIC_S_HEAD_FLOAT,                                // seestate
        heretic_sfx_hedsit,                                  // seesound
        8,                                                   // reactiontime
        heretic_sfx_hedat1,                                  // attacksound
        HERETIC_S_HEAD_PAIN1,                                // painstate
        32,                                                  // painchance
        heretic_sfx_hedpai,                                  // painsound
        0,                                                   // meleestate
        HERETIC_S_HEAD_ATK1,                                 // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_HEAD_DIE1,                                 // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        heretic_sfx_heddth,                                  // deathsound
        6,                                                   // speed
        40 * FRACUNIT,                                       // radius
        72 * FRACUNIT,                                       // height
        325,                                                 // mass
        0,                                                   // damage
        heretic_sfx_hedact,                                  // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_NOBLOOD, // flags
        MF2_PASSMOBJ                                         // flags2
    },

    {
        // MT_HEADFX1
        -1,                                                     // doomednum
        HERETIC_S_HEADFX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_HEADFXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        13 * FRACUNIT,                                          // speed
        12 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_THRUGHOST                          // flags2
    },

    {
        // MT_HEADFX2
        -1,                                                     // doomednum
        HERETIC_S_HEADFX2_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_HEADFXI2_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        8 * FRACUNIT,                                           // speed
        12 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        3,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_HEADFX3
        -1,                                                     // doomednum
        HERETIC_S_HEADFX3_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_HEADFXI3_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        10 * FRACUNIT,                                          // speed
        14 * FRACUNIT,                                          // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        5,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT                         // flags2
    },

    {
        // MT_WHIRLWIND
        -1,                   // doomednum
        HERETIC_S_HEADFX4_1,  // spawnstate
        1000,                 // spawnhealth
        HERETIC_S_NULL,       // seestate
        0,                    // seesound
        8,                    // reactiontime
        heretic_sfx_None,     // attacksound
        HERETIC_S_NULL,       // painstate
        0,                    // painchance
        heretic_sfx_None,     // painsound
        HERETIC_S_NULL,       // meleestate
        HERETIC_S_NULL,       // missilestate
        HERETIC_S_NULL,       // crashstate
        HERETIC_S_HEADFXI4_1, // deathstate
        HERETIC_S_NULL,       // xdeathstate
        0,                    // deathsound
        10 * FRACUNIT,        // speed
        16 * FRACUNIT,        // radius
        74 * FRACUNIT,        // height
        100,                  // mass
        1,                    // damage
        heretic_sfx_None,     // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY |
            MF_SHADOW, // flags
        MF2_NOTELEPORT // flags2
    },

    {
        // MT_CLINK
        90,                                                  // doomednum
        HERETIC_S_CLINK_LOOK1,                               // spawnstate
        150,                                                 // spawnhealth
        HERETIC_S_CLINK_WALK1,                               // seestate
        heretic_sfx_clksit,                                  // seesound
        8,                                                   // reactiontime
        heretic_sfx_clkatk,                                  // attacksound
        HERETIC_S_CLINK_PAIN1,                               // painstate
        32,                                                  // painchance
        heretic_sfx_clkpai,                                  // painsound
        HERETIC_S_CLINK_ATK1,                                // meleestate
        0,                                                   // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_CLINK_DIE1,                                // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        heretic_sfx_clkdth,                                  // deathsound
        14,                                                  // speed
        20 * FRACUNIT,                                       // radius
        64 * FRACUNIT,                                       // height
        75,                                                  // mass
        0,                                                   // damage
        heretic_sfx_clkact,                                  // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_NOBLOOD, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ                          // flags2
    },

    {
        // MT_WIZARD
        15,                     // doomednum
        HERETIC_S_WIZARD_LOOK1, // spawnstate
        180,                    // spawnhealth
        HERETIC_S_WIZARD_WALK1, // seestate
        heretic_sfx_wizsit,     // seesound
        8,                      // reactiontime
        heretic_sfx_wizatk,     // attacksound
        HERETIC_S_WIZARD_PAIN1, // painstate
        64,                     // painchance
        heretic_sfx_wizpai,     // painsound
        0,                      // meleestate
        HERETIC_S_WIZARD_ATK1,  // missilestate
        HERETIC_S_NULL,         // crashstate
        HERETIC_S_WIZARD_DIE1,  // deathstate
        HERETIC_S_NULL,         // xdeathstate
        heretic_sfx_wizdth,     // deathsound
        12,                     // speed
        16 * FRACUNIT,          // radius
        68 * FRACUNIT,          // height
        100,                    // mass
        0,                      // damage
        heretic_sfx_wizact,     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_FLOAT |
            MF_NOGRAVITY, // flags
        MF2_PASSMOBJ      // flags2
    },

    {
        // MT_WIZFX1
        -1,                                                     // doomednum
        HERETIC_S_WIZFX1_1,                                     // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_WIZFXI1_1,                                    // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        18 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        3,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_IMP
        66,                     // doomednum
        HERETIC_S_IMP_LOOK1,    // spawnstate
        40,                     // spawnhealth
        HERETIC_S_IMP_FLY1,     // seestate
        heretic_sfx_impsit,     // seesound
        8,                      // reactiontime
        heretic_sfx_impat1,     // attacksound
        HERETIC_S_IMP_PAIN1,    // painstate
        200,                    // painchance
        heretic_sfx_imppai,     // painsound
        HERETIC_S_IMP_MEATK1,   // meleestate
        HERETIC_S_IMP_MSATK1_1, // missilestate
        HERETIC_S_IMP_CRASH1,   // crashstate
        HERETIC_S_IMP_DIE1,     // deathstate
        HERETIC_S_IMP_XDIE1,    // xdeathstate
        heretic_sfx_impdth,     // deathsound
        10,                     // speed
        16 * FRACUNIT,          // radius
        36 * FRACUNIT,          // height
        50,                     // mass
        0,                      // damage
        heretic_sfx_impact,     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY |
            MF_COUNTKILL,             // flags
        MF2_SPAWNFLOAT | MF2_PASSMOBJ // flags2
    },

    {
        // MT_IMPLEADER
        5,                      // doomednum
        HERETIC_S_IMP_LOOK1,    // spawnstate
        80,                     // spawnhealth
        HERETIC_S_IMP_FLY1,     // seestate
        heretic_sfx_impsit,     // seesound
        8,                      // reactiontime
        heretic_sfx_impat2,     // attacksound
        HERETIC_S_IMP_PAIN1,    // painstate
        200,                    // painchance
        heretic_sfx_imppai,     // painsound
        0,                      // meleestate
        HERETIC_S_IMP_MSATK2_1, // missilestate
        HERETIC_S_IMP_CRASH1,   // crashstate
        HERETIC_S_IMP_DIE1,     // deathstate
        HERETIC_S_IMP_XDIE1,    // xdeathstate
        heretic_sfx_impdth,     // deathsound
        10,                     // speed
        16 * FRACUNIT,          // radius
        36 * FRACUNIT,          // height
        50,                     // mass
        0,                      // damage
        heretic_sfx_impact,     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY |
            MF_COUNTKILL,             // flags
        MF2_SPAWNFLOAT | MF2_PASSMOBJ // flags2
    },

    {
        // MT_IMPCHUNK1
        -1,                    // doomednum
        HERETIC_S_IMP_CHUNKA1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_NOBLOCKMAP,         // flags
        0                      // flags2
    },

    {
        // MT_IMPCHUNK2
        -1,                    // doomednum
        HERETIC_S_IMP_CHUNKB1, // spawnstate
        1000,                  // spawnhealth
        HERETIC_S_NULL,        // seestate
        heretic_sfx_None,      // seesound
        8,                     // reactiontime
        heretic_sfx_None,      // attacksound
        HERETIC_S_NULL,        // painstate
        0,                     // painchance
        heretic_sfx_None,      // painsound
        HERETIC_S_NULL,        // meleestate
        HERETIC_S_NULL,        // missilestate
        HERETIC_S_NULL,        // crashstate
        HERETIC_S_NULL,        // deathstate
        HERETIC_S_NULL,        // xdeathstate
        heretic_sfx_None,      // deathsound
        0,                     // speed
        20 * FRACUNIT,         // radius
        16 * FRACUNIT,         // height
        100,                   // mass
        0,                     // damage
        heretic_sfx_None,      // activesound
        MF_NOBLOCKMAP,         // flags
        0                      // flags2
    },

    {
        // MT_IMPBALL
        -1,                                                     // doomednum
        HERETIC_S_IMPFX1,                                       // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_IMPFXI1,                                      // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        10 * FRACUNIT,                                          // speed
        8 * FRACUNIT,                                           // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT                         // flags2
    },

    {
        // MT_KNIGHT
        64,                                     // doomednum
        HERETIC_S_KNIGHT_STND1,                 // spawnstate
        200,                                    // spawnhealth
        HERETIC_S_KNIGHT_WALK1,                 // seestate
        heretic_sfx_kgtsit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_kgtatk,                     // attacksound
        HERETIC_S_KNIGHT_PAIN1,                 // painstate
        100,                                    // painchance
        heretic_sfx_kgtpai,                     // painsound
        HERETIC_S_KNIGHT_ATK1,                  // meleestate
        HERETIC_S_KNIGHT_ATK1,                  // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_KNIGHT_DIE1,                  // deathstate
        HERETIC_S_NULL,                         // xdeathstate
        heretic_sfx_kgtdth,                     // deathsound
        12,                                     // speed
        24 * FRACUNIT,                          // radius
        78 * FRACUNIT,                          // height
        150,                                    // mass
        0,                                      // damage
        heretic_sfx_kgtact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ             // flags2
    },

    {
        // MT_KNIGHTGHOST
        65,                                                 // doomednum
        HERETIC_S_KNIGHT_STND1,                             // spawnstate
        200,                                                // spawnhealth
        HERETIC_S_KNIGHT_WALK1,                             // seestate
        heretic_sfx_kgtsit,                                 // seesound
        8,                                                  // reactiontime
        heretic_sfx_kgtatk,                                 // attacksound
        HERETIC_S_KNIGHT_PAIN1,                             // painstate
        100,                                                // painchance
        heretic_sfx_kgtpai,                                 // painsound
        HERETIC_S_KNIGHT_ATK1,                              // meleestate
        HERETIC_S_KNIGHT_ATK1,                              // missilestate
        HERETIC_S_NULL,                                     // crashstate
        HERETIC_S_KNIGHT_DIE1,                              // deathstate
        HERETIC_S_NULL,                                     // xdeathstate
        heretic_sfx_kgtdth,                                 // deathsound
        12,                                                 // speed
        24 * FRACUNIT,                                      // radius
        78 * FRACUNIT,                                      // height
        150,                                                // mass
        0,                                                  // damage
        heretic_sfx_kgtact,                                 // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_SHADOW, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ                         // flags2
    },

    {
        // MT_KNIGHTAXE
        -1,                                                     // doomednum
        HERETIC_S_SPINAXE1,                                     // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SPINAXEX1,                                    // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        9 * FRACUNIT,                                           // speed
        10 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        2,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_WINDTHRUST | MF2_NOTELEPORT | MF2_THRUGHOST         // flags2
    },

    {
        // MT_REDAXE
        -1,                                                     // doomednum
        HERETIC_S_REDAXE1,                                      // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_REDAXEX1,                                     // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_hrnhit,                                     // deathsound
        9 * FRACUNIT,                                           // speed
        10 * FRACUNIT,                                          // radius
        8 * FRACUNIT,                                           // height
        100,                                                    // mass
        7,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_THRUGHOST                          // flags2
    },

    {
        // MT_SORCERER1
        7,                                      // doomednum
        HERETIC_S_SRCR1_LOOK1,                  // spawnstate
        2000,                                   // spawnhealth
        HERETIC_S_SRCR1_WALK1,                  // seestate
        heretic_sfx_sbtsit,                     // seesound
        8,                                      // reactiontime
        heretic_sfx_sbtatk,                     // attacksound
        HERETIC_S_SRCR1_PAIN1,                  // painstate
        56,                                     // painchance
        heretic_sfx_sbtpai,                     // painsound
        0,                                      // meleestate
        HERETIC_S_SRCR1_ATK1,                   // missilestate
        HERETIC_S_NULL,                         // crashstate
        HERETIC_S_SRCR1_DIE1,                   // deathstate
        HERETIC_S_NULL,                         // xdeathstate
        heretic_sfx_sbtdth,                     // deathsound
        16,                                     // speed
        28 * FRACUNIT,                          // radius
        100 * FRACUNIT,                         // height
        800,                                    // mass
        0,                                      // damage
        heretic_sfx_sbtact,                     // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ | MF2_BOSS  // flags2
    },

    {
        // MT_SRCRFX1
        -1,                                                     // doomednum
        HERETIC_S_SRCRFX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SRCRFXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        20 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        10 * FRACUNIT,                                          // height
        100,                                                    // mass
        10,                                                     // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_FIREDAMAGE                         // flags2
    },

    {
        // MT_SORCERER2
        -1,                                                  // doomednum
        HERETIC_S_SOR2_LOOK1,                                // spawnstate
        3500,                                                // spawnhealth
        HERETIC_S_SOR2_WALK1,                                // seestate
        heretic_sfx_sorsit,                                  // seesound
        8,                                                   // reactiontime
        heretic_sfx_soratk,                                  // attacksound
        HERETIC_S_SOR2_PAIN1,                                // painstate
        32,                                                  // painchance
        heretic_sfx_sorpai,                                  // painsound
        0,                                                   // meleestate
        HERETIC_S_SOR2_ATK1,                                 // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_SOR2_DIE1,                                 // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        0,                                                   // deathsound
        14,                                                  // speed
        16 * FRACUNIT,                                       // radius
        70 * FRACUNIT,                                       // height
        300,                                                 // mass
        0,                                                   // damage
        heretic_sfx_soract,                                  // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_DROPOFF, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ | MF2_BOSS               // flags2
    },

    {
        // MT_SOR2FX1
        -1,                                                     // doomednum
        HERETIC_S_SOR2FX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SOR2FXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        20 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        1,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_SOR2FXSPARK
        -1,                             // doomednum
        HERETIC_S_SOR2FXSPARK1,         // spawnstate
        1000,                           // spawnhealth
        HERETIC_S_NULL,                 // seestate
        heretic_sfx_None,               // seesound
        8,                              // reactiontime
        heretic_sfx_None,               // attacksound
        HERETIC_S_NULL,                 // painstate
        0,                              // painchance
        heretic_sfx_None,               // painsound
        HERETIC_S_NULL,                 // meleestate
        HERETIC_S_NULL,                 // missilestate
        HERETIC_S_NULL,                 // crashstate
        HERETIC_S_NULL,                 // deathstate
        HERETIC_S_NULL,                 // xdeathstate
        heretic_sfx_None,               // deathsound
        0,                              // speed
        20 * FRACUNIT,                  // radius
        16 * FRACUNIT,                  // height
        100,                            // mass
        0,                              // damage
        heretic_sfx_None,               // activesound
        MF_NOBLOCKMAP | MF_NOGRAVITY,   // flags
        MF2_NOTELEPORT | MF2_CANNOTPUSH // flags2
    },

    {
        // MT_SOR2FX2
        -1,                                                     // doomednum
        HERETIC_S_SOR2FX2_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_SOR2FXI2_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        6 * FRACUNIT,                                           // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        10,                                                     // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT                                          // flags2
    },

    {
        // MT_SOR2TELEFADE
        -1,                      // doomednum
        HERETIC_S_SOR2TELEFADE1, // spawnstate
        1000,                    // spawnhealth
        HERETIC_S_NULL,          // seestate
        heretic_sfx_None,        // seesound
        8,                       // reactiontime
        heretic_sfx_None,        // attacksound
        HERETIC_S_NULL,          // painstate
        0,                       // painchance
        heretic_sfx_None,        // painsound
        HERETIC_S_NULL,          // meleestate
        HERETIC_S_NULL,          // missilestate
        HERETIC_S_NULL,          // crashstate
        HERETIC_S_NULL,          // deathstate
        HERETIC_S_NULL,          // xdeathstate
        heretic_sfx_None,        // deathsound
        0,                       // speed
        20 * FRACUNIT,           // radius
        16 * FRACUNIT,           // height
        100,                     // mass
        0,                       // damage
        heretic_sfx_None,        // activesound
        MF_NOBLOCKMAP,           // flags
        0                        // flags2
    },

    {
        // MT_MINOTAUR
        9,                                                   // doomednum
        HERETIC_S_MNTR_LOOK1,                                // spawnstate
        3000,                                                // spawnhealth
        HERETIC_S_MNTR_WALK1,                                // seestate
        heretic_sfx_minsit,                                  // seesound
        8,                                                   // reactiontime
        heretic_sfx_minat1,                                  // attacksound
        HERETIC_S_MNTR_PAIN1,                                // painstate
        25,                                                  // painchance
        heretic_sfx_minpai,                                  // painsound
        HERETIC_S_MNTR_ATK1_1,                               // meleestate
        HERETIC_S_MNTR_ATK2_1,                               // missilestate
        HERETIC_S_NULL,                                      // crashstate
        HERETIC_S_MNTR_DIE1,                                 // deathstate
        HERETIC_S_NULL,                                      // xdeathstate
        heretic_sfx_mindth,                                  // deathsound
        16,                                                  // speed
        28 * FRACUNIT,                                       // radius
        100 * FRACUNIT,                                      // height
        800,                                                 // mass
        7,                                                   // damage
        heretic_sfx_minact,                                  // activesound
        MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL | MF_DROPOFF, // flags
        MF2_FOOTCLIP | MF2_PASSMOBJ | MF2_BOSS               // flags2
    },

    {
        // MT_MNTRFX1
        -1,                                                     // doomednum
        HERETIC_S_MNTRFX1_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_MNTRFXI1_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        0,                                                      // deathsound
        20 * FRACUNIT,                                          // speed
        10 * FRACUNIT,                                          // radius
        6 * FRACUNIT,                                           // height
        100,                                                    // mass
        3,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_FIREDAMAGE                         // flags2
    },

    {
        // MT_MNTRFX2
        -1,                                                     // doomednum
        HERETIC_S_MNTRFX2_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_MNTRFXI2_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_phohit,                                     // deathsound
        14 * FRACUNIT,                                          // speed
        5 * FRACUNIT,                                           // radius
        12 * FRACUNIT,                                          // height
        100,                                                    // mass
        4,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_FIREDAMAGE                         // flags2
    },

    {
        // MT_MNTRFX3
        -1,                                                     // doomednum
        HERETIC_S_MNTRFX3_1,                                    // spawnstate
        1000,                                                   // spawnhealth
        HERETIC_S_NULL,                                         // seestate
        0,                                                      // seesound
        8,                                                      // reactiontime
        heretic_sfx_None,                                       // attacksound
        HERETIC_S_NULL,                                         // painstate
        0,                                                      // painchance
        heretic_sfx_None,                                       // painsound
        HERETIC_S_NULL,                                         // meleestate
        HERETIC_S_NULL,                                         // missilestate
        HERETIC_S_NULL,                                         // crashstate
        HERETIC_S_MNTRFXI2_1,                                   // deathstate
        HERETIC_S_NULL,                                         // xdeathstate
        heretic_sfx_phohit,                                     // deathsound
        0,                                                      // speed
        8 * FRACUNIT,                                           // radius
        16 * FRACUNIT,                                          // height
        100,                                                    // mass
        4,                                                      // damage
        heretic_sfx_None,                                       // activesound
        MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY, // flags
        MF2_NOTELEPORT | MF2_FIREDAMAGE                         // flags2
    },

    {
        // MT_AKYY
        73,                        // doomednum
        HERETIC_S_AKYY1,           // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        0                          // flags2
    },

    {
        // MT_BKYY
        79,                        // doomednum
        HERETIC_S_BKYY1,           // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        0                          // flags2
    },

    {
        // MT_CKEY
        80,                        // doomednum
        HERETIC_S_CKYY1,           // spawnstate
        1000,                      // spawnhealth
        HERETIC_S_NULL,            // seestate
        heretic_sfx_None,          // seesound
        8,                         // reactiontime
        heretic_sfx_None,          // attacksound
        HERETIC_S_NULL,            // painstate
        0,                         // painchance
        heretic_sfx_None,          // painsound
        HERETIC_S_NULL,            // meleestate
        HERETIC_S_NULL,            // missilestate
        HERETIC_S_NULL,            // crashstate
        HERETIC_S_NULL,            // deathstate
        HERETIC_S_NULL,            // xdeathstate
        heretic_sfx_None,          // deathsound
        0,                         // speed
        20 * FRACUNIT,             // radius
        16 * FRACUNIT,             // height
        100,                       // mass
        0,                         // damage
        heretic_sfx_None,          // activesound
        MF_SPECIAL | MF_NOTDMATCH, // flags
        0                          // flags2
    },

    {
        // MT_AMGWNDWIMPY
        10,               // doomednum
        HERETIC_S_AMG1,   // spawnstate
        AMMO_GWND_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMGWNDHEFTY
        12,               // doomednum
        HERETIC_S_AMG2_1, // spawnstate
        AMMO_GWND_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMMACEWIMPY
        13,               // doomednum
        HERETIC_S_AMM1,   // spawnstate
        AMMO_MACE_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMMACEHEFTY
        16,               // doomednum
        HERETIC_S_AMM2,   // spawnstate
        AMMO_MACE_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMCBOWWIMPY
        18,               // doomednum
        HERETIC_S_AMC1,   // spawnstate
        AMMO_CBOW_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMCBOWHEFTY
        19,               // doomednum
        HERETIC_S_AMC2_1, // spawnstate
        AMMO_CBOW_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMSKRDWIMPY
        20,               // doomednum
        HERETIC_S_AMS1_1, // spawnstate
        AMMO_SKRD_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMSKRDHEFTY
        21,               // doomednum
        HERETIC_S_AMS2_1, // spawnstate
        AMMO_SKRD_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMPHRDWIMPY
        22,               // doomednum
        HERETIC_S_AMP1_1, // spawnstate
        AMMO_PHRD_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMPHRDHEFTY
        23,               // doomednum
        HERETIC_S_AMP2_1, // spawnstate
        AMMO_PHRD_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMBLSRWIMPY
        54,               // doomednum
        HERETIC_S_AMB1_1, // spawnstate
        AMMO_BLSR_WIMPY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_AMBLSRHEFTY
        55,               // doomednum
        HERETIC_S_AMB2_1, // spawnstate
        AMMO_BLSR_HEFTY,  // spawnhealth
        HERETIC_S_NULL,   // seestate
        heretic_sfx_None, // seesound
        8,                // reactiontime
        heretic_sfx_None, // attacksound
        HERETIC_S_NULL,   // painstate
        0,                // painchance
        heretic_sfx_None, // painsound
        HERETIC_S_NULL,   // meleestate
        HERETIC_S_NULL,   // missilestate
        HERETIC_S_NULL,   // crashstate
        HERETIC_S_NULL,   // deathstate
        HERETIC_S_NULL,   // xdeathstate
        heretic_sfx_None, // deathsound
        0,                // speed
        20 * FRACUNIT,    // radius
        16 * FRACUNIT,    // height
        100,              // mass
        0,                // damage
        heretic_sfx_None, // activesound
        MF_SPECIAL,       // flags
        0                 // flags2
    },

    {
        // MT_SOUNDWIND
        42,                          // doomednum
        HERETIC_S_SND_WIND,          // spawnstate
        1000,                        // spawnhealth
        HERETIC_S_NULL,              // seestate
        heretic_sfx_None,            // seesound
        8,                           // reactiontime
        heretic_sfx_None,            // attacksound
        HERETIC_S_NULL,              // painstate
        0,                           // painchance
        heretic_sfx_None,            // painsound
        HERETIC_S_NULL,              // meleestate
        HERETIC_S_NULL,              // missilestate
        HERETIC_S_NULL,              // crashstate
        HERETIC_S_NULL,              // deathstate
        HERETIC_S_NULL,              // xdeathstate
        heretic_sfx_None,            // deathsound
        0,                           // speed
        20 * FRACUNIT,               // radius
        16 * FRACUNIT,               // height
        100,                         // mass
        0,                           // damage
        heretic_sfx_None,            // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        0                            // flags2
    },

    {
        // MT_SOUNDWATERFALL
        41,                          // doomednum
        HERETIC_S_SND_WATERFALL,     // spawnstate
        1000,                        // spawnhealth
        HERETIC_S_NULL,              // seestate
        heretic_sfx_None,            // seesound
        8,                           // reactiontime
        heretic_sfx_None,            // attacksound
        HERETIC_S_NULL,              // painstate
        0,                           // painchance
        heretic_sfx_None,            // painsound
        HERETIC_S_NULL,              // meleestate
        HERETIC_S_NULL,              // missilestate
        HERETIC_S_NULL,              // crashstate
        HERETIC_S_NULL,              // deathstate
        HERETIC_S_NULL,              // xdeathstate
        heretic_sfx_None,            // deathsound
        0,                           // speed
        20 * FRACUNIT,               // radius
        16 * FRACUNIT,               // height
        100,                         // mass
        0,                           // damage
        heretic_sfx_None,            // activesound
        MF_NOBLOCKMAP | MF_NOSECTOR, // flags
        0                            // flags2
    }};
