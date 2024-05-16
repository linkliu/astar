#include <cstdlib>
#include<iostream>
#include<string>
#include<queue>
#include<curses.h>
#include"map.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::queue;

int main(int argc, char* argv[])
{
     Map map(41, 81);
     map.DrawMap();
    return EXIT_SUCCESS;
}
