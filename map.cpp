#include"map.h"
#include "mnode.h"
#include <cmath>
#include<iostream>
#include <ncurses.h>
#include<sstream>
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

bool Map::isMapIndexValid(int my, int mx)
{
    if(my>=0 && my<_maxMapIndex_y && mx>=0 && mx<_maxMapIndex_X)
        return true;
    return false;
}

bool Map::NodeCheck(const MNode &node)
{
    return isMapIndexValid(node.posy, node.posx);
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
    else 
    {
        stringstream ss;
        ss<<"invalid mapindexy:"<<_mapIndex_Y<<" or mapindexx:"<<_mapIndex_X;
        endwin();
        cout<<ss.str()<<std::endl;
    }
}

void Map::Draw(const char* str, int _mapIndex_Y, int _mapIndex_X)
{
    if(isMapIndexValid(_mapIndex_Y, _mapIndex_X))
    {
        int posy = _mapIndex_Y*_nodeHeight+1;
        int posx = _mapIndex_X*_nodeWidth+2;
        move(posy, posx);
        printw("%s", str);
    }
    else 
    {
        stringstream ss;
        ss<<"invalid mapindexy:"<<_mapIndex_Y<<" or mapindexx:"<<_mapIndex_X;
        endwin();
        cout<<ss.str()<<std::endl;
    }
}

int Map::Size()
{
    return _maxMapIndex_X*_maxMapIndex_y;
}

pair<int, int> Map::ExchNumToPosIndex(int num)
{
    pair<int, int> rowColPair;
    if(num>=0 and num < Size())
    {
        int posy = std::ceil(num/_maxMapIndex_y);
        int posx = num%_maxMapIndex_y;
        return make_pair(posy, posx);
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

bool Reachable(MNode node)
{
    if((node.NType == ENodeType::PATH || node.NType == ENodeType::END ||
        node.NType == ENodeType::START) && (node.NState == ENodeState::FOUND))
    {
        return true;
    }
    return false;
}

list<MNode> Map::GetNeighbors(MNode node, list<MNode>& neighborsList)
{
    if(!neighborsList.empty())
    {
        neighborsList.clear();
    }
    if(isMapIndexValid(node.posy, node.posx) && Reachable(node))
    {
        neighborsList.push_back(node);
    }
    return neighborsList;
}

