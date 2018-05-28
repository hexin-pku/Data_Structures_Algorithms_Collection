#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "BinSearchT.h"

int SearchBT(PBT pbt,int key,PTN* pploc)//返回插入节点的父节点
{
    PTN p=pbt->ptree;PTN pre=NULL;
    while(p!=NULL)
    {
        if(p->key==key)
        {
            *pploc=p;return true;//需要二级指针！课件的写法是错误的！
        }
        pre=p;
        if(p->key>key) p=p->llink;
        else {p=p->rlink;}
    }
    *pploc=pre;
    return false;
}

int InsertBT(PBT pbt,PTN ptn)
{
    PTN ploc=NULL;
    if(SearchBT(pbt,ptn->key,&ploc)==true) {printf("    key %d was repeat!\n",ptn->key);return false;}

    if(ploc==NULL)pbt->ptree=ptn;
    else if(ptn->key < ploc->key)ploc->llink=ptn;
    else ploc->rlink=ptn;
    return true;
}

PBT CreatBT(FILE* fp)
{
    PBT pbt=(PBT)malloc(sizeof(BT));
    pbt->ptree=NULL;//空树
    if(fp==NULL) return pbt;
    char Aline[200];
    char* toke=(char*)malloc(50*sizeof(char));
    char sep[]=" ,; ";
    int key;int data;

    while(fgets(Aline,199,fp))
    {
        toke=strtok(Aline,sep);sscanf(toke,"%d",&key);
        toke=strtok(NULL,sep);sscanf(toke,"%d",&data);
        PTN ptn=(PTN)malloc(sizeof(TN));//申请空间
        ptn->key=key; ptn->data=data;
        ptn->llink=NULL; ptn->rlink=NULL;
        InsertBT(pbt,ptn);//____________________
    }
    return pbt;
}

int DelBTNode(PBT pbt,int key)//还是有点小问题
{
    PTN p=pbt->ptree;PTN pre=NULL;//从根节点开始

    while(p!=NULL)
    {
        if(p->key==key)//找到了待删除的节点
        {
            if(p->llink==NULL)//待删除节点没有左子女，并且pre不为空
            {
                if(pre!=NULL)
                {
                    if(pre->llink==p) pre->llink=p->rlink;
                    else pre->rlink=p->rlink;
                }
                else if(p->rlink!=NULL) pbt->ptree=p->rlink;
                else {printf("    提示：根节点删除后就变成空树\n");return -1;}
            }
            else
            {
                PTN pfindr=p->llink;PTN prefindr=p;//pfinder肯定是非空的

                while(pfindr->rlink!=NULL)
                {prefindr=pfindr;pfindr=pfindr->rlink;}

                if(prefindr==p)prefindr->llink=pfindr->llink;
                else prefindr->rlink=pfindr->llink;//完成脱链

                pfindr->rlink=p->rlink;
                pfindr->llink=p->llink;//完成对p的替代（接受p的左右子女）

                if(pre!=NULL)
                {
                    if(pre->llink==p) pre->llink=pfindr;
                    else pre->rlink=pfindr;//接入p的父节点
                }
                else pbt->ptree=pfindr;//重置根节点
            }
            free(p);
            return true;
        }
        pre=p;
        if(p->key>key) p=p->llink;
        else {p=p->rlink;}
    }
    return false;
}

int BinRound(PTN ptree)//递归定义
{
    PTN p=ptree;
    if(p==NULL) return 0;
    BinRound(p->llink);
    printf("    key %d :    data %d\n",p->key,p->data);
    BinRound(p->rlink);
    return 0;
}

int BinHeight(PTN ptree, int* ph, int* phmax)//递归定义
{
    //printf("ph=%d phmax=%d\n",*ph,*phmax);
    *ph=*ph+1;//进入树或子树
    //printf("ph=%d phmax=%d\n\n",*ph,*phmax);
    PTN p=ptree;//引用

    if(p->llink==NULL&&p->rlink==NULL)
    {
        if(*ph>*phmax)*phmax=*ph;
        *ph=*ph-1;//退回
        return 0;
    }
    if(p->llink!=NULL)BinHeight(p->llink,ph,phmax);
    printf("    key %d :    data %d     h:%d\n",p->key,p->data,*ph);
    if(p->rlink!=NULL)BinHeight(p->rlink,ph,phmax);

    *ph=*ph-1;//退回
    return 0;
}

