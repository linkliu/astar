#include <chrono>
#include <clocale>
#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
#include<thread>
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
    Map map(41, 81);
    cout<<"map size="<<map.Size();
    map.DrawMap();
    MNode startNode(9, 10, "☉");
    MNode endNode(10, 19, "☢");
    //map.Draw("☉", 19, 0);
    //map.Draw("☢", 10, 19);
    map.Draw(startNode);
    map.Draw(endNode);
    refresh();
    BFS(map, startNode, endNode);
    getch();
    map.ClearMap();
    return EXIT_SUCCESS;
}
