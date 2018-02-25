#include "include/Config.h"
#include <include/rapidjson/error/en.h>
#include <fstream>
#include <iostream>
#include <sstream>

Config::Config()
{

}

void Config::loadConfig(const std::string& configFileName)
{
    std::stringstream ss;
    std::ifstream inputStream(configFileName);
    if(!inputStream)
    {
      throw std::runtime_error("Application::loadConfig Error - Failed to load " + configFileName);
    }
    ss << inputStream.rdbuf();
    inputStream.close();
    rapidjson::Document doc;
    rapidjson::ParseResult ok(doc.Parse(ss.str().c_str()));
    if(!ok)
    {
        std::cout << stderr << "JSON parse error: %s (%u)" << rapidjson::GetParseError_En(ok.Code()) << ok.Offset() << std::endl;
        exit(EXIT_FAILURE);
    }

    setConfig(doc);
}

void Config::setConfig(rapidjson::Document& document)
{
    /// Air
    m_airThermalCond = document["blockAir"]["thermalCond"].GetFloat();
    m_airOrigineTemp = document["blockAir"]["origineTemp"].GetInt();

    /// Dirt
    m_dirtThermalCond = document["blockDirt"]["thermalCond"].GetFloat();
    m_dirtOrigineTemp = document["blockDirt"]["origineTemp"].GetInt();

    /// Food
    m_foodGrowthRate = document["blockFood"]["growthRate"].GetInt();
    m_foodBaseQuantity = document["blockFood"]["baseQuantity"].GetInt();

    /// Mushroom
    m_mushroomMaxCare = document["blockFood"]["blockMushroom"]["maxCare"].GetInt();
    m_mushroomDecayLimit = document["blockFood"]["blockMushroom"]["decayLimit"].GetInt();
    m_mushroomDecayRate = document["blockFood"]["blockMushroom"]["decayRate"].GetInt();
    m_mushroomFlatGrowthRate = document["blockFood"]["blockMushroom"]["flatGrowthRate"].GetInt();

    /// Storage
    m_storageDefaultCapacity = document["blockStorage"]["defaultCapacity"].GetInt();

    /// Stone
    m_stoneThermalCond = document["blockStone"]["thermalCond"].GetFloat();
    m_stoneOrigineTemp = document["blockStone"]["origineTemp"].GetInt();

}


