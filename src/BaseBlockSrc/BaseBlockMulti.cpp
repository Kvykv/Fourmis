#include "include/BaseBlockHeader/BaseBlockMulti.h"

BaseBlockMulti::BaseBlockMulti(int blockType, std::string tag, bool diggable)
    :BaseBlock(blockType, tag, diggable)
{
    switch (blockType)       // Premier element de chaque case : par defaut
    {
        case 3 :            // Storage
            m_structure = {{{5,3},  {5,3},   {5,3},
                            {5,3},           {5,3},
                            {1,3,4},{1,3,4}, {1,3,4}}};
            break;
        case 6 :            // QueenChamber
            m_structure = {{{5},  {5},   {5},
                            {5},           {5},
                            {1,4},{1,4}, {1,4}}};
            break;
        case 7 :            // Mushroom
            m_structure = {{{5},  {5},   {5},
                            {5,7},           {5,7},
                            {1,4},{1,4}, {1,4}}};
            break;
        default :
            BaseBlock::getStructure();
    }
}


std::array<std::vector<int>,8> BaseBlockMulti::getStructure()
{
    return m_structure;
}
