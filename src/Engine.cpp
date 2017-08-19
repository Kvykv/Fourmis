#include "Engine.h"
#include <string>
#include <sstream>

Engine::Engine()
    :timePerFrame(sf::seconds(1.f/30.f))
    ,window(sf::VideoMode(1920,1080), "TileMap"/*, sf::Style::Fullscreen*/)
{                   //sf::VideoMode::getDesktopMode
    vector<vector<int> > tableau;
    tableau.resize(largeur);
    creerTableau(tableau);
    tileMap = TileMap(tableau);
    antHill =  AntHill(tileMap);
}

bool Engine::run()
{
    antHill.addAnt(1);
    draw();
    //tileMap.showTileMap();
    sf::Clock clock;
    int i(0);
    sf::Time time;
    while(window.isOpen())
    {
        clock.restart();
        processEvents();
        draw();
        sf::sleep(timePerFrame - clock.getElapsedTime());
        i++;
        if (i>=50)
        {
            //antHill.addEgg();
            i-=50;
        }
    }
    return true;
}
void Engine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Q)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            //antHill.addEgg();
        }
    }
    Entite::nexStepArray(antHill.getEntityArray());
}
void Engine::draw()
{
    window.clear();
    window.draw(tileMap);
    Entite::drawEntiteArray(antHill.getEntityArray(), window);
    drawInformations();
    window.display();
}

void Engine::drawInformations()
{
    std::stringstream sstm;
    sstm << "Number of :        Idle : " << antHill.m_numberWorkerIdle << "       Food : " << antHill.m_numberWorkerFood << "        Gather : " << antHill.m_numberWorkerGather << "        Build : " << antHill.m_numberWorkerBuild << "        Eggs : " << antHill.m_numberEggs;
    string infos = sstm.str();
    sf::Text text;
    sf::Font font;
    text.setString(infos);
    text.setPosition(10,10);
    font.loadFromFile("resources/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    window.draw(text);
}
