#include "map.h"
#include "mnode.h"
#include <chrono>
#include <cmath>
#include <curses.h>
#include <iostream>
#include <map>
#include <ncurses.h>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>
using std::cout;
using std::stringstream;
using std::endl;
using std::pair;
using std::make_pair;

Map::Map(int _row, int _col):_mapRow(_row), _mapCol(_col)
{
    _maxMapIndex_Y = std::floor(_mapRow/_nodeHeight);
    _maxMapIndex_X = std::floor(_mapCol/_nodeWidth);
}

Map::~Map()
{
    if(mapPtr!=nullptr)
        delwin(mapPtr);
}

Map::Map(Map&& oriRef)noexcept:_mapRow(oriRef._mapRow),_mapCol(oriRef._mapCol),
	_nodeWidth(oriRef._nodeWidth),_nodeHeight(oriRef._nodeHeight),
	_maxMapIndex_Y(oriRef._maxMapIndex_Y),_maxMapIndex_X(oriRef._maxMapIndex_X),
	mapPtr(std::move(oriRef.mapPtr)),nodeMap(std::move(oriRef.nodeMap)),NumMap(std::move(oriRef.NumMap))
{
}

Map& Map::operator=(Map&& other)noexcept
{
	if(this!=&other)
	{
		mapPtr = std::move(other.mapPtr);
		nodeMap = std::move(other.nodeMap);
		NumMap = std::move(other.NumMap);
		_mapRow = other._mapRow;
		_mapCol = other._mapCol;
		_nodeWidth = other._nodeWidth;
		_nodeHeight = other._nodeHeight;
		_maxMapIndex_Y = other._maxMapIndex_Y;
		_maxMapIndex_X = other._maxMapIndex_X;
		other.mapPtr = nullptr;
		nodeMap.clear();
		NumMap.clear();
	}
	return *this;
}

bool Map::isMapIndexValid(int my, int mx) const
{
    if(my>=0 && my<_maxMapIndex_Y && mx>=0 && mx<_maxMapIndex_X)
    {
        return true;
    }
    else
    {
        //stringstream ss;
        //ss<<"invalid _mapIndex_Y:"<<my<<",_mapIndex_X:"<<mx;
        //endwin();
        //cout<<ss.str()<<std::endl;
        return false;
    }
}

bool Map::isNumValid(int num) const
{
    return num >= 0 && num < Size();
}

bool Map::NodeCheck(const MNode &node) const
{
    return isMapIndexValid(node.mapIndex_Y, node.mapIndex_X);
}

