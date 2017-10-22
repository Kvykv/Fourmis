#ifndef ANTWORKER_H
#define ANTWORKER_H

#include <memory>

#include "include/Ant.h"
#include "include/StateHeader/StateWorker.h"

class StateWorker;
class AntWorker : public Ant
{
    public:
        AntWorker(TileMap *tileMap, AntHill *antHill);
        AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill);
        ~AntWorker();
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
