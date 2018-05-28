#ifndef SOLVEMAZEBYQUEUE_H_INCLUDED
#define SOLVEMAZEBYQUEUE_H_INCLUDED
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"

int AppendHeadSur(PCQ que,PMazeG pmg);//返回新加入的一层数据结点的头指针，不返回队列是否可以？————————————
PMazeN CheckQueHead(PCQ que, PMazeG pmg);
int SolveByQue(PMazeG pmg);


#endif // SOLVEMAZEBYQUEUE_H_INCLUDED
