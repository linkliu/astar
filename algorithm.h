#ifndef _algorithm_h
#define _algorithm_h
#include "map.h"
#include "mnode.h"
#include <map>
#include <vector>
class Algorithm
{
	private:
		Map aMap;
		MNode startNode;
		MNode endNode;

	protected:
		Map& GetMap();
		MNode& GetStartNode();
		MNode& GetEndNode();

	public:
		Algorithm() = default;
		Algorithm(Map& _map):aMap(_map){}
		Algorithm(Map& _map, MNode& _start, MNode& _end):aMap(_map),startNode(_start), endNode(_end){}
		virtual map<int, int> Resolve() = 0;
		virtual std::vector<int> FindPath(map<int, int>&) = 0;
		virtual ~Algorithm() = default;
		

};
#endif
