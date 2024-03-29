//-----------------------------------------------------------------------------
//
// Copyright 2017 Christoph Oelckers
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/
//
//-----------------------------------------------------------------------------

#include "umapinfo.hh"
#include "scanner.hh"
#include <cassert>
#include <cctype>
#include <cpp/strings.hh>
#include <cstdlib>
#include <cstring>

#include "doomdef.hh"
#include "doomstat.hh"
#include "g_game.hh"
#include "m_misc.hh"

void M_AddEpisode(const std::string &map, std::string *def);

MapList Maps;

//==========================================================================
//
// The Doom actors in their original order
// Names are the same as in ZDoom.
//
//==========================================================================

static const char *const ActorNames[] = {
    "DoomPlayer", "ZombieMan", "ShotgunGuy", "Archvile", "ArchvileFire",
    "Revenant", "RevenantTracer", "RevenantTracerSmoke", "Fatso", "FatShot",
    "ChaingunGuy", "DoomImp", "Demon", "Spectre", "Cacodemon", "BaronOfHell",
    "BaronBall", "HellKnight", "LostSoul", "SpiderMastermind", "Arachnotron",
    "Cyberdemon", "PainElemental", "WolfensteinSS", "CommanderKeen",
    "BossBrain", "BossEye", "BossTarget", "SpawnShot", "SpawnFire",
    "ExplosiveBarrel", "DoomImpBall", "CacodemonBall", "Rocket", "PlasmaBall",
    "BFGBall", "ArachnotronPlasma", "BulletPuff", "Blood", "TeleportFog",
    "ItemFog", "TeleportDest", "BFGExtra", "GreenArmor", "BlueArmor",
    "HealthBonus", "ArmorBonus", "BlueCard", "RedCard", "YellowCard",
    "YellowSkull", "RedSkull", "BlueSkull", "Stimpack", "Medikit", "Soulsphere",
    "InvulnerabilitySphere", "Berserk", "BlurSphere", "RadSuit", "Allmap",
    "Infrared", "Megasphere", "Clip", "ClipBox", "RocketAmmo", "RocketBox",
    "Cell", "CellPack", "Shell", "ShellBox", "Backpack", "BFG9000", "Chaingun",
    "Chainsaw", "RocketLauncher", "PlasmaRifle", "Shotgun", "SuperShotgun",
    "TechLamp", "TechLamp2", "Column", "TallGreenColumn", "ShortGreenColumn",
    "TallRedColumn", "ShortRedColumn", "SkullColumn", "HeartColumn", "EvilEye",
    "FloatingSkull", "TorchTree", "BlueTorch", "GreenTorch", "RedTorch",
    "ShortBlueTorch", "ShortGreenTorch", "ShortRedTorch", "Stalagtite",
    "TechPillar", "CandleStick", "Candelabra", "BloodyTwitch", "Meat2", "Meat3",
    "Meat4", "Meat5", "NonsolidMeat2", "NonsolidMeat4", "NonsolidMeat3",
    "NonsolidMeat5", "NonsolidTwitch", "DeadCacodemon", "DeadMarine",
    "DeadZombieMan", "DeadDemon", "DeadLostSoul", "DeadDoomImp",
    "DeadShotgunGuy", "GibbedMarine", "GibbedMarineExtra", "HeadsOnAStick",
    "Gibs", "HeadOnAStick", "HeadCandles", "DeadStick", "LiveStick", "BigTree",
    "BurningBarrel", "HangNoGuts", "HangBNoBrain", "HangTLookingDown",
    "HangTSkull", "HangTLookingUp", "HangTNoBrain", "ColonGibs",
    "SmallBloodPool", "BrainStem",
    // Boom/MBF additions
    "PointPusher", "PointPuller", "MBFHelperDog", "PlasmaBall1", "PlasmaBall2",
    "EvilSceptre", "UnholyBible", nullptr};

// -----------------------------------------------
//
//
// -----------------------------------------------

