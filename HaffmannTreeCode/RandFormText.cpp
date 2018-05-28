#include <cstdio>
#include <cstdlib>
#include "CodeStack.h"
#include "HaffmannTree.h"
#include "Translate.h"

void RandFormText()
{
    freopen("d:\\codefile\\datafile\\coderand.txt","w",stdout);
    for(int i=32;i<128;i++)
    {
        printf("%c %d",char(i),rand()%100);
    }
}
