#include "BlockDirt.h"
#include <cstdlib>

using namespace std;

BlockDirt::BlockDirt(shared_ptr<BaseBlock> baseBlock, int hardness)
    :Block(baseBlock, false, hardness)
{
}



std::string BlockDirt::getInfo()
{
    std::stringstream sstm;
    sstm << Block::getInfo() << "    Hardness : " << getCost();
    return sstm.str();
}
