#ifndef GAME_FRAME_H
#define GAME_FRAME_H

#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Game_Frame
{
    friend class FrameHandler;
    public:
        Game_Frame();
        virtual ~Game_Frame();
        virtual bool start();
        virtual bool end();
        bool isRunning();
        virtual bool change(Game_Frame & to);
        virtual bool gfx_tick(CL_PixelBuffer*);
        virtual bool in_tick(CL_InputContext);
        virtual bool think_tick();
        virtual bool net_tick();
    protected:
        virtual bool receive(Game_Frame & from);
        void * owner;
    private:
        bool _isrunning;
};

#endif // GAME_FRAME_H
