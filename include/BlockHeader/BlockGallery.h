#ifndef BLOCKGALLERY_H
#define BLOCKGALLERY_H

#include "Block.h"
#include "BaseBlockGallery.h"

class BlockGallery : public Block
{
    public:
        BlockGallery(std::shared_ptr<BaseBlock> baseBlock);

    protected:

    private:
};

#endif // BLOCKGALLERY_H
