// Copyright (c) 1993-2011 PrBoom developers (see AUTHORS)
// Licence: GPLv2 or later (see COPYING)

#pragma once

#include <cstddef>

// Convert WAVE files to Doom sound format

// convert wav file to doom sound format
std::size_t wav_to_doom(void **lumpdata, const char *filename);
