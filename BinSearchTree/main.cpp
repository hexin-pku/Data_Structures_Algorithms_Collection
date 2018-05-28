#include <cstdio>
#include <cstdlib>
#include "BinSearchT.h"

using namespace std;

int RandForm(FILE* fp);
int Control(PBT pbt);
int main()
{
    FILE* fp1=fopen("d:\\codefile\\datafile\\BinTreeData.txt","w");
    RandForm(fp1);

    FILE* fp=fopen("d:\\codefile\\datafile\\BinTreeData.txt","r");
    PBT pbt=CreatBT(fp);fclose(fp);

    Control(pbt);
    ShowTree(pbt);

    free(pbt);
    return 0;
}

int RandForm(FILE* fp)
{
    int key=33;
    for(int i=32,j=1;i>3;i=i/2,j*=2)
    {
        key=i;
        for(int k=0;k<j;k++,key+=2*i)
        {
            key=key+key%3-key%2;
            printf("key is %d\n",key);
            fprintf(fp,"%d %d\n",key,(-i*i+70*i)%key);
        }
    }
    fclose(fp);
    return 0;
}

int Control(PBT pbt)
{
    printf("---------------------------------------------------------\n");
    printf("There are following options:\n");
    printf("    input 1: search a key and show its data\n");
    printf("    input 2: add a key and its data\n");
    printf("    input 3: delete a key and its data\n");
    printf("    input 4: show the dictionary in order\n");
    printf("    input 5: show the tree in level\n");
    printf("    input 0: leave\n");
    printf("---------------------------------------------------------\n\n");
    int opt=0;
    while(scanf("%d",&opt)&&opt!=0)
    {
        switch(opt)
        {
            case 1:
                {
                   int key;printf("input the key\n");scanf("%d",&key);
                   PTN ploc;
                   if(SearchBT(pbt,key,&ploc)==true)
                   {
                       printf("    the key %d is bonding with the data %d\n\n",ploc->key,ploc->data);
                   }
                   else printf("    the key is not in the dictionary\n\n");
                   break;
                }
            case 2:
                {
                    int key;int data;printf("input the key data separate by blank\n");scanf("%d %d",&key,&data);
                    PTN p=(PTN)malloc(sizeof(TN));
                    p->key=key;p->data=data;
                    p->llink=NULL;p->rlink=NULL;
                    InsertBT(pbt,p);
                    printf("    add completed\n\n");
                    break;
                }
            case 3:
                {
                    int key;printf("input the key\n");scanf("%d",&key);
                    PTN ploc;
                    if(SearchBT(pbt,key,&ploc)==true)
                    {
                        DelBTNode(pbt,key);
                        printf("    delete completed\n\n");
                    }
                    else printf("    the key is not in the dictionary\n\n");
                    break;
                }
            case 4:{BinRound(pbt->ptree);printf("\n");break;}
            case 5:{ShowTree(pbt);break;}
            default:break;
        }
        printf("---------------------------------------------------------\n");
        printf("There are following options:\n");
        printf("    input 1: search a key and show its data\n");
        printf("    input 2: add a key and its data\n");
        printf("    input 3: delete a key and its data\n");
        printf("    input 4: show the dictionary in order\n");
        printf("    input 5: show the tree in level\n");
        printf("    input 0: leave\n");
        printf("---------------------------------------------------------\n\n");
    }
    return 0;
}
