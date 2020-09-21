#include "compressheader.h"
#include <qdebug.h>

int compress_main(char* ifilename, char* ofilename)
{
    FILE *ifp,*ofp,*ffp;
    char choic;

    /*
    ------------------------------
    char *ifilename,*ofilename;
    ifilename=(char *)malloc(1);
    ofilename=(char *)malloc(1);
    printf("a.压 缩 b.解压缩 ");
    choic=getchar();
    --------------------------------
    */

    choic = 'a';
    if(choic=='a')
    {
    	/*
       -----------------------
       printf("请输入压缩(Compress)源文件名:");
       scanf("%s",ifilename);
       printf("请输入压缩(Compress)输出文件名:");
       scanf("%s",ofilename);
	   -------------------------------------
	   */

       if((ifp=fopen(ifilename,"rb"))==nullptr)
       {
           qDebug() << "无法打开文件!" ;
           return -1;
       }
       if((ofp=fopen(ofilename,"wb"))==nullptr)
       {
           qDebug() << "无法创建文件!" ;
           return -1;
       }
       compress(ifp,ofp);
       qDebug() << "文件" << ifilename << "成功压缩为文件" << ofilename;
       fclose(ifp);
       fclose(ofp);
    }
    //解压缩
    else
    {
       printf("请输入解压缩(Decompress)源文件名:");
       scanf("%s",ifilename);
       printf("请输入解压缩(Decompress)输出文件名:");
       scanf("%s",ofilename);
       if((ofp=fopen(ifilename,"rb"))==nullptr)
       {
           printf("无法打开文件!");
           getchar();
           return 1;
       }
       if((ffp=fopen(ofilename,"wb"))==nullptr)
       {
           printf("无法创建文件!");
           getchar();
           return 1;
       }
       decompress(ofp,ffp);
       printf("文件%s成功解压缩为文件%s!",ifilename,ofilename);
       fclose(ofp);
       fclose(ffp);
    }
    return 0;
}

int decompress_main()
{

}


DWORD getBMPsize(FILE *ifp)
{
    DWORD size;
    fseek(ifp,2,0);
    fread(&size,4,1,ifp);
    rewind(ifp);
    return size;
}
/**************************缓冲区初始化****************************/
void buf_init(char *buffer,int size)
{
    memset(buffer,-1,size);
}
/******************************************************************************************/
/************************************以下是压缩算法****************************************/
/******************************************************************************************/
void compress(FILE *ifp,FILE *ofp)
{
          
    unsigned long input,output=0;
    input=getBMPsize(ifp);
    char buffer[MaxSize];/*缓冲区*/
    while(!feof(ifp))
    {
        wbuffer(ifp,buffer,MaxSize);
        output=RLE(ofp,buffer,MaxSize,output);
    }
    qDebug() << "Compressing Rate= " << output*100.0/input ;
    //printf("%d",sizeof(OutUnit));
}

