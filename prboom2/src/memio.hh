// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//

// e6y
// All tabs are replaced with spaces.
// Fixed eol style of files.

#ifndef MEMIO_H
#define MEMIO_H

#include <cstddef>

typedef struct _MEMFILE MEMFILE;

typedef enum
{
    MEM_SEEK_SET,
    MEM_SEEK_CUR,
    MEM_SEEK_END,
} mem_rel_t;

MEMFILE *mem_fopen_read(const void *buf, std::size_t buflen);
std::size_t mem_fread(
    void *buf, std::size_t size, std::size_t nmemb, MEMFILE *stream
);
MEMFILE *mem_fopen_write(void);
std::size_t mem_fwrite(
    const void *ptr, std::size_t size, std::size_t nmemb, MEMFILE *stream
);
void mem_get_buf(MEMFILE *stream, void **buf, std::size_t *buflen);
void mem_fclose(MEMFILE *stream);
long mem_ftell(MEMFILE *stream);
int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);

#endif /* #ifndef MEMIO_H */
