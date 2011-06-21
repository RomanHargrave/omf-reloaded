#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <omfsprite.h>
#include <bitmap.h>

using namespace std;

int main(int argc, char ** argv)
{
    string input;
    stringstream sstr;
    ifstream in;
    ofstream ou;
    color24 a,b,c;
    int m;
    omfSpriteHeader omfheader;
    unsigned long long index = 0;
    BYTE byte;
    int last;

    cout << "Escribe la carpeta de los sprites a convertir" << endl;
    getline(cin,input);
    cout << "Escribe los colores del sprite, separados cada uno por una línea, y separado" << endl
    << "cada color por un espacio" << endl
    << "por ejemplo: " << endl
    << "0 0 0" << endl
    << "255 0 0" << endl
    << "255 255 255" << endl
    << "con eso tomas el negro, el rojo y el blanco" << endl;

    // Primer color:
    cin >> m;
    a.r = (char)m;
    cin >> m;
    a.g = (char)m;
    cin >> m;
    a.b = (char)m;
    // Segundo color:
    cin >> m;
    b.r = (char)m;
    cin >> m;
    b.g = (char)m;
    cin >> m;
    b.b = (char)m;
    // Tercer color:
    cin >> m;
    c.r = (char)m;
    cin >> m;
    c.g = (char)m;
    cin >> m;
    c.b = (char)m;

    cout << "Escribe la cantidad de sprites a convertir" << endl;
    cin >> last;
    for (int i = 0; i <= last; i++)
    {
        // Abrir entrada:
        sstr << input << i;
        cout << sstr.str() << endl;
        in.open(sstr.str().c_str());
        // Coger el header del sprite:
        while(in.good() && index < sizeof(omfSpriteHeader))
        {
            byte = in.get();
            memcpy(indexPointer(index,&omfheader),&byte,sizeof(BYTE));
            index++;
        }
        // Comprobar que no sea un link:
        if (omfheader.link)
        {
            if (in.is_open())
                in.close();
            sstr.str("");
            index = 0;
            continue;
        }
        // Si no es un link, creo un bmp:
        sstr << ".bmp";
        ou.open(sstr.str().c_str());
        // Coger los pixels del sprite:
        void * pixels = malloc(sizeof(BYTE)*omfheader.length);
        index = 0;
        while(in.good() && index < sizeof(BYTE)*omfheader.length)
        {
            byte = in.get();
            memcpy(indexPointer(index,pixels),&byte,sizeof(BYTE));
            index++;
        }
        // Crear un bitmap:
        size_t width, height;
        void * rawBitMap = omfSpriteToRawData(pixels, sizeof(BYTE)*omfheader.length, a, b, c,width,height);
        void * bitmap = bmp24BitsFromPixels(rawBitMap,height,width,width);
        // Guardar el bitmap:
        ou.write((const char *)bitmap,width);
        // Deshacer los cambios y liberar la memoria:
        free(pixels);
        free(rawBitMap);
        free(bitmap);
        if (in.is_open())
            in.close();
        if (ou.is_open())
            ou.close();
        sstr.str("");
        index = 0;
    }
    return 0;
}