void Map::drawGrid(int _row, int _col)
{
    initscr();
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

void Map::GenTerrain(const map<ENodeType, list<pair<int, int>>> &TerrainMap) 
{
    if (Size() > 0) 
	{
        // generate map by terrain data
        for (pair<ENodeType, list<pair<int, int>>> tPair : TerrainMap) 
		{
            for (pair<int, int> ePair : tPair.second) 
			{
				MNode& node = GetNode(ePair.first, ePair.second);
				node.NTypeSetter(tPair.first);
				Draw(node, EDrawType::TYPE);
            }
        }
    }
}

void Map::buildNodes(map<int, MNode>& nMap)
{
    for (int i = 0; i < Size(); i++) 
    {
        pair<int, int> ipair = ExchNumToMapIndex(i); 
        MNode node = MNode(ipair.first, ipair.second);
		node.NTypeSetter(ENodeType::NORMAL);
		node.NStateSetter(ENodeState::NONE);
        node.index = i;
        nodeMap.insert({i, node});
    }
}

void Map::DrawMap()
{
    cout<<"_mapRow="<<_mapRow<<"_mapCol="<<_mapCol<<std::endl;
    drawGrid(_mapRow, _mapCol);
    buildNodes(nodeMap);
}

void Map::ClearMap()
{
    endwin();
}

void Map::ClearNode(const MNode& node)
{
    if(isMapIndexValid(node.mapIndex_Y, node.mapIndex_X))
    {
        pair<int, int> miPair = ExchMapIndexToPOS(node.mapIndex_Y, node.mapIndex_X);
        move(miPair.first, miPair.second-1);
        printw("%s", " ");
        move(miPair.first, miPair.second);
        printw("%s", " ");
        move(miPair.first, miPair.second+1);
        printw("%s", " ");
    }
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

void Map::Draw(const MNode& node, EDrawType dType) const
{
    if(isMapIndexValid(node.mapIndex_Y, node.mapIndex_X))
    {
        pair<int, int> miPair = ExchMapIndexToPOS(node.mapIndex_Y, node.mapIndex_X);
        move(miPair.first, miPair.second);
		switch (dType) 
		{
			case EDrawType::STATE:
				printw("%s", node.stateStr.c_str());
				break;
			case EDrawType::TYPE:
				printw("%s", node.typeStr.c_str());
				break;
			case EDrawType::DIR:
				printw("%s", node.dirStr.c_str());
				break;
			default:
				printw("%s", "er");

		}
    }
}

void Map::Draw(const list<MNode> & dlist, EDrawType dType) const 
{
    for (MNode node : dlist) 
    {
        Draw(node, dType);
    }
}

int Map::Size() const
{
    return _maxMapIndex_X*_maxMapIndex_Y;
}

const int Map::GetNodeNum(const MNode &node) const
{
    return ExchMapIndexToNum(node.mapIndex_Y, node.mapIndex_X);
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

bool Map::isReachable(const MNode &node) const 
{

    if ((node.NType == ENodeType::NORMAL || node.NType == ENodeType::END ||
         node.NType == ENodeType::START)) 
    {
        return true;
    }
    return false;
}

bool Map::Reacheable(const MNode& node) const
{
	return isReachable(node);
}

MNode& Map::GetNode(int _mapIndex_Y, int _mapIndex_X)
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
        if(isReachable(node))
        {
            //node.NStateSetter(ENodeState::NEXT);
            nlist.push_back(node);
        }
    }
}

list<pair<int, int>> Map::enumsNeighbors(const MNode& node)
{
	list<pair<int, int>> pairList;
	pair<int, int> nPair = node.GetMapIndexYX();
	//LEFT
	pairList.push_back({nPair.first, nPair.second-1});
    //LEFT_UP
	// pairList.push_back({nPair.first-1, nPair.second-1});
	//UP
	pairList.push_back({nPair.first-1, nPair.second});
    //RIGHT_UP
	// pairList.push_back({nPair.first-1, nPair.second+1});
	//RIGHT
	pairList.push_back({nPair.first, nPair.second+1});
    //RIGHT_DOWN
	// pairList.push_back({nPair.first+1, nPair.second+1});
	//DOWN
	pairList.push_back({nPair.first+1, nPair.second});
    //LEFT_DOWN
	// pairList.push_back({nPair.first+1, nPair.second-1});
	return pairList;
}

list<MNode> Map::GetFilterNeighbors(const MNode& node)
{
	list<MNode> neighborsList;
	list<pair<int, int>> pairList = enumsNeighbors(node);
	for (pair<int, int> mPair : pairList) 
	{
		filterNeightbor(mPair, neighborsList);
	}
    return neighborsList;
}

list<MNode> Map::GetNeighbors(const MNode& node)
{
	list<MNode> neighborsList;
    list<pair<int, int>> pairList = enumsNeighbors(node);
	for (pair<int, int> mPair : pairList) 
	{
		if(isMapIndexValid(mPair.first, mPair.second))
		{
			neighborsList.push_back(GetNode(mPair.first, mPair.second));
		}
	}
    return neighborsList;
}

//绘制地形
void Map::DrawTerrain(const map<ENodeType, list<pair<int, int>>>& terMap)
{
	if(Size() > 0 && terMap.size()>0)
	{
		for (pair<ENodeType, list<pair<int, int>>> firPair : terMap) 
		{
			ENodeType &nType = firPair.first;
			list<pair<int, int>>& typeList = firPair.second;
			for (pair<int, int> secPair : typeList) 
			{
				MNode& terNode = GetNode(secPair.first, secPair.second);
				terNode.NTypeSetter(nType);
				Draw(terNode, EDrawType::TYPE);
			}
		}
		refresh();
	}
}
//绘制检测来源
void Map::DrawOriginPath(const map<int, int>& oriMap, const MNode& startNode, const MNode& endNode)
{
	if(oriMap.size()<=0 || Size()<=0)
	{
		cout<<"invalid origin map or Map!"<<endl;
		return;
	}
	for (pair<int, int> mPair : oriMap) 
	{
		pair<int, int> firPair = ExchNumToMapIndex(mPair.first);
		pair<int, int> secPair = ExchNumToMapIndex(mPair.second);
		MNode& node1 = GetNode(firPair.first, firPair.second);
		MNode& node2 = GetNode(secPair.first, secPair.second);
		if(node1!=startNode && node1!=endNode)
		{
			node1.NDirSetter(node1.JudgeDir(node2));
			Draw(node1, EDrawType::DIR);
		}
	}
}

//绘制最终路径
void Map::DrawFinalPath(const vector<int>& pathVec, const MNode& startNode, const MNode& endNode)
{
	if(pathVec.size()<=0 || Size()<=0)
	{
		cout<<"invalid pathVec or Map"<<endl;
		return;
	}
	for (auto np = pathVec.begin(); np != pathVec.end() - 1; np++) 
	{
		pair<int, int> firPair = ExchNumToMapIndex(*np);
		pair<int, int> secPair = ExchNumToMapIndex(*(np+1));
		MNode& node1 = GetNode(firPair.first, firPair.second);
		MNode& node2 = GetNode(secPair.first, secPair.second);
		node1.NDirSetter(node2.JudgeDir(node1));
		if(node1!=endNode)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
            ClearNode(node1);
			Draw(node1, EDrawType::DIR);
			refresh();
		}
	}
}


