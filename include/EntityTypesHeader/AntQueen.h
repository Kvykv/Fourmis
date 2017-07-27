#ifndef ANTQUEEN_H
#define ANTQUEEN_H

#include "Ant.h"

class AntHill;
class AntQueen : public Ant
{
    public:
        AntQueen(TileMap *tileMap, AntHill *antHill);
        AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill);

    protected:

    private:
};

#endif // ANTQUEEN_H
