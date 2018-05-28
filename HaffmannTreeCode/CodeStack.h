#ifndef CODESTACK_H_INCLUDED
#define CODESTACK_H_INCLUDED

typedef struct CodeStack
{
    int S[20];
    int top;
}CS,*PCS;

PCS CreatCStack(void);
bool IsEmpty(PCS pcstack);
bool IsFull(PCS pcstack);

void PushStack(int n, PCS pcstack);
int PopStack(PCS pcstack);

#endif // CODESTACK_H_INCLUDED
