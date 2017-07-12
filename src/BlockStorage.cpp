#include "BlockStorage.h"

using namespace std;

BlockStorage::BlockStorage(int quantite, int valueStorage)
    :Block(3, true, true, 1)
    ,m_valueStorage(valueStorage)
    ,m_quantite(quantite)
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
int BlockStorage::getValueStorage()
{
    return m_valueStorage;
}
