#include"mnode.h"
#include <curses.h>
#include<ncurses.h>

void MNode::draw(WINDOW* wnd)
{
    for (int firdex = 0; firdex < height; firdex++) 
    {
        for (int secdex = 0; secdex < width; secdex++) 
        {
            mvwaddch(wnd, firdex, secdex, 'o');
        }
    }
}
