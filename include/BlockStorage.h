#ifndef BLOCKSTORAGE_H
#define BLOCKSTORAGE_H
#include "Block.h"

class BlockStorage : public Block
{
    public:
        BlockStorage(int quantite, int valueStorage);
        virtual void setQuantite(int quantite);
        virtual int getQuantite();
        virtual void dimQuantite(int quantite);
        virtual void addQuantite(int quantite);
        virtual int getValueStorage();

    protected:
        int m_valueStorage;
        int m_quantite;

    private:
};

#endif // BLOCKSTORAGE_H
