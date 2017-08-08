#include "EntityTypesHeader/AntWorker.h"

AntWorker::AntWorker(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 0)
    ,m_state(new StateWorkerFood(this))
{
    setNextAction();
}

AntWorker::AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 0)
    ,m_state(new StateWorkerFood(this))
{
    setNextAction();
}

void AntWorker::gather(int typeResource)
{
    if (m_ptrMap->getBlock(m_destination)->getBlockType() == typeResource)
    {
        int quantity(min(1000, m_ptrMap->getBlock(m_destination)->getQuantite()));
        setInventoryQuantity(quantity);
        setInventoryType(m_ptrMap->getBlock(m_destination)->getBlockType());
        m_ptrMap->getBlock(m_destination)->dimQuantite(quantity);
    }
}
bool AntWorker::store()
{
    if (getBlock(m_destination)->getBlockType() != 3)
    {
        setBlock(m_destination, 3, m_inventoryType);
    }
    else if(getBlock(m_destination)->getQuantite() > 20000)
    {
        lookFor(3);
        return true;
    }
    if(getInventoryType() == getBlock(m_destination)->getValueStorage())
    {
        int quantity(min(20000-getBlock(m_destination)->getQuantite(), getInventoryQuantity()));
        getBlock(m_destination)->addQuantite(quantity);
        setInventoryQuantity(getInventoryQuantity()-quantity);
    }
    return true;
}

StateWorker* AntWorker::getState()
{
    return m_state.get();
}
void AntWorker::setState(StateWorker newState)
{
    if (newState.m_string == "food")
    {
        m_state.reset(new StateWorkerFood(this));
    }
    else if (newState.m_string == "idle")
    {
        m_state.reset(new StateWorkerIdle(this));
    }
    else if (newState.m_string == "gather")
    {
        m_state.reset(new StateWorkerGather(this));
    }
}

bool AntWorker::nextStep()
{
    falling();
    return m_state->execute(this);
}
