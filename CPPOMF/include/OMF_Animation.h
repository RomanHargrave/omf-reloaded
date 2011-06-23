#ifndef OMF_ANIMATION_H
#define OMF_ANIMATION_H

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class OMF_Animation
{
    public:
        OMF_Animation(CL_File file);
        OMF_Animation(CL_String filename);
        OMF_Animation(const void * buffer, size_t sizeofbuffer);
        ~OMF_Animation();
    protected:
    private:
};

#endif // OMF_ANIMATION_H
