#ifndef APPLICATION_H
#define APPLICATION_H

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <global_options.h>

class application
{
    public:
        static int main(const std::vector<CL_String> &args);
        static bool gfx_tick(CL_GraphicContext);
        static bool in_tick(CL_InputContext);
        static bool think_tick();
        static bool net_tick();
        static float delta();
    protected:
    private:
};

#endif // APPLICATION_H
