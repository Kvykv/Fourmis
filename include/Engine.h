#ifndef ENGINE_H
#define ENGINE_H
#include "BlockHeader/Block.h"
#include "EntityTypesHeader/AntQueen.h"
#include "EntityTypesHeader/AntWorker.h"
#include "TileMap.h"
#include "AntHill.h"
#include "Entite.h"
#include "time.h"
#include "IAPathFinding.h"
#include "IA.h"
#include "ResourceHolder.h"
#include "MathHelp.h"
#include "WorldGen.h"
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

    private:
        void draw();
        void processEvents();
        void handleRealTimeEvents();
        void drawInformations();
        std::string getTargetInfo();
        void updateTPS();

    private:
        float framePerSecond;
        TileMap tileMap;
        WorldGen m_worldGen;
        AntHill antHill;
        AntHillAI m_antHillAI;
        sf::Time timePerFrame;
        sf::RenderWindow window;
        sf::View m_mainView;
        sf::View m_miniView;
        int m_counter;
        bool m_statePause;
        float m_velocity;
        const double tailleTileHauteur;
        const double tailleTileLargeur;
        sf::RectangleShape m_outlineMiniMap;
        std::pair<int,int> m_targetCoord;
        std::shared_ptr<Config> m_config;
};

#endif // ENGINE_H
