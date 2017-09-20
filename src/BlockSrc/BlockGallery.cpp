#include "BlockGallery.h"

BlockGallery::BlockGallery(std::shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, true, 1)
{
}
