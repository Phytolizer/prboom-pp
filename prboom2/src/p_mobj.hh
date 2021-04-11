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
 * DESCRIPTION:
 *      Map Objects, MObj, definition and handling.
 *
 *-----------------------------------------------------------------------------*/

#ifndef __P_MOBJ__
#define __P_MOBJ__

// Basics.
#include "doomtype.hh"
#include "m_fixed.hh"
#include "tables.hh"

// We need the thinker_t stuff.
#include "d_think.hh"

// We need the WAD data structure for Map things,
// from the THINGS lump.
#include "doomdata.hh"

// States are tied to finite states are
//  tied to animation frames.
// Needs precompiled tables/data structures.
#include "info.hh"

#include "dsda_mobj_extension.hh"

//
// NOTES: mobj_t
//
// mobj_ts are used to tell the refresh where to draw an image,
// tell the world simulation when objects are contacted,
// and tell the sound driver how to position a sound.
//
// The refresh uses the next and prev links to follow
// lists of things in sectors as they are being drawn.
// The sprite, frame, and angle elements determine which patch_t
// is used to draw the sprite if it is visible.
// The sprite and frame values are allmost allways set
// from state_t structures.
// The statescr.exe utility generates the states.h and states.c
// files that contain the sprite/frame numbers from the
// statescr.txt source file.
// The xyz origin point represents a point at the bottom middle
// of the sprite (between the feet of a biped).
// This is the default origin position for patch_ts grabbed
// with lumpy.exe.
// A walking creature will have its z equal to the floor
// it is standing on.
//
// The sound code uses the x,y, and subsector fields
// to do stereo positioning of any sound effited by the mobj_t.
//
// The play simulation uses the blocklinks, x,y,z, radius, height
// to determine when mobj_ts are touching each other,
// touching lines in the map, or hit by trace lines (gunshots,
// lines of sight, etc).
// The mobj_t->flags element has various bit flags
// used by the simulation.
//
// Every mobj_t is linked into a single sector
// based on its origin coordinates.
// The subsector_t is found with R_PointInSubsector(x,y),
// and the sector_t can be found with subsector->sector.
// The sector links are only used by the rendering code,
// the play simulation does not care about them at all.
//
// Any mobj_t that needs to be acted upon by something else
// in the play world (block movement, be shot, etc) will also
// need to be linked into the blockmap.
// If the thing has the MF_NOBLOCK flag set, it will not use
// the block links. It can still interact with other things,
// but only as the instigator (missiles will run into other
// things, but nothing can run into a missile).
// Each block in the grid is 128*128 units, and knows about
// every line_t that it contains a piece of, and every
// interactable mobj_t that has its origin contained.
//
// A valid mobj_t is a mobj_t that has the proper subsector_t
// filled in for its xy coordinates and is linked into the
// sector from which the subsector was made, or has the
// MF_NOSECTOR flag set (the subsector_t needs to be valid
// even if MF_NOSECTOR is set), and is linked into a blockmap
// block or has the MF_NOBLOCKMAP flag set.
// Links should only be modified by the P_[Un]SetThingPosition()
// functions.
// Do not change the MF_NO? flags while a thing is valid.
//
// Any questions?
//

//
// Misc. mobj flags
//

// Call P_SpecialThing when touched.
#define MF_SPECIAL (uint_64_t)(0x0000000000000001)
// Blocks.
#define MF_SOLID (uint_64_t)(0x0000000000000002)
// Can be hit.
#define MF_SHOOTABLE (uint_64_t)(0x0000000000000004)
// Don't use the sector links (invisible but touchable).
#define MF_NOSECTOR (uint_64_t)(0x0000000000000008)
// Don't use the blocklinks (inert but displayable)
#define MF_NOBLOCKMAP (uint_64_t)(0x0000000000000010)

