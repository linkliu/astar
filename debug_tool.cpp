#include "debug_tool.h"
#include "map.h"
#include "mnode.h"
#include <iostream>
using std::cout;
using std::endl;
void print_map(Map &tMap)
{
    for (int firdex = 0; firdex < tMap.GetMapRow(); firdex++) 
    {
        for (int secdex = 0; secdex < tMap.GetMapCol(); secdex++) 
        {
            MNode node = tMap.GetNode(secdex, firdex);
            cout<<node.NType<<",";
        }
        cout<<endl;
    }
}
