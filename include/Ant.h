#ifndef ANT_H
#define ANT_H

#include "Entite.h"
#include "AntHill.h"

class Ant : public Entite
{
    public:
        Ant(TileMap *tileMap, AntHill *antHill, int type);
        Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type);
        virtual bool setBlock(std::pair<int,int> coord, int blockType, int blockValue = 0);
        AntHill* getAntHill();

    protected:
        AntHill *m_antHill;
    private:
};

#endif // ANT_H
