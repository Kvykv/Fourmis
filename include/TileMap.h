#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "BlockAir.h"
#include "BlockDirt.h"
#include "BlockFood.h"
#include "BlockStorage.h"
#include "BaseBlock.h"
#include <vector>
#include <memory>

static const int largeur(960);
static const int hauteur(540);
static const double tailleTileHauteur((double)sf::VideoMode::getDesktopMode().height/hauteur);
static const double tailleTileLargeur((double)sf::VideoMode::getDesktopMode().width/largeur);

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    TileMap(std::vector<std::vector<int> >& tableau);
    void initialiserTileMap(std::vector<std::vector<int> >& tableau);
    void showTileMap() const;
    void load();
    void initFood();
    void createGrass(int x, int y);
    void setBlockCrossable(int x, int y, bool boolean);
    void setBlock(int x, int y, int blockType, int blockValue = 0);
    void setBlock(std::pair<int,int> coord, int blockType, int blockValue = 0);
    void setSurfaceBlock(int x, int y);
    void setSurfaceVoisinage(int x, int y);
    void setSurfaceTotale();
    Block* getBlock(int x, int y);
    Block* getBlock(std::pair<int,int> coord);
    void dimQuantiteBlock(std::pair<int,int> coord, int quantite);
    std::vector<std::pair<int, int> > getNeighbours(int x, int y);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void paintBlock(int x, int y);
    void paintVoisinage(int x, int y);
    sf::VertexArray m_array;
    std::array<std::shared_ptr<BaseBlock>, 4> m_blockFactory;

    std::vector<std::vector<std::unique_ptr<Block>>> m_terrain;
};

void creerTableau(std::vector<std::vector<int> >& tableau);

#endif // TILEMAP_H
