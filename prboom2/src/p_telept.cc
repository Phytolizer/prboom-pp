/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2002 by
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
 *      Teleportation.
 *
 *-----------------------------------------------------------------------------*/

#include "doomdef.hh"
#include "doomstat.hh"
#include "p_map.hh"
#include "p_maputl.hh"
#include "p_spec.hh"
#include "p_tick.hh"
#include "p_user.hh"
#include "r_demo.hh"
#include "r_main.hh"
#include "s_sound.hh"
#include "sounds.hh"

static mobj_t *P_TeleportDestination(line_t *line)
{
    int i;
    for (i = -1; (i = P_FindSectorFromLineTag(line, i)) >= 0;)
    {
        thinker_t *th = nullptr;
        while ((th = P_NextThinker(th, th_misc)) != nullptr)
        {
            if (th->function == P_MobjThinker)
            {
                mobj_t *m = (mobj_t *)th;
                if (m->type == MT_TELEPORTMAN &&
                    m->subsector->sector->iSectorID == i)
                {
                    return m;
                }
            }
        }
    }
    return nullptr;
}
//
// TELEPORTATION
//
// killough 5/3/98: reformatted, cleaned up

int EV_Teleport(line_t *line, int side, mobj_t *thing)
{
    mobj_t *m;

    if (heretic)
    {
        return Heretic_EV_Teleport(line, side, thing);
    }

    // don't teleport missiles
    // Don't teleport if hit back of line,
    //  so you can get out of teleporter.
    if (side || thing->flags & MF_MISSILE)
    {
        return 0;
    }

    // killough 1/31/98: improve performance by using
    // P_FindSectorFromLineTag instead of simple linear search.

    if ((m = P_TeleportDestination(line)) != nullptr)
    {
        fixed_t oldx = thing->x, oldy = thing->y, oldz = thing->z;
        player_t *player = thing->player;

        // killough 5/12/98: exclude voodoo dolls:
        if (player && player->mo != thing)
        {
            player = nullptr;
        }

        if (!P_TeleportMove(thing, m->x, m->y, false))
        { /* killough 8/9/98 */
            return 0;
        }

        if (compatibility_level != finaldoom_compatibility)
        {
            thing->z = thing->floorz;
        }
        thing->PrevZ = thing->z;

        if (player)
        {
            player->viewz = thing->z + player->viewheight;
        }

        // spawn teleport fog and emit sound at source
        S_StartSound(P_SpawnMobj(oldx, oldy, oldz, MT_TFOG), sfx_telept);

        // spawn teleport fog and emit sound at destination
        S_StartSound(
            P_SpawnMobj(
                m->x + 20 * finecosine[m->angle >> ANGLETOFINESHIFT],
                m->y + 20 * finesine[m->angle >> ANGLETOFINESHIFT], thing->z,
                MT_TFOG
            ),
            sfx_telept
        );

        /* don't move for a bit
         * cph - DEMOSYNC - BOOM had (player) here? */
        if (thing->player)
        {
            thing->reactiontime = 18;
        }

        thing->angle = m->angle;

        thing->momx = thing->momy = thing->momz = 0;

        /* killough 10/98: kill all bobbing momentum too */
        if (player)
        {
            player->momx = player->momy = 0;
        }

        // e6y
        if (player && player->mo == thing)
        {
            R_ResetAfterTeleport(player);
        }

        return 1;
    }
    return 0;
}

//
// Silent TELEPORTATION, by Lee Killough
// Primarily for rooms-over-rooms etc.
//

int EV_SilentTeleport(line_t *line, int side, mobj_t *thing)
{
    mobj_t *m;

    // don't teleport missiles
    // Don't teleport if hit back of line,
    // so you can get out of teleporter.

    if (side || thing->flags & MF_MISSILE)
    {
        return 0;
    }

    if ((m = P_TeleportDestination(line)) != nullptr)
    {
        // Height of thing above ground, in case of mid-air teleports:
        fixed_t z = thing->z - thing->floorz;

        // Get the angle between the exit thing and source linedef.
        // Rotate 90 degrees, so that walking perpendicularly across
        // teleporter linedef causes thing to exit in the direction
        // indicated by the exit thing.
        angle_t angle =
            R_PointToAngle2(0, 0, line->dx, line->dy) - m->angle + ANG90;

        // Sine, cosine of angle adjustment
        fixed_t s = finesine[angle >> ANGLETOFINESHIFT];
        fixed_t c = finecosine[angle >> ANGLETOFINESHIFT];

        // Momentum of thing crossing teleporter linedef
        fixed_t momx = thing->momx;
        fixed_t momy = thing->momy;

        // Whether this is a player, and if so, a pointer to its player_t
        player_t *player = thing->player;

        // Attempt to teleport, aborting if blocked
        if (!P_TeleportMove(thing, m->x, m->y, false))
        { /* killough 8/9/98 */
            return 0;
        }

        // Rotate thing according to difference in angles
        thing->angle += angle;

        // Adjust z position to be same height above ground as before
        thing->z = z + thing->floorz;
        thing->PrevZ = thing->z;

        // Rotate thing's momentum to come out of exit just like it entered
        thing->momx = FixedMul(momx, c) - FixedMul(momy, s);
        thing->momy = FixedMul(momy, c) + FixedMul(momx, s);

        // Adjust player's view, in case there has been a height change
        // Voodoo dolls are excluded by making sure player->mo == thing.
        if (player && player->mo == thing)
        {
            // Save the current deltaviewheight, used in stepping
            fixed_t deltaviewheight = player->deltaviewheight;

            // Clear deltaviewheight, since we don't want any changes
            player->deltaviewheight = 0;

            // Set player's view according to the newly set parameters
            P_CalcHeight(player);

            // Reset the delta to have the same dynamics as before
            player->deltaviewheight = deltaviewheight;
        }

        // e6y
        if (player && player->mo == thing)
        {
            R_ResetAfterTeleport(player);
        }

        return 1;
    }
    return 0;
}

