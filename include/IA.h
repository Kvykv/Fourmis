#ifndef IA_H
#define IA_H

#include "TileMap.h"
#include "AntHill.h"

class AntHillAI
{
    public:
        AntHillAI();
        AntHillAI(AntHill* antHill);

    protected:

    private:
        AntHill* m_antHill;
};

#endif // IA_H
