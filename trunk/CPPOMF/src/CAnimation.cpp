#include "CAnimation.h"

CAnimation::CAnimation()
{
    // NULL init:
    m_overlayTable = NULL;
    m_string = NULL;
    m_extraStringLength = NULL;
    m_extraString = NULL;
}

CAnimation::CAnimation(const byte * animData)
{
    // NULL init:
    m_overlayTable = NULL;
    m_string = NULL;
    m_extraStringLength = NULL;
    m_extraString = NULL;
    this->load(animData);
}

CAnimation::~CAnimation()
{
    if (m_overlayTable)
        delete[] m_overlayTable;
    if (m_string)
        delete[] m_string;
    if (m_extraString)
    {
        for (int i = 0; i < m_extraAmount; i++)
            delete[] m_extraString[i];
    }
    delete[] m_extraString;
}

void CAnimation::load(const byte * animData)
{
    // Start at 8 because the 8 bytes zero padding:
    m_readSize = 8;
    animData += 8;

    memcpy(&m_overlay,animData,sizeof(m_overlay));
    m_readSize += sizeof(m_overlay);
    animData += sizeof(m_overlay);

    memcpy(&m_frameCount,animData,sizeof(m_frameCount));
    m_readSize += sizeof(m_frameCount);
    animData += sizeof(m_frameCount);

    // Store overlay table:
    m_overlayTable = new dword[m_overlay];
    memcpy(m_overlayTable,animData,sizeof(dword)*m_overlay);
    m_readSize += sizeof(dword)*m_overlay;
    animData += sizeof(dword)*m_overlay;

    memcpy(&m_stringLength,animData,sizeof(m_stringLength));
    m_readSize += sizeof(m_stringLength);
    animData += sizeof(m_stringLength);

    // m_stringLength plus 1 because null terminator
    m_string = new byte[m_stringLength+1];
    memcpy(m_string,animData,sizeof(byte)*m_stringLength);
    m_readSize += sizeof(byte)*m_stringLength;
    animData += sizeof(byte)*m_stringLength;

    memcpy(&m_extraAmount,animData,sizeof(m_extraAmount));
    m_readSize += sizeof(m_extraAmount);
    animData += sizeof(m_extraAmount);

    if (m_extraString)
    {
        // Extra strings:
        m_extraStringLength = new word[m_extraAmount];
        m_extraString = new byte*[m_extraAmount];

        for (int i = 0; i < m_extraAmount; i++)
        {

            memcpy(&m_extraStringLength[i],animData,sizeof(m_extraStringLength[i]));
            m_readSize += sizeof(m_extraStringLength[i]);
            animData += sizeof(m_extraStringLength[i]);

            m_extraString[i] = new byte[m_extraStringLength[i]+1];
            memcpy(m_extraString[i],animData,sizeof(byte)*m_extraStringLength[i]);
            m_readSize += sizeof(byte)*m_extraStringLength[i];
            animData += sizeof(byte)*m_extraStringLength[i];
        }
    }
    // Load sprites:
    m_sprites = new CSprite[m_frameCount]();
    for (int i = 0; i < m_frameCount; i++)
    {
        m_sprites[i].load(animData);
        animData += m_sprites[i].rawSize();
    }
}


int CAnimation::rawSize()
{
    return m_readSize;
}
