/******************** (C) COPYRIGHT 2015 ********************
* 文件名          : CARD.h
* 版本            : V3.1.0.0
* 日期            : 2015-5-10
* 描述            : 集合了模块对卡片的所有发送命令操作
										可以选择有用的调用，无用的删除
										还有命令的解析，将命令中的卡号和数据等存到Card结构体中
*********************************************************************************/

#ifndef _CARD_H
#define _CARD_H

/* 包含文件 -------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


//#define CARDSerial            Serial
#define CARD_HAL_USARTx					huart1
#define CARD_USARTx							USART1

//-----------------------------------------------
// 模式
#define CARD_FLAG_NONE					0
#define CARD_FLAG_RESDATA  			1
#define CARD_FLAG_WAIT					2
#define CARD_FLAG_EXIST					3
#define CARD_FLAG_LEDLIGHT			4

/* 外部类型 -------------------------------------------------------------------*/
typedef struct _CMD
{
	unsigned char ReceiveBuffer[32];
	unsigned char SendBuffer[32];
	unsigned char ReceivePoint;
	unsigned char Code;
	unsigned char block_data[16];
}CMD;

typedef struct _CARD
{
	unsigned int Type;
	unsigned long UID;
	unsigned long Value;
	unsigned char KeyA[6];
	unsigned char KeyB[6];
	unsigned char BlockData[16];
}CARD;

/* 外部变量 -------------------------------------------------------------------*/
extern CARD Card;
extern CMD Cmd;
/* 外部函数 ------------------------------------------------------------------ */
void SetBound115200(void);
void SetBound9600(void);
void ReadCard(void);
void ReadBlock(unsigned char block);
void WriteBlock(unsigned char block, unsigned char *blockData);
void MakeCard(unsigned char block, unsigned long value);
void Inc(unsigned char block, unsigned long value);
void Dec(unsigned char block, unsigned long value);
void ClearCard(unsigned char block);
uint8_t UartReceiveCommand(uint8_t data);

#endif /* __Card_H */

/***************** (C) COPYRIGHT 2017 优灵科技***** END OF FILE ****************/

