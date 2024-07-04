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
    MNode startNode(6, 4, "☉");
    MNode endNode(10, 19, "☢");
    //map.Draw("☉", 19, 0);
    //map.Draw("☢", 10, 19);
    tMap.Draw(startNode);
    tMap.Draw(endNode);
    //cout<<"path----------------------------------1"<<endl;
    //print_map(tMap);
    ConstructMap(tMap);
    //cout<<"path----------------------------------2"<<endl;
    refresh();
    BFS(tMap, startNode, endNode);
    //cout<<"path----------------------------------3"<<endl;
    getch();
    tMap.ClearMap();
    return EXIT_SUCCESS;
}
