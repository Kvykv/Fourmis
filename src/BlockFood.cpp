#include "BlockFood.h"

using namespace std;

BlockFood::BlockFood(int quantite)
    :Block(2, true, true, 1)
    ,m_quantity(quantite)
{
    m_tag = "Food";
}

void BlockFood::setQuantity(int quantite)
{
    m_quantity = quantite;
}
int BlockFood::getQuantity()
{
    return m_quantity;
}
void BlockFood::dimQuantity(int quantite)
{
    m_quantity = m_quantity - quantite;
}
void BlockFood::addQuantity(int quantite)
{
    m_quantity = m_quantity + quantite;
}
