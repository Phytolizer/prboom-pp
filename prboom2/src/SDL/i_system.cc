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
 *  Misc system stuff needed by Doom, implemented for Linux.
 *  Mainly timer handling, and ENDOOM/ENDBOOM.
 *
 *-----------------------------------------------------------------------------
 */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdio.h>

#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#ifdef _MSC_VER
#define F_OK 0 /* Check for file existence */
#define W_OK 2 /* Check for write permission */
#define R_OK 4 /* Check for read permission */
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <sys/stat.h>

#include "SDL.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef _MSC_VER
#include <io.h>
#endif
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef PRBOOM_SERVER
#include "m_argv.hh"
#endif
#include "lprintf.hh"
#include "doomtype.hh"
#include "doomdef.hh"
#ifndef PRBOOM_SERVER
#include "d_player.hh"
#include "m_fixed.hh"
#include "r_fps.hh"
#include "e6y.hh"
#endif
#include "i_system.hh"

#ifdef __GNUG__
#pragma implementation "i_system.h"
#endif
#include "i_system.hh"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "z_zone.hh"

void I_uSleep(unsigned long usecs)
{
    SDL_Delay(usecs / 1000);
}

int ms_to_next_tick;

static int basetime = 0;
int I_GetTime_RealTime(void)
{
    int i;
    int t = SDL_GetTicks();

    // e6y: removing startup delay
    if (basetime == 0)
        basetime = t;
    t -= basetime;

    i = t * (TICRATE / 5) / 200;
    ms_to_next_tick = (i + 1) * 200 / (TICRATE / 5) - t;
    if (ms_to_next_tick > 1000 / TICRATE || ms_to_next_tick < 1)
        ms_to_next_tick = 1;
    return i;
}

#ifndef PRBOOM_SERVER
static unsigned int start_displaytime;
static unsigned int displaytime;
static dboolean InDisplay = false;
static int saved_gametic = -1;
dboolean realframe = false;

dboolean I_StartDisplay(void)
{
    if (InDisplay)
        return false;

    realframe = (!movement_smooth) || (gametic > saved_gametic);

    if (realframe)
        saved_gametic = gametic;

    start_displaytime = SDL_GetTicks();
    InDisplay = true;
    return true;
}

void I_EndDisplay(void)
{
    displaytime = SDL_GetTicks() - start_displaytime;
    InDisplay = false;
}

static int subframe = 0;
static int prevsubframe = 0;
int interpolation_method;
fixed_t I_GetTimeFrac(void)
{
    unsigned long now;
    fixed_t frac;

    now = SDL_GetTicks();

    subframe++;

    if (tic_vars.step == 0)
    {
        frac = FRACUNIT;
    }
    else
    {
        extern int renderer_fps;
        if ((interpolation_method == 0) || (prevsubframe <= 0) ||
            (renderer_fps <= 0))
        {
            frac = (fixed_t)((now - tic_vars.start + displaytime) * FRACUNIT /
                             tic_vars.step);
        }
        else
        {
            frac = (fixed_t)((now - tic_vars.start) * FRACUNIT / tic_vars.step);
            frac = (unsigned int)((float)FRACUNIT * TICRATE * subframe /
                                  renderer_fps);
        }
        frac = BETWEEN(0, FRACUNIT, frac);
    }

    return frac;
}

void I_GetTime_SaveMS(void)
{
    if (!movement_smooth)
        return;

    tic_vars.start = SDL_GetTicks();
    tic_vars.next =
        (unsigned int)((tic_vars.start * tic_vars.msec + 1.0f) / tic_vars.msec);
    tic_vars.step = tic_vars.next - tic_vars.start;
    prevsubframe = subframe;
    subframe = 0;
}
#endif

/*
 * I_GetRandomTimeSeed
 *
 * CPhipps - extracted from G_ReloadDefaults because it is O/S based
 */
unsigned long I_GetRandomTimeSeed(void)
{
    return (unsigned long)time(NULL);
}

/* cphipps - I_GetVersionString
 * Returns a version string in the given buffer
 */
const char *I_GetVersionString(char *buf, size_t sz)
{
    snprintf(buf, sz, "%s v%s (https://github.com/kraflab/dsda-doom/)",
             PACKAGE_NAME, PACKAGE_VERSION);
    return buf;
}

/* cphipps - I_SigString
 * Returns a string describing a signal number
 */
const char *I_SigString(char *buf, size_t sz, int signum)
{
#ifdef HAVE_STRSIGNAL
    if (strsignal(signum) && strlen(strsignal(signum)) < sz)
        strcpy(buf, strsignal(signum));
    else
#endif
        snprintf(buf, sz, "signal %d", signum);
    return buf;
}

