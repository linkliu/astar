#include "bfs_algorithm.h"
#include "mnode.h"
#include <map>
#include <vector>

map<int, int> BFSAlgorithm::Resolve()
{
	Map& aMap = GetMap();
	MNode& sNode = GetStartNode();
	MNode& eNode = GetEndNode();
	map<int, int> ori_map;
	if(!aMap.NodeCheck(sNode) || !aMap.NodeCheck(eNode) || aMap.Size() < 0)
	{
		stringstream ss;
        ss<<"invalid start node:"<<sNode.ToString()<<" or end node:"<<eNode.ToString()<<endl;
        cout<<ss.str();
        endwin();
        return ori_map;	
	}

	return ori_map;
}


vector<int> BFSAlgorithm::FindPath()
{
	vector<int> pathVec;
	return pathVec;
}

