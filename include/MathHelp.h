#ifndef MATHHELP_H
#define MATHHELP_H
#include <cmath>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class MathHelp
{
    public:
        MathHelp();
        static int distance(int x1, int y1, int x2, int y2);
        static int distance(pair<int,int> coord1, pair<int,int> coord2);
        static int distancePath(int x1, int y1, int x2, int y2);
        static int distancePath(pair<int,int> coord1, pair<int,int> coord2);

    protected:

    private:
};

#endif // MATHHELP_H
