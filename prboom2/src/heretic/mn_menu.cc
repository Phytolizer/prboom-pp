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

// MN_menu.c

#include "doomstat.hh"
#include "w_wad.hh"
#include "v_video.hh"
#include "m_menu.hh"
#include "heretic/dstrings.hh"
#include "heretic/mn_menu.hh"

#define ITEM_HEIGHT 20
#define SELECTOR_XOFFSET (-28)
#define SELECTOR_YOFFSET (-1)
#define SCREENSIZE_INDEX 5
#define MOUSE_HORIZ_INDEX 1
#define MOUSE_VERT_INDEX 3
#define MOUSE_MLOOK_INDEX 5
#define MOUSE_ACCEL_INDEX 7
#define SFX_VOL_INDEX 1
#define MUS_VOL_INDEX 3

static int FontABaseLump;
static int FontBBaseLump;
static int SkullBaseLump;
static int MenuTime;

static void MN_InitFonts(void)
{
  FontABaseLump = W_GetNumForName(DEH_String("FONTA_S")) + 1;
  FontBBaseLump = W_GetNumForName(DEH_String("FONTB_S")) + 1;
}

extern menu_t MainDef;
extern menu_t EpiDef;
extern menu_t NewDef;
extern menu_t OptionsDef;
extern menu_t SetupDef;
extern menu_t MouseDef;
extern menu_t SoundDef;
extern menu_t LoadDef;
extern menu_t SaveDef;
extern menuitem_t EpisodeMenu[];
extern menuitem_t NewGameMenu[];
extern menuitem_t SoundMenu[];
extern short EpiMenuMap[];
extern short EpiMenuEpi[];

void M_DrawThermo(int x, int y, int thermWidth, int thermDot);

void MN_Init(void)
{
  MN_InitFonts();
  SkullBaseLump = W_GetNumForName(DEH_String("M_SKL00"));

  // override doom menu parameters

  MainDef.x = 110;
  MainDef.y = 56;

  EpiDef.x = 80;
  EpiDef.y = 50;

  NewDef.x = 38;
  NewDef.y = 30;

  OptionsDef.x = 88;
  OptionsDef.y = 16;

  SetupDef.x = OptionsDef.x;
  SetupDef.y = OptionsDef.y;

  MouseDef.x = OptionsDef.x;
  MouseDef.y = OptionsDef.y;

  SoundDef.x = OptionsDef.x;
  SoundDef.y = OptionsDef.y;

  LoadDef.x = 70;
  LoadDef.y = 30;
  LoadDef.numitems = 6;

  SaveDef.x = 70;
  SaveDef.y = 30;
  SaveDef.numitems = 6;

  EpisodeMenu[0].alttext = "CITY OF THE DAMNED";
  EpisodeMenu[1].alttext = "HELL'S MAW";
  EpisodeMenu[2].alttext = "THE DOME OF D'SPARIL";
  EpisodeMenu[3].alttext = "THE OSSUARY";
  EpisodeMenu[4].alttext = "THE STAGNANT DEMESNE";

  NewGameMenu[0].alttext = "THOU NEEDETH A WET-NURSE";
  NewGameMenu[1].alttext = "YELLOWBELLIES-R-US";
  NewGameMenu[2].alttext = "BRINGEST THEM ONETH";
  NewGameMenu[3].alttext = "THOU ART A SMITE-MEISTER";
  NewGameMenu[4].alttext = "BLACK PLAGUE POSSESSES THEE";

  SoundMenu[0].alttext = "SFX VOLUME";
  SoundMenu[2].alttext = "MUSIC VOLUME";

  if (gamemode == retail)
  {
    EpiMenuEpi[3] = 4;
    EpiMenuEpi[4] = 5;
    EpiMenuMap[3] = 1;
    EpiMenuMap[4] = 1;
    EpiDef.numitems = 5;
    EpiDef.y -= ITEM_HEIGHT;
  }
  else
  {
    EpiMenuEpi[3] = -1;
    EpiMenuEpi[4] = -1;
    EpiMenuMap[3] = -1;
    EpiMenuMap[4] = -1;
    EpiDef.numitems = 3;
  }
}

