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
 *      Archiving: SaveGame I/O.
 *
 *-----------------------------------------------------------------------------*/

#include <cstdint>

#include "am_map.hh"
#include "doomstat.hh"
#include "e6y.hh" //e6y
#include "lprintf.hh"
#include "m_random.hh"
#include "p_enemy.hh"
#include "p_maputl.hh"
#include "p_saveg.hh"
#include "p_spec.hh"
#include "p_tick.hh"
#include "r_main.hh"
#include "s_advsound.hh"

#include "dsda/msecnode.hh"

#define MARKED_FOR_DELETION -2

byte *save_p;

// Pads save_p to a 4-byte boundary
//  so that the load/save works on SGI&Gecko.
#define PADSAVEP()                                                             \
    do                                                                         \
    {                                                                          \
        save_p += (4 - ((intptr_t)save_p & 3)) & 3;                            \
    } while (0)
//
// P_ArchivePlayers
//
void P_ArchivePlayers()
{
    int i;

    CheckSaveGame(sizeof(player_t) * MAXPLAYERS); // killough
    for (i = 0; i < MAXPLAYERS; i++)
    {
        if (playeringame[i])
        {
            int j;
            player_t *dest;

            PADSAVEP();
            dest = (player_t *)save_p;
            memcpy(dest, &players[i], sizeof(player_t));
            save_p += sizeof(player_t);
            for (j = 0; j < NUMPSPRITES; j++)
            {
                if (dest->psprites[j].state)
                {
                    dest->psprites[j].state =
                        (state_t *)(dest->psprites[j].state - states);
                }
            }
        }
    }
}

//
// P_UnArchivePlayers
//
void P_UnArchivePlayers()
{
    int i;

    for (i = 0; i < MAXPLAYERS; i++)
    {
        if (playeringame[i])
        {
            int j;

            PADSAVEP();

            memcpy(&players[i], save_p, sizeof(player_t));
            save_p += sizeof(player_t);

            // will be set when unarc thinker
            players[i].mo = nullptr;
            players[i].message = nullptr;
            players[i].attacker = nullptr;
            // HERETIC_TODO: does the rain need to be remembered?
            players[i].rain1 = nullptr;
            players[i].rain2 = nullptr;

            for (j = 0; j < NUMPSPRITES; j++)
            {
                if (players[i].psprites[j].state)
                {
                    players[i].psprites[j].state =
                        &states[(size_t)players[i].psprites[j].state];
                }
            }
        }
    }
}

//
// P_ArchiveWorld
//
void P_ArchiveWorld()
{
    int i;
    const sector_t *sec;
    const line_t *li;
    const side_t *si;
    short *put;

    // killough 3/22/98: fix bug caused by hoisting save_p too early
    // killough 10/98: adjust size for changes below
    size_t size =
        (sizeof(short) * 5 + sizeof sec->floorheight + sizeof sec->ceilingheight
        ) * numsectors +
        sizeof(short) * 3 * numlines + 4 + 2;

    for (i = 0; i < numlines; i++)
    {
        if (lines[i].sidenum[0] != NO_INDEX)
        {
            size += sizeof(short) * 3 + sizeof si->textureoffset +
                    sizeof si->rowoffset;
        }
        if (lines[i].sidenum[1] != NO_INDEX)
        {
            size += sizeof(short) * 3 + sizeof si->textureoffset +
                    sizeof si->rowoffset;
        }
    }

    CheckSaveGame(size); // killough

    PADSAVEP(); // killough 3/22/98

    put = (short *)save_p;

    // do sectors
    for (i = 0, sec = sectors; i < numsectors; i++, sec++)
    {
        // killough 10/98: save full floor & ceiling heights, including fraction
        memcpy(put, &sec->floorheight, sizeof sec->floorheight);
        put =
            static_cast<short *>((void *)((char *)put + sizeof sec->floorheight)
            );
        memcpy(put, &sec->ceilingheight, sizeof sec->ceilingheight);
        put = static_cast<short *>(
            (void *)((char *)put + sizeof sec->ceilingheight)
        );

        *put++ = sec->floorpic;
        *put++ = sec->ceilingpic;
        *put++ = sec->lightlevel;
        *put++ = sec->special; // needed?   yes -- transfer types
        *put++ = sec->tag;     // needed?   need them -- killough
    }

    // do lines
    for (i = 0, li = lines; i < numlines; i++, li++)
    {
        int j;

        *put++ = li->flags;
        *put++ = li->special;
        *put++ = li->tag;

        for (j = 0; j < 2; j++)
        {
            if (li->sidenum[j] != NO_INDEX)
            {
                si = &sides[li->sidenum[j]];

                // killough 10/98: save full sidedef offsets,
                // preserving fractional scroll offsets

                memcpy(put, &si->textureoffset, sizeof si->textureoffset);
                put = static_cast<short *>(
                    (void *)((char *)put + sizeof si->textureoffset)
                );
                memcpy(put, &si->rowoffset, sizeof si->rowoffset);
                put = static_cast<short *>(
                    (void *)((char *)put + sizeof si->rowoffset)
                );

                *put++ = si->toptexture;
                *put++ = si->bottomtexture;
                *put++ = si->midtexture;
            }
        }
    }

    *put++ = static_cast<short>(musinfo.current_item);

    save_p = (byte *)put;
}

