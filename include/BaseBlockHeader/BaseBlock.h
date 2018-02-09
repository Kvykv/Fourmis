#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <include/Config.h>
#include <string>
#include <array>
#include <vector>
#include <memory>


class BaseBlock
{
    public:
        BaseBlock(int blockType, std::string tag, bool diggable, float thermalConductivity, std::shared_ptr<Config> config);

        int getBlockType();
        std::string getTag();
        float getThermalCond();
        bool isDiggable();
        bool isSupport();
        std::shared_ptr<Config> getConfig();


        virtual std::array<std::vector<int>,8> getStructure();


    private:
        int m_blockType;
        std::string m_tag;
        bool m_diggable;
        float m_thermalConductivity;
        std::shared_ptr<Config> m_config;
};

#endif // BASEBLOCK_H
