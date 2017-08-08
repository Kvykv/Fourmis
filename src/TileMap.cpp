#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <iostream>
using namespace std;


/* -------------------------- Load ---------------------------------------- */

TileMap::TileMap(){}
TileMap::TileMap(vector<vector<int> >& tableau)
{
    m_terrain.resize(largeur);
    for (int i = 0; i < largeur; i++)
    {
        m_terrain[i].resize(hauteur);
    }
    initialiserTileMap(tableau);
}
void TileMap::initialiserTileMap(vector<vector<int> >& tableau)
{
    for (int x=0; x<largeur; x++)
    {
        for (int y=0; y<hauteur; y++)
        {
            switch(tableau[x][y])
            {
            case 0:
                 m_terrain[x][y].reset(new BlockAir());
                 break;
            case 1:
                 m_terrain[x][y].reset(new BlockDirt());
                 break;
            default:
                 m_terrain[x][y].reset(new BlockAir());
                 break;
            }
        }
    }
    load();
    setSurfaceTotale();
    initFood();
}
void TileMap::initFood()
{
    int x(0);
    for (int i = 0; i < largeur/20; i++)
    {
        x = (rand()%(largeur-2)) + 1;
        for (int y = 0; y < hauteur; y ++)
        {
            if  (m_terrain[x][y]->isCrossable())
            {
                createGrass(x, y);
                break;
            }
        }
    }
}
void TileMap::createGrass(int x, int y)
{
    int height(rand()%7);
    int width(1);
    for (int i= 0; i<height; i++)
    {
        setBlock(min(largeur-2,x+width), max(1,y-i), 2, 10000);
        width = rand()%2;
    }
}
void creerTableau(vector<vector<int> >& tableau)
{
    double var(2 * hauteur/ 5); // Proportion ciel
    for (int x = 0; x < largeur; x++)
    {
        var = var + rand()%7 - 3;
        tableau[x].resize(hauteur);
        for (int y = 0; y < hauteur; y++)
        {
            if (y > var)
            {
              tableau[x][y] = 1; // 1 : dirt
            } else
            {
              tableau[x][y] = 0; // 0 : sky
            }
        }
    }
}


// -------------------------- Graphique -----------------------------------

void TileMap::paintBlock(int x, int y)
{
    int blockType(m_terrain[x][y]->getBlockType());
    sf::Vertex* quad = &m_array[(x+y*largeur)*4];
    // Position carré
    quad[0].position = sf::Vector2f(x*tailleTileLargeur,y*tailleTileHauteur);
    quad[1].position = sf::Vector2f((x+1)*tailleTileLargeur, y*tailleTileHauteur);
    quad[2].position = sf::Vector2f((x+1)*tailleTileLargeur, (y+1)*tailleTileHauteur);
    quad[3].position = sf::Vector2f(x*tailleTileLargeur, (y+1)*tailleTileHauteur);
    sf::Color color;
    if (blockType == 1)
    {
        int cost(m_terrain[x][y]->getCost());
        color = sf::Color(91 - cost/50 + 20, 60 - cost/50 + 20, 20 - cost/50 + 20);
    }
    else if (blockType == 2)
    {
        color = sf::Color(58, 157, 35);
    }
    else if (blockType == 3)
    {
        color = sf::Color(0,0,0);
    }
    else
    {
            color = sf::Color(119 + 10 * ((static_cast<float>(rand()%100))/100 - 1 / 2),(181 + 10 * ((static_cast<float>(rand()%100))/100 - 1 / 2)), (254 + 10 * ((static_cast<float>(rand()%100))/100 - 1)));
    }
    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
}
void TileMap::paintVoisinage(int x, int y)
{
    paintBlock(x, y);
	paintBlock(x + 1, y);
	paintBlock(x - 1, y);
	paintBlock(x, y + 1);
	paintBlock(x, y - 1);
}
void TileMap::load()
{
    // Set du VertexArray
    m_array.setPrimitiveType(sf::Quads);
    m_array.resize(hauteur * largeur * 4);

    // Remplissage du tableau de Vertex
    for (int x = 0; x < largeur; x++)
    {
        for (int y = 0; y < hauteur; y++)
        {
            paintBlock(x, y);
        }
    }
}
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_array, states);
}
void TileMap::showTileMap() const
{
    for (int y=0; y<hauteur; y++)
    {
        for (int x=0; x<largeur; x++)
        {
            cout << m_terrain[x][y]->getBlockType();
        }
    cout << endl;
    }
    cout << endl;
    for (int y=0; y<hauteur; y++)
    {
        for (int x=0; x<largeur; x++)
        {
            cout << m_terrain[x][y]->isCrossable();
        }
    cout << endl;
    }
}


