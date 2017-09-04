#include "Block.h"
#include <iostream>
using namespace std;

Block::Block(shared_ptr<BaseBlock> baseBlock):m_baseBlock(baseBlock)
{
    m_isCrossable = false;
    m_isDiggable = false;
}
Block::Block(shared_ptr<BaseBlock> baseBlock, bool crossable, bool diggable, int cost)
    :m_baseBlock(baseBlock)
    ,m_isCrossable(crossable)
    ,m_isDiggable(diggable)
    ,m_cost(cost)
{}
int Block::getBlockType() const
{
    return m_baseBlock->getBlockType();
}

int Block::getCost() const
{
    return m_cost;
}
void Block::setCost(int cost)
{
    m_cost = cost;
}
string Block::getTag() const
{
    return m_baseBlock->getTag();
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

void Block::setQuantity(int quantite)
{
}
int Block::getQuantity()
{
    return 1;
}
void Block::dimQuantity(int quantite)
{
}
void Block::addQuantity(int quantite)
{
}
int Block::getTypeStorage()
{
    return 0;
}

int Block::getCapacity()
{
    return 0;
}