void MN_Ticker(void)
{
    if (!menuactive)
    {
        return;
    }
    MenuTime++;
}

extern menu_t* currentMenu;
extern short itemOn;
extern int showMessages;
extern int screenSize;

void MN_DrawMessage(const char* messageString)
{
  char *msg;
  char *p;
  int y;

  msg = strdup(messageString);
  p = msg;
  y = 100 - MN_TextAHeight(msg) / 2;

  while (*p)
  {
    char *text;
    char c;

    text = p;
    while ((c = *p) && *p != '\n')
      p++;
    *p = 0;

    MN_DrTextA(text, 160 - MN_TextAWidth(text) / 2, y);
    y += R_NumPatchHeight(FontABaseLump);

    if ((*p = c))
      p++;
  }
  free(msg);
}

void MN_Drawer(void)
{
  int i;
  int x;
  int y;
  int max;
  const char* selName;

  x = currentMenu->x;
  y = currentMenu->y;
  max = currentMenu->numitems;

  for (i = 0; i < max; i++)
  {
    const char *text = currentMenu->menuitems[i].alttext;
    if (text)
      MN_DrTextB(DEH_String(text), x, y);
    y += ITEM_HEIGHT;
  }

  y = currentMenu->y + (itemOn * ITEM_HEIGHT) + SELECTOR_YOFFSET;
  selName = DEH_String(MenuTime & 16 ? "M_SLCTR1" : "M_SLCTR2");
  V_DrawNamePatch(x + SELECTOR_XOFFSET, y, 0, selName, CR_DEFAULT, VPT_STRETCH);
  // MenuItem_t *item;
  // const char *message;
  // const char *selName;
  //
  // if (MenuActive == false)
  // {
  //   if (askforquit)
  //   {
  //     message = DEH_String(QuitEndMsg[typeofask - 1]);
  //
  //     MN_DrTextA(message, 160 - MN_TextAWidth(message) / 2, 80);
  //     if (typeofask == 3)
  //     {
  //       MN_DrTextA(SlotText[quicksave - 1], 160 -
  //                  MN_TextAWidth(SlotText[quicksave - 1]) / 2, 90);
  //       MN_DrTextA(DEH_String("?"), 160 +
  //                  MN_TextAWidth(SlotText[quicksave - 1]) / 2, 90);
  //     }
  //     if (typeofask == 4)
  //     {
  //       MN_DrTextA(SlotText[quickload - 1], 160 -
  //                  MN_TextAWidth(SlotText[quickload - 1]) / 2, 90);
  //       MN_DrTextA(DEH_String("?"), 160 +
  //                  MN_TextAWidth(SlotText[quickload - 1]) / 2, 90);
  //     }
  //     UpdateState |= I_FULLSCRN;
  //   }
  //   return;
  // }
  // else
  // {
  //   UpdateState |= I_FULLSCRN;
  //   if (InfoType)
  //   {
  //     MN_DrawInfo();
  //     return;
  //   }
  //   if (screenblocks < 10)
  //   {
  //     BorderNeedRefresh = true;
  //   }
  //   if (CurrentMenu->drawFunc != NULL)
  //   {
  //     CurrentMenu->drawFunc();
  //   }
  //   x = CurrentMenu->x;
  //   y = CurrentMenu->y;
  //   item = CurrentMenu->items;
  //   for (i = 0; i < CurrentMenu->itemCount; i++)
  //   {
  //     if (item->type != ITT_EMPTY && item->text)
  //     {
  //       MN_DrTextB(DEH_String(item->text), x, y);
  //     }
  //
  //     y += ITEM_HEIGHT;
  //     item++;
  //   }
  //
  //   y = CurrentMenu->y + (CurrentItPos * ITEM_HEIGHT) + SELECTOR_YOFFSET;
  //   selName = DEH_String(MenuTime & 16 ? "M_SLCTR1" : "M_SLCTR2");
  //   V_DrawPatch(x + SELECTOR_XOFFSET, y,
  //               W_CacheLumpName(selName, PU_CACHE));
  // }
}

