#include "CSprite.h"

CSprite::CSprite()
{
    // Init
    m_readSize = 0;
}

CSprite::CSprite(const byte * spriteData)
{
    // Init
    m_readSize = 0;
    this->load(spriteData);
}

CSprite::~CSprite()
{
}

void CSprite::load(const byte * spriteData)
{


    // Read the whole header:
    memcpy(&m_length,spriteData,sizeof(m_length));
    m_readSize += sizeof(m_length);
    spriteData += sizeof(m_length);

    memcpy(&m_x,spriteData,sizeof(m_x));
    m_readSize += sizeof(m_x);
    spriteData += sizeof(m_x);

    memcpy(&m_y,spriteData,sizeof(m_y));
    m_readSize += sizeof(m_y);
    spriteData += sizeof(m_y);

    memcpy(&m_width,spriteData,sizeof(m_width));
    m_readSize += sizeof(m_width);
    spriteData += sizeof(m_width);

    memcpy(&m_height,spriteData,sizeof(m_height));
    m_readSize += sizeof(m_height);
    spriteData += sizeof(m_height);

    memcpy(&m_index,spriteData,sizeof(m_index));
    m_readSize += sizeof(m_index);
    spriteData += sizeof(m_index);

    memcpy(&m_dataMissing,spriteData,sizeof(m_dataMissing));
    m_readSize += sizeof(m_dataMissing);
    spriteData += sizeof(m_dataMissing);

    /// Instructions from wiki:
    if (m_index == 0)
        m_dataMissing = 0;

    m_spriteData = std::vector<std::vector<byte> > (m_height,
                   std::vector<byte>(m_width,0));

    /// Sprite data reading:
    // Initialize X and Y to 0
    int x = 0, y = 0;
    word p;
    while (true)
    {
        // Read 1 WORD as p:
        memcpy(&p,spriteData,sizeof(p));
        m_readSize += sizeof(p);
        spriteData += sizeof(p);

        // Modulus p by 4 to get opcode:
        int opcode = p%4;
        // Integer divide p by 4 to get data:
        int data = p/4;

        // Compare the opcode against the following:


        if (opcode == 0)
        {
            x = data;
        }
        else if (opcode == 1)
        {
            for (;data > 0; x++, data--)
            {
                // Read 1 byte and store it as pixel X,Y
                m_spriteData[y][x] = spriteData[0];
                m_readSize += sizeof(byte);
                spriteData += sizeof(byte);
            }
            x = 0;
        }

        else if (opcode == 2)
            y = data;
        else
            break;

    }
}

int CSprite::rawSize()
{
    return m_readSize;
}

SDL_Rect CSprite::imageInfo()
{
    SDL_Rect result;
    result.x = m_x;
    result.y = m_y;
    result.w = m_width;
    result.h = m_height;

    return result;
}

void CSprite::draw(int x, int y, const CPalette & pal)
{
    COMF * c = COMF::getSingletonPtr();
    for (size_t i = 0; i < m_spriteData.size(); i++)
    {
        for (size_t j = 0; j < m_spriteData[i].size(); j++)
        {
            if (m_spriteData[i][j])
                c->setPixel(x+j+m_x,y+i+m_y,pal.getColor(m_spriteData[i][j]));
        }
    }
}
