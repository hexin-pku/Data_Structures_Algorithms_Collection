#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

char wordlist[][16]={"to","the","and","of","in","a","my","and","his","who","on","introduction"};
char seps[]=" ,\t\n";

typedef struct Book
{
    int No;
    Book* link;
}Bk, *PBk;

typedef struct Key
{
    char info[16];
    Bk head;//头结点，头结点的空间已经分配（头结点不用指针，否则分配起来太麻烦）
}Key, *PK;

typedef struct KeyList
{
    Key klist[200];
    int tot;
    unsigned int maxlen;
}KL, *PKL;

PKL InputBook();
int FindWord(char** words, char* akey);
int FindKeyLoc(PKL pkl, char* akey);
int FindExist(PKL pkl, char* akey);
PKL ClrBk(PKL pkl, int loc);
int ClrKlist(PKL pkl);
PKL SetLoc(PKL pkl, int loc, char* akey, int num);
PKL CreatKey(PKL pkl, char* akey, int num);
PKL AddBook(PKL pkl, int id, int num);
PKL AddKey(PKL pkl, char* akey, int num);
int ShowIndexList(PKL pkl);
int KeyFindBook(PKL pkl, char* akey);


PKL InputBook()
{
    FILE* fin=fopen("d:\\codefile\\datafile\\booklist.txt","r");//请先建立相应的文件夹

    PKL pklist=(PKL)malloc(sizeof(KL));
    pklist->tot=0;//初始化关键词个数为0
    pklist->maxlen=0;
    //for(int k=0;k<200;k++)pklist->klist[k].head.link=NULL;

    char Aline[100];//一行输入
    char* token;//提取一行中单词
    int Num;//书号
    while(fgets(Aline, 100, fin) && Aline != NULL)
    {
        token=strtok(Aline,seps);
        if(token==NULL)continue;//防止多打的空行!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        sscanf(token,"%d",&Num);//第一个数据输入书号
        token=strtok(NULL, seps);
        while(token!=NULL)
        {
            pklist=AddKey(pklist,token, Num);
            token=strtok(NULL, seps);
        }
    }
    return pklist;
}

int FindWord(char words[][16], char* akey)
{
    int nwrd=sizeof(wordlist)/sizeof(wordlist[0]);
    akey=_strlwr(akey);
    for(int i=0;i<nwrd; i++)
    {
        if(strcmp(words[i], akey)==0)return 1;
    }
    return 0;
}

int FindKeyLoc(PKL pkl, char* akey)//实现折半查找，返回存在位置或者应该插入的位置，特别的首位插入则会返回-1
{
    akey=_strlwr(akey);
    int m1=0;
    int m2=pkl->tot;//故意多1，注意tot==0或1的情况
    int mid;

    if(strcmp(_strlwr( pkl->klist[m1].info ),akey)>0)return -1;//克服首位插入的问题，-1表示放于首位，在-1位置后面0插入

    //剩下情况考虑akey能够落在[m1,m2)的区间内
    while(m2-m1>1)//一般意义的终点是m2-m1=1
    {
        mid=(m1+m2)/2;
        if(strcmp(_strlwr( pkl->klist[mid].info ),akey)>0)//中间mid有可能等于akey，这时全都交给了m1，m2不可能等于akey
        {
            m2=mid;//m2保持大于akey
        }
        else m1=mid;//m1保持小于等于akey
    }
    return  m1;//m1小于等于akey，所以akey要在m1的后面插入
}

int FindExist(PKL pkl, char* akey)//辅助函数FindKeyLoc判断元素是否存在，把两个函数拆开便于模块化使用
{
    int loc=FindKeyLoc(pkl, akey);
    if(loc!=-1 && strcmp(_strlwr( pkl->klist[loc].info ),_strlwr(akey))==0) return 1;
    else return 0;
}

PKL ClrBk(PKL pkl, int loc)//清除booklist记录
{
    PBk prepb=&pkl->klist[loc].head;//prepb始终都是head
    PBk pb=prepb->link;
    while(pb!=NULL)
    {
        pb=pb->link;
        free(prepb);
        prepb->link=pb;
    }
    pkl->klist[loc].head.link=NULL;
    pkl->klist[loc].head.No=0;
    return pkl;
}

int ClrKlist(PKL pkl)
{
    for(int i=0;i<pkl->tot;i++)
    {
        pkl=ClrBk(pkl, i);
    }
    free(pkl);
    return 0;
}

