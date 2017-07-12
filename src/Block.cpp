#include "Block.h"
#include <iostream>
using namespace std;

Block::Block():m_valeurCase(0)
    ,m_tag("Air")
{
    m_isCrossable = false;
    m_isDiggable = false;
}
Block::Block(int n, bool crossable, bool diggable, int cost)
    :m_valeurCase(n)
    ,m_isCrossable(crossable)
    ,m_isDiggable(diggable)
    ,m_cost(cost)
{}
int Block::getValeurCase() const
{
    return m_valeurCase;
}
void Block::setValeurCase(int n)
{
    m_valeurCase = n;
    if (n==0)
    {
        setCrossable(false);
        setDiggable(false);
    }
    else if (n==2)
    {
        setCrossable(false);
        setDiggable(true);
    }
    else
    {
        setCrossable(false);
        setDiggable(false);
    }
}
int Block::getCost() const
{
    return m_cost;
}
void Block::setCost(int cost)
{
    m_cost = cost;
}
string Block::getString() const
{
    return m_tag;
}
bool Block::isCrossable()
{
    return m_isCrossable;
}
bool Block::isDiggable()
{
    return m_isDiggable;
}
void Block::setCrossable(bool boolean)
{
    m_isCrossable = boolean;
}
void Block::setDiggable(bool boolean)
{
    m_isDiggable = boolean;
}

/* --------------------- Heritage --------------------- */

void Block::setQuantite(int quantite)
{
}
int Block::getQuantite()
{
    return 1;
}
void Block::dimQuantite(int quantite)
{
}
void Block::addQuantite(int quantite)
{
}
int Block::getValueStorage()
{
    return 0;
}
