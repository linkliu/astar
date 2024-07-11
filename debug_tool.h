#ifndef _DEBUG_TOOL_H
#define _DEBUG_TOOL_H

#include "map.h"
#include "mnode.h"
void print_map(Map& tMap);
const void print_map_path(const map<int, int>& _map, Map& tMap);
const void print_origin_map(const map<int, int>& _map);

#endif
