#ifndef _MAP_CONFIG_H
#define _MAP_CONFIG_H
#include "mnode.h"
#include <list>
#include <map>
#include <utility>
using std::map;
using std::list;

class MapConfig
{
	public:
		static map<ENodeType, list<pair<int, int>>> TerrainMap;
		
};

#endif