//
// P_UnArchiveWorld
//
void P_UnArchiveWorld()
{
    int i;
    sector_t *sec;
    line_t *li;
    short *get;

    PADSAVEP(); // killough 3/22/98

    get = (short *)save_p;

    // do sectors
    for (i = 0, sec = sectors; i < numsectors; i++, sec++)
    {
        // killough 10/98: load full floor & ceiling heights, including
        // fractions

        memcpy(&sec->floorheight, get, sizeof sec->floorheight);
        get =
            static_cast<short *>((void *)((char *)get + sizeof sec->floorheight)
            );
        memcpy(&sec->ceilingheight, get, sizeof sec->ceilingheight);
        get = static_cast<short *>(
            (void *)((char *)get + sizeof sec->ceilingheight)
        );

        sec->floorpic = *get++;
        sec->ceilingpic = *get++;
        sec->lightlevel = *get++;
        sec->special = *get++;
        sec->tag = *get++;
        sec->ceilingdata =
            nullptr; // jff 2/22/98 now three thinker fields, not two
        sec->floordata = nullptr;
        sec->lightingdata = nullptr;
        sec->soundtarget = nullptr;
    }

    // do lines
    for (i = 0, li = lines; i < numlines; i++, li++)
    {
        int j;

        li->flags = *get++;
        li->special = *get++;
        li->tag = *get++;
        for (j = 0; j < 2; j++)
        {
            if (li->sidenum[j] != NO_INDEX)
            {
                side_t *si = &sides[li->sidenum[j]];

                // killough 10/98: load full sidedef offsets, including
                // fractions

                memcpy(&si->textureoffset, get, sizeof si->textureoffset);
                get = static_cast<short *>(
                    (void *)((char *)get + sizeof si->textureoffset)
                );
                memcpy(&si->rowoffset, get, sizeof si->rowoffset);
                get = static_cast<short *>(
                    (void *)((char *)get + sizeof si->rowoffset)
                );

                si->toptexture = *get++;
                si->bottomtexture = *get++;
                si->midtexture = *get++;
            }
        }
    }

    musinfo.current_item = *get++;

    save_p = (byte *)get;
}

//
// Thinkers
//

using thinkerclass_t = enum
{
    tc_end,
    tc_mobj
};

// phares 9/13/98: Moved this code outside of P_ArchiveThinkers so the
// thinker indices could be used by the code that saves sector info.

static int number_of_thinkers;

static dboolean P_IsMobjThinker(thinker_t *thinker)
{
    return thinker->function == P_MobjThinker ||
           thinker->function == P_BlasterMobjThinker ||
           (thinker->function == P_RemoveThinkerDelayed &&
            thinker->references != 0);
}

void P_ThinkerToIndex()
{
    thinker_t *th;

    // killough 2/14/98:
    // count the number of thinkers, and mark each one with its index, using
    // the prev field as a placeholder, since it can be restored later.

    number_of_thinkers = 0;
    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (P_IsMobjThinker(th))
        {
            th->prev = (thinker_t *)(intptr_t)++number_of_thinkers;
        }
    }
}

// phares 9/13/98: Moved this code outside of P_ArchiveThinkers so the
// thinker indices could be used by the code that saves sector info.

void P_IndexToThinker()
{
    // killough 2/14/98: restore prev pointers
    thinker_t *th;
    thinker_t *prev = &thinkercap;

    for (th = thinkercap.next; th != &thinkercap; prev = th, th = th->next)
    {
        th->prev = prev;
    }
}

/*
 * killough 11/98
 *
 * Same as P_SetTarget() in p_tick.c, except that the target is nullified
 * first, so that no old target's reference count is decreased (when loading
 * savegames, old targets are indices, not really pointers to targets).
 */

static void P_SetNewTarget(mobj_t **mop, mobj_t *targ)
{
    *mop = nullptr;
    P_SetTarget(mop, targ);
}

// savegame file stores ints in the corresponding * field; this function
// safely casts them back to int.
int P_GetMobj(mobj_t *mi, size_t s)
{
    size_t i = (size_t)mi;
    if (i >= s)
    {
        I_Error("Corrupt savegame");
    }
    return i;
}

//
// Things to handle:
//
// T_MoveCeiling, (ceiling_t: sector_t * swizzle), - active list
// T_VerticalDoor, (vldoor_t: sector_t * swizzle),
// T_MoveFloor, (floormove_t: sector_t * swizzle),
// T_LightFlash, (lightflash_t: sector_t * swizzle),
// T_StrobeFlash, (strobe_t: sector_t *),
// T_Glow, (glow_t: sector_t *),
// T_PlatRaise, (plat_t: sector_t *), - active list
// T_MoveElevator, (plat_t: sector_t *), - active list      // jff 2/22/98
// T_Scroll                                                 // killough 3/7/98
// T_Pusher                                                 // phares 3/22/98
// T_FireFlicker                                            // killough 10/4/98
//

// killough 2/16/98: save/restore random number generator state information

void P_ArchiveRNG()
{
    CheckSaveGame(sizeof rng);
    memcpy(save_p, &rng, sizeof rng);
    save_p += sizeof rng;
}

void P_UnArchiveRNG()
{
    memcpy(&rng, save_p, sizeof rng);
    save_p += sizeof rng;
}

