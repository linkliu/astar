#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H
#include<queue>
#include "map.h"
#include "mnode.h"

void ConstructMap(Map& aMap);

void BFS(Map& aMap, const MNode& startNode, const MNode& endNode, map<int, int>&);
void Dijkstra(const Map& aMap, const MNode& startNode, const MNode& endNode);
void AStar(const Map& aMap, const MNode& startNode, const MNode& endNode);

#endif
