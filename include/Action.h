#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <vector>
#include "Block.h"
#include "BlockAir.h"

using namespace std;

class Action
{
    public:
        Action();
        Action(pair<int,int> coordAction, Block block, int typeAction);
        bool isOver();
        void setOver(bool state);
        int getType();
        pair<int,int> getCoord();
        Block getBlock();

    protected:
        Block m_block;
        pair<int,int> m_coord;
        int m_typeAction;
        bool m_isOver;
};

#endif // ACTION_H
