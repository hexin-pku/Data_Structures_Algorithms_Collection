#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

typedef struct StackNode
{
    float argnum[2];//设置传递参数
    char argc[4];
}SN,*PSN;

typedef struct StackStrc
{
    PSN stk;
    int N;//记录栈的最大空间
    int t;//栈的指示变量
    int ot;//栈的指示变量2
}SS,*PSS;

int ShowStack(SS Stk)
{
    printf("t is %d;ot is %d\n",Stk.t,Stk.ot);
    printf("    栈结构：\n");
    char flag[2]="N";
    int m=(Stk.t>=Stk.ot)?Stk.t:Stk.ot;
    for(int i=0;i<=m;i++)
    {
        printf("        第%d层 存储信息%f",i,(i<=Stk.t)?(Stk.stk+i)->argnum[0]:0);
        printf("  存储运算%s\n",(i<=Stk.ot)?(Stk.stk+i)->argc:flag);
    }
    return 0;
}

int IsOpr(char* p)//辅助判断是否是运算符
{
    if(strcmp(p,"+")==0 || strcmp(p,"-")==0 || strcmp(p,"*")==0 || strcmp(p,"/")==0 || strcmp(p,"%")==0|| strcmp(p,"!")==0 ||strcmp(p,"^")==0|| strcmp(p,"(")==0 || strcmp(p,")")==0)return 1;
    if(strcmp(p,"cos")==0 || strcmp(p,"sin")==0 || strcmp(p,"tan")==0 ||strcmp(p,"cot")==0)return 1;
    else return 0;
}

int IsNum(char* p)
{
    if(IsOpr(p)==1)return 0;//0表示是运算符
    for(;*p!='\0';p++)//注意指针要取内容
    {
        if((*p<'0' || *p>'9') && *p!='.')
            return -1;//-1表示没有定义的输入，允许小数的输入
    }
    return 1;//1表示输入的是一个数
}

float TransferNum(char* s)
{
    float rst=0.0;
    int hpn=0;//记录小数点的出现
    int dot=1;//记录小数点的位置
    while(*s!='\0')
    {
        if(*s=='.')
        {
            s++;
            hpn=1;
            continue;
        }
        if(hpn==1)dot*=10;
        rst=rst*10+(int)(*s)-(int)('0');
        s++;//忘记自增了
    }
    rst/=dot;
    return rst;
}

int Level(char* c)
{
    if(strcmp(c,"(")==0)return 0;
    if(strcmp(c,"+")==0||strcmp(c,"-")==0)return 1;
    if(strcmp(c,"*")==0||strcmp(c,"/")==0||strcmp(c,"%")==0)return 2;
    if(strcmp(c,"^")==0||strcmp(c,"!")==0)return 3;
    if(strcmp(c,"cos")==0||strcmp(c,"sin")==0||strcmp(c,"tan")==0||strcmp(c,"cot")==0)return 3;
    return -1;//出错
}

int Cmpr(char* token,SS Stk)
{
    if(Level(token)>Level((Stk.stk+Stk.ot)->argc))return 1;
    else if(Level(token)==Level((Stk.stk+Stk.ot)->argc))return 0;
    else return -1;
}

SS InStack(SS Stk, float token)
{
    ShowStack(Stk);
    if(Stk.t>=Stk.N)
    {
        printf("    栈溢出！\n");
        return Stk;
        exit(0);//其他解决方案?
    }
    else
    {
        Stk.t++;
        (Stk.stk+Stk.t)->argnum[0]=token;
        return Stk;
    }
}

SS OInStack(SS Stk, char* token)//返回的不是指针,无法修改内部的变量值
{
    ShowStack(Stk);
    if(Stk.ot>=Stk.N)
    {
        printf("    栈溢出！\n");
        return Stk;
        exit(0);//其他解决方案?
    }
    else
    {
        Stk.ot++;
        strncpy((Stk.stk+Stk.ot)->argc, token, 4);
        return Stk;
    }
}

