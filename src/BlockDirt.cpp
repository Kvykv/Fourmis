#include "BlockDirt.h"
#include <cstdlib>

BlockDirt::BlockDirt(shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, false, true, 1000 + rand()%1000 - 500)
{
}