// -------------------------- Gameplay -------------------------------------

void TileMap::setBlock(int x, int y, int blockType, int blockValue)
{
    switch(blockType)
    {
    case 0:
        m_terrain[x][y].reset(new BlockAir());
        break;
    case 1:
        m_terrain[x][y].reset(new BlockDirt());
        break;
    case 2:
        m_terrain[x][y].reset(new BlockFood(blockValue));
        break;
    case 3:
        m_terrain[x][y].reset(new BlockStorage(0, blockValue));
    }
    setSurfaceVoisinage(x, y);
    paintVoisinage(x, y);
}
void TileMap::setBlock(pair<int,int> coord, int blockType, int blockValue)
{
    setBlock(coord.first, coord.second, blockType, blockValue);
}
void TileMap::setBlockCrossable(int x, int y, bool boolean)
{
    m_terrain[x][y]->setCrossable(boolean);
}
Block* TileMap::getBlock(int x, int y)
{
    return m_terrain[x][y].get();
}
Block* TileMap::getBlock(pair<int,int> coord)
{
    return m_terrain[coord.first][coord.second].get();
}
void TileMap::dimQuantiteBlock(pair<int,int> coord, int quantite)
{
    getBlock(coord)->dimQuantite(quantite);
    if (getBlock(coord)->getQuantite() <= 0)
    {
        setBlock(coord, 0);
    }
}
void TileMap::setSurfaceBlock(int x, int y)
{
	if (x < (largeur -1)&& 0 < x && y < (hauteur - 1) && 0 < y)
    {
		bool support((m_terrain[x + 1][y]->isDiggable())
				|| (m_terrain[x][y + 1]->isDiggable()) || (m_terrain[x - 1][y]->isDiggable())
				|| (m_terrain[x][y - 1]->isDiggable())||(m_terrain[x + 1][y+1]->isDiggable())
				|| (m_terrain[x-1][y + 1]->isDiggable()) || (m_terrain[x - 1][y+1]->isDiggable())
				|| (m_terrain[x-1][y - 1]->isDiggable()));
		if (m_terrain[x][y]->getBlockType() == 0 && support)
        {
            setBlockCrossable(x, y, true);
		}
		else if (m_terrain[x][y]->isCrossable() && !support)
		{
		    setBlockCrossable(x, y, false);
		}
	}
}
void TileMap::setSurfaceVoisinage(int x, int y)
{
	setSurfaceBlock(x, y);
	setSurfaceBlock(x + 1, y);
	setSurfaceBlock(x - 1, y);
	setSurfaceBlock(x, y + 1);
	setSurfaceBlock(x, y - 1);
	setSurfaceBlock(x + 1, y+1);
	setSurfaceBlock(x - 1, y-1);
	setSurfaceBlock(x-1, y + 1);
	setSurfaceBlock(x+1, y - 1);
}
void TileMap::setSurfaceTotale()
{
    for (int x = 0; x < largeur; x++) {
        for (int y = 0; y < hauteur; y++) {
            setSurfaceBlock(x, y);
        }
    }
}
vector<pair<int, int> > TileMap::getNeighbours(int x, int y)
{
    pair<int,int> tmp;
    vector<pair<int, int> > neighbours;
    if (x != largeur-1){
        tmp.first = x+1;
        tmp.second = y;
        neighbours.push_back(tmp);
        if (y != hauteur-1){
            tmp.first = x+1;
            tmp.second = y+1;
            neighbours.push_back(tmp);
        }
        if (y != 0){
            tmp.first = x+1;
            tmp.second = y-1;
            neighbours.push_back(tmp);
        }
    }
    if (x != 0){
        tmp.first = x-1;
        tmp.second = y;
        neighbours.push_back(tmp);
        if (y != hauteur-1){
            tmp.first = x-1;
            tmp.second = y+1;
            neighbours.push_back(tmp);
        }
        if (y != 0){
            tmp.first = x-1;
            tmp.second = y-1;
            neighbours.push_back(tmp);
        }
    }
    if (y != hauteur-1){
        tmp.first = x;
        tmp.second = y+1;
        neighbours.push_back(tmp);
    }
    if (y != 0){
        tmp.first = x;
        tmp.second = y-1;
        neighbours.push_back(tmp);
    }
    return neighbours;
}