/************************************将二进制的位写入缓冲区***************************************/
void wbuffer(FILE *ifp,char *buffer,int size)
{
    char *tpbuf=buffer;
    unsigned char temp=0;
    int i;
    /* fseek(ifp,62,0); */
    buf_init(buffer,size);
      
    while(size>0&&!feof(ifp))
    {
        temp=fgetc(ifp);/*每次取8个像素*/
        if(feof(ifp))break;//BUG之所在,必须要再读一个字节,函数才能判断文件尾
           
        for(i=7;i>=0;--i,++tpbuf)
        {
            *tpbuf=(temp>>i)&1;/*写入一行转换为二进制,高位在行左边*/
            /* printf("%d",buffer[MaxSize-size][j]); */
        }
        size-=8;
           
    }
    //bufdisplay("codisplay.txt",buffer,MaxSize);
    //getchar();
}
/**********************************对缓冲区中数值进行编码，并返回码序列**************************************/
unsigned long RLE(FILE *ofp,char *buffer,int size,unsigned long output)
{
	unsigned short ounit=0,count=0;
	int i=0;             
	char temp;
	char *tpbuf=buffer;
	  
	temp=0;
	  
	while(*tpbuf!=-1&&(i<size-1))//确保不超出缓冲区并且数据有效
	{
	    temp=*tpbuf;
	    ounit=count=0;
	    //currentbit=temp;
	    if(!IsFeasible(tpbuf,buffer,MaxSize))
	    {
	        int k=0;
	        for(k=13;k>=0&&*tpbuf!=-1&&tpbuf!=(buffer+size-1);--k,++tpbuf,++i)//！！！！越界了！！！！
	        {
	            count+=(*tpbuf)<<k;
	        }
	        ounit=count;//不压缩
	        //ounit->id=0;//任意值
	        fwrite(&ounit,sizeof(unsigned short),1,ofp);
	              
	        }
	        else
	        {
	            count=0;
	            ounit+=1<<15;//压缩
	            ounit+=temp<<14;
	            while(*tpbuf==temp&&i<size-1)
	            {
	                ++count;
	                ++tpbuf;
	                ++i;
	            }
	            ounit+=count;
	            fwrite(&ounit,sizeof(unsigned short),1,ofp);
	        }
	        output+=sizeof(unsigned short);
	  }
	  
	  return output;
}
int IsFeasible(char *current,char *buffer,int size)
{
    char i,id;
    int distance=current-buffer;
    for(i=0,id=*current;i<16;++i,++distance)
    {
        if(*(current+i)!=id||*(current+i)==-1||distance>(size-1))return 0;
    }
    return 1;
}
/******************************************************************************************/
/************************************以下是解压缩算法****************************************/
/******************************************************************************************/
void decompress(FILE *ifp,FILE *ofp)
{
    char buffer[MaxSize];
    buf_init(buffer,MaxSize);
    while(!feof(ifp))
    {
        //fgetc(ifp);
        decode(ifp,buffer,MaxSize);
        rbuffer(ofp,buffer,MaxSize);
        //printf("Waiting..... ");getchar();
    }
        
}
/********************************根据编码规则进行解码************************************/
void decode(FILE *ifp,char *buffer,int size)
{
    int i=0;
    unsigned short temp=0;
    char *tpbuf=buffer;
                
    buf_init(buffer,MaxSize);
    while(i<size-1&&!feof(ifp))
    {
        fread(&temp,sizeof(unsigned short),1,ifp);
        if(feof(ifp))   break;//BUG之所在,解决了,没有这句就会多读32位
        if(temp>(1<<15))//第一位为１压缩，否则按非压缩处理
        {
           if(((temp>>14)&1)==1)//第２位为１，则像素为１,否则为
               //一定要将操作数移位和１与，不可将１移位和操作数与
           {
                unsigned short num1=temp&((1<<14)-1);
                for(;num1>0&&i<size;--num1,++i,++tpbuf)
                    *tpbuf=1;
           }
           else
           {
                unsigned short num0=temp&((1<<14)-1);
                for(;num0>0&&i<size;--num0,++i,++tpbuf)
                    *tpbuf=0;
           }
        }
        else//非压缩
        {
               int k;
               for(k=13;k>=0&&(tpbuf-buffer)<size-1;--k,++tpbuf,++i)//如果不够14位有几位取几位
               {
                   //if(*)
                   *tpbuf=(temp>>k)&1;
               }
        }
        //int a=temp;
   } 
    
   //bufdisplay("dedisplay.txt",buffer,MaxSize); 
}
/*******************************读取缓冲区中二进制，输出到文件**********************************/
void rbuffer(FILE *ofp,char *buffer,int size)
{
    unsigned char temp=0;
    int i=0;
    char *tpbuf=buffer;
    
    while(size>0&&*tpbuf!=-1)
    {
       for(i=7;i>=0;--i,++tpbuf)//将位信息转换为１字节整数，并输出到文件
       {
            /* printf("%d ",buffer[MaxSize-size][i]<<i); */
            if(*tpbuf==-1)break;
            /* getchar(); */
            temp+=*tpbuf<<i;
            --size;
       }
       fputc(temp,ofp);
       temp=0;
    }
}

/*void bufdisplay(char *s,char *buffer,int size)
{
    int i;
    FILE *fp=fopen(s,"wt");
    for(i=0;i<size;++i)
    {
      fprintf(fp,"%d",buffer[i]);
      //fprintf(fp," ");
    }
    fclose(fp);  
}*/
