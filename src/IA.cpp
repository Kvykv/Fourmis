#include "IA.h"

using namespace std;

AntHillAI::AntHillAI(){}

AntHillAI::AntHillAI(AntHill* antHill)
    :m_antHill(antHill)
{
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(200,300), 2));
    m_antHill->addBuildQueue(Tile(3, pair<int,int>(250,350), 2));
}
