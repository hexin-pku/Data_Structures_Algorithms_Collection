#include "MazeGraph.h"
#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define QMAXNUM 50;
typedef struct CQueue
{
	PMazeN cque;
	int M;
	int f, r;
	int stat;
}CQ, *PCQ;

PCQ CreatEmptyCQ(int M);
bool IsEmptyQueue(PCQ que);
bool IsFullQueue(PCQ que);
PCQ AddToQueue(PCQ que,MazeN mzn);
PCQ PopQueue(PCQ que);
PMazeN GetheadQueue(PCQ que);
int ShowQueue(PCQ que);
int ShowQueueRcd(PCQ que, int rcd);

#endif // QUEUE_H_INCLUDED
