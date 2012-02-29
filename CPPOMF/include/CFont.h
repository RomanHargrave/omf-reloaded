#ifndef CFONT_H
#define CFONT_H

#include <string>
#include <general.h>
#include <algorithm>
#include <algorithm.h>
#include <COMF.h>
#include <SDL/SDL.h>

/**
*   Enumeration for all kind of fonts.
*/
enum FONTS
{
    F_large, F_small
};


/**
*   Environment to write on screen texts with OMF's fonts.
*   This is a static class. Don't make an instance of it.
*   Access to singleton instead.
*/
class CFont
{
public:
    /**
    *   Don't use constructor. Instead, use singleton access.
    */
    CFont();

    /**
    *   Just a destructor. Nothing to say here...
    */
    virtual ~CFont();

    /**
    *   Returns the singleton for font access:
    */
    static CFont * getSingletonPtr();
    static CFont & getSingleton();

    /**
    *   Draw on screen at (x,y) the "text" with that "font",
    *   and returns a rectangle where the text is going to be drawn
    */
    SDL_Rect draw(int x, int y, const std::string & text, FONTS font, const pixel & color);

protected:
private:
    /**
        Draws a single character at (x,y).
    */
    void drawChar(int x, int y, char m, FONTS font, const pixel & color);

    /**
    *   Those pointers contain information from OMF fonts.
    */
    byte * m_charTableLarge;
    byte * m_charTableSmall;
};

#endif // CFONT_H
