#include "include/BlockHeader/BlockAir.h"

using namespace std;

BlockAir::BlockAir(shared_ptr<BaseBlock> baseBlock)
    :Block(baseBlock, false, 1)
{
}
