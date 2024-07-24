#include <asm-generic/errno.h>
#include <bits/types/struct_tm.h>
#include <chrono>
#include <clocale>
#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
#include<thread>
#include "debug_tool.h"
#include "mnode.h"
#include"map.h"
#include "astar_algorithm.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    Map tMap(41, 81);
    cout<<"map size="<<tMap.Size();
    tMap.DrawMap();
    MNode startNode(3, 9);
    MNode endNode(10, 19);
	startNode.NTypeSetter(ENodeType::START);
	startNode.NStateSetter(ENodeState::NONE);
	endNode.NTypeSetter(ENodeType::END);
	endNode.NStateSetter(ENodeState::NONE);
    tMap.Draw(startNode, EDrawType::TYPE);
    tMap.Draw(endNode, EDrawType::TYPE);
    ConstructMap(tMap);
    refresh();
    map<int, int> originMap;
    BFS(tMap, startNode, endNode, originMap);
    refresh();
    getch();
    tMap.ClearMap();
    return EXIT_SUCCESS;
}
