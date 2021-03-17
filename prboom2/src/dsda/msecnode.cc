//
// Copyright(C) 2020 by Ryan Krafnick
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
// DESCRIPTION:
//	DSDA MSecNode Management
//

#include "r_defs.hh"
#include "p_saveg.hh"
#include "lprintf.hh"
#include "p_tick.hh"
#include "p_mobj.hh"

#include "msecnode.hh"

extern sector_t *sectors;
extern int numsectors;

msecnode_t *P_GetSecnode(void);
msecnode_t *P_DelSecnode(msecnode_t *node);
int P_GetMobj(mobj_t *mi, size_t s);

static dboolean dsda_IsMSecNodeMobj(thinker_t *thinker)
{
    return thinker->function == P_MobjThinker ||
           thinker->function == P_BlasterMobjThinker;
}

// The MSecNodes store an intersecting web of nodes.
// The nodes are ordered by sector for each thing
//   and by thing for each sector.
// The order of these nodes matters:
//   A crusher damages things in the msecnode order,
//     which causes painstates based on rng, which is order-dependent.
// In order to have syncing key-frames / saves, we must preserve the order.

// Serialization strategy:
//
// The msecnode_t struct has 6 pointers:
//   1 sector, 1 mobj, 4 msecnodes
// A trivial serialization is not possible.
//
// Since the position of everything is preserved,
//   the number of msecnodes in any list is preserved.
//
// We could build a sparse 2d array of msecnodes,
//   but this isn't really feasible.
// Example: eviternity map 32,
//   7207 sectors and 2420 things = 17 million entries.
//
// To serialize:
// - iterate over all the sectors and store the order of things.
//   - must also store the number of things here because
//     there is a bug in the sector management code:
//       despite being in the same position, a reloaded monster
//       sometimes has a different list of sectors that it is in!
// - iterate over all the things and store the order of sectors.
//   - must also store the number of sectors here because
//     this information will be missing while unarchiving.
//
// To deserialize:
// - iterate over all the sectors
//   - iterate over their current msecnode lists
//   - replace the msecnode thing based on the stored order
//   - expand the list if it has too few elements (as described above)
// - iterate over all the things
//   - because of the order change in the sector msecnode lists,
//     the thing's msecnode list may be completely scrambled.
//   - iterate over the stored sectors
//     - iterate over the sector's restored msecnode list
//     - find the msecnode referencing this thing
//     - restore the prev / next values for the thing msecnode list
// - after iterating over all the things and through their sectors,
//   the sector ordering of msecnodes should be corrected,
//   and the thing ordering should still be correct from the first step.

void dsda_ArchiveMSecNodes(void)
{
    int sector_i;
    thinker_t *th;
    msecnode_t *msecnode;
    int count;

    // Store the m_things using the mobj_p indices (see p_saveg.c)
    for (sector_i = 0; sector_i < numsectors; ++sector_i)
    {
        // While this shouldn't be necessary, sometimes the m_snext chain
        //   is not managed correctly, leading to a different length on load.
        count = 0;
        msecnode = sectors[sector_i].touching_thinglist;
        while (msecnode)
        {
            count++;
            msecnode = msecnode->m_snext;
        }

        CheckSaveGame(sizeof(count));
        memcpy(save_p, &count, sizeof(count));
        save_p += sizeof(count);

        msecnode = sectors[sector_i].touching_thinglist;
        while (msecnode)
        {
            th = &msecnode->m_thing->thinker;

            CheckSaveGame(sizeof(th->prev));
            memcpy(save_p, &th->prev, sizeof(th->prev));
            save_p += sizeof(th->prev);

            msecnode = msecnode->m_snext;
        }
    }

    // Store the m_sectors using the sector indices
    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (!dsda_IsMSecNodeMobj(th))
        {
            continue;
        }

        // We must store the count because it will be unobtainable
        //   while we are rewriting the m_tnext chains
        count = 0;
        msecnode = ((mobj_t *)th)->touching_sectorlist;
        while (msecnode)
        {
            count++;
            msecnode = msecnode->m_tnext;
        }

        CheckSaveGame(sizeof(count));
        memcpy(save_p, &count, sizeof(count));
        save_p += sizeof(count);

        msecnode = ((mobj_t *)th)->touching_sectorlist;
        while (msecnode)
        {
            sector_i = msecnode->m_sector - sectors;

            CheckSaveGame(sizeof(sector_i));
            memcpy(save_p, &sector_i, sizeof(sector_i));
            save_p += sizeof(sector_i);

            msecnode = msecnode->m_tnext;
        }
    }
}

