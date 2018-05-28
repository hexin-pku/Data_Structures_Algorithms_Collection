#ifndef MAZEGRAPH_H_INCLUDED
#define MAZEGRAPH_H_INCLUDED

typedef struct MazeNode
{
    int wll;//'0','1','b','e'
    int x,y;
    int been;//
    int dirc[4];//directions，0表示没有走过，1表示走过，-1表示上一级结点的方向
}MazeN, *PMazeN;

typedef struct MazeGraph
{
    int M;//行数
    int N;//列数
    int A;
    int xb,yb;//迷宫起点
    int xe,ye;//迷宫终点
    int solve;
    PMazeN maze;
}MazeG, *PMazeG;

PMazeG CreatMazeGraph(FILE* fin);
void DeMazeGraph(PMazeG pm);
int ShowMazeGraph(FILE* fout, PMazeG pm);
int SurroundBeen(PMazeG pmg,PMazeN pmn, int i);
int ShowMazeBeen(FILE* fout, PMazeG pm);
int ShowMazePath(FILE* fin, PMazeG pmg);
int ShowMazeDircFrom(FILE* fout, PMazeG pmg);

#endif // MAZEGRAPH_H_INCLUDED
