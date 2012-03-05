#include "sprite.h"
#include <main.h>

sSprite loadSprite(FILE * pFile, int position)
{
    sSprite result;
    // Load header and image data.
    result.header = loadSpriteHeader(pFile,position);
    result.imageData = loadSpriteData(pFile,position+sizeof(result.header),result.header.length);

    return result;
}

void saveSprite(sSprite s,FILE * pFile,int position)
{
    // Save header and data
    saveSpriteHeader(s.header,pFile,position);
    saveSpriteData(s.imageData,pFile,position+sizeof(s.header));
}

void destroySprite(sSprite s)
{
    // Destroy header and data
    destroySpriteHeader(s.header);
    destroySpriteData(s.imageData);
}

void printSprite(sSprite s, int offset)
{
    // Show information.
    int index = offset;
    printf("0x%X: \t\theader:\n\n",index);
    printSpriteHeader(s.header,index);
    index += sizeof(s.header);

    // Sprite image data is to large to show it.
    printf("\n0x%x \t\tdata:\n",index);
    printf("Too large... use go command\n");
}

sSprite spriteEditor(sSprite in, int offset)
{
    sSprite out = in;
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
            printSprite(out,offset);
        }
        else if (!strcmp(action,"help"))
        {
            showCommandsHelp();
        }
        else if (!strcmp(action,"set"))
        {
            printf("If you want to set anything use go command to get into header or data.\n");
        }
        else if (!strcmp(action,"go"))
        {
            char where[64];
            scanf("%s",where);
            if (!strcmp(where,"header"))
            {
                SYSTEM_CLEAR;
                printf("Editting sprite header.\n");
                spriteHeaderEditor(out.header,offset);
            }
            else if (!strcmp(where,"data"))
            {
                SYSTEM_CLEAR;
                printf("Editting image data.\n");
                spriteDataEditor(out.imageData,offset+sizeof(sSpriteHeader));
            }
        }
        else if (!strcmp(action,"save"))
        {
            char filename[128];
            scanf("%s",filename);
            FILE * pFile = fopen(filename,"wb");
            if (pFile)
            {
                saveSprite(out,pFile,0);
                fclose(pFile);
            }
            else
            {
                printf("Could not open or create %s file\n",filename);
            }
        }
        else
        {
            if (strcmp(action,"exit"))
                printf("Unkown command \"%s\". Write help to check command list.\n",action);
        }
    }
    return out;
}
