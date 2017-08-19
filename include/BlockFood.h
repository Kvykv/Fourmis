#ifndef BLOCKFOOD_H
#define BLOCKFOOD_H
#include "Block.h"
#include <iostream>

class BlockFood : public Block
{
    public:
        BlockFood(int quantite);
        virtual void setQuantity(int quantite);
        virtual int getQuantity();
        virtual void dimQuantity(int quantite);
        virtual void addQuantity(int quantite);

    protected:
        int m_quantity;
};

#endif // BLOCKFOOD_H
