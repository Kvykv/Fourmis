#ifndef ANT_H
#define ANT_H

#include "AntHill.h"
#include "Entite.h"

class Ant : public Entite
{
    public:
        Ant(TileMap *tileMap, AntHill *antHill);
        Ant(int x, int y, TileMap *tileMap, AntHill *antHill);

    protected:

    private:
        AntHill *m_antHill;
};

#endif // ANT_H
