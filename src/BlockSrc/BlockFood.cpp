#include "include/BlockHeader/BlockFood.h"

using namespace std;

BlockFood::BlockFood(shared_ptr<BaseBlock> baseBlock, int quantite)
    :Block(baseBlock, true, 1)
    ,m_quantity(quantite)
{
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
    m_quantity = m_quantity - quantite;
    return (m_quantity <= 0);
}
void BlockFood::addQuantity(int quantite)
{
    m_quantity = m_quantity + quantite;
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

