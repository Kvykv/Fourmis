#ifndef INCLUDECONFIG_H
#define INCLUDECONFIG_H

#include <include/rapidjson/document.h>

class Config
{
public:
    Config();

    void setConfig(rapidjson::Document& document);
    void loadConfig(const std::string& configFileName);

    /// Queen
    int m_queenHatchingTime;
    int m_queenLayingCost;
    int m_queenLayingCD;
    int m_queenSize;

    /// Air
    float m_airThermalCond;
    int m_airOrigineTemp;

    /// Dirt
    float m_dirtThermalCond;
    int m_dirtOrigineTemp;

    /// Stone
    float m_stoneThermalCond;
    int m_stoneOrigineTemp;

    /// Food
    int m_foodGrowthRate;
    int m_foodBaseQuantity;

    /// Mushroom
    int m_mushroomMaxCare;
    int m_mushroomDecayLimit;
    int m_mushroomDecayRate;
    int m_mushroomFlatGrowthRate;

};

#endif // INCLUDECONFIG_H
