#ifndef ANT_H
#define ANT_H

#include "Entite.h"
#include "AntHill.h"

class Ant : public Entite
{
    public:
        Ant(TileMap *tileMap, AntHill *antHill, int type);
        Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type);
        virtual void setBlock(pair<int,int> coord, int blockType, int blockValue);
        AntHill* getAntHill();

    protected:
        AntHill *m_antHill;
    private:
};

#endif // ANT_H
