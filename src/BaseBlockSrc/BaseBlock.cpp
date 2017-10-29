#include "include/BaseBlockHeader/BaseBlock.h"

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

std::array<std::vector<int>,8> BaseBlock::getStructure()
{
    std::array<std::vector<int>,8> structure = {{{-1},  {-1},   {-1},
                                                 {-1},           {-1},
                                                 {-1},{-1}, {-1}}};
    return structure;
}
