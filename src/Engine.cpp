#include "Engine.h"
#include <string>
#include <sstream>

using namespace std;

Engine::Engine()
    :timePerFrame(sf::seconds(1.f/30.f))
    ,window(sf::VideoMode(1920,1080), "TileMap"/*, sf::Style::Fullscreen*/)
    ,m_mainView(window.getDefaultView())
    ,m_miniView(window.getDefaultView())
    ,m_velocity(15.0f)
    ,m_outlineMiniMap(sf::Vector2f(0, 0))
    ,m_counter(0)
    ,m_worldGen()
{                   //sf::VideoMode::getDesktopMode
    vector<vector<int> > tableau;
    tableau.resize(largeur);
    m_worldGen.creerTableau(tableau);
    tileMap = TileMap(tableau);
    antHill =  AntHill(tileMap);
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
    draw();
    sf::Clock clock;
    sf::Time time;
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
        {
            window.close();
        }
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            m_statePause = !m_statePause;
    }

    if(!m_statePause)
    {
        m_counter++;
        if (m_counter%10 == 0)
        {
            antHill.updateFoodCapacity();
        }
        if (m_counter%20 == 0)
        {
            m_antHillAI.update();
        }
        if (m_counter == 1000)
        {
            m_counter = 0;
        }
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
                        << "        Eggs : "                    << antHill.m_numberEggs
                        << "      ||        Food Capacity : "   << antHill.getFoodCapacity()
                        << "        Food Stored : "             << antHill.getCurrentFoodStorage()
                        << "      || Dead : "                   << antHill.m_dead;
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
}
