
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FxDataParseTR_H
#define __FxDataParseTR_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
#include "string.h"
class FxDataParseTR
{

public:
		typedef void (*FUN)(uint8_t ch);
		uint8_t *RxBuf;
		uint8_t *data;
		uint16_t size;
		uint16_t RxBufCount;
		uint16_t RxBufSize;
		uint8_t *flag;
		uint8_t flaglen;
    FxDataParseTR();//
    FxDataParseTR(uint16_t Bufsize);//
		FxDataParseTR(uint16_t Bufsize,uint8_t flag1,uint8_t flag2);//
		void reflag(uint8_t flag1,uint8_t flag2);
		uint8_t read(uint8_t ch);
		uint8_t read(uint8_t *s,uint16_t len);
		void send(uint8_t *s,uint16_t len);
		//void (*write)(uint8_t ch);
		FUN write;
		FxDataParseTR(uint16_t Bufsize,uint8_t flag1,uint8_t flag2,FUN fun);
		
private:
	uint8_t flagsta;
	uint8_t check;
	void writenull(uint8_t ch);
	
		
};

#ifdef __cplusplus
}
#endif
#endif /*__ FxDataParseTR */