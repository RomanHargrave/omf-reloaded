#include "application.h"

CL_ClanApplication app(&application::main);

// Static items to access:
static cl_uint64 _lasttime = 0;
static CL_PixelBuffer * d_pixel_buffer;
FrameHandler gfh;
Intro gfi;

int application::main(const std::vector<CL_String> &args)
{
    // Setups:
    CL_SetupCore setup_core;
    CL_SetupDisplay setup_display;
    CL_SetupGL setup_opengl;
    global_options * options = global_options::getSingletonPtr();

    #ifdef _DEBUG
    CL_ConsoleWindow console("Console",80,200);
    #endif

    // Window:
    CL_DisplayWindowDescription cdwd;
    cdwd.set_fullscreen(true);
    cdwd.set_size(CL_Size(320,200),true);
    CL_DisplayWindow window(cdwd);
    // Window's contexts:
    CL_GraphicContext gc = window.get_gc();
    CL_InputContext ic = window.get_ic();


    // The pixel buffer to draw:
    d_pixel_buffer = new CL_PixelBuffer(gc,320,200);
    // Loop relationed:
    float sleepdelta = 1000.0/options->framerate;
    bool run = true;

    // Frames of the videogame:
    gfh.handle((Game_Frame*)&gfi,"Intro");

    // Videogame's loop:
    while (run)
    {
        run = run && application::in_tick(ic);
        run = run && application::think_tick();
        run = run && application::net_tick();
        run = run && application::gfx_tick(gc);
        window.flip();

        CL_KeepAlive::process();
        CL_System::sleep(sleepdelta);
    }

    delete d_pixel_buffer;

    return 0;
}

bool application::gfx_tick(CL_GraphicContext gc)
{
    bool result = true;
    d_pixel_buffer->lock(cl_access_read_write);
    result = result && gfh.gfx_tick(d_pixel_buffer);
    d_pixel_buffer->unlock();
    return true;
}

bool application::in_tick(CL_InputContext ic)
{
    if (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE))
        return false;
    return true;
}

bool application::net_tick()
{
    return true;
}

bool application::think_tick()
{

    return true;
}

float application::delta()
{
    float result = 0;
    if (_lasttime)
        result = (CL_System::get_microseconds()-_lasttime);
    _lasttime = CL_System::get_microseconds();
    return result/1000000.0;
}
