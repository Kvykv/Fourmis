#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "BlockAir.h"
#include "BlockDirt.h"
#include "BlockFood.h"
#include "BlockStorage.h"
#include <vector>
#include <memory>

using namespace std;
static const int largeur(500);
static const int hauteur(300);
static const double tailleTileHauteur((double)sf::VideoMode::getDesktopMode().height/hauteur);
static const double tailleTileLargeur((double)sf::VideoMode::getDesktopMode().width/largeur);

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    TileMap(vector<vector<int> >& tableau);
    void initialiserTileMap(vector<vector<int> >& tableau);
    void showTileMap() const;
    void load();
    void initFood();
    void createGrass(int x, int y);
    void setBlockCrossable(int x, int y, bool boolean);
    void setBlock(int x, int y, int valeurCase);
    void setBlock(pair<int,int> coord, Block block);
    void setSurfaceBlock(int x, int y);
    void setSurfaceVoisinage(int x, int y);
    void setSurfaceTotale();
    Block* getBlock(int x, int y);
    Block* getBlock(pair<int,int> coord);
    void dimQuantiteBlock(pair<int,int> coord, int quantite);
    vector<pair<int, int> > getNeighbours(int x, int y);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void paintBlock(int x, int y);
    void paintVoisinage(int x, int y);
    sf::VertexArray m_array;

    array<array<unique_ptr<Block>,hauteur>,largeur> m_terrain;
};

void creerTableau(vector<vector<int> >& tableau);

#endif // TILEMAP_H
