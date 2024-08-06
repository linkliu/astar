#ifndef _ASTAR_ALGORITHM_H
#define _ASTAR_ALGORITHM_H
#include "algorithm.h"
#include "map.h"
#include <map>
#include <vector>
using std::vector;
using std::map;

class AStarAlgorithm : public Algorithm
{
	public:
		AStarAlgorithm() = default;
		AStarAlgorithm(Map& _map):Algorithm(_map){}
		AStarAlgorithm(Map& _map, MNode& _start, MNode& _end):Algorithm(_map, _start, _end){}
		map<int, int> Resolve() override;
		vector<int> FindPath() override;
};
#endif
