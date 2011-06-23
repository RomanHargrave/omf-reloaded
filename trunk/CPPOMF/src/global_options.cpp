#include "global_options.h"

static global_options * _singletonptr = 0;

global_options::global_options()
{
    // Singleton relationed:
    _singletonptr = this;

    // Default options:
    framerate = 60;         // Frames per second
    speed = 1000;           // How much virtual miliseconds are a real second.
    server_port = 2345;     // Hosting net games, which is the listen port.
}


global_options::~global_options()
{
    _singletonptr = 0;
}

global_options * global_options::getSingletonPtr()
{
    return (_singletonptr ? _singletonptr : new global_options());
}
