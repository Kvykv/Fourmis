#ifndef ANTHILL_H
#define ANTHILL_H
#include "BlockHeader/Block.h"
#include "Entite.h"
#include <map>
#include <memory>
#include <string>
#include <deque>
#include "ResourceHolder.h"
#include "Config.h"
#include "StructureHeader/Structure.h"

struct Tile
{
public :
    Tile(int aBlockType, std::pair<int,int> aCoord, int aBlockValue = 0, std::string aStructureTag = "");
    std::pair<int,int> coord;
    int blockType;
    int blockValue;
    std::string structureTag;
};

class AntHillAI;
class Structure;

class AntHill
{
    public:
        using TileArray = std::multimap<std::string, std::pair<int,int>>;

    public:
        AntHill();
        AntHill(TileMap &tileMap, std::shared_ptr<Config> config);
        std::vector<std::unique_ptr<Entite> >* getEntityArray();
        std::map<std::string, Structure>* getStructureArray();
        void addTile(std::string aStructure, std::string aString, std::pair<int,int> coord);

        ///Set and get
        int getPopulation();
        void updateFoodCapacity();
        int getFoodCapacity();
        int getCurrentFoodStorage();
        TileMap* getTileMap();
        Structure* getSpecificStructure(std::string tag);
        std::deque<Tile>* getQueueBuild();
        void setBlock(std::pair<int,int> coord, int blockType, int blockValue = 0, std::string aStructureTag = "");

        void addAnt(std::pair<int,int> coord, int antType);
        void addAnt(int antType);
        void addEgg(int eggType);
        void addEgg(std::pair<int,int> coord, int eggType);
        void addBuildQueue(Tile tile);
        Tile popBuildQueue();
        bool isEmptyBuildQueue();

        /// Compteurs
        int m_numberQueen;
        int m_numberWorkerIdle;
        int m_numberWorkerGather;
        int m_numberWorkerBuild;
        int m_numberWorkerFarm;
        int m_numberEggs;
        int m_dead;

        /// Textures
        void loadTextures();
        TextureHolder* getResourceHolder();

    protected:
        std::vector<Entite::Ptr> m_entityArray;
        std::map<std::string, Structure> m_structureArray;
        TileMap* m_tileMap;
        int m_storageFoodCapacity;
        int m_storageFoodCurrent;
        std::deque<Tile> m_buildQueue;
        TextureHolder m_resourceHolder;
        std::shared_ptr<Config> m_config;
};

#endif // ANTHILL_H
