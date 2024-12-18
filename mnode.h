#ifndef _MNODE_H
#define _MNODE_H
#include <map>
#include <ncurses.h>
#include <sstream>
#include <iostream>
#include <string>
#include <utility>
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;
using std::map;
using std::pair;
using std::cout;

enum class EDir
{
    NONE,
    LEFT,
    LEFT_UP,
    UP,
    RIGHT_UP,
    RIGHT,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN,
};

enum class ENodeType
{
    NONE,
    NORMAL,
    BARRIER,
    WATER,
    START,
    END,
};

enum class ENodeState
{
    NONE,
    FOUND,
    FINDDING,
    NEXT,
};

enum class EDrawType 
{
	NONE,
	STATE,
	TYPE,
	DIR,
};

static map<ENodeState, string> NSStrMap = 
{
    {ENodeState::NONE, " "},
    {ENodeState::FOUND, "☒"},
    {ENodeState::FINDDING, "☆"},
    {ENodeState::NEXT, "★"},
};

static map<ENodeType, string> NTStrMap = {
    {ENodeType::NONE, " "}, 
    {ENodeType::NORMAL, " "},
    {ENodeType::BARRIER, "▇"}, 
    {ENodeType::WATER, "⁜"},
    {ENodeType::START, "☉"},   
    {ENodeType::END, "☢"},
};

static map<EDir, string> NDirStrMap = 
{
    {EDir::NONE, "↺"},
    {EDir::LEFT, "⇦"},
    {EDir::LEFT_UP, "⇖"},
    {EDir::UP, "⇧"},
    {EDir::RIGHT_UP, "⇗"},
    {EDir::RIGHT, "⇨"},
    {EDir::RIGHT_DOWN, "⇘"},
    {EDir::DOWN, "⇩"},
    {EDir::LEFT_DOWN, "⇙"},
};

static map<ENodeType, int> NCostMap = 
{
	{ENodeType::NONE, 1},
	{ENodeType::NORMAL, 2},
	{ENodeType::START, 2},
	{ENodeType::END, 2},
	{ENodeType::WATER, 10},
	{ENodeType::BARRIER, 10},

};

inline ostream& operator<<(ostream&os, ENodeType nodeType)
{
    switch (nodeType) 
    { 
        case ENodeType::BARRIER: return os<<"BARRIER";
        case ENodeType::NORMAL: return os<<"NORMAL";
        case ENodeType::NONE: return os<<"NONE";
        case ENodeType::WATER: return os<<"WATER";
        case ENodeType::START: return os<<"START";
        case ENodeType::END: return os<<"END";
        default: return os<<"Unknow node type";
    }
}

inline ostream& operator<<(ostream&os, ENodeState nodeState)
{
    switch (nodeState) 
    { 
        case ENodeState::NONE: return os<<"NONE";
        case ENodeState::FOUND: return os<<"FOUND";
        case ENodeState::FINDDING: return os<<"FINDDING";
        case ENodeState::NEXT: return os<<"NEXT";
        default: return os<<"Unknow node state";
    }
}

inline ostream& operator<<(ostream&os, EDir dir)
{
    switch (dir) 
    {
        case EDir::LEFT: return os<<"left";
        case EDir::RIGHT: return os<<"right";
        case EDir::UP: return os<<"up";
        case EDir::DOWN: return os<<"down";
        default:return os<<"Unknow dir type";
    }
}

struct MNode
{
    int mapIndex_Y = 0;
    int mapIndex_X = 0;
    int index = 0;
    string stateStr = "";
	string typeStr = "";
	string dirStr = "";
    ENodeType NType = ENodeType::NORMAL;
    ENodeState NState = ENodeState::NONE;
    EDir NDir = EDir::NONE;
	int nodeCost = 0;
	int curCost = 0;
    int meetIndex = 0;
    int heCost = 0;
    