#ifndef PRBOOM_SERVER
dboolean I_FileToBuffer(const char *filename, byte **data, int *size)
{
    FILE *hfile;

    dboolean result = false;
    byte *buffer = NULL;
    size_t filesize = 0;

    hfile = fopen(filename, "rb");
    if (hfile)
    {
        fseek(hfile, 0, SEEK_END);
        filesize = ftell(hfile);
        fseek(hfile, 0, SEEK_SET);

        buffer = (byte *)malloc(filesize);
        if (buffer)
        {
            if (fread(buffer, filesize, 1, hfile) == 1)
            {
                result = true;

                if (data)
                {
                    *data = buffer;
                }

                if (size)
                {
                    *size = filesize;
                }
            }
        }

        fclose(hfile);
    }

    if (!result)
    {
        free(buffer);
        buffer = NULL;
    }

    return result;
}
#endif // PRBOOM_SERVER

/*
 * I_Read
 *
 * cph 2001/11/18 - wrapper for read(2) which handles partial reads and aborts
 * on error.
 */
void I_Read(int fd, void *vbuf, size_t sz)
{
    unsigned char *buf = (unsigned char *)vbuf;

    while (sz)
    {
        int rc = read(fd, buf, sz);
        if (rc <= 0)
        {
            I_Error("I_Read: read failed: %s", rc ? strerror(errno) : "EOF");
        }
        sz -= rc;
        buf += rc;
    }
}

/*
 * I_Filelength
 *
 * Return length of an open file.
 */

int I_Filelength(int handle)
{
    struct stat fileinfo;
    if (fstat(handle, &fileinfo) == -1)
        I_Error("I_Filelength: %s", strerror(errno));
    return fileinfo.st_size;
}

#ifndef PRBOOM_SERVER

// Return the path where the executable lies -- Lee Killough
// proff_fs 2002-07-04 - moved to i_system
#ifdef _WIN32

void I_SwitchToWindow(HWND hwnd)
{
    typedef BOOL(WINAPI * TSwitchToThisWindow)(HWND wnd, BOOL restore);
    static TSwitchToThisWindow SwitchToThisWindow = NULL;

    if (!SwitchToThisWindow)
        SwitchToThisWindow = (TSwitchToThisWindow)GetProcAddress(
            GetModuleHandle("user32.dll"), "SwitchToThisWindow");

    if (SwitchToThisWindow)
    {
        HWND hwndLastActive = GetLastActivePopup(hwnd);

        if (IsWindowVisible(hwndLastActive))
            hwnd = hwndLastActive;

        SetForegroundWindow(hwnd);
        Sleep(100);
        SwitchToThisWindow(hwnd, TRUE);
    }
}

const char *I_DoomExeDir(void)
{
    static const char current_dir_dummy[] = {
        "."}; // proff - rem extra slash 8/21/03
    static char *base;
    if (!base) // cache multiple requests
    {
        size_t len = strlen(*myargv);
        char *p = (base = (char *)malloc(len + 1)) + len - 1;
        strcpy(base, *myargv);
        while (p > base && *p != '/' && *p != '\\')
            *p-- = 0;
        if (*p == '/' || *p == '\\')
            *p-- = 0;
        if (strlen(base) < 2 || access(base, W_OK) != 0)
        {
            free(base);
            base = (char *)malloc(1024);
            if (!getcwd(base, 1024) || access(base, W_OK) != 0)
                strcpy(base, current_dir_dummy);
        }
    }
    return base;
}

const char *I_GetTempDir(void)
{
    static char tmp_path[PATH_MAX] = {0};

    if (tmp_path[0] == 0)
    {
        GetTempPath(sizeof(tmp_path), tmp_path);
    }

    return tmp_path;
}

#elif defined(AMIGA)

const char *I_DoomExeDir(void)
{
    return "PROGDIR:";
}

const char *I_GetTempDir(void)
{
    return "PROGDIR:";
}

#elif defined(MACOSX)

/* Defined elsewhere */

#else
// cph - V.Aguilar (5/30/99) suggested return ~/.lxdoom/, creating
//  if non-existant
// cph 2006/07/23 - give prboom+ its own dir
static const char prboom_dir[] = {
    "/.dsda-doom"}; // Mead rem extra slash 8/21/03

const char *I_DoomExeDir(void)
{
    static char *base;
    if (!base) // cache multiple requests
    {
        char *home = getenv("HOME");
        size_t len = strlen(home);

        base = malloc<char *>(len + strlen(prboom_dir) + 1);
        strcpy(base, home);
        // I've had trouble with trailing slashes before...
        if (base[len - 1] == '/')
            base[len - 1] = 0;
        strcat(base, prboom_dir);
        mkdir(base, S_IRUSR | S_IWUSR | S_IXUSR); // Make sure it exists
    }
    return base;
}

const char *I_GetTempDir(void)
{
    return "/tmp";
}

#endif

/*
 * HasTrailingSlash
 *
 * cphipps - simple test for trailing slash on dir names
 */

