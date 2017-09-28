#include "WorldGen.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

WorldGen::WorldGen()
{
}


void WorldGen::creerTableau(vector<vector<int> >& tableau)
{
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

    // Stone

    for (int y = 0 ; y < hauteur; y++)
    {
        var = pow(y, 9)/pow(hauteur, 9)*100 ;
        for (int x = 0; x < largeur; x++)
        {
            if ((rand()%100 + 1)<var)
            {
                if (tableau[x][y] == 1)
                {
                    tableau[x][y] = 4; // 4 : stone
                }
            }
        }
    }
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
            worldHeight[i] = interpolateLinear(worldHeight[lowEdge], worldHeight[highEdge], i - lowEdge, step);
    }
}


int WorldGen::interpolateLinear(int lowEdge, int highEdge, int n, int delta)
{
    if (delta != 0)
        return lowEdge + n*(highEdge - lowEdge)/delta;
}