//
// Silent linedef-based TELEPORTATION, by Lee Killough
// Primarily for rooms-over-rooms etc.
// This is the complete player-preserving kind of teleporter.
// It has advantages over the teleporter with thing exits.
//

// maximum fixed_t units to move object to avoid hiccups
#define FUDGEFACTOR 10

int EV_SilentLineTeleport(
    line_t *line, int side, mobj_t *thing, dboolean reverse
)
{
    int i;
    line_t *l;

    if (side || thing->flags & MF_MISSILE)
    {
        return 0;
    }

    for (i = -1; (i = P_FindLineFromLineTag(line, i)) >= 0;)
    {
        if ((l = lines + i) != line && l->backsector)
        {
            // Get the thing's position along the source linedef
            fixed_t pos = D_abs(line->dx) > D_abs(line->dy)
                              ? FixedDiv(thing->x - line->v1->x, line->dx)
                              : FixedDiv(thing->y - line->v1->y, line->dy);

            // Get the angle between the two linedefs, for rotating
            // orientation and momentum. Rotate 180 degrees, and flip
            // the position across the exit linedef, if reversed.
            angle_t angle = (reverse ? pos = FRACUNIT - pos, 0 : ANG180) +
                            R_PointToAngle2(0, 0, l->dx, l->dy) -
                            R_PointToAngle2(0, 0, line->dx, line->dy);

            // Interpolate position across the exit linedef
            fixed_t x = l->v2->x - FixedMul(pos, l->dx);
            fixed_t y = l->v2->y - FixedMul(pos, l->dy);

            // Sine, cosine of angle adjustment
            fixed_t s = finesine[angle >> ANGLETOFINESHIFT];
            fixed_t c = finecosine[angle >> ANGLETOFINESHIFT];

            // Maximum distance thing can be moved away from interpolated
            // exit, to ensure that it is on the correct side of exit linedef
            int fudge = FUDGEFACTOR;

            // Whether this is a player, and if so, a pointer to its player_t.
            // Voodoo dolls are excluded by making sure
            // thing->player->mo==thing.
            player_t *player = thing->player && thing->player->mo == thing
                                   ? thing->player
                                   : nullptr;

            // Whether walking towards first side of exit linedef steps down
            int stepdown =
                l->frontsector->floorheight < l->backsector->floorheight;

            // Height of thing above ground
            fixed_t z = thing->z - thing->floorz;

            // Side to exit the linedef on positionally.
            //
            // Notes:
            //
            // This flag concerns exit position, not momentum. Due to
            // roundoff error, the thing can land on either the left or
            // the right side of the exit linedef, and steps must be
            // taken to make sure it does not end up on the wrong side.
            //
            // Exit momentum is always towards side 1 in a reversed
            // teleporter, and always towards side 0 otherwise.
            //
            // Exiting positionally on side 1 is always safe, as far
            // as avoiding oscillations and stuck-in-wall problems,
            // but may not be optimum for non-reversed teleporters.
            //
            // Exiting on side 0 can cause oscillations if momentum
            // is towards side 1, as it is with reversed teleporters.
            //
            // Exiting on side 1 slightly improves player viewing
            // when going down a step on a non-reversed teleporter.

            int side = reverse || (player && stepdown);

            // Make sure we are on correct side of exit linedef.
            while (P_PointOnLineSide(x, y, l) != side && --fudge >= 0)
            {
                if (D_abs(l->dx) > D_abs(l->dy))
                {
                    y -= (l->dx < 0) != side ? -1 : 1;
                }
                else
                {
                    x += (l->dy < 0) != side ? -1 : 1;
                }
            }

            // Attempt to teleport, aborting if blocked
            if (!P_TeleportMove(thing, x, y, false))
            { /* killough 8/9/98 */
                return 0;
            }

            // e6y
            if (player && player->mo == thing)
            {
                R_ResetAfterTeleport(player);
            }

            // Adjust z position to be same height above ground as before.
            // Ground level at the exit is measured as the higher of the
            // two floor heights at the exit linedef.
            thing->z = z + sides[l->sidenum[stepdown]].sector->floorheight;
            thing->PrevZ = thing->z;

            // Rotate thing's orientation according to difference in linedef
            // angles
            thing->angle += angle;

            // Momentum of thing crossing teleporter linedef
            x = thing->momx;
            y = thing->momy;

            // Rotate thing's momentum to come out of exit just like it entered
            thing->momx = FixedMul(x, c) - FixedMul(y, s);
            thing->momy = FixedMul(y, c) + FixedMul(x, s);

            // Adjust a player's view, in case there has been a height change
            if (player)
            {
                // Save the current deltaviewheight, used in stepping
                fixed_t deltaviewheight = player->deltaviewheight;

                // Clear deltaviewheight, since we don't want any changes now
                player->deltaviewheight = 0;

                // Set player's view according to the newly set parameters
                P_CalcHeight(player);

                // Reset the delta to have the same dynamics as before
                player->deltaviewheight = deltaviewheight;
            }

            // e6y
            if (player && player->mo == thing)
            {
                R_ResetAfterTeleport(player);
            }

            return 1;
        }
    }
    return 0;
}

