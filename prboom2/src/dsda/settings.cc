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

#include "doomstat.hh"
#include "m_argv.hh"
#include "e6y.hh"
#include "r_things.hh"

#include "settings.hh"

int dsda_auto_key_frame_interval;
int dsda_auto_key_frame_depth;
int dsda_strict_mode;
int dsda_cycle_ghost_colors;
int dsda_exhud;
int dsda_tas;
int dsda_skip_next_wipe;
int dsda_wipe_at_full_speed;
int dsda_track_attempts;
int dsda_fine_sensitivity;

void dsda_InitSettings()
{
    dsda_ChangeStrictMode();
}

int dsda_CompatibilityLevel()
{
    int i, level;

    if (heretic)
    {
        return doom_12_compatibility;
    }

    i = M_CheckParm("-complevel");

    if (i && (i + 1 < myargc))
    {
        level = atoi(myargv[i + 1]);

        if (level >= -1)
        {
            return level;
        }
    }

    return UNSPECIFIED_COMPLEVEL;
}

void dsda_ChangeStrictMode()
{
    I_Init2();       // side effect of realtic clock rate
    M_ChangeSpeed(); // side effect of always sr50
}

void dsda_SetTas()
{
    dsda_tas = true;
}

double dsda_FineSensitivity(int base)
{
    return (double)base + (double)dsda_fine_sensitivity / 100;
}

dboolean dsda_StrictMode()
{
    return dsda_strict_mode && demorecording && !dsda_tas;
}

dboolean dsda_CycleGhostColors()
{
    return dsda_cycle_ghost_colors;
}

dboolean dsda_AlwaysSR50()
{
    return movement_strafe50 && !dsda_StrictMode();
}

dboolean dsda_ExHud()
{
    return dsda_exhud;
}

dboolean dsda_TrackAttempts()
{
    return dsda_track_attempts && demorecording;
}

dboolean dsda_PainPalette()
{
    return dsda_StrictMode() || palette_ondamage;
}

dboolean dsda_BonusPalette()
{
    return dsda_StrictMode() || palette_onbonus;
}

dboolean dsda_PowerPalette()
{
    return dsda_StrictMode() || palette_onpowers;
}

dboolean dsda_ShowHealthBars()
{
    return health_bar && !dsda_StrictMode();
}

dboolean dsda_WipeAtFullSpeed()
{
    return dsda_wipe_at_full_speed;
}

int dsda_RealticClockRate()
{
    if (dsda_StrictMode())
    {
        return 100;
    }

    return realtic_clock_rate;
}

int dsda_AutoKeyFrameInterval()
{
    if (dsda_StrictMode())
    {
        return 0;
    }

    return dsda_auto_key_frame_interval;
}

int dsda_AutoKeyFrameDepth()
{
    if (dsda_StrictMode())
    {
        return 0;
    }

    return dsda_auto_key_frame_depth;
}

void dsda_SkipNextWipe()
{
    dsda_skip_next_wipe = 1;
}

dboolean dsda_SkipWipe()
{
    if (dsda_skip_next_wipe)
    {
        dsda_skip_next_wipe = 0;
        return true;
    }

    return !render_wipescreen;
}