// killough 2/22/98: Save/restore automap state
// killough 2/22/98: Save/restore automap state
void P_ArchiveMap()
{
    int i, zero = 0, one = 1;
    CheckSaveGame(
        2 * sizeof zero + sizeof markpointnum +
        markpointnum * (sizeof(markpoints[0].x) + sizeof(markpoints[0].y)) +
        sizeof automapmode + sizeof one
    );

    memcpy(save_p, &automapmode, sizeof automapmode);
    save_p += sizeof automapmode;
    memcpy(save_p, &one, sizeof one); // CPhipps - used to be viewactive, now
    save_p += sizeof one;             // that's worked out locally by D_Display
    memcpy(save_p, &zero, sizeof zero); // CPhipps - used to be followplayer
    save_p += sizeof zero;              //  that is now part of automapmode
    memcpy(
        save_p, &zero,
        sizeof zero
    ); // CPhipps - used to be automap_grid, ditto
    save_p += sizeof zero;
    memcpy(save_p, &markpointnum, sizeof markpointnum);
    save_p += sizeof markpointnum;

    for (i = 0; i < markpointnum; i++)
    {
        memcpy(save_p, &markpoints[i].x, sizeof(markpoints[i].x));
        save_p += sizeof(markpoints[i].x);
        memcpy(save_p, &markpoints[i].y, sizeof(markpoints[i].y));
        save_p += sizeof(markpoints[i].y);
    }
}

void P_UnArchiveMap()
{
    int unused;
    memcpy(&automapmode, save_p, sizeof automapmode);
    save_p += sizeof automapmode;
    memcpy(&unused, save_p, sizeof unused);
    save_p += sizeof unused;
    memcpy(&unused, save_p, sizeof unused);
    save_p += sizeof unused;
    memcpy(&unused, save_p, sizeof unused);
    save_p += sizeof unused;

    if (automapmode & am_active)
    {
        AM_Start();
    }

    memcpy(&markpointnum, save_p, sizeof markpointnum);
    save_p += sizeof markpointnum;

    if (markpointnum)
    {
        int i;
        while (markpointnum >= markpointnum_max)
        {
            markpoints = static_cast<markpoint_t *>(realloc(
                markpoints,
                sizeof *markpoints *
                    (markpointnum_max =
                         markpointnum_max ? markpointnum_max * 2 : 16)
            ));
        }

        for (i = 0; i < markpointnum; i++)
        {
            memcpy(&markpoints[i].x, save_p, sizeof(markpoints[i].x));
            save_p += sizeof(markpoints[i].x);
            memcpy(&markpoints[i].y, save_p, sizeof(markpoints[i].y));
            save_p += sizeof(markpoints[i].y);

            AM_setMarkParams(i);
        }
    }
}

void P_ArchiveThinkerSubclass(th_class cls)
{
    int count;
    thinker_t *cap, *th;

    count = 0;
    cap = &thinkerclasscap[cls];
    for (th = cap->cnext; th != cap; th = th->cnext)
    {
        count++;
    }

    CheckSaveGame(count * sizeof(mobj_t *) + sizeof(count));

    memcpy(save_p, &count, sizeof(count));
    save_p += sizeof(count);

    for (th = cap->cnext; th != cap; th = th->cnext)
    {
        memcpy(save_p, &th->prev, sizeof(th->prev));
        save_p += sizeof(th->prev);
    }
}

void P_ArchiveThinkerSubclasses()
{
    // Other subclass ordering is not relevant
    P_ArchiveThinkerSubclass(th_friends);
    P_ArchiveThinkerSubclass(th_enemies);
}

void P_UnArchiveThinkerSubclass(th_class cls, mobj_t **mobj_p, int mobj_count)
{
    int i;
    int count;

    // Reset thinker subclass list
    thinkerclasscap[cls].cprev->cnext = thinkerclasscap[cls].cnext;
    thinkerclasscap[cls].cnext->cprev = thinkerclasscap[cls].cprev;
    thinkerclasscap[cls].cprev = thinkerclasscap[cls].cnext =
        &thinkerclasscap[cls];

    memcpy(&count, save_p, sizeof(count));
    save_p += sizeof(count);

    for (i = 0; i < count; ++i)
    {
        thinker_t *th;
        mobj_t *mobj;

        memcpy(&mobj, save_p, sizeof(mobj));
        save_p += sizeof(mobj);

        mobj = mobj_p[P_GetMobj(mobj, mobj_count + 1)];

        if (mobj)
        {
            // remove mobj from current subclass list
            th = mobj->thinker.cnext;
            if (th != nullptr)
            {
                th->cprev = mobj->thinker.cprev;
                th->cprev->cnext = th;
            }

            th = &thinkerclasscap[cls];
            th->cprev->cnext = &mobj->thinker;
            mobj->thinker.cnext = th;
            mobj->thinker.cprev = th->cprev;
            th->cprev = &mobj->thinker;
        }
        else
        {
            I_Error("P_UnArchiveThinkerSubclass: mobj does not exist!\n");
        }
    }
}

void P_UnArchiveThinkerSubclasses(mobj_t **mobj_p, int mobj_count)
{
    P_UnArchiveThinkerSubclass(th_friends, mobj_p, mobj_count);
    P_UnArchiveThinkerSubclass(th_enemies, mobj_p, mobj_count);
}

extern mobj_t **blocklinks;
extern int bmapwidth;
extern int bmapheight;

void P_ArchiveBlockLinks()
{
    int i;
    int size;

    size = bmapwidth * bmapheight;

    for (i = 0; i < size; ++i)
    {
        int count = 0;
        mobj_t *mobj;

        mobj = blocklinks[i];
        while (mobj)
        {
            ++count;
            mobj = mobj->bnext;
        }

        CheckSaveGame(count * sizeof(mobj_t *) + sizeof(count));

        memcpy(save_p, &count, sizeof(count));
        save_p += sizeof(count);

        mobj = blocklinks[i];
        while (mobj)
        {
            memcpy(save_p, &mobj->thinker.prev, sizeof(mobj->thinker.prev));
            save_p += sizeof(mobj->thinker.prev);
            mobj = mobj->bnext;
        }
    }
}

