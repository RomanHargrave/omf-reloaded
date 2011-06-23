#include "FrameHandler.h"

FrameHandler::FrameHandler()
{
    m_running = 0;
}

FrameHandler::~FrameHandler()
{
    //dtor
}

void FrameHandler::handle(Game_Frame * gf, CL_String name)
{
    if (m_handle[name])
        return;
    m_handle[name] = gf;
    gf->owner = (void*)this;
}

bool FrameHandler::gfx_tick(CL_PixelBuffer * pxb)
{
    if (m_running)
        return m_running->gfx_tick(pxb);
    return true;
}
