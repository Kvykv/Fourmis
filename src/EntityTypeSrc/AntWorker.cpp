#include "EntityTypesHeader/AntWorker.h"

AntWorker::AntWorker(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 0)
{
    setNextAction();
}

AntWorker::AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 0)
{
    setNextAction();
}

void AntWorker::gather(Block* block)
{
    int quantity(min(1000, block->getQuantite()));
    setInventoryQuantity(quantity);
    setInventoryType(block->getBlockType());
    block->dimQuantite(quantity);
}
void AntWorker::store(Block* block)
{
    if (getBlock(m_currentAction.getCoord())->getBlockType() != 3)
    {
        setBlock(m_currentAction.getCoord(), 3, m_inventoryType);
    }
    else if(getBlock(m_currentAction.getCoord())->getQuantite()<20000)
    {
        lookFor(3);
    }
    if(getInventoryType() == block->getValueStorage())
    {
        int quantity(min(20000-block->getQuantite(), getInventoryQuantity()));
        block->addQuantite(quantity);
        setInventoryQuantity(getInventoryQuantity()-quantity);
    }
}

