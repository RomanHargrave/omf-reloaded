#include <cstdlib>
#include <omfsprite.h>
#include <vector>
#include <cstring>

using namespace std;

void * omfSpriteToRawData(void * omfSprite, WORD length, color24 first, color24 second, color24 third, size_t & out_width, size_t & out_height)
{
    // Color blanco:
    color24 trans;
    trans.r = trans.g = trans.b = 255;

    // Otras definiciones:
    void * result;
    vector<vector<color24> > image;
    unsigned long long index = 0;
    unsigned int LastX = 0;
    unsigned int LastY = 0;
    BYTE colorNumber;
    WORD temp;
    WORD dataLength;
    WORD command;

    out_width = 0;
    out_height = 0;

    while (length)
    {
        memcpy(&temp,indexPointer(index,omfSprite),sizeof(WORD));
        index += sizeof(WORD);
        length-= sizeof(WORD);

        dataLength = temp / 4;
        command = temp % 4;

        if (command == 0)
            LastX = dataLength;
        else if (command == 2)
        {
            LastY = dataLength;
            if (LastY >= image.size())
            {
                image.resize(LastY + 1,vector<color24>());
                out_height = LastY+1;
            }

        }
        else if (command == 3)
            break;
        else
        {
            for (int i = 0; i < dataLength; i++)
            {
                // Leer el color:
                memcpy(&colorNumber,indexPointer(index,omfSprite),sizeof(BYTE));
                index += sizeof(BYTE);
                length -= sizeof(BYTE);
                // Escribir el color:
                if (colorNumber < 16)
                {
                    if (LastX >= image[LastY].size())
                    {
                        image[LastY].resize(LastX + 1,trans);
                    }
                    image[LastY][LastX].r = colorNumber * first.r / 15;
                    image[LastY][LastX].g = colorNumber * first.g / 15;
                    image[LastY][LastX].b = colorNumber * first.b / 15;
                }
                else if (colorNumber < 32)
                {
                    if (LastX >= image[LastY].size())
                    {
                        image[LastY].resize(LastX + 1,trans);
                    }
                    image[LastY][LastX].r = (colorNumber-16) * second.r / 15;
                    image[LastY][LastX].g = (colorNumber-16) * second.g / 15;
                    image[LastY][LastX].b = (colorNumber-16) * second.b / 15;
                }
                else
                {
                    if (LastX >= image[LastY].size())
                    {
                        image[LastY].resize(LastX + 1,trans);
                    }
                    image[LastY][LastX].r = (colorNumber-32) * third.r / 15;
                    image[LastY][LastX].g = (colorNumber-32) * third.g / 15;
                    image[LastY][LastX].b = (colorNumber-32) * third.b / 15;
                }
                LastX++;
                if (LastX >= out_width)
                    out_width = LastX;
            }
            LastX = 0;
        }
    }
    // Ahora: copiar todo el vector a un bloque plano de información.
    // Como ya no voy a necesitar el color transparente (trans) más, lo uso como color temporal:
    unsigned long long padding = 4-(out_width*sizeof(color24))%4;
    padding = (padding == 4 ? 0 : padding);
    result = malloc((sizeof(color24)*out_width+padding)*out_height);
    index = 0;
    for (size_t i = 0; i < out_height; i++)
    {
        for (size_t j = 0; j < out_width; j++)
        {
            // Si no existe el color, se pone uno transparente:
            if (j >= image[out_height-i-1].size())
            {
                trans.r = trans.g = trans.b = 255;
            }
            else
                trans = image[out_height-i-1][j];
            // Se copia el color:
            // En bitmap, se copia BGR:
            memcpy(indexPointer(index,result),&trans.b,1);
            index++;
            memcpy(indexPointer(index,result),&trans.g,1);
            index++;
            memcpy(indexPointer(index,result),&trans.r,1);
            index++;
        }
        for (size_t j = 0; j < padding; j++)
        {
            memcpy(indexPointer(index,result),"\0",1);
            index++;
        }

    }
    return result;
}