void P_UnArchiveBlockLinks(mobj_t **mobj_p, int mobj_count)
{
    int i;
    int size;

    size = bmapwidth * bmapheight;

    for (i = 0; i < size; ++i)
    {
        int j;
        int count;
        mobj_t *mobj;
        mobj_t **bprev;

        memcpy(&count, save_p, sizeof(count));
        save_p += sizeof(count);

        bprev = &blocklinks[i];
        for (j = 0; j < count; ++j)
        {
            memcpy(&mobj, save_p, sizeof(mobj));
            save_p += sizeof(mobj);

            mobj = mobj_p[P_GetMobj(mobj, mobj_count + 1)];

            if (mobj)
            {
                *bprev = mobj;
                mobj->bprev = bprev;
                mobj->bnext = nullptr;
                bprev = &mobj->bnext;
            }
            else
            {
                I_Error("P_UnArchiveBlockLinks: mobj does not exist!\n");
            }
        }
    }
}

// dsda - fix save / load synchronization
// merges thinkerclass_t and specials_e
using true_thinkerclass_t = enum
{
    tc_true_mobj,
    tc_true_ceiling,
    tc_true_door,
    tc_true_floor,
    tc_true_plat,
    tc_true_flash,
    tc_true_strobe,
    tc_true_glow,
    tc_true_elevator,
    tc_true_scroll,
    tc_true_pusher,
    tc_true_flicker,
    tc_true_friction,
    tc_true_end
};

