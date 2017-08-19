#ifndef BLOCK_H
#define BLOCK_H
#include <string>

using namespace std;
class Block
{
    public:
        Block();
        Block(int n, bool crossable, bool diggable, int cost);
        int getBlockType() const;
        void setBlockType(int n);
        int getCost() const;
        void setCost(int cost);
        bool isDiggable();
        bool isCrossable();
        void setCrossable(bool boolean);
        void setDiggable(bool boolean);

        // Heritage
        virtual string getString() const;
        virtual void setQuantity(int quantite);
        virtual void dimQuantity(int quantite);
        virtual void addQuantity(int quantite);
        virtual int getQuantity();
        virtual int getTypeStorage();
        virtual int getCapacity();

    protected:
        int m_blockType;
        int m_cost;
        bool m_isCrossable = false;
        bool m_isDiggable = false;
        string m_tag;

    private:
};

#endif
