#include <chrono>
#include <clocale>
#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
#include<thread>
#include"map.h"
#include "mnode.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    Map map(41, 81);
    cout<<"map size="<<map.Size();
    map.DrawMap();
    //MNode startNode(19, 0, "☉");
    //MNode endNode(10, 19, "☢");
    map.Draw("☉", 19, 0);
    map.Draw("☢", 10, 19);
    refresh();
    getch();
    map.ClearMap();
    return EXIT_SUCCESS;
}
