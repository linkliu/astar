#ifndef _BFS_ALGORITHM_H
#define _BFS_ALGORITHM_H
#include "algorithm.h"
#include "map.h"
class BFSAlgorithm : public Algorithm
{
	public:
		BFSAlgorithm() = default;
		BFSAlgorithm(Map& _map):Algorithm(_map){}
		BFSAlgorithm(Map& _map, MNode& _start, MNode& _end):Algorithm(_map, _start, _end){}
		void Resolve() override;
		void FindPath() override;
};
#endif
