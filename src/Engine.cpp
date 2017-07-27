#include "Engine.h"

Engine::Engine()
    :timePerFrame(sf::seconds(1.f/30.f))
    ,window(sf::VideoMode(1920,1080), "TileMap"/*, sf::Style::Fullscreen*/)
{                   //sf::VideoMode::getDesktopMode
    vector<vector<int> > tableau;
    tableau.resize(largeur);
    creerTableau(tableau);
    tileMap = TileMap(tableau);
    m_antHill = AntHill(tileMap);
}

bool Engine::run()
{
    m_antHill.addAnt();
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
            m_antHill.addEgg();
        }
    }
    Entite::nexStepArray(m_antHill.getEntityArray());
}
void Engine::draw()
{
    window.clear();
    window.draw(tileMap);
    Entite::drawEntiteArray(m_antHill.getEntityArray(), window);
    window.display();
}