static void FreeMap(MapEntry *mape)
{
    if (mape->properties)
    {
        free(mape->properties);
    }
    if (mape->bossactions)
    {
        free(mape->bossactions);
    }
    mape->propertycount = 0;
    mape->properties = nullptr;
}

void FreeMapList()
{
    unsigned i;

    for (i = 0; i < Maps.mapcount; i++)
    {
        FreeMap(&Maps.maps[i]);
    }
    free(Maps.maps);
    Maps.maps = nullptr;
    Maps.mapcount = 0;
}

void ReplaceString(std::string *pptr, const char *newstring)
{
    *pptr = newstring;
}

// -----------------------------------------------
//
// Parses a set of string and concatenates them
//
// -----------------------------------------------

static std::string ParseMultiString(Scanner &scanner, int /* error */)
{
    std::string build;

    if (scanner.CheckToken(Token::Identifier))
    {
        if (!stricmp(scanner.string, "clear"))
        {
            return strdup("-"
            ); // this was explicitly deleted to override the default.
        }

        scanner.ErrorF("Either 'clear' or string constant expected");
    }

    do
    {
        scanner.MustGetToken(Token::StringConst);
        if (build.empty())
        {
            build = scanner.string;
        }
        else
        {
            size_t newlen = build.length() + strlen(scanner.string) +
                            2; // strlen for both the existing text and the new
                               // line, plus room for one \n and one \0
            build += "\n";
            build += scanner.string;
        }
    } while (scanner.CheckToken(Token::Type{','}));
    return build;
}

// -----------------------------------------------
//
// Parses a lump name. The buffer must be at least 9 characters.
//
// -----------------------------------------------

static int ParseLumpName(Scanner &scanner, char *buffer)
{
    scanner.MustGetToken(Token::StringConst);
    if (strlen(scanner.string) > 8)
    {
        scanner.ErrorF("String too long. Maximum size is 8 characters.");
        return 0;
    }
    strncpy(buffer, scanner.string, 8);
    buffer[8] = 0;
    M_Strupr(buffer);
    return 1;
}

// -----------------------------------------------
//
// Parses a standard property that is already known
// These do not get stored in the property list
// but in dedicated struct member variables.
//
// -----------------------------------------------