// Not to be activated by sound, deaf monster.
#define MF_AMBUSH (uint_64_t)(0x0000000000000020)
// Will try to attack right back.
#define MF_JUSTHIT (uint_64_t)(0x0000000000000040)
// Will take at least one step before attacking.
#define MF_JUSTATTACKED (uint_64_t)(0x0000000000000080)
// On level spawning (initial position),
//  hang from ceiling instead of stand on floor.
#define MF_SPAWNCEILING (uint_64_t)(0x0000000000000100)
// Don't apply gravity (every tic),
//  that is, object will float, keeping current height
//  or changing it actively.
#define MF_NOGRAVITY (uint_64_t)(0x0000000000000200)

// Movement flags.
// This allows jumps from high places.
#define MF_DROPOFF (uint_64_t)(0x0000000000000400)
// For players, will pick up items.
#define MF_PICKUP (uint_64_t)(0x0000000000000800)
// Player cheat. ???
#define MF_NOCLIP (uint_64_t)(0x0000000000001000)
// Player: keep info about sliding along walls.
#define MF_SLIDE (uint_64_t)(0x0000000000002000)
// Allow moves to any height, no gravity.
// For active floaters, e.g. cacodemons, pain elementals.
#define MF_FLOAT (uint_64_t)(0x0000000000004000)
// Don't cross lines
//   ??? or look at heights on teleport.
#define MF_TELEPORT (uint_64_t)(0x0000000000008000)
// Don't hit same species, explode on block.
// Player missiles as well as fireballs of various kinds.
#define MF_MISSILE (uint_64_t)(0x0000000000010000)
// Dropped by a demon, not level spawned.
// E.g. ammo clips dropped by dying former humans.
#define MF_DROPPED (uint_64_t)(0x0000000000020000)
// Use fuzzy draw (shadow demons or spectres),
//  temporary player invisibility powerup.
#define MF_SHADOW (uint_64_t)(0x0000000000040000)
// Flag: don't bleed when shot (use puff),
//  barrels and shootable furniture shall not bleed.
#define MF_NOBLOOD (uint_64_t)(0x0000000000080000)
// Don't stop moving halfway off a step,
//  that is, have dead bodies slide down all the way.
#define MF_CORPSE (uint_64_t)(0x0000000000100000)
// Floating to a height for a move, ???
//  don't auto float to target's height.
#define MF_INFLOAT (uint_64_t)(0x0000000000200000)

// On kill, count this enemy object
//  towards intermission kill total.
// Happy gathering.
#define MF_COUNTKILL (uint_64_t)(0x0000000000400000)

// On picking up, count this item object
//  towards intermission item total.
#define MF_COUNTITEM (uint_64_t)(0x0000000000800000)

// Special handling: skull in flight.
// Neither a cacodemon nor a missile.
#define MF_SKULLFLY (uint_64_t)(0x0000000001000000)

// Don't spawn this object
//  in death match mode (e.g. key cards).
#define MF_NOTDEATHMATCH (uint_64_t)(0x0000000002000000)

// Player sprites in multiplayer modes are modified
//  using an internal color lookup table for re-indexing.
// If 0x4 0x8 or 0xc,
//  use a translation table for player colormaps
#define MF_TRANSLATION (uint_64_t)(0x000000000c000000)
#define MF_TRANSLATION1 (uint_64_t)(0x0000000004000000)
#define MF_TRANSLATION2 (uint_64_t)(0x0000000008000000)
// Hmm ???.
#define MF_TRANSSHIFT 26

#define MF_UNUSED2 (uint_64_t)(0x0000000010000000)
#define MF_UNUSED3 (uint_64_t)(0x0000000020000000)

// Translucent sprite?                                          // phares
#define MF_TRANSLUCENT (uint_64_t)(0x0000000040000000)

// this is free            LONGLONG(0x0000000100000000)

// these are greater than an int. That's why the flags below are now uint_64_t