void MN_DrawMainMenu(void)
{
  int frame;

  frame = (MenuTime / 3) % 18;
  V_DrawNamePatch(88, 0, 0, DEH_String("M_HTIC"), CR_DEFAULT, VPT_STRETCH);
  V_DrawNumPatch(40, 10, 0, SkullBaseLump + (17 - frame), CR_DEFAULT, VPT_STRETCH);
  V_DrawNumPatch(232, 10, 0, SkullBaseLump + frame, CR_DEFAULT, VPT_STRETCH);
}

void MN_DrawOptions(void)
{
    if (showMessages)
    {
        MN_DrTextB(DEH_String("ON"), 196, OptionsDef.y + 3 * ITEM_HEIGHT);
    }
    else
    {
        MN_DrTextB(DEH_String("OFF"), 196, OptionsDef.y + 3 * ITEM_HEIGHT);
    }
    MN_DrawSlider(OptionsDef.x - 8, OptionsDef.y + ITEM_HEIGHT * SCREENSIZE_INDEX, 9, screenSize);
}

void MN_DrawSetup(void)
{
  // nothing for heretic
}

extern int mouseSensitivity_mlook;
extern int mouse_acceleration;

void MN_DrawMouse(void)
{
  MN_DrawSlider(MouseDef.x - 8, MouseDef.y + ITEM_HEIGHT * MOUSE_HORIZ_INDEX,
                200, mouseSensitivity_horiz);

  MN_DrawSlider(MouseDef.x - 8, MouseDef.y + ITEM_HEIGHT * MOUSE_VERT_INDEX,
                200, mouseSensitivity_vert);

  //e6y
  MN_DrawSlider(MouseDef.x - 8, MouseDef.y + ITEM_HEIGHT * MOUSE_MLOOK_INDEX,
                200, mouseSensitivity_mlook);

  MN_DrawSlider(MouseDef.x - 8, MouseDef.y + ITEM_HEIGHT * MOUSE_ACCEL_INDEX,
                200, mouse_acceleration);
}

void MN_DrawSound(void)
{
  MN_DrawSlider(SoundDef.x - 8, SoundDef.y + ITEM_HEIGHT * SFX_VOL_INDEX, 16, snd_SfxVolume);

  MN_DrawSlider(SoundDef.x - 8, SoundDef.y + ITEM_HEIGHT * MUS_VOL_INDEX, 16, snd_MusicVolume);
}

extern char savegamestrings[10][SAVESTRINGSIZE];

static void MN_DrawFileSlots(int x, int y)
{
  int i;

  for (i = 0; i < 6; i++)
  {
    V_DrawNamePatch(x, y, 0, DEH_String("M_FSLOT"), CR_DEFAULT, VPT_STRETCH);
    MN_DrTextA(savegamestrings[i], x + 5, y + 5);
    y += ITEM_HEIGHT;
  }
}

void MN_DrawLoad(void)
{
  const char *title;

  title = DEH_String("LOAD GAME");

  MN_DrTextB(title, 160 - MN_TextBWidth(title) / 2, 10);
  MN_DrawFileSlots(LoadDef.x, LoadDef.y);
}

extern int saveStringEnter;
extern int saveSlot;

void MN_DrawSave(void)
{
  const char *title;

  title = DEH_String("SAVE GAME");

  MN_DrTextB(title, 160 - MN_TextBWidth(title) / 2, 10);
  MN_DrawFileSlots(SaveDef.x, SaveDef.y);

  if (saveStringEnter)
  {
    int i;

    i = MN_TextAWidth(savegamestrings[saveSlot]);
    MN_DrTextA("[", SaveDef.x + 5 + i, SaveDef.y + 5 + saveSlot * ITEM_HEIGHT); // [ is _ in font A
  }
}

