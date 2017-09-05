#ifndef MATHHELP_H
#define MATHHELP_H
#include <cmath>
#include <vector>
#include <map>
#include <iostream>


class MathHelp
{
    public:
        MathHelp();
        static int distance(int x1, int y1, int x2, int y2);
        static int distance(std::pair<int,int> coord1, std::pair<int,int> coord2);
        static int distancePath(int x1, int y1, int x2, int y2);
        static int distancePath(std::pair<int,int> coord1, std::pair<int,int> coord2);

    protected:

    private:
};

#endif // MATHHELP_H
