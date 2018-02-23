#include "include/IAPathFinding.h"
#include "include/MathHelp.h"
#include <iostream>
#include <windows.h>
using namespace std;

Node::Node(){}
Node::Node(pair<int,int> coordNode, pair<int,int> coordTarget, Node& parent, int costG, int costF)
    :m_coordParent(parent.m_coordNode)
    ,m_costG(costG)
    ,m_costH(MathHelp::distancePath(coordNode.first, coordTarget.first, coordNode.second, coordTarget.second))
    ,m_coordNode(coordNode)
    ,m_costF(costF)
{
}
Node::Node(pair<int,int> coordNode, pair<int,int> coordParent)
    :m_coordParent(coordParent)
    ,m_costG(0)
    ,m_coordNode(coordNode)
{
}
void Node::setCostH(pair<int,int>& coordTarget)
{
    m_costH = MathHelp::distancePath(m_coordNode.first, coordTarget.first, m_coordNode.second, coordTarget.second);
}

bool IAPathFinding::containsCoord(pair<int,int> coord, vector<Node> liste, int &index)
{
    for (unsigned int i = 0; i<liste.size(); i++ )
    {
        if (coord == liste[i].m_coordNode)
        {
            index = i;
            return true;
        }
    }
    return false;
}

vector<pair<int,int> > IAPathFinding::pathFinding(TileMap* tileMap, const pair<int,int> coordTarget, const pair<int,int> coordEntite){
  		map<pair<int,int>, Node> ouverte;
		vector<Node> fermee;
		vector<pair<int,int> > path;
        bool isReachable(false);
		vector<pair<int,int> > neighbours(tileMap->getNeighbours(coordTarget.first, coordTarget.second));
        for (unsigned int i=0; i<neighbours.size(); i++)
        {
            if((tileMap->getBlock(neighbours[i]))->isCrossable() ||
                        tileMap->getBlock(neighbours[i])->isDiggable())
            {
                isReachable = true;
            }
        }
        if (!isReachable || MathHelp::distance(coordEntite,coordTarget)<= 1)
        {
            path.push_back(coordEntite);
            return path;
        }
		bool isClosed[largeur][hauteur];
		bool isOpened[largeur][hauteur];
		for (int i = 0; i < largeur; i++)
        {
            for (int j = 0; j < hauteur; j++)
            {
                isClosed[i][j] = false;
                isOpened[i][j] = false;
            }
        }
		pair<int,int> coordParent;
		coordParent.first = -1;
		coordParent.second = -1;
		Node rootNode(coordEntite, coordParent);
		fermee.push_back(rootNode);
		Node current(rootNode);
		int newCostF, newCostG;
		if (current.m_coordNode != coordTarget){
        do {
            vector<pair<int, int> > neighbours = tileMap->getNeighbours(current.m_coordNode.first, current.m_coordNode.second);
            for (unsigned int i = 0; i< neighbours.size(); i++){
                if (tileMap->getBlock(neighbours[i].first, neighbours[i].second)->isCrossable() ||
                     tileMap->getBlock(neighbours[i].first, neighbours[i].second)->isDiggable()){
					if (!isClosed[neighbours[i].first][neighbours[i].second]){
                        newCostG = current.m_costG + MathHelp::distancePath(current.m_coordNode, neighbours[i])*tileMap->getBlock(neighbours[i].first, neighbours[i].second)->getCost();
                        newCostF = newCostG  + MathHelp::distancePath(neighbours[i], coordTarget);
                        if (isOpened[neighbours[i].first][neighbours[i].second])
                        {
							if (newCostF < ouverte[neighbours[i]].m_costF)
							{
                                ouverte[neighbours[i]].m_costF = newCostF;              // ouverte a forcement neighbours[i] --> pas d'erreur
								ouverte[neighbours[i]].m_coordParent = current.m_coordNode;
							}
						}
						else
						{
						    isOpened[neighbours[i].first][neighbours[i].second] = true;
							ouverte[neighbours[i]] = Node(neighbours[i], coordTarget, current, newCostG, newCostF);
						}
					}
				}
            }
			if (ouverte.size()!=0){
				Node next = IAPathFinding::addIndexFermee(ouverte);
				current = next;
				isClosed[next.m_coordNode.first][next.m_coordNode.second] = true;
				fermee.push_back(next);
			}
        } while (ouverte.size()!=0 && MathHelp::distance(current.m_coordNode,coordTarget)>0);
        }
		// Get path
        int ind(0);
		Node node = fermee[fermee.size()-1];
		if (node.m_coordParent.first != -1){
			while (!(node.m_coordParent.first == -1)){
				path.insert(path.begin(),node.m_coordNode);
				containsCoord(node.m_coordParent, fermee, ind);
				node = fermee[ind];
			}
        }
		return path;
}
Node IAPathFinding::addIndexFermee(map<pair<int,int>, Node> &ouverte){
    Node node;
    pair<int,int> coord;
    node = ouverte.begin()->second;
    int temp;
    int mini = ouverte.begin()->second.m_costF;
    map<pair<int,int>, Node>::iterator ite = ouverte.begin();
    while (ite != ouverte.end())
    {
        temp = ite->second.m_costF;
        if (temp <= mini)
        {
            mini = temp;
            coord = ite->first;
        }
        ite++;
    }
    node = ouverte[coord];
    ouverte.erase(coord);
    return node;
}
