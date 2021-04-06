#pragma once

#include "misc/rust.hh"
#include <vector>

namespace sndinfo
{

struct SoundInfo {
    std::vector<std::string> lumps;
    bool singularity;
    int pitch;
    int volume;
};

extern std::vector<rust::SoundInfo> G_INFO;

void parse(int lumpnum);

} // namespace sndinfo
