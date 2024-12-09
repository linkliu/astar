#include "astar_algorithm.h"
#include <functional>
#include <queue>
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
    if(!aMap.NodeCheck(startNode) || !aMap.NodeCheck(endNode) || aMap.Size() < 0)
	{
		stringstream ss;
        ss<<"invalid start node:"<<startNode.ToString()<<" or end node:"<<endNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return solveMap;	
	}
    priority_queue<MNode, vector<MNode>, std::greater<MNode>> waveQueue;
	return solveMap;
}

vector<int> AStarAlgorithm::FindPath(map<int, int>& solveMap)
{
	return {};
}
