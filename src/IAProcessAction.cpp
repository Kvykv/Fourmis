#include "IAProcessAction.h"

IAProcessAction::IAProcessAction()
{
}

bool IAProcessAction::processAction(Entite *entite, Action action)
{
    int typeAction(action.getType());
    switch (typeAction)
    {
    case 0 :
        break;
    case 1 :
        entite->setBlock(action.getCoord(), action.getPtrBlock());
        break;
    case 2 :
        entite->setBlock(action.getCoord(), action.getPtrBlock());
        entite->setGoingForFood(false);
        entite->setAction(entite->getMemoryAction());
        entite->setHasArrived(false);
        break;
    }
    entite->setNextAction();
    return true;
}