#define MF_TOUCHY LONGLONG(0x0000000100000000)
#define MF_BOUNCES LONGLONG(0x0000000200000000)
#define MF_FRIEND LONGLONG(0x0000000400000000)

#define MF_RESSURECTED LONGLONG(0x0000001000000000)
#define MF_NO_DEPTH_TEST LONGLONG(0x0000002000000000)
#define MF_FOREGROUND LONGLONG(0x0000004000000000)
#define MF_PLAYERSPRITE LONGLONG(0x0000008000000000)

// This actor not targetted when it hurts something else
#define MF_NOTARGET LONGLONG(0x0000010000000000)
// fly mode is active
#define MF_FLY LONGLONG(0x0000020000000000)
// [FG] colored blood and gibs
#define MF_COLOREDBLOOD LONGLONG(0x0000040000000000)

#define ALIVE(thing)                                                           \
    ((thing->health > 0) &&                                                    \
     ((thing->flags & (MF_COUNTKILL | MF_CORPSE | MF_RESSURECTED)) ==          \
      MF_COUNTKILL))

// killough 9/15/98: Same, but internal flags, not intended for .deh
// (some degree of opaqueness is good, to avoid compatibility woes)

enum
{
    MIF_FALLING = 1, // Object is falling
    MIF_ARMED = 2,   // Object is armed (for MF_TOUCHY objects)
};

struct mobj_t;

// heretic
typedef struct
{
    int i;
    mobj_t *m;
} specialval_t;

// Map Object definition.
//
//
// killough 2/20/98:
//
// WARNING: Special steps must be taken in p_saveg.c if C pointers are added to
// this mobj_s struct, or else savegames will crash when loaded. See p_saveg.c.
// Do not add "struct mobj_s *fooptr" without adding code to p_saveg.c to
// convert the pointers to ordinals and back for savegames. This was the whole
// reason behind monsters going to sleep when loading savegames (the "target"
// pointer was simply nullified after loading, to prevent Doom from crashing),
// and the whole reason behind loadgames crashing on savegames of AV attacks.
//

// killough 9/8/98: changed some fields to shorts,
// for better memory usage (if only for cache).
/* cph 2006/08/28 - move Prev[XYZ] fields to the end of the struct. Add any
 * other new fields to the end, and make sure you don't break savegames! */

struct player_t;

struct mobj_t
{
    // List: thinker links.
    thinker_t thinker;

    // Info for drawing: position.
    fixed_t x;
    fixed_t y;
    fixed_t z;

    // More list: links in sector (if needed)
    mobj_t *snext;
    mobj_t **sprev; // killough 8/10/98: change to ptr-to-ptr

    // More drawing info: to determine current sprite.
    angle_t angle;      // orientation
    spritenum_t sprite; // used to find patch_t and flip value
    int frame;          // might be ORed with FF_FULLBRIGHT

    // Interaction info, by BLOCKMAP.
    // Links in blocks (if needed).
    mobj_t *bnext;
    mobj_t **bprev; // killough 8/11/98: change to ptr-to-ptr

    struct subsector_s *subsector;

    // The closest interval over all contacted Sectors.
    fixed_t floorz;
    fixed_t ceilingz;

    // killough 11/98: the lowest floor over all contacted Sectors.
    fixed_t dropoffz;

    // For movement checking.
    fixed_t radius;
    fixed_t height;

    // Momentums, used to update position.
    fixed_t momx;
    fixed_t momy;
    fixed_t momz;

    // If == validcount, already checked.
    int validcount;

    mobjtype_t type;
    mobjinfo_t *info; // &mobjinfo[mobj->type]

    int tics; // state tic counter
    state_t *state;
    uint_64_t flags;
    int intflags; // killough 9/15/98: internal flags
    int health;

    // Movement direction, movement generation (zig-zagging).
    short movedir;     // 0-7
    short movecount;   // when 0, select a new dir
    short strafecount; // killough 9/8/98: monster strafing

    // Thing being chased/attacked (or nullptr),
    // also the originator for missiles.
    mobj_t *target;

