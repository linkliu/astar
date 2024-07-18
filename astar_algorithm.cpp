#include <algorithm>
#include <chrono>
#include <curses.h>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>
#include <vector>
#include "mnode.h"
#include "debug_tool.h"
#include "astar_algorithm.h"
using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::find_if;
using std::make_pair;

static map<ENodeType, list<pair<int,int>>> ElementsMap = 
{
    {ENodeType::BARRIER, 
            {
                {13,4},{14,4},{15,4}, {15,4},{16,4}, {17,4},{18,4},{19,4},
                {13,5},{14,5},{15,5}, {15,5},{16,5}, {17,5},{18,5},{19,5},
                {0,4},{1,4},{2,4}, {3,4},{4,4}, {5,4},{6,4},{7,4},{8,4},{9,4},{10,4},{11,4},{11,5},{11,6},{11,7},{11,8},{11,9},{11,10},{11,11},
                {0,5},{1,5},{2,5}, {3,5},{4,5}, {5,5},{6,5},{7,5},
            }
        },
    {ENodeType::WATER,
            {
                {2,12},{3,12},{4,12},{5,12},{6,12},{7, 12}, {8,12}, {9,12},{10,12},{11,12},{12,12},
                {2,13},{3,13},{4,13},{5,13},{6,13},{7, 13}, {8,13}, {9,13},{10,13},{11,13},{12,13}
            }
        }
};

void ConstructMap(Map &aMap)
{
    if(aMap.Size() > 0)
    {
        //cout<<endl;
        //cout<<"constsruct--------------------------------------------------start"<<endl;
        for (pair<ENodeType, list<pair<int, int>>> ePair : ElementsMap) 
        {
            for (pair<int, int> miPair : ePair.second) 
            {
                MNode& node = aMap.GetNode(miPair.first, miPair.second);
                node.NTypeSetter(ePair.first);
                //cout<<node.NType<<"$->"<<node.str<<",";
                aMap.Draw(node);
            }
        }
        //cout<<endl;
        //cout<<"constsruct--------------------------------------------------end"<<endl;
        refresh();
    }
}

void BFS(Map &aMap, const MNode &startNode, const MNode &endNode, map<int, int>& originMap)
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
        if(!ckNode.IsSamePos(startNode) && !ckNode.IsSamePos(endNode))
        {
            ckNode.NStateSetter(ENodeState::FINDDING);
			aMap.Draw(ckNode);
        }
        nbList = aMap.GetNeighbors(ckNode, nbList);
        
        //map.Draw(nbList);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //refresh();
        for ( MNode nextNode: nbList) 
        {
            //如果还没有检查过，插入到下一个要找的步骤
            auto checkedFun = [nextNode](MNode node){return node.IsSamePos(nextNode); };
            if(originMap.find(aMap.GetNodeNum(nextNode)) == originMap.cend())
            {
                originMap.insert(make_pair<int, int>(aMap.GetNodeNum(nextNode), aMap.GetNodeNum(ckNode)));
            }
            if(find_if(reachedVector.cbegin(), reachedVector.cend(), checkedFun) == reachedVector.cend())
            {
                waveList.push_back(nextNode);
				if(!nextNode.IsSamePos(startNode) && !nextNode.IsSamePos(nextNode))
				{
					nextNode.NStateSetter(ENodeState::NEXT);
				}
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
