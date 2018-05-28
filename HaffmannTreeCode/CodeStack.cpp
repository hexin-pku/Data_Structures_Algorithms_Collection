#include <cstdio>
#include <cstdlib>
#include "CodeStack.h"

PCS CreatCStack(void)
{
    PCS pcstack=(PCS)malloc(sizeof(CS));
    pcstack->top=-1;
    return pcstack;
}

bool IsEmpty(PCS pcstack)
{
    if(pcstack->top==-1)
        return 1;
    else return 0;
}

bool IsFull(PCS pcstack)
{
    if(pcstack->top==19)//×¢Òâ¸³ÖµºÅÓëµÈºÅ£¡£¡
        return 1;
    else return 0;
}

void PushStack(int n, PCS pcstack)
{
    if(IsFull(pcstack)==1)
    {
        printf("    Õ»Òç³ö!\n");
    }
    else
    {
        pcstack->top++;
        pcstack->S[pcstack->top]=n;
    }
}

int PopStack(PCS pcstack)
{
    if(IsEmpty(pcstack)==1)
    {
        printf("    Õ»¿Õ!\n");
    }
    else
    {
        pcstack->top--;
        return pcstack->S[pcstack->top+1];
    }
}
