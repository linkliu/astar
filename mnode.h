#ifndef _MNODE_H
#define _MNODE_H
#include <ncurses.h>
#include <sstream>
#include <ostream>
#include <string>
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;



enum class ENodeType
{
    NONE,
    PATH,
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

inline ostream& operator<<(ostream&os, ENodeType nodeType)
{
    switch (nodeType) 
    { 
        case ENodeType::BARRIER: return os<<"BARRIER";
        case ENodeType::PATH: return os<<"PATH";
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
struct MNode
{
    int mapIndex_Y = 0;
    int mapIndex_X = 0;
    int index = 0;
    string str = "";
    ENodeType NType = ENodeType::PATH;
    ENodeState NState = ENodeState::NONE;
    MNode() = default;
    MNode(int _mapY, int _mapX, string _str):mapIndex_Y(_mapY), mapIndex_X(_mapX), str(_str)
    {
    }

    string ToString() const
    {
        stringstream ss;
        ss<<"posy:"<<mapIndex_Y<<",posx:"<<mapIndex_X<<",NType:"<<NType<<",NState:"<<NState<<endl;
        ss<<"str:"<<str<<endl;
        return ss.str();
    }
    bool IsSamePos(const MNode node) const
    {
        return mapIndex_Y == node.mapIndex_Y && mapIndex_X == node.mapIndex_X;
    }
};
#endif
