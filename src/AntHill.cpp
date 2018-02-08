#include "include/AntHill.h"
#include "include/EntityTypesHeader/AntWorker.h"
#include "include/EntityTypesHeader/AntQueen.h"
#include "include/EntityTypesHeader/AntEgg.h"

using namespace std;

Tile::Tile(int aBlockType, pair<int,int> aCoord, int aBlockValue)
    :coord(aCoord)
    ,blockType(aBlockType)
    ,blockValue(aBlockValue)
{
}

AntHill::AntHill(){}
AntHill::AntHill(TileMap &tileMap, std::shared_ptr<Config> config)
    :m_tileMap(&tileMap)
    ,m_numberQueen(0)
    ,m_numberWorkerIdle(0)
    ,m_numberWorkerGather(0)
    ,m_numberWorkerBuild(0)
    ,m_numberWorkerFarm(0)
    ,m_numberEggs(0)
    ,m_dead(0)
    ,m_storageFoodCapacity(0)
    ,m_storageFoodCurrent(0)
    ,m_config(config)
{
    loadTextures();
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
    auto storage = m_tileArray.equal_range("Storage");
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

std::deque<Tile>* AntHill::getQueueBuild()
{
    return &m_buildQueue;
}

TileMap* AntHill::getTileMap()
{
    return m_tileMap;
}

vector<pair<int,int>> AntHill::getSpecificTile(string tag)
{
    vector<pair<int,int>> listCoord;
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> listTag = m_tileArray.equal_range(tag);
    if (listTag.first!=m_tileArray.end())
    {
        for (multimap<string, pair<int,int> >::iterator i = listTag.first; i != listTag.second; i++)
        {
            listCoord.push_back(i->second);
        }
    }
    return listCoord;
}

int AntHill::getSpecificNumberTile(string tag)
{
    return getSpecificTile(tag).size();
}

pair<int,int> AntHill::getSpecificUniqueTile(string tag)
{
    vector<pair<int,int>> tileVect(getSpecificTile(tag));
    if (tileVect.size() == 0)
        return pair<int,int>(-1,-1);
    else
        return tileVect[rand()%tileVect.size()];
}

void AntHill::setBlock(pair<int,int> coord, int blockType, int blockValue)
{
    m_tileMap->setBlock(coord, blockType, blockValue);
    if (blockType == 3 || blockType == 6 || blockType == 7)
        addTile(m_tileMap->getBlock(coord)->getTag(), coord);
}



void AntHill::addAnt(int antType)
{
    switch (antType)
    {
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

void AntHill::addBuildQueue(Tile tile)
{
    m_buildQueue.push_back(tile);
}

Tile AntHill::popBuildQueue()
{
    Tile tile = m_buildQueue.front();
    m_buildQueue.pop_front();
    return tile;
}

bool AntHill::isEmptyBuildQueue()
{
    return m_buildQueue.empty();
}



/// Textures
void AntHill::loadTextures()
{
    m_resourceHolder.load(TextureAnt, "resources/ant.png");
    m_resourceHolder.load(TextureEgg, "resources/egg.png");
}

TextureHolder* AntHill::getResourceHolder()
{
    return &m_resourceHolder;
}




