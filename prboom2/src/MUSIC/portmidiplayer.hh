/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *
 *  Copyright (C) 2011 by
 *  Nicholai Main
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
 *
 *---------------------------------------------------------------------
 */

#ifndef PORTMIDIPLAYER_H
#define PORTMIDIPLAYER_H

#include "musicplayer.hh"

const char *pm_name(void);
int pm_init(int samplerate);
void pm_shutdown(void);
void pm_setvolume(int v);
void pm_pause(void);
void pm_resume(void);
const void *pm_registersong(const void *data, unsigned len);
void pm_unregistersong(const void *handle);
void pm_play(const void *handle, int looping);
void pm_stop(void);
void pm_render(void *vdest, unsigned bufflen);

constexpr music_player_t pm_player = {
    pm_name,  pm_init,   pm_shutdown,     pm_setvolume,
    pm_pause, pm_resume, pm_registersong, pm_unregistersong,
    pm_play,  pm_stop,   pm_render};

#endif // PORTMIDI_H
