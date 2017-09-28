#include "BlockDirt.h"
#include <cstdlib>

using namespace std;

BlockDirt::BlockDirt(shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, false, 1000 + rand()%1000 - 500)
{
}
