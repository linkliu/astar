#ifndef _GBFS_ALGORITHM_H
#define _GBFS_ALGORITHM_H
#include "algorithm.h"
#include "map.h"
#include "mnode.h"
#include <ncurses.h>
#include <vector>
using std::map;
using std::vector;
class GBFSAlgorithm: public Algorithm
{
	public:
		GBFSAlgorithm() = default;
		GBFSAlgorithm(Map& _map):Algorithm(_map){}
		GBFSAlgorithm(Map& _map, MNode& _start, MNode& _end):Algorithm(_map, _start, _end){}
		map<int, int> Resolve() override;
		vector<int> FindPath(map<int, int>&) override;
		int Heuristic(const MNode&, const MNode&) const;
};
#endif
