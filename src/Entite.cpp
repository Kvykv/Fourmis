#include "Entite.h"
using namespace std;

/* -------------------------- Constructeurs / get / set ---------------------------------------- */

Entite::Entite(TileMap *tileMap, int type)
    :m_ptrMap(tileMap)
    ,m_hunger(1000)
    ,m_goingForFood(false)
    ,m_entityType(type)
{

    int x = (rand()%(largeur-2)) + 1;
    for (int y = 0; y < hauteur; y ++)
    {
        if  (m_ptrMap->getBlock(x, y)->isCrossable())
        {
            m_coordX = x;
            m_coordY = y;
            m_shape.setRadius(1*tailleTileLargeur);
            paintEntite();
            m_shape.setFillColor(sf::Color::Black);
            break;
        }
    }

}
Entite::Entite(int x, int y, TileMap *tileMap, int type)
    :m_coordX(x)
    ,m_coordY(y)
    ,m_ptrMap(tileMap)
    ,m_hunger(1000)
    ,m_goingForFood(false)
    ,m_entityType(type)
{
    m_shape.setRadius(1.5*tailleTileLargeur);
    paintEntite();
    m_shape.setFillColor(sf::Color::Black);
}
int Entite::getCoordX()
{
    return m_coordX;
}
int Entite::getCoordY()
{
    return m_coordY;
}
pair<int,int> Entite::getCoord()
{
    pair<int,int> coord;
    coord.first = m_coordX;
    coord.second = m_coordY;
    return coord;

}
void Entite::setCoordX(int x)
{
    m_coordX = x;
}
void Entite::setCoordY(int y)
{
    m_coordY = y;
}
void Entite::setPath(vector<pair<int,int> > path)
{
    m_path = path;
}
Block* Entite::getBlock(pair<int,int> coord)
{
    return m_ptrMap->getBlock(coord);
}
void Entite::setBlock(pair<int,int> coord, int blockType, int blockValue)
{
    if(MathHelp::distance(coord, getCoord())<=2)
    {
        m_ptrMap->setBlock(coord, blockType, blockValue);
    }
}
void Entite::setGoingForFood(bool boolean)
{
    m_goingForFood = boolean;
}
Action Entite::getMemoryAction()
{
    return m_memoryAction;
}
void Entite::setAction(pair<int,int> coord, int blockType, int blockValue, int typeAction)
{
    m_currentAction = Action(coord, blockType, blockValue, typeAction);
    goTo(coord);
}
void Entite::setAction(Action action)
{
    m_currentAction = action;
    goTo(action.getCoord());
}
Action Entite::getAction()
{
    return m_currentAction;
}
bool Entite::hasArrived()
{
    return m_hasArrived;
}
void Entite::setHasArrived(bool boolean)
{
    m_hasArrived = boolean;
}
void Entite::setInventoryType(int type)
{
    if (type != 0)
    {
        m_inventoryType = type;
    }
}
void Entite::setInventoryQuantity(int quantity)
{
    m_inventoryQuantity = quantity;
}
int Entite::getInventoryType()
{
    return m_inventoryType;
}
int Entite::getInventoryQuantity()
{
    return m_inventoryQuantity;
}


/* -------------------------- Graphics ---------------------------------------- */

void Entite::paintEntite()
{
    m_shape.setPosition((m_coordX-0.5)*tailleTileLargeur,(m_coordY-0.5)*tailleTileHauteur);
}
void Entite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_shape, states);
}
void Entite::drawEntiteArray(vector<unique_ptr<Entite> > *entiteArray, sf::RenderWindow &window)
{
    for (int i=0; i < entiteArray->size() ; i++)
    {
        window.draw(*(*entiteArray)[i]);
    }
}
/* -------------------------- Actions ---------------------------------------- */


