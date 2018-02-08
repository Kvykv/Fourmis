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
    m_test = document["test"].GetFloat();
    m_foodGrowthRate = document["blockFood"]["growthRate"].GetInt();
    m_mushroomMaxCare = document["blockFood"]["blockMushroom"]["maxCare"].GetInt();
    m_mushroomDecayLimit = document["blockFood"]["blockMushroom"]["decayLimit"].GetInt();
    m_mushroomDecayRate = document["blockFood"]["blockMushroom"]["decayRate"].GetInt();
    m_mushroomFlatGrowthRate = document["blockFood"]["blockMushroom"]["flatGrowthRate"].GetInt();
}


