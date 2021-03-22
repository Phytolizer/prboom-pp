#include "sndinfo.hh"
#include "rust/rust.hh"
#include "doomstat.hh"
#include "sounds.hh"
#include "w_wad.hh"
#include <iostream>
#include <map>

void sndinfo::parse(int lumpnum)
{
    const auto *rawData = static_cast<const char *>(W_CacheLumpNum(lumpnum));
    std::string lump = {rawData, rawData + W_LumpLength(lumpnum)};
    rust::SoundInfo *buf = nullptr;
    size_t bufLen = 0;
    rust::parse_sndinfo(heretic, lump.c_str(), lump.length(), &buf, &bufLen);
    std::map<sfxenum_t, SoundInfo> lumps;

    for (int i = 0; i < bufLen; i++)
    {
        rust::SoundInfo &si = buf[i];
        for (int j = 0; j < si.num_lumps; ++j)
        {
            auto [_, inserted] = lumps.try_emplace(
                si.sfx,
                SoundInfo{std::vector{std::string{
                              si.lumps[j], si.lumps[j] + si.lump_lens[j]}},
                          si.singularity, si.pitch, si.volume});
            if (!inserted)
            {
                lumps[si.sfx].lumps.emplace_back(si.lumps[j],
                                                 si.lumps[j] + si.lump_lens[j]);
            }
        }
    }

    for (const auto &[sfx, si] : lumps)
    {
        S_sfx[sfx].altNames = si.lumps;
        S_sfx[sfx].singularity = si.singularity;
        S_sfx[sfx].pitch = si.pitch;
        S_sfx[sfx].volume = si.volume;
        S_sfx[sfx].lumpnums = {-1};

        std::cout << "SFX #" << sfx
                  << " is now associated with the following lumps:\n";
        for (const auto &lmp : si.lumps) {
            std::cout << "\t" << lmp << "\n";
        }
    }

    rust::deallocate_rust_sound_info(buf, bufLen);
}
