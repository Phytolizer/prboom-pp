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
 *      Cheat code checking.
 *
 *-----------------------------------------------------------------------------*/

#ifndef __M_CHEAT__
#define __M_CHEAT__

#include <cstddef>

#include "cpp/enums/cheat_when_t.hh"
#include "d_event.hh"
#include "doomtype.hh"

#define CHEAT(cheat, deh_cheat, when, func, arg)                               \
    {                                                                          \
        cheat, deh_cheat, when, func, arg, 0, 0, sizeof(cheat) - 1, 0, 0, 0,   \
            ""                                                                 \
    }

#define CHEAT_ARGS_MAX 8 /* Maximum number of args at end of cheats */

/* killough 4/16/98: Cheat table structure */

typedef struct cheatseq_s
{
    const char *cheat;
    const char *const deh_cheat = nullptr;
    const cheat_when_t::Type when = cheat_when_t::cht_never;
    void (*const func)() = nullptr;
    const int arg = 0;
    uint_64_t code = 0, mask = 0;

    // settings for this cheat
    std::size_t sequence_len = 0;
    std::size_t deh_sequence_len = 0;

    // state used during the game
    std::size_t chars_read = 0;
    int param_chars_read = 0;
    char parameter_buf[CHEAT_ARGS_MAX]{};
} cheatseq_t;

extern cheatseq_t cheat[];

dboolean M_CheatResponder(event_t *ev);
void cheat_god();
void cheat_buddha();

#endif
