#include"map.h"
#include "mnode.h"
#include <cmath>
#include <curses.h>
#include<iostream>
#include <list>
#include <ncurses.h>
#include<sstream>
#include <stdexcept>
#include <utility>
using std::cout;
using std::stringstream;
using std::endl;
using std::pair;
using std::make_pair;

Map::Map(int _row, int _col):_mapRow(_row), _mapCol(_col)
{
    _maxMapIndex_y = std::floor(_mapRow/_nodeHeight);
    _maxMapIndex_X = std::floor(_mapCol/_nodeWidth);
}

Map::~Map()
{
    if(mapPtr!=nullptr)
        delwin(mapPtr);
}

bool Map::isMapIndexValid(int my, int mx) const
{
    if(my>=0 && my<_maxMapIndex_y && mx>=0 && mx<_maxMapIndex_X)
    {
        return true;
    }
    else
    {
        stringstream ss;
        ss<<"invalid _mapIndex_Y:"<<my<<",_mapIndex_X:"<<mx;
        endwin();
        cout<<ss.str()<<std::endl;
        return false;
    }
}

bool Map::isNumValid(int num) const
{
    return num >= 0 && num < Size();
}

bool Map::NodeCheck(const MNode &node)
{
    return isMapIndexValid(node.mapIndex_Y, node.mapIndex_X);
}


void Map::DrawMap()
{
    initscr();
    cout<<"_mapRow="<<_mapRow<<"_mapCol="<<_mapCol<<std::endl;
    for (int firdex = 0; firdex < _mapRow; firdex++) 
    {
        for (int secdex = 0 ; secdex < _mapCol; secdex++) 
        {
            move(firdex, secdex);
            int firMod = firdex%_nodeHeight;
            int secMod = secdex%_nodeWidth;
            if(firdex==0 && secdex == 0)
            {
                printw("%s","┏");
            }
            else if(firdex == _mapRow -1 && secdex == 0)
            {
                printw("%s","┗");
            }
            else if(firdex == 0 && secdex == _mapCol - 1)
            {
                printw("%s", "┓");
            }
            else if(firdex == _mapRow - 1 && secdex == _mapCol - 1)
            {
                printw("%s", "┛");
            }
            else if(firdex == 0 && firMod == 0 && secMod == 0)
            {
                //addch('+');
                printw("%s","┬");
            }
            else if(secdex == 0 && firMod == 0 && secMod == 0)
            {
                printw("%s", "├");
            }
            else if(secdex == _mapCol -1 && firMod == 0 && secMod == 0)
            {
                printw("%s", "┤");
            }
            else if(firdex == _mapRow - 1 && firMod == 0 && secMod == 0)
            {
                printw("%s", "┴");
            }
            else if(firMod == 0 && secMod == 0)
            {
                printw("%s", "┼");
            }
            else if (firMod==0 && secMod!=0) 
            {
                //addch('-');
                printw("%s","─");
            }
            else if (firMod!=0 && secMod==0)
            {
                //addch('|');
                printw("%s","│");
            }
            else 
            {
                printw("%s"," ");
            }
        }
    }
    for (int i = 0; i < Size(); i++) 
    {
        pair<int, int> ipair = ExchNumToMapIndex(i); 
        MNode node = MNode(ipair.first, ipair.second, ENodeType::NORMAL, ENodeState::NONE);
        nodeMap.insert({i, node});
    }
    refresh();
}

void Map::ClearMap()
{
    endwin();
}

void Map::Draw(int num, int _mapIndex_Y, int _mapIndex_X)
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        if(std::abs(num) > 999)
        {
            cout<<"max number is 999"<<endl;
            return;
        }
        else 
        {
            int num1 = std::floor((num%1000)/100);
            int num2 = std::floor((num%100)/10);
            int num3 = num%10;
            int posy = _mapIndex_Y*_nodeHeight+1;
            int posx = _mapIndex_X*_nodeWidth;
            move(posy, posx+1);
            addch(NumMap[num1]);
            move(posy, posx+2);
            addch(NumMap[num2]);
            move(posy, posx+3);
            addch(NumMap[num3]);
        }
    }
    else 
    {
        stringstream ss;
        ss<<"invalid mapindexy:"<<_mapIndex_Y<<" or mapindexx:"<<_mapIndex_X;
        endwin();
        cout<<ss.str()<<std::endl;
    }
}

