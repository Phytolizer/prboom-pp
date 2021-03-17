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

#ifndef MADPLAYER_H
#define MADPLAYER_H




const char *mp_name(void);
int mp_init (int samplerate);
void mp_shutdown (void);
void mp_setvolume (int v);
void mp_pause (void);
void mp_resume (void);
const void *mp_registersong (const void *data, unsigned len);
void mp_unregistersong (const void *handle);
void mp_play (const void *handle, int looping);
void mp_stop (void);
void mp_render (void *vdest, unsigned bufflen);





constexpr music_player_t mp_player =
    {
        mp_name,
        mp_init,
        mp_shutdown,
        mp_setvolume,
        mp_pause,
        mp_resume,
        mp_registersong,
        mp_unregistersong,
        mp_play,
        mp_stop,
        mp_render
    };





#endif // MADPLAYER_H
