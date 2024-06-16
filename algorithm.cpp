#include "algorithm.h"
#include "mnode.h"
#include <algorithm>
#include <curses.h>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::find_if;

void BFS(Map &map, const MNode &startNode, const MNode &endNode)
{
    if(!map.NodeCheck(startNode) || !map.NodeCheck(endNode) || map.Size() <= 0)
    {
        stringstream ss;
        ss<<"invalid start node:"<<startNode.ToString()<<" or end node:"<<endNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return;
    }
    list<MNode> waveList;
    waveList.push_back(startNode);
    vector<MNode>  reachedVector;
    reachedVector.push_back(startNode);
    list<MNode> nbList;
    while(!waveList.empty())
    {
        MNode ckNode = waveList.front();
        ckNode.NState = ENodeState::FINDDING;
        map.Draw(ckNode);
        for ( MNode nextNode: map.GetNeighbors(ckNode, nbList)) 
        {
            //如果还没有检查过，插入到下一个要找的步骤
            auto checkedFun = [nextNode](MNode node){return node.IsSamePos(nextNode); };
            if(find_if(reachedVector.cbegin(), reachedVector.cend(), checkedFun) == reachedVector.cend())
            {
                waveList.push_back(nextNode);
                reachedVector.push_back(nextNode);
            }
            //TODO 如果找到了，不计入
        }
        waveList.pop_front();
    }
}

void Dijkstra(const Map &map, const MNode &startNode, const MNode &endNode)
{

}

void AStar(const Map &map, const MNode &startNode, const MNode &endNode)
{

}
