#include "include/EntityTypesHeader/AntEgg.h"
#include <iostream>

AntEgg::AntEgg(TileMap *tileMap, AntHill *antHill, int eggType)
    :Ant(tileMap, antHill, 2)
    ,m_eggType(eggType)
    ,m_hatchingCoolDown(500)
{
    m_sprite.setTexture(m_antHill->getResourceHolder()->get(TextureEgg));
    //float scale(1.0/m_sprite.getTexture()->getSize().x);

    auto fscale = [&] (float s) -> float {return 1.0/m_sprite.getTexture()->getSize().x;};

    m_sprite.setScale(fscale(1.f)*m_ptrMap->getTailleTileLargeur(),fscale(1.f)*m_ptrMap->getTailleTileHauteur());
    paintEntite();
    setNextAction();
    m_antHill->m_numberEggs+=1;
}

AntEgg::AntEgg(int x, int y, TileMap *tileMap, AntHill *antHill, int eggType)
    :Ant(x, y, tileMap, antHill, 2)
    ,m_eggType(eggType)
    ,m_hatchingCoolDown(1000)
{
    m_sprite.setTexture(m_antHill->getResourceHolder()->get(TextureEgg));
    float scale(1.0/m_sprite.getTexture()->getSize().x);
    m_sprite.setScale(scale*m_ptrMap->getTailleTileLargeur(),scale*m_ptrMap->getTailleTileHauteur());
    paintEntite();
    setNextAction();
    m_antHill->m_numberEggs+=1;
}

void AntEgg::setNextAction()
{
}
bool AntEgg::nextStep()
{
    m_hatchingCoolDown--;
    if (m_hatchingCoolDown == 0)
    {
        m_antHill->addAnt(getCoord(), m_eggType);
        m_antHill->m_numberEggs-=1;
        return true;
    }
    return false;
}
