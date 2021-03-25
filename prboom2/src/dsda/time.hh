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
//	DSDA Time
//

#ifndef __DSDA_TIME__
#define __DSDA_TIME__

typedef enum {
  dsda_timer_displaytime,
  dsda_timer_tic,
  dsda_timer_realtime,
  DSDA_TIMER_COUNT
} dsda_timer_t;

void dsda_StartTimer(int timer);
unsigned long long dsda_ElapsedTime(int timer);

#endif
