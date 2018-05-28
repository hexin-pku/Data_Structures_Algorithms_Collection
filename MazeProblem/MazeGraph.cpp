#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "MazeGraph.h"//定义了迷宫图结构

using namespace std;
PMazeG CreatMazeGraph(FILE* fin)//fin是数据文件
{
    int m,n;
    fscanf(fin,"%d",&m);
    fscanf(fin,"%d",&n);
    PMazeG pm=(PMazeG)malloc(sizeof(MazeG));
    pm->xb=0; pm->xe=0;
    pm->yb=0; pm->ye=0;
    pm->M=m;
    pm->N=n;
    pm->A=0;
    pm->solve=0;

    pm->maze=(PMazeN)malloc((m*n)*sizeof(MazeN));//给图元素分配空间
    for(int i=0;i<pm->M;i++)
    {
        for(int j=0;j<pm->N;j++)
        {
            //ShowMazeGraph(stdout,pm);
            //printf("\n");
            int tmp;
            fscanf(fin,"%d",&tmp);
            if(pm->A >= (pm->M)*(pm->N))break;
            (pm->maze+pm->N*i+j)->wll=tmp;
            pm->A++;
            (pm->maze+pm->N*i+j)->x=i;
            (pm->maze+pm->N*i+j)->y=j;
            if((pm->maze+pm->N*i+j)->wll==2)
            {
                pm->xb=i;
                pm->yb=j;
            }
            if((pm->maze+pm->N*i+j)->wll==3)
            {
                pm->xe=i;
                pm->ye=j;
            }
            if((pm->maze+pm->N*i+j)->wll==1 || (pm->maze+pm->N*i+j)->wll==2)
                (pm->maze+pm->N*i+j)->been=1;//整数记录步数表示在栈中，0表示没进过栈，-1表示被退过栈
            else (pm->maze+pm->N*i+j)->been=0;
            for(int k=0;k<4;k++)(pm->maze+pm->N*i+j)->dirc[k]=0;//0123分别表示东南西北，0表示方向都还没有探索，1表示探索过了，-1表示退栈方向
        }
        //ShowMazeGraph(stdout,pm);
        //printf("\n");
    }
    return pm;
}

void DeMazeGraph(PMazeG pm)
{
    free(pm->maze);
    free(pm);pm=NULL;
}

int ShowMazeGraph(FILE* fout, PMazeG pm)
{
    printf("--------------迷宫信息的显示-------------\n");
    printf("迷宫信息：\n    行数=%d      列数=%d\n    起点=b       终点=e\n\n",pm->M,pm->N);
    for(int i=0;i<pm->M;i++)
    {
        printf("    ");
        for(int j=0;j<pm->N;j++)
        {
            if((pm->maze+pm->N*i+j)->wll==1)printf("# ");
            else if((pm->maze+pm->N*i+j)->wll==0)printf("  ");
            else if((pm->maze+pm->N*i+j)->wll==2)printf("b ");
            else if((pm->maze+pm->N*i+j)->wll==3)printf("e ");
            else if((pm->maze+pm->N*i+j)->wll==9)printf("+ ");
            else printf("? ");//,(pm->maze+pm->N*i+j)->wll);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    if(pm->solve==1)return 1;
    else return 0;
}

int SurroundBeen(PMazeG pmg,PMazeN pmn, int i)//返回一个结点的某个方向的结点占据情况
{
    if(i==0)
    {
        if((pmg->maze+pmg->N*pmn->x+pmn->y+1)->been==0)return 0;//0表示没有走过
        else return 1;
    }
    if(i==1)
    {
        if((pmg->maze+pmg->N*(pmn->x+1)+pmn->y)->been==0)return 0;
        else return 1;
    }
    if(i==2)
    {
        if((pmg->maze+pmg->N*pmn->x+pmn->y-1)->been==0)return 0;
        else return 1;
    }
    if(i==3)
    {
        if((pmg->maze+pmg->N*(pmn->x-1)+pmn->y)->been==0)return 0;
        else return 1;
    }
    return 1;//????
}

int ShowMazeBeen(FILE* fout, PMazeG pm)
{
    printf("-------------迷宫探索进程更新------------\n");
    printf("迷宫信息：\n    行数=%d      列数=%d\n    起点=b       终点=e\n\n",pm->M,pm->N);
    for(int i=0;i<pm->M;i++)
    {
        printf("    ");
        for(int j=0;j<pm->N;j++)
        {
            if((pm->maze+pm->N*i+j)->wll==1) printf("# ");
            else if((pm->maze+pm->N*i+j)->wll==2) printf("b ");
            else if((pm->maze+pm->N*i+j)->wll==3) printf("# ");
            else if((pm->maze+pm->N*i+j)->been==1)printf("+ ");
            else if((pm->maze+pm->N*i+j)->been==0)printf("  ");
            else printf("? ");//,(pm->maze+pm->N*i+j)->been);
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
    if(pm->solve==1)return 1;
    else return 0;
}

int ShowMazePath(FILE* fin, PMazeG pmg)
{
    int x=pmg->xe;
    int y=pmg->ye;
    while(x!=pmg->xb || y!=pmg->yb)
    {
        int k=0;
        for(;k<4;k++)
        {
            if((pmg->maze+pmg->N*x+y)->dirc[k]<0)break;
        }
        if(k==0)y++;
        if(k==1)x++;
        if(k==2)y--;
        if(k==3)x--;
        (pmg->maze+pmg->N*x+y)->wll=9;
    }
    (pmg->maze+pmg->N*x+y)->wll=2;
    ShowMazeGraph(stdout,pmg);
    return 0;
}

int ShowMazeDircFrom(FILE* fout, PMazeG pmg)
{
    printf("M=%d, N=%d\n",pmg->M,pmg->N);
    for(int i=0;i<pmg->M;i++)
    {
        for(int j=0;j<pmg->N;j++)
        {
            int k=0;
            for(;k<4;k++)
            {
                if((pmg->maze+pmg->N*i+j)->dirc[k]<0)break;
            }
            if((pmg->maze+pmg->N*i+j)->wll!=1)printf("%d ",k);
            else printf("# ");
        }
        printf("\n");
    }
    return 0;
}
