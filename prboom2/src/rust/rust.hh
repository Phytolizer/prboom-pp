#pragma once

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>
#include "sounds.hh"

namespace rust {

struct SoundInfo {
  sfxenum_t sfx;
  const uint8_t *const *lumps;
  const uintptr_t *lump_lens;
  uintptr_t num_lumps;
  bool singularity;
  int pitch;
  int volume;
};

extern "C" {

/// # Safety
/// This function cleans up after the C++ side is finished with the data
/// that was passed py pointer from parse_sndinfo.
void deallocate_rust_sound_info(SoundInfo *ptr, unsigned long len);

/// # Safety
/// This function uses a ptr/length pair to construct a slice.
/// It is a safe conversion as long as W_LumpLength and W_CacheLumpNum return accurate values.
void parse_sndinfo(bool heretic,
                   bool strict,
                   const char *lump,
                   int lump_length,
                   SoundInfo **buf,
                   unsigned long *buf_len);

} // extern "C"

} // namespace rust
