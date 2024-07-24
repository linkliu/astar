#ifndef _ASTAR_ALGORITHM_H
#define _ASTAR_ALGORITHM_H
#include "algorithm.h"
#include "map.h"
class AStarAlgorithm : public Algorithm
{
	public:
		AStarAlgorithm() = default;
		AStarAlgorithm(Map& _map):Algorithm(_map){}
		AStarAlgorithm(Map& _map, MNode& _start, MNode& _end):Algorithm(_map, _start, _end){}
		void Resolve() override;
		void FindPath() override;
};
#endif
