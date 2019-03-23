

/* Includes ------------------------------------------------------------------*/
#include "FxDataParseTR.h"

FxDataParseTR::FxDataParseTR()
{
	RxBuf = new uint8_t[200]();
	data = new uint8_t[200]();
	RxBufCount = 0;
	RxBufSize = 200;
	flag = new uint8_t[2]();
	flag[0]=0xAA;
	flag[1]=0xAF;
	flaglen=2;
	flagsta=0;
	write=NULL;
	
}

FxDataParseTR::FxDataParseTR(uint16_t Bufsize)
{
		RxBuf = new uint8_t[Bufsize]();
		data = new uint8_t[Bufsize]();
		RxBufSize = Bufsize;
		RxBufCount = 0;
		flag = new uint8_t[2]();
		flag[0]=0xAA;
		flag[1]=0xAF;
		flaglen=2;
		flagsta=0;
		write=NULL;
		
}
FxDataParseTR::FxDataParseTR(uint16_t Bufsize,uint8_t flag1,uint8_t flag2)
{
		RxBuf = new uint8_t[Bufsize]();
		data = new uint8_t[Bufsize]();
		RxBufSize = Bufsize;
		RxBufCount = 0;
		flag = new uint8_t[2]();
		flag[0]=flag1;
		flag[1]=flag2;
		flaglen=2;
		flagsta=0;
		write=NULL;
		
}
FxDataParseTR::FxDataParseTR(uint16_t Bufsize,uint8_t flag1,uint8_t flag2,FUN fun)
{
		RxBuf = new uint8_t[Bufsize]();
		RxBufSize = Bufsize;
		data = new uint8_t[Bufsize];
		RxBufCount = 0;
		flag = new uint8_t[2]();
		flag[0]=flag1;
		flag[1]=flag2;
		flaglen=2;
		flagsta=0;
		write=fun;
		
}

void FxDataParseTR::reflag(uint8_t flag1,uint8_t flag2)
{
				flag[0]=flag1;
				flag[1]=flag2;
				flagsta=0;
}
uint8_t FxDataParseTR::read(uint8_t ch)
{
	if(flagsta==0){
		if(ch==flag[0]){
			flagsta=1;//
			RxBufCount = 0;
			RxBuf[RxBufCount++]=ch;
		}
	}else if(flagsta==1){
		if(RxBufCount==1 && ch==flag[1]){
			flagsta=2;
			
			RxBuf[RxBufCount++]=ch;
		}else{
			flagsta=0;
			memset(RxBuf,0,sizeof(RxBufCount));
			RxBufCount = 0;
		}
	}else if(flagsta==2){
		RxBuf[RxBufCount++]=ch;
		if(RxBufCount==4){//判断数据长度
			size=((RxBuf[2]<<8)+RxBuf[3])&0xFFFF;
			flagsta=3;
			check=0;
		}
		
	}else if(flagsta==3){
		
		RxBuf[RxBufCount++] = ch;
		
		if(RxBufCount>size+4){
			
			if(check==ch){
				
				memcpy(data,RxBuf+4,size);
				//RxBuf[RxBufCount++] = ch;
				flagsta = 0;
				memset(RxBuf, 0, sizeof(RxBufCount));
				RxBufCount = 0;
				return 0;
			}
			
		}
		check += ch;
		
	}
	return 1;
}
uint8_t FxDataParseTR::read(uint8_t *s,uint16_t len)
{
	for(int i=0;i<len;i++){
		if(read(s[i])==0){
			return 0;
		}
	}
	return 1;
}
void FxDataParseTR::send(uint8_t *s,uint16_t len){
	uint8_t sum=0;
	//uint8_t senddata[len+5];
	write(flag[0]);
	write(flag[1]);
	write((len>>8)&0xff);
	write((len)&0xff);
	uint16_t i;
	for(i=0;i<len;i++){
		write(s[i]);
		sum+=s[i];
	}
	write(sum);
	
}



