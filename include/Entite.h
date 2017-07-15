#ifndef ENTITE_H
#define ENTITE_H

#include "TileMap.h"
#include "MathHelp.h"
#include "Action.h"
#include "IAPathFinding.h"
#include "AntHill.h"
#include <vector>
#include <iostream>


class Entite : public sf::Drawable, public sf::Transformable
{
    public:
        // Constructeur
        Entite(TileMap *tileMap, AntHill *antHill);
        Entite(int x, int y, TileMap *tileMap, AntHill *antHill);

        // Set et get
        void setCoordX(int x);
        void setCoordY(int y);
        int getCoordX();
        int getCoordY();
        pair<int,int> getCoord();
        Block* getBlock(pair<int,int> coord);
        void setBlock(pair<int,int> coord, int blockType, int blockValue);
        void setPath(vector<pair<int,int> > path);
        void setGoingForFood(bool boolean);
        Action getMemoryAction();
        void setAction(Action action);
        Action getAction();
        void setAction(pair<int,int> coord, int blockType, int blockValue, int typeAction);
        bool hasArrived();
        void setHasArrived(bool boolean);
        void setInventoryType(int type);
        void setInventoryQuantity(int quantity);
        int getInventoryQuantity();
        int getInventoryType();

        // Graphic
        void paintEntite();
        static void drawEntiteArray(vector<Entite> &entiteArray, sf::RenderWindow &window);

        // Actions
        static void nexStepArray(vector<Entite> &entiteArray);
        void deplacerEntite(int x, int y);
        void deplacerEntite(pair<int,int> coord);
        void creuserBlock(int x, int y);
        bool oneMovement();
        bool oneAction();
        bool falling();
        void gather(Block* block);
        void store(Block* block);

        // Entite IA base
        bool nextStep();
        void goTo(pair<int,int> coord);
        void getFood();
        void setNextAction();
        pair<int,int> lookFor(int typeBlock);
        pair<int,int> lookUp(pair<int,int> coord, int typeBlock);

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int m_coordY;
        int m_coordX;
        bool m_hasArrived;
        bool m_goingForFood;
        int m_iter;
        int m_hunger;
        int m_inventoryType;
        int m_inventoryQuantity;
        AntHill *m_antHill;
        TileMap *m_ptrMap;
        vector<pair<int,int> > m_path;
        sf::CircleShape m_shape;
        Action m_currentAction;
        Action m_memoryAction;
};

#endif // ENTITE_H
