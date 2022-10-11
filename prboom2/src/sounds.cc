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
 *      Created by a sound utility.
 *      Kept as a sample, DOOM2 sounds.
 *
 *-----------------------------------------------------------------------------*/

// killough 5/3/98: reformatted

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "doomtype.hh"
#include "sounds.hh"

//
// Information about all the music
//

musicinfo_t doom_S_music[] = {
    {nullptr},
    {"e1m1", 0},
    {"e1m2", 0},
    {"e1m3", 0},
    {"e1m4", 0},
    {"e1m5", 0},
    {"e1m6", 0},
    {"e1m7", 0},
    {"e1m8", 0},
    {"e1m9", 0},
    {"e2m1", 0},
    {"e2m2", 0},
    {"e2m3", 0},
    {"e2m4", 0},
    {"e2m5", 0},
    {"e2m6", 0},
    {"e2m7", 0},
    {"e2m8", 0},
    {"e2m9", 0},
    {"e3m1", 0},
    {"e3m2", 0},
    {"e3m3", 0},
    {"e3m4", 0},
    {"e3m5", 0},
    {"e3m6", 0},
    {"e3m7", 0},
    {"e3m8", 0},
    {"e3m9", 0},
    {"inter", 0},
    {"intro", 0},
    {"bunny", 0},
    {"victor", 0},
    {"introa", 0},
    {"runnin", 0},
    {"stalks", 0},
    {"countd", 0},
    {"betwee", 0},
    {"doom", 0},
    {"the_da", 0},
    {"shawn", 0},
    {"ddtblu", 0},
    {"in_cit", 0},
    {"dead", 0},
    {"stlks2", 0},
    {"theda2", 0},
    {"doom2", 0},
    {"ddtbl2", 0},
    {"runni2", 0},
    {"dead2", 0},
    {"stlks3", 0},
    {"romero", 0},
    {"shawn2", 0},
    {"messag", 0},
    {"count2", 0},
    {"ddtbl3", 0},
    {"ampie", 0},
    {"theda3", 0},
    {"adrian", 0},
    {"messg2", 0},
    {"romer2", 0},
    {"tense", 0},
    {"shawn3", 0},
    {"openin", 0},
    {"evil", 0},
    {"ultima", 0},
    {"read_m", 0},
    {"dm2ttl", 0},
    {"dm2int", 0},

    // custom music from MUSINFO lump
    {"musinfo", 0}};

//
// Information about all the sfx
//

