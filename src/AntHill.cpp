#include "AntHill.h"

AntHill::AntHill(TileMap &tileMap)
    :m_tileMap(&tileMap)
{
}

AntHill::AntHill(){}

void AntHill::addTile(pair<int,int> coord)
{
    m_tileArray.insert(pair<string,pair<int,int> >(m_tileMap->getBlock(coord)->getString(), coord));
}

vector<unique_ptr<Entite> >* AntHill::getEntityArray()
{
    return &m_entityArray;
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
