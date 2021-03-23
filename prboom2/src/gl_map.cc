/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright 2006 - 2008 G Jackson, Jaakko Kerônen
 *  Copyright 2009 - Andrey Budko
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
 * DESCRIPTION: Cool automap things
 *
 *---------------------------------------------------------------------
 */

#include "gl_struct.hh"
#include <array>
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cmath>

#include "SDL.h"
#ifdef HAVE_LIBSDL2_IMAGE
#include "SDL_image.h"
#endif

#include "gl_opengl.hh"
#include "gl_intern.hh"
#include "w_wad.hh"
#include "m_misc.hh"
#include "am_map.hh"
#include "lprintf.hh"

am_icon_t am_icons[am_icon_count + 1] = {
    {static_cast<GLuint>(-1), "M_SHADOW"},

    {static_cast<GLuint>(-1), "M_ARROW"},
    {static_cast<GLuint>(-1), "M_NORMAL"},
    {static_cast<GLuint>(-1), "M_HEALTH"},
    {static_cast<GLuint>(-1), "M_ARMOUR"},
    {static_cast<GLuint>(-1), "M_AMMO"},
    {static_cast<GLuint>(-1), "M_KEY"},
    {static_cast<GLuint>(-1), "M_POWER"},
    {static_cast<GLuint>(-1), "M_WEAP"},

    {static_cast<GLuint>(-1), "M_ARROW"},
    {static_cast<GLuint>(-1), "M_ARROW"},
    {static_cast<GLuint>(-1), "M_ARROW"},
    {static_cast<GLuint>(-1), "M_MARK"},
    {static_cast<GLuint>(-1), "M_NORMAL"},

    {static_cast<GLuint>(-1), nullptr},
};

using map_nice_thing_t = struct map_nice_thing_s
{
    vbo_xy_uv_rgba_t v[4];
};

static std::array<std::vector<map_nice_thing_t>, am_icon_count> map_things;

void gld_InitMapPics()
{
    int i, lump;

    i = 0;
    while (am_icons[i].name)
    {
        lump = (W_CheckNumForName)(am_icons[i].name, ns_prboom);
        am_icons[i].lumpnum = lump;
        if (lump != -1)
        {
            SDL_Surface *surf = nullptr;
#ifdef HAVE_LIBSDL2_IMAGE
            SDL_Surface *surf_raw;

            surf_raw = IMG_Load_RW(
                SDL_RWFromConstMem(W_CacheLumpNum(lump), W_LumpLength(lump)),
                true);

            surf = SDL_ConvertSurface(surf_raw, &RGBAFormat, 0);
            SDL_FreeSurface(surf_raw);
#endif

            W_UnlockLumpNum(lump);

            if (surf)
            {
                glGenTextures(1, &am_icons[i].tex_id);
                glBindTexture(GL_TEXTURE_2D, am_icons[i].tex_id);

                if (gl_arb_texture_non_power_of_two)
                {
                    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
                    glTexImage2D(GL_TEXTURE_2D, 0, gl_tex_format, surf->w,
                                 surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                                 surf->pixels);
                }
                else
                {
                    gluBuild2DMipmaps(GL_TEXTURE_2D, gl_tex_format, surf->w,
                                      surf->h, GL_RGBA, GL_UNSIGNED_BYTE,
                                      surf->pixels);
                }

                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR); // tex_filter[MIP_PATCH].min_filter);
                glTexParameteri(
                    GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR); // tex_filter[MIP_PATCH].mag_filter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

                SDL_FreeSurface(surf);
            }
        }

        i++;
    }
}