int ShowTree(PBT pbt)
{
    PQN pqn=(PQN)malloc(sizeof(QN));
    pqn->ptn=pbt->ptree;pqn->qlink=NULL;

    PQ pq=CreatEm();
    InQueue(pq,pqn);

    int h=-1;int hmax=0;
    BinHeight(pbt->ptree,&h,&hmax);
    //printf("    h:%d hmax:%d\n",h,hmax);

    //ShowQue(pq);
    int cnt=0;//根节点0层

    int donext=1;
    printf("------------------------Tree-form------------------------\n\n");
    while(donext)
    {
        //ShowQue(pq);
        donext=InLevel(pq,cnt);//如果下一层压栈全部为空，donext=0
        OutLevel(pq,cnt,hmax);
        cnt++;
    }
    printf("\n---------------------------------------------------------\n");
    return 0;
}

int InNode(PQ pq,PTN ptn)
{
    PQN pqnl=(PQN)malloc(sizeof(QN));
    if(ptn==NULL)pqnl->ptn=NULL;
    else {pqnl->ptn=ptn->llink;}
    pqnl->qlink=NULL;
    InQueue(pq,pqnl);

    PQN pqnr=(PQN)malloc(sizeof(QN));
    if(ptn==NULL)pqnr->ptn=NULL;
    else {pqnr->ptn=ptn->rlink;}
    pqnr->qlink=NULL;
    InQueue(pq,pqnr);

    if(ptn!=NULL && (ptn->llink!=NULL || ptn->rlink!=NULL))return 1;
    else return 0;
}

int InLevel(PQ pq,int cnt)
{
    int donext=0;
    int k=1;
    for(;cnt>0;cnt--,k=k*2);
    PQN tmp=pq->f->qlink;
    for(int i=0;i<k;i++)
    {
        if(InNode(pq,tmp->ptn)==1)donext=1;
        tmp=tmp->qlink;
        if(tmp==NULL){printf("  wrong\n");break;}//__________________________________
    }
    return donext;
}

int OutLevel(PQ pq, int cnt, int ht)
{
    int b=1;
    for(int j=0;j<ht-cnt;j++)b=b*2;
    b--;

    for(int j=0;j<b;j++)printf("  ");

    int k=1;
    for(;cnt>0;cnt--,k=k*2);
    for(int i=0;i<k;i++)
    {
        PQN tmp=OutQueue(pq);
        if(tmp->ptn==NULL)printf(" No ");
        else printf(" %d ",tmp->ptn->key);
        for(int j=0;j<b;j++)printf("    ");
    }

    for(int j=0;j<cnt;j++)b=b/2;
    for(int j=0;j<b;j++)printf("  ");
    printf("\n");
    return 0;
}

PQ CreatEm(void)
{
    PQ pq=(PQ)malloc(sizeof(Q));
    pq->f=(PQN)malloc(sizeof(QN));
    pq->f->ptn=NULL;pq->f->qlink=NULL;
    pq->r=pq->f;//空的条件
    return pq;
}

int IsEmpty(PQ pq)
{
    if(pq->f==pq->r)return true;
    else return false;
}

int InQueue(PQ pq, PQN pqn)
{
    pq->r->qlink=pqn;
    pq->r=pqn;
    return 0;//完成
}

PQN OutQueue(PQ pq)
{
    if(pq->f==pq->r)return NULL;//已空
    if(pq->f->qlink==pq->r)pq->r=pq->f;//
    PQN tmp=pq->f->qlink;
    pq->f->qlink=tmp->qlink;
    return tmp;
}

PQN GetHQueue(PQ pq)
{
    return pq->f->qlink;
}

int ShowQue(PQ pq)
{
    PQN tmp=pq->f->qlink;
    printf("--------------------------queue-f------------------------\n");
    while(tmp!=NULL)
    {
        if(tmp->ptn!=NULL)printf("key %d\n",tmp->ptn->key);
        else printf("key NULL\n");
        tmp=tmp->qlink;
    }
    printf("--------------------------queue-r------------------------\n");
    return 0;
}
