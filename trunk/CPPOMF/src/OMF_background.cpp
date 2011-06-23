#include "OMF_background.h"

// Background from filename
OMF_Background::OMF_Background(CL_String filename)
{
    // Open that file:
    this->load(filename);
    // And parse it:
    this->parse();
    // No buffer:
    b_back = 0;
}

// This copies the buffer. So you can feel free to delete your buffer.
// This class won't touch your buffer as it is treated as CONST.
OMF_Background::OMF_Background(const void * buffer, size_t sizeofbuffer)
{
    // Is not using file:
    usingFile = false;
    // Copy the buffer:
    b_back = malloc(sizeofbuffer);
    memcpy(b_back,buffer,sizeofbuffer);
    // and parse it:
    this->parse();
}

// Blank background
OMF_Background::OMF_Background()
{
    // We are not (yet) using file:
    usingFile = false;
    // No buffer:
    b_back = 0;
}

OMF_Background::~OMF_Background()
{
    // If buffer, deallocate it:
    if (b_back)
        free(b_back);
}

// Given a filename, class opens it, and parses it:
void OMF_Background::load(CL_String name)
{
    usingFile = true;
    f_back.open(name);
}

// Given a CL_PixelBuffer of 320x200,
// it draws the background.
void OMF_Background::draw(CL_PixelBuffer * in_pixel_buffer)
{

}
