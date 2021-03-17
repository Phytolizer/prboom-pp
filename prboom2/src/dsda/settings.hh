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
//	DSDA Settings
//

#ifndef __DSDA_SETTINGS__
#define __DSDA_SETTINGS__

#include "doomtype.hh"

#define UNSPECIFIED_COMPLEVEL -2

extern int dsda_auto_key_frame_interval;
extern int dsda_auto_key_frame_depth;
extern int dsda_strict_mode;
extern int dsda_cycle_ghost_colors;
extern int dsda_exhud;
extern int dsda_track_attempts;
extern int dsda_wipe_at_full_speed;
extern int dsda_fine_sensitivity;

void dsda_InitSettings();
int dsda_CompatibilityLevel();
void dsda_ChangeStrictMode();
void dsda_SetTas();
double dsda_FineSensitivity(int base);
dboolean dsda_StrictMode();
dboolean dsda_CycleGhostColors();
dboolean dsda_AlwaysSR50();
dboolean dsda_ExHud();
dboolean dsda_TrackAttempts();
dboolean dsda_ShowHealthBars();
dboolean dsda_PainPalette();
dboolean dsda_BonusPalette();
dboolean dsda_PowerPalette();
dboolean dsda_WipeAtFullSpeed();
int dsda_RealticClockRate();
int dsda_AutoKeyFrameInterval();
int dsda_AutoKeyFrameDepth();
void dsda_SkipNextWipe();
dboolean dsda_SkipWipe();

#endif
