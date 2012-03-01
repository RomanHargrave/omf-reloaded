#include "sprite_header.h"
#include <main.h>

sSpriteHeader loadSpriteHeader(FILE * pFile)
{
    sSpriteHeader result;
    int sz = fread(&result,sizeof(result),1,pFile);
    if (sz != 1)
    {
        fprintf(stderr, "Error reading a sprite header from file.\n");
        exit(0);
    }
    return result;
}

void saveSpriteHeader(sSpriteHeader s,FILE * pFile)
{
    int w = fwrite(&s, sizeof(s),1,pFile);
    if (w != 1)
    {
        fprintf(stderr, "Error saving the sprite header.\n");
        exit(0);
    }
}

void printSpriteHeader(sSpriteHeader s, int offset)
{
    int index = offset;
    printf("0x%X: %3d\t\tLength\n",index,s.length);
    index += sizeof(s.length);
    printf("0x%X: %3d\t\tX\n",index,s.x);
    index += sizeof(s.x);
    printf("0x%X: %3d\t\tY\n",index,s.y);
    index += sizeof(s.y);
    printf("0x%X: %3d\t\tWidth\n",index,s.width);
    index += sizeof(s.width);
    printf("0x%X: %3d\t\tHeight\n",index,s.height);
    index += sizeof(s.height);
    printf("0x%X: %3d\t\tIndex\n",index,s.index);
    index += sizeof(s.index);
    printf("0x%X: %3d\t\tData missing\n",index,s.dataMissing);
}

sSpriteHeader spriteHeaderEditor(sSpriteHeader in)
{
    sSpriteHeader out = in;
    char action[512];
    while (strcmp(action,"exit"))
    {
        if (scanf("%s",action) == EOF)
        {
            printf("End of file found. Exiting.");
            break;
        }
        if (!strlen(action))
            continue;
        if (!strcmp(action,"show"))
        {
            printSpriteHeader(out,0);
        }
        else if (!strcmp(action,"help"))
        {
            showCommandsHelp();
        }
        else
        {
            if (strcmp(action,"exit"))
                printf("Unkown command \"%s\". Write help to check command list.\n",action);
        }
    }
    return out;
}