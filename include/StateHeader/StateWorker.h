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
        std::string m_string;
};

class StateWorkerIdle : public StateWorker
{
    public:
        StateWorkerIdle(AntWorker* antWorker);
        ~StateWorkerIdle();
        virtual bool execute(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
};


class StateWorkerGather : public StateWorker
{
    public:
        StateWorkerGather(AntWorker* antWorker);
        ~StateWorkerGather();
        virtual bool execute(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
};

class StateWorkerBuild : public StateWorker
{
    public:
        StateWorkerBuild(AntWorker* antWorker);
        ~StateWorkerBuild();
        virtual bool execute(AntWorker* antWorker);
        virtual void setNextAction(AntWorker* antWorker);
        bool build(AntWorker* antWorker);
        void setBuildOrder(Tile tile);

    protected:
        Tile m_buildOrder;
};

#endif // STATEWORKER_H
