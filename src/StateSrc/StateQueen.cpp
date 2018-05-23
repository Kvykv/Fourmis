#include "include/StateHeader/StateQueen.h"

using namespace std;

StateQueen::StateQueen()
{
}

bool StateQueen::execute(AntQueen* antQueen)
{
    return false;
}

bool  StateQueen::updateState(AntQueen* AntQueen)
{
    return false;
}


/// State Queen Laying

StateQueenLaying::StateQueenLaying(AntQueen* antQueen)
{
    m_string = "laying";
}

bool StateQueenLaying::execute(AntQueen* antQueen)
{
    bool isDead(false);
    isDead = updateState(antQueen);
    while (!antQueen->hasArrived())
    {
        antQueen->oneMovement();
        return isDead;
    }
    if (!antQueen->isGoingForFood() && antQueen->getCDLaying() > 200)
    {
        antQueen->layEgg(0);
    }
    return isDead;
}

bool StateQueenLaying::updateState(AntQueen* antQueen)
{
    antQueen->falling();
    antQueen->dimHunger(1);
    antQueen->updateLaying(1);
    if (antQueen->checkFood())
    {
        return true;
    }
    if (antQueen->getHunger() < 500)
    {
        antQueen->setState(StateQueenFood(antQueen));
    }
    return false;
}

/// State Queen Food

StateQueenFood::StateQueenFood(AntQueen* antQueen)
{
    antQueen->getFood();
    m_string = "food";
}

bool StateQueenFood::execute(AntQueen* antQueen)
{
    bool isDead(false);
    isDead = updateState(antQueen);
    while (!antQueen->hasArrived())
    {
        antQueen->oneMovement();
        return isDead;
    }
    antQueen->eat();
    return isDead;
}

bool StateQueenFood::updateState(AntQueen* antQueen)
{
    antQueen->dimHunger(1);
    if (antQueen->checkFood())
    {
        return true;
    }
    if (!antQueen->isGoingForFood())
    {
        antQueen->setState(StateQueenLaying(antQueen));
    }
    return false;
}
