    #ifndef BLOCKDIRT_H
#define BLOCKDIRT_H

#include "Block.h"

class BlockDirt : public Block
{
    public:
        BlockDirt(std::shared_ptr<BaseBlock> baseBlock, int hardness = 1000);

        virtual std::string getInfo();

    protected:

    private:
};

#endif // BLOCKDIRT_H
