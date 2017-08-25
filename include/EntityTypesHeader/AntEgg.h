#ifndef ANTEGG_H
#define ANTEGG_H

#include "Ant.h"

class AntEgg : public Ant
{
    public:
        AntEgg(TileMap *tileMap, AntHill *antHill, int eggType);
        AntEgg(int x, int y, TileMap *tileMap, AntHill *antHill, int eggType);

    private:
        virtual bool nextStep();
        virtual void setNextAction();

        int m_eggType;
        int m_hatchingCoolDown;
};

#endif // ANTEGG_H
