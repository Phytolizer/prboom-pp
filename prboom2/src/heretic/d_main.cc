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

// D_main.c

#include "d_main.hh"
#include "../d_main.hh"
#include "g_game.hh"
#include "sounds.hh"

#include "heretic/dstrings.hh"

static void Heretic_D_DrawTitle(const char *_x)
{
    D_SetPage(DEH_String("TITLE"), 350, heretic_mus_titl);
}

static void Heretic_D_DrawCredits(const char *_x)
{
    D_SetPage(DEH_String("CREDIT"), 200, 0);
}

static void Heretic_D_DrawOrder(const char *_x)
{
    D_SetPage(DEH_String("ORDER"), 200, 0);
}

const demostate_t heretic_demostates[][4] = {
    {
        {Heretic_D_DrawTitle, nullptr},
        {Heretic_D_DrawTitle, nullptr},
        {Heretic_D_DrawTitle, nullptr},
        {Heretic_D_DrawTitle, nullptr},
    },

    {
        {G_DeferedPlayDemo, "demo1"},
        {G_DeferedPlayDemo, "demo1"},
        {G_DeferedPlayDemo, "demo1"},
        {G_DeferedPlayDemo, "demo1"},
    },

    {
        {Heretic_D_DrawCredits, nullptr},
        {Heretic_D_DrawCredits, nullptr},
        {Heretic_D_DrawCredits, nullptr},
        {Heretic_D_DrawCredits, nullptr},
    },

    {
        {G_DeferedPlayDemo, "demo2"},
        {G_DeferedPlayDemo, "demo2"},
        {G_DeferedPlayDemo, "demo2"},
        {G_DeferedPlayDemo, "demo2"},
    },

    {
        {Heretic_D_DrawOrder, nullptr},
        {Heretic_D_DrawCredits, nullptr},
        {Heretic_D_DrawCredits, nullptr},
        {Heretic_D_DrawCredits, nullptr},
    },

    {
        {G_DeferedPlayDemo, "demo3"},
        {G_DeferedPlayDemo, "demo3"},
        {G_DeferedPlayDemo, "demo3"},
        {G_DeferedPlayDemo, "demo3"},
    },

    {
        {nullptr},
        {nullptr},
        {nullptr},
        {nullptr},
    }};
