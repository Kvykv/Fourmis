#ifndef HEADERSSTRUCTUREHEADERSTRUCTURE_H
#define HEADERSSTRUCTUREHEADERSTRUCTURE_H

#include <string>
#include <map>
#include <vector>

#include "include/AntHill.h"

class AntHill;

class Structure
{
public:
    Structure();
    Structure(std::string tag, AntHill *antHill);

    void setAntHill(AntHill *antHill);
    std::multimap<std::string, std::pair<int,int>>* getTileArray();
    std::vector<std::pair<int,int>> getSpecificTile(std::string tag);
    int getSpecificNumberTile(std::string tag);
    std::pair<int,int> getSpecificUniqueTile(std::string tag);
    void addTile(std::string aString, std::pair<int,int> coord);



private:
    std::string m_tag;
    AntHill *m_antHill;
    std::multimap<std::string, std::pair<int,int>> m_tileArray;
};

#endif // HEADERSSTRUCTUREHEADERSTRUCTURE_H
