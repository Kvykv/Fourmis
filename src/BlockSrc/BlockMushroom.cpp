#include "include\BlockHeader\BlockMushroom.h"
#include "include\Config.h"

using namespace std;

BlockMushroom::BlockMushroom(shared_ptr<BaseBlock> baseBlock, int quantite, int care)
    :BlockFood(baseBlock, quantite)
    ,m_care(care)
{
}

void BlockMushroom::update(int i)
{
    if (i%100 == 0)
    {
        m_care=max(0, m_care - 25);
        if (m_care < getConfig()->m_mushroomDecayLimit)
           dimQuantity(m_quantity/getConfig()->m_mushroomDecayRate);
        else
           addQuantity(getConfig()->m_mushroomFlatGrowthRate + m_quantity/getConfig()->m_foodGrowthRate);
    }
}

int BlockMushroom::getCare()
{
    return m_care;
}

bool BlockMushroom::addCare(int care)
{
    m_care = min(getConfig()->m_mushroomMaxCare, m_care + care);
    return true;
}

int BlockMushroom::getResourceType()
{
    if(m_quantity < 1000)
        return 0;
    else
        return 2;
}

int BlockMushroom::getStorageType()
{
    return 2;
}

std::string BlockMushroom::getInfo()
{
    std::stringstream sstm;
    sstm << BlockFood::getInfo() << "    Care : " << getCare();
    return sstm.str();
}

bool BlockMushroom::isEmpty()
{
    return (m_quantity == 0);
}

std::shared_ptr<Config> BlockMushroom::getConfig()
{
    return m_baseBlock->getConfig();
}
