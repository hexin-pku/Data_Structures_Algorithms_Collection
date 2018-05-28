#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "SepStack.h"
#include "CrossRiver.h"
bool side(int location, int movers)
{
    return ((location & movers) != 0);
}

bool safe(int location)
{
	//羊吃白菜
    if (side(location, GOAT) == side(location, CABBAGE) &&
		side(location, GOAT) != side(location, FARMER))
		return false;
	//狼吃羊
    if (side(location, GOAT) == side(location, WOLF) &&
		side(location, GOAT) != side(location, FARMER))
		return false;
	//其它为安全状态
	return true;
}

void TakeSolution(int location2, int location1, char *pstr)
{
	//两次行动的差异
	int location = location2 ^ location1;
	if (side(location, FARMER))
	{
		//农夫的行动
		char obj_action[20] = "";
		if (side(location, WOLF))
            strcat(obj_action, "狼");
		if (side(location, CABBAGE))
            strcat(obj_action, "白菜");
		if (side(location, GOAT))
            strcat(obj_action, "羊");
		if (obj_action[0])
		{
			sprintf(pstr, "农夫带%s到", obj_action);
			strcat(pstr, side(location2, FARMER) ? "南边" : "北边");
		}
		else
			sprintf(pstr, "农夫自己回到%s", side(location2, FARMER) ? "南边" : "北边");
	}
}
