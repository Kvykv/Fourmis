#include "BlockFood.h"

using namespace std;

BlockFood::BlockFood(int quantite)
    :Block(2, true, true, 1)
    ,m_quantite(quantite)
{
    m_tag = "Food";
}

void BlockFood::setQuantite(int quantite)
{
    m_quantite = quantite;
}
int BlockFood::getQuantite()
{
    return m_quantite;
}
void BlockFood::dimQuantite(int quantite)
{
    m_quantite = m_quantite - quantite;
}
void BlockFood::addQuantite(int quantite)
{
    m_quantite = m_quantite + quantite;
}
