#include <chrono>
#include <clocale>
#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
#include<thread>
#include"map.h"
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
    /*for (int i = 0; i < map.Size(); i++) */
    /*{*/
        /*auto piPair = map.ExchNumToPosIndex(i);*/
        /*map.Draw(i, piPair.first, piPair.second);*/
        /*refresh();*/
        /*std::this_thread::sleep_for(std::chrono::milliseconds(50));*/
    /*}*/
    map.Draw("▨", 0, 0);
    map.Draw("▨", 19, 19);
    refresh();
    getch();
    map.ClearMap();
    return EXIT_SUCCESS;
}
