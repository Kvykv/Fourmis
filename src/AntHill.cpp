#include "AntHill.h"

Tile::Tile(pair<int,int> coord, Block &block)
    :m_coord(coord)
    ,m_block(block)
{
}

AntHill::AntHill(TileMap &tileMap)
    :m_tileMap(&tileMap)
{
}

AntHill::AntHill(){}

void AntHill::addTile(pair<int,int> coord, Block& block)
{
    m_tileArray.insert(pairTile(block.getString(), Tile(coord, block)));
}
