#ifndef CSPRITE_H
#define CSPRITE_H

#include <vector>
#include <SDL/SDL.h>
#include <CPalette.h>
#include <COMF.h>
#include <general.h>

class CSprite
{
public:
    /**
    *   Default constructor.
    */
    CSprite();

    /**
    *   The same as default constructor plus it calls load function.
    */
    CSprite(const byte * spriteData);

    /**
    *   Just a destructor
    */
    virtual ~CSprite();

    /**
    *   Loads from raw byte memory, sprite header and sprite data.
    */
    void load(const byte * spriteData);

    /**
    *   Returns the size of read bytes of sprite.
    */
    int rawSize();

    /**
    *   Draws the sprite.
    *   TODO: Use palettes.
    */
    void draw(int x, int y, const CPalette & pal);

    /**
    *   Returns a rectangle of the size of the sprite,
    *   and position the offset of the sprite.
    */
    SDL_Rect imageInfo();

protected:
private:
    int m_readSize;

    /**
    *    Header information:
    */
    word m_length;
    short m_x;
    short m_y;
    word m_width;
    word m_height;
    byte m_index;
    byte m_dataMissing;

    /**
    *   Data of sprite:
    */
    std::vector<std::vector<byte> > m_spriteData;
};

#endif // CSPRITE_H
