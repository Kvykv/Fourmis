#ifndef IAPATHFINDING_H
#define IAPATHFINDING_H
#include <map>
#include <vector>
#include "TileMap.h"


struct point{
    int x,y;
};


class Node {
public:
    int m_id;
	std::pair<int,int> m_coordParent;
	int m_costG;
	int m_costH;
    std::pair<int,int> m_coordNode;
    int m_costF;
	bool operator<=(Node const&b);
	void setCostH(std::pair<int,int>& coordTarget);
	void setCost(int n);
	Node(std::pair<int,int> coordNode, std::pair<int,int> coordTarget, Node& parent, int costG, int costF);
	Node(std::pair<int,int> coordNode, std::pair<int,int> coordParent);
	Node();
};
class IAPathFinding
{
    public:
        static std::vector<std::pair<int,int> > pathFinding(TileMap* tileMap, std::pair<int,int> coordTarget, std::pair<int,int> coordEntite);
        static bool containsCoord(std::pair<int,int> coord, std::vector<Node> liste, int &index);
        static Node addIndexFermee(std::map<std::pair<int,int>, Node> &ouverte);

    protected:

    private:
};

#endif
