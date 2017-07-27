#include "EntityTypesHeader/AntEgg.h"

AntEgg::AntEgg(TileMap *tileMap, AntHill *antHill, std::string eggType)
    :Ant(tileMap, antHill)
    ,m_eggType(eggType)
{

}

AntEgg::AntEgg(int x, int y, TileMap *tileMap, AntHill *antHill, std::string eggType)
    :Ant(x, y, tileMap, antHill)
    ,m_eggType(eggType)
{

}


/*virtual bool nextStep()
{

}*/
