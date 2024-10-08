#include <asm-generic/errno.h>
#include <bits/types/struct_tm.h>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <string>
#include "dijstra_algorithm.h"
#include "map_config.h"
#include "mnode.h"
#include "map.h"
using std::cout;
using std::string;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    Map tMap(41, 81);
    cout<<"map size="<<tMap.Size();
    tMap.DrawMap();
    MNode startNode(3, 9);
    MNode endNode(10, 0);
	startNode.NTypeSetter(ENodeType::START);
	startNode.NStateSetter(ENodeState::NONE);
	endNode.NTypeSetter(ENodeType::END);
	endNode.NStateSetter(ENodeState::NONE);
    tMap.Draw(startNode, EDrawType::TYPE);
    tMap.Draw(endNode, EDrawType::TYPE);
	tMap.DrawTerrain(MapConfig::TerrainMap);
	DIJAlgorithm dij(tMap, startNode, endNode);
    map<int, int> bfsSolveMap = dij.Resolve();
    refresh();
    getch();
    tMap.ClearMap();
    return EXIT_SUCCESS;
}
