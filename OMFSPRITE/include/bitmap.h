#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>
#include <cstdlib>

/* Note: the magic number has been removed from the bmpfile_header structure
   since it causes alignment problems
     struct bmpfile_magic should be written/read first
   followed by the
     struct bmpfile_header
   [this avoids compiler-specific alignment pragmas etc.]
*/

struct bmpfile_magic
{
  unsigned char magic[2];
};

struct bmpfile_header
{
  uint32_t filesz;
  uint16_t creator1;
  uint16_t creator2;
  uint32_t bmp_offset;
};

struct BITMAPINFOHEADER
{
  uint32_t header_sz;
  int32_t width;
  int32_t height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
};

void *  bmp24BitsFromPixels(void * pixels, size_t height, size_t width, size_t & totalsize);

#endif // BITMAP_H
