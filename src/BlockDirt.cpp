#include "BlockDirt.h"
#include <cstdlib>

BlockDirt::BlockDirt()
    :Block(1, false, true, 1000+rand()%1000 - 500)
{
    m_tag ="Dirt";
}
