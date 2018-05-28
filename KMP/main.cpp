#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

int* CalNext(char* mode)
{
    int modetot=strlen(mode);//记录mode的长度
    int* next=(int*)malloc(modetot*sizeof(int));//分配一个整数数组
    //
    int i =0;
    int k=-1;
    next[i]=k;//初始化next[0]=-1，next数组记录i之前(注意是不包括i之前的！！！)的最大真子集重复前后缀长度记为k，跳入下一个j则记k=-1
                //next也代表这次k与i对比不成功，使用的下一个k的对比地址
    while(i<modetot-1)//虽然i<modetot-1，这一次循环计算的是next[i+1],所以如此
    {
        //假设next[i]都已经算出来了，i-1前即有重复前后缀长度k，再结合mode[i]的性质计算mode[i+1]
        while(k>=0 && mode[i]!=mode[k]) k=next[k];//k<=i-1，将指针i看成目标，k看成模式
        //k=-1，next的说明上一结果是j的平移，i++和k=0作为起点计算下一结果；
        //mode[i]=mode[k],那么mode[i+1]之前的最大真子集重复前后缀将等于mode[i]+1，next结果也将直接得到；
        //否则mode[i]前只有k个相同，对于mode[i+1]，模式指针地址进1，目标指针地址进1（其实是到mode[i]，是mode[i+1]前的最后一个元素），对比
        //如果不匹配，跳跃模式指针地址k，查找直到mode[k]=mode[i]，
        //其中k是地址，之前一定已经有k个前缀相同，加起来对mode[i+1]来说一共是k+1个前缀,
        i++;k++;
        if(mode[i]==mode[k]) next[i]=next[k];
        //修正，已经初步算出next[i]=k，即对于j，i不行时,换用next[i]=k比较，如果mode[i]==mode[k]那么自然需要再换k的地址，不如提前考虑
        else next[i]=k;//正常算出next[i]=k;
    }
    return next;
}

int Strfindstr(char* target, char* mode)
{
    int targettot=strlen(target);int modetot=strlen(mode);
    int* Next=CalNext(mode);
    printf("next数组为：\n");
    for(int k=0;k<modetot;k++)printf("%d  ",Next[k]);//显示next数组计算结果
    int j=0;//指向目标
    int i=0;//指向模式
    while(j < targettot && i < modetot)
    {
        if(i==-1 || target[j]==mode[i])//匹配成功或重新开始时
        {
            j++;
            i++;
        }
        else i=Next[i];//ij匹配不成功，i指针换地址（地址之前的已经保证匹配）
    }
    if(i >= modetot)//终点应该是j指针没有到头，而i指针指向了mode中的"\0"，注意这种情况下j的指向对应mode中的"\0"
    {
        printf("\n\n子串位置从第%d个字符处开始:\n",j-i+1);//输出的是子串首位在母串的序号（从1开始计数），如果从零开始计数，应该返回j-1
        return j-modetot+1;
    }
    else
    {
        printf("None\n");
        return  -1;//没有找到
    }
}

int main()
{
    char a[]="aabcbabcaabcaababc";
    char mode[]="abcaababc";
    int i=Strfindstr(a,mode);
    printf("%s\n",a);
    for(int j=0;j<i-1;j++)printf(" ");
    printf("%s\n",mode);
    return 0;
}