void Map::Draw(char ch, int _mapIndex_Y, int _mapIndex_X)
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        int posy = _mapIndex_Y*_nodeHeight+1;
        int posx = _mapIndex_X*_nodeWidth+2;
        move(posy, posx);
        addch(ch);
    }
}

void Map::Draw(const char* str, int _mapIndex_Y, int _mapIndex_X)
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        pair<int, int> mpPair = ExchMapIndexToPOS(_mapIndex_Y, _mapIndex_X);
        move(mpPair.first, mpPair.second);
        printw("%s", str);
    }
}

void Map::Draw(const MNode& node) const
{
    if(isMapIndexValid(node.mapIndex_Y, node.mapIndex_X))
    {
        pair<int, int> miPair = ExchMapIndexToPOS(node.mapIndex_Y, node.mapIndex_X);
        move(miPair.first, miPair.second);
        printw("%s", node.str.c_str());
    }
}

void Map::Draw(const list<MNode> & dlist) const 
{
    for (MNode node : dlist) 
    {
        Draw(node);
    }
}

int Map::Size() const
{
    return _maxMapIndex_X*_maxMapIndex_y;
}

pair<int, int> Map::ExchMapIndexToPOS(int _mapIndex_Y, int _mapIndex_X) const
{
    if (isMapIndexValid(_mapIndex_Y, _mapIndex_X)) 
    {
        int posy = _mapIndex_Y * _nodeHeight + 1;
        int posx = _mapIndex_X * _nodeWidth + 2;
        return make_pair(posy, posx);
    }
    else 
    {
        return make_pair(0, 0);
    }
}

pair<int, int> Map::ExchNumToMapIndex(int num) const
{
    if(isNumValid(num))
    {
        int mapIndex_Y = std::ceil(num/_maxMapIndex_X);
        int mapIndex_x = num%_maxMapIndex_X;
        return make_pair(mapIndex_Y, mapIndex_x);
    }
    else 
    {
        stringstream ss;
        ss<<"invalid exchange num:"<<num;
        endwin();
        cout<<ss.str()<<std::endl;
        return make_pair(0, 0);
    }
}

int Map::ExchMapIndexToNum(int _mapIndex_Y, int _mapIndex_X) const
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        return _mapIndex_Y*_maxMapIndex_X + _mapIndex_X;
    }
    else 
    {
        return -1;
    }
}

bool Reachable(MNode node)
{
    if((node.NType == ENodeType::NORMAL || node.NType == ENodeType::END ||
        node.NType == ENodeType::START))
    {
        return true;
    }
    return false;
}

const MNode& Map::GetNode(int _mapIndex_Y, int _mapIndex_X) const
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        int num = ExchMapIndexToNum(_mapIndex_Y, _mapIndex_X);
        auto getIt = nodeMap.find(num);
        if(getIt != nodeMap.cend())
        {
            return getIt->second; 
        }
        else 
        {
            throw std::domain_error(&"cant find num="[num]);
        }
    }
    else 
    {
        throw std::invalid_argument("invalid map index x,y");
    }
}

void Map::filterNeightbor(pair<int, int> &npair, list<MNode> & nlist)
{
    if(isMapIndexValid(npair.first, npair.second))
    {
        MNode node = GetNode(npair.first, npair.second);
        //node.NStateSetter(ENodeState::NEXT);
        nlist.push_back(node);
    }
}

list<MNode>& Map::GetNeighbors(const MNode& node, list<MNode>& neighborsList)
{
    if(!neighborsList.empty())
    {
        neighborsList.clear();
    }
    if(isMapIndexValid(node.mapIndex_Y, node.mapIndex_X) && Reachable(node))
    {
        neighborsList.push_back(node);
    }
    pair<int, int> mapIndexPiar = node.GetMapIndexYX();
    pair<int, int> leftPair = {mapIndexPiar.first, mapIndexPiar.second -1};
    pair<int, int> upPair = {mapIndexPiar.first -1, mapIndexPiar.second};
    pair<int, int> rightPair = {mapIndexPiar.first, mapIndexPiar.second + 1};
    pair<int, int> downPair = {mapIndexPiar.first + 1, mapIndexPiar.second};
    //LEFT
    filterNeightbor(leftPair, neighborsList);
    //UP
    filterNeightbor(upPair,neighborsList);
    //RIGHT
    filterNeightbor(rightPair, neighborsList);
    //DOWN
    filterNeightbor(downPair, neighborsList);
    return neighborsList;
}

