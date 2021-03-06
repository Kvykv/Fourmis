#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "Config.h"
#include "BlockHeader/Block.h"
#include "BlockHeader/BlockAir.h"
#include "BlockHeader/BlockDirt.h"
#include "BlockHeader/BlockFood.h"
#include "BlockHeader/BlockStone.h"
#include "BlockHeader/BlockStorage.h"
#include "BlockHeader/BlockGallery.h"
#include "BlockHeader/BlockQueenChamber.h"
#include "BlockHeader/BlockMushroom.h"
#include "BaseBlockHeader/BaseBlockMulti.h"
#include "WorldGen.h"
#include <vector>
#include <list>
#include <memory>


class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap();
    TileMap(std::vector<std::vector<int> >& tableau, std::shared_ptr<Config> config);
    void initialiserTileMap(std::vector<std::vector<int> >& tableau);
    void showTileMap() const;
    void paintMap();
    void load();
    double getTailleTileHauteur();
    double getTailleTileLargeur();
    bool getDisplayModeTemperature();
    void setDisplayModeTemperature(bool mode);
    void initFood();
    void createGrass(int x, int y);
    void setBlockCrossable(int x, int y, bool boolean);
    void setBlock(int x, int y, int blockType, int blockValue = 0);
    void setBlock(std::pair<int,int> coord, int blockType, int blockValue = 0);
    void setTemperatureBlock(int x, int y);
    void setSurfaceBlock(int x, int y);
    void setSurfaceVoisinage(int x, int y);
    void setSurfaceTotale();
    Block* getBlock(int x, int y);
    Block* getBlock(std::pair<int,int> coord);
    BaseBlock* getBaseBlock(int blockType);
    void dimQuantiteBlock(std::pair<int,int> coord, int quantite);
    std::vector<std::pair<int, int>> getNeighbours(int x, int y);
    std::vector<std::pair<int, int>> getNeighbours(std::pair<int,int> coord);
    void updateTileEntityArray(int i);

    /// Temperature

    void updateBlockTemperature(std::pair<int,int> coord);
    void updateRandomChunk();


private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void paintBlock(int x, int y);
    void paintVoisinage(int x, int y);
    sf::VertexArray m_array;
    double tailleTileHauteur;
    double tailleTileLargeur;

    std::shared_ptr<Config> m_config;
    bool m_displayModeTemperature;
    std::array<std::shared_ptr<BaseBlock>, 8> m_blockFactory;
    std::list<std::pair<int,int>> m_tileEntityArray;
    std::vector<std::vector<std::unique_ptr<Block>>> m_terrain;
};


#endif // TILEMAP_H
