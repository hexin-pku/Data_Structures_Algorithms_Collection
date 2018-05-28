#include "HaffmannTree.h"
#include "CodeStack.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

void RandFormText()
{
    FILE* fout=fopen("d:\\codefile\\datafile\\coderand.txt","w");
    fprintf(fout,"%d\n",95+2);
    for(int i=32;i<127;i++)
    {
        fprintf(fout,"%c %d\n",char(i),1+rand()%100);
    }
    fprintf(fout,"\t %d\n",1+rand()%100);
    fprintf(fout,"\n %d\n",1+rand()%100);
    fprintf(fout,"%c %d\n",'\0',1+rand()%100);
    fclose(fout);
}

PHT CreatHtTree(int N)
{
    PHT phtree=(PHT)malloc(sizeof(HT));
    phtree->N=N;
    phtree->ht=(PHtNode)malloc((2*N-1)*sizeof(HtNode));
    for(int i=0;i<(2*phtree->N-1);i++)
    {
        (phtree->ht+i)->ww=0;
        (phtree->ht+i)->parent=-1;
        (phtree->ht+i)->rlink=-1;
        (phtree->ht+i)->llink=-1;
        (phtree->ht+i)->ch='\0';
    }
    return phtree;
}

void InitHtTree(PHT phtree, FILE* fin)
{
    char Aline[200];
    //char tmp_ch[2];int tmp_flc;

    fgets(Aline,200,fin);
    fgets(Aline,200,fin);
    for(int i=0;i < (phtree->N) && Aline!=NULL;i++)
    {
        //fscanf(fin,"%s",tmp_ch);
        //fscanf(fin,"%d",&tmp_flc);
        (phtree->ht+i)->ch=Aline[0];//_____________________________________
        (phtree->ht+i)->ww=atoi(Aline+2);
        fgets(Aline,200,fin);

    }
}

void FindMin(PHT phtree,int creatnum, int* m1, int* m2)//_________________???
{
    int mm1=0;int mm2,tmp;
    while((phtree->ht+mm1)->parent!=-1)mm1++;//直到找到一个无父节点的mm1
    mm2=mm1+1;
    while((phtree->ht+mm2)->parent!=-1)mm2++;//找到另一个无父节点的mm2
    int i=mm2+1;

    if((phtree->ht+mm1)->ww > (phtree->ht+mm2)->ww)
    {
        tmp=mm2;mm2=mm1;mm1=tmp;
    }//保持mm1权重<=mm2权重

    for(;i<phtree->N+creatnum;i++)
    {
        if((phtree->ht+i)->parent!=-1)continue;
        if((phtree->ht+i)->ww < (phtree->ht+mm1)->ww)
        {
            mm2=mm1;
            mm1=i;
        }
        else if((phtree->ht+i)->ww < (phtree->ht+mm2)->ww) mm2=i;
    }
    *m1=mm1;
    *m2=mm2;
}

PHT BuildHtTree(PHT phtree)
{
    int m1,m2;
    int creatnum=0;
    for(int i=0;i<phtree->N-1;i++)
    {
        FindMin(phtree,creatnum,&m1,&m2);
        (phtree->ht+m1)->parent=phtree->N+creatnum;
        (phtree->ht+phtree->N+creatnum)->rlink=m1;
        (phtree->ht+m2)->parent=phtree->N+creatnum;
        (phtree->ht+phtree->N+creatnum)->llink=m2;
        phtree->root=phtree->N+creatnum;
        (phtree->ht+phtree->N+creatnum)->ww=(phtree->ht+m1)->ww+(phtree->ht+m2)->ww;
        creatnum++;
    }
    return phtree;
}

char* GetCode_ByLoc(int loc, PHtNode nd)//_________________________必须适当时候清除内存
{
    PCS PS=CreatCStack();
    char buff[32];*buff='\0';

    while((nd+loc)->parent!=-1)
    {
        int pa=(nd+loc)->parent;
        if((nd+pa)->rlink==loc)PushStack(0,PS);
        else PushStack(1,PS);
        loc=pa;
    }

    int cnt=0;
    while(IsEmpty(PS)!=1)
    {
        if(PopStack(PS)==1)
        {
            *(buff+cnt)='1';
        }//出栈!!
        else *(buff+cnt)='0';
        *(buff+cnt+1)='\0';
        cnt++;
    }
    char* pcode=(char*)malloc((strlen(buff)+1)*sizeof(char));
    strncpy(pcode,buff,strlen(buff)+1);//+1不可少！！
    return pcode;
}

void ShowHtCode(PHT phtree)
{
    PHtNode nd=phtree->ht;

    printf("字符    频率      Haffmann编码\n");
    for(int i=0;i<phtree->N;i++)
    {
        printf("%c      %5.5d      ",(phtree->ht+i)->ch,(phtree->ht+i)->ww);
        char* pcode=GetCode_ByLoc(i, nd);
        printf("%s\n",pcode);
        free(pcode);pcode=NULL;
    }
    printf("\n");
}

void ShowHt(PHT phtree)
{
    printf("使用静态链表存储Haffmann树结构：\n");
    printf("下标      权重      右子    左子    父母    字符\n");
    for(int i=0;i<2*phtree->N-1;i++)
    {
        printf("idx: %3.3d  ww:%5.5d  r:%+3.3d  l:%+3.3d  p:%+3.3d  ch:%c  ",i,(phtree->ht+i)->ww,(phtree->ht+i)->rlink,(phtree->ht+i)->llink,(phtree->ht+i)->parent,(phtree->ht+i)->ch);
        printf("\n");
    }
    printf("\n\n");
}