// heretic

#include "heretic/def.hh"

dboolean P_Teleport(mobj_t *thing, fixed_t x, fixed_t y, angle_t angle)
{
    fixed_t oldx;
    fixed_t oldy;
    fixed_t oldz;
    fixed_t aboveFloor;
    fixed_t fogDelta;
    player_t *player;
    unsigned an;
    mobj_t *fog;

    oldx = thing->x;
    oldy = thing->y;
    oldz = thing->z;
    aboveFloor = thing->z - thing->floorz;
    if (!P_TeleportMove(thing, x, y, false))
    {
        return (false);
    }
    if (thing->player)
    {
        player = thing->player;
        if (player->powers[pw_flight] && aboveFloor)
        {
            thing->z = thing->floorz + aboveFloor;
            if (thing->z + thing->height > thing->ceilingz)
            {
                thing->z = thing->ceilingz - thing->height;
            }
            player->viewz = thing->z + player->viewheight;
        }
        else
        {
            thing->z = thing->floorz;
            player->viewz = thing->z + player->viewheight;
            player->lookdir = 0;
        }
        if (demo_smoothturns && player == &players[displayplayer])
        {
            R_SmoothPlaying_Add(angle - thing->angle);
        }
    }
    else if (thing->flags & MF_MISSILE)
    {
        thing->z = thing->floorz + aboveFloor;
        if (thing->z + thing->height > thing->ceilingz)
        {
            thing->z = thing->ceilingz - thing->height;
        }
    }
    else
    {
        thing->z = thing->floorz;
    }
    // Spawn teleport fog at source and destination
    fogDelta = thing->flags & MF_MISSILE ? 0 : TELEFOGHEIGHT;
    fog = P_SpawnMobj(oldx, oldy, oldz + fogDelta, HERETIC_MT_TFOG);
    S_StartSound(fog, heretic_sfx_telept);
    an = angle >> ANGLETOFINESHIFT;
    fog = P_SpawnMobj(
        x + 20 * finecosine[an], y + 20 * finesine[an], thing->z + fogDelta,
        HERETIC_MT_TFOG
    );
    S_StartSound(fog, heretic_sfx_telept);
    if (thing->player && !thing->player->powers[pw_weaponlevel2])
    { // Freeze player for about .5 sec
        thing->reactiontime = 18;
    }
    thing->angle = angle;
    if (thing->flags2 & MF2_FOOTCLIP &&
        P_GetThingFloorType(thing) != FLOOR_SOLID)
    {
        thing->flags2 |= MF2_FEETARECLIPPED;
    }
    else if (thing->flags2 & MF2_FEETARECLIPPED)
    {
        thing->flags2 &= ~MF2_FEETARECLIPPED;
    }
    if (thing->flags & MF_MISSILE)
    {
        angle >>= ANGLETOFINESHIFT;
        thing->momx = FixedMul(thing->info->speed, finecosine[angle]);
        thing->momy = FixedMul(thing->info->speed, finesine[angle]);
    }
    else
    {
        thing->momx = thing->momy = thing->momz = 0;
    }
    return (true);
}

dboolean Heretic_EV_Teleport(line_t *line, int side, mobj_t *thing)
{
    int i;
    int tag;
    mobj_t *m;
    thinker_t *thinker;
    sector_t *sector;

    if (thing->flags2 & MF2_NOTELEPORT)
    {
        return (false);
    }
    if (side == 1)
    { // Don't teleport when crossing back side
        return (false);
    }
    tag = line->tag;
    for (i = 0; i < numsectors; i++)
    {
        if (sectors[i].tag == tag)
        {
            for (thinker = thinkercap.next; thinker != &thinkercap;
                 thinker = thinker->next)
            {
                if (thinker->function != P_MobjThinker)
                { // Not a mobj
                    continue;
                }
                m = (mobj_t *)thinker;
                if (m->type != HERETIC_MT_TELEPORTMAN)
                { // Not a teleportman
                    continue;
                }
                sector = m->subsector->sector;
                if (sector - sectors != i)
                { // Wrong sector
                    continue;
                }
                return (P_Teleport(thing, m->x, m->y, m->angle));
            }
        }
    }
    return (false);
}
