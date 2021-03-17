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

#ifndef DUMBPLAYER_H
#define DUMBPLAYER_H

const char *db_name(void);
int db_init(int samplerate);
void db_shutdown(void);
void db_setvolume(int v);
void db_pause(void);
void db_resume(void);
const void *db_registersong(const void *data, unsigned len);
void db_unregistersong(const void *handle);
void db_play(const void *handle, int looping);
void db_stop(void);
void db_render(void *vdest, unsigned bufflen);

constexpr music_player_t db_player = {
    db_name,  db_init,   db_shutdown,     db_setvolume,
    db_pause, db_resume, db_registersong, db_unregistersong,
    db_play,  db_stop,   db_render};

#endif // DUMBPLAYER_H
