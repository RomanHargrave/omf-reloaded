#ifndef FONT_8_H
#define FONT_8_H

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef BYTE font8Letter[8];
typedef struct
{
    int size;
    font8Letter * f;
} font8;

/**
*   Loads a font from file
*   WARNING: Free this pointer when you don't need it.
*/
font8 loadFont8(FILE *);

/**
*   Saves a font in a file
*/
void saveFont8(font8, FILE *);

/**
*   Prints a single character, with char representation and offset int
*/
void printFont8Letter(font8Letter,char,int);

/**
*   Prints a whole font:
*/
void printFont8(font8,int);

/**
*   Gains control of the program and converts it into a font8 editor:
*/
font8 font8Editor(font8);

#endif // FONT_8_H
