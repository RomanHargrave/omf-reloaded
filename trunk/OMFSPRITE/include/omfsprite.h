#ifndef OMFSPRITE_H_INCLUDED
#define OMFSPRITE_H_INCLUDED

#define indexPointer(in,pt) (void*)((long long)pt+in)

typedef unsigned char BYTE;
typedef short WORD;
typedef int DWORD;
typedef unsigned short UWORD;
typedef unsigned int UDWORD;

struct color24
{
    BYTE r,g,b;
};

struct color32
{
    BYTE r,g,b,a;
};


// Thanks to vulture a.k.a. Sean Stanek
struct omfSpriteHeader
{
    WORD length;
    WORD x;
    WORD y;
    WORD width;
    WORD height;
    BYTE index;
    BYTE link;
};

// Convierte un bloque de graficos OMF SPrITE a el estilo bitmap de colores de 32bits.
// Es decir, el OMF SPRITE SIN cabecera, y devuelve un BITMAP SIN cabecera.
void * omfSpriteToRawData(void * omfSprite, WORD length, color24 first, color24 second, color24 third, size_t & out_width, size_t & out_height);

#endif // OMFSPRITE_H_INCLUDED
