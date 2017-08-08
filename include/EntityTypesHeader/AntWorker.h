#ifndef ANTWORKER_H
#define ANTWORKER_H

#include "Ant.h"
#include "StateWorker.h"

class AntHill;
class StateWorker;

class AntWorker : public Ant
{
    public:
        AntWorker(TileMap *tileMap, AntHill *antHill);
        AntWorker(int x, int y, TileMap *tileMap, AntHill *antHill);
        void gather(int typeResource);
        bool store();
        virtual bool nextStep();
        StateWorker* getState();
        void setState(StateWorker newState);

    protected:

    private:
        unique_ptr<StateWorker> m_state;
};

#endif // ANTWORKER_H