PKL SetLoc(PKL pkl, int loc, char* akey, int num)//（假设已经移动好了后）实现某一位置的关键词更新，注意以往数据的清除和初始化
{
    if(loc < pkl->tot) pkl=ClrBk(pkl, loc);//不在最后赋值，说明前面腾出的位置上有内存需要释放出来；

    strncpy(pkl->klist[loc].info, akey, 16);//更新loc处的key；考虑&到底要不要？？？——————————————
    pkl->klist[loc].head.No=0;
    PBk bn=(PBk)malloc(sizeof(Bk));//申请一个新的结点记录信息
    bn->No=num;
    bn->link=NULL;
    pkl->klist[loc].head.link=bn;//加入新节点，更新信息booklist和keylist
    pkl->klist[loc].head.No++;//keylist的更新在这个函数体外，还未更新
    return pkl;
}

PKL CreatKey(PKL pkl, char* akey, int num)
{
    if(pkl->tot >= 200)
    {
        printf("溢出\n");
        return pkl;
    }
    int loc=FindKeyLoc(pkl, akey);
    if(loc==-1)//首位插入
    {
        if(pkl->tot!=0)
        {
            for(int i=pkl->tot;i>0;i--)pkl->klist[i]=pkl->klist[i-1];//非空表腾出首位，空表直接插入首位即可
        }
        pkl=SetLoc(pkl, 0, akey, num);//插入首位
        pkl->tot++;
        pkl->maxlen=(strlen(akey) > pkl->maxlen)?strlen(akey):pkl->maxlen;
        return pkl;
    }
    for(int i=pkl->tot;i>loc+1;i--) pkl->klist[i]=pkl->klist[i-1];//对于插入loc之后的位置，loc可以是0,1,...tot-1，先完成移动，明显loc=tot-1时不用移动
    pkl=SetLoc(pkl, loc+1, akey, num);
    pkl->tot++;
    pkl->maxlen=(strlen(akey) > pkl->maxlen)?strlen(akey):pkl->maxlen;
    return pkl;
}

PKL AddBook(PKL pkl, int id, int num)//当key存在时，只用添加book
{
    PBk tail=&pkl->klist[id].head;//注意取地址！！
    for(;tail->link!=NULL && tail->link->No <num ;tail=tail->link);//找到按照顺序排列书号的位置
    PBk bn=(PBk)malloc(sizeof(Bk));//创建一个新节点
    bn->No=num;
    bn->link=NULL;
    tail->link=bn;
    pkl->klist[id].head.No++;//这信息更新，里将头结点head的信息用做记录单链表的元素数，而非书号
    return pkl;
}

PKL AddKey(PKL pkl, char* akey, int num)//pwl是wordlist生成的表，起到排除作用；
{
    int findinword=FindWord(wordlist, akey);
    if(findinword==1)return pkl;//常用词不加入，返回原列表

    int findinkey=FindExist(pkl, akey);//判断关键词是否存在
    if(findinkey==0)
    {
        pkl=CreatKey(pkl, akey, num);//不存在，新建关键词
    }
    else
    {
        int loc=FindKeyLoc(pkl, akey);//存在，则在关键词位置loc后面加上书号即可
        pkl=AddBook(pkl, loc, num);
    }
    return pkl;
}

int ShowIndexList(PKL pkl)
{
    printf("Keywords-Book's No. IndexList：\n");
    for(int i=0 ;i < pkl->tot;i++)
    {
        printf("    %-12.12s ： ",pkl->klist[i].info);
        PBk head=pkl->klist[i].head.link;
        for(;head!=NULL; head=head->link)
        {
            printf("  %d",head->No);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int KeyFindBook(PKL pkl, char* akey)
{
    akey=_strlwr(akey);
    if(FindExist(pkl, akey)==0)
    {
        printf("    关键词不存在。\n");
        return -1;//异常
    }
    printf("Search word: \n    %-12.12s ： ",akey);
    int loc=FindKeyLoc(pkl, akey);
    PBk pb=pkl->klist[loc].head.link;
    while(pb!=NULL)
    {
        printf("  %d",pb->No);
        pb=pb->link;
    }
    printf("\n");
    return 0;
}

int main()
{
    //freopen("d:\\codefile\\datafile\\ShowIdxofBook.txt", "w", stdout);
    PKL keys=InputBook();
    ShowIndexList(keys);
    KeyFindBook(keys, "computer");
    ClrKlist(keys);
    return 0;
}