dboolean HasTrailingSlash(const char *dn)
{
    return ((dn[strlen(dn) - 1] == '/')
#if defined(_WIN32)
            || (dn[strlen(dn) - 1] == '\\')
#endif
#if defined(AMIGA)
            || (dn[strlen(dn) - 1] == ':')
#endif
    );
}

/*
 * I_FindFile
 *
 * proff_fs 2002-07-04 - moved to i_system
 *
 * cphipps 19/1999 - writen to unify the logic in FindIWADFile and the WAD
 *      autoloading code.
 * Searches the standard dirs for a named WAD file
 * The dirs are listed at the start of the function
 */

#ifndef MACOSX /* OSX defines its search paths elsewhere. */

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

char *I_FindFileInternal(const char *wfname, const char *ext, dboolean isStatic)
{
    // lookup table of directories to search
    static struct search_t
    {
        const char *dir;           // directory
        const char *sub;           // subdirectory
        const char *env;           // environment variable
        const char *(*func)(void); // for I_DoomExeDir
    } search0[] =
        {
            {NULL, NULL, NULL, I_DoomExeDir}, // config directory
            {NULL},                           // current working directory
            {NULL, NULL, "DOOMWADDIR"},       // run-time $DOOMWADDIR
            {DOOMWADDIR},           // build-time configured DOOMWADDIR
            {NULL, "doom", "HOME"}, // ~/doom
            {NULL, "doom/iwad", "HOME"}, // ~/doom/iwad
            {NULL, "doom/pwad", "HOME"}, // ~/doom/pwad
            {NULL, NULL, "HOME"},   // ~
            {"/usr/local/share/games/doom"},
            {"/usr/share/games/doom"},
            {"/usr/local/share/doom"},
            {"/usr/share/doom"},
        },
      *search;

    static size_t num_search;
    size_t i;
    size_t pl;

    static char static_p[PATH_MAX];
    char *dinamic_p = NULL;
    char *p = (isStatic ? static_p : dinamic_p);

    if (!wfname)
        return NULL;

    if (!num_search)
    {
        char *dwp;

        // initialize with the static lookup table
        num_search = sizeof(search0) / sizeof(*search0);
        search = malloc<search_t *>(num_search * sizeof(*search));
        memcpy(search, search0, num_search * sizeof(*search));

        // add each directory from the $DOOMWADPATH environment variable
        if ((dwp = getenv("DOOMWADPATH")))
        {
            char *left, *ptr, *dup_dwp;

            dup_dwp = strdup(dwp);
            left = dup_dwp;

            for (;;)
            {
                ptr = strchr(left, PATH_SEPARATOR);
                if (ptr != NULL)
                {
                    *ptr = '\0';

                    num_search++;
                    search = realloc(search, num_search * sizeof(*search));
                    memset(&search[num_search - 1], 0, sizeof(*search));
                    search[num_search - 1].dir = strdup(left);

                    left = ptr + 1;
                }
                else
                {
                    break;
                }
            }

            num_search++;
            search = realloc(search, num_search * sizeof(*search));
            memset(&search[num_search - 1], 0, sizeof(*search));
            search[num_search - 1].dir = strdup(left);

            free(dup_dwp);
        }
    }

    /* Precalculate a length we will need in the loop */
    pl = strlen(wfname) + (ext ? strlen(ext) : 0) + 4;

    for (i = 0; i < num_search; i++)
    {
        const char *d = NULL;
        const char *s = NULL;
        /* Each entry in the switch sets d to the directory to look in,
         * and optionally s to a subdirectory of d */
        // switch replaced with lookup table
        if (search[i].env)
        {
            if (!(d = getenv(search[i].env)))
                continue;
        }
        else if (search[i].func)
            d = search[i].func();
        else
            d = search[i].dir;
        s = search[i].sub;

        if (!isStatic)
            p = (char *)std::malloc((d ? strlen(d) : 0) + (s ? strlen(s) : 0) +
                                    pl);
        sprintf(p, "%s%s%s%s%s", d ? d : "",
                (d && !HasTrailingSlash(d)) ? "/" : "", s ? s : "",
                (s && !HasTrailingSlash(s)) ? "/" : "", wfname);

        if (ext && access(p, F_OK))
            strcat(p, ext);
        if (!access(p, F_OK))
        {
            if (!isStatic)
                lprintf(LO_INFO, " found %s\n", p);
            return p;
        }
        //    if (!isStatic)
        //      free(p);
    }
    return NULL;
}

char *I_FindFile(const char *wfname, const char *ext)
{
    return I_FindFileInternal(wfname, ext, false);
}

const char *I_FindFile2(const char *wfname, const char *ext)
{
    return (const char *)I_FindFileInternal(wfname, ext, true);
}

#endif

#endif // PRBOOM_SERVER