#ifndef ANTWORKER_H
#define ANTWORKER_H

#include "Ant.h"
#include <memory>
#include "StateWorker.h"

class StateWorker;
class AntWorker : public Ant
{
    public:
        AntWorker(TileMap *tileMap, AntHill *antHill);
        AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill);
        void gather(int typeResource);
        bool store();
        std::pair<int,int> getNotFullStorage();
        virtual bool nextStep();
        StateWorker* getState();
        void setState(StateWorker newState);
        Tile popBuildQueue();

    protected:

    private:
        std::unique_ptr<StateWorker> m_state;
};

#endif // ANTWORKER_H
