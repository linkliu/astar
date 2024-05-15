#ifndef _MNODE_H
#define _MNODE_H
#include <ncurses.h>
struct MNode
{
    int map_index = 0;
    int height = 3;
    int width = 3;
    char ch = 'o';
    void draw(WINDOW* wnd);
};
#endif
