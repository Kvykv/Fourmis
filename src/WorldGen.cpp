#include "include/WorldGen.h"
#include <math.h>
#include <cstdlib>
#include <random>
#include <iostream>
#include "include/MathHelp.h"

using namespace std;

WorldGen::WorldGen()
{
}


void WorldGen::creerTableau(vector<vector<int> >& tableau)
{
    std::default_random_engine generator;
    generator.seed(rand()) ;
    array<int, largeur + 1> worldHeight;
    setWorldHeight(worldHeight);
    double var(2 * hauteur/ 5); // Proportion ciel

    for (int x = 0; x < largeur; x++)
    {
        tableau[x].resize(hauteur);
        for (int y = 0; y < hauteur; y++)
        {
            if (y > var + worldHeight[x])
            {
              tableau[x][y] = 1; // 1 : dirt
            }
            else
            {
              tableau[x][y] = 0; // 0 : sky
            }
        }
    }

    setStone(tableau, generator);
}

void WorldGen::setWorldHeight(array<int, largeur + 1> &worldHeight)
{
    int step(largeur/10);
    int lowEdge(0);
    int highEdge(0);
    for(int i = 0; i < largeur + 1; i += step)
        worldHeight[i] = rand()%50 - 25;
    worldHeight[largeur] = rand()%50 - 25;

    for (int i = 0; i < largeur + 1; ++i)
    {
        if (i%step == 0)
        {
            lowEdge = i;
            highEdge = i + step;
        }
        else
            worldHeight[i] = (interpolateSin(worldHeight[lowEdge], worldHeight[highEdge], i - lowEdge, step)
                            + interpolateCubic(worldHeight[lowEdge], worldHeight[highEdge], i - lowEdge, step))/2;
    }
}

void WorldGen::setStone(std::vector<std::vector<int>>& tableau, std::default_random_engine& generator)
{
    std::normal_distribution<double> distribution(0,0.20);
    float var;
    for (int y = 0 ; y < hauteur; y++)
    {
        for (int x = 0; x < largeur; x++)
        {
            var = distribution(generator)*tableau[0].size();
            if ((tableau[0].size()-y)<std::abs(var))
            {
                if (tableau[x][y] == 1)
                {
                    tableau[x][y] = 4; // 4 : stone
                }
            }
        }
    }
    for(int i = 0; i < 100; i++)
        addRock(tableau, generator);
}


int WorldGen::interpolateLinear(int lowEdge, int highEdge, int n, int delta)
{
    if (delta != 0)
        return lowEdge + n*(highEdge - lowEdge)/delta;
}

int WorldGen::interpolateCubic(int lowEdge, int highEdge, int n, int delta)
{
    float x = (float)n/delta;
    float p1 = 3*pow(1-x, 2) - 2*pow(1-x, 3);
    float p2 = 3*pow(x, 2) - 2*pow(x, 3);
    return lowEdge*p1 + highEdge*p2;
}

int WorldGen::interpolateSin(int lowEdge, int highEdge, int n, int delta)
{
    float x = (float)n/delta;
    float p1 = cos(3.14*x/2);
    float p2 = sin(3.14*x/2);
    return lowEdge*p1 + highEdge*p2;
}

void WorldGen::addRock(std::vector<std::vector<int>>& tableau, std::default_random_engine& generator)
{
    std::normal_distribution<double> distribution(0,1);

    int x(generator()%tableau.size());
    int y(generator()%tableau[0].size());
    int size(max(1,(int)(5*distribution(generator))+15));
    std::pair<int,int> coord;

    for (int i = 0; i < size; i++)
    {
        int ite(0);
        x = max(0, min((int)tableau.size()-1, x + (int)(5*distribution(generator))));
        y = max(0, min((int)tableau[0].size()-1, y + (int)(5*distribution(generator))));
        vector<pair<int,int>> neighbours;
        if (tableau[x][y] != 0)
        {
            tableau[x][y] = 4;
            neighbours = MathHelp::getNeighbours(x,y, (int)tableau.size(), (int)tableau[0].size());
            for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                tableau[it->first][it->second] = 4;
            int sizeRock(max(1,((int)(5*distribution(generator)+15))));

            while(ite < sizeRock)
            {
                ite++;

                coord.first = x;
                coord.second = min(hauteur-1, y + ite);
                if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator))) && tableau[coord.first][coord.second] != 0)
                {
                    tableau[coord.first][coord.second] = 4;
                    neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                    for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                        tableau[it->first][it->second] = 4;
                }

                coord.first = x;
                coord.second = max(0, y - ite);
                if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator)))&& tableau[coord.first][coord.second] != 0)
                {
                    tableau[coord.first][coord.second] = 4;
                    neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                    for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                        tableau[it->first][it->second] = 4;
                }
                for (int i = 0; i < ite + 2; i++)       // Scan en losange
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = min(hauteur-1, y + ite - i);
                    if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator)))&& tableau[coord.first][coord.second] != 0)
                    {
                        tableau[coord.first][coord.second] = 4;
                        neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                            tableau[it->first][it->second] = 4;
                    }

                    coord.first = max(0, x-i);
                    coord.second = min(hauteur-1, y + ite - i);
                    if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator)))&& tableau[coord.first][coord.second] != 0)
                    {
                        tableau[coord.first][coord.second] = 4;
                        neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                            tableau[it->first][it->second] = 4;
                    }

                    coord.first = min(largeur-1, x+i);
                    coord.second = max(0, y - ite + i);
                    if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator)))&& tableau[coord.first][coord.second] != 0)
                    {
                        tableau[coord.first][coord.second] = 4;
                        neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                            tableau[it->first][it->second] = 4;
                    }

                    coord.first = max(0, x-i);
                    coord.second = max(0, y - ite + i);
                    if(((double)(MathHelp::distancePath(coord.first, coord.second, x, y))/sizeRock < abs(20*distribution(generator)))&& tableau[coord.first][coord.second] != 0)
                    {
                        tableau[coord.first][coord.second] = 4;
                        neighbours = MathHelp::getNeighbours(coord.first,coord.second, (int)tableau.size(), (int)tableau[0].size());
                        for (auto it = neighbours.begin(); it != neighbours.end(); it++)
                            tableau[it->first][it->second] = 4;
                    }
                }
            }
        }
    }
}

