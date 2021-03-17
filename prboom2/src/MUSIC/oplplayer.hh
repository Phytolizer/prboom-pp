// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005 Simon Howard
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
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//
// DESCRIPTION:
//  System interface for music.
//
//-----------------------------------------------------------------------------

#ifndef OPLPLAYER_H
#define OPLPLAYER_H

const char *I_OPL_SynthName(void);
int I_OPL_InitMusic(int samplerate);
void I_OPL_ShutdownMusic(void);
void I_OPL_SetMusicVolume(int v);
void I_OPL_PauseSong(void);
void I_OPL_ResumeSong(void);
const void *I_OPL_RegisterSong(const void *data, unsigned len);
void I_OPL_UnRegisterSong(const void *handle);
void I_OPL_PlaySong(const void *handle, int looping);
void I_OPL_StopSong(void);
void I_OPL_RenderSamples(void *vdest, unsigned bufflen);

constexpr music_player_t opl_synth_player = {
    I_OPL_SynthName,      I_OPL_InitMusic,      I_OPL_ShutdownMusic,
    I_OPL_SetMusicVolume, I_OPL_PauseSong,      I_OPL_ResumeSong,
    I_OPL_RegisterSong,   I_OPL_UnRegisterSong, I_OPL_PlaySong,
    I_OPL_StopSong,       I_OPL_RenderSamples};

#endif