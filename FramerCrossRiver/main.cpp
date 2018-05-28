#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"
//常量定义
#define FARMER	0x08
#define WOLF	0x04
#define CABBAGE 0x02
#define GOAT	0x01

int main(int argc, char* argv[])
{
    int movers, location, newlocation;
    int route[16];            //记录已经考虑的状态路径

    //初始准备
    PSS pstk = CreateEmptyStack();
    InStack(pstk, 0x00);//
	int i;
    route[0] = 0;
    for (i = 1; i < 16; i++)  route[i] = -1;

    //开始移动
    while (!IsEmptyStack(pstk) && route[15] < 0)
    {
		//打印当前栈内容
		printStack(pstk);
		getchar();

		//得到现在的状态
        location = Gettop(pstk);
		int cnt = 0;
        for (movers = GOAT; movers <= FARMER; movers <<= 1)
        {
            //农夫总是在移动，随农夫移动的东西必须与农夫在同侧
            if (side(location, FARMER) == side(location, movers))
            {
                //新位置，农夫与要移动的东西同时过河[状态改变]
                newlocation = location ^(FARMER | movers);
                if (safe(newlocation) && route[newlocation] < 0)
                {
                    //安全并且未访问过的状态(进入下一层)
                    route[newlocation] = location;
                    InStack(pstk, newlocation);
					cnt++;
					break;
                }
            }
        }

		//如果该状态无法继续, 退栈(回到上一层)
		if (!cnt)
		{
			printf("--状态: %1d  %1d  %1d  %1d 无法继续\n",
					side(location, FARMER), side(location, WOLF),
					side(location, CABBAGE), side(location, GOAT));
			OutStack(pstk);
		}
		else
		{
			printf("++加入: %1d  %1d  %1d  %1d 新状态\n",
					side(newlocation, FARMER), side(newlocation, WOLF),
					side(newlocation, CABBAGE), side(newlocation, GOAT));
		}
    }

    //后向打印路径
    if (route[15] >= 0)
    {
		printf("=============农夫过河问题具体步骤================\n");
		printf("      农夫  狼    白菜   羊 \n");
		printf("-------------------------------------------------\n");
        for (location = 15; location >= 0; location = route[location])
        {
			char str[32] = "初始状态";
			if (location != 0)
			{
				TakeSolution(location, route[location], str);
			}
            printf("状态:   %1d     %1d     %1d     %1d      %s\n",
					side(location, FARMER), side(location, WOLF),
					side(location, CABBAGE), side(location, GOAT), str);
            if (location == 0)   break;
        }
    }
	getchar();

	return 0;
}
