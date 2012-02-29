#ifndef CPALETTE_H
#define CPALETTE_H

#include <cstring>
#include <general.h>

/**
*   Class for load a palette
*/
class CPalette
{
public:
    /**
    *   Default constructor.
    */
    CPalette();

    /**
    *   Constructor from memory.
    */
    CPalette(const byte * paletteData);

    /**
    *   Default destructor.
    */
    virtual ~CPalette();

    /**
    *   Returns a color by the index.
    */
    pixel getColor(int index) const;


protected:
private:
    /**
    *   256 colors:
    */
    byte m_paletteColors[256*3];
};

#endif // CPALETTE_H
