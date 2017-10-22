#ifndef BLOCKSTONE_H
#define BLOCKSTONE_H

#include "include/Block.h"
#include "include/BaseBlockHeader/BaseBlockStone.h"

class BlockStone : public Block
{
    public:
        BlockStone(std::shared_ptr<BaseBlock> baseBlock);

    protected:

    private:
};

#endif // BLOCKSTONE_H