SS OutStack(SS Stk, char* token)
{
    ShowStack(Stk);
    if(strcmp(token,"+")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=(Stk.stk+Stk.t-1)->argnum[0]+(Stk.stk+Stk.t)->argnum[0];
    if(strcmp(token,"-")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=(Stk.stk+Stk.t-1)->argnum[0]-(Stk.stk+Stk.t)->argnum[0];
    if(strcmp(token,"*")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=(Stk.stk+Stk.t-1)->argnum[0]*(Stk.stk+Stk.t)->argnum[0];
    if(strcmp(token,"/")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=(Stk.stk+Stk.t-1)->argnum[0]/(Stk.stk+Stk.t)->argnum[0];
    if(strcmp(token,"%")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=(int)floor((Stk.stk+Stk.t-1)->argnum[0])%(int)floor((Stk.stk+Stk.t)->argnum[0]);//小数的问题？
    if(strcmp(token,"^")==0)
        (Stk.stk+Stk.t-1)->argnum[0]=pow((Stk.stk+Stk.t-1)->argnum[0],(Stk.stk+Stk.t)->argnum[0]);
    if(strcmp(token,"!")==0)
    {
        int tmp=floor((Stk.stk+Stk.t)->argnum[0]+0.5);
        float s=1.0;
        if(tmp<=0)
        {
            (Stk.stk+Stk.t)->argnum[0]=1;return Stk;
        }
        for(;tmp>0;tmp--)s*=tmp;
        (Stk.stk+Stk.t)->argnum[0]=s;
        return Stk;
    }
    if(strcmp(token,"sin")==0)
    {
        (Stk.stk+Stk.t)->argnum[0]=sin((Stk.stk+Stk.t)->argnum[0]);
        return Stk;
    }
    if(strcmp(token,"cos")==0)
    {
        (Stk.stk+Stk.t)->argnum[0]=cos((Stk.stk+Stk.t)->argnum[0]);
        return Stk;
    }
    if(strcmp(token,"tan")==0)
    {
        (Stk.stk+Stk.t)->argnum[0]=tan((Stk.stk+Stk.t)->argnum[0]);
        return Stk;
    }
    if(strcmp(token,"cot")==0)
    {
        (Stk.stk+Stk.t)->argnum[0]=1.0/tan((Stk.stk+Stk.t)->argnum[0]);
        return Stk;
    }
    Stk.t--;//对于二元运算需要退栈
    return Stk;
}

float CalcPostfixExpr(char* Aline)
{
    char sep[5]=" \n\t\b";//换行符
    SS Stk;//申请栈结构空间
    Stk.N=strlen(Aline);//估计栈的空间
    Stk.stk=(PSN)malloc(Stk.N*sizeof(SN));//为栈层指针申请空间
    Stk.t=-1;

    char* token;//每次提取一串字符
    token=strtok(Aline,sep);

    while(token!=NULL)//开始提取字符
    {
        if(IsNum(token)==1)//提取的是数字
        {
            Stk=InStack(Stk, TransferNum(token));//存栈
        }
        else if(IsNum(token)==0)//是运算符的话则退栈
        {
            Stk=OutStack(Stk, token);//退栈
        }
        else
        {
            printf("    输入内容 %s 无法识别，计算出现故障：\n",token);
            return 0;//不完美
        }
        token=strtok(NULL, sep);
    }
    //ShowStack(Stk);
    return Stk.stk->argnum[0];
    free(Stk.stk);
}

float CalcInfixExpr(char* Aline)
{
    char sep[5]=" \n\t\b";//换行符
    SS Stk;//申请栈结构空间
    Stk.N=strlen(Aline);//估计栈的空间
    Stk.stk=(PSN)malloc(Stk.N*sizeof(SN));//为栈层指针申请空间
    Stk.t=-1;
    Stk.ot=-1;
    int tk=0;

    char* token;
    token=strtok(Aline, sep);
    while(token!=NULL)
    {
        printf("%s\n",token);
        if(IsNum(token)==1)
        {
            Stk=InStack(Stk, TransferNum(token));
            if(tk==1)
            {
                //char tmp[4];
                //strncpy(tmp,Stk.stk+Stk.ot-1)->argc,4);
                Stk=OutStack(Stk, (Stk.stk+Stk.ot-1)->argc);
                strncpy((Stk.stk+Stk.ot)->argc,(Stk.stk+Stk.ot+1)->argc,4);
                tk=0;
            }
        }
        else if(IsNum(token)==0)//分情况讨论
        {
            if(strcmp(token,"(")==0)
            {
                Stk=OInStack(Stk, token);
            }
            else if(strcmp(token,")")==0)
            {
                while(strcmp((Stk.stk+Stk.ot)->argc,"(")!=0 && Stk.ot>=0)
                {
                    Stk=OutStack(Stk, (Stk.stk+Stk.ot)->argc);
                    Stk.ot--;
                }
                Stk.ot--;
            }
            else
            {
                if(Stk.ot==-1 && Cmpr(token,Stk)>=0)//??
                {
                    Stk=OInStack(Stk, token);
                }
                else
                {
                    Stk=OInStack(Stk, token);
                    tk=1;
                }
            }
        }
        token=strtok(NULL, sep);
    }
    while(Stk.ot>0)
    {
        OutStack(Stk,(Stk.stk+Stk.ot)->argc);
    }
    return Stk.stk->argnum[0];
    free(Stk.stk);
}

int main()
{
    //freopen("d:\\codefile\\datafile\\datain3.txt","r",stdin);
    char Aline[1024];//一行输入
    //char kik[5]="82";
    //printf("    kik是否是数字呢？1，是数字；0，是字母；-1，都不是：\n\t%d",IsNum(kik));
    //int way=0;
    //int chg=0;
    //char lok[]="[";
    //printf("%s Is Num: %d\n",lok,IsNum(lok));
    while(fgets(Aline, 1024, stdin) && Aline != NULL)
    {
        Aline[strlen(Aline)-1]='\0';
        printf("Expression %s\n",Aline);
        float answer=CalcInfixExpr(Aline);
        printf("    the result is:%.3f\n",answer);
    }
    // free buff
    return 0;
}
