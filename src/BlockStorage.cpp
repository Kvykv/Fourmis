#include "BlockStorage.h"

using namespace std;

BlockStorage::BlockStorage(shared_ptr<BaseBlock> baseBlock, int quantity, int typeStorage)
    :Block(baseBlock, true, 1)
    ,m_storageType(typeStorage)
    ,m_quantity(quantity)
    ,m_capacity(20000)
{
}

void BlockStorage::setQuantity(int quantity)
{
    m_quantity = quantity;
}
int BlockStorage::getQuantity()
{
    return m_quantity;
}
void BlockStorage::dimQuantity(int quantity)
{
    m_quantity = m_quantity - quantity;
}
void BlockStorage::addQuantity(int quantity)
{
    m_quantity = m_quantity + quantity;
}
int BlockStorage::getStorageType()
{
    return m_storageType;
}

int BlockStorage::getCapacity()
{
    return m_capacity;
}

bool BlockStorage::isEmpty()
{
    return (m_quantity == 0);
}

std::string BlockStorage::getInfo()
{
    std::stringstream sstm;
    sstm << Block::getInfo() << "    Resource Type : " << getStorageType() << "   Quantity : " << getQuantity();
    return sstm.str();
}

