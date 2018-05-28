#ifndef TRANSLATE_H_INCLUDED
#define TRANSLATE_H_INCLUDED
#include "HaffmannTree.h"
#include "CodeStack.h"
#include <cstdio>
#include <cstdlib>

char* TransTextToCode(char* ptext, PHT phtree);
char* TransCodeToText(char* pcode, PHT phtree);
void TransTextToCode_byFile(FILE* ftext,FILE* fcode,PHT phtree);
void TransCodeToText_byFile(FILE* fcode,FILE* ftext,PHT phtree);

#endif // TRANSLATE_H_INCLUDED
