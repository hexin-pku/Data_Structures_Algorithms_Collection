typedef struct TNode
{
    int key;
    int data;
    TNode* llink;
    TNode* rlink;
}TN,* PTN;

typedef struct BinTree
{
    TNode* ptree;
}BT,*PBT;

typedef struct QNode
{
    PTN ptn;
    QNode* qlink;
}QN,*PQN;

typedef struct TQueue//
{
    PQN f;//head结点
    PQN r;//指向队尾元素
}Q,*PQ;

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

#endif // QUEUE_H_INCLUDED
