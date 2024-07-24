#ifndef _algorithm_h
#define _algorithm_h
#include "map.h"
#include "mnode.h"
#include <map>
class Algorithm
{
	private:
		Map aMap;
		MNode startNode;
		MNode endNode;

	public:
		Algorithm() = default;
		Algorithm(Map& _map):aMap(_map){}
		Algorithm(Map& _map, MNode& _start, MNode& _end):aMap(_map),startNode(_start), endNode(_end){}
		virtual void Resolve() = 0;
		virtual void FindPath() = 0;
		virtual ~Algorithm() = default;
		

};
#endif
