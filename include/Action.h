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
        Action(pair<int,int> coordAction, int blockType, int blockValue, int typeAction);
        bool isOver();
        void setOver(bool state);
        int getType();
        pair<int,int> getCoord();
        int getBlockType();
        int getBlockValue();

    protected:
        int m_blockType;
        int m_blockValue;
        pair<int,int> m_coord;
        int m_typeAction;
        bool m_isOver;
};

#endif // ACTION_H
