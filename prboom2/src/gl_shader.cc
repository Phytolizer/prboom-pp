/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef USE_SHADERS

#include <SDL.h>
#include <SDL_opengl.h>
#include <math.h>
#include "doomstat.hh"
#include "v_video.hh"
#include "gl_opengl.hh"
#include "gl_intern.hh"
#include "r_main.hh"
#include "w_wad.hh"
#include "i_system.hh"
#include "r_bsp.hh"
#include "lprintf.hh"
#include "e6y.hh"
#include "r_things.hh"

GLShader *sh_main = nullptr;
static GLShader *active_shader = nullptr;

static GLShader *gld_LoadShader(const char *vpname, const char *fpname);

int glsl_Init(void)
{
    static int init = false;

    // if (!init)
    {
        init = true;

        if (!gl_arb_shader_objects)
        {
            lprintf(LO_WARN, "glsl_Init: shaders expects OpenGL 2.0\n");
        }
        else
        {
            sh_main = gld_LoadShader("glvp", "glfp");
        }
    }

    return (sh_main != nullptr);
}

static int ReadLump(const char *filename, const char *lumpname,
                    unsigned char **buffer)
{
    FILE *file = nullptr;
    int size = 0;
    const unsigned char *data;
    int lump;

    file = fopen(filename, "r");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        fseek(file, 0, SEEK_SET);
        *buffer = static_cast<unsigned char *>(std::malloc(size + 1));
        size = fread(*buffer, 1, size, file);
        if (size > 0)
        {
            (*buffer)[size] = 0;
        }
        fclose(file);
    }
    else
    {
        char name[9];
        char *p;

        strncpy(name, lumpname, 9);
        name[8] = 0;
        for (p = name; *p; p++)
        {
            *p = toupper(*p);
        }

        lump = (W_CheckNumForName)(name, ns_prboom);

        if (lump != -1)
        {
            size = W_LumpLength(lump);
            data = static_cast<const unsigned char *>(W_CacheLumpNum(lump));
            *buffer = static_cast<unsigned char *>(std::calloc(1, size + 1));
            memcpy(*buffer, data, size);
            (*buffer)[size] = 0;
            W_UnlockLumpNum(lump);
        }
    }

    return size;
}

static GLShader *gld_LoadShader(const char *vpname, const char *fpname)
{
#define buffer_size 2048
    int idx;
    int linked;
    char buffer[buffer_size];
    char *vp_data = nullptr;
    char *fp_data = nullptr;
    int vp_size, fp_size;
    size_t vp_fnlen, fp_fnlen;
    char *filename = nullptr;
    GLShader *shader = nullptr;

    vp_fnlen =
        doom_snprintf(nullptr, 0, "%s/shaders/%s.txt", I_DoomExeDir(), vpname);
    fp_fnlen =
        doom_snprintf(nullptr, 0, "%s/shaders/%s.txt", I_DoomExeDir(), fpname);
    filename = static_cast<char *>(std::malloc(MAX(vp_fnlen, fp_fnlen) + 1));

    sprintf(filename, "%s/shaders/%s.txt", I_DoomExeDir(), vpname);
    vp_size = ReadLump(filename, vpname,
                       reinterpret_cast<unsigned char **>(&vp_data));

    sprintf(filename, "%s/shaders/%s.txt", I_DoomExeDir(), fpname);
    fp_size = ReadLump(filename, fpname,
                       reinterpret_cast<unsigned char **>(&fp_data));

    if (vp_data && fp_data)
    {
        shader = static_cast<GLShader *>(calloc(1, sizeof(GLShader)));

        shader->hVertProg = GLEXT_glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
        shader->hFragProg =
            GLEXT_glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

        GLEXT_glShaderSourceARB(shader->hVertProg, 1,
                                const_cast<const GLcharARB **>(&vp_data),
                                &vp_size);
        GLEXT_glShaderSourceARB(shader->hFragProg, 1,
                                const_cast<const GLcharARB **>(&fp_data),
                                &fp_size);

        GLEXT_glCompileShaderARB(shader->hVertProg);
        GLEXT_glCompileShaderARB(shader->hFragProg);

        shader->hShader = GLEXT_glCreateProgramObjectARB();

        GLEXT_glAttachObjectARB(shader->hShader, shader->hVertProg);
        GLEXT_glAttachObjectARB(shader->hShader, shader->hFragProg);

        GLEXT_glLinkProgramARB(shader->hShader);

        GLEXT_glGetInfoLogARB(shader->hShader, buffer_size, nullptr, buffer);

        GLEXT_glGetObjectParameterivARB(shader->hShader,
                                        GL_OBJECT_LINK_STATUS_ARB, &linked);

        if (linked)
        {
            lprintf(LO_INFO,
                    "gld_LoadShader: Shader \"%s+%s\" compiled OK: %s\n",
                    vpname, fpname, buffer);

            shader->lightlevel_index =
                GLEXT_glGetUniformLocationARB(shader->hShader, "lightlevel");

            GLEXT_glUseProgramObjectARB(shader->hShader);

            idx = GLEXT_glGetUniformLocationARB(shader->hShader, "tex");
            GLEXT_glUniform1iARB(idx, 0);

            GLEXT_glUseProgramObjectARB(0);
        }
        else
        {
            lprintf(LO_ERROR,
                    "gld_LoadShader: Error compiling shader \"%s+%s\": %s\n",
                    vpname, fpname, buffer);
            free(shader);
            shader = nullptr;
        }
    }

    std::free(filename);
    std::free(vp_data);
    std::free(fp_data);

    return shader;
}

void glsl_SetActiveShader(GLShader *shader)
{
    if (gl_lightmode == gl_lightmode_shaders)
    {
        if (shader != active_shader)
        {
            GLEXT_glUseProgramObjectARB((shader ? shader->hShader : 0));
            active_shader = shader;
        }
    }
}

void glsl_SetLightLevel(float lightlevel)
{
    if (sh_main)
    {
        GLEXT_glUniform1fARB(sh_main->lightlevel_index, lightlevel);
    }
}

int glsl_IsActive(void)
{
    return (gl_lightmode == gl_lightmode_shaders && sh_main);
}

#endif // USE_SHADERS
