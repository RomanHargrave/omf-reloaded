#include "CFont.h"

static CFont * _single;

CFont::CFont()
{
    /// Load large font:
    m_charTableLarge = (byte*)falloc("data/GRAPHCHR.DAT");
    if (!m_charTableLarge)
        fprintf(stderr, "Unable open data/GRAPHCHR.DAT");

    /// Load small font:
    m_charTableSmall = (byte*)falloc("data/CHARSMAL.DAT");
    if (!m_charTableSmall)
        fprintf(stderr, "Unable open data/CHARSMAL.DAT");
}

CFont::~CFont()
{
    if (m_charTableLarge)
        free(m_charTableLarge);
    if (m_charTableSmall)
        free(m_charTableSmall);
}

CFont * CFont::getSingletonPtr()
{
    return (_single ? _single : _single = new CFont());
}

CFont & CFont::getSingleton()
{
    return (_single ? *_single : *(_single = new CFont()));
}

SDL_Rect CFont::draw(int x, int y, const std::string & text, FONTS font, const pixel & color)
{
    // Rectangle being returned:
    SDL_Rect result;
    result.x = x;
    result.y = y;
    result.w = 0;

    // Iterate over string:
    for (int i = 0; i < (int)text.size(); i++)
    {
        // New line:
        if (text[i] == '\n')
        {
            // Add the height of the font:
            if (font  == F_large)
                y += 8;
            else if (font == F_small)
                y += 6;
            x = result.x;
        }
        else if (text[i] == '\t')
        {
            // Insert 2 spaces where tab is found.
            x += (8)*2;
        }
        else
        {
            this->drawChar(x,y,text[i],font,color);
            x+=8;
        }
        result.w = std::max((int)result.w,x-result.x);
    }
    // Add one line height:
    if (font  == F_large)
        y += 8;
    else if (font == F_small)
        y += 6;
    result.h = y-result.y;


    return result;
}

void CFont::drawChar(int x, int y, char m, FONTS font, const pixel & color)
{
    int index = 0;
    int height = 0;

    // Get index in memory:
    if (font == F_large)
    {
        index = (m-32)*8;
        height = 8;
    }
    else if (font == F_small)
    {
        index = (m-32)*6;
        height = 6;
    }

    // Draw:
    for (int i = 0; i < height; i++)
    {
        // Get index in pixels:
        byte line = 0;
        if (font == F_small)
            line = m_charTableSmall[index+i];
        else if (font == F_large)
            line = m_charTableLarge[index+i];
        for (int j = 0; j < 8; j++)
        {
            if (line&128)
            {
                COMF::getSingletonPtr()->setPixel(x+j,y+i,color);
            }
            line <<= 1;
        }
    }
}
