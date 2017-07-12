#ifndef IAPROCESSACTION_H
#define IAPROCESSACTION_H

#include "Action.h"
#include "Entite.h"
#include <vector>
#include <iostream>

class Entite;

class IAProcessAction
{
    public:
        IAProcessAction();
        static bool processAction(Entite *entite, Action action);

    protected:

    private:
};

#endif // IAPROCESSACTION_H
