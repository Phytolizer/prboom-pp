/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION: Main game control interface.
 *-----------------------------------------------------------------------------*/

#ifndef __G_GAME__
#define __G_GAME__

#include <string>

#include "doomdef.hh"
#include "d_event.hh"
#include "d_ticcmd.hh"

//
// GAME
//

#define DEMOMARKER 0x80

// killough 5/2/98: number of bytes reserved for saving options
#define GAME_OPTION_SIZE 64

dboolean G_Responder(event_t *ev);
dboolean G_CheckDemoStatus(void);
void G_DeathMatchSpawnPlayer(int playernum);
void G_InitNew(skill_t skill, int episode, int map);
void G_DeferedInitNew(skill_t skill, int episode, int map);
void G_DeferedPlayDemo(const char *demo);       // CPhipps - const
void G_LoadGame(int slot, dboolean is_command); // killough 5/15/98
void G_ForcedLoadGame(void); // killough 5/15/98: forced loadgames
void G_DoLoadGame(void);
void G_SaveGame(int slot, char *description); // Called by M_Responder.
void G_BeginRecording(void);
// CPhipps - const on these string params
void G_RecordDemo(const char *name); // Only called by startup code.
void G_ExitLevel(void);
void G_SecretExitLevel(void);
void G_WorldDone(void);
void G_EndGame(void); /* cph - make m_menu.c call a G_* function for this */
void G_Ticker(void);
void G_ScreenShot(void);
void G_ReloadDefaults(void); // killough 3/1/98: loads game defaults
int G_SaveGameName(char *, size_t, int,
                   dboolean); /* killough 3/22/98: sets savegame filename */
void G_SetFastParms(int);     // killough 4/10/98: sets -fast parameters
void G_DoNewGame(void);
void G_DoReborn(int playernum);
void G_DoPlayDemo(void);
void G_DoCompleted(void);
void G_ReadDemoContinueTiccmd(ticcmd_t *cmd); // e6y
void G_ReadDemoTiccmd(ticcmd_t *cmd);
void G_WriteDemoTiccmd(ticcmd_t *cmd);
void G_DoWorldDone(void);
void G_Compatibility(void);
const byte *G_ReadOptions(
    const byte *demo_pointer); /* killough 3/1/98 - cph: const byte* */
byte *G_WriteOptions(byte *demo_pointer); // killough 3/1/98
void G_PlayerReborn(int player);
void G_RestartLevel(void); // CPhipps - menu involked level restart
void G_DoVictory(void);
void G_BuildTiccmd(ticcmd_t *cmd); // CPhipps - move decl to header
void G_ChangedPlayerColour(
    int pn, int cl); // CPhipps - On-the-fly player colour changing
void G_MakeSpecialEvent(buttoncode_t bc, ...); /* cph - new event stuff */
int G_ValidateMapName(const std::string &mapname, int *pEpi, int *pMap);

// e6y
extern dboolean democontinue;
extern char democontinuename[];
void G_CheckDemoContinue(void);
void G_SetSpeed(void);

// e6y
#define RDH_SAFE 0x00000001
#define RDH_SKIP_HEADER 0x00000002
const byte *G_ReadDemoHeaderEx(const byte *demo_pointer, size_t size,
                               unsigned int params);
const byte *G_ReadDemoHeader(const byte *demo_pointer, size_t size);
void G_CalculateDemoParams(const byte *demo_p);

// killough 1/18/98: Doom-style printf;   killough 4/25/98: add gcc attributes
// CPhipps - renames to doom_printf to avoid name collision with glibc
void doom_printf(const char *, ...) __attribute__((format(printf, 1, 2)));

// killough 5/2/98: moved from m_misc.c:

extern int key_forward;
extern int key_backward;
extern int autorun; // always running?                   // phares

extern int defaultskill;       // jff 3/24/98 default skill
extern dboolean haswolflevels; // jff 4/18/98 wolf levels present
extern dboolean secretexit;

extern int bodyquesize; // killough 2/8/98: adustable corpse limit

// killough 5/2/98: moved from d_deh.c:
// Par times (new item with BOOM) - from g_game.c
extern int pars[5][10]; // hardcoded array size
extern int cpars[];     // hardcoded array size
// CPhipps - Make savedesciption visible in wider scope
#define SAVEDESCLEN 32
extern char savedescription[SAVEDESCLEN]; // Description to save in savegame

/* cph - compatibility level strings */
extern const char *comp_lev_str[];

// e6y
// There is a new command-line switch "-shorttics".
// This makes it possible to practice routes and tricks
// (e.g. glides, where this makes a significant difference)
// with the same mouse behaviour as when recording,
// but without having to be recording every time.
extern int shorttics;

// e6y: for r_demo.c
extern int longtics;
extern int bytes_per_tic;

extern dboolean boom_autoswitch;
extern dboolean done_autoswitch;

#define singleplayer                                                           \
    (!demorecording && !demoplayback && !democontinue && !netgame)
#define comperr(i)                                                             \
    (default_comperr[i] && !demorecording && !demoplayback && !democontinue && \
     !netgame)

#endif
