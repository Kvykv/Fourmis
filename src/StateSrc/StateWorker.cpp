#include "StateWorker.h"

StateWorker::StateWorker()
{
}

bool StateWorker::execute(AntWorker* antWorker)
{
}

bool  StateWorker::updateState(AntWorker* antWorker)
{
}


void StateWorker::setNextAction(AntWorker* antWorker)
{

}


/// State Worker Idle

StateWorkerIdle::StateWorkerIdle(AntWorker* antWorker)
{
    setNextAction(antWorker);
    m_string = "idle";
}

bool StateWorkerIdle::execute(AntWorker* antWorker)
{
    bool isDead(false);
    isDead = updateState(antWorker);
    while (!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    if (!antWorker->isGoingForFood())
    {
        antWorker->setBlock(antWorker->getDestination(), 0, 0);
        setNextAction(antWorker);
    }
    return isDead;
}

bool StateWorkerIdle::updateState(AntWorker* antWorker)
{
    antWorker->dimHunger(1);
    if (antWorker->checkFood())
    {
        return true;
    }
    if (antWorker->getHunger() < 500)
    {
        antWorker->setState(StateWorkerFood(antWorker));
    }
    return false;
}

void StateWorkerIdle::setNextAction(AntWorker* antWorker)
{
    antWorker->goTo(pair<int,int>(300 + rand()%20,hauteur - 100 + rand()%5));
}




/// State Worker Food

StateWorkerFood::StateWorkerFood(AntWorker* antWorker)
{
    antWorker->getFood();
    m_string = "food";
}

bool StateWorkerFood::execute(AntWorker* antWorker)
{
    bool isDead(false);
    isDead = updateState(antWorker);
    while (!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    antWorker->eat();
    return isDead;
}

bool StateWorkerFood::updateState(AntWorker* antWorker)
{
    antWorker->dimHunger(1);
    if (antWorker->checkFood())
    {
        return true;
    }
    if (!antWorker->isGoingForFood())
    {
        antWorker->setState(StateWorkerGather(antWorker));
    }
    return false;
}



/// State Worker Gather

StateWorkerGather::StateWorkerGather(AntWorker* antWorker)
{
    setNextAction(antWorker);
    m_string = "gather";
}

bool StateWorkerGather::execute(AntWorker* antWorker)
{
    bool isDead(false);
    isDead = updateState(antWorker);
    while (!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    if (antWorker->getInventoryQuantity() != 0)
    {
        antWorker->store();
    }
    else
    {
        antWorker->gather(2);
    }
    setNextAction(antWorker);
    return isDead;
}

bool StateWorkerGather::updateState(AntWorker* antWorker)
{
    antWorker->dimHunger(1);
    if (antWorker->checkFood())
    {
        return true;
    }
    if (antWorker->getHunger() < 500)
    {
        antWorker->setState(StateWorkerFood(antWorker));
    }
    return false;
}

void StateWorkerGather::setNextAction(AntWorker* antWorker)
{
    if(antWorker->getInventoryQuantity() != 0)
    {
        antWorker->goTo(pair<int,int>(200 + 5*(rand()%4),hauteur - 100));
    }
    else
    {
        cout << antWorker->getCoordY() << "  " << antWorker->m_previousCoord.first << endl;
        antWorker->goTo(antWorker->lookFor(2));
    }
}
