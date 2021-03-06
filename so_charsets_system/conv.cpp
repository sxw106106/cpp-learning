#include "/tmp/iconv/include/iconv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUTLEN 255

//代码转换:从一种编码转为另一种编码
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0) return -1;
	memset(outbuf,0,outlen);
	//if (iconv(cd,pin,&((size_t *)inlen),pout,&((size_t *)outlen) )==-1) return -1;
	if (iconv(cd,pin,((size_t *)(&inlen)),pout,((size_t *)(&outlen)) )==-1) return -1;

	iconv_close(cd);
	return 0;
}
//UNICODE码转为GB2312码
int u2g(char *inbuf,int inlen,char *outbuf,int outlen)
{
	return code_convert("utf-8","gbk",inbuf,inlen,outbuf,outlen);
}
//GB2312码转为UNICODE码
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen)
{
	return code_convert("gbk","utf-8",inbuf,inlen,outbuf,outlen);
}

int main(int argc, char **argv)
{

	if(argc<3)
	{
		printf("conv3 1/0 xxx\n");
		printf("argv[2] 0 = u2g \n");
		printf("argv[2] 1 = g2u \n");
		return -1;
	}
	//char *in_utf8[6] =   {"01 26涓","02 瀹跺涵鎴愬憳", "03 姘存灉","04 鏁板瓧1鍒","05 浜斿畼" , "06 中文"};
	
	char out[OUTLEN];
	int rec ;

	if(atoi(argv[1])==0)
	{
		//unicode码转为gb2312码
		for(int i=2;i<argc;i++)
		{
			//rec = u2g(in_utf8[i],strlen(in_utf8[i]),out,OUTLEN);
			rec = u2g(argv[i],255,out,OUTLEN);			
			printf("unicode-->gb2312 in=%s out=%s\n",argv[i],out);
		}
	}
	else if(atoi(argv[1])==1)
	{
		//gb2312码转为unicode码
		for(int i=2;i<argc;i++)
		{
			//rec = u2g(in_utf8[i],strlen(in_utf8[i]),out,OUTLEN);
	
			rec = g2u(argv[i],255,out,OUTLEN);
			printf("gb2312-->unicode in=%s out=%s\n",argv[i],out);
		}
	}
	
	return 0;
}
