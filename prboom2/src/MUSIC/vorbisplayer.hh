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

#ifndef VORBISPLAYER_H
#define VORBISPLAYER_H

#include "musicplayer.hh"

const char *vorb_name(void);
int vorb_init(int samplerate);
void vorb_shutdown(void);
void vorb_setvolume(int v);
void vorb_pause(void);
void vorb_resume(void);
const void *vorb_registersong(const void *data, unsigned len);
void vorb_unregistersong(const void *handle);
void vorb_play(const void *handle, int looping);
void vorb_stop(void);
void vorb_render(void *vdest, unsigned bufflen);

constexpr music_player_t vorb_player = {
    vorb_name,  vorb_init,   vorb_shutdown,     vorb_setvolume,
    vorb_pause, vorb_resume, vorb_registersong, vorb_unregistersong,
    vorb_play,  vorb_stop,   vorb_render};

#endif // VORBISPLAYER_H
