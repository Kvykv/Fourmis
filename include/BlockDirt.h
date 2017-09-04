    #ifndef BLOCKDIRT_H
#define BLOCKDIRT_H

#include "Block.h"
#include "BaseBlockDirt.h"

class BlockDirt : public Block
{
    public:
        BlockDirt(shared_ptr<BaseBlock> baseBlock);

    protected:

    private:
};

#endif // BLOCKDIRT_H
