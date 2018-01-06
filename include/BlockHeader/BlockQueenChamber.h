#ifndef BLOCKQUEENCHAMBER_H
#define BLOCKQUEENCHAMBER_H


#include "include/BlockHeader/Block.h"

class BlockQueenChamber : public Block
{
public:
    BlockQueenChamber(std::shared_ptr<BaseBlock> baseBlock);
};

#endif // BLOCKQUEENCHAMBER_H
