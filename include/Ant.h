#ifndef ANT_H
#define ANT_H

#include "Entite.h"
#include "AntHill.h"
#include "ResourceHolder.h"

class Ant : public Entite
{
    public:
        Ant(TileMap *tileMap, AntHill *antHill, int type);
        Ant(int x, int y, TileMap *tileMap, AntHill *antHill, int type);
        virtual bool setBlock(std::pair<int,int> coord, int blockType, int blockValue = 0, std::string structureTag = "");
        virtual std::pair<int,int> lookForFood(int typeBlock);
        std::pair<int,int> getNotEmptyStorage();
        AntHill* getAntHill();
        std::pair<int,int> getRandomDestination();

    protected:
        AntHill *m_antHill;
    private:
};

#endif // ANT_H
