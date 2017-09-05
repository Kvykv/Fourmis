#ifndef BLOCKFOOD_H
#define BLOCKFOOD_H
#include "Block.h"
#include "BaseBlockFood.h"
#include <iostream>

class BlockFood : public Block
{
    public:
        BlockFood(std::shared_ptr<BaseBlock> baseBlock, int quantite);
        virtual void setQuantity(int quantite);
        virtual int getQuantity();
        virtual void dimQuantity(int quantite);
        virtual void addQuantity(int quantite);

    protected:
        int m_quantity;
};

#endif // BLOCKFOOD_H
