#include "include/BlockHeader/BlockFood.h"

using namespace std;

BlockFood::BlockFood(shared_ptr<BaseBlock> baseBlock, int quantite)
    :Block(baseBlock, true, 1)
    ,m_quantity(quantite)
{
    if (quantite == -1)
        m_quantity = baseBlock->getConfig()->m_foodBaseQuantity;
}


void BlockFood::setQuantity(int quantite)
{
    m_quantity = quantite;
}
int BlockFood::getQuantity()
{
    return m_quantity;
}
bool BlockFood::dimQuantity(int quantite)
{
    m_quantity = max(m_quantity - quantite, 0);
    return (m_quantity == 0);
}
void BlockFood::addQuantity(int quantite)
{
    m_quantity = min(50000, m_quantity + quantite);
}

int BlockFood::getStorageType()
{
    return m_baseBlock->getBlockType();
}


std::string BlockFood::getInfo()
{
    std::stringstream sstm;
    sstm << Block::getInfo() << "    Resource Type : " << getStorageType() << "   Quantity : " << getQuantity();
    return sstm.str();
}

void BlockFood::update(int i)
{
    if (i%100 == 0)
        addQuantity(m_quantity/100);
}
