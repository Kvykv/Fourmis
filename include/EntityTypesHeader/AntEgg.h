#ifndef ANTEGG_H
#define ANTEGG_H

#include "Ant.h"

class AntEgg : public Ant
{
    public:
        AntEgg(TileMap *tileMap, AntHill *antHill, std::string eggType);
        AntEgg(int x, int y, TileMap *tileMap, AntHill *antHill, std::string eggType);

    private:
        virtual bool nextStep();

        std::string m_eggType;
        int m_hatchingCoolDown;
};

#endif // ANTEGG_H
