#ifndef ENTITE_H
#define ENTITE_H

#include "include/MathHelp.h"
#include "include/TileMap.h"
#include "include/IAPathFinding.h"
#include "include/StateHeader/State.h"
#include "include/ItemHeader/item.h"
#include <vector>
#include <iostream>


class Entite : public sf::Drawable, public sf::Transformable
{
    public:
        using Ptr = std::unique_ptr<Entite>;

    public:
        // Constructeur
        Entite(TileMap* tileMap, int type);
        Entite(int x, int y, TileMap *tileMap, int type);

        // Set et get
        void setCoordX(int x);
        void setCoordY(int y);
        int getCoordX();
        int getCoordY();
        std::pair<int,int> getCoord();
        Block* getBlock(std::pair<int,int> coord);
        virtual bool setBlock(std::pair<int,int> coord, int blockType, int blockValue);
        void setPath(std::vector<std::pair<int,int> > path);
        void setGoingForFood(bool boolean);
        bool isGoingForFood();
        bool hasArrived();
        void setHasArrived(bool boolean);
        void setInventoryType(int type);
        void setInventoryQuantity(int quantity);
        int getInventoryQuantity();
        int getInventoryType();
        int getHunger();
        TileMap* getPtrMap();
        void setHunger(int food);
        void dimHunger(int food);
        bool checkFood();
        std::pair<int,int> getDestination();
        void setDestination(std::pair<int,int> coord);


        // Graphic
        void paintEntite();
        static void drawEntiteArray(const std::vector<Entite::Ptr>& entiteArray, sf::RenderWindow &window);

        // Actions
        static void nexStepArray(std::vector<std::unique_ptr<Entite> > *entiteArray);
        void deplacerEntite(int x, int y);
        void deplacerEntite(std::pair<int,int> coord);
        void creuserBlock(int x, int y);
        void eat();
        bool oneMovement();
        bool falling();
        std::pair<int,int> getRandomDestination();

        // Entite IA base
        virtual bool nextStep();
        void goTo(std::pair<int,int> coord);
        bool getFood();
        virtual std::pair<int,int> lookForFood(int typeBlock);
        std::pair<int,int> lookFor(int typeBlock);
        std::pair<int,int> lookUp(std::pair<int,int> coord, int typeBlock);

        std::pair <int,int> m_previousCoord;
        std::vector<std::pair<int,int> > m_path;
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int m_entityType=0;
        int m_coordX;
        int m_coordY;
        bool m_hasArrived;
        bool m_goingForFood;
        int m_iter;
        int m_hunger;
        Item m_inventory;
        std::pair <int,int> m_destination;
        TileMap *m_ptrMap;
        sf::Sprite m_sprite;
};

#endif // ENTITE_H
