#include "Ant.h"

using namespace std;

Ant::Ant(TileMap *tileMap, AntHill *antHill, int type)
    :Entite(tileMap, type)
    ,m_antHill(antHill)
{
}

Ant::Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type)
    :Entite(x, y, tileMap, type)
    ,m_antHill(antHill)
{

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
