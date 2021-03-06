// Copyright (c) 1993-2011 PrBoom developers (see AUTHORS)
// Licence: GPLv2 or later (see COPYING)

#pragma once

#include <cstddef>

// Output wad construction - add lump data, build wad directory

// append lump to output wad
void output_add(const char *filename, const void *data, std::size_t size);

// write output file to filename
void output_write(const char *filename);
