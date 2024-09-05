#include "dijstra_algorithm.h"
#include "mnode.h"
#include <chrono>
#include <functional>
#include <ncurses.h>
#include <queue>
#include <thread>
#include <utility>
using std::priority_queue;
using std::make_pair;

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
	map<int, int> curCostMap;
	curCostMap.insert(make_pair(aMap.GetNodeNum(startNode), 0));
	waveQueue.push(startNode);
	int meetIndex = 0;
	while(!waveQueue.empty())
	{
		const MNode checkNode = waveQueue.top();
		if(checkNode == endNode)
		{
			break;
		}
		list<MNode> neighborList = aMap.GetNeighbors(checkNode);
		for (MNode nextNode : neighborList) 
		{
			int ckNodeNum = aMap.GetNodeNum(checkNode);
			int nextNodeNum = aMap.GetNodeNum(nextNode);
			int nextCurCost = curCostMap[ckNodeNum] + nextNode.nodeCost;
			map<int, int>::const_iterator citer = curCostMap.find(nextNodeNum);
			if(citer == curCostMap.cend() || nextCurCost < citer->second)
			{
				curCostMap[nextNodeNum] = nextCurCost;
				nextNode.CurCostSetter(nextCurCost);
				nextNode.MISetter(meetIndex);
				if(nextNode!=startNode && nextNode!=endNode)
				{
					// nextNode.NStateSetter(ENodeState::FINDDING);
					// aMap.Draw(nextNode, EDrawType::STATE);
					aMap.Draw(nextNode.curCost, nextNode.mapIndex_Y, nextNode.mapIndex_X);
					refresh();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(30));
				waveQueue.push(nextNode);
				solveMap.insert(make_pair(nextNodeNum, ckNodeNum));
				meetIndex += 1;
			}
		}
		waveQueue.pop();
	}
	return solveMap;
}


vector<int> DIJAlgorithm::FindPath(map<int, int>& solMap)
{
	return {};
}
