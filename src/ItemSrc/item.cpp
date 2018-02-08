#include "include/ItemHeader/item.h"

Item::Item(int type, int quantity)
    :m_type(type)
    ,m_quantity(quantity)
{
}

int Item::getType()
{
    return m_type;
}

void Item::setType(int type)
{
    m_type = type;
}

int Item::getQuantity()
{
    return m_quantity;
}

void Item::setQuantity(int quantity)
{
    m_quantity = quantity;
}
