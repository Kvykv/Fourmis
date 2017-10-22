#ifndef BLOCKFOOD_H
#define BLOCKFOOD_H
#include "Block.h"
#include <iostream>

class BlockFood : public Block
{
    public:
        BlockFood(std::shared_ptr<BaseBlock> baseBlock, int quantite);
        virtual void setQuantity(int quantite);
        virtual int getQuantity();
        virtual bool dimQuantity(int quantite);
        virtual void addQuantity(int quantite);
        virtual int getStorageType();
        virtual std::string getInfo();

    protected:
        int m_quantity;
};

#endif // BLOCKFOOD_H
