#ifndef BLOCKSTORAGE_H
#define BLOCKSTORAGE_H
#include "Block.h"
#include "BaseBlockHeader/BaseBlockStorage.h"

class BlockStorage : public Block
{
    public:
        BlockStorage(std::shared_ptr<BaseBlock> baseBlock, int quantity, int typeStorage);
        virtual void setQuantity(int quantity);
        virtual int getQuantity();
        virtual bool dimQuantity(int quantity);
        virtual void addQuantity(int quantity);
        virtual int getStorageType();
        virtual int getCapacity();
        virtual bool isEmpty();
        virtual std::string getInfo();

    protected:
        int m_storageType;
        int m_quantity;
        const int m_capacity;

    private:
};

#endif // BLOCKSTORAGE_H
