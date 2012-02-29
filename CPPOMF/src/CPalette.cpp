#include "CPalette.h"

CPalette::CPalette()
{
    //ctor
}

CPalette::CPalette(const byte * paletteData)
{
    //Load palette:
    memcpy(m_paletteColors,paletteData,256*3);
}

CPalette::~CPalette()
{
    //dtor
}

pixel CPalette::getColor(int index) const
{
    return pixel(m_paletteColors[index*3],m_paletteColors[index*3+1],m_paletteColors[index*3+2]);
}
