#ifndef BLOCKSTORAGE_H
#define BLOCKSTORAGE_H
#include "Block.h"
#include "BaseBlockStorage.h"

class BlockStorage : public Block
{
    public:
        BlockStorage(shared_ptr<BaseBlock> baseBlock, int quantite, int valueStorage);
        virtual void setQuantite(int quantite);
        virtual int getQuantite();
        virtual void dimQuantite(int quantite);
        virtual void addQuantite(int quantite);
        virtual int getTypeStorage();
        virtual int getCapacity();

    protected:
        int m_typeStorage;
        int m_quantite;
        const int m_capacity;

    private:
};

#endif // BLOCKSTORAGE_H
