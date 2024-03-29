#pragma once

/* Warning, this file is autogenerated by cbindgen. Don't modify this manually.
 */

#include "doomdef.hh"
#include "info.hh"
#include "sounds.hh"
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <ostream>

namespace rust
{

struct EnemyStats
{
    mobjtype_t enemy;
    unsigned long kills;

    EnemyStats(mobjtype_t const &enemy, unsigned long const &kills)
        : enemy(enemy), kills(kills)
    {
    }

    bool operator==(const EnemyStats &other) const
    {
        return enemy == other.enemy && kills == other.kills;
    }
    bool operator!=(const EnemyStats &other) const
    {
        return enemy != other.enemy || kills != other.kills;
    }
};

struct RawWeaponStats
{
    unsigned long kills;
    EnemyStats *enemies;
    unsigned long num_enemies;
    unsigned long enemies_capacity;

    RawWeaponStats(
        unsigned long const &kills, EnemyStats *const &enemies,
        unsigned long const &num_enemies, unsigned long const &enemies_capacity
    )
        : kills(kills), enemies(enemies), num_enemies(num_enemies),
          enemies_capacity(enemies_capacity)
    {
    }

    bool operator==(const RawWeaponStats &other) const
    {
        return kills == other.kills && enemies == other.enemies &&
               num_enemies == other.num_enemies &&
               enemies_capacity == other.enemies_capacity;
    }
    bool operator!=(const RawWeaponStats &other) const
    {
        return kills != other.kills || enemies != other.enemies ||
               num_enemies != other.num_enemies ||
               enemies_capacity != other.enemies_capacity;
    }
};

struct SoundInfo
{
    sfxenum_t sfx;
    const uint8_t *const *lumps;
    const size_t *lump_lens;
    size_t num_lumps;
    bool singularity;
    int pitch;
    int volume;

    SoundInfo(
        sfxenum_t const &sfx, const uint8_t *const *const &lumps,
        const size_t *const &lump_lens, size_t const &num_lumps,
        bool const &singularity, int const &pitch, int const &volume
    )
        : sfx(sfx), lumps(lumps), lump_lens(lump_lens), num_lumps(num_lumps),
          singularity(singularity), pitch(pitch), volume(volume)
    {
    }

    bool operator==(const SoundInfo &other) const
    {
        return sfx == other.sfx && lumps == other.lumps &&
               lump_lens == other.lump_lens && num_lumps == other.num_lumps &&
               singularity == other.singularity && pitch == other.pitch &&
               volume == other.volume;
    }
    bool operator!=(const SoundInfo &other) const
    {
        return sfx != other.sfx || lumps != other.lumps ||
               lump_lens != other.lump_lens || num_lumps != other.num_lumps ||
               singularity != other.singularity || pitch != other.pitch ||
               volume != other.volume;
    }
};

extern "C"
{

    void add_kill(weapontype_t weapon, mobjtype_t enemy);

    /// # Safety
    /// This function can only take Rust-allocated stats.
    /// It deallocates them using drop, so be very careful on the C/C++ end.
    void cleanup_stats(RawWeaponStats *stats);

    /// # Safety
    /// This function cleans up after the C++ side is finished with the data
    /// that was passed py pointer from parse_sndinfo.
    void deallocate_rust_sound_info(SoundInfo *ptr, unsigned long len);

    /// # Safety
    /// This function allocates a RawWeaponStats and passes it by pointer.
    /// It is safe as long as the C/C++ side remembers to call cleanup_stats.
    int get_stats(weapontype_t weapon, RawWeaponStats *raw_stats);

    /// # Safety
    /// This function's safety relies on that of M_LookupDefault.
    /// Otherwise, it is safe.
    int load_defaults();

    int load_weapon_stats();

    /// # Safety
    /// This function uses a ptr/length pair to construct a slice.
    /// It is a safe conversion as long as W_LumpLength and W_CacheLumpNum
    /// return accurate values.
    void parse_sndinfo(
        bool heretic, bool strict, const char *lump, int lump_length,
        SoundInfo **buf, unsigned long *buf_len
    );

    /// # Safety
    /// This function reads lots of raw C structs.
    void save_defaults();

    int save_weapon_stats();

    const char *weapon_name(weapontype_t weapon);

} // extern "C"

} // namespace rust
