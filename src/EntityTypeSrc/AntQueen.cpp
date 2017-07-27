#include "EntityTypesHeader/AntQueen.h"

AntQueen::AntQueen(TileMap *tileMap, AntHill *antHill, vector<Entite> *antColony)
    :Ant(tileMap, antHill)
    ,m_antColony(antColony)
{

}

AntQueen::AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill, vector<Entite> *antColony)
    :Ant(x, y, tileMap, antHill)
    ,m_antColony(antColony)
{

}