sfxinfo_t doom_S_sfx[] = {
    // S_sfx[0] needs to be a dummy for odd reasons.
    {{}, false, 0, nullptr, -1, -1, nullptr},

    // sfx_pistol
    {{"pistol"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_shotgn
    {{"shotgn"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_sgcock
    {{"sgcock"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_dshtgn
    {{"dshtgn"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_dbopn
    {{"dbopn"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_dbcls
    {{"dbcls"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_dbload
    {{"dbload"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_plasma
    {{"plasma"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_bfg
    {{"bfg"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_sawup
    {{"sawup"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_sawidl
    {{"sawidl"}, false, 118, nullptr, -1, -1, nullptr},
    // sfx_sawful
    {{"sawful"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_sawhit
    {{"sawhit"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_rlaunc
    {{"rlaunc"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_bfgball_explode
    {{"rxplod"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_imp_shoot
    {{"firsht"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_imp_fireball_explode
    {{"firxpl"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_pstart
    {{"pstart"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_pstop
    {{"pstop"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_doropn
    {{"doropn"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_dorcls
    {{"dorcls"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_stnmov
    {{"stnmov"}, false, 119, nullptr, -1, -1, nullptr},
    // sfx_swtchn
    {{"swtchn"}, false, 78, nullptr, -1, -1, nullptr},
    // sfx_swtchx
    {{"swtchx"}, false, 78, nullptr, -1, -1, nullptr},
    // sfx_player_pain
    {{"plpain"}, true, 96, nullptr, -1, -1, nullptr},
    // sfx_baron_pain
    {{"dmpain"}, false, 96, nullptr, -1, -1, nullptr},
    // sfx_possessed_pain
    {{"popain"}, true, 96, nullptr, -1, -1, nullptr},
    // sfx_archvile_pain
    {{"vipain"}, false, 96, nullptr, -1, -1, nullptr},
    // sfx_mancubus_pain
    {{"mnpain"}, false, 96, nullptr, -1, -1, nullptr},
    // sfx_painelemental_pain
    {{"pepain"}, true, 96, nullptr, -1, -1, nullptr},
    // sfx_slop
    {{"slop"}, true, 78, nullptr, -1, -1, nullptr},
    // sfx_itemup
    {{"itemup"}, true, 78, nullptr, -1, -1, nullptr},
    // sfx_wpnup
    {{"wpnup"}, true, 78, nullptr, -1, -1, nullptr},
    // sfx_oof
    {{"oof"}, true, 96, nullptr, -1, -1, nullptr},
    // sfx_telept
    {{"telept"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_possessed_wake
    {{"posit1", "posit2", "posit3"}, false, 98, nullptr, -1, -1, nullptr},
    // sfx_posit2
    {{}, false, 98, &doom_S_sfx[sfx_possessed_wake], -1, -1, nullptr},
    // sfx_posit3
    {{}, false, 98, &doom_S_sfx[sfx_possessed_wake], -1, -1, nullptr},
    // sfx_imp_wake
    {{"bgsit1", "bgsit2"}, true, 98, nullptr, -1, -1, nullptr},
    // sfx_bgsit2
    {{}, true, 98, &doom_S_sfx[sfx_imp_wake], -1, -1, nullptr},
    // sfx_pinky_wake
    {{"sgtsit"}, false, 98, nullptr, -1, -1, nullptr},
    // sfx_cacodemon_wake
    {{"cacsit"}, false, 98, nullptr, -1, -1, nullptr},
    // sfx_baron_wake
    {{"brssit"}, false, 94, nullptr, -1, -1, nullptr},
    // sfx_cyberdemon_wake
    {{"cybsit"}, false, 92, nullptr, -1, -1, nullptr},
    // sfx_spidermastermind_wake
    {{"spisit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_arachnotron_wake
    {{"bspsit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_hellknight_wake
    {{"kntsit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_archvile_wake
    {{"vilsit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_mancubus_wake
    {{"mansit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_painelemental_wake
    {{"pesit"}, false, 90, nullptr, -1, -1, nullptr},
    // sfx_lostsoul_attack
    {{"sklatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_pinky_attack
    {{"sgtatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_skepch
    {{"skepch"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_vilatk
    {{"vilatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_claw
    {{"claw"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_skeswg
    {{"skeswg"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_player_death
    {{"pldeth"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_pdiehi
    {{"pdiehi"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_possessed_death
    {{"podth1", "podth2", "podth3"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_podth2
    {{}, false, 70, &doom_S_sfx[sfx_possessed_death], -1, -1, nullptr},
    // sfx_podth3
    {{}, false, 70, &doom_S_sfx[sfx_possessed_death], -1, -1, nullptr},
    // sfx_imp_death
    {{"bgdth1", "bgdth2"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_bgdth2
    {{}, false, 70, &doom_S_sfx[sfx_imp_death], -1, -1, nullptr},
    // sfx_pinky_death
    {{"sgtdth"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_cacodemon_death
    {{"cacdth"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_lostsoul_death
    {{"firxpl"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_baron_death
    {{"brsdth"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_cyberdemon_death
    {{"cybdth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_spidermastermind_death
    {{"spidth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_arachnotron_death
    {{"bspdth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_archvile_death
    {{"vildth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_hellknight_death
    {{"kntdth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_painelemental_death
    {{"pedth"}, true, 32, nullptr, -1, -1, nullptr},
    // sfx_revenant_death
    {{"skedth"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_possessed_active
    {{"posact"}, false, 120, nullptr, -1, -1, nullptr},
    // sfx_imp_active
    {{"bgact"}, false, 120, nullptr, -1, -1, nullptr},
    // sfx_baron_active
    {{"dmact"}, false, 120, nullptr, -1, -1, nullptr},
    // sfx_arachnotron_active
    {{"bspact"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_arachnotron_walk
    {{"bspwlk"}, false, 100, nullptr, 150, 0, nullptr},
    // sfx_archvile_active
    {{"vilact"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_noway
    {{"noway"}, false, 78, nullptr, -1, -1, nullptr},
    // sfx_barexp
    {{"barexp"}, false, 60, nullptr, -1, -1, nullptr},
    // sfx_punch
    {{"punch"}, false, 64, nullptr, -1, -1, nullptr},
    // sfx_hoof
    {{"hoof"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_metal
    {{"metal"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_tink
    {{"tink"}, false, 60, nullptr, -1, -1, nullptr},
    // sfx_bdopn
    {{"bdopn"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_bdcls
    {{"bdcls"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_itmbk
    {{"itmbk"}, false, 100, nullptr, -1, -1, nullptr},
    // sfx_flame
    {{"flame"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_flamst
    {{"flamst"}, false, 32, nullptr, -1, -1, nullptr},
    // sfx_getpow
    {{"getpow"}, false, 60, nullptr, -1, -1, nullptr},
    // sfx_icon_spit
    {{"bospit"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_boscub
    {{"boscub"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_bossit
    {{"bossit"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_icon_pain
    {{"bospn"}, true, 70, nullptr, -1, -1, nullptr},
    // sfx_icon_death
    {{"bosdth"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_manatk
    {{"manatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_mancubus_death
    {{"mandth"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_ss_wake
    {{"sssit"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_ss_death
    {{"podth1", "podth2", "podth3"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_commanderkeen_pain
    {{"keenpn"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_commanderkeen_death
    {{"keendt"}, false, 70, nullptr, -1, -1, nullptr},

    // sfx_revenant_active
    {{"skeact"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_revenant_wake
    {{"skesit"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_revenant_attack
    {{"skeatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_radio
    {{"radio"}, false, 60, nullptr, -1, -1, nullptr},
    // sfx_dgsit
    {{"dgsit"}, false, 98, nullptr, -1, -1, nullptr},

    // e6y
    // sfx_dgatk
    {{"dgatk"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_dgact
    {{"dgact"}, false, 120, nullptr, -1, -1, nullptr},
    // everything from here up to 500 is reserved for future use.

    // per-monster/weapon sounds that aren't part of original doom
    // sfx_dgdth
    {{"dgdth"}, false, 70, nullptr, -1, -1, nullptr},
    // sfx_dgpain
    {{"dgpain"}, false, 96, nullptr, -1, -1, nullptr},
    // sfx_secret
    {{"secret"}, false, 60, nullptr, -1, -1, nullptr},
    // sfx_gibdth
    {{"gibdth"}, false, 60, nullptr, -1, -1, nullptr},
    // free slots for dehextra. priorities should be overridden by user.
    // there is a gap present to accomodate eternity engine - see their commit
    // @ https://github.com/team-eternity/eternity/commit/b8fb8f71 - which means
    // i must use desginated initializers, or else supply an exact number of
    // dummy
    // entries to pad it out. not sure which would be uglier to maintain. -sh
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{}, false, 0, nullptr, -1, -1, nullptr},
    {{"fre000"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre001"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre002"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre003"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre004"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre005"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre006"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre007"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre008"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre009"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre010"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre011"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre012"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre013"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre014"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre015"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre016"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre017"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre018"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre019"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre020"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre021"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre022"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre023"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre024"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre025"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre026"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre027"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre028"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre029"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre030"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre031"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre032"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre033"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre034"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre035"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre036"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre037"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre038"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre039"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre040"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre041"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre042"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre043"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre044"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre045"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre046"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre047"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre048"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre049"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre050"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre051"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre052"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre053"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre054"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre055"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre056"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre057"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre058"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre059"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre060"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre061"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre062"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre063"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre064"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre065"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre066"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre067"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre068"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre069"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre070"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre071"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre072"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre073"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre074"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre075"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre076"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre077"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre078"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre079"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre080"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre081"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre082"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre083"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre084"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre085"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre086"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre087"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre088"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre089"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre090"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre091"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre092"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre093"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre094"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre095"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre096"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre097"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre098"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre099"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre100"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre101"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre102"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre103"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre104"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre105"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre106"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre107"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre108"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre109"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre110"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre111"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre112"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre113"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre114"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre115"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre116"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre117"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre118"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre119"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre120"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre121"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre122"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre123"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre124"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre125"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre126"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre127"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre128"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre129"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre130"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre131"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre132"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre133"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre134"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre135"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre136"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre137"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre138"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre139"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre140"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre141"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre142"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre143"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre144"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre145"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre146"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre147"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre148"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre149"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre150"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre151"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre152"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre153"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre154"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre155"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre156"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre157"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre158"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre159"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre160"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre161"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre162"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre163"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre164"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre165"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre166"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre167"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre168"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre169"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre170"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre171"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre172"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre173"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre174"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre175"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre176"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre177"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre178"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre179"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre180"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre181"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre182"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre183"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre184"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre185"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre186"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre187"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre188"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre189"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre190"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre191"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre192"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre193"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre194"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre195"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre196"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre197"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre198"}, false, 127, nullptr, -1, -1, nullptr},
    {{"fre199"}, false, 127, nullptr, -1, -1, nullptr},

    // sfx_player_chaingun
    {{}, false, 64, &doom_S_sfx[sfx_pistol], -1, -1, nullptr},
    // sfx_chaingunner_shoot
    {{}, false, 64, &doom_S_sfx[sfx_shotgn], -1, -1, nullptr},
    // sfx_cacodemon_pain
    {{}, false, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_chaingunner_pain
    {{}, false, 96, &doom_S_sfx[sfx_possessed_pain], -1, -1, nullptr},
    // sfx_cyberdemon_pain
    {{}, false, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_hellknight_pain
    {{}, false, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_imp_pain
    {{}, true, 96, &doom_S_sfx[sfx_possessed_pain], -1, -1, nullptr},
    // sfx_lostsoul_pain
    {{}, false, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_pinky_pain
    {{}, true, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_revenant_pain
    {{}, true, 96, &doom_S_sfx[sfx_possessed_pain], -1, -1, nullptr},
    // sfx_shotgunner_pain
    {{}, true, 96, &doom_S_sfx[sfx_possessed_pain], -1, -1, nullptr},
    // sfx_spectre_pain
    {{}, true, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_spidermastermind_pain
    {{}, true, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_ss_pain
    {{}, true, 96, &doom_S_sfx[sfx_possessed_pain], -1, -1, nullptr},
    // sfx_plasma_sizzle
    {{}, true, 70, &doom_S_sfx[sfx_imp_fireball_explode], -1, -1, nullptr},
    // sfx_tracer_explode
    {{}, true, 60, &doom_S_sfx[sfx_barexp], -1, -1, nullptr},
    // sfx_pinky_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_baron_shoot
    {{}, false, 70, &doom_S_sfx[sfx_imp_shoot], -1, -1, nullptr},
    // sfx_baron_attack
    {{}, false, 70, &doom_S_sfx[sfx_claw], -1, -1, nullptr},
    // sfx_baron_shot_sizzle
    {{}, true, 70, &doom_S_sfx[sfx_imp_fireball_explode], -1, -1, nullptr},
    // sfx_cacodemon_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_cacodemon_shoot
    {{}, false, 70, &doom_S_sfx[sfx_imp_shoot], -1, -1, nullptr},
    // sfx_lostsoul_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_spidermastermind_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_spidermastermind_shoot
    {{}, false, 64, &doom_S_sfx[sfx_shotgn], -1, -1, nullptr},
    // sfx_arachnotron_pain
    {{}, false, 96, &doom_S_sfx[sfx_baron_pain], -1, -1, nullptr},
    // sfx_arachnotron_shoot
    {{}, false, 64, &doom_S_sfx[sfx_plasma], -1, -1, nullptr},
    // sfx_arachnotron_plasma_sizzle
    {{}, false, 70, &doom_S_sfx[sfx_imp_fireball_explode], -1, -1, nullptr},
    // sfx_cyberdemon_active
    {{}, true, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_painelemental_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_ss_active
    {{}, false, 120, &doom_S_sfx[sfx_possessed_active], -1, -1, nullptr},
    // sfx_ss_shoot
    {{}, false, 64, &doom_S_sfx[sfx_shotgn], -1, -1, nullptr},
    // sfx_chaingunner_wake
    {{}, false, 98, &doom_S_sfx[sfx_possessed_wake], -1, -1, nullptr},
    // sfx_chaingunner_active
    {{}, false, 120, &doom_S_sfx[sfx_possessed_active], -1, -1, nullptr},
    // sfx_chaingunner_death
    {{}, false, 70, &doom_S_sfx[sfx_possessed_death], -1, -1, nullptr},
    // sfx_hellknight_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_hellknight_shoot
    {{}, false, 70, &doom_S_sfx[sfx_imp_shoot], -1, -1, nullptr},
    // sfx_hellknight_shot_sizzle
    {{}, false, 70, &doom_S_sfx[sfx_imp_fireball_explode], -1, -1, nullptr},
    // sfx_hellknight_attack
    {{}, false, 70, &doom_S_sfx[sfx_claw], -1, -1, nullptr},
    // sfx_mancubus_active
    {{}, false, 120, &doom_S_sfx[sfx_possessed_active], -1, -1, nullptr},
    // sfx_mancubus_shoot
    {{}, false, 70, &doom_S_sfx[sfx_imp_shoot], -1, -1, nullptr},
    // sfx_mancubus_projectile_explode
    {{}, false, 70, &doom_S_sfx[sfx_imp_fireball_explode], -1, -1, nullptr},
    // sfx_archvile_resurrect
    {{}, false, 78, &doom_S_sfx[sfx_slop], -1, -1, nullptr},
    // sfx_archvile_zap
    {{}, false, 60, &doom_S_sfx[sfx_barexp], -1, -1, nullptr},
    // sfx_shotgunner_wake
    {{}, false, 98, &doom_S_sfx[sfx_possessed_wake], -1, -1, nullptr},
    // sfx_shotgunner_death
    {{}, false, 70, &doom_S_sfx[sfx_possessed_death], -1, -1, nullptr},
    // sfx_shotgunner_active
    {{}, true, 120, &doom_S_sfx[sfx_possessed_active], -1, -1, nullptr},
    // sfx_possessed_shoot
    {{}, false, 64, &doom_S_sfx[sfx_pistol], -1, -1, nullptr},
    // sfx_spectre_wake
    {{}, false, 98, &doom_S_sfx[sfx_pinky_wake], -1, -1, nullptr},
    // sfx_spectre_attack
    {{}, false, 70, &doom_S_sfx[sfx_pinky_attack], -1, -1, nullptr},
    // sfx_spectre_death
    {{}, false, 70, &doom_S_sfx[sfx_pinky_death], -1, -1, nullptr},
    // sfx_spectre_active
    {{}, false, 120, &doom_S_sfx[sfx_baron_active], -1, -1, nullptr},
    // sfx_rocket_explode
    {{}, false, 60, &doom_S_sfx[sfx_barexp], -1, -1, nullptr},

};
