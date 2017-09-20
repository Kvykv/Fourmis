#ifndef WORLDGEN_H
#define WORLDGEN_H

#include <vector>
#include <array>

constexpr int largeur(960);
constexpr int hauteur(540);

class WorldGen
{
    public:
        WorldGen();

        void creerTableau(std::vector<std::vector<int>>& tableau);

    private:
        int interpolateLinear(int lowEdge, int highEdge, int n, int delta);
        void setWorldHeight(std::array<int, largeur + 1> &worldHeight);

};

#endif // WORLDGEN_H