    // Reaction time: if non 0, don't attack yet.
    // Used by player to freeze a bit after teleporting.
    short reactiontime;

    // If >0, the current target will be chased no
    // matter what (even if shot by another object)
    short threshold;

    // killough 9/9/98: How long a monster pursues a target.
    short pursuecount;

    short gear; // killough 11/98: used in torque simulation

    // Additional info record for player avatars only.
    // Only valid if type == MT_PLAYER
    player_t *player;

    // Player number last looked for.
    short lastlook;

    // For nightmare respawn.
    mapthing_t spawnpoint;

    // Thing being chased/attacked for tracers.
    mobj_t *tracer;

    // new field: last known enemy -- killough 2/15/98
    mobj_t *lastenemy;

    // killough 8/2/98: friction properties part of sectors,
    // not objects -- removed friction properties from here
    // e6y: restored friction properties here
    // Friction values for the sector the object is in
    int friction; // phares 3/17/98
    int movefactor;

    // a linked list of sectors where this object appears
    struct msecnode_s *touching_sectorlist; // phares 3/14/98

    fixed_t PrevX;
    fixed_t PrevY;
    fixed_t PrevZ;

    // e6y
    angle_t pitch; // orientation
    int index;
    short patch_width;

    int iden_nums; // hi word stores thing num, low word identifier num

    fixed_t pad; // cph - needed so I can get the size unambiguously on amd64

    dsda_mobj_extension_t dsda_extension;

    // heretic
    int damage;            // For missiles
    int flags2;            // Heretic flags
    specialval_t special1; // Special info
    specialval_t special2; // Special info

    // SEE WARNING ABOVE ABOUT POINTER FIELDS!!!
};

// External declarations (fomerly in p_local.h) -- killough 5/2/98

#define VIEWHEIGHT (41 * FRACUNIT)

#define GRAVITY FRACUNIT
#define MAXMOVE (30 * FRACUNIT)

#define ONFLOORZ INT_MIN
#define ONCEILINGZ INT_MAX
#define FLOATRANDZ (INT_MAX - 1)

// Time interval for item respawning.
#define ITEMQUESIZE 128

#define FLOATSPEED (FRACUNIT * 4)
#define STOPSPEED (FRACUNIT / 16)

// killough 11/98:
// For torque simulation:

#define OVERDRIVE 6
#define MAXGEAR (OVERDRIVE + 16)

// killough 11/98:
// Whether an object is "sentient" or not. Used for environmental influences.
#define sentient(mobj) ((mobj)->health > 0 && (mobj)->info->seestate)

extern int iquehead;
extern int iquetail;

// [FG] colored blood and gibs
extern dboolean colored_blood;
extern int one_shot_probability;
extern dboolean buddha_mode;

struct mobj_t;

mobj_t *P_SubstNullMobj(mobj_t *th);
void P_RespawnSpecials(void);
mobj_t *P_SpawnMobj(fixed_t x, fixed_t y, fixed_t z, mobjtype_t type);
void P_RemoveMobj(mobj_t *th);
dboolean P_SetMobjState(mobj_t *mobj, statenum_t state);
void P_MobjThinker(mobj_t *mobj);
void P_SpawnPuff(fixed_t x, fixed_t y, fixed_t z);
uint_64_t P_ColoredBlood(mobj_t *bleeder);
void P_SpawnBlood(fixed_t x, fixed_t y, fixed_t z, int damage, mobj_t *bleeder);
mobj_t *P_SpawnMissile(mobj_t *source, mobj_t *dest, mobjtype_t type);
mobj_t *P_SpawnPlayerMissile(mobj_t *source, mobjtype_t type);
dboolean P_IsDoomnumAllowed(int doomnum);
mobj_t *P_SpawnMapThing(const mapthing_t &mthing, int index);
void P_SpawnPlayer(int n, const mapthing_t &mthing);
dboolean P_CheckMissileSpawn(mobj_t *); // killough 8/2/98
void P_ExplodeMissile(mobj_t *);        // killough

