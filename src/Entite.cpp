#include "include/Entite.h"
using namespace std;

/* -------------------------- Constructeurs / get / set ---------------------------------------- */

Entite::Entite(TileMap *tileMap, int type)
    :m_ptrMap(tileMap)
    ,m_entityType(type)
    ,m_goingForFood(false)
    ,m_hunger(2000)
{
    int x = (rand()%(largeur-2)) + 1;
    for (int y = 0; y < hauteur; y ++)
    {
        if  (m_ptrMap->getBlock(x, y)->isCrossable())
        {
            m_coordX = x;
            m_coordY = y;
            m_sprite.setScale(1*m_ptrMap->getTailleTileLargeur(), 1*m_ptrMap->getTailleTileHauteur());
            break;
        }
    }
}
Entite::Entite(int x, int y, TileMap *tileMap, int type)
    :m_ptrMap(tileMap)
    ,m_entityType(type)
    ,m_coordX(x)
    ,m_coordY(y)
    ,m_goingForFood(false)
    ,m_hunger(2000)
{
    m_sprite.setScale(1*m_ptrMap->getTailleTileLargeur(), 1*m_ptrMap->getTailleTileHauteur());
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
bool Entite::setBlock(pair<int,int> coord, int blockType, int blockValue)
{
    if(MathHelp::distance(coord, getCoord())<=2)
    {
        m_ptrMap->setBlock(coord, blockType, blockValue);
    }
    return true;
}
void Entite::setGoingForFood(bool boolean)
{
    m_goingForFood = boolean;
}
bool Entite::isGoingForFood()
{
    return m_goingForFood;
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
    m_inventory.setType(type);
}
void Entite::setInventoryQuantity(int quantity)
{
    m_inventory.setQuantity(quantity);
}
int Entite::getInventoryType()
{
    return m_inventory.getType();
}
int Entite::getInventoryQuantity()
{
    return m_inventory.getQuantity();
}

int Entite::getHunger()
{
    return m_hunger;
}

void Entite::setHunger(int food)
{
    m_hunger = food;
}

void Entite::dimHunger(int food)
{
    m_hunger-=food;
}

bool Entite::checkFood()
{
    if (m_hunger == 0)
    {
        return true;
    }
    return false;
}
void Entite::setDestination(pair<int,int> coord)
{
    m_destination = coord;
}
pair<int,int> Entite::getDestination()
{
    return m_destination;
}

TileMap* Entite::getPtrMap()
{
    return m_ptrMap;
}

/* -------------------------- Graphics ---------------------------------------- */

void Entite::paintEntite()
{
    m_sprite.setPosition(m_coordX*m_ptrMap->getTailleTileLargeur() - 0.5*m_sprite.getScale().x * m_sprite.getTexture()->getSize().x,m_coordY*m_ptrMap->getTailleTileHauteur() - 0.5*m_sprite.getScale().y*m_sprite.getTexture()->getSize().y);
}
void Entite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
void Entite::drawEntiteArray(const vector<Entite::Ptr>& entiteArray, sf::RenderWindow &window)
{
    for(auto itr = entiteArray.begin(); itr != entiteArray.end(); ++itr)
        window.draw(**itr);
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

pair<int,int> Entite::getRandomDestination()
{
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(rand()%30+25);
    while(ite < 60)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->isCrossable())
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->isCrossable())
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isCrossable())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isCrossable())
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isCrossable())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isCrossable())
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                return coord;
            }
        }
    }
    return coord;
}

void Entite::creuserBlock(int x, int y)
{
    if(MathHelp::distance(x, y, m_coordX, m_coordY)< 3)
    {
        m_ptrMap->setBlock(x,y,5);
    }
}

void Entite::eat()
{
    if (getBlock(m_destination)->getStorageType() == 2)
    {
        int quantity(min(2000, getBlock(m_destination)->getQuantity()));
        m_ptrMap->dimQuantiteBlock(m_destination, quantity);
        m_hunger+=quantity;
        m_goingForFood = false;
    }
    else
    {
        getFood();
    }
}
void Entite::nexStepArray(vector<unique_ptr<Entite> > *entiteArray)
{
    vector<int> areDead;
    for (unsigned int i=0; i < entiteArray->size() ; i++)
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
void Entite::falling()
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
       // cout << m_coordX << "  " << m_coordY << endl;
    }
    m_iter++;
    return true;
}

