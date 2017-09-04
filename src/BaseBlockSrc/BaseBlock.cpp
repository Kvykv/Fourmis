#include "BaseBlock.h"

BaseBlock::BaseBlock(int blockType, string tag)
    :m_blockType(blockType)
    ,m_tag(tag)
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

