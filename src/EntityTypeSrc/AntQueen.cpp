#include "EntityTypesHeader/AntQueen.h"

AntQueen::AntQueen(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 1)
{
    m_shape.setRadius(2*tailleTileLargeur);
    paintEntite();
    m_shape.setFillColor(sf::Color::Red);
    setNextAction();
}

AntQueen::AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 1)
{
    m_shape.setRadius(2*tailleTileLargeur);
    paintEntite();
    m_shape.setFillColor(sf::Color::Red);
    setNextAction();
}
