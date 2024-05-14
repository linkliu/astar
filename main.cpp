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
     Map map;
     map.DrawMap(10, 10);
    return EXIT_SUCCESS;
}
