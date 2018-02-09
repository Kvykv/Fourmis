#ifndef BASEBLOCKMULTI_H
#define BASEBLOCKMULTI_H

#include <vector>
#include <array>

#include "include/BaseBlockHeader/BaseBlock.h"

class BaseBlockMulti : public BaseBlock
{
    public:
        BaseBlockMulti(int blockType, std::string tag, bool diggable, int thermalConductivity, std::shared_ptr<Config> config);
        virtual std::array<std::vector<int>,8> getStructure();

    private:
        std::array<std::vector<int>,8> m_structure;
};

#endif // BASEBLOCKMULTI_H
