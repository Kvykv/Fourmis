#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <string>
#include <array>
#include <vector>


class BaseBlock
{
    public:
        BaseBlock(int blockType = 0, std::string tag = "air", bool diggable = false);

        int getBlockType();
        std::string getTag();
        bool isDiggable();
        bool isSupport();


        virtual std::array<std::vector<int>,8> getStructure();
    private:
        int m_blockType;
        std::string m_tag;
        bool m_diggable;
};

#endif // BASEBLOCK_H
