#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Stack.h"

PCS CreatCS(int M)
{
    PCS pcs=(PCS)malloc(sizeof(CS));
    pcs->layer=(PDN)malloc(M*sizeof(DataNode));
    return pcs;
}

void DeleteCS(PCS pcs)
{
    free(pcs->layer);
    free(pcs);
}

PCS push(PCS pcs, DataNode lyr)
{
    if(pcs->top+1>=pcs->M) return pcs;
    else
    {
        pcs->top++;
        pcs->layer[pcs->top]=lyr;
        return pcs;
    }
}

PCS pop(PCS pcs)
{
    if(pcs->top<=-1) return pcs;
    else
    {
        pcs->top--;
        return pcs;
    }
}
