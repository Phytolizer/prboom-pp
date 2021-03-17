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

#ifndef FLPLAYER_H
#define FLPLAYER_H


const char *fl_name(void);
int fl_init (int samplerate);
void fl_shutdown (void);
void fl_setvolume (int v);
void fl_pause (void);
void fl_resume (void);
const void *fl_registersong (const void *data, unsigned len);
void fl_unregistersong (const void *handle);
void fl_play (const void *handle, int looping);
void fl_stop (void);
void fl_render (void *vdest, unsigned bufflen);







constexpr music_player_t fl_player =
    {
        fl_name,
        fl_init,
        fl_shutdown,
        fl_setvolume,
        fl_pause,
        fl_resume,
        fl_registersong,
        fl_unregistersong,
        fl_play,
        fl_stop,
        fl_render
    };






#endif // FLPLAYER_H
