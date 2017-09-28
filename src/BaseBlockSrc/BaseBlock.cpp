#include "BaseBlock.h"

using namespace std;

BaseBlock::BaseBlock(int blockType, string tag, bool diggable)
    :m_blockType(blockType)
    ,m_tag(tag)
    ,m_diggable(diggable)
{
}


int BaseBlock::getBlockType()
{
    return m_blockType;
}

string BaseBlock::getTag()
{
    return m_tag;
}

bool BaseBlock::isDiggable()
{
    return m_diggable;
}

