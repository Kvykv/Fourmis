#include "include/EntityTypesHeader/AntWorker.h"

using namespace std;

AntWorker::AntWorker(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 0)
{
    float scale(3.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*m_ptrMap->getTailleTileLargeur(),scale*m_ptrMap->getTailleTileHauteur());
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
    m_sprite.setScale(scale*m_ptrMap->getTailleTileLargeur(),scale*m_ptrMap->getTailleTileHauteur());
    paintEntite();
    if (antHill->m_numberWorkerBuild == -1)
    {
        m_state.reset(new StateWorkerBuild(this));
    }
    if (antHill->m_numberWorkerFarm != antHill->getSpecificStructure("Field")->getSpecificNumberTile("Mushroom")/2+1)
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
    if (getBlock(m_destination)->getResourceType() == typeResource)
    {
        if(m_cooldown < 30)
            incrCooldown();
        else
        {
            resetCooldown();
            int quantity(min(4000, m_ptrMap->getBlock(m_destination)->getQuantity()));
            setInventoryQuantity(quantity);
            setInventoryType(m_ptrMap->getBlock(m_destination)->getResourceType());
            m_ptrMap->dimQuantiteBlock(m_destination, quantity);
        }
    }
}
bool AntWorker::store()
{
    if(m_cooldown < 20)
        incrCooldown();
    else
    {
        resetCooldown();
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
    auto storage = m_antHill->getSpecificStructure("Storage")->getSpecificTile("Storage");
    if (storage.size()!=0)
    {
        for (unsigned int i = 0; i != storage.size(); i++)
        {
            if (m_ptrMap->getBlock(storage[i])->getQuantity()  < getBlock(storage[i])->getCapacity() && getInventoryType() == getBlock(storage[i])->getStorageType())
            {
                return storage[i];
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

    if (m_cooldown > 100 && getBlock(m_destination)->getCare() > 1400)
    {
        resetCooldown();
        return false;
    }
    incrCooldown();
    return (getBlock(m_destination)->addCare(1));
}
