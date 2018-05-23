#include "include/StateHeader/StateWorker.h"

using namespace std;

StateWorker::StateWorker()
{
}

bool StateWorker::execute(AntWorker* antWorker)
{
    return false;
}

bool StateWorker::updateState(AntWorker* antWorker)
{
    antWorker->falling();
    antWorker->dimHunger(1);
    if (antWorker->checkFood())
    {
        return true;
    }
    if (antWorker->getHunger() < 500 && !antWorker->isGoingForFood())
    {
        antWorker->getFood();
    }
    return false;
}

void StateWorker::setNextAction(AntWorker* antWorker){}

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
    if(!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    if (!antWorker->isGoingForFood())
    {
        setNextAction(antWorker);
    }
    else
    {
        antWorker->eat();
    }
    return isDead;
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
        antWorker->eat();
    else
    {
        if (antWorker->getInventoryQuantity() != 0)
            antWorker->store();
        else
            antWorker->gather(2);
        if (antWorker->getCooldown() == 0)
            setNextAction(antWorker);
    }
    return isDead;
}


void StateWorkerGather::setNextAction(AntWorker* antWorker)
{
    if(antWorker->getInventoryQuantity() != 0)
        antWorker->goTo(antWorker->getNotFullStorage());
    else
        antWorker->goTo(antWorker->lookFor(2));
}


/// State Worker Build

StateWorkerBuild::StateWorkerBuild(AntWorker* antWorker)
    :m_buildOrder(0, antWorker->getCoord())
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
        antWorker->eat();
    else
    {
        bool success(build(antWorker));
        if (success)
            setNextAction(antWorker);
    }
    return isDead;
}

bool StateWorkerBuild::build(AntWorker* antWorker)
{
    if (m_buildOrder.blockType == -1)
        return true;
    else
        return antWorker->setBlock(m_buildOrder.coord, m_buildOrder.blockType, m_buildOrder.blockValue, m_buildOrder.structureTag);
}

void StateWorkerBuild::setNextAction(AntWorker* antWorker)
{
    setBuildOrder(antWorker->popBuildQueue());
    antWorker->goTo(m_buildOrder.coord);
}

void StateWorkerBuild::setBuildOrder(Tile tile)
{
    m_buildOrder = tile;
}

/// State Worker Farmer

StateWorkerFarm::StateWorkerFarm(AntWorker* antWorker)
{
    setNextAction(antWorker);
    m_string = "farm";
    antWorker->getAntHill()->m_numberWorkerFarm +=1;
}

bool StateWorkerFarm::execute(AntWorker* antWorker)
{
    bool isDead(false);
    isDead = updateState(antWorker);
    while (!antWorker->hasArrived())
    {
        antWorker->oneMovement();
        return isDead;
    }
    if (antWorker->isGoingForFood())
        antWorker->eat();
    else
    {
        if(!antWorker->farm())
            setNextAction(antWorker);
    }
    return isDead;
}

void StateWorkerFarm::setNextAction(AntWorker* antWorker)
{
    antWorker->goTo(antWorker->getAntHill()->getSpecificStructure("Field")->getSpecificUniqueTile("Mushroom"));
}



