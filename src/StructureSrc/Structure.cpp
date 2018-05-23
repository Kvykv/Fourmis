#include "include/StructureHeader/Structure.h"

using namespace std;

Structure::Structure(){}

Structure::Structure(string tag, AntHill *antHill)
    :m_tag(tag)
    ,m_antHill(antHill)
{
}

void Structure::setAntHill(AntHill *antHill)
{
    m_antHill = antHill;
}


std::multimap<std::string, std::pair<int,int>>* Structure::getTileArray()
{
    return &m_tileArray;
}


void Structure::addTile(string aString, pair<int,int> coord)
{
    m_tileArray.insert(pair<string,pair<int,int> >(aString, coord));
}

vector<pair<int,int>> Structure::getSpecificTile(string tag)
{
    vector<pair<int,int>> listCoord;
    pair<multimap<string, pair<int,int> >::iterator, multimap<string, pair<int,int> >::iterator> listTag = m_tileArray.equal_range(tag);
    if (listTag.first!=m_tileArray.end())
    {
        for (multimap<string, pair<int,int> >::iterator i = listTag.first; i != listTag.second; i++)
        {
            listCoord.push_back(i->second);
        }
    }
    return listCoord;
}

int Structure::getSpecificNumberTile(string tag)
{
    return getSpecificTile(tag).size();
}

pair<int,int> Structure::getSpecificUniqueTile(string tag)
{
    vector<pair<int,int>> tileVect(getSpecificTile(tag));
    if (tileVect.size() == 0)
        return pair<int,int>(-1,-1);
    else
        return tileVect[rand()%tileVect.size()];
}

