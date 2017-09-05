#include "BlockStorage.h"

using namespace std;

BlockStorage::BlockStorage(shared_ptr<BaseBlock> baseBlock, int quantity, int typeStorage)
    :Block(baseBlock, true, 1)
    ,m_typeStorage(typeStorage)
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
int BlockStorage::getTypeStorage()
{
    return m_typeStorage;
}

int BlockStorage::getCapacity()
{
    return m_capacity;
}
