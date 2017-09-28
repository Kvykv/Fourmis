#include "Block.h"
#include <iostream>
using namespace std;

Block::Block(shared_ptr<BaseBlock> baseBlock):m_baseBlock(baseBlock)
{
    m_isCrossable = false;
}
Block::Block(shared_ptr<BaseBlock> baseBlock, bool crossable, int cost)
    :m_baseBlock(baseBlock)
    ,m_isCrossable(crossable)
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
    return m_baseBlock->isDiggable();
}
void Block::setCrossable(bool boolean)
{
    m_isCrossable = boolean;
}

/* --------------------- Heritage --------------------- */

void Block::setQuantity(int quantite)
{
}
int Block::getQuantity()
{
    return 0;
}
bool Block::dimQuantity(int quantite)
{
    return false;
}
void Block::addQuantity(int quantite)
{
}
int Block::getStorageType()
{
    return 0;
}

int Block::getCapacity()
{
    return 0;
}

bool Block::isEmpty()
{
    return false;
}

string Block::getInfo()
{
    std::stringstream sstm;
    sstm << "Block Infos : " << m_baseBlock->getTag();
    return sstm.str();
}