void gld_AddNiceThing(int type, float x, float y, float radius, float angle,
                      unsigned char r, unsigned char g, unsigned char b,
                      unsigned char a)
{
    map_things[type].emplace_back();
    map_nice_thing_t &thing = map_things[type].back();

    float sina_r = (float)sin(angle) * radius;
    float cosa_r = (float)cos(angle) * radius;

#define MAP_NICE_THING_INIT(index, _x, _y, _u, _v)                             \
    {                                                                          \
        thing.v[index].x = _x;                                                \
        thing.v[index].y = _y;                                                \
        thing.v[index].u = _u;                                                \
        thing.v[index].v = _v;                                                \
        thing.v[index].r = r;                                                 \
        thing.v[index].g = g;                                                 \
        thing.v[index].b = b;                                                 \
        thing.v[index].a = a;                                                 \
    }

    MAP_NICE_THING_INIT(0, x + sina_r + cosa_r, y - cosa_r + sina_r, 1.0f,
                        0.0f);
    MAP_NICE_THING_INIT(1, x + sina_r - cosa_r, y - cosa_r - sina_r, 0.0f,
                        0.0f);
    MAP_NICE_THING_INIT(2, x - sina_r - cosa_r, y + cosa_r - sina_r, 0.0f,
                        1.0f);
    MAP_NICE_THING_INIT(3, x - sina_r + cosa_r, y + cosa_r + sina_r, 1.0f,
                        1.0f);

#undef MAP_NICE_THING_INIT
}

void gld_DrawNiceThings(int fx, int fy, int fw, int fh)
{
    int i;
    int j;

    glScissor(fx, SCREENHEIGHT - (fy + fh), fw, fh);
    glEnable(GL_SCISSOR_TEST);

    glDisable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gld_EnableTexture2D(GL_TEXTURE0_ARB, true);

#if defined(USE_VERTEX_ARRAYS) || defined(USE_VBO)
    // activate vertex array, texture coord array and color arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
#endif

    for (i = 0; i < am_icon_count; i++)
    {
        std::vector<map_nice_thing_t> &things = map_things[i];

        if (things.empty())
        {
            continue;
        }

        glBindTexture(GL_TEXTURE_2D, am_icons[i].tex_id);

#if defined(USE_VERTEX_ARRAYS) || defined(USE_VBO)
        {
            map_nice_thing_t &thing = things[0];

            // activate and specify pointers to arrays
            glVertexPointer(2, GL_FLOAT, sizeof(thing.v[0]), &thing.v[0].x);
            glTexCoordPointer(2, GL_FLOAT, sizeof(thing.v[0]), &thing.v[0].u);
            glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(thing.v[0]),
                           &thing.v[0].r);

            glDrawArrays(GL_QUADS, 0, things.size() * 4);
        }
#else
        for (j = 0; j < things->count; j++)
        {
            map_nice_thing_t *thing = &((map_nice_thing_t *)things->data)[j];

            glColor4ubv(&thing->v[0].r);

            glBegin(GL_TRIANGLE_FAN);
            {
                glTexCoord2f(thing->v[0].u, thing->v[0].v);
                glVertex2f(thing->v[0].x, thing->v[0].y);
                glTexCoord2f(thing->v[1].u, thing->v[1].v);
                glVertex2f(thing->v[1].x, thing->v[1].y);
                glTexCoord2f(thing->v[2].u, thing->v[2].v);
                glVertex2f(thing->v[2].x, thing->v[2].y);
                glTexCoord2f(thing->v[3].u, thing->v[3].v);
                glVertex2f(thing->v[3].x, thing->v[3].y);
            }
            glEnd();
        }
#endif
    }

#if defined(USE_VERTEX_ARRAYS) || defined(USE_VBO)
    // deactivate vertex array, texture coord array and color arrays
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
#endif

    gld_ResetLastTexture();
    glDisable(GL_SCISSOR_TEST);
}

void gld_ClearNiceThings()
{
    for (auto &thingsList : map_things)
    {
        thingsList.clear();
    }
}

void gld_DrawMapLines()
{
#if defined(USE_VERTEX_ARRAYS) || defined(USE_VBO)
    if (!map_lines.empty())
    {
        map_point_t &point = map_lines[0].point[0];

        gld_EnableTexture2D(GL_TEXTURE0_ARB, false);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(2, GL_FLOAT, sizeof(point), &point.x);
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(point), &point.r);

        glDrawArrays(GL_LINES, 0, map_lines.size() * 2);

        gld_EnableTexture2D(GL_TEXTURE0_ARB, true);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
#endif
}
