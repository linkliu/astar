#include "algorithm.h"
#include "map.h"
#include "mnode.h"

Map& Algorithm::GetMap()
{
	return aMap;
}

const MNode& Algorithm::GetStartNode() const
{
	return startNode;
}

const MNode& Algorithm::GetEndNode() const
{
	return endNode;
}
