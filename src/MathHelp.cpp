#include "MathHelp.h"

using namespace std;

MathHelp::MathHelp()
{
}

int MathHelp::distance(int x1, int y1, int x2, int y2)
{
    int distance = abs(x1 - x2) + abs(y1 - y2);
    return distance;
}
int MathHelp::distance(pair<int,int> coord1, pair<int,int> coord2)
{
    int distance = abs(coord1.first - coord2.first) + abs(coord1.second - coord2.second);
    return distance;
}
int MathHelp::distancePath(pair<int,int> coord1, pair<int,int> coord2)
{
    return distancePath(coord1.first, coord1.second, coord2.first, coord2.second);
}
int MathHelp::distancePath(int x1, int y1, int x2, int y2)
{
    int distance = (int) 10*(pow((x1 - x2),2) + pow((y1 - y2),2));
    return distance;
}
