#ifndef _MNODE_H
#define _MNODE_H
#include <map>
#include <ncurses.h>
#include <sstream>
#include <ostream>
#include <string>
#include <utility>
using std::string;
using std::stringstream;
using std::endl;
using std::ostream;
using std::map;
using std::pair;



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

struct MNode
{
    map<ENodeState, string> NodePicMap = 
    {
        {ENodeState::NONE," "},
        {ENodeState::FOUND,"☒"},
        {ENodeState::FINDDING,"☆"},
        {ENodeState::NEXT,"★"},
    };
    int mapIndex_Y = 0;
    int mapIndex_X = 0;
    int index = 0;
    string str = "";
    ENodeType NType = ENodeType::NORMAL;
    ENodeState NState = ENodeState::NONE;
    
    MNode() = default;
    MNode(int _mapY, int _mapX, string _str):mapIndex_Y(_mapY), mapIndex_X(_mapX), str(_str)
    {
    }
    MNode(int _mapY, int _mapX, ENodeType _type, ENodeState _state):
        mapIndex_Y(_mapY), 
        mapIndex_X(_mapX), 
        NType(_type),
        NState(_state)
    {
        NStateSetter(_state);
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

    void NtypeSetter(const ENodeType ntype)
    {
        NType = ntype;
    }

    void NStateSetter(const ENodeState nstate)
    {
        NState = nstate;
        str = NodePicMap[nstate];
    }

    pair<int, int> GetMapIndexYX() const
    {
        return std::make_pair(mapIndex_Y, mapIndex_Y);
    }
};
#endif
