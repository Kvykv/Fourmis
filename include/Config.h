#ifndef INCLUDECONFIG_H
#define INCLUDECONFIG_H

#include <include/rapidjson/document.h>

class Config
{
public:
    Config();

    void setConfig(rapidjson::Document& document);
    void loadConfig(const std::string& configFileName);

    float m_test;

    /// Queen
    int m_queenHatchingTime;
    int m_queenLayingCost;
    int m_queenLayingCD;
    int m_queenSize;

    /// Food

    int m_foodGrowthRate;

    /// Mushroom
    int m_mushroomMaxCare;
    int m_mushroomDecayLimit;
    int m_mushroomDecayRate;
    int m_mushroomFlatGrowthRate;

};

#endif // INCLUDECONFIG_H
