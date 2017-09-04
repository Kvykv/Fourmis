#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include "BaseBlock.h"
#include <memory>

using namespace std;
class Block
{
    public:
        Block(shared_ptr<BaseBlock> baseBlock);
        Block(shared_ptr<BaseBlock> baseBlock , bool crossable, bool diggable, int cost);
        int getBlockType() const;
        int getCost() const;
        void setCost(int cost);
        bool isDiggable();
        bool isCrossable();
        void setCrossable(bool boolean);
        void setDiggable(bool boolean);

        // Heritage
        virtual string getTag() const;
        virtual void setQuantity(int quantite);
        virtual void dimQuantity(int quantite);
        virtual void addQuantity(int quantite);
        virtual int getQuantity();
        virtual int getTypeStorage();
        virtual int getCapacity();

    protected:
        shared_ptr<BaseBlock> m_baseBlock;
        int m_cost;
        bool m_isCrossable = false;
        bool m_isDiggable = false;

    private:
};

#endif
