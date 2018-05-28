#include "Translate.h"
#include "HaffmannTree.h"
#include <cstring>

char* TransTextToCode(char* ptext, PHT phtree)
{
    char buff[200000];*buff='\0';int cnt=0;//初始化
    while(*ptext!='\0')
    {
        int i=0;
        for(;i<phtree->N;i++)
        {
            if((phtree->ht+i)->ch==*ptext)break;
        }
        if(i==phtree->N)
        {
            printf("the unknown word is there! please check!\n");
            return NULL;//___________________________________attention
        }
        ////////////////////////////////////////////向buff中加每个字符对应的代码
        char* pchcode=GetCode_ByLoc(i,phtree->ht);
        if(pchcode==NULL)return NULL;//_______________________________________attention
        if(cnt+strlen(pchcode)>200000)
        {
            printf("    临时数据溢出！超出部分的信息处理将丢失！\n");
            break;
        }//对一些预先情况的处理

        for(unsigned int i=0;i<strlen(pchcode);i++)
        {
            *(buff+cnt+i)=*(pchcode+i);
            *(buff+cnt+i+1)='\0';//这里要随时保证以'\0'为结尾，否则会错误
        }
        cnt+=strlen(pchcode);
        free(pchcode);pchcode=NULL;
        ////////////////////////////////////////////
        ptext++;
    }
    char* pcode=(char*)malloc((strlen(buff)+1)*sizeof(char));
    strncpy(pcode,buff,(strlen(buff)+1));
    return pcode;
}

char* TransCodeToText(char* pcode, PHT phtree)
{
    char buff[200000];
    int cnt=0;
    *buff='\0';

    while((*pcode=='0'|| *pcode=='1' ) && cnt<200000)
    {
        int tmp=phtree->root;
        while( (phtree->ht+tmp)->rlink!=-1 || (phtree->ht+tmp)->llink!=-1)
        {
            if(*pcode=='0'){tmp=(phtree->ht+tmp)->rlink;pcode++;}
            else if(*pcode=='1'){tmp=(phtree->ht+tmp)->llink;pcode++;}
            else {printf("？the know char is |%c| ?\n",*pcode);pcode++;exit(0);}
        }
        //printf("%c",(phtree->ht+tmp)->ch);
        *(buff+cnt)=(phtree->ht+tmp)->ch;
        *(buff+cnt+1)='\0';
        cnt++;
    }
    if(cnt==200000)printf("    临时数据溢出！超出部分的信息处理将丢失！\n");

    char* ptext=(char*)malloc((strlen(buff)+1)*sizeof(char));
    strncpy(ptext,buff,(strlen(buff)+1));
    return ptext;
}

void TransTextToCode_byFile(FILE* ftext,FILE* fcode,PHT phtree)
{
    char Aline[200];
    while(fgets(Aline,200,ftext))
    {
        char* pcode=TransTextToCode(Aline,phtree);
        fprintf(fcode,"%s",pcode);
        free(pcode);pcode=NULL;
    }
    fclose(ftext);fclose(fcode);
}

void TransCodeToText_byFile(FILE* fcode,FILE* ftext,PHT phtree)
{
    char Aline[20000];
    int cnt=0;
    while(fgets(Aline,20000,fcode))
    {
        char* ptext=TransCodeToText(Aline,phtree);
        fprintf(ftext,"%s",ptext);
    }
    fclose(ftext);fclose(fcode);
}
