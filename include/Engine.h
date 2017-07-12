#ifndef ENGINE_H
#define ENGINE_H
#include "Block.h"
#include "TileMap.h"
#include "AntHill.h"
#include "Entite.h"
#include "time.h"
#include "IAPathFinding.h"
#include <windows.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

class Engine
{
    public:
        Engine();
        bool run();
        void draw();
        void processEvents();
    protected:
        TileMap tileMap;
        vector<Entite> m_entityArray;
        AntHill m_antHill;
        sf::Time timePerFrame;
        sf::RenderWindow window;

    private:
};

#endif // ENGINE_H