static int ParseStandardProperty(Scanner &scanner, MapEntry *mape)
{
    // find the next line with content.
    // this line is no property.

    scanner.MustGetToken(Token::Identifier);
    char *pname = strdup(scanner.string);
    scanner.MustGetToken(Token::Type{'='});

    if (!stricmp(pname, "levelname"))
    {
        scanner.MustGetToken(Token::StringConst);
        mape->levelname = scanner.string;
    }
    else if (!stricmp(pname, "next"))
    {
        ParseLumpName(scanner, mape->nextmap);
        if (!G_ValidateMapName(mape->nextmap, nullptr, nullptr))
        {
            scanner.ErrorF("Invalid map name %s.", mape->nextmap);
            return 0;
        }
    }
    else if (!stricmp(pname, "nextsecret"))
    {
        ParseLumpName(scanner, mape->nextsecret);
        if (!G_ValidateMapName(mape->nextsecret, nullptr, nullptr))
        {
            scanner.ErrorF("Invalid map name %s", mape->nextmap);
            return 0;
        }
    }
    else if (!stricmp(pname, "levelpic"))
    {
        ParseLumpName(scanner, mape->levelpic);
    }
    else if (!stricmp(pname, "skytexture"))
    {
        ParseLumpName(scanner, mape->skytexture);
    }
    else if (!stricmp(pname, "music"))
    {
        ParseLumpName(scanner, mape->music);
    }
    else if (!stricmp(pname, "endpic"))
    {
        ParseLumpName(scanner, mape->endpic);
    }
    else if (!stricmp(pname, "endcast"))
    {
        scanner.MustGetToken(Token::BoolConst);
        if (scanner.boolean)
        {
            strcpy(mape->endpic, "$CAST");
        }
        else
        {
            strcpy(mape->endpic, "-");
        }
    }
    else if (!stricmp(pname, "endbunny"))
    {
        scanner.MustGetToken(Token::BoolConst);
        if (scanner.boolean)
        {
            strcpy(mape->endpic, "$BUNNY");
        }
        else
        {
            strcpy(mape->endpic, "-");
        }
    }
    else if (!stricmp(pname, "endgame"))
    {
        scanner.MustGetToken(Token::BoolConst);
        if (scanner.boolean)
        {
            strcpy(mape->endpic, "!");
        }
        else
        {
            strcpy(mape->endpic, "-");
        }
    }
    else if (!stricmp(pname, "exitpic"))
    {
        ParseLumpName(scanner, mape->exitpic);
    }
    else if (!stricmp(pname, "enterpic"))
    {
        ParseLumpName(scanner, mape->enterpic);
    }
    else if (!stricmp(pname, "nointermission"))
    {
        scanner.MustGetToken(Token::BoolConst);
        mape->nointermission = scanner.boolean;
    }
    else if (!stricmp(pname, "partime"))
    {
        scanner.MustGetInteger();
        mape->partime = TICRATE * scanner.number;
    }
    else if (!stricmp(pname, "intertext"))
    {
        std::string lname = ParseMultiString(scanner, 1);
        if (lname.empty())
        {
            return 0;
        }
        mape->intertext = lname;
    }
    else if (!stricmp(pname, "intertextsecret"))
    {
        std::string lname = ParseMultiString(scanner, 1);
        if (lname.empty())
        {
            return 0;
        }
        mape->intertextsecret = lname;
    }
    else if (!stricmp(pname, "interbackdrop"))
    {
        ParseLumpName(scanner, mape->interbackdrop);
    }
    else if (!stricmp(pname, "intermusic"))
    {
        ParseLumpName(scanner, mape->intermusic);
    }
    else if (!stricmp(pname, "episode"))
    {
        std::string lname = ParseMultiString(scanner, 1);
        if (lname.empty())
        {
            return 0;
        }
        M_AddEpisode(mape->mapname, &lname);
    }
    else if (!stricmp(pname, "bossaction"))
    {
        scanner.MustGetToken(Token::Identifier);
        int classnum, special, tag;
        if (!stricmp(scanner.string, "clear"))
        {
            // mark level free of boss actions
            classnum = special = tag = -1;
            if (mape->bossactions)
            {
                free(mape->bossactions);
            }
            mape->bossactions = nullptr;
            mape->numbossactions = -1;
        }
        else
        {
            int i;
            for (i = 0; ActorNames[i]; i++)
            {
                if (!stricmp(scanner.string, ActorNames[i]))
                {
                    break;
                }
            }
            if (ActorNames[i] == nullptr)
            {
                scanner.ErrorF("Unknown thing type %s", scanner.string);
                return 0;
            }

            scanner.MustGetToken(Token::Type{','});
            scanner.MustGetInteger();
            special = scanner.number;
            scanner.MustGetToken(Token::Type{','});
            scanner.MustGetInteger();
            tag = scanner.number;
            // allow no 0-tag specials here, unless a level exit.
            if (tag != 0 || special == 11 || special == 51 || special == 52 ||
                special == 124)
            {
                if (mape->numbossactions == -1)
                {
                    mape->numbossactions = 1;
                }
                else
                {
                    mape->numbossactions++;
                }
                mape->bossactions = (struct BossAction *)realloc(
                    mape->bossactions,
                    sizeof(struct BossAction) * mape->numbossactions
                );
                mape->bossactions[mape->numbossactions - 1].type = i;
                mape->bossactions[mape->numbossactions - 1].special = special;
                mape->bossactions[mape->numbossactions - 1].tag = tag;
            }
        }
    }
    else
    {
        do
        {
            if (!scanner.CheckFloat())
            {
                scanner.GetNextToken();
            }
            if (scanner.token > Token::BoolConst)
            {
                scanner.Error(Token::Identifier);
            }

        } while (scanner.CheckToken(Token::Type{','}));
    }
    free(pname);
    return 1;
}

