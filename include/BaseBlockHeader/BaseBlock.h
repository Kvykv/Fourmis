#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <string>

using namespace std;

class BaseBlock
{
    public:
        BaseBlock(int blockType = 0, string tag = "air");

        int getBlockType();
        string getTag();

    private:
        int m_blockType;
        string m_tag;
};

#endif // BASEBLOCK_H
