#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <string>


class BaseBlock
{
    public:
        BaseBlock(int blockType = 0, std::string tag = "air", bool diggable = false);

        int getBlockType();
        std::string getTag();
        bool isDiggable();

    private:
        int m_blockType;
        std::string m_tag;
        bool m_diggable;
};

#endif // BASEBLOCK_H
