#ifndef ANTHILL_H
#define ANTHILL_H
#include "Block.h"
#include "Entite.h"
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
        multimap<string, pair<int,int> >* getTileArray();
        void addTile(string aString, pair<int,int> coord);

        ///Set and get
        int getPopulation();
        void updateFoodCapacity();
        int getFoodCapacity();
        int getCurrentFoodStorage();

        void addAnt(pair<int,int> coord, int antType);
        void addAnt(int antType);
        void addEgg(int eggType);
        void addEgg(pair<int,int> coord, int eggType);

        /// Compteurs
        int m_numberWorkerIdle;
        int m_numberWorkerGather;
        int m_numberWorkerBuild;
        int m_numberEggs;

    protected:
        vector<unique_ptr<Entite> > m_entityArray;
        multimap<string, pair<int,int> > m_tileArray;
        TileMap* m_tileMap;
        int m_storageFoodCapacity;
        int m_storageFoodCurrent;
};

#endif // ANTHILL_H
