#ifndef SEPSTACK_H_INCLUDED
#define SEPSTACK_H_INCLUDED
#ifndef FARMER
#define FARMER	 0x08
#endif // FARMER
#ifndef WOLF
#define WOLF   0x04
#endif // FARMER
#ifndef CABBAGE
#define CABBAGE   0x02
#endif // CABBAGE
#ifndef GOAT
#define GOAT   0x01
#endif // GOAT

typedef struct CStack
{
	int data[20];//栈的大小20足以
	int top;
} *PSS;

PSS CreateEmptyStack();
bool IsEmptyStack(PSS pStk);//
bool InStack(PSS pStk, int x);
bool OutStack(PSS pStk);
int Gettop(PSS pStk);
void printStack(PSS pStk);

#endif // SEPSTACK_H_INCLUDED
