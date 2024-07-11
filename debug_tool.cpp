#include "debug_tool.h"
#include "map.h"
#include "mnode.h"
#include <chrono>
#include <curses.h>
#include <iostream>
#include <thread>
using std::cout;
using std::endl;
void print_map(Map &tMap)
{
    for (int firdex = 0; firdex < tMap.GetMapRow(); firdex++) 
    {
        for (int secdex = 0; secdex < tMap.GetMapCol(); secdex++) 
        {
            MNode node = tMap.GetNode(secdex, firdex);
            cout<<node.NType<<"->"<<node.str<<",";
        }
        cout<<endl;
    }
}

const void print_map_path(const map<int, int>& _map, Map& tMap)
{
    if(_map.size()<=0 || tMap.Size() <= 0)
    {
        cout<<"invalid path map or tMap!"<<endl;
        return;
    }

    for (pair<int, int> mPair: _map) 
    {
        pair<int, int> firPair = tMap.ExchNumToMapIndex(mPair.first);
        pair<int, int> secPair = tMap.ExchNumToMapIndex(mPair.second);
        MNode& node1 = tMap.GetNode(firPair.first, firPair.second);
        MNode& node2 = tMap.GetNode(secPair.first, secPair.second);
        node1.NDirSetter(node1.JudgeDir(node2));
        tMap.Draw(node1);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //refresh();
    }

}

const void print_origin_map(const map<int, int> &_map)
{
    for (pair<int, int> mPair : _map) 
    {
        cout<<"("<<mPair.first<<","<<mPair.second<<"):"<< "|";
    }
    cout<<endl;
}
