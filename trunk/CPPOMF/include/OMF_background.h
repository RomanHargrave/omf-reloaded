#ifndef OMF_BACKGROUND_H
#define OMF_BACKGROUND_H

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class OMF_background
{
    public:
        OMF_background();
        ~OMF_background();
        void draw(CL_PixelBuffer & in_pixel_buffer);
    protected:
    private:
        CL_File f_back;
};

#endif // OMF_BACKGROUND_H
