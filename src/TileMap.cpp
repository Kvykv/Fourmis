#include <SFML/Graphics.hpp>
#include "include/TileMap.h"
#include <math.h>
#include <iostream>
using namespace std;


/* -------------------------- Load ---------------------------------------- */

TileMap::TileMap(){}
TileMap::TileMap(vector<vector<int> >& tableau)
{
    m_blockFactory[0].reset(new BaseBlock(0, "Air", false));
    m_blockFactory[1].reset(new BaseBlock(1, "Dirt", true));
    m_blockFactory[2].reset(new BaseBlock(2, "Food", true));
    m_blockFactory[3].reset(new BaseBlockMulti(3, "Storage", true));
    m_blockFactory[4].reset(new BaseBlock(4, "Stone", false));
    m_blockFactory[5].reset(new BaseBlock(5, "Gallery", false));
    m_blockFactory[6].reset(new BaseBlockMulti(6, "QueenChamber", false));


    m_terrain.resize(largeur);
    for (int i = 0; i < largeur; i++)
    {
        m_terrain[i].resize(hauteur);
    }
    initialiserTileMap(tableau);
}
void TileMap::initialiserTileMap(vector<vector<int> >& tableau)
{
    int depth(0);
    for (int x=0; x<largeur; x++)
    {
        depth = 0;
        for (int y=0; y<hauteur; y++)
        {
            switch(tableau[x][y])
            {
            case 0:
                 m_terrain[x][y].reset(new BlockAir(m_blockFactory[0]));
                 break;
            case 1:
                 depth+=1;
                 m_terrain[x][y].reset(new BlockDirt(m_blockFactory[1], 1000  + rand()%1000 - 500));
                 break;
            case 4:
                depth+=1;
                m_terrain[x][y].reset(new BlockStone(m_blockFactory[4]));
                break;
            default:
                 m_terrain[x][y].reset(new BlockAir(m_blockFactory[0]));
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
    int height(rand()%7+1);
    int width(1);
    setBlock(min(largeur-2,x), max(1,y), 2, 10000);
    for (int i= 1; i<height; i++)
    {
        setBlock(min(largeur-2,x+width), max(1,y-i), 2, 10000);
        width = rand()%2;
    }
}



// -------------------------- Graphique -----------------------------------

void TileMap::paintBlock(int x, int y)
{
    int blockType(m_terrain[x][y]->getBlockType());
    sf::Vertex* quad = &m_array[(x+y*largeur)*4];
    // Position carre
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
        color = sf::Color(153 - 50*m_terrain[x][y]->getQuantity()/m_terrain[x][y]->getCapacity(), 153, 51);
    }
    else if (blockType == 4)
    {
        color = sf::Color(115 - rand()%20,115- rand()%20,115- rand()%20);
    }
    else if (blockType == 5)
    {
        color = sf::Color(244,164,96,200);
    }
    else if (blockType == 6)
    {
        color = sf::Color(205, 133, 63, 200);
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
            cout << m_terrain[x][y]->getTag();
        }
    cout << endl;
    }
}


// -------------------------- Gameplay -------------------------------------


void TileMap::setBlock(int x, int y, int blockType, int blockValue)
{
    pair<int,int> coord(x,y);
    m_tileEntityArray.remove(coord);
    switch(blockType)
    {
    case 0:
        m_terrain[x][y].reset(new BlockAir(m_blockFactory[0]));
        break;
    case 1:
        m_terrain[x][y].reset(new BlockDirt(m_blockFactory[1]));
        break;
    case 2:
        m_tileEntityArray.push_back(coord);
        m_terrain[x][y].reset(new BlockFood(m_blockFactory[2], blockValue));
        break;
    case 3:
        m_tileEntityArray.push_back(coord);
        m_terrain[x][y].reset(new BlockStorage(m_blockFactory[3], 0, blockValue));
        break;
    case 4:
        m_terrain[x][y].reset(new BlockStone(m_blockFactory[4]));
        break;
    case 5:
        m_terrain[x][y].reset(new BlockGallery(m_blockFactory[5]));
        break;
    case 6:
        m_terrain[x][y].reset(new BlockQueenChamber(m_blockFactory[6]));
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
    getBlock(coord)->dimQuantity(quantite);
    if (getBlock(coord)->getQuantity() == 0 && getBlock(coord)->getBlockType() == 2)
        setBlock(coord, 0);
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
    if (y != 0)
    {
        if (x != 0)
        {
            tmp.first = x-1;                                                        //  1
            tmp.second = y-1;                                                       //  0
            neighbours.push_back(tmp);                                              //  0
        }
        tmp.first = x;                                                              //  01
        tmp.second = y-1;                                                           //  0x
        neighbours.push_back(tmp);                                                  //  00
        if (x != largeur-1)
        {
            tmp.first = x+1;                                                        //  001
            tmp.second = y-1;                                                       //  0x0
            neighbours.push_back(tmp);                                              //  000
        }
    }
    if (x != 0)
    {
        tmp.first = x-1;                                                            //  0
        tmp.second = y;                                                             //  1
        neighbours.push_back(tmp);                                                  //  0
    }
    if (x != largeur -1)
    {
        tmp.first = x+1;                                                            //  000
        tmp.second = y;                                                             //  0x1
        neighbours.push_back(tmp);                                                  //  000
    }
    if (y != hauteur-1)
    {
        if (x != 0)
        {
            tmp.first = x-1;                                                        //  0
            tmp.second = y+1;                                                       //  0
            neighbours.push_back(tmp);                                              //  1
        }
        tmp.first = x;                                                              //  00
        tmp.second = y+1;                                                           //  0x
        neighbours.push_back(tmp);                                                  //  01
        if (x != largeur - 1)
        {
            tmp.first = x+1;                                                        //  000
            tmp.second = y+1;                                                       //  0x0
            neighbours.push_back(tmp);                                              //  001
        }
    }
    return neighbours;
}

std::vector<std::pair<int, int> > TileMap::getNeighbours(pair<int,int> coord)
{
    return getNeighbours(coord.first, coord.second);
}

BaseBlock* TileMap::getBaseBlock(int blockType)
{
    return m_blockFactory[blockType].get();
}

void TileMap::updateTileEntityArray(int i)
{
    for (auto it = m_tileEntityArray.begin(); it != m_tileEntityArray.end(); ++it)
        getBlock(*it)->update(i);
}
