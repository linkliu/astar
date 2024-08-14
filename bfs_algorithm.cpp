#include "bfs_algorithm.h"
#include "map.h"
#include "mnode.h"
#include <iostream>
#include <ncurses.h>
#include <thread>
#include <utility>
using std::make_pair;

map<int, int> BFSAlgorithm::Resolve()
{
	Map& aMap = GetMap();
	MNode& startNode = GetStartNode();
	MNode& endNode = GetEndNode();
	map<int, int> solveMap;
	if(!aMap.NodeCheck(startNode) || !aMap.NodeCheck(endNode) || aMap.Size() < 0)
	{
		stringstream ss;
        ss<<"invalid start node:"<<startNode.ToString()<<" or end node:"<<endNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return solveMap;	
	}
	list<MNode> waveList;
	waveList.push_back(startNode);
	while(!waveList.empty())
	{
		MNode & checkNode = waveList.front();
		list<MNode> neighborList = aMap.GetNeighbors(checkNode);
		for (MNode nextNode : neighborList) 
		{
			//还没有查询过
			if(solveMap.find(aMap.GetNodeNum(nextNode)) == solveMap.cend() && nextNode != startNode)
			{
				//test,log out
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				if(nextNode!=startNode && nextNode!=endNode)
				{
					nextNode.NStateSetter(ENodeState::FINDDING);
					aMap.Draw(nextNode, EDrawType::STATE);
					refresh();
				}
				solveMap.insert(make_pair(aMap.GetNodeNum(nextNode), aMap.GetNodeNum(checkNode)));
				waveList.push_back(nextNode);
			}
		}
		waveList.pop_front();
	}
	return solveMap;
}


vector<int> BFSAlgorithm::FindPath(map<int, int>& oriMap)
{
	Map& aMap = GetMap();
	MNode& startNode = GetStartNode();
	MNode& endNode = GetEndNode();
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
	while (oriMap.find(checkNodeNum) != oriMap.cend()) 
	{
		pathVec.push_back(checkNodeNum);
		checkNodeNum = oriMap.find(checkNodeNum)->second;
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

