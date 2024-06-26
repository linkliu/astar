#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H
#include<queue>
#include "map.h"
#include "mnode.h"
void BFS(Map& map, const MNode& startNode, const MNode& endNode);
void Dijkstra(const Map& map, const MNode& startNode, const MNode& endNode);
void AStar(const Map& map, const MNode& startNode, const MNode& endNode);

#endif
