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
        Block(std::shared_ptr<BaseBlock> baseBlock , bool crossable, int cost, int temperature = 0);
        int getBlockType() const;
        int getCost() const;
        void setCost(int cost);
        bool isDiggable();
        bool isCrossable();
        bool isSupport();
        void setCrossable(bool boolean);
        float getThermalCond();
        int getTemperature();
        void setTemperature(int temperature);


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
        virtual void update(int i);
        virtual int getCare();
        virtual bool addCare(int care);

    protected:
        std::shared_ptr<BaseBlock> m_baseBlock;
        int m_cost;
        int m_temperature;
        bool m_isCrossable = false;

    private:
};

#endif
