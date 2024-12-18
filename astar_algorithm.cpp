#include "astar_algorithm.h"
#include "mnode.h"
#include <chrono>
#include <functional>
#include <queue>
#include <thread>
#include <utility>
using std::priority_queue;
using std::make_pair;


int AStarAlgorithm::Heuristic(const MNode& nodeA, const MNode& nodeB) const
{
	return std::abs(nodeA.mapIndex_X - nodeB.mapIndex_X) + std::abs(nodeA.mapIndex_Y - nodeB.mapIndex_Y);
}

map<int, int> AStarAlgorithm::Resolve()
{
    Map& aMap = GetMap();
    const MNode& startNode = GetStartNode();
    const MNode& endNode = GetEndNode();
    map<int, int> solveMap;
	map<int, int> lessCostMap;
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
	lessCostMap.insert({aMap.GetNodeNum(startNode), 0});
	while (!waveQueue.empty()) 
	{
		const MNode checkNode = waveQueue.top();
		waveQueue.pop();
		if(checkNode == endNode)
		{
			break;
		}
		list<MNode> neighborList = aMap.GetFilterNeighbors(checkNode);
		for (MNode nextNode : neighborList) 
		{
			int ckNodeNum = aMap.GetNodeNum(checkNode);
			int nextNodeNum = aMap.GetNodeNum(nextNode);
			int nextCost = lessCostMap[ckNodeNum] + aMap.GetCost(checkNode, nextNode);
			if(lessCostMap.find(nextNodeNum) == lessCostMap.cend() || nextCost < lessCostMap[nextNodeNum])
			{
				lessCostMap[nextNodeNum] = nextCost;
				int heCost = nextCost + Heuristic(nextNode, endNode);	
				nextNode.CurHeCostSetter(heCost);
				if(nextNode != startNode && nextNode != endNode)
				{
					aMap.Draw(nextNode.heCost, nextNode.mapIndex_Y, nextNode.mapIndex_X);
					refresh();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				waveQueue.push(nextNode);
				solveMap.insert(make_pair(nextNodeNum, ckNodeNum));
			}
		}
	}
	return solveMap;
}

vector<int> AStarAlgorithm::FindPath(map<int, int>& solveMap)
{
	const Map& aMap = GetMap();
	const MNode& startNode = GetStartNode();
	const MNode& endNode = GetEndNode();
	vector<int> pathVec;
	if(!aMap.NodeCheck(startNode) || !aMap.NodeCheck(endNode) || aMap.Size()<=0)
	{
		stringstream ss;
		ss<<"invalid startNode:"<<startNode.ToString()<<", or endNode:"<<endNode.ToString()<<endl;
		cout<<ss.str();
		endwin();
		return pathVec;
	}
	int checkNodeNum = aMap.GetNodeNum(endNode); 
	while (solveMap.find(checkNodeNum) != solveMap.cend()) 
	{
		pathVec.push_back(checkNodeNum);
		checkNodeNum = solveMap.find(checkNodeNum)->second;
	}
	//有路径
	if(checkNodeNum == aMap.GetNodeNum(startNode))
	{
		pathVec.push_back(checkNodeNum);
	}
	else //没有找到
	{
		pathVec.clear();
	}
	return pathVec;
}
