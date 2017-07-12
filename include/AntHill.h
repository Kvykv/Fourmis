#ifndef ANTHILL_H
#define ANTHILL_H
#include "Block.h"
#include "TileMap.h"
#include <map>
#include <memory>
#include <string>

using namespace std;

struct Tile
{
    pair<int,int> m_coord;
    Block m_block;
    Tile(pair<int,int> coord, Block &block);
};
typedef pair<string, Tile> pairTile;

class Entite;

class AntHill
{
    public:
        AntHill();
        AntHill(TileMap &tileMap);
        void addTile(pair<int,int> coord, Block &block);

    protected:
        TileMap* m_tileMap;
        multimap<string, Tile> m_tileArray;
};

#endif // ANTHILL_H
