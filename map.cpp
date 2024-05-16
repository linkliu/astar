#include"map.h"
#include <cmath>
#include <curses.h>
#include<ncurses.h>
#include<iostream>
using std::cout;

Map::~Map()
{
    if(mapPtr!=nullptr)
        delwin(mapPtr);
}

void Map::DrawMap()
{
    initscr();
    cout<<"_mapRow="<<_mapRow<<"_mapCol="<<_mapCol<<std::endl;
    int count = 0;
    for (int firdex = 0; firdex < _mapRow; firdex++) 
    {
        for (int secdex = 0 ; secdex < _mapCol; secdex++) 
        {
            move(firdex, secdex);
            int firMod = firdex%_nodeHeight;
            int secMod = secdex%_nodeWidth;
            if(firMod==0 && secMod==0)
            {
                addch('+');
                count+=1;
            }
            else if (firMod==0 && secMod!=0) 
            {
                addch('-');
            }
            else if (firMod!=0 && secMod==0)
            {
                addch('|');
            }
            else 
            {
                std::cout<<"count="<<secMod<<",";
                if(secMod == 1)
                {
                    addch(NumMap[std::round((count%1000)/100)]);
                }
                else if(secMod == 2)
                {
                    addch(NumMap[std::round((count%100)/10)]);
                }
                else if(secMod == 3)
                {
                    addch(NumMap[std::round(count%10)]);
                }
            }
        }
        std::cout<<std::endl;
    }
    refresh();
    getch();
    this->ClearMap();
}

void Map::ClearMap()
{
    endwin();
}
