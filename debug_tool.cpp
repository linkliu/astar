#include "debug_tool.h"
#include "map.h"
#include "mnode.h"
#include <cstdlib>
#include <curses.h>
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
            cout<<node.NType<<"->"<<node.typeStr<<",";
        }
        cout<<endl;
    }
}

const void print_map_path(const map<int, int>& _map, Map& tMap, MNode& startNode, MNode&endNode)
{
    if(_map.size()<=0 || tMap.Size() <= 0)
    {
        cout<<"invalid path map or tMap!"<<endl;
        return;
    }
    //auto cp_fun = [](pair<int, int> &a, pair<int, int> &b) {
    //  return a.second < b.second;
    //};
    //vector<pair<int, int>> mVec;
    //for (pair<int, int> mPair : _map) {
    //    mVec.push_back(mPair);
    //}
    //std::sort(mVec.begin(), mVec.end(), cp_fun);
    //for (pair<int, int> vPair : mVec) {
    //    pair<int, int> firPair = tMap.ExchNumToMapIndex(vPair.first);
    //    pair<int, int> secPair = tMap.ExchNumToMapIndex(vPair.second);
    //    MNode &node1 = tMap.GetNode(firPair.first, firPair.second);
    //    MNode &node2 = tMap.GetNode(secPair.first, secPair.second);
    //    cout << "node:" << vPair.first << " in "
    //         << " node:" << vPair.second << "->" << node2.JudgeDir(node1)
    //         << endl;
    //}
    for (pair<int, int> mPair: _map) 
    {
        pair<int, int> firPair = tMap.ExchNumToMapIndex(mPair.first);
        pair<int, int> secPair = tMap.ExchNumToMapIndex(mPair.second);
        MNode& node1 = tMap.GetNode(firPair.first, firPair.second);
        MNode& node2 = tMap.GetNode(secPair.first, secPair.second);
		if(!node1.IsSamePos(startNode) && !node1.IsSamePos(endNode))
		{
			node1.NDirSetter(node1.JudgeDir(node2));
			tMap.Draw(node1, EDrawType::DIR);
		}
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
