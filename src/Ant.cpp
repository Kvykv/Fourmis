#include "Ant.h"

Ant::Ant(TileMap *tileMap, AntHill *antHill)
    :Entite(tileMap)
    ,m_antHill(antHill)
{

}

Ant::Ant(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Entite(x, y, tileMap)
    ,m_antHill(antHill)
{

}
