#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct DataNode
{
    int data;
}Data, *PDN;

typedef struct CStack
{
    int M;
    int top;
    PDN layer;
}CS, *PCS;

PCS CreatCS(int M);
void DeleteCS(PCS pcs);
PCS push(PCS pcs, DataNode lyr);
PCS pop(PCS pcs);

#endif // STACK_H_INCLUDED
