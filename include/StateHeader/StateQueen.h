#ifndef STATEQUEEN_H
#define STATEQUEEN_H

#include "include/StateHeader/State.h"
#include "include/EntityTypesHeader/AntQueen.h"

class AntQueen;

class StateQueen : public State
{
    public:
        StateQueen();
        virtual bool execute(AntQueen* antQueen);
        virtual bool updateState(AntQueen* AntQueen);
        std::string m_string;

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
