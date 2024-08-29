#include "dijstra_algorithm.h"
#include "mnode.h"
#include <functional>
#include <ncurses.h>
#include <queue>
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
	map<int, int> costMap;
	costMap.insert(make_pair(aMap.GetNodeNum(startNode), 0));
	waveQueue.push(startNode);
	while(!waveQueue.empty())
	{
		const MNode& checkNode = waveQueue.top();
		if(checkNode == endNode)
		{
			break;
		}
		list<MNode> neighborList = aMap.GetNeighbors(checkNode);
		for (MNode nextNode : neighborList) 
		{
			int ckNodeNum = aMap.GetNodeNum(checkNode);
			int nextNodeNum = aMap.GetNodeNum(nextNode);
			int nextCost = costMap[ckNodeNum] + nextNode.nodeCost;
			map<int, int>::const_iterator citer = costMap.find(nextNodeNum);
			if(citer == costMap.cend() || nextCost < citer->second)
			{
				if(nextNode!=startNode && nextNode!=endNode)
				{
					nextNode.NStateSetter(ENodeState::FINDDING);
					aMap.Draw(nextNode, EDrawType::STATE);
					refresh();
				}
				costMap[nextNodeNum] = nextCost;
				waveQueue.push(nextNode);
				solveMap.insert(make_pair(nextNodeNum, ckNodeNum));
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