/* -------------------------- Entity base IA ---------------------------------------- */

bool Entite::getFood()
{
    if (m_hunger == 0)
    {
        return true;
    }
    pair<int,int> coord(lookForFood(2));
    goTo(coord);
    m_goingForFood = true;
    return false;
}

pair<int,int> Entite::lookForFood(int typeBlock)
{
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(0);
    vector<pair<int,int> > airBlocks;
    while(ite < 40)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->getStorageType() == typeBlock && !m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->isEmpty())
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->getStorageType() == typeBlock && !m_ptrMap->getBlock(x, max(0, y - ite))->isEmpty())
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isEmpty())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isEmpty())
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isEmpty())
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->getStorageType() == typeBlock && !m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isEmpty())
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            if (ite > 37)              //Sinon : scan air et crossable et choix au hasard
            {
                if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
            }
        }
    }
    if (airBlocks.size() != 0)          // On s'eloigne du dernier point franchi
    {
        coord = airBlocks[rand()%(airBlocks.size())];
        for (unsigned int i=0; i<airBlocks.size(); i++)
        {
            if (MathHelp::distancePath(airBlocks[i], m_previousCoord) > MathHelp::distancePath(coord, m_previousCoord))
            {
                coord = airBlocks[i];
            }
        }
    }
    m_previousCoord = getCoord();
    return coord;
}

pair<int,int> Entite::lookFor(int typeBlock)
{
    pair<int,int> coord = getCoord();
    int x(coord.first);
    int y(coord.second);
    int ite(0);
    vector<pair<int,int> > airBlocks;
    while(ite < 40)
    {
        ite++;
        if (m_ptrMap->getBlock(x, min(hauteur-1, y + ite))->getBlockType() == typeBlock)
        {
            coord.first = x;
            coord.second = min(hauteur-1, y + ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        else if (m_ptrMap->getBlock(x, max(0, y - ite))->getBlockType() == typeBlock)
        {
            coord.first = x;
            coord.second = max(0, y - ite);
            coord = lookUp(coord, 2);
            return coord;
        }
        for (int i = 0; i < ite + 2; i++)       // Scan en losange
        {
            if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->getBlockType() == typeBlock)
            {
                coord.first = min(largeur-1, x+i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->getBlockType() == typeBlock)
            {
                coord.first = max(0, x-i);
                coord.second = min(hauteur-1, y + ite - i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->getBlockType() == typeBlock)
            {
                coord.first = min(largeur-1, x+i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            else if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->getBlockType() == typeBlock)
            {
                coord.first = max(0, x-i);
                coord.second = max(0, y - ite + i);
                coord = lookUp(coord, 2);
                return coord;
            }
            if (ite > 37)              //Sinon : scan air et crossable et choix au hasard
            {
                if (m_ptrMap->getBlock(min(largeur-1, x+i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), min(hauteur-1, y + ite - i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = min(hauteur-1, y + ite - i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(min(largeur-1, x+i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = min(largeur-1, x+i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
                if (m_ptrMap->getBlock(max(0, x-i), max(0, y - ite + i))->isCrossable())
                {
                    coord.first = max(0, x-i);
                    coord.second = max(0, y - ite + i);
                    airBlocks.push_back(coord);
                }
            }
        }
    }
    if (airBlocks.size() != 0)          // On s'eloigne du dernier point franchi
    {
        coord = airBlocks[rand()%(airBlocks.size())];
        for (unsigned int i=0; i<airBlocks.size(); i++)
        {
            if (MathHelp::distancePath(airBlocks[i], m_previousCoord) > MathHelp::distancePath(coord, m_previousCoord))
            {
                coord = airBlocks[i];
            }
        }
    }
    m_previousCoord = getCoord();
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
    if (coord.first >= 0)
    {
        setDestination(coord);
        setPath(IAPathFinding::pathFinding(m_ptrMap, m_destination, getCoord()));
        m_hasArrived = false;
        m_iter = 0;
    }
}

bool Entite::nextStep()
{
    bool isDead(false);
    m_hunger -= 1;
    isDead = checkFood();
    if (m_hunger == 500)
    {
        getFood();
    }
    falling();
    while (!m_hasArrived)
    {
        oneMovement();
        return isDead;
    }
    return isDead;
}
