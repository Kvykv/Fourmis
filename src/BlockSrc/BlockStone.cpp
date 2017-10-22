#include "include/BlockHeader/BlockStone.h"

BlockStone::BlockStone(std::shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, false, 1)
{
}