// -----------------------------------------------
//
// Parses a complete map entry
//
// -----------------------------------------------

static int ParseMapEntry(Scanner &scanner, MapEntry *val)
{
    val->mapname.clear();
    val->propertycount = 0;
    val->properties = nullptr;

    scanner.MustGetIdentifier("map");
    scanner.MustGetToken(Token::Identifier);
    if (!G_ValidateMapName(scanner.string, nullptr, nullptr))
    {
        scanner.ErrorF("Invalid map name %s", scanner.string);
        return 0;
    }

    val->mapname = scanner.string;
    scanner.MustGetToken(Token::Type{'{'});
    while (!scanner.CheckToken(Token::Type{'}'}))
    {
        ParseStandardProperty(scanner, val);
    }
    return 1;
}

// -----------------------------------------------
//
// Parses a complete UMAPINFO lump
//
// -----------------------------------------------

int ParseUMapInfo(
    const unsigned char *buffer, size_t length, umapinfo_errorfunc err
)
{
    Scanner scanner((const char *)buffer, length);
    unsigned int i;

    scanner.SetErrorCallback(err);

    while (scanner.TokensLeft())
    {
        MapEntry parsed = {nullptr};
        ParseMapEntry(scanner, &parsed);

        // Set default level progression here to simplify the checks elsewhere.
        // Doing this lets us skip all normal code for this if nothing has been
        // defined.
        if (parsed.endpic[0] && (strcmp(parsed.endpic, "-") != 0))
        {
            parsed.nextmap[0] = parsed.nextsecret[0] = 0;
            if (parsed.endpic[0] == '!')
            {
                parsed.endpic[0] = 0;
            }
        }
        else if (!parsed.nextmap[0] && !parsed.endpic[0])
        {
            if (!str::caseInsensitiveCompare(parsed.mapname, "MAP30"))
            {
                strcpy(parsed.endpic, "$CAST");
            }
            else if (!str::caseInsensitiveCompare(parsed.mapname, "E1M8"))
            {
                strcpy(parsed.endpic, gamemode == retail ? "CREDIT" : "HELP2");
            }
            else if (!str::caseInsensitiveCompare(parsed.mapname, "E2M8"))
            {
                strcpy(parsed.endpic, "VICTORY");
            }
            else if (!str::caseInsensitiveCompare(parsed.mapname, "E3M8"))
            {
                strcpy(parsed.endpic, "$BUNNY");
            }
            else if (!str::caseInsensitiveCompare(parsed.mapname, "E4M8"))
            {
                strcpy(parsed.endpic, "ENDPIC");
            }
            else if (gamemission == chex && !str::caseInsensitiveCompare(parsed.mapname, "E1M5"))
            {
                strcpy(parsed.endpic, "CREDIT");
            }
            else
            {
                int ep, map;
                G_ValidateMapName(parsed.mapname, &ep, &map);
                map++;
                if (gamemode == commercial)
                {
                    sprintf(parsed.nextmap, "MAP%02d", map);
                }
                else
                {
                    sprintf(parsed.nextmap, "E%dM%d", ep, map);
                }
            }
        }

        // Does this property already exist? If yes, replace it.
        for (i = 0; i < Maps.mapcount; i++)
        {
            if (parsed.mapname == Maps.maps[i].mapname)
            {
                FreeMap(&Maps.maps[i]);
                Maps.maps[i] = parsed;
                break;
            }
        }
        // Not found so create a new one.
        if (i == Maps.mapcount)
        {
            Maps.mapcount++;
            Maps.maps = (MapEntry *)realloc(
                Maps.maps, sizeof(MapEntry) * Maps.mapcount
            );
            Maps.maps[Maps.mapcount - 1] = parsed;
        }
    }
    return 1;
}

MapProperty *FindProperty(MapEntry *map, const char *name)
{
    return nullptr;
}
