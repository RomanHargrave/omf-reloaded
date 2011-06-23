#ifndef INTRO_H
#define INTRO_H

#include <Game_Frame.h>
#include <FrameHandler.h>
#include <OMF_background.h>

class Intro : public Game_Frame
{
    public:
        Intro();
        ~Intro();
        bool start();
        bool end();
        bool change(Game_Frame & to, CL_String name);
        bool gfx_tick(CL_PixelBuffer*);
        bool in_tick(CL_InputContext);
        bool think_tick();
        bool net_tick();
    protected:
        bool receive(Game_Frame & from);
    private:
        OMF_Background m_back;
};

#endif // INTRO_H
