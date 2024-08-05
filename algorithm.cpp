#include "algorithm.h"
#include "map.h"
#include "mnode.h"

Map& Algorithm::GetMap()
{
	return aMap;
}

MNode& Algorithm::GetStartNode()
{
	return startNode;
}

MNode& Algorithm::GetEndNode()
{
	return endNode;
}
