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
    RIGHT,
    UP,
    DOWN,
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
    {EDir::RIGHT, "⇨"},
    {EDir::UP, "⇧"},
    {EDir::DOWN, "⇩"},
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
    
    MNode() = default;
    MNode(int _mapY, int _mapX):mapIndex_Y(_mapY), mapIndex_X(_mapX){}
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

    void NTypeSetter(ENodeType ntype)
    {
        NType = ntype;
        typeStr = NTStrMap[ntype];
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

    pair<int, int> GetMapIndexYX() const
    {
        return std::make_pair(mapIndex_Y, mapIndex_X);
    }

    EDir JudgeDir(const MNode& other) const
    {
        pair<int, int> selfPair = GetMapIndexYX();
        pair<int, int> otherPair = other.GetMapIndexYX();
        if(selfPair.first == otherPair.first)
        {
            if(selfPair.second < otherPair.second) 
            {
                return EDir::RIGHT;
            }
            else
            {
                return EDir::LEFT;
            }
        }
        if(selfPair.second == otherPair.second)
        {
            if(selfPair.first < otherPair.first)
            {
                return EDir::DOWN;
            }
            else 
            {
                return EDir::UP;
            }
        }
        return EDir::NONE;
    }
};
#endif
