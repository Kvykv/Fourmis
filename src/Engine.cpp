#include "include/Engine.h"
#include "include/Config.h"
#include <string>
#include <sstream>

using namespace std;

Engine::Engine()
    :framePerSecond(30.f)
    ,m_worldGen()
    ,window(sf::VideoMode(1920,1080), "TileMap"/*, sf::Style::Fullscreen*/)
    ,m_mainView(window.getDefaultView())
    ,m_miniView(window.getDefaultView())
    ,m_counter(0)
    ,m_statePause(0)
    ,m_velocity(15.0f)
    ,tailleTileHauteur(((double)sf::VideoMode::getDesktopMode().height/hauteur))
    ,tailleTileLargeur(((double)sf::VideoMode::getDesktopMode().width/largeur))
    ,m_outlineMiniMap(sf::Vector2f(0, 0))
    ,m_targetCoord(pair<int,int>(-1,-1))
    ,m_config(new Config)
{
    m_config->loadConfig("config.json");

    vector<vector<int> > tableau;
    tableau.resize(largeur);
    m_worldGen.creerTableau(tableau);
    tileMap = TileMap(tableau, m_config);
    antHill =  AntHill(tileMap, m_config);
    m_antHillAI = AntHillAI(&antHill);


    /// Graphic
    m_mainView.zoom(1.0f);
    m_miniView.setViewport(sf::FloatRect(0.8, 0, 0.2, 0.2));
    m_outlineMiniMap.setSize((sf::Vector2f(m_miniView.getViewport().width, m_miniView.getViewport().height)^window.getDefaultView().getSize()) + sf::Vector2f(4.f,4.f));
    m_outlineMiniMap.setFillColor(sf::Color::Black);
    m_outlineMiniMap.setPosition(window.getDefaultView().getSize().x - m_outlineMiniMap.getSize().x ,0);
}

bool Engine::run()
{
    antHill.addAnt(1);
    antHill.addAnt(0);
    draw();
    sf::Clock clock;
    sf::Time time;
    updateTPS();
    while(window.isOpen())
    {
        clock.restart();
        processEvents();
        draw();
        sf::sleep(timePerFrame - clock.getElapsedTime());
    }
    return true;
}
void Engine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            m_statePause = !m_statePause;
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T)
        {
            tileMap.setDisplayModeTemperature(!tileMap.getDisplayModeTemperature());
            tileMap.paintMap();
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_mainView);
            worldPos.x = worldPos.x/tailleTileLargeur;
            worldPos.y = worldPos.y/tailleTileHauteur;
            m_targetCoord = pair<int,int>(worldPos.x, worldPos.y);
        }
        if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Num3))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_mainView);
            worldPos.x = worldPos.x/tailleTileLargeur;
            worldPos.y = worldPos.y/tailleTileHauteur;
            m_antHillAI.addBlock(3, pair<int,int>(worldPos.x, worldPos.y), 2, "Storage");
        }
        if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Num6))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_mainView);
            worldPos.x = worldPos.x/tailleTileLargeur;
            worldPos.y = worldPos.y/tailleTileHauteur;
            m_antHillAI.addBlock(6, pair<int,int>(worldPos.x, worldPos.y), 0, "ThroneRoom");
        }
        if(event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Num7))
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_mainView);
            worldPos.x = worldPos.x/tailleTileLargeur;
            worldPos.y = worldPos.y/tailleTileHauteur;
            m_antHillAI.addBlock(7, pair<int,int>(worldPos.x, worldPos.y), 0, "Field");
        }
    }

    if(!m_statePause)
    {
        m_counter++;
        if (m_counter%10 == 0)
        {
            antHill.updateFoodCapacity();
        }
        if (m_counter%100 == 0)
        {
            m_antHillAI.update();
        }
        if (m_counter == 1000)
        {
            m_counter = 0;
        }
        for(int i = 0; i < 2000; i++)
            tileMap.updateRandomChunk();
        tileMap.updateTileEntityArray(m_counter);
        Entite::nexStepArray(antHill.getEntityArray());
    }


    handleRealTimeEvents();
}
void Engine::draw()
{
    window.clear();

    window.setView(m_mainView);
    window.draw(tileMap);
    Entite::drawEntiteArray(*antHill.getEntityArray(), window);

    window.setView(window.getDefaultView());
    window.draw(m_outlineMiniMap);


    window.setView(m_miniView);
    window.draw(tileMap);

    window.setView(window.getDefaultView());
    drawInformations();

    window.display();
}

