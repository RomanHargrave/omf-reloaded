#ifndef GENERAL_H
#define GENERAL_H

/// NULL definition
#ifndef NULL
#define NULL 0
#endif

/**
*   This constant will try to achieve a constant framerate.
*   This will ask operative system to be idle between frames.
*/
#define FRAME_RATE 30

/**
*   This is how large will be the screen in
*   relation of 320*200. A factor of 2:
*   480*200
*   A factor of 3:
*   960*600
*/
#define SCALE 3

/// Byte type
typedef unsigned char byte;
/// Word type
typedef unsigned short word;
/// Double word type:
typedef unsigned int dword;
/// Pixel type:
struct pixel
{
    pixel()
    {
        b = g = r = a = 0;
    }
    pixel(byte _b, byte _g, byte _r, byte _a = 255)
    {
        b = _b;
        g = _g;
        r = _r;
        a = _a;
    }
    byte b;
    byte g;
    byte r;
    byte a;
};

#endif // GENERAL_H
