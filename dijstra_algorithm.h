#ifndef _DIJ_ALGORITHM_H
#define _DIJ_ALGORITHM_H
#include "algorithm.h"
#include "map.h"
class DIJAlgorithm : public Algorithm
{
	public:
		DIJAlgorithm() = default;
		DIJAlgorithm(Map& _map):Algorithm(_map){}
		DIJAlgorithm(Map& _map, MNode& _start, MNode& _end):Algorithm(_map, _start, _end){}
		void Resolve() override;
		void FindPath() override;
};
#endif
