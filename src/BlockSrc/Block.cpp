#include "include/BlockHeader/Block.h"
#include <iostream>
using namespace std;

Block::Block(shared_ptr<BaseBlock> baseBlock)
    :m_baseBlock(baseBlock)
    ,m_temperature(0)
    ,m_isCrossable(false)
{
}
Block::Block(shared_ptr<BaseBlock> baseBlock, bool crossable, int cost, int temperature)
    :m_baseBlock(baseBlock)
    ,m_cost(cost)
    ,m_temperature(temperature)
    ,m_isCrossable(crossable)
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
bool Block::isSupport()
{
    return m_baseBlock->isSupport();
}

void Block::setCrossable(bool boolean)
{
    m_isCrossable = boolean;
}

float Block::getThermalCond()
{
    return m_baseBlock->getThermalCond();
}

int Block::getTemperature()
{
    return m_temperature;
}
void Block::setTemperature(int temperature)
{
    m_temperature = max(0, min(10000,temperature));
}

/* --------------------- Heritage --------------------- */

void Block::setQuantity(int quantite)
{
    (void)quantite;
}
int Block::getQuantity()
{
    return 0;
}
bool Block::dimQuantity(int quantite)
{
    (void)quantite;
    return false;
}
void Block::addQuantity(int quantite)
{
    (void)quantite;
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
    sstm << "Block Infos : " << m_baseBlock->getTag() << "   Temperature (cC) : " << m_temperature;
    return sstm.str();
}

void Block::update(int i)
{
    (void)i;
}

int Block::getCare()
{
    return -1;
}
bool Block::addCare(int care)
{
    (void)care;
    return false;
}


