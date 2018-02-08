#include "include/EntityTypesHeader/AntWorker.h"

using namespace std;

AntWorker::AntWorker(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 0)
{
    float scale(3.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*tailleTileLargeur,scale*tailleTileHauteur);
    paintEntite();
    if (antHill->m_numberWorkerBuild == 0)
    {
        m_state.reset(new StateWorkerBuild(this));
    }
    else if (antHill->m_numberWorkerGather == 0)
    {
        m_state.reset(new StateWorkerGather(this));
    }
    else
    {
        m_state.reset(new StateWorkerIdle(this));
    }
}

AntWorker::AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 0)
{
    float scale(3.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*tailleTileLargeur,scale*tailleTileHauteur);
    paintEntite();
    if (antHill->m_numberWorkerBuild == -1)
    {
        m_state.reset(new StateWorkerBuild(this));
    }
    if (antHill->m_numberWorkerFarm != antHill->getSpecificNumberTile("Mushroom"))
    {
        m_state.reset(new StateWorkerFarm(this));
    }
    else if (rand()%11 < 5)
    {
        m_state.reset(new StateWorkerGather(this));
    }
    else
    {
        m_state.reset(new StateWorkerIdle(this));
    }
}

AntWorker::~AntWorker()
{
    if (m_state->m_string == "idle")
    {
        m_antHill->m_numberWorkerIdle -= 1;
    }
    else if (m_state->m_string == "gather")
    {
        m_antHill->m_numberWorkerGather -= 1;
    }
    else if (m_state->m_string == "build")
    {
        m_antHill->m_numberWorkerBuild -= 1;
    }
    m_antHill->m_dead+=1;
}

void AntWorker::gather(int typeResource)
{
    if (getBlock(m_destination)->getBlockType() == typeResource)
    {
        int quantity(min(2000, m_ptrMap->getBlock(m_destination)->getQuantity()));
        setInventoryQuantity(quantity);
        setInventoryType(m_ptrMap->getBlock(m_destination)->getStorageType());
        m_ptrMap->dimQuantiteBlock(m_destination, quantity);
    }
}
bool AntWorker::store()
{
    if (getBlock(m_destination)->getBlockType() != 3)
    {
        goTo(getNotFullStorage());
        return true;
    }
    else if(getBlock(m_destination)->getQuantity() >= getBlock(m_destination)->getCapacity())
    {
        goTo(getNotFullStorage());
        return true;
    }
    if(getInventoryType() == getBlock(m_destination)->getStorageType())
    {
        int quantity(min(getBlock(m_destination)->getCapacity()-getBlock(m_destination)->getQuantity(), getInventoryQuantity()));
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
        m_state.reset(new StateWorkerIdle(this));
    else if (newState.m_string == "gather")
        m_state.reset(new StateWorkerGather(this));
    else if (newState.m_string == "build")
        m_state.reset(new StateWorkerBuild(this));
    else if (newState.m_string == "farm")
         m_state.reset(new StateWorkerFarm(this));
}

pair<int,int> AntWorker::getNotFullStorage()
{
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> storage = m_antHill->getTileArray()->equal_range("Storage");
    if (storage.first!=m_antHill->getTileArray()->end())
    {
        for (multimap<string, pair<int,int> >::iterator i = storage.first; i != storage.second; i++)
        {
            if (getBlock(i->second)->getQuantity() < getBlock(i->second)->getCapacity())
            {
                return i->second;
            }
        }
    }
    return getCoord();
}

bool AntWorker::nextStep()
{
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
        return Tile(-1, getCoord());
    }
}

bool AntWorker::farm()
{
    if (getBlock(m_destination)->getQuantity() >= 500 && getBlock(m_destination)->getCare() > 1400)
    {
        gather(7);
        return false;
    }
    return (getBlock(m_destination)->addCare(1));

}
