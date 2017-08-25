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
    antWorker->getAntHill()->m_numberWorkerIdle +=1;
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
    }
    else
    {
        antWorker->eat();
    }
    setNextAction(antWorker);
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
        antWorker->getFood();
    }
    return false;
}

void StateWorkerIdle::setNextAction(AntWorker* antWorker)
{
    antWorker->goTo(antWorker->getRandomDestination());
}


/// State Worker Gather

StateWorkerGather::StateWorkerGather(AntWorker* antWorker)
{
    setNextAction(antWorker);
    m_string = "gather";
    antWorker->getAntHill()->m_numberWorkerGather +=1;
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
    if (antWorker->isGoingForFood())
    {
        antWorker->eat();
    }
    else
    {
        if (antWorker->getInventoryQuantity() != 0)
        {
            antWorker->store();
        }
        else
        {
            antWorker->gather(2);
        }
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
        antWorker->getFood();
    }
    return false;
}

void StateWorkerGather::setNextAction(AntWorker* antWorker)
{
    if(antWorker->getInventoryQuantity() != 0)
    {
        antWorker->goTo(antWorker->getNotFullStorage());
    }
    else
    {
        antWorker->goTo(antWorker->lookFor(2));
    }
}


/// State Worker Build

StateWorkerBuild::StateWorkerBuild(AntWorker* antWorker)
{
    setNextAction(antWorker);
    m_string = "build";
    antWorker->getAntHill()->m_numberWorkerBuild +=1;
}

bool StateWorkerBuild::execute(AntWorker* antWorker)
{
    bool isDead(false);
    isDead = updateState(antWorker);
    while (!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    if (antWorker->isGoingForFood())
    {
        antWorker->eat();
    }
    else
    {

    }
    setNextAction(antWorker);
    return isDead;
}

bool StateWorkerBuild::updateState(AntWorker* antWorker)
{
    antWorker->dimHunger(1);
    if (antWorker->checkFood())
    {
        return true;
    }
    if (antWorker->getHunger() < 500)
    {
        antWorker->getFood();
    }
    return false;
}

void StateWorkerBuild::setNextAction(AntWorker* antWorker)
{

}
