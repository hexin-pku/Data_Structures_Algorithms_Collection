#include <cstdio>
#include <cstdlib>


using namespace std;
//将有关图着色的数据保存在txt文件中，第一行给出图的顶点个数
//后面n行给出这n个顶点的关系矩阵，数字间通过空格隔开
//默认的输入路径是d:\\codefile\\datafile\\datain1.txt
//默认的输出路径是d:\\codefile\\datafile\\dataou1.txt

typedef struct Node//定义结点的基本属性
{
   int clr; //结点的颜色
} Node,*PNode;

typedef struct Graphtype//定义一个图的基本属性，由结点和其邻接矩阵构成
{
    int Nver;//图的顶点数
    int NBeenColored;//已经被涂色的顶点数，不能初始化
    PNode Ver;//图的顶点，作为一组指针
    int* Adjmtx;//邻接矩阵，作为一组指针
}Graph, *PGraph;

bool CanColor(PGraph PG, int clr, int j , int i)//判断PG对应的图的第j个元素能否使用clr着色，因为是按照顺序的，所以只用对i之后j之前的元素进行判断即可
{
    bool CanClr=true;//初始化为可以着色

    for(int k=i ; k < j ; k++)
    {
        if(*(PG->Adjmtx+k*PG->Nver+j) && (PG->Ver+k)->clr==clr)//如果元素k与j邻接并且已经被着色为clr则不能着色；错把pnode类型与clr比较
            {
                CanClr=false;
                break;//跳出循环
            }
    }
    return CanClr;
}

int Color(PGraph PG,FILE* fout){
    int color = 0;//k代表染第几种颜色
    int init=0;//记录搜索染色的起点，初始化为0
    while (PG->NBeenColored < PG->Nver) {//当图还有点未被染色时，继续执行
        color++;
        fprintf(fout,"颜色分组%d:",color);

        //找到第一个未着色的节点，用新颜色染色
        int i;
        for (i = init; i < PG->Nver; i++)
        {
           if ((PG->Ver+i)->clr == 0)
           {
               (PG->Ver+i)->clr = color;
               PG->NBeenColored++;//着色点+1
               fprintf(fout," 顶点%02d",i+1);
               init=i+1;//说明之前的点都已经染色，下次搜索直接从这里开始
               break;
           }
        }

        //再把其他所有不和该新染色点相邻的顶点着相同的颜色
        //以上i是新颜色的第一个顶点，剩下的顶点应该从它后面找
        for(int j=i+1; j<PG->Nver; j++)
        {
           if((PG->Ver+j)->clr ==0 && CanColor(PG,color,j,i) )//条件是结点j未被着色,并且与它之前的被color着色结点不冲突
           {
               (PG->Ver+j)->clr = color;
               PG->NBeenColored++;//着色点+1
               fprintf(fout," 顶点%02d",j+1);
           }
        }
        fprintf(fout,"\n");
     }
     return color;
}

int main() {
    FILE *fin, *fout;
    fin = fopen("d:\\codefile\\datafile\\datain1.txt","r");
    fout = fopen("d:\\codefile\\datafile\\dataout1.txt","w");
    //以上定义重定向的文件指针
    //datain1.txt是存放数据的文件名
    //dataout1.txt是存放输出数据的文件名
    if(fin==NULL)
    {
        fprintf(fout,"The file d:\\codefile\\datafile\\datain1.txt is not existing!\n");
        exit(0);
    }
    //判断文件指针是否正确指向


    int n=0;
    fscanf(fin,"%d",&n);//读入图的顶点个数
    PGraph PG=(PGraph)malloc(sizeof(Graph));//为图分配空间
    PG->Nver=n;//图的顶点数目赋值
    PG->NBeenColored=0;//图已染色点初始化为0

    PG->Ver=(PNode)malloc(n*sizeof(struct Node));//为图的n个结点分配空间（点集）
    PG->Adjmtx=(int*)malloc(n*n*sizeof(int));//为图的n*n关系矩阵分配空间（关系集）

    //初始化关系矩阵，初始化0表示没有涂色
    for (int i = 0; i < n; i++)
    {
         for (int j = 0; j < n; j++) {
            fscanf(fin,"%d",PG->Adjmtx+i*n+j);
         }
         (PG->Ver+i)->clr = 0;
    }


    int clrneed = Color(PG,fout);//执行对图的染色程序
    fprintf(fout,"一共需要%d种颜色。",clrneed);

    free(PG->Ver);
    free(PG->Adjmtx);
    free(PG);
    //释放空间
    //注意codeblock似乎没有野指针问题，VC中存在野指针问题

    return 0;
}

