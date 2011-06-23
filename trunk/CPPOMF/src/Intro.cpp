#include "Intro.h"

Intro::Intro()
{
    // Allocate and parse the intro.bk file.
    m_back.load("./resources/original/intro.bk");
}

Intro::~Intro()
{

}

bool Intro::start()
{
    // Todo:
    // Initiate all video and sounds:
    return true;
}

bool Intro::end()
{
    // Todo:
    // Stop the video. Maybe it is nothing.
    return true;
}

// When changing from one Game_Frame to another Game_Frame, the Game_Frame
// that loses the focus must tell the Frame Handler that owns it to register
// the change.
bool Intro::change(Game_Frame & to, CL_String name)
{
    FrameHandler * fh = (FrameHandler*)owner;
    fh->run(name);
    return true;
}

bool Intro::gfx_tick(CL_PixelBuffer * cpxb)
{
    // Todo:
    m_back.draw(cpxb);
    return true;
}

bool Intro::in_tick(CL_InputContext)
{
    // Todo:
    // Detect escape to skip intro
    // Detect keys 2097 to check for that intro "cheat".
    return true;
}

bool Intro::think_tick()
{
    // Todo:
    // Emit sounds syncronized with the video.
    return true;
}

bool Intro::net_tick()
{
    return true;
}


bool Intro::receive(Game_Frame & from)
{
    return true;
}