// dsda - fix save / load synchronization
// merges P_ArchiveThinkers & P_ArchiveSpecials
void P_TrueArchiveThinkers()
{
    thinker_t *th;
    size_t size = 0; // killough

    CheckSaveGame(sizeof brain); // killough 3/26/98: Save boss brain state
    memcpy(save_p, &brain, sizeof brain);
    save_p += sizeof brain;

    // save off the current thinkers (memory size calculation -- killough)
    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (th->function.isNull())
        {
            platlist_t *pl;
            ceilinglist_t *cl; // jff 2/22/98 need this for ceilings too now
            for (pl = activeplats; pl; pl = pl->next)
            {
                if (pl->plat == (plat_t *)th) // killough 2/14/98
                {
                    size += 4 + sizeof(plat_t);
                    goto end;
                }
            }
            for (cl = activeceilings; cl; cl = cl->next)
            {                                       // search for activeceiling
                if (cl->ceiling == (ceiling_t *)th) // jff 2/22/98
                {
                    size += 4 + sizeof(ceiling_t);
                    goto end;
                }
            }
        end:;
        }
        else
        {
            size += th->function == T_MoveCeiling    ? 4 + sizeof(ceiling_t)
                    : th->function == T_VerticalDoor ? 4 + sizeof(vldoor_t)
                    : th->function == T_MoveFloor    ? 4 + sizeof(floormove_t)
                    : th->function == T_PlatRaise    ? 4 + sizeof(plat_t)
                    : th->function == T_LightFlash   ? 4 + sizeof(lightflash_t)
                    : th->function == T_StrobeFlash  ? 4 + sizeof(strobe_t)
                    : th->function == T_Glow         ? 4 + sizeof(glow_t)
                    : th->function == T_MoveElevator ? 4 + sizeof(elevator_t)
                    : th->function == T_Scroll       ? 4 + sizeof(scroll_t)
                    : th->function == T_Pusher       ? 4 + sizeof(pusher_t)
                    : th->function == T_FireFlicker  ? 4 + sizeof(fireflicker_t)
                    : th->function == T_Friction     ? 4 + sizeof(friction_t)
                    : P_IsMobjThinker(th)            ? 4 + sizeof(mobj_t)
                                                     : 0;
        }
    }

    CheckSaveGame(size + 1); // killough; cph: +1 for the tc_endspecials

    // save off the current thinkers
    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (th->function.isNull())
        {
            platlist_t *pl;
            ceilinglist_t *cl; // jff 2/22/98 add iter variable for ceilings

            // killough 2/8/98: fix plat original height bug.
            // Since acv==nullptr, this could be a plat in stasis.
            // so check the active plats list, and save this
            // plat (jff: or ceiling) even if it is in stasis.

            for (pl = activeplats; pl; pl = pl->next)
            {
                if (pl->plat == (plat_t *)th)
                { // killough 2/14/98
                    goto plat;
                }
            }

            for (cl = activeceilings; cl; cl = cl->next)
            {
                if (cl->ceiling == (ceiling_t *)th)
                { // jff 2/22/98
                    goto ceiling;
                }
            }

            continue;
        }

        if (th->function == T_MoveCeiling)
        {
            ceiling_t *ceiling;
        ceiling: // killough 2/14/98
            *save_p++ = tc_true_ceiling;
            PADSAVEP();
            ceiling = (ceiling_t *)save_p;
            memcpy(ceiling, th, sizeof(*ceiling));
            save_p += sizeof(*ceiling);
            ceiling->sector =
                (sector_t *)(intptr_t)(ceiling->sector->iSectorID);
            continue;
        }

        if (th->function == T_VerticalDoor)
        {
            vldoor_t *door;
            *save_p++ = tc_true_door;
            PADSAVEP();
            door = (vldoor_t *)save_p;
            memcpy(door, th, sizeof *door);
            save_p += sizeof(*door);
            door->sector = (sector_t *)(intptr_t)(door->sector->iSectorID);
            // jff 1/31/98 archive line remembered by door as well
            door->line = (line_t *)(door->line ? door->line - lines : -1);
            continue;
        }

        if (th->function == T_MoveFloor)
        {
            floormove_t *floor;
            *save_p++ = tc_true_floor;
            PADSAVEP();
            floor = (floormove_t *)save_p;
            memcpy(floor, th, sizeof(*floor));
            save_p += sizeof(*floor);
            floor->sector = (sector_t *)(intptr_t)(floor->sector->iSectorID);
            continue;
        }

        if (th->function == T_PlatRaise)
        {
            plat_t *plat;
        plat: // killough 2/14/98: added fix for original plat height above
            *save_p++ = tc_true_plat;
            PADSAVEP();
            plat = (plat_t *)save_p;
            memcpy(plat, th, sizeof(*plat));
            save_p += sizeof(*plat);
            plat->sector = (sector_t *)(intptr_t)(plat->sector->iSectorID);
            continue;
        }

        if (th->function == T_LightFlash)
        {
            lightflash_t *flash;
            *save_p++ = tc_true_flash;
            PADSAVEP();
            flash = (lightflash_t *)save_p;
            memcpy(flash, th, sizeof(*flash));
            save_p += sizeof(*flash);
            flash->sector = (sector_t *)(intptr_t)(flash->sector->iSectorID);
            continue;
        }

        if (th->function == T_StrobeFlash)
        {
            strobe_t *strobe;
            *save_p++ = tc_true_strobe;
            PADSAVEP();
            strobe = (strobe_t *)save_p;
            memcpy(strobe, th, sizeof(*strobe));
            save_p += sizeof(*strobe);
            strobe->sector = (sector_t *)(intptr_t)(strobe->sector->iSectorID);
            continue;
        }

        if (th->function == T_Glow)
        {
            glow_t *glow;
            *save_p++ = tc_true_glow;
            PADSAVEP();
            glow = (glow_t *)save_p;
            memcpy(glow, th, sizeof(*glow));
            save_p += sizeof(*glow);
            glow->sector = (sector_t *)(intptr_t)(glow->sector->iSectorID);
            continue;
        }

        // killough 10/4/98: save flickers
        if (th->function == T_FireFlicker)
        {
            fireflicker_t *flicker;
            *save_p++ = tc_true_flicker;
            PADSAVEP();
            flicker = (fireflicker_t *)save_p;
            memcpy(flicker, th, sizeof(*flicker));
            save_p += sizeof(*flicker);
            flicker->sector =
                (sector_t *)(intptr_t)(flicker->sector->iSectorID);
            continue;
        }

        // jff 2/22/98 new case for elevators
        if (th->function == T_MoveElevator)
        {
            elevator_t *elevator; // jff 2/22/98
            *save_p++ = tc_true_elevator;
            PADSAVEP();
            elevator = (elevator_t *)save_p;
            memcpy(elevator, th, sizeof(*elevator));
            save_p += sizeof(*elevator);
            elevator->sector =
                (sector_t *)(intptr_t)(elevator->sector->iSectorID);
            continue;
        }

        // killough 3/7/98: Scroll effect thinkers
        if (th->function == T_Scroll)
        {
            *save_p++ = tc_true_scroll;
            PADSAVEP();
            memcpy(save_p, th, sizeof(scroll_t));
            save_p += sizeof(scroll_t);
            continue;
        }

        // phares 3/22/98: Push/Pull effect thinkers

        if (th->function == T_Pusher)
        {
            *save_p++ = tc_true_pusher;
            PADSAVEP();
            memcpy(save_p, th, sizeof(pusher_t));
            save_p += sizeof(pusher_t);
            continue;
        }

        if (th->function == T_Friction)
        {
            *save_p++ = tc_true_friction;
            PADSAVEP();
            memcpy(save_p, th, sizeof(friction_t));
            save_p += sizeof(friction_t);
            continue;
        }

        if (P_IsMobjThinker(th))
        {
            mobj_t *mobj;

            *save_p++ = tc_true_mobj;
            PADSAVEP();
            mobj = (mobj_t *)save_p;

            // e6y
            memcpy(mobj, th, sizeof(*mobj));
            save_p += sizeof(*mobj);

            mobj->state = (state_t *)(mobj->state - states);

            // Example:
            // - Archvile is attacking a lost soul
            // - The lost soul dies before the attack hits
            // - The lost soul is marked for deletion
            // - The archvile will still attack the spot where the lost soul was
            // - We need to save such objects and remember they are marked for
            // deletion
            if (mobj->thinker.function == P_RemoveThinkerDelayed)
            {
                mobj->index = MARKED_FOR_DELETION;
            }

            // killough 2/14/98: convert pointers into indices.
            // Fixes many savegame problems, by properly saving
            // target and tracer fields. Note: we store nullptr if
            // the thinker pointed to by these fields is not a
            // mobj thinker.

            if (mobj->target)
            {
                mobj->target = P_IsMobjThinker(&mobj->target->thinker)
                                   ? (mobj_t *)mobj->target->thinker.prev
                                   : nullptr;
            }

            if (mobj->tracer)
            {
                mobj->tracer = P_IsMobjThinker(&mobj->tracer->thinker)
                                   ? (mobj_t *)mobj->tracer->thinker.prev
                                   : nullptr;
            }

            // killough 2/14/98: new field: save last known enemy. Prevents
            // monsters from going to sleep after killing monsters and not
            // seeing player anymore.

            if (mobj->lastenemy)
            {
                mobj->lastenemy = P_IsMobjThinker(&mobj->lastenemy->thinker)
                                      ? (mobj_t *)mobj->lastenemy->thinker.prev
                                      : nullptr;
            }

            // killough 2/14/98: end changes

            if (heretic)
            {
                switch (mobj->type)
                {
                case HERETIC_MT_MACEFX4:    // A_DeathBallImpact
                case HERETIC_MT_WHIRLWIND:  // A_WhirlwindSeek
                case HERETIC_MT_MUMMYFX1:   // A_MummyFX1Seek
                case HERETIC_MT_HORNRODFX2: // A_SkullRodPL2Seek
                case HERETIC_MT_PHOENIXFX1: // A_PhoenixPuff
                    if (mobj->special1.m)
                    {
                        mobj->special1.m =
                            P_IsMobjThinker(&mobj->special1.m->thinker)
                                ? (mobj_t *)mobj->special1.m->thinker.prev
                                : nullptr;
                    }
                    break;
                case HERETIC_MT_POD:
                    if (mobj->special2.m)
                    {
                        mobj->special2.m =
                            P_IsMobjThinker(&mobj->special2.m->thinker)
                                ? (mobj_t *)mobj->special2.m->thinker.prev
                                : nullptr;
                    }
                    break;
                default:
                    break;
                }
            }

            if (mobj->player)
            {
                mobj->player = (player_t *)((mobj->player - players) + 1);
            }
        }
    }

    // add a terminating marker
    *save_p++ = tc_true_end;

    // killough 9/14/98: save soundtargets
    {
        int i;
        CheckSaveGame(numsectors * sizeof(mobj_t *)); // killough 9/14/98
        for (i = 0; i < numsectors; i++)
        {
            mobj_t *target = sectors[i].soundtarget;
            // Fix crash on reload when a soundtarget points to a removed corpse
            // (prboom bug #1590350)
            if (target && P_IsMobjThinker(&target->thinker))
            {
                target = (mobj_t *)target->thinker.prev;
            }
            else
            {
                target = nullptr;
            }
            memcpy(save_p, &target, sizeof target);
            save_p += sizeof target;
        }
    }

    P_ArchiveBlockLinks();
    P_ArchiveThinkerSubclasses();

    dsda_ArchiveMSecNodes();
}

