#include "include/MathHelp.h"

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

vector<pair<int, int> > MathHelp::getNeighbours(int x, int y, int largeur, int hauteur)
{
    pair<int,int> tmp;
    vector<pair<int, int> > neighbours;
    if (y != 0)
    {
        if (x != 0)
        {
            tmp.first = x-1;                                                        //  1
            tmp.second = y-1;                                                       //  0
            neighbours.push_back(tmp);                                              //  0
        }
        tmp.first = x;                                                              //  01
        tmp.second = y-1;                                                           //  0x
        neighbours.push_back(tmp);                                                  //  00
        if (x != largeur-1)
        {
            tmp.first = x+1;                                                        //  001
            tmp.second = y-1;                                                       //  0x0
            neighbours.push_back(tmp);                                              //  000
        }
    }
    if (x != 0)
    {
        tmp.first = x-1;                                                            //  0
        tmp.second = y;                                                             //  1
        neighbours.push_back(tmp);                                                  //  0
    }
    if (x != largeur -1)
    {
        tmp.first = x+1;                                                            //  000
        tmp.second = y;                                                             //  0x1
        neighbours.push_back(tmp);                                                  //  000
    }
    if (y != hauteur-1)
    {
        if (x != 0)
        {
            tmp.first = x-1;                                                        //  0
            tmp.second = y+1;                                                       //  0
            neighbours.push_back(tmp);                                              //  1
        }
        tmp.first = x;                                                              //  00
        tmp.second = y+1;                                                           //  0x
        neighbours.push_back(tmp);                                                  //  01
        if (x != largeur - 1)
        {
            tmp.first = x+1;                                                        //  000
            tmp.second = y+1;                                                       //  0x0
            neighbours.push_back(tmp);                                              //  001
        }
    }
    return neighbours;
}
