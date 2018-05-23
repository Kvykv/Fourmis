#ifndef ANTQUEEN_H
#define ANTQUEEN_H

#include "include/Ant.h"
#include "include/StateHeader/StateQueen.h"

class StateQueen;
class AntQueen : public Ant
{
    public:
        AntQueen(TileMap *tileMap, AntHill *antHill);
        AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill);
        ~AntQueen();
        void setCDLaying(int par);
        void addCDLaying(int incr);
        int getCDLaying();
        void updateLaying(int incr);
        bool layEgg(int eggType);
        virtual bool nextStep();
        StateQueen* getState();
        void setState(StateQueen newState);

    protected:

    private:
        std::unique_ptr<StateQueen> m_state;
        int m_CDLaying;
};

#endif // ANTQUEEN_H
