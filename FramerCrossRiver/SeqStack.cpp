#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"

PSS CreateEmptyStack()
{
	PSS pStk = (PSS)malloc(sizeof(struct CStack));
	if (pStk)
	{
		pStk->top=-1;
	}
	return pStk;
}

/////////////////////////////////
//栈判空
/////////////////////////////////
bool IsEmptyStack(PSS pStk)
{
	if (pStk && pStk->top == -1)
		return true;
	else
		return false;
}

/////////////////////////////////
//栈插入(入栈)
/////////////////////////////////
bool InStack(PSS pStk, int x)
{
	if (pStk && (pStk->top+1) == 20)
	{
		printf("栈已满, 不能再加入!\n");
		return false;
	}
	pStk->top++;
	pStk->data[pStk->top] = x;
	return true;
}

/////////////////////////////////
//栈删除(出栈)
/////////////////////////////////
bool OutStack(PSS pStk)
{
	if (IsEmptyStack(pStk))
	{
		printf("栈已空, 不能再删除!\n");
		return false;
	}
	pStk->top--;
	return true;
}

/////////////////////////////////
//获取栈尾元素
/////////////////////////////////
int Gettop(PSS pStk)
{
	return (pStk->data[pStk->top]);
}

void printStack(PSS pStk)
{
	printf("--当前栈内容------------------\n");
	for (int i = pStk->top; i >= 0; i--)
	{
		int location = pStk->data[i];
        printf("  %1d   %1d   %1d   %1d\n",
				side(location, FARMER), side(location, WOLF),
				side(location, CABBAGE), side(location, GOAT));
	}
	printf("--农--狼--菜--羊---------------\n");
}
