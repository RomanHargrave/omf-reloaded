#ifndef CANIMATION_H
#define CANIMATION_H

#include <CSprite.h>
#include <general.h>
#include <cstring>

/**
*   This class loads an animation, and gives a
*   good environment to access to information.
*/
class CAnimation
{
public:
    /**
    *   Default constructor. Does nothing but init pointers to NULL.
    */
    CAnimation();

    /**
    *   The same as default constructor plus it calls load function.
    */
    CAnimation(const byte * animData);

    /**
    *   Default constructor:
    */
    virtual ~CAnimation();

    /**
    *   Loads information about an animation from raw byte memory.
    *   The size of readed information can be retrieved with rawSize.
    */
    void load(const byte * animData);

    /**
    *   Returns the raw size, that is, the size of the animation in file format.
    *   Useful for advance a pointer in a file.
    */
    int rawSize();

protected:
private:

    int m_readSize;

    /**
    *   Data from animation:
    */
    /// byte zero_pading[8];
    word m_overlay;
    byte m_frameCount;
    dword * m_overlayTable;

    word m_stringLength;
    byte * m_string;
    /// The null terminator is already included in string
    byte m_extraAmount;

    word * m_extraStringLength;
    byte ** m_extraString;
    /// The null terminator is already included in string

    CSprite * m_sprites;
};

#endif // CANIMATION_H
