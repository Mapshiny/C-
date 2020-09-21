#ifndef BMPHEADER_H
#define BMPHEADER_H

typedef unsigned char   BYTE;	//1字节
typedef unsigned short   WORD;	//2字节
typedef unsigned long   DWORD;	//8字节
typedef long            LONG;

typedef struct 
{
        /* BITMAPFILEHEADER*/
        BYTE    bfType[2];// 位图文件的类型，必须为BM
        DWORD   bfSize;//位图文件的大小，以字节为单位
        WORD    bfReserved1;// 位图文件保留字，必须为
        WORD    bfReserved2;// 位图文件保留字，必须为
        DWORD   bfOffBits;// 位图数据的起始位置，以相对于位图文件头的偏移量表示，以字节为单位
        /* BIT MAP INFO HEADER*/
        DWORD   BiSize;// 本结构所占用字节数
        LONG    BiWidth;// 位图的宽度，以像素为单位
        LONG    BiHeight;// 位图的高度，以像素为单位
        WORD    BiPlanes;// 目标设备的级别，必须为
        WORD    BiBitCount;//每个像素所需的位数，必须是
        DWORD   BiCompression;// 位图压缩类型，必须是0(不压缩), 1(BI_RLE8压缩类型)或(BI_RLE4压缩类型)之一
        DWORD   BiSizeImage;// 位图的大小，以字节为单位
        LONG    BiXpelsPerMeter;// 位图水平分辨率，每米像素数
        LONG    BiYpelsPerMeter;// 位图垂直分辨率，每米像素数
        DWORD   BiClrUsed;// 位图实际使用的颜色表中的颜色数
        DWORD   BiClrImportant;// 位图显示过程中重要的颜色数
} BITMAPHEADER;
/*************颜色表**************/
typedef struct
{   
        unsigned char   blue;// 蓝色的亮度(值范围为-255)   
        unsigned char   green;   
        unsigned char   red;   
        char   reserved;// 保留，必须为
} RGBQUAD;
/*********压缩字符流结点**********/
#endif //BMPHEADER
