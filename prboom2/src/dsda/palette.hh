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
//	DSDA Palette Management
//

#ifndef __DSDA_PALETTE__
#define __DSDA_PALETTE__

#include "SDL.h"

using dsda_playpal_index_t = enum
{
    playpal_default,
    playpal_1,
    playpal_2,
    playpal_3,
    playpal_4,
    playpal_5,
    playpal_6,
    playpal_7,
    playpal_8,
    playpal_9,
    playpal_heretic_e2end,
    NUMPALETTES
};

using dsda_playpal_t = struct playpal_data_s
{
    const int index;
    const char *lump_name;
    unsigned char *lump = nullptr;
    // See r_patch.c
    int transparent = 0;
    int duplicate = 0;

    // Array of SDL_Color structs used for setting the 256-colour palette
    SDL_Color *colours = nullptr;
    unsigned short *Palettes15 = nullptr;
    unsigned short *Palettes16 = nullptr;
    unsigned int *Palettes32 = nullptr;
};

dsda_playpal_t *dsda_PlayPalData();
void dsda_CyclePlayPal();
void dsda_SetPlayPal(int index);
void dsda_FreePlayPal();
void dsda_FreeTrueColorPlayPal();
void dsda_InitPlayPal();

#endif
