// Copyright (c) 1993-2011 PrBoom developers (see AUTHORS)
// Licence: GPLv2 or later (see COPYING)

// Convert portable pixmap to Doom patch format

#include "config.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "rd_graphic.hh"
#include "rd_palette.hh"
#include "rd_util.hh"

//
// parseppm
//
// try to read a ppm file header and get width/height of image
//

static unsigned char *parseppm(
    char *ppm, size_t size, const char *file, int *width, int *height
)
{
    int maxcol, numpixels;
    char *pos = ppm;

    if (size < 2 || !(*pos++ == 'P' && *pos++ == '6'))
    {
        die("Not a PPM: %s\n", file);
    }

    // Ignore comments like "# Created by GIMP ..." in line 2
    if (*pos++ == '\n' && *pos == '#')
    {
        while (*pos != '\n')
        {
            pos++;
        }
    }

    numpixels = *width = static_cast<int>(strtol(pos, &pos, 0));
    numpixels *= *height = static_cast<int>(strtol(pos, &pos, 0));
    maxcol = static_cast<int>(strtol(pos, &pos, 0));

    if (maxcol != 255 || !isspace(*pos++))
    {
        die("Invalid PPM header: %s\n", file);
    }

    if (!numpixels || static_cast<unsigned long>(numpixels) >
                          (size - static_cast<unsigned long>(ppm - pos)) / 3)
    {
        die("Invalid PPM size: %s\n", file);
    }

    return (unsigned char *)pos;
}

//
// column_pixels_to_colours
//
// make an array of colour indices from a column of raw pixel data
// (random access to which is easier while building a patch column)
//

static void pixels_to_colours(
    int *colours, unsigned char *pixels, int width, int height, int x
)
{
    int i = height;
    int *colour = colours;
    unsigned char *rgb = &pixels[3 * x];

    while (--i >= 0)
    {
        *colour = palette_getindex(rgb);
        colour++;
        rgb += 3 * width;
    }
}

//
// createcolumn
//
// make a doom patch column from an array of colour indices
//

static size_t createcolumn(unsigned char **column, int *colours, int height)
{
    size_t size = 256, length = 0;
    unsigned char *data = static_cast<unsigned char *>(xmalloc(size));
    int i, y, top, transparent, opaque;

    for (y = 0; y < height;)
    {
        // we are at the start of a new post
        top = y;

        // count transparent pixels above post and opaque pixels in it
        transparent = opaque = 0;
        for (; y < height && colours[y] == -1; y++)
        {
            transparent++;
        }
        for (; y < height && colours[y] >= 0; y++)
        {
            opaque++;
        }

        if (opaque > 0) // this post has pixels
        {
            while (size < length + static_cast<size_t>(opaque) + 8)
            {
                size *= 2,
                    data = static_cast<unsigned char *>(xrealloc(data, size));
            }

            data[length++] =
                static_cast<unsigned char>(top + transparent); // column offset
            data[length++] =
                static_cast<unsigned char>(opaque); // length of column
            data[length++] = 0;                     // padding

            for (i = 0; i < opaque; i++)
            {
                data[length++] =
                    static_cast<unsigned char>(colours[top + transparent + i]);
            }

            data[length++] = 0; // more padding
        }
    }
    data[length++] = 0xff; // end of column

    *column = data;
    return length;
}

//
// ppm_to_patch
//
// convert an 8-bit portable pixmap to doom's patch format
// insert_x and insert_y are the graphic/sprite insertion point
//

size_t ppm_to_patch(
    void **lumpdata, const char *filename, int insert_x, int insert_y
)
{
    void *data;
    size_t size = read_or_die(&data, filename);

    int i, width, height, *column_colours;
    unsigned char *pixels, **columns, *patch;
    size_t *columnsizes, totalcolumnsize, offset;

    pixels =
        parseppm(static_cast<char *>(data), size, filename, &width, &height);
    columns = static_cast<unsigned char **>(
        xmalloc(static_cast<size_t>(width) * sizeof(*columns))
    );
    columnsizes = static_cast<size_t *>(
        xmalloc(static_cast<size_t>(width) * sizeof(*columnsizes))
    );
    column_colours = static_cast<int *>(
        xmalloc(static_cast<size_t>(height) * sizeof(*column_colours))
    );

    for (totalcolumnsize = i = 0; i < width; i++)
    {
        pixels_to_colours(column_colours, pixels, width, height, i);
        columnsizes[i] = createcolumn(&columns[i], column_colours, height);
        totalcolumnsize += columnsizes[i];
    }

    patch = static_cast<unsigned char *>(
        xmalloc(static_cast<size_t>(8 + 4 * width) + totalcolumnsize)
    );

    ((short *)patch)[0] = SHORT(width);
    ((short *)patch)[1] = SHORT(height);
    ((short *)patch)[2] = SHORT(insert_x);
    ((short *)patch)[3] = SHORT(insert_y);

    for (offset = static_cast<size_t>(8 + 4 * width), i = 0; i < width; i++)
    {
        ((int *)(patch + 8))[i] = static_cast<int>(offset);
        offset += columnsizes[i];
    }

    for (offset = static_cast<size_t>(8 + 4 * width), i = 0; i < width; i++)
    {
        memmove(patch + offset, columns[i], columnsizes[i]);
        offset += columnsizes[i];
        free(columns[i]);
    }

    free(column_colours);
    free(columnsizes);
    free(columns);
    free(data);

    *lumpdata = patch;
    return static_cast<size_t>(8 + 4 * width) + totalcolumnsize;
}

//
// ppm_to_bitmap
//
// convert an 8-bit PPM to a raw map of Doom palette indices (for flats)
//

size_t ppm_to_bitmap(void **lumpdata, const char *filename)
{
    void *data;
    size_t size = read_or_die(&data, filename);

    int i, j, width, height;
    unsigned char *pixels, *bitmap;

    pixels = parseppm(
        reinterpret_cast<char *>(data), size, filename, &width, &height
    );
    bitmap =
        static_cast<unsigned char *>(xmalloc(static_cast<size_t>(width * height)
        ));

    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width; i++)
        {
            bitmap[width * j + i] = static_cast<unsigned char>(
                palette_getindex(&pixels[3 * (width * j + i)])
            );
        }
    }

    free(data);

    *lumpdata = bitmap;
    return static_cast<size_t>(width * height);
}
