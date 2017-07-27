#ifndef ANTHILL_H
#define ANTHILL_H
#include "Block.h"
#include "TileMap.h"
#include "Entite.h"
#include "AntWorker.h"
#include "AntQueen.h"
#include "AntEgg.h"
#include <map>
#include <memory>
#include <string>

using namespace std;


class AntHill
{
    public:
        AntHill();
        AntHill(TileMap &tileMap);
        vector<unique_ptr<Entite> >* getEntityArray();
        void addTile(pair<int,int> coord);
        void addAnt(int typeAnt = 0);
        void addAnt(pair<int,int> coord, int typeAnt = 0);
        void addEgg(int typeEgg = 0);
        void addEgg(pair<int,int> coord, int typeEgg = 0);

    protected:
        TileMap* m_tileMap;
        vector<unique_ptr<Entite> > m_entityArray;
        multimap<string, pair<int,int> > m_tileArray;
};

#endif // ANTHILL_H