static void dsda_UnArchiveMSecNodeMobj(msecnode_t *msecnode, mobj_t **mobj_p,
                                       int mobj_count)
{
    mobj_t *mobj;

    memcpy(&mobj, save_p, sizeof(mobj));
    save_p += sizeof(mobj);

    mobj = mobj_p[P_GetMobj(mobj, mobj_count + 1)];

    if (mobj)
    {
        msecnode->m_thing = mobj;
    }
    else
    {
        I_Error("dsda_UnArchiveMSecNodeMobj: mobj does not exist!\n");
    }
}

void dsda_UnArchiveMSecNodes(mobj_t **mobj_p, int mobj_count)
{
    int i, sector_i;
    thinker_t *th;
    mobj_t *mobj;
    msecnode_t *msecnode;
    msecnode_t *msecnode_prev;
    msecnode_t **msecnode_next;
    dboolean found;
    int count, existing_count;

    for (sector_i = 0; sector_i < numsectors; ++sector_i)
    {
        memcpy(&count, save_p, sizeof(count));
        save_p += sizeof(count);

        // Due to a bug in m_snext chain management,
        //   this value can differ from the one stored originally.
        existing_count = 0;

        msecnode_prev = nullptr;
        msecnode_next = &sectors[sector_i].touching_thinglist;
        msecnode = sectors[sector_i].touching_thinglist;

        // Preserve the m_snext chain, but overwrite the m_things
        while (msecnode)
        {
            existing_count++;

            // If there are too many, delete the rest of them
            if (existing_count > count)
            {
                msecnode_prev = msecnode->m_sprev;
                while (msecnode)
                {
                    P_DelSecnode(msecnode);

                    if (msecnode_prev)
                    {
                        msecnode = msecnode_prev->m_snext;
                    }
                    else
                    {
                        msecnode = nullptr;
                    }
                }

                break;
            }

            dsda_UnArchiveMSecNodeMobj(msecnode, mobj_p, mobj_count);

            msecnode_prev = msecnode;
            msecnode_next = &msecnode->m_snext;
            msecnode = msecnode->m_snext;
        }

        // If the count is too low, add the missing msecnodes
        for (i = existing_count; i < count; ++i)
        {
            msecnode = P_GetSecnode();
            msecnode->visited = 0;
            msecnode->m_sector = &sectors[sector_i];

            dsda_UnArchiveMSecNodeMobj(msecnode, mobj_p, mobj_count);

            // This will be filled in below
            msecnode->m_tprev = nullptr;
            msecnode->m_tnext = nullptr;

            // Hook into the chain
            msecnode->m_sprev = msecnode_prev;
            msecnode->m_snext = nullptr;
            *msecnode_next = msecnode;
            msecnode_prev = msecnode;
            msecnode_next = &msecnode->m_snext;
        }
    }

    // The msecnode (sector, thing) pairs are set,
    //   but the m_tnext chains now weave through the wrong msecnodes
    for (th = thinkercap.next; th != &thinkercap; th = th->next)
    {
        if (!dsda_IsMSecNodeMobj(th))
        {
            continue;
        }

        mobj = ((mobj_t *)th);

        // The rewriting going on in this loop reorganizes the m_tnext chains,
        //   so we cannot trust the existing chain length
        memcpy(&count, save_p, sizeof(count));
        save_p += sizeof(count);

        mobj->touching_sectorlist = nullptr;
        msecnode_prev = nullptr;
        msecnode_next = &mobj->touching_sectorlist;

        for (i = 0; i < count; ++i)
        {
            memcpy(&sector_i, save_p, sizeof(sector_i));
            save_p += sizeof(sector_i);

            // The sector msecnodes were rewritten above,
            //   so we need to find the actual msecnode match (sector, thing)
            found = false;
            msecnode = sectors[sector_i].touching_thinglist;
            while (msecnode)
            {
                if (msecnode->m_thing == mobj)
                {
                    found = true;
                    break;
                }

                msecnode = msecnode->m_snext;
            }

            if (!found)
            {
                I_Error("dsda_UnArchiveMSecNodes: mobj missing in sector "
                        "msecnodes!\n");
            }

            // Rewrite the m_tnext chain with the new msecnodes
            msecnode->m_tprev = msecnode_prev;
            msecnode->m_tnext = nullptr;
            *msecnode_next = msecnode;
            msecnode_prev = msecnode;
            msecnode_next = &msecnode->m_tnext;
        }
    }
}
