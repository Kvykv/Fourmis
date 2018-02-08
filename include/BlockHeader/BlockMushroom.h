#ifndef INCLUDEBLOCKHEADERLOCKMUSHROOM_H
#define INCLUDEBLOCKHEADERLOCKMUSHROOM_H

#include "BlockFood.h"

class BlockMushroom : public BlockFood
{
public:
    BlockMushroom(std::shared_ptr<BaseBlock> baseBlock, int quantite = 0, int care = 1000);
    virtual void update(int i);
    virtual int getCare();
    virtual bool addCare(int care);
    virtual int getStorageType();
    virtual std::string getInfo();
    virtual bool isEmpty();
    std::shared_ptr<Config> getConfig();


private:
    int m_care;

};

#endif // INCLUDEBLOCKHEADERLOCKMUSHROOM_H
