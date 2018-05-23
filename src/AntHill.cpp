#include "include/AntHill.h"
#include "include/EntityTypesHeader/AntWorker.h"
#include "include/EntityTypesHeader/AntQueen.h"
#include "include/EntityTypesHeader/AntEgg.h"

using namespace std;

Tile::Tile(int aBlockType, pair<int,int> aCoord, int aBlockValue, std::string aStructureTag)
    :coord(aCoord)
    ,blockType(aBlockType)
    ,blockValue(aBlockValue)
    ,structureTag(aStructureTag)
{
}

AntHill::AntHill(){}
AntHill::AntHill(TileMap &tileMap, std::shared_ptr<Config> config)
    :m_numberQueen(0)
    ,m_numberWorkerIdle(0)
    ,m_numberWorkerGather(0)
    ,m_numberWorkerBuild(0)
    ,m_numberWorkerFarm(0)
    ,m_numberEggs(0)
    ,m_dead(0)
    ,m_storageFoodCapacity(0)
    ,m_storageFoodCurrent(0)
    ,m_tileMap(&tileMap)
    ,m_config(config)
{
    loadTextures();
}

void AntHill::addTile(string aStructure, string aString, pair<int,int> coord)
{
    if(m_structureArray[aStructure].getTileArray()->size()==0)
        m_structureArray[aStructure].setAntHill(this);
    m_structureArray[aStructure].addTile(aString, coord);
}

vector<unique_ptr<Entite> >* AntHill::getEntityArray()
{
    return &m_entityArray;
}

map<string, Structure>* AntHill::getStructureArray()
{
    return &m_structureArray;
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
    auto storage = m_structureArray["Storage"].getSpecificTile("Storage");
    if (storage.size() != 0)
    {
        for (unsigned int i = 0; i < storage.size(); i++)
        {
            m_storageFoodCapacity += m_tileMap->getBlock(storage[i])->getCapacity();
            m_storageFoodCurrent += m_tileMap->getBlock(storage[i])->getQuantity();
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

Structure* AntHill::getSpecificStructure(string tag)
{
    return &m_structureArray[tag];
}


void AntHill::setBlock(pair<int,int> coord, int blockType, int blockValue, string aStructureTag)
{
    m_tileMap->setBlock(coord, blockType, blockValue);
    if (blockType == 3 || blockType == 6 || blockType == 7)
        addTile(aStructureTag, m_tileMap->getBlock(coord)->getTag(), coord);
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




