#include "BlockStorage.h"

using namespace std;

BlockStorage::BlockStorage(int quantite, int typeStorage)
    :Block(3, true, true, 1)
    ,m_typeStorage(typeStorage)
    ,m_quantite(quantite)
    ,m_capacity(20000)
{
    m_tag = "Storage";
}

void BlockStorage::setQuantite(int quantite)
{
    m_quantite = quantite;
}
int BlockStorage::getQuantite()
{
    return m_quantite;
}
void BlockStorage::dimQuantite(int quantite)
{
    m_quantite = m_quantite - quantite;
}
void BlockStorage::addQuantite(int quantite)
{
    m_quantite = m_quantite + quantite;
}
int BlockStorage::getTypeStorage()
{
    return m_typeStorage;
}

int BlockStorage::getCapacity()
{
    return m_capacity;
}
