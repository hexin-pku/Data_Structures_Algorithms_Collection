#ifndef CROSSRIVER_H_INCLUDED
#define CROSSRIVER_H_INCLUDED
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"

bool side(int location, int movers);
bool safe(int location);
void TakeSolution(int location2, int location1, char* pstr);

#endif // CROSSRIVER_H_INCLUDED
