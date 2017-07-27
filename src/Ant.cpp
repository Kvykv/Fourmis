#include "Ant.h"

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
