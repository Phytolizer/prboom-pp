//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 1993-2008 Raven Software
// Copyright(C) 2005-2014 Simon Howard
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
// F_finale.c

#include "doomstat.hh"
#include "w_wad.hh"
#include "v_video.hh"
#include "s_sound.hh"
#include "sounds.hh"

#include "dsda/palette.hh"

#include "heretic/def.hh"
#include "heretic/dstrings.hh"

#include "heretic/f_finale.hh"

static int finalestage;                // 0 = text, 1 = art screen
static int finalecount;

#define TEXTSPEED       3
#define TEXTWAIT        250

static const char *finaletext;
static const char *finaleflat;

static int FontABaseLump;

extern enum automapmode_e automapmode;

/*
=======================
=
= F_StartFinale
=
=======================
*/

void Heretic_F_StartFinale(void)
{
  gameaction = ga_nothing;
  gamestate = GS_FINALE;
  automapmode &= ~am_active;

  switch (gameepisode)
  {
    case 1:
      finaleflat = DEH_String("FLOOR25");
      finaletext = DEH_String(HERETIC_E1TEXT);
      break;
    case 2:
      finaleflat = DEH_String("FLATHUH1");
      finaletext = DEH_String(HERETIC_E2TEXT);
      break;
    case 3:
      finaleflat = DEH_String("FLTWAWA2");
      finaletext = DEH_String(HERETIC_E3TEXT);
      break;
    case 4:
      finaleflat = DEH_String("FLOOR28");
      finaletext = DEH_String(HERETIC_E4TEXT);
      break;
    case 5:
      finaleflat = DEH_String("FLOOR08");
      finaletext = DEH_String(HERETIC_E5TEXT);
      break;
  }

  finalestage = 0;
  finalecount = 0;
  FontABaseLump = W_GetNumForName(DEH_String("FONTA_S")) + 1;
  S_ChangeMusic(heretic_mus_cptd, true);
}

dboolean Heretic_F_Responder(event_t * event)
{
  if (event->type != ev_keydown)
  {
    return false;
  }
  if (finalestage == 1 && gameepisode == 2)
  {                           // we're showing the water pic, make any key kick to demo mode
    finalestage++;
    return true;
  }
  return false;
}

/*
=======================
=
= F_Ticker
=
=======================
*/

void Heretic_F_Ticker(void)
{
  finalecount++;
  if (!finalestage && finalecount > strlen(finaletext) * TEXTSPEED + TEXTWAIT)
  {
    finalecount = 0;
    if (!finalestage)
    {
      finalestage = 1;
    }
  }
}

/*
=======================
=
= F_TextWrite
=
=======================
*/

void Heretic_F_TextWrite(void)
{
  int x, y;
  int count;
  const char *ch;
  int c;
  int cx, cy;
  int lump;
  int width;

  //
  // erase the entire screen to a tiled background
  //
  V_DrawBackground(finaleflat, 0);

  // e6y: wide-res
  V_FillBorder(-1, 0);

  //
  // draw some of the text onto the screen
  //
  cx = 20;
  cy = 5;
  ch = finaletext;

  count = (finalecount - 10) / TEXTSPEED;
  if (count < 0)
    count = 0;
  for (; count; count--)
  {
    c = *ch++;
    if (!c)
      break;
    if (c == '\n')
    {
      cx = 20;
      cy += 9;
      continue;
    }

    c = toupper(c);
    if (c < 33)
    {
      cx += 5;
      continue;
    }

    lump = FontABaseLump + c - 33;
    width = R_NumPatchWidth(lump);
    if (cx + width > SCREENWIDTH)
      break;
    V_DrawNumPatch(cx, cy, 0, lump, CR_DEFAULT, VPT_STRETCH);
    cx += width;
  }
}

/*
==================
=
= F_DemonScroll
=
==================
*/

void F_DemonScroll(void)
{
  const byte *p1, *p2;
  static int yval = 0;
  static int nextscroll = 0;

  if (finalecount < nextscroll)
  {
    return;
  }

  p1 = W_CacheLumpName(DEH_String("FINAL1"));
  p2 = W_CacheLumpName(DEH_String("FINAL2"));

  if (finalecount < 70)
  {
    V_DrawRawScreen(p1);
    nextscroll = finalecount;
  }
  else if (yval < 200)
  {
    V_DrawRawScreenSection(p2 + (200 - yval) * 320, 0, yval);
    V_DrawRawScreenSection(p1, yval, 200 - yval);
    yval++;
    nextscroll = finalecount + 3;
  }
  else
  {                           //else, we'll just sit here and wait, for now
    V_DrawRawScreen(p2);
  }

  W_UnlockLumpName(DEH_String("FINAL1"));
  W_UnlockLumpName(DEH_String("FINAL2"));
}

/*
==================
=
= F_DrawUnderwater
=
==================
*/

void F_DrawUnderwater(void)
{
  switch (finalestage)
  {
    case 1:
      V_SetPlayPal(playpal_heretic_e2end);
      V_DrawRawScreen(W_CacheLumpName(DEH_String("E2END")));
      W_UnlockLumpName(DEH_String("E2END"));
      V_SetPlayPal(playpal_default);

      break;
    case 2:
      V_DrawRawScreen(W_CacheLumpName(DEH_String("TITLE")));
      W_UnlockLumpName(DEH_String("TITLE"));
  }
}

/*
=======================
=
= F_Drawer
=
=======================
*/

void Heretic_F_Drawer(void)
{
  // UpdateState |= I_FULLSCRN;
  if (!finalestage)
    Heretic_F_TextWrite();
  else
  {
    switch (gameepisode)
    {
      case 1:
        if (gamemode == shareware)
        {
          V_DrawRawScreen(W_CacheLumpName("ORDER"));
          W_UnlockLumpName("ORDER");
        }
        else
        {
          V_DrawRawScreen(W_CacheLumpName("CREDIT"));
          W_UnlockLumpName("CREDIT");
        }
        break;
      case 2:
        F_DrawUnderwater();
        break;
      case 3:
        F_DemonScroll();
        break;
      case 4:            // Just show credits screen for extended episodes
      case 5:
        V_DrawRawScreen(W_CacheLumpName("CREDIT"));
        W_UnlockLumpName("CREDIT");
        break;
    }
  }
}
