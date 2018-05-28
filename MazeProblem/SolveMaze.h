#ifndef SOLVEMAZE_H_INCLUDED
#define SOLVEMAZE_H_INCLUDED

PCQ AddLevelSurround(PCQ que, PMazeG pmg, int rcd);
int AddNodeSurround(PCQ que,PMazeG pmg,PMazeN pmn,int i);//返回新加入的一层数据结点的头指针，不返回队列是否可以？————————————
PMazeN CheckOutLevel(PCQ que, int rcd, PMazeG pmg);
int Solve(PMazeG pmg);

#endif // SOLVEMAZE_H_INCLUDED
