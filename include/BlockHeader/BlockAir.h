#ifndef BLOCKAIR_H
#define BLOCKAIR_H

#include "Block.h"

class BlockAir : public Block
{
    public:
        BlockAir(std::shared_ptr<BaseBlock> baseBlock);

    protected:

    private:
};

#endif // BLOCKAIR_H
