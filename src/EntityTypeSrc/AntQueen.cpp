#include "include/EntityTypesHeader/AntQueen.h"

using namespace std;

AntQueen::AntQueen(TileMap *tileMap, AntHill *antHill)
    :Ant(tileMap, antHill, 1)
    ,m_state(new StateQueenLaying(this))
    ,m_CDLaying(0)
{
    float scale(4.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*tailleTileLargeur,scale*tailleTileHauteur);
    paintEntite();
    m_antHill->m_numberQueen ++;
}

AntQueen::AntQueen(int x, int y, TileMap *tileMap, AntHill *antHill)
    :Ant(x, y, tileMap, antHill, 1)
    ,m_state(new StateQueenLaying(this))
    ,m_CDLaying(0)
{
    float scale(4.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*tailleTileLargeur,scale*tailleTileHauteur);
    paintEntite();
    m_antHill->m_numberQueen ++;
}

AntQueen::~AntQueen()
{
    m_antHill->m_numberQueen --;
}

void AntQueen::setCDLaying(int par)
{
    m_CDLaying = par;
}
void AntQueen::addCDLaying(int incr)
{
    m_CDLaying += incr;
}
int AntQueen::getCDLaying()
{
    return m_CDLaying;
}
void AntQueen::updateLaying(int incr)
{
    if (m_ptrMap->getBlock(getCoord())->getBlockType() == 6)
        addCDLaying(2*incr);
    else
    {
        addCDLaying(1);
        if (hasArrived())
            goTo(m_antHill->getSpecificUniqueTile("QueenChamber"));
    }
}

StateQueen* AntQueen::getState()
{
    return m_state.get();
}
void AntQueen::setState(StateQueen newState)
{
    if (newState.m_string == "food")
    {
        m_state.reset(new StateQueenFood(this));
    }
    else if (newState.m_string == "laying")
    {
        m_state.reset(new StateQueenLaying(this));
    }
}

bool AntQueen::layEgg(int eggType)
{
    if (hasArrived())
    {
        m_CDLaying = 0;
        vector<pair<int,int> > neighbours(m_ptrMap->getNeighbours(m_coordX, m_coordY));
        int par(rand()%8);
        for (int i=0; i<neighbours.size(); i++)
        {
            if (m_ptrMap->getBlock(neighbours[(par+i)%8])->isCrossable())
            {
                m_antHill->addEgg(neighbours[(par+i)%8], eggType);
                return true;
            }
        }
    }

    return false;
}

bool AntQueen::nextStep()
{
    return m_state->execute(this);
}