// heretic

// --- mobj.flags2 ---

#define MF2_LOGRAV 0x00000001 // alternate gravity setting
#define MF2_WINDTHRUST                                                         \
    0x00000002                     // gets pushed around by the wind
                                   // specials
#define MF2_FLOORBOUNCE 0x00000004 // bounces off the floor
#define MF2_THRUGHOST 0x00000008   // missile will pass through ghosts
#define MF2_FLY 0x00000010         // fly mode is active
#define MF2_FOOTCLIP 0x00000020    // if feet are allowed to be clipped
#define MF2_SPAWNFLOAT 0x00000040  // spawn random float z
#define MF2_NOTELEPORT 0x00000080  // does not teleport
#define MF2_RIP                                                                \
    0x00000100 // missile rips through solid
               // targets
#define MF2_PUSHABLE                                                           \
    0x00000200               // can be pushed by other moving
                             // mobjs
#define MF2_SLIDE 0x00000400 // slides against walls
#define MF2_ONMOBJ                                                             \
    0x00000800 // mobj is resting on top of another
               // mobj
#define MF2_PASSMOBJ                                                           \
    0x00001000                        // Enable z block checking.  If on,
                                      // this flag will allow the mobj to
                                      // pass over/under other mobjs.
#define MF2_CANNOTPUSH 0x00002000     // cannot push other pushable mobjs
#define MF2_FEETARECLIPPED 0x00004000 // a mobj's feet are now being cut
#define MF2_BOSS 0x00008000           // mobj is a major boss
#define MF2_FIREDAMAGE 0x00010000     // does fire damage
#define MF2_NODMGTHRUST                                                        \
    0x00020000                   // does not thrust target when
                                 // damaging
#define MF2_TELESTOMP 0x00040000 // mobj can stomp another
#define MF2_FLOATBOB 0x00080000  // use float bobbing z movement
#define MF2_DONTDRAW 0X00100000  // don't generate a vissprite

#define AMMO_GWND_WIMPY 10
#define AMMO_GWND_HEFTY 50
#define AMMO_CBOW_WIMPY 5
#define AMMO_CBOW_HEFTY 20
#define AMMO_BLSR_WIMPY 10
#define AMMO_BLSR_HEFTY 25
#define AMMO_SKRD_WIMPY 20
#define AMMO_SKRD_HEFTY 100
#define AMMO_PHRD_WIMPY 1
#define AMMO_PHRD_HEFTY 10
#define AMMO_MACE_WIMPY 20
#define AMMO_MACE_HEFTY 100

extern mobj_t *MissileMobj;

void P_BlasterMobjThinker(mobj_t *mobj);
mobj_t *P_SpawnMissileAngle(mobj_t *source, mobjtype_t type, angle_t angle,
                            fixed_t momz);
dboolean P_SetMobjStateNF(mobj_t *mobj, statenum_t state);
void P_ThrustMobj(mobj_t *mo, angle_t angle, fixed_t move);
dboolean P_SeekerMissile(mobj_t *actor, angle_t thresh, angle_t turnMax);
mobj_t *P_SPMAngle(mobj_t *source, mobjtype_t type, angle_t angle);
int P_HitFloor(mobj_t *thing);
int P_GetThingFloorType(mobj_t *thing);
int P_FaceMobj(mobj_t *source, mobj_t *target, angle_t *delta);
void P_BloodSplatter(fixed_t x, fixed_t y, fixed_t z, mobj_t *originator);
void P_RipperBlood(mobj_t *mo);
dboolean Heretic_P_SetMobjState(mobj_t *mobj, statenum_t state);
void P_FloorBounceMissile(mobj_t *mo);
void Heretic_P_SpawnPuff(fixed_t x, fixed_t y, fixed_t z);

#endif
