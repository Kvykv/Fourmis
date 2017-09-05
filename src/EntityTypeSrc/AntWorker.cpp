#include "EntityTypesHeader/AntWorker.h"

using namespace std;

AntWorker::AntWorker(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 0)
    ,m_state(new StateWorkerIdle(this))
{
    setNextAction();
}

AntWorker::AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 0)
{
    setNextAction();
    if (antHill->m_numberWorkerBuild == 0)
    {
        m_state.reset(new StateWorkerBuild(this));
    }
    else if (rand()%10 < 6)
    {
        m_state.reset(new StateWorkerGather(this));
    }
    else
    {
        m_state.reset(new StateWorkerIdle(this));
    }
}

void AntWorker::gather(int typeResource)
{
    if (m_ptrMap->getBlock(m_destination)->getBlockType() == typeResource)
    {
        int quantity(min(1000, m_ptrMap->getBlock(m_destination)->getQuantity()));
        setInventoryQuantity(quantity);
        setInventoryType(m_ptrMap->getBlock(m_destination)->getBlockType());
        m_ptrMap->getBlock(m_destination)->dimQuantity(quantity);
    }
}
bool AntWorker::store()
{
    if (getBlock(m_destination)->getBlockType() != 3)
    {
        goTo(getNotFullStorage());
        return true;
    }
    else if(getBlock(m_destination)->getQuantity() >= 20000)
    {
        goTo(getNotFullStorage());
        return true;
    }
    if(getInventoryType() == getBlock(m_destination)->getTypeStorage())
    {
        int quantity(min(20000-getBlock(m_destination)->getQuantity(), getInventoryQuantity()));
        getBlock(m_destination)->addQuantity(quantity);
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
     if (newState.m_string == "idle")
    {
        m_state.reset(new StateWorkerIdle(this));
    }
    else if (newState.m_string == "gather")
    {
        m_state.reset(new StateWorkerGather(this));
    }
    else if (newState.m_string == "build")
    {
        m_state.reset(new StateWorkerBuild(this));
    }
}

pair<int,int> AntWorker::getNotFullStorage()
{
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> storage = m_antHill->getTileArray()->equal_range("Storage");
    if (storage.first!=m_antHill->getTileArray()->end())
    {
        for (multimap<string, pair<int,int> >::iterator i = storage.first; i != storage.second; i++)
        {
            if (m_ptrMap->getBlock(i->second)->getQuantity() < m_ptrMap->getBlock(i->second)->getCapacity())
            {
                return i->second;
            }
        }
    }
    return getCoord();
}

bool AntWorker::nextStep()
{
    falling();
    return m_state->execute(this);
}

Tile AntWorker::popBuildQueue()
{
    if(!m_antHill->isEmptyBuildQueue())
    {
        return m_antHill->popBuildQueue();
    }
    else
    {
        return Tile(0, getCoord());
    }
}
