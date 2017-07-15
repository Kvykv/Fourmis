#ifndef ANTWORKER_H
#define ANTWORKER_H

#include "Ant.h"

class AntWorker : public Ant
{
    public:
        AntWorker(TileMap *tileMap, AntHill *antHill);
        AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill);
        void gather(Block* block);
        void store(Block* block);
    protected:

    private:
};

#endif // ANTWORKER_H
