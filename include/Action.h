#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include <vector>
#include "Block.h"
#include "BlockAir.h"


class Action
{
    public:
        Action();
        Action(std::pair<int,int> coordAction, int blockType, int blockValue, int typeAction);
        bool isOver();
        void setOver(bool state);
        int getType();
        std::pair<int,int> getCoord();
        int getBlockType();
        int getBlockValue();

    protected:
        int m_blockType;
        int m_blockValue;
        std::pair<int,int> m_coord;
        int m_typeAction;
        bool m_isOver;
};

#endif // ACTION_H
