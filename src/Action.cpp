#include "Action.h"

Action::Action()
    :m_typeAction(0)
{
}
Action::Action(pair<int,int> coordAction, Block block, int typeAction)
    :m_coord(coordAction)
    ,m_block(block)
    ,m_typeAction(typeAction)
    ,m_isOver(false)
{
}
bool Action::isOver()
{
    return m_isOver;
}
void Action::setOver(bool state)
{
    m_isOver = state;
}
int Action::getType()
{
    return m_typeAction;
}
pair<int,int> Action::getCoord()
{
    return m_coord;
}
Block Action::getBlock()
{
    return m_block;
}
