#include "include/BlockHeader/BlockGallery.h"

BlockGallery::BlockGallery(std::shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, true, 1)
{
}
