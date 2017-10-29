#ifndef BASEBLOCKMULTI_H
#define BASEBLOCKMULTI_H

#include <vector>
#include <array>

#include "include/BaseBlockHeader/BaseBlock.h"

class BaseBlockMulti : public BaseBlock
{
    public:
        BaseBlockMulti(int blockType = 0, std::string tag = "air", bool diggable = false);
        virtual std::array<std::vector<int>,8> getStructure();

    private:
        std::array<std::vector<int>,8> m_structure;
};

#endif // BASEBLOCKMULTI_H
