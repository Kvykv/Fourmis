#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include "include/BaseBlockHeader/BaseBlock.h"
#include <memory>
#include <sstream>

class Block
{
    public:
        Block(std::shared_ptr<BaseBlock> baseBlock);
        Block(std::shared_ptr<BaseBlock> baseBlock , bool crossable, int cost);
        int getBlockType() const;
        int getCost() const;
        void setCost(int cost);
        bool isDiggable();
        bool isCrossable();
        void setCrossable(bool boolean);

        // Heritage
        virtual std::string getTag() const;
        virtual void setQuantity(int quantite);
        virtual bool dimQuantity(int quantite);
        virtual void addQuantity(int quantite);
        virtual int getQuantity();
        virtual int getStorageType();
        virtual int getCapacity();
        virtual bool isEmpty();
        virtual std::string getInfo();
        virtual void update();

    protected:
        std::shared_ptr<BaseBlock> m_baseBlock;
        int m_cost;
        bool m_isCrossable = false;

    private:
};

#endif
