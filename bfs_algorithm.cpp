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
	list<MNode> waveList;
	waveList.push_back(startNode);
	while(!waveList.empty())
	{
		MNode & checkNode = waveList.front();
		if(checkNode == endNode)
		{
			break;
		}
		list<MNode> neighborList = aMap.GetFilterNeighbors(checkNode);
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


vector<int> BFSAlgorithm::FindPath(map<int, int>& solveMap)
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

int BFSAlgorithm::CalStepsToStart(const MNode& cnode, const map<int, int>& solveMap)
{
	 Map& aMap = GetMap();
	 if(!aMap.NodeCheck(cnode) || solveMap.size() <= 0)
	 {
		stringstream ss;
		ss<<"invalid cnode:"<<cnode.ToString()<<", or solveMap.size=:"<<solveMap.size()<<endl;
		cout<<ss.str();
		endwin();
		return -1;
	 }
	 const MNode& startNode = GetStartNode();
	 int checkNodeNum = aMap.GetNodeNum(cnode);
	 int step = 0;
	 while (solveMap.find(checkNodeNum) != solveMap.cend()) 
	 {
		 step+=1;
		 checkNodeNum = solveMap.find(checkNodeNum)->second;
	 }
	 return step;
}

void BFSAlgorithm::DrawNodeSteps(const map<int, int>& solveMap)
{
	Map& aMap = GetMap();
	const MNode& startNode = GetStartNode();
	const MNode& endNode = GetEndNode();
	for (int firdex = 0; firdex < aMap.Size(); firdex++) 
	{
		pair<int, int> firPair = aMap.ExchNumToMapIndex(firdex);
		MNode& node = aMap.GetNode(firPair.first, firPair.second);
		int steps = CalStepsToStart(node, solveMap);
		if(node != startNode && node != endNode && aMap.Reacheable(node))
		{
			aMap.Draw(steps, firPair.first, firPair.second);
		}
	}
	refresh();
}



