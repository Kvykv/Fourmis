#ifndef ANTHILL_H
#define ANTHILL_H
#include "Block.h"
#include "Entite.h"
#include <map>
#include <memory>
#include <string>
#include <queue>

struct Tile
{
public :
    Tile(int aBlockType, std::pair<int,int> aCoord, int aBlockValue = 0);
    std::pair<int,int> coord;
    int blockType;
    int blockValue;
};

class AntHillAI;

class AntHill
{
    public:
        AntHill();
        AntHill(TileMap &tileMap);
        std::vector<std::unique_ptr<Entite> >* getEntityArray();
        std::multimap<std::string, std::pair<int,int> >* getTileArray();
        void addTile(std::string aString, std::pair<int,int> coord);

        ///Set and get
        int getPopulation();
        void updateFoodCapacity();
        int getFoodCapacity();
        int getCurrentFoodStorage();
        std::queue<Tile>* getQueueBuild();

        void addAnt(std::pair<int,int> coord, int antType);
        void addAnt(int antType);
        void addEgg(int eggType);
        void addEgg(std::pair<int,int> coord, int eggType);
        void addBuildQueue(Tile tile);
        Tile popBuildQueue();
        bool isEmptyBuildQueue();

        /// Compteurs
        int m_numberWorkerIdle;
        int m_numberWorkerGather;
        int m_numberWorkerBuild;
        int m_numberEggs;

    protected:
        std::vector<std::unique_ptr<Entite>> m_entityArray;
        std::multimap<std::string, std::pair<int,int>> m_tileArray;
        TileMap* m_tileMap;
        int m_storageFoodCapacity;
        int m_storageFoodCurrent;
        std::queue<Tile> m_buildQueue;
};

#endif // ANTHILL_H
