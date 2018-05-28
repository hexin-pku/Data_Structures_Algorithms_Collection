#ifndef BLOCKINDEX_H_INCLUDED
#define BLOCKINDEX_H_INCLUDED

typedef struct BlockNode
{
    int data;
    BlockNode* link;
}BN, *PBN;

typedef struct BlockDate
{
    int Max;
    int Loc;
}BD,*PBD;

typedef struct BlockSeqLink
{
    int Max;
    int iniidx;//¼ÇÂ¼
    PBN Rcd;
}BSL,*PBSL;

int InterSearch(PBD pblock,int tar,int* pLoc, int N);
int IntraSearch(int* pdata,int tar,int* pLoc, int nsize);
int ShowBlock(PBD pblock,int N);

#endif // BLOCKINDEX_H_INCLUDED