void Entite::deplacerEntite(int x, int y)
{
    if (m_ptrMap->getBlock(x,y)->isDiggable() && !m_ptrMap->getBlock(x,y)->isCrossable())
    {
        creuserBlock(x,y);
    }
    setCoordX(x);
    setCoordY(y);
    paintEntite();
}
void Entite::deplacerEntite(pair<int,int> coord)
{
    deplacerEntite(coord.first, coord.second);
}
void Entite::creuserBlock(int x, int y)
{
    if(MathHelp::distance(x, y, m_coordX, m_coordY)< 3)
    {
        m_ptrMap->setBlock(x,y,0);
    }
}
void Entite::nexStepArray(vector<unique_ptr<Entite> > *entiteArray)
{
    vector<int> areDead;
    for (int i=0; i < entiteArray->size() ; i++)
    {
        bool isDead((*entiteArray)[i]->nextStep());
        if (isDead)
        {
        areDead.push_back(i);
        }
    }
    if(areDead.size()>0)
    {
        for (int i=areDead.size()-1; i>=0; i--)
        {
            entiteArray->erase(entiteArray->begin() + areDead[i]);
        }
    }
}
bool Entite::falling()
{
    if (!getBlock(getCoord())->isCrossable())
    {
        deplacerEntite(getCoordX(), getCoordY()+1);
    }
}
bool Entite::oneMovement()
{
    if (m_path.size()==0)
    {
        m_hasArrived = true;
        return true;
    }
    deplacerEntite(m_path[m_iter]);
    if (m_iter == (int)m_path.size()-1)
    {
        m_hasArrived = true;
        m_iter = 0;
    }
    m_iter++;
    return true;
}
bool Entite::oneAction()
{
    int type(m_currentAction.getType());
    switch (type)
    {
    case 0 :
        break;
    case 1 :
        m_ptrMap->setBlock(m_currentAction.getCoord(), 0);
        break;
    case 2 :
        {
            int quantity(min(500, getBlock(m_currentAction.getCoord())->getQuantite()));
            m_ptrMap->dimQuantiteBlock(m_currentAction.getCoord(), quantity);
            m_hunger+=quantity;
            m_goingForFood = false;
            setAction(m_memoryAction);
            return true;
            break;
        }
    case 3 :
        break;
    }
    setNextAction();
    return true;
}

/* -------------------------- Entity base IA ---------------------------------------- */

bool Entite::getFood()
{
    if (m_hunger == 0)
    {
        return true;
    }
    if (!m_goingForFood)
    {
        if (m_hunger < 250 && m_hunger%20 == 0)
        {
            m_memoryAction = m_currentAction;
            pair<int,int> coord(lookFor(2));
            coord = lookUp(coord, 2);
            if (m_ptrMap->getBlock(coord)->getBlockType()==2)
            {
                setAction(coord, 0, 0, 2);
                m_goingForFood = true;
            }
        }
    }
    return false;
}
pair<int,int> Entite::lookFor(int typeBlock)
{
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(0);
    if (m_ptrMap->getBlock(coord)->getBlockType() == typeBlock)
    {
        return coord;
    }
    while(ite < 1000)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->getBlockType() == typeBlock)
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->getBlockType() == typeBlock)
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->getBlockType() == typeBlock)
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->getBlockType() == typeBlock)
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->getBlockType() == typeBlock)
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->getBlockType() == typeBlock)
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
        }
    }
    return coord;
}
pair<int,int> Entite::lookUp(pair<int,int> coord, int typeBlock)
{
    bool boolean(true);
    int x = coord.first;
    int y = coord.second;
    while (boolean && y > 0)
    {
        if (m_ptrMap->getBlock(x,y-1)->getBlockType() == typeBlock)
        {
            coord.first = x;
            coord.second = y-1;
        }
        else if (m_ptrMap->getBlock(x-1,y-1)->getBlockType() == typeBlock)
        {
            coord.second = y-1;
            coord.first = x-1;
        }
        else if (m_ptrMap->getBlock(x+1,y-1)->getBlockType() == typeBlock)
        {
            coord.second = y-1;
            coord.first = x+1;
        }
        else {boolean = false;}
        y--;
    }
    return coord;
}
void Entite::goTo(pair<int,int> coord)
{
    setPath(IAPathFinding::pathFinding(m_ptrMap, coord, getCoord()));
    m_hasArrived = false;
    m_iter = 0;
}
void Entite::setNextAction()
{
    pair<int,int> coord;
    coord.first = 300 + rand()%20;
    coord.second = 300+ rand()%5;
    if(coord.first == m_coordX && coord.second == m_coordY)
    {
        setAction(coord, 0, 0, 0);
    }
    else
    {
        setAction(coord, 0, 0, 1);
    }

}
bool Entite::nextStep()
{
    bool isDead(false);
    m_hunger -= 1;
    isDead = getFood();
    falling();
    while (!m_hasArrived)
    {
        oneMovement();
        return isDead;
    }
    oneAction();
    return isDead;
}
