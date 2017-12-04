#include "include/IA.h"

using namespace std;

AntHillAI::AntHillAI(){}

AntHillAI::AntHillAI(AntHill* antHill)
    :m_antHill(antHill)
    ,m_tileMap(antHill->getTileMap())
{
    addBlock(Tile(6, pair<int,int>(300,350)));
    addBlock(Tile(3, pair<int,int>(280,340), 2));
    addBlock(Tile(7, pair<int,int>(360, 320)));
}

void AntHillAI::update()
{
    double rate(double(m_antHill->getCurrentFoodStorage())/double(m_antHill->getFoodCapacity()+1));
    if (rate > 0.8)
    {
        expandStorage();
    }
}

void AntHillAI::expandStorage()
{
    vector<pair<int,int>> listCoord(m_antHill->getSpecificTile("Storage"));
    vector<pair<int,int>> listNeighbours(m_antHill->getTileMap()->getNeighbours(listCoord[rand()%listCoord.size()]));
    int inc(rand()%listNeighbours.size());
    for (int i = inc; i < listNeighbours.size() + inc; i++)
    {
        if (m_antHill->getTileMap()->getBlock(listNeighbours[i%(listNeighbours.size())])->getBlockType() <= 1)
        {
            addBlock(Tile(3, listNeighbours[i%(listNeighbours.size())], 2));
        }
    }
}

std::array<std::vector<int>,8> AntHillAI::getStructure(int blockType)
{
    return m_tileMap->getBaseBlock(blockType)->getStructure();
}

void AntHillAI::buildStructure(Tile tile)
{
    auto structure(getStructure(tile.blockType));
    int a(0);
    a = a + 1;
    if (structure[0][0] != -1)
    {
        auto neighbours(m_tileMap->getNeighbours(tile.coord));
        for (unsigned int i = 0; i != neighbours.size(); ++i)
        {
            auto it(std::find_if(structure[i].begin(), structure[i].end(), [&] (int x) {return x == m_tileMap->getBlock(neighbours[i])->getBlockType();}));
            if (it == structure[i].end())
            {
                auto itQueue(std::find_if(m_antHill->getQueueBuild()->begin(), m_antHill->getQueueBuild()->end(), [&] (Tile tile) {return tile.coord == neighbours[i];}));
                if (itQueue == m_antHill->getQueueBuild()->end())
                    addBlock(structure[i][0], neighbours[i]);
            }
        }
    }
}


void AntHillAI::addBlock(Tile tile)
{
    buildStructure(tile);
    m_antHill->addBuildQueue(tile);
}

void AntHillAI::addBlock(int blockType, pair<int,int> coord, int blockValue)
{
    addBlock(Tile(blockType, coord, blockValue));
}















  /*  m_antHill->addBuildQueue(Tile(3, pair<int,int>(320,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(321,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(322,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(323,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(324,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(325,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(326,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(327,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(329,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(330,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(331,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(332,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(333,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(334,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(335,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(336,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(328,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(327,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(326,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(325,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(324,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(323,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(322,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(321,330), 2));

    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(340,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(341,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(342,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(343,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(344,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(345,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(346,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(347,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(348,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(349,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(350,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(351,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(352,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(353,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(354,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(355,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(356,320), 2));

    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(360,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(361,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(362,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(363,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(364,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(365,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(366,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(367,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(368,333), 2));

    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(370,333), 2));

    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,321), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,322), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,323), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,324), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,325), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,326), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,328), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,329), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,330), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,331), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,332), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(374,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(375,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(376,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(377,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(378,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(379,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(380,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(381,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(382,333), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(375,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(376,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(377,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(378,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(379,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(380,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(381,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(382,320), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(375,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(376,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(377,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(378,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(379,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(380,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(381,327), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(382,327), 2));
    */


