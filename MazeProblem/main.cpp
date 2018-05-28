#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"
#include "Queue.h"
#include "SolveMaze.h"
#include "SolveMazeByQueue.h"

using namespace std;
int main()
{
    freopen("d:\\codefile\\datafile\\datainMaze.txt","r",stdin);
    //freopen("d:\\codefile\\datafile\\ShowMazeGraph.txt","w",stdout);
    PMazeG pm;
    pm=CreatMazeGraph(stdin);
    ShowMazeGraph(stdout,pm);

    printf("    起始坐标    (xb,yb):(%d,%d)\n",pm->xb,pm->yb);
    printf("    终点坐标    (xe,ye):(%d,%d)\n\n",pm->xe,pm->ye);

    if(SolveByQue(pm)==1)
    {
        ShowMazePath(stdout,pm);
    }
    else printf("    迷宫问题无解！\n");

    DeMazeGraph(pm);

    fclose(stdout);
    return 0;
}