    MNode() = default;
    MNode(int _mapY, int _mapX):mapIndex_Y(_mapY), mapIndex_X(_mapX){}
	MNode(const MNode&) = default;
	MNode& operator=(const MNode&) = default;
	MNode(MNode&& other)noexcept:mapIndex_Y(other.mapIndex_Y), mapIndex_X(other.mapIndex_X),nodeCost(other.nodeCost),
		index(other.index), stateStr(other.stateStr), typeStr(other.typeStr), curCost(other.curCost),meetIndex(other.meetIndex),heCost(other.heCost),
		dirStr(other.dirStr),NType(other.NType),NState(other.NState),NDir(other.NDir){}
	MNode& operator=(MNode&&other)noexcept
	{
		if(this != &other)
		{
			mapIndex_Y = other.mapIndex_Y;
			mapIndex_X = other.mapIndex_X;
			index = other.index;
            nodeCost = other.nodeCost;
			curCost = other.curCost;
            heCost = other.heCost;
			stateStr = other.stateStr;
			typeStr = other.typeStr;
			dirStr = other.dirStr;
			NType = other.NType;
			NState = other.NState;
			NDir = other.NDir;
            meetIndex = other.meetIndex;
		}
		return *this;
	}

    string ToString() const
    {
        stringstream ss;
        ss<<"posy:"<<mapIndex_Y<<",posx:"<<mapIndex_X<<",NType:"<<NType<<",NState:"<<NState<<",NDir="<<NDir<<endl;
        ss<<"stateStr:"<<stateStr<<",typeStr:"<<typeStr<<",dirStr:"<<dirStr<<endl;
        return ss.str();
    }

    bool IsSamePos(const MNode& node) const
    {
        return mapIndex_Y == node.mapIndex_Y && mapIndex_X == node.mapIndex_X;
    }

	bool operator==(const MNode& node) const
	{
		return mapIndex_Y==node.mapIndex_Y && mapIndex_X==node.mapIndex_X;
	}

	bool operator!=(const MNode& node) const
	{
		return !(*this == node);
	}

	bool operator<(const MNode& node) const
	{
        return heCost < node.heCost;
	}

	bool operator>(const MNode& node) const
	{
		return heCost > node.heCost;
	}

    bool operator<=(const MNode& node) const
	{
        return heCost <= node.heCost;
	}

	bool operator>=(const MNode& node) const
	{
		return heCost >= node.heCost;
	}

    void NTypeSetter(ENodeType ntype)
    {
        NType = ntype;
        typeStr = NTStrMap[ntype];
		nodeCost = NCostMap[NType];
    }

    void NStateSetter(ENodeState nstate)
    {
        NState = nstate;
        stateStr = NSStrMap[nstate];
    }

    void NDirSetter(const EDir dir)
    {
        NDir = dir;
        dirStr = NDirStrMap[dir];
    }

	void CurCostSetter(int cost)
	{
		curCost = cost;
	}

    void CurHeCostSetter(int cost)
    {
        heCost = cost;
    }

    void MISetter(int index)
    {
        meetIndex = index;
    }

    pair<int, int> GetMapIndexYX() const
    {
        return std::make_pair(mapIndex_Y, mapIndex_X);
    }

    EDir JudgeDir(const MNode& other) const
    {
        pair<int, int> selfPair = GetMapIndexYX();
        pair<int, int> otherPair = other.GetMapIndexYX();
        int yDir = selfPair.first - otherPair.first;
        int xDir = selfPair.second - otherPair.second;
        switch (yDir + xDir)
        {
            case -2:
                return EDir::LEFT_UP;
            case 2:
                return EDir::RIGHT_DOWN;
            case 0:
                if(yDir == -1) return EDir::RIGHT_UP;
                else return EDir::LEFT_DOWN;
            case -1:
                if(yDir == -1) return EDir::UP;
                else return EDir::LEFT;
            case 1:
                if(yDir == 1) return EDir::DOWN;
                else return EDir::RIGHT;
        default:
            return EDir::NONE;
        }
    }
};
#endif
