#include "include\BlockHeader\BlockMushroom.h"

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
        m_care-=50;
        if (m_care < 1000)
           dimQuantity(m_quantity/10);
        else
           addQuantity(100 + m_quantity/10);
    }

}

int BlockMushroom::getCare()
{
    return m_care;
}

bool BlockMushroom::addCare(int care)
{
    m_care = min(1200, m_care + care);
    return true;
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
