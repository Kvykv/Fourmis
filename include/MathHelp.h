#ifndef MATHHELP_H
#define MATHHELP_H
#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <D:/Programs/SFML/include/SFML/System/Vector2.hpp>


class MathHelp
{
    public:
        MathHelp();
        static int distance(int x1, int y1, int x2, int y2);
        static int distance(std::pair<int,int> coord1, std::pair<int,int> coord2);
        static int distancePath(int x1, int y1, int x2, int y2);
        static int distancePath(std::pair<int,int> coord1, std::pair<int,int> coord2);
};

template <typename T>
bool operator<(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
    return (v1.x < v2.x) || (v1.x == v2.x && v1.y < v2.y);
}

template <typename T>
bool operator>(sf::Vector2<T> v1, sf::Vector2<T> v2)
{
    return (v1.x > v2.x) || (v1.x == v2.x && v1.y > v2.y);
}

template <typename T, typename G>
sf::Vector2<T> operator/(sf::Vector2<T> v1, G val)
{
    return sf::Vector2<T>(v1.x/static_cast<T>(val), v1.y/static_cast<T>(val));
}

template <typename T>
sf::Vector2<T> operator^(sf::Vector2<T> v1, sf::Vector2<T> v2 )
{
    return sf::Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}


#endif // MATHHELP_H
