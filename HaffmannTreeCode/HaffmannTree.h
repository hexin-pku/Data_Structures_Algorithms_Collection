#ifndef HAFFMANNTREE_H_INCLUDED
#define HAFFMANNTREE_H_INCLUDED
#include <cstdio>
#include <cstdlib>

typedef struct HtNode
{
    int ww;
    int rlink;
    int llink;
    int parent;
    char ch;//Íâ²¿½áµã´æ´¢×Ö·û
}*PHtNode;

typedef struct HtTree
{
    int N;//
    int root;
    PHtNode ht;
}HT,*PHT;

void RandFormText();
PHT CreatHtTree(int N);
void InitHtTree(PHT phtree, FILE* fin);
void FindMin(PHT phtree,int creatnum, int* m1, int* m2);
PHT BuildHtTree(PHT phtree);
char* GetCode_ByLoc(int loc, PHtNode nd);
void ShowHtCode(PHT phtree);
void ShowHt(PHT phtree);

#endif // HAFFMANNTREE_H_INCLUDED
