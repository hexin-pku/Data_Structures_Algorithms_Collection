#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "CodeStack.h"
#include "HaffmannTree.h"
#include "Translate.h"

using namespace std;

int main()
{
    RandFormText();//随机生成一个字母对应的频率表，保存为文件，依据这个表构建Haffmann树
    FILE* fin=fopen("d:\\codefile\\datafile\\coderand.txt","r");
    //freopen("d:\\codefile\\datafile\\HaffmannTree_outpot.txt","w",stdout);

    //////////////////////构建Haffmann树//////////////////////////////////////
    int n;
    fscanf(fin,"%d",&n);
    PHT ht=CreatHtTree(n);
    InitHtTree(ht,fin);
    BuildHtTree(ht);//完成霍夫曼树的构建
    ShowHt(ht);
    ShowHtCode(ht);
    //////////////////////////////////////////////////////////////////////////


    /////////实现控制台窗口输入文本并用Haffmann树转化为相应的代码并解码////////
    char* text=(char*)malloc(100*sizeof(char));
    while(fgets(text,99,stdin)!=NULL)
    {
        if(*text=='\n')break;

        printf("the text is\n   %s\n",text);
        char* lock=TransTextToCode(text,ht);//申请空间并将原字符串穿换成01编码
        printf("translate it to code:\n   %s\n",lock);

        char* unlock=TransCodeToText(lock,ht);//把01编码再次转化成原字符串
        printf("translate the code to text again:\n   %s\n",unlock);

        free(lock);lock=NULL;
        free(unlock);unlock=NULL;
    }
    free(text);
    //////////////////////////////////////////////////////////////////////////



    //////////////////实现导入文件把文件文本进行01编码或解码///////////////////
    FILE* ftext=fopen("d:\\codefile\\datafile\\CarData.txt","r");
    FILE* fcode_in=fopen("d:\\codefile\\datafile\\CarData_haff.txt","w");
    FILE* fcode_out=fopen("d:\\codefile\\datafile\\CarData_haff.txt","r");
    FILE* ftext_re=fopen("d:\\codefile\\datafile\\CarData_re.txt","w");

    TransTextToCode_byFile(ftext,fcode_in,ht);
    TransCodeToText_byFile(fcode_out,ftext_re,ht);
    ////////////////////////////////////////////////////////////////////////////

    return 0;
}
