#include "COMF.h"

static COMF * _single = NULL;

COMF::COMF()
{
    // Try to init SDL:
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    /// Flags explaination:
    /// SDL_SWSURFACE because perpixel manipulation
    m_screen = SDL_SetVideoMode(320*SCALE,200*SCALE,32,SDL_SWSURFACE);
}

COMF::~COMF()
{
    //dtor
}

bool COMF::draw(double deltaTime)
{

    return true;
}

bool COMF::input(double deltaTime)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return false;
            break;
        case SDL_QUIT:
            return false;
            break;
        }
    }
    return true;
}

int COMF::run()
{
    pixel p = pixel(255,255,255,255);
    SDL_Rect r = CFont::getSingletonPtr()->draw(10,10,"TWO PLAYER GAME\nNew line feed",F_large, p);

    p.b = p.g = 0;
    setPixel(r.x,r.y,p);
    setPixel(r.x+r.w,r.y,p);
    setPixel(r.x+r.w,r.y+r.h,p);
    setPixel(r.x,r.y+r.h,p);

    byte * spriteData = (byte*)falloc("data/FIGHTER0/Anim15/FrameE.opx");
    byte * paletteData = (byte*)falloc("data/test.plt");

    CPalette pal(paletteData);
    free(paletteData);

    CSprite sp(spriteData);
    free(spriteData);

    sp.draw(200,100,pal);

    spriteData = (byte*)falloc("data/FIGHTER0/Anim26/FrameA.opx");

    CSprite sp2(spriteData);
    free(spriteData);

    sp2.draw(295,41,pal);

    bool life = true;

    Uint32 lastTime = SDL_GetTicks();
    while (life)
    {
        Uint32 time = SDL_GetTicks();
        double deltaTime = (time-lastTime)/1000.0;
        lastTime = time;

        double frame_time = (1./FRAME_RATE);

        /// Process input:
        life = life&this->input(deltaTime);

        time = SDL_GetTicks();
        deltaTime = (time-lastTime)/1000.0;
        if (deltaTime < frame_time)
        {
            SDL_Delay((Uint32)((frame_time-deltaTime)*1000));
        }
    }
    return 0;
}

COMF * COMF::getSingletonPtr()
{
    return (_single ? _single : _single = new COMF());
}

COMF & COMF::getSingleton()
{
    return (_single ? *_single : *(_single = new COMF()));
}

void * COMF::getPixelArray()
{
    return m_screen->pixels;
}

void COMF::setPixel(int x, int y, const pixel & p)
{
    if (x < 0 || x >= 320*SCALE)
        return;
    if (y < 0 || y >= 200*SCALE)
        return;

    x*=SCALE;
    y*=SCALE;

    for (int i = 0; i < SCALE; i++)
        for (int j = 0; j < SCALE; j++)
        {
            int xy = (320*SCALE)*(y+i)+(x+j);
            byte * pixels = (byte*)m_screen->pixels;
            pixels[xy*sizeof(p)] = p.b;
            pixels[xy*sizeof(p)+1] = p.g;
            pixels[xy*sizeof(p)+2] = p.r;
            pixels[xy*sizeof(p)+3] = p.a;
        }

}
