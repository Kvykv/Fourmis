#ifndef IAPATHFINDING_H
#define IAPATHFINDING_H
#include <map>
#include <vector>
#include "TileMap.h"

using namespace std;

struct point{
    int x,y;
};


class Node {
public:
    int m_id;
	pair<int,int> m_coordParent;
	int m_costG;
	int m_costH;
	int m_costF;
	pair<int,int> m_coordNode;
	bool operator<=(Node const&b);
	void setCostH(pair<int,int>& coordTarget);
	void setCost(int n);
	Node(pair<int,int> coordNode, pair<int,int> coordTarget, Node& parent, int costG, int costF);
	Node(pair<int,int> coordNode, pair<int,int> coordParent);
	Node();
};
class IAPathFinding
{
    public:
        static vector<pair<int,int> > pathFinding(TileMap* tileMap, pair<int,int> coordTarget, pair<int,int> coordEntite);
        static bool containsCoord(pair<int,int> coord, vector<Node> liste, int &index);
        static Node addIndexFermee(map<pair<int,int>, Node> &ouverte);

    protected:

    private:
};

#endif
