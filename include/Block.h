#ifndef BLOCK_H
#define BLOCK_H
#include <string>

using namespace std;
class Block
{
    public:
        Block();
        Block(int n, bool crossable, bool diggable, int cost);
        int getValeurCase() const;
        void setValeurCase(int n);
        int getCost() const;
        void setCost(int cost);
        bool isDiggable();
        bool isCrossable();
        void setCrossable(bool boolean);
        void setDiggable(bool boolean);

        // Heritage
        virtual string getString() const;
        virtual void setQuantite(int quantite);
        virtual void dimQuantite(int quantite);
        virtual void addQuantite(int quantite);
        virtual int getQuantite();
        virtual int getValueStorage();

    protected:
        int m_valeurCase;
        int m_cost;
        bool m_isCrossable = false;
        bool m_isDiggable = false;
        string m_tag;

    private:
};

#endif
