#ifndef ANT_H
#define ANT_H

#include "Entite.h"

class AntHill;

class Ant : public Entite
{
    public:
        Ant(TileMap *tileMap, AntHill *antHill, int type);
        Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type);

    protected:
        AntHill *m_antHill;
    private:
};

#endif // ANT_H