void MN_DrawPause(void)
{
  const char *title;

  title = "PAUSE";
  MN_DrTextB(title, 160 - MN_TextBWidth(title) / 2, 10);
}

void MN_DrTextA(const char *text, int x, int y)
{
  char c;
  int lump;

  while ((c = *text++) != 0)
  {
    c = static_cast<char>(toupper(c));
    if (c < 33)
    {
      x += 5;
    }
    else
    {
      lump = FontABaseLump + c - 33;
      V_DrawNumPatch(x, y, 0, lump, CR_DEFAULT, VPT_STRETCH);
      x += R_NumPatchWidth(lump) - 1;
    }
  }
}

int MN_TextAHeight(const char *text)
{
  int i, line_height, total_height;

  line_height = R_NumPatchHeight(FontABaseLump);
  total_height = line_height;

  for (i = 0; text[i]; i++)
    if (text[i] == '\n')
      total_height += line_height;
  return total_height;
}

int MN_TextAWidth(const char *text)
{
  char c;
  int width;
  int lump;

  width = 0;
  while ((c = *text++) != 0)
  {
    c = static_cast<char>(toupper(c));
    if (c < 33)
    {
      width += 5;
    }
    else
    {
      lump = FontABaseLump + c - 33;
      width += R_NumPatchWidth(lump) - 1;
    }
  }
  return (width);
}

void MN_DrTextB(const char *text, int x, int y)
{
  char c;
  int lump;

  while ((c = *text++) != 0)
  {
    c = static_cast<char>(toupper(c));
    if (c < 33)
    {
      x += 8;
    }
    else
    {
      lump = FontBBaseLump + c - 33;
      V_DrawNumPatch(x, y, 0, lump, CR_DEFAULT, VPT_STRETCH);
      x += R_NumPatchWidth(lump) - 1;
    }
  }
}

int MN_TextBWidth(const char *text)
{
  char c;
  int width;
  int lump;

  width = 0;
  while ((c = *text++) != 0)
  {
    c = static_cast<char>(toupper(c));
    if (c < 33)
    {
      width += 5;
    }
    else
    {
      lump = FontBBaseLump + c - 33;
      width += R_NumPatchWidth(lump) - 1;
    }
  }
  return (width);
}

#define SLIDER_LIMIT 200
#define SLIDER_WIDTH (SLIDER_LIMIT - 64)
#define SLIDER_PATCH_COUNT (SLIDER_WIDTH / 8)

void MN_DrawSlider(int x, int y, int width, int slot)
{
  int x2;
  int count;
  char num[4];
  int slot_x;
  short slider_img = 0;

  width = (width > SLIDER_LIMIT) ? SLIDER_LIMIT : width;

  V_DrawNamePatch(x, y, 0, DEH_String("M_SLDLT"), CR_DEFAULT, VPT_STRETCH);

  for (x2 = x + 32, count = SLIDER_PATCH_COUNT; count--; x2 += 8)
  {
    const char* name;

    name = DEH_String(slider_img & 1 ? "M_SLDMD1" : "M_SLDMD2");
    slider_img ^= 1;

    V_DrawNamePatch(x2, y, 0, name, CR_DEFAULT, VPT_STRETCH);
  }

  V_DrawNamePatch(x2, y, 0, DEH_String("M_SLDRT"), CR_DEFAULT, VPT_STRETCH);

  // [crispy] print the value
  snprintf(num, 4, "%3d", slot);
  MN_DrTextA(num, x2 + 32, y + 3);

  // [crispy] do not crash anymore if the value is out of bounds
  if (slot >= width)
  {
    slot = width - 1;
  }

  slot_x = x + 36 + (SLIDER_WIDTH - 8) * slot / (width - 1);

  V_DrawNamePatch(slot_x, y + 7, 0, DEH_String("M_SLDKB"), CR_DEFAULT, VPT_STRETCH);
}
