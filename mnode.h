#ifndef _MNODE_H
#define _MNODE_H
#include <ncurses.h>

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

struct MNode
{
    int posy = 0;
    int posx = 0;
    char ch = 'o';
    ENodeType NType = ENodeType::PATH;
    ENodeState NState = ENodeState::NONE;
};
#endif
