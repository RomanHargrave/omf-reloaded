#include <bitmap.h>
#include <omfsprite.h>
#include <cstring>

void *  bmp24BitsFromPixels(void * pixels, size_t height, size_t width, size_t & totalsize)
{
    void * result;
    unsigned long long index = 0;
    bmpfile_magic h1;

    bmpfile_header h2;
    BITMAPINFOHEADER h3;

    // Padding para llegar cada línea a un dividible por 4:
    unsigned long long padding = 4-(width*sizeof(color24))%4;
    padding = (padding == 4? 0 : 4);

    h1.magic[0] = 'B';
    h1.magic[1] = 'M';
    h2.bmp_offset = sizeof(bmpfile_magic)+sizeof(bmpfile_header)+sizeof(BITMAPINFOHEADER);
    h2.creator1 = 0;
    h2.creator2 = 0;
    h2.filesz = sizeof(bmpfile_magic)+sizeof(bmpfile_header)+sizeof(BITMAPINFOHEADER)+(sizeof(color24)*width+padding)*height;
    h3.bitspp = 24;
    h3.bmp_bytesz = (sizeof(color24)*width+padding)*height;
    h3.compress_type = 0;
    h3.header_sz = sizeof(BITMAPINFOHEADER);
    h3.height = height;
    h3.hres = 2835;
    h3.ncolors = 0;
    h3.nimpcolors = 0;
    h3.nplanes = 1;
    h3.vres = 2835;
    h3.width = width;

    totalsize = h2.filesz;
    result = malloc(h2.filesz);

    memcpy(indexPointer(index,result),&h1,sizeof(bmpfile_magic));
    index+=sizeof(bmpfile_magic);
    memcpy(indexPointer(index,result),&h2,sizeof(bmpfile_header));
    index+=sizeof(bmpfile_header);
    memcpy(indexPointer(index,result),&h3,sizeof(BITMAPINFOHEADER));
    index+=sizeof(BITMAPINFOHEADER);
    memcpy(indexPointer(index,result),pixels,(sizeof(color24)*width+padding)*height);
    index+=(sizeof(color24)*width+padding)*height;

    return result;
}
