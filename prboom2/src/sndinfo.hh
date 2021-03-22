#pragma once

#include <vector>
#include "rust/rust.hh"

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
