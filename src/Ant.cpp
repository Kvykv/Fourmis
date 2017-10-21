#include "include/Ant.h"

using namespace std;

Ant::Ant(TileMap *tileMap, AntHill *antHill, int type)
    :Entite(tileMap, type)
    ,m_antHill(antHill)
{
    m_sprite.setTexture(m_antHill->getResourceHolder()->get(TextureAnt));
}

Ant::Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type)
    :Entite(x, y, tileMap, type)
    ,m_antHill(antHill)
{
    m_sprite.setTexture(m_antHill->getResourceHolder()->get(TextureAnt));
}

AntHill* Ant::getAntHill()
{
    return m_antHill;
}

bool Ant::setBlock(pair<int,int> coord, int blockType, int blockValue)
{
    if(MathHelp::distance(coord, getCoord())<=2)
    {
        m_ptrMap->setBlock(coord, blockType, blockValue);
        if (blockType == 3)
        {
            m_antHill->addTile(m_ptrMap->getBlock(coord)->getTag(), coord);
        }
        return true;
    }
    return false;
}


pair<int,int> Ant::lookForFood(int typeBlock)
{
    if (m_ptrMap->getBlock(getCoord())->getBlockType() == 5 && m_antHill->getCurrentFoodStorage() != 0)
    {
        return getNotEmptyStorage();
    }
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(0);
    vector<pair<int,int> > airBlocks;
    while(ite < 40)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->getStorageType() == typeBlock && !m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->isEmpty())
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->getStorageType() == typeBlock && !m_ptrMap->getBlock(x, max(0, y - ite))->isEmpty())
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isEmpty())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isEmpty())
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isEmpty())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isEmpty())
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            if (ite > 37)              //Sinon : scan air et crossable et choix au hasard
            {
                if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
            }
        }
    }
    if (airBlocks.size() != 0)          // On s'éloigne du dernier point franchi
    {
        coord = airBlocks[rand()%(airBlocks.size())];
        for (int i=0; i<airBlocks.size(); i++)
        {
            if (MathHelp::distancePath(airBlocks[i], m_previousCoord) > MathHelp::distancePath(coord, m_previousCoord))
            {
                coord = airBlocks[i];
            }
        }
    }
    m_previousCoord = getCoord();
    return coord;
}


pair<int,int> Ant::getNotEmptyStorage()
{
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> storage = m_antHill->getTileArray()->equal_range("Storage");
    if (storage.first!=m_antHill->getTileArray()->end())
    {
        for (multimap<string, pair<int,int> >::iterator i = storage.first; i != storage.second; i++)
        {
            if (m_ptrMap->getBlock(i->second)->getQuantity() != 0)
            {
                return i->second;
            }
        }
    }
    return getCoord();
}
