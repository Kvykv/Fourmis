#include "AntHill.h"
#include "AntWorker.h"
#include "AntQueen.h"
#include "AntEgg.h"

AntHill::AntHill(){}
AntHill::AntHill(TileMap &tileMap)
    :m_tileMap(&tileMap)
    ,m_numberWorkerIdle(0)
    ,m_numberWorkerFood(0)
    ,m_numberWorkerGather(0)
    ,m_numberWorkerBuild(0)
    ,m_numberEggs(0)
{
}

void AntHill::addTile(string aString, pair<int,int> coord)
{
    m_tileArray.insert(pair<string,pair<int,int> >(aString, coord));
}

vector<unique_ptr<Entite> >* AntHill::getEntityArray()
{
    return &m_entityArray;
}

multimap<string, pair<int,int> >* AntHill::getTileArray()
{
    return &m_tileArray;
}

///Set and get

int AntHill::getPopulation()
{
    return m_entityArray.size();
}

void AntHill::updateFoodCapacity()
{
    m_storageFoodCapacity = 0;
    m_storageFoodCurrent = 0;
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> storage = m_tileArray.equal_range("storage");
    if (storage.first!=m_tileArray.end())
    {
        for (multimap<string, pair<int,int> >::iterator i = storage.first; i != storage.second; i++)
        {
            m_storageFoodCapacity += m_tileMap->getBlock(i->second)->getCapacity();
            m_storageFoodCurrent += m_tileMap->getBlock(i->second)->getQuantity();
        }
    }
}

int AntHill::getFoodCapacity()
{
    return m_storageFoodCapacity;
}
int AntHill::getCurrentFoodStorage()
{
    return m_storageFoodCurrent;
}



void AntHill::addAnt(int antType)
{
    switch (antType)
    {
    case 0 :
        {unique_ptr<Entite> ptr_Entite(new AntWorker(m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));
        break;}
    case 1 :
        {unique_ptr<Entite> ptr_Entite(new AntQueen(m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));
        break;}
    default :
        {unique_ptr<Entite> ptr_Entite(new AntWorker(m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));}
    }
}

void AntHill::addAnt(pair<int,int> coord, int antType)
{
    switch (antType)
    {
    case 0 :
        {unique_ptr<Entite> ptr_Entite(new AntWorker(coord.first, coord.second, m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));
        break;}
    case 1 :
        {unique_ptr<Entite> ptr_Entite(new AntQueen(coord.first, coord.second, m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));
        break;}
    default :
        {unique_ptr<Entite> ptr_Entite(new AntWorker(coord.first, coord.second, m_tileMap, this));
        m_entityArray.push_back(move(ptr_Entite));}
    }
}

void AntHill::addEgg(int eggType)
{
    unique_ptr<Entite> ptr_Entite(new AntEgg(m_tileMap, this, eggType));
    m_entityArray.push_back(move(ptr_Entite));
}

void AntHill::addEgg(pair<int,int> coord, int eggType)
{
    unique_ptr<Entite> ptr_Entite(new AntEgg(coord.first, coord.second, m_tileMap, this, eggType));
    m_entityArray.push_back(move(ptr_Entite));
}

