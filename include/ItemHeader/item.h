#ifndef ITEMHEADERITEM_H
#define ITEMHEADERITEM_H

class Item
{
public:
    Item(int type = 0, int quantity = 0);
    int getType();
    void setType(int type);
    int getQuantity();
    void setQuantity(int quantity);

private:
    int m_type;
    int m_quantity;
};

#endif // ITEMHEADERITEM_H
