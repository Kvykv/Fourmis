#ifndef ANTQUEEN_H
#define ANTQUEEN_H

#include "Ant.h"
#include "StateQueen.h"

class StateQueen;
class AntQueen : public Ant
{
    public:
        AntQueen(TileMap *tileMap, AntHill *antHill);
        AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill);
        void setCDLaying(int par);
        void addCDLaying(int incr);
        int getCDLaying();
        bool layEgg(int eggType);
        virtual bool nextStep();
        StateQueen* getState();
        void setState(StateQueen newState);

    protected:

    private:
        int m_CDLaying;
        unique_ptr<StateQueen> m_state;
};

#endif // ANTQUEEN_H
