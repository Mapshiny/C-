/*黑白点二值位图游程编码压缩程序*/
  /*2008.3.20  
  作者：付闯　*/
#ifndef COMPRESSHEADER_H
#define COMPRESSHEADER_H

#include<stdio.h>
#include<stdlib.h>
// #include<conio.h>
// #include<conio.c>
#include<string.h>
#include"bmpheader.h"
const unsigned short MaxSize=16384;//14字节最大数

int compress_main(char*, char*);//压缩主程序
int decompress_main(char*, char*);//解压缩主程序

void compress(FILE *,FILE *);//压缩
void decompress(FILE *,FILE *);//解压缩
void wbuffer(FILE *,char *,int);/*将像素信息写入缓冲区*/
void buf_init(char *,int);//缓冲初始化
void rbuffer(FILE *,char *,int);//读缓冲到文件

unsigned long RLE(FILE *,char *,int,unsigned long);//游程压缩，并返回写入字节数

void decode(FILE *,char *,int);//解码，逆运算
//void bufdisplay(char *,char *,int);//打印缓冲，测试用
DWORD getBMPsize(FILE *ifp);//获取位图大小
int IsFeasible(char *,char *,int);//判断压缩可行性，可行






//void StringConvert();

#endif
