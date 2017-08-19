#ifndef STATEWORKER_H
#define STATEWORKER_H

#include "State.h"
#include "AntWorker.h"

class AntWorker;

class StateWorker : public State
{
    public:
        StateWorker();
        virtual bool execute(AntWorker* antWorker);
        virtual bool updateState(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
        string m_string;
};

class StateWorkerIdle : public StateWorker
{
    public:
        StateWorkerIdle(AntWorker* antWorker);
        virtual bool execute(AntWorker* antWorker);
        virtual bool updateState(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
};

class StateWorkerFood : public StateWorker
{
    public:
        StateWorkerFood(AntWorker* antWorker);
        virtual bool execute(AntWorker* antWorker);
        virtual bool updateState(AntWorker* antWorker);
};

class StateWorkerGather : public StateWorker
{
    public:
        StateWorkerGather(AntWorker* antWorker);
        virtual bool execute(AntWorker* antWorker);
        virtual bool updateState(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
};

class StateWorkerBuild : public StateWorker
{
    public:
        StateWorkerBuild(AntWorker* antWorker);
        virtual bool execute(AntWorker* antWorker);
        virtual bool updateState(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
};

#endif // STATEWORKER_H
