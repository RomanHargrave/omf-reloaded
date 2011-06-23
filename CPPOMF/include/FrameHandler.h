#ifndef FRAMEHANDLER_H
#define FRAMEHANDLER_H

#include <Game_Frame.h>
#include <map>

class FrameHandler
{
    public:
        FrameHandler();
        ~FrameHandler();
        // Game_Frame handling:
        void handle(Game_Frame * gf, CL_String name);
        void unhandle(CL_String name);
        void run(CL_String name);
        void change(CL_String name);
        // Getters and Setters:
        Game_Frame * getGameFrame(CL_String name);

        // Ticks:
        bool gfx_tick(CL_PixelBuffer * pxb);
    protected:
    private:
    std::map<CL_String,Game_Frame*> m_handle;
    Game_Frame * m_running;

};

#endif // FRAMEHANDLER_H
