#include "include/BaseBlockHeader/BaseBlock.h"

using namespace std;

BaseBlock::BaseBlock(int blockType, string tag, bool diggable, float thermalConductivity, std::shared_ptr<Config> config)
    :m_blockType(blockType)
    ,m_tag(tag)
    ,m_diggable(diggable)
    ,m_thermalConductivity(thermalConductivity)
    ,m_config(config)
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

float BaseBlock::getThermalCond()
{
    return m_thermalConductivity;
}

bool BaseBlock::isDiggable()
{
    return m_diggable;
}

bool BaseBlock::isSupport()
{
    return m_diggable || (m_blockType == 4);
}

std::array<std::vector<int>,8> BaseBlock::getStructure()
{
    std::array<std::vector<int>,8> structure = {{{-1},  {-1},   {-1},
                                                 {-1},           {-1},
                                                 {-1},{-1}, {-1}}};
    return structure;
}

std::shared_ptr<Config> BaseBlock::getConfig()
{
    return m_config;
}
