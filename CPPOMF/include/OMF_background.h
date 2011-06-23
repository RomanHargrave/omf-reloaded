#ifndef OMF_BACKGROUND_H
#define OMF_BACKGROUND_H

#include <cstring>
#include <cstdlib>
#include <OMF_Animation.h>

class OMF_Background
{
    public:
        OMF_Background();
        OMF_Background(CL_String filename);
        OMF_Background(const void * buffer, size_t sizeofbuffer);
        ~OMF_Background();
        // Process functions:
        void draw(CL_PixelBuffer * in_pixel_buffer);
        void load(CL_String filename);
        void parse();
        // Data access functions:
        // Header:
        int getID();
        int getWidth();
        int getHeight();
        // Animations:
        int nextAnimationOffset(int index);
        char animationIndex(int animationOffset);
        // Animation headers:
        // Unkown values
        // AF Animation:
        OMF_Animation * getAnimation(int index);
        // Footer:
        int getArea();
        int getPalettes();
        // Palettes:
        CL_Color getPaleteColor(int index,char color);
    protected:
    private:
        CL_File f_back;
        void * b_back;
        bool usingFile;
};

#endif // OMF_BACKGROUND_H
