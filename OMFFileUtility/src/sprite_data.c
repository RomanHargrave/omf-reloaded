#include "sprite_data.h"
#include <main.h>

spriteData loadSpriteData(FILE * pFile, int position, int size)
{
    int backup = ftell(pFile);
    // Start at position:
    fseek(pFile,position,SEEK_SET);

    spriteData result;

    result.size = size;
    result.data = (BYTE*)malloc(sizeof(BYTE)*result.size);

    int sz = fread(result.data,sizeof(BYTE),result.size,pFile);
    if (sz != result.size)
    {
        fprintf(stderr, "Error reading sprite data from file.\n");
        exit(0);
    }

    // return file to position:
    fseek(pFile,backup,SEEK_SET);

    return result;
}

void saveSpriteData(spriteData s,FILE * pFile,int position)
{
    int backup = ftell(pFile);
    fseek(pFile,position,SEEK_SET);
    int w = fwrite(s.data, sizeof(BYTE),s.size,pFile);
    if (w != s.size)
    {
        fprintf(stderr, "Error saving the sprite header.\n");
        exit(0);
    }
    fseek(pFile,backup,SEEK_SET);
}

void destroySpriteData(spriteData s)
{
    free(s.data);
}

void printSpriteData(spriteData s, int offset)
{
    // Iterate over all data:
    int i = 0;
    while(i < s.size)
    {
        WORD * p = (WORD*)&s.data[i];
        i+=sizeof(WORD);
        int opcode  = (*p)%4;
        int info    = (*p)/4;

        printf("0x%04X: %d\t\t",offset+i,*p);
        if (opcode == 0)
        {
           printf("Set X to %d\n",info);
        }
        else if (opcode == 2)
        {
           printf("Set Y to %d\n",info);
        }
        else if (opcode == 1)
        {
           printf("Store %d pixels\n",info);
           while(info)
           {
               BYTE pix = s.data[i];
               i += sizeof(BYTE);
               printf("0x%02X ",pix);
               info--;
           }
           printf("\n");
        }
        else if (opcode == 3)
        {
            printf("End of sprite data\n");
            break;
        }
    }
}

spriteData spriteDataEditor(spriteData in, int offset)
{
    spriteData out = in;
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
            printSpriteData(out,offset);
        }
        else if (!strcmp(action,"help"))
        {
            showCommandsHelp();
        }
        else if (!strcmp(action,"set"))
        {
            char kind[64];
            int pos;
            int value;
            scanf("%s %X %d",kind,&pos,&value);
            if (pos < offset || pos > offset+12)
            {
                printf("Attemp to write outside the sprite data");
            }
            modifyValue(kind,pos-offset,value,&out);
        }
        else if (!strcmp(action,"save"))
        {
            char filename[128];
            scanf("%s",filename);
            FILE * pFile = fopen(filename,"wb");
            if (pFile)
            {
                saveSpriteHeader(out,pFile,0);
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
