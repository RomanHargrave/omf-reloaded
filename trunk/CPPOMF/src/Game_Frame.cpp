#include "Game_Frame.h"

Game_Frame::Game_Frame()
{
    //ctor
}

Game_Frame::~Game_Frame()
{
    //dtor
}

bool Game_Frame::start()
{
    return !_isrunning;
}

bool Game_Frame::end()
{
    return _isrunning;
}

bool Game_Frame::isRunning()
{
    return _isrunning;
}

bool Game_Frame::change(Game_Frame & to)
{
    return _isrunning;
}

bool Game_Frame::gfx_tick(CL_PixelBuffer*)
{
    return false;
}

bool Game_Frame::in_tick(CL_InputContext)
{
    return false;
}

bool Game_Frame::think_tick()
{
    return false;
}

bool Game_Frame::net_tick()
{
    return false;
}


bool Game_Frame::receive(Game_Frame & from)
{
    return !_isrunning;
}
