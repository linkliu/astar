#ifndef ASTAR_ALGORITHM_H
#define ASTAR_ALGORITHM_H
#include<queue>
#include <vector>
#include "map.h"
#include "mnode.h"
using std::vector;

void ConstructMap(Map& aMap);

void BFS(Map& aMap, const MNode& startNode, const MNode& endNode, map<int, int>&);
void FindBFSPath(const map<int, int>&, const MNode& startNode, const MNode& endNode, vector<int>&);
void Dijkstra(const Map& aMap, const MNode& startNode, const MNode& endNode);
void AStar(const Map& aMap, const MNode& startNode, const MNode& endNode);

#endif