// dsda - fix save / load synchronization
// merges P_UnArchiveThinkers & P_UnArchiveSpecials
void P_TrueUnArchiveThinkers()
{
    thinker_t *th;
    mobj_t **mobj_p; // killough 2/14/98: Translation table
    int mobj_count;  // killough 2/14/98: size of or index into table
    true_thinkerclass_t tc;

    totallive = 0;
    // killough 3/26/98: Load boss brain state
    memcpy(&brain, save_p, sizeof brain);
    save_p += sizeof brain;

    // remove all the current thinkers
    for (th = thinkercap.next; th != &thinkercap;)
    {
        thinker_t *next = th->next;
        if (P_IsMobjThinker(th))
        {
            P_RemoveMobj((mobj_t *)th);
            P_RemoveThinkerDelayed(th); // fix mobj leak
        }
        else
        {
            std::free(th);
        }
        th = next;
    }
    P_InitThinkers();

    // killough 2/14/98: count number of thinkers by skipping through them
    {
        byte *sp; // save pointer and skip header

        sp = save_p;
        mobj_count = 0;

        while ((tc = static_cast<true_thinkerclass_t>(*save_p++)) != tc_true_end
        )
        {
            if (tc == tc_true_mobj)
            {
                mobj_count++;
            }
            PADSAVEP();
            save_p += tc == tc_true_ceiling    ? sizeof(ceiling_t)
                      : tc == tc_true_door     ? sizeof(vldoor_t)
                      : tc == tc_true_floor    ? sizeof(floormove_t)
                      : tc == tc_true_plat     ? sizeof(plat_t)
                      : tc == tc_true_flash    ? sizeof(lightflash_t)
                      : tc == tc_true_strobe   ? sizeof(strobe_t)
                      : tc == tc_true_glow     ? sizeof(glow_t)
                      : tc == tc_true_elevator ? sizeof(elevator_t)
                      : tc == tc_true_scroll   ? sizeof(scroll_t)
                      : tc == tc_true_pusher   ? sizeof(pusher_t)
                      : tc == tc_true_flicker  ? sizeof(fireflicker_t)
                      : tc == tc_true_friction ? sizeof(friction_t)
                      : tc == tc_true_mobj     ? sizeof(mobj_t)
                                               : 0;
        }

        if (*--save_p != tc_true_end)
        {
            I_Error(
                "P_TrueUnArchiveThinkers: Unknown tc %i in size calculation",
                *save_p
            );
        }

        // first table entry special: 0 maps to nullptr
        *(mobj_p =
              static_cast<mobj_t **>(malloc((mobj_count + 1) * sizeof *mobj_p))
        ) = nullptr; // table of pointers
        save_p = sp; // restore save pointer
    }

    // read in saved thinkers
    mobj_count = 0;
    while ((tc = static_cast<true_thinkerclass_t>(*save_p++)) != tc_true_end)
    {
        switch (tc)
        {
        case tc_true_ceiling:
            PADSAVEP();
            {
                ceiling_t *ceiling =
                    static_cast<ceiling_t *>(std::malloc(sizeof(*ceiling)));
                memcpy(ceiling, save_p, sizeof(*ceiling));
                save_p += sizeof(*ceiling);
                ceiling->sector = &sectors[(size_t)ceiling->sector];
                ceiling->sector->ceilingdata = ceiling; // jff 2/22/98

                if (ceiling->thinker.function.notNull())
                {
                    ceiling->thinker.function = T_MoveCeiling;
                }

                P_AddThinker(&ceiling->thinker);
                P_AddActiveCeiling(ceiling);
                break;
            }

        case tc_true_door:
            PADSAVEP();
            {
                vldoor_t *door =
                    static_cast<vldoor_t *>(std::malloc(sizeof(*door)));
                memcpy(door, save_p, sizeof(*door));
                save_p += sizeof(*door);
                door->sector = &sectors[(size_t)door->sector];

                // jff 1/31/98 unarchive line remembered by door as well
                door->line = (intptr_t)door->line != -1
                                 ? &lines[(size_t)door->line]
                                 : nullptr;

                door->sector->ceilingdata = door; // jff 2/22/98
                door->thinker.function = T_VerticalDoor;
                P_AddThinker(&door->thinker);
                break;
            }

        case tc_true_floor:
            PADSAVEP();
            {
                floormove_t *floor =
                    static_cast<floormove_t *>(std::malloc(sizeof(*floor)));
                memcpy(floor, save_p, sizeof(*floor));
                save_p += sizeof(*floor);
                floor->sector = &sectors[(size_t)floor->sector];
                floor->sector->floordata = floor; // jff 2/22/98
                floor->thinker.function = T_MoveFloor;
                P_AddThinker(&floor->thinker);
                break;
            }

        case tc_true_plat:
            PADSAVEP();
            {
                plat_t *plat =
                    static_cast<plat_t *>(std::malloc(sizeof(*plat)));
                memcpy(plat, save_p, sizeof(*plat));
                save_p += sizeof(*plat);
                plat->sector = &sectors[(size_t)plat->sector];
                plat->sector->floordata = plat; // jff 2/22/98

                if (plat->thinker.function.notNull())
                {
                    plat->thinker.function = T_PlatRaise;
                }

                P_AddThinker(&plat->thinker);
                P_AddActivePlat(plat);
                break;
            }

        case tc_true_flash:
            PADSAVEP();
            {
                lightflash_t *flash =
                    static_cast<lightflash_t *>(std::malloc(sizeof(*flash)));
                memcpy(flash, save_p, sizeof(*flash));
                save_p += sizeof(*flash);
                flash->sector = &sectors[(size_t)flash->sector];
                flash->thinker.function = T_LightFlash;
                P_AddThinker(&flash->thinker);
                break;
            }

        case tc_true_strobe:
            PADSAVEP();
            {
                strobe_t *strobe =
                    static_cast<strobe_t *>(std::malloc(sizeof(*strobe)));
                memcpy(strobe, save_p, sizeof(*strobe));
                save_p += sizeof(*strobe);
                strobe->sector = &sectors[(size_t)strobe->sector];
                strobe->thinker.function = T_StrobeFlash;
                P_AddThinker(&strobe->thinker);
                break;
            }

        case tc_true_glow:
            PADSAVEP();
            {
                glow_t *glow =
                    static_cast<glow_t *>(std::malloc(sizeof(*glow)));
                memcpy(glow, save_p, sizeof(*glow));
                save_p += sizeof(*glow);
                glow->sector = &sectors[(size_t)glow->sector];
                glow->thinker.function = T_Glow;
                P_AddThinker(&glow->thinker);
                break;
            }

        case tc_true_flicker: // killough 10/4/98
            PADSAVEP();
            {
                fireflicker_t *flicker =
                    static_cast<fireflicker_t *>(std::malloc(sizeof(*flicker)));
                memcpy(flicker, save_p, sizeof(*flicker));
                save_p += sizeof(*flicker);
                flicker->sector = &sectors[(size_t)flicker->sector];
                flicker->thinker.function = T_FireFlicker;
                P_AddThinker(&flicker->thinker);
                break;
            }

            // jff 2/22/98 new case for elevators
        case tc_true_elevator:
            PADSAVEP();
            {
                elevator_t *elevator =
                    static_cast<elevator_t *>(std::malloc(sizeof(*elevator)));
                memcpy(elevator, save_p, sizeof(*elevator));
                save_p += sizeof(*elevator);
                elevator->sector = &sectors[(size_t)elevator->sector];
                elevator->sector->floordata = elevator;   // jff 2/22/98
                elevator->sector->ceilingdata = elevator; // jff 2/22/98
                elevator->thinker.function = T_MoveElevator;
                P_AddThinker(&elevator->thinker);
                break;
            }

        case tc_true_scroll: // killough 3/7/98: scroll effect thinkers
            PADSAVEP();
            {
                scroll_t *scroll =
                    static_cast<scroll_t *>(std::malloc(sizeof(scroll_t)));
                memcpy(scroll, save_p, sizeof(scroll_t));
                save_p += sizeof(scroll_t);
                scroll->thinker.function = T_Scroll;
                P_AddThinker(&scroll->thinker);
                break;
            }

        case tc_true_pusher: // phares 3/22/98: new Push/Pull effect thinkers
            PADSAVEP();
            {
                pusher_t *pusher =
                    static_cast<pusher_t *>(std::malloc(sizeof(pusher_t)));
                memcpy(pusher, save_p, sizeof(pusher_t));
                save_p += sizeof(pusher_t);
                pusher->thinker.function = T_Pusher;
                pusher->source = P_GetPushThing(pusher->affectee);
                P_AddThinker(&pusher->thinker);
                break;
            }

        case tc_true_friction:
            PADSAVEP();
            {
                friction_t *friction =
                    static_cast<friction_t *>(std::malloc(sizeof(friction_t)));
                memcpy(friction, save_p, sizeof(friction_t));
                save_p += sizeof(friction_t);
                friction->thinker.function = T_Friction;
                P_AddThinker(&friction->thinker);
                break;
            }

        case tc_true_mobj:
            PADSAVEP();
            {
                mobj_t *mobj =
                    static_cast<mobj_t *>(std::malloc(sizeof(mobj_t)));

                // killough 2/14/98 -- insert pointers to thinkers into table,
                // in order:
                mobj_count++;
                mobj_p[mobj_count] = mobj;

                memcpy(mobj, save_p, sizeof(mobj_t));
                save_p += sizeof(mobj_t);

                mobj->state = states + (intptr_t)mobj->state;

                if (mobj->player)
                {
                    (mobj->player = &players[(size_t)mobj->player - 1])->mo =
                        mobj;
                }

                mobj->info = &mobjinfo[mobj->type];

                // Don't place objects marked for deletion
                if (mobj->index == MARKED_FOR_DELETION)
                {
                    mobj->thinker.function = P_RemoveThinkerDelayed;
                    P_AddThinker(&mobj->thinker);

                    // The references value must be nonzero to reach the target
                    // code
                    mobj->thinker.references = 1;
                    break;
                }

                P_SetThingPosition(mobj);

                // killough 2/28/98:
                // Fix for falling down into a wall after savegame loaded:
                //      mobj->floorz = mobj->subsector->sector->floorheight;
                //      mobj->ceilingz = mobj->subsector->sector->ceilingheight;

                mobj->thinker.function = P_MobjThinker;
                P_AddThinker(&mobj->thinker);

                if (mobj->type == HERETIC_MT_BLASTERFX1)
                {
                    mobj->thinker.function = P_BlasterMobjThinker;
                }

                if (!((mobj->flags ^ MF_COUNTKILL) &
                      (MF_FRIEND | MF_COUNTKILL | MF_CORPSE)))
                {
                    totallive++;
                }
                break;
            }

        default:
            I_Error("P_TrueUnarchiveSpecials: Unknown tc %i in extraction", tc);
        }
    }

    // killough 2/14/98: adjust target and tracer fields, plus
    // lastenemy field, to correctly point to mobj thinkers.
    // nullptr entries automatically handled by first table entry.
    //
    // killough 11/98: use P_SetNewTarget() to set fields

    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (P_IsMobjThinker(th))
        {
            P_SetNewTarget(
                &((mobj_t *)th)->target,
                mobj_p[P_GetMobj(((mobj_t *)th)->target, mobj_count + 1)]
            );

            P_SetNewTarget(
                &((mobj_t *)th)->tracer,
                mobj_p[P_GetMobj(((mobj_t *)th)->tracer, mobj_count + 1)]
            );

            P_SetNewTarget(
                &((mobj_t *)th)->lastenemy,
                mobj_p[P_GetMobj(((mobj_t *)th)->lastenemy, mobj_count + 1)]
            );

            if (heretic)
            {
                switch (((mobj_t *)th)->type)
                {
                case HERETIC_MT_MACEFX4:    // A_DeathBallImpact
                case HERETIC_MT_WHIRLWIND:  // A_WhirlwindSeek
                case HERETIC_MT_MUMMYFX1:   // A_MummyFX1Seek
                case HERETIC_MT_HORNRODFX2: // A_SkullRodPL2Seek
                case HERETIC_MT_PHOENIXFX1: // A_PhoenixPuff
                    P_SetNewTarget(
                        &((mobj_t *)th)->special1.m,
                        mobj_p[P_GetMobj(
                            ((mobj_t *)th)->special1.m, mobj_count + 1
                        )]
                    );
                    break;
                case HERETIC_MT_POD:
                    P_SetNewTarget(
                        &((mobj_t *)th)->special2.m,
                        mobj_p[P_GetMobj(
                            ((mobj_t *)th)->special2.m, mobj_count + 1
                        )]
                    );
                    break;
                default:
                    break;
                }
            }

            // restore references now that targets are set
            if (((mobj_t *)th)->index == MARKED_FOR_DELETION)
            {
                ((mobj_t *)th)->index = -1;
                th->references--;
            }
        }
    }

    { // killough 9/14/98: restore soundtargets
        int i;
        for (i = 0; i < numsectors; i++)
        {
            mobj_t *target;
            memcpy(&target, save_p, sizeof target);
            save_p += sizeof target;
            // Must verify soundtarget. See P_TrueArchiveThinkers.
            P_SetNewTarget(
                &sectors[i].soundtarget,
                mobj_p[P_GetMobj(target, mobj_count + 1)]
            );
        }
    }

    P_UnArchiveBlockLinks(mobj_p, mobj_count);
    P_UnArchiveThinkerSubclasses(mobj_p, mobj_count);

    dsda_UnArchiveMSecNodes(mobj_p, mobj_count);

    free(mobj_p); // free translation table

    // killough 3/26/98: Spawn icon landings:
    if (gamemode == commercial)
    {
        // P_SpawnBrainTargets overwrites brain.targeton and brain.easy with
        // zero.
        struct brain_s brain_tmp = brain; // saving

        P_SpawnBrainTargets();

        // old demos with save/load tics should not be affected by this fix
        if (!prboom_comp[PC_RESET_MONSTERSPAWNER_PARAMS_AFTER_LOADING].state)
        {
            brain = brain_tmp; // restoring
        }
    }
}
