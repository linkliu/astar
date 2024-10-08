#include "dijstra_algorithm.h"
#include "mnode.h"
#include <chrono>
#include <cmath>
#include <functional>
#include <ncurses.h>
#include <queue>
#include <thread>
#include <utility>
using std::priority_queue;
using std::make_pair;

int DIJAlgorithm::Heuristic(const MNode& nodeA , const MNode& nodeB) const
{
	return std::abs(nodeA.mapIndex_X - nodeB.mapIndex_X) + std::abs(nodeA.mapIndex_Y - nodeB.mapIndex_Y);
}

map<int, int> DIJAlgorithm::Resolve()
{
	Map& aMap = GetMap();
	const MNode& startNode = GetStartNode();
	const MNode& endNode = GetEndNode();
	map<int, int> solveMap;
	if(!aMap.NodeCheck(startNode) || !aMap.NodeCheck(endNode) || aMap.Size() < 0)
	{
		stringstream ss;
        ss<<"invalid start node:"<<startNode.ToString()<<" or end node:"<<endNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return solveMap;	
	}
	priority_queue<MNode, vector<MNode>, std::greater<MNode>> waveQueue;
	waveQueue.push(startNode);
	while(!waveQueue.empty())
	{
		const MNode checkNode = waveQueue.top();
		waveQueue.pop();
		if(checkNode == endNode)
		{
			break;
		}
		list<MNode> neighborList = aMap.GetNeighbors(checkNode);
		for (MNode nextNode : neighborList) 
		{
			int ckNodeNum = aMap.GetNodeNum(checkNode);
			int nextNodeNum = aMap.GetNodeNum(nextNode);
			map<int, int>::const_iterator citer = solveMap.find(nextNodeNum);
			if(citer == solveMap.cend() && nextNode != startNode)
			{
				nextNode.CurCostSetter(Heuristic(endNode, nextNode));
				if(nextNode!=startNode && nextNode!=endNode)
				{
					// nextNode.NStateSetter(ENodeState::FINDDING);
					// aMap.Draw(nextNode, EDrawType::STATE);
					aMap.Draw(nextNode.index, nextNode.mapIndex_Y, nextNode.mapIndex_X);
					refresh();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				waveQueue.push(nextNode);
				solveMap.insert(make_pair(nextNodeNum, ckNodeNum));
			}
		}
		// waveQueue.pop();
	}
	return solveMap;
}


vector<int> DIJAlgorithm::FindPath(map<int, int>& solMap)
{
	return {};
}
