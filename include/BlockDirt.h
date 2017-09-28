    #ifndef BLOCKDIRT_H
#define BLOCKDIRT_H

#include "Block.h"
#include "BaseBlockDirt.h"

class BlockDirt : public Block
{
    public:
        BlockDirt(std::shared_ptr<BaseBlock> baseBlock);

        virtual std::string getInfo();

    protected:

    private:
};

#endif // BLOCKDIRT_H
