#ifndef COMF_H
#define COMF_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <general.h>
#include <CFont.h>
#include <CSprite.h>

/**
*   Class that makes all environment
*/
class COMF
{
public:
    /**
    *   Default constructor of COMF. Do not call it.
    *   Instead of it, access this environmnet with singleton ways.
    */
    COMF();

    /**
    *   Functions that returns the singleton of this class.
    */
    static COMF * getSingletonPtr();
    static COMF & getSingleton();

    virtual ~COMF();

    /**
    *   This function makes magic on screen and draws everything!
    */
    bool draw(double deltaTime);

    /**
    *   This function takes input and handle it
    */
    bool input(double deltaTime);

    /**
    * This function starts the game.
    * Before this function, configuration must be loaded.
    */
    int run();

    /**
    *   Return the pixel array of the game's screen.
    */
    void * getPixelArray();

    /**
    *   Sets a pixel at (x,y)
    *   NOTE: This automatically converts to resolution used,
    *   so (x,y) are always [0,320) and [0,200)
    */
    void setPixel(int x, int y, const pixel & p);

protected:
private:
    SDL_Surface * m_screen;
};

#endif // COMF_H
