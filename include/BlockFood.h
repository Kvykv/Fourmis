#ifndef BLOCKFOOD_H
#define BLOCKFOOD_H
#include "Block.h"
#include <iostream>

class BlockFood : public Block
{
    public:
        BlockFood(int quantite);
        virtual void setQuantite(int quantite);
        virtual int getQuantite();
        virtual void dimQuantite(int quantite);
        virtual void addQuantite(int quantite);

    protected:
        int m_quantite;
};

#endif // BLOCKFOOD_H
