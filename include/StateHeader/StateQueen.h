#ifndef STATEQUEEN_H
#define STATEQUEEN_H

#include "State.h"
#include "AntQueen.h"

class AntQueen;

class StateQueen : public State
{
    public:
        StateQueen();
        virtual bool execute(AntQueen* antQueen);
        virtual bool updateState(AntQueen* AntQueen);
        string m_string;

    private:
};

class StateQueenLaying : public StateQueen
{
    public:
        StateQueenLaying(AntQueen* antQueen);
        virtual bool execute(AntQueen* antQueen);
        virtual bool updateState(AntQueen* AntQueen);
};

class StateQueenFood : public StateQueen
{
    public:
        StateQueenFood(AntQueen* antQueen);
        virtual bool execute(AntQueen* antQueen);
        virtual bool updateState(AntQueen* AntQueen);
};

#endif // STATEQUEEN_H
