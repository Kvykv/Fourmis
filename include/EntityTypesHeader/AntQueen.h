#ifndef ANTQUEEN_H
#define ANTQUEEN_H

#include "Ant.h"

class AntQueen : public Ant
{
    public:
        AntQueen(TileMap *tileMap, AntHill *antHill, vector<Entite> *antColony);
        AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill, vector<Entite> *antColony);

    protected:

    private:
       vector<Entite> *m_antColony;
};

#endif // ANTQUEEN_H
