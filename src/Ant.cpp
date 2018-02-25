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

bool Ant::setBlock(pair<int,int> coord, int blockType, int blockValue, string structureTag)
{
    if(m_cooldown < 30)
        incrCooldown();
    else
    {
        resetCooldown();
        if(MathHelp::distance(coord, getCoord())<=2)
        {
            m_antHill->setBlock(coord, blockType, blockValue, structureTag);
            return true;
        }
        else
            goTo(coord);
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
    if (airBlocks.size() != 0)          // On s'eloigne du dernier point franchi
    {
        coord = airBlocks[rand()%(airBlocks.size())];
        for (unsigned int i=0; i<airBlocks.size(); i++)
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
    auto storage = m_antHill->getSpecificStructure("Storage")->getSpecificTile("Storage");
    if (storage.size()!=0)
    {
        for (unsigned int i = 0; i != storage.size(); i++)
        {
            if (m_ptrMap->getBlock(storage[i])->getQuantity() != 0)
            {
                return storage[i];
            }
        }
    }
    return getCoord();
}

pair<int,int> Ant::getRandomDestination()
{
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(rand()%30+15);
    while(ite < 50)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->isCrossable())
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->isCrossable())
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isCrossable())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isCrossable())
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isCrossable())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isCrossable())
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
        }
    }
    coord = Entite::getRandomDestination();
    return coord;
}