void Engine::drawInformations()
{
    std::stringstream sstm;
    sstm                << "Population : "                      << antHill.getPopulation()
                        << "    |    Queen : "                  << antHill.m_numberQueen
                        << "        Idle : "                    << antHill.m_numberWorkerIdle
                        << "        Gather : "                  << antHill.m_numberWorkerGather
                        << "        Build : "                   << antHill.m_numberWorkerBuild
                        << "        Farm : "                    << antHill.m_numberWorkerFarm
                        << "        Eggs : "                    << antHill.m_numberEggs
                        << "      ||        Food Capacity : "   << antHill.getFoodCapacity()
                        << "        Food Stored : "             << antHill.getCurrentFoodStorage() << endl
                        << "Dead : "            << antHill.m_dead << endl
                        << "Target : " << m_targetCoord.first << " " << m_targetCoord.second << "  ||  " << getTargetInfo() << endl
                        << "TPS : " << framePerSecond << "   || State Pause : " << m_statePause;
    string infos = sstm.str();
    sf::Font font;
    sf::Text text;
    text.setPosition(10,10);
    font.loadFromFile("resources/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setString(infos);
    window.draw(text);
}

void Engine::handleRealTimeEvents()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        if(m_mainView.getCenter().y - m_mainView.getSize().y/2 > m_velocity*1)
            m_mainView.move(0, -m_velocity*1);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        if(m_mainView.getCenter().y + m_mainView.getSize().y/2 < window.getDefaultView().getSize().y)
            m_mainView.move(0, m_velocity*1);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        if(m_mainView.getCenter().x - m_mainView.getSize().x/2 > m_velocity*1)
            m_mainView.move(-m_velocity*1, 0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        if(m_mainView.getCenter().x + m_mainView.getSize().x/2 < window.getDefaultView().getSize().x)
            m_mainView.move(m_velocity*1, 0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))         // Dezoom
    {
        m_mainView.zoom(1.1f);
        if (window.getDefaultView().getSize() < m_mainView.getSize())
        {
            m_mainView = window.getDefaultView();
        }
        if(m_mainView.getCenter().y - m_mainView.getSize().y/2 < 0)
            m_mainView.move(0, - m_mainView.getCenter().y + m_mainView.getSize().y/2);

        if(m_mainView.getCenter().y + m_mainView.getSize().y/2 > window.getDefaultView().getSize().y)
            m_mainView.move(0, - m_mainView.getCenter().y - m_mainView.getSize().y/2 + window.getDefaultView().getSize().y);

        if(m_mainView.getCenter().x - m_mainView.getSize().x/2 < 0)
            m_mainView.move( -m_mainView.getCenter().x + m_mainView.getSize().x/2, 0);

        if(m_mainView.getCenter().x + m_mainView.getSize().x/2 > window.getDefaultView().getSize().x)
            m_mainView.move(- m_mainView.getCenter().x - m_mainView.getSize().x/2 + window.getDefaultView().getSize().x, 0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))         // Zoom
    {
        m_mainView.zoom(0.9f);
        if (window.getDefaultView().getSize()/10 > m_mainView.getSize())
        {
            m_mainView.setSize(window.getDefaultView().getSize()/10);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))         // Plus vite
    {
        framePerSecond = min(framePerSecond + 1.f, 80.f);
        updateTPS();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))         // Moins vite
    {
        framePerSecond = max (framePerSecond - 1.f, 10.f);
        updateTPS();
    }
}


std::string Engine::getTargetInfo()
{
    if (m_targetCoord.first == -1)
    {
        return "";
    }
    return tileMap.getBlock(m_targetCoord)->getInfo();
}

void Engine::updateTPS()
{
    timePerFrame = sf::seconds(1.f/framePerSecond);
}
