#include <algorithm>
#include <chrono>
#include <curses.h>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>
#include <vector>
#include "mnode.h"
#include "astar_algorithm.h"
using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::find_if;

static map<ENodeType, list<pair<int,int>>> ElementsMap = 
{
    {ENodeType::BARRIER, {{13,4},{14,4},{15,4}, {15,5},{15,6}}},
    {ENodeType::WATER,{{7,7},{7,8},{7,9},{8,9},{9,9},{10, 9}}}
};

void ConstructMap(const Map &aMap)
{
    if(aMap.Size() > 0)
    {
        for (pair<ENodeType, list<pair<int, int>>> ePair : ElementsMap) 
        {
            for (pair<int, int> miPair : ePair.second) 
            {
                MNode node = aMap.GetNode(miPair.first, miPair.second);
                node.NtypeSetter(ePair.first);
                aMap.Draw(node);
            }
        }
        refresh();
    }
}

void BFS(Map &aMap, const MNode &startNode, const MNode &endNode)
{
    if(!aMap.NodeCheck(startNode) || !aMap.NodeCheck(endNode) || aMap.Size() <= 0)
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
        ckNode.NStateSetter(ENodeState::FINDDING);
        aMap.Draw(ckNode);
        nbList = aMap.GetNeighbors(ckNode, nbList);
        //map.Draw(nbList);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        refresh();
        for ( MNode nextNode: nbList) 
        {
            //如果还没有检查过，插入到下一个要找的步骤
            auto checkedFun = [nextNode](MNode node){return node.IsSamePos(nextNode); };
            if(find_if(reachedVector.cbegin(), reachedVector.cend(), checkedFun) == reachedVector.cend())
            {
                waveList.push_back(nextNode);
                nextNode.NStateSetter(ENodeState::NEXT);
                reachedVector.push_back(nextNode);
            }
        }
        waveList.pop_front();
        //map.Draw(nbList);
        refresh();
    }
}

void Dijkstra(const Map &map, const MNode &startNode, const MNode &endNode)
{

}

void AStar(const Map &map, const MNode &startNode, const MNode &endNode)
{

}
