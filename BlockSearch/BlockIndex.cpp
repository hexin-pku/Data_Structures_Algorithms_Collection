#include <cstdio>
#include <cstdlib>
#include "BlockIndex.h"

int InterSearch(PBD pblock,int tar,int* pLoc, int N)
{
    if((pblock)->Max > tar) {*pLoc=0;return true;}
    if((pblock+N-1)->Max <tar) return false;

    int m1=0;int m2=N-1;
    *pLoc=(m1+m2)/2;
    while(m2>m1+1)
    {
        //printf("m1=%d md=%d m2=%d\n",m1,*pLoc,m2);//_____________________
        if((pblock+*pLoc)->Max >= tar) m2=*pLoc;
        else m1=*pLoc;
        *pLoc=(m1+m2)/2;
    }
    //printf("final m2==%d\n",m2);
    *pLoc=m2;
    return true;
}

int IntraSearch(int* pdata,int tar,int* pLoc, int nsize)
{
    int check=0;
    for(int i=0;i<nsize;i++)
    {
        //printf("loc==%d\n",*pLoc);//_______________
        if(*(pdata+*pLoc)==tar){check=1;break;}
        *pLoc=*pLoc+1;
    }
    if(check==1)return true;
    else return false;
}

int ShowBlock(PBD pblock,int N)
{
    for(int i=0;i<N;i++)
    {
        printf("the block %d:\n    Max is %d\n    LinkIndex is %d\n\n",i,pblock->Max,pblock->Loc);
        pblock++;
    }
    return 0;
}

int IntraSearch_2()
{
    return 0;
}
