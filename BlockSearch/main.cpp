#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "BlockIndex.h"

using namespace std;
PBD Finput_seqseq(int** ppdata,int* pN,int* pnsize);

int main()
{
    int* pdata;//用于数据的记录，初始化NULL
    int N;int nsize;//索引表的长度和索引块的大小
    PBD pblock=Finput_seqseq(&pdata,&N,&nsize);//完成记录，并获得块索引表
    ///////////////////////////////////////////////


    ///////////////////////////////////////////////
    ShowBlock(pblock,N);
    ///////////////////////////////////////////////
    int tar;//带搜索目标
    printf("input number to search, and input any letter to leave\n\n");

    while(scanf("%d",&tar))//功能循环
    {
        int Loc=-1;
        int hang=-1;int lie=-1;
        if(InterSearch(pblock, tar, &hang, N)==true)
        {
            Loc=hang*nsize;
            if(IntraSearch(pdata, tar, &Loc, nsize)==true)
            {
                lie=Loc-hang*nsize;
                printf("the index of data of %d is %d\n      in block %d\n      in intra-block location (for 1 to count) %d\n      in total index %d\n",tar,Loc,hang,lie+1,nsize*hang+lie);
            }
            else printf("this number is not found!\n\n");
        }
        else printf("this number is not found!\n\n");
    }

    ///////////////////////////////////////////////
    free(pblock);
    return 0;
}

PBD Finput_seqseq(int** ppdata,int* pN, int* pnsize)
{
    int N;int nsize;
    FILE* fp=fopen("d:\\codefile\\datafile\\blocksearchdata.txt","r");
    char Aline[100];char sep[]={',',' '};
    fgets(Aline,99,fp);char toke[2];
    strncpy(toke,strtok(Aline,sep),2);
    sscanf(toke,"%d",&N);
    strncpy(toke,strtok(NULL,sep),2);
    sscanf(toke,"%d",&nsize);
    PBD pblock=(PBD)malloc(N*sizeof(BD));
    *pN=N;*pnsize=nsize;

    int* pdata=(int*)malloc(N*nsize*sizeof(int));
    fgets(Aline,100,fp);
    printf("%s\n",Aline);//______________________
    for(int i=0;i<N;i++)
    {
        int m=0;
        for(int j=0;j<nsize;j++)
        {
            int tmp=0;
            if(j==0)strncpy(toke,strtok(Aline,sep),2);
            else strncpy(toke,strtok(NULL,sep),2);
            sscanf(toke,"%d",&tmp);
            //printf("tmp=%d\n",tmp);//____________________________
            *(pdata+i*nsize+j)=tmp;
            if(tmp>m)m=tmp;
        }
        //printf("max=%d\n",m);//__________________________________
        (pblock+i)->Loc=i*nsize;
        (pblock+i)->Max=m;

        fgets(Aline,100,fp);
        if(i!=N-1)printf("%s\n",Aline);//______________________
        else printf("\n\n");
    }
    fclose(fp);
    *ppdata=pdata;//数据记录向函数外转移
    return pblock;
}
/*
int Finput_seqlink()
{
    int N;//int nsize;
    FILE* fp=fopen("d:\\codefile\\datafile\\blocksearchdata.txt","r");
    char Aline[100];char sep[]={',',' '};
    fgets(Aline,99,fp);char toke[2];
    strncpy(toke,strtok(Aline,sep),2);
    sscanf(toke,"%d",&N);
    //strncpy(toke,strtok(NULL,sep),2);
    //sscanf(toke,"%d",&nsize);
    PBSL pblocksl=(PBSL)malloc(N*sizeof(BD));
    *pN=N;*pnsize=nsize;

    //int* pdata=(int*)malloc(N*nsize*sizeof(BSL));
    fgets(Aline,100,fp);
    printf("%s\n",Aline);//______________________
    for(int i=0;i<N;i++)
    {
        int m=0;
        for(int j=0;j<nsize;j++)
        {
            int tmp=-1;
            if(j==0)strncpy(toke,strtok(Aline,sep),2);
            else strncpy(toke,strtok(NULL,sep),2);
            sscanf(toke,"%d",&tmp);
            if(tmp==-1)
            //printf("tmp=%d\n",tmp);//____________________________
            *(pdata+i*nsize+j)=tmp;
            if(tmp>m)m=tmp;
        }
        //printf("max=%d\n",m);//__________________________________
        (pblock+i)->Loc=i*nsize;
        (pblock+i)->Max=m;

        fgets(Aline,100,fp);
        if(i!=N-1)printf("%s\n",Aline);//______________________
        else printf("\n\n");
    }
    fclose(fp);
    *ppdata=pdata;//数据记录向函数外转移
    return pblock;
}
*/

