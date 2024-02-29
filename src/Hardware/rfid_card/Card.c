/******************** (C) COPYRIGHT 2015 ********************
* 文件名          : Card.c
* 版本            : V3.1.0.0
* 日期            : 2015-5-10
* 描述            : 集合了模块对卡片的所有发送命令操作
										可以选择有用的调用，无用的删除
										还有命令的解析，将命令中的卡号和数据等存到Card结构体中
********************************************************************************/
/* 包含文件 -------------------------------------------------------------------*/
#include "Card.h"
#include <Message.h>
/* 宏定义 ---------------------------------------------------------------------*/
/* 本文件使用的变量 -----------------------------------------------------------*/
CARD Card;
CMD Cmd;
extern UART_HandleTypeDef CARD_HAL_USARTx;
uint8_t card_res;
uint8_t card_res_flag = CARD_FLAG_NONE;
/* 本文件使用的函数声明 -------------------------------------------------------*/
unsigned char CheckSum(unsigned char *dat, unsigned char num);
/* 本文件函数体 ---------------------------------------------------------------*/
void UartSendCommand(uint8_t *buff, uint8_t cnt);
uint8_t UartReceiveCommand(uint8_t data);
/*******************************************************************************
* 函数名         : ReadCard
* 描述           : 读卡号
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void SetBound115200(void)
{
	unsigned char len = 0x0A;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0x00;
	Cmd.SendBuffer[2] = 0x2C;
	Cmd.SendBuffer[3] = 0x00;
	Cmd.SendBuffer[4] = 0x01;
	Cmd.SendBuffer[5] = 0xC2;
	Cmd.SendBuffer[6] = 0x00;
	Cmd.SendBuffer[7] = 0x98;
	Cmd.SendBuffer[8] = 0x24;
	Cmd.SendBuffer[9] = 0x31;
	Cmd.SendBuffer[10] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}
/*******************************************************************************
* 函数名         : ReadCard
* 描述           : 读卡号
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void SetBound9600(void)
{
	unsigned char len = 0x0A;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0x00;
	Cmd.SendBuffer[2] = 0x2C;
	Cmd.SendBuffer[3] = 0x00;
	Cmd.SendBuffer[4] = 0x00;
	Cmd.SendBuffer[5] = 0x25;
	Cmd.SendBuffer[6] = 0x80;
	Cmd.SendBuffer[7] = 0x98;
	Cmd.SendBuffer[8] = 0x24;
	Cmd.SendBuffer[9] = 0x31;
	Cmd.SendBuffer[10] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}
/*******************************************************************************
* 函数名         : ReadCard
* 描述           : 读卡号
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void ReadCard(void)
{
	unsigned char len = 3;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x10;
	Cmd.SendBuffer[3] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : ReadBlock
* 描述           : 读块数据
* 输入           : block: 将要操作的块地址。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void ReadBlock(unsigned char block)
{
	unsigned char len = 4;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x11;
	Cmd.SendBuffer[3] = block;
	Cmd.SendBuffer[4] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : WriteBlock
* 描述           : 写块数据
* 输入           : block: 将要操作的块地址。
									 blockData: 将要写入的数据。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void WriteBlock(unsigned char block, unsigned char *blockData)
{
	unsigned char i;
	unsigned char len = 20;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x12;
	Cmd.SendBuffer[3] = block;

	for(i = 0; i < 16; i ++)
	{
		Cmd.SendBuffer[4 + i] = blockData[i];
	}
	Cmd.SendBuffer[20] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : MakeCard
* 描述           : 办卡。
* 输入           : block: 将要操作的块地址。
                   value: 将要操作的值。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void MakeCard(unsigned char block, unsigned long value)
{
	unsigned char len = 9;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x13;
	Cmd.SendBuffer[3] = block;
	Cmd.SendBuffer[4] = 0;	//固定为0
	Cmd.SendBuffer[5] = (unsigned char)(value >> 24);
	Cmd.SendBuffer[6] = (unsigned char)(value >> 16);
	Cmd.SendBuffer[7] = (unsigned char)(value >> 8);
	Cmd.SendBuffer[8] = (unsigned char)(value);
	
	Cmd.SendBuffer[9] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : Inc
* 描述           : 充值。
* 输入           : block: 将要操作的块地址。
                   value: 将要操作的值。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void Inc(unsigned char block, unsigned long value)
{
	unsigned char len = 8;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x15;
	Cmd.SendBuffer[3] = block;
	Cmd.SendBuffer[4] = (unsigned char)(value >> 24);
	Cmd.SendBuffer[5] = (unsigned char)(value >> 16);
	Cmd.SendBuffer[6] = (unsigned char)(value >> 8);
	Cmd.SendBuffer[7] = (unsigned char)(value);
	
	Cmd.SendBuffer[8] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : Dec
* 描述           : 扣款。
* 输入           : block: 将要操作的块地址。
                   value: 将要操作的值。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void Dec(unsigned char block, unsigned long value)
{
	unsigned char len = 8;
	
	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x16;
	Cmd.SendBuffer[3] = block;
	Cmd.SendBuffer[4] = (unsigned char)(value >> 24);
	Cmd.SendBuffer[5] = (unsigned char)(value >> 16);
	Cmd.SendBuffer[6] = (unsigned char)(value >> 8);
	Cmd.SendBuffer[7] = (unsigned char)(value);
	
	Cmd.SendBuffer[8] = CheckSum(Cmd.SendBuffer, len);
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : ClearCard
* 描述           : 清除卡
* 输入           : block: 将要操作的块地址。
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void ClearCard(unsigned char block)
{
	unsigned char len = 7;

	Cmd.SendBuffer[0] = len;
	Cmd.SendBuffer[1] = 0;
	Cmd.SendBuffer[2] = 0x14;
	Cmd.SendBuffer[3] = block;
	Cmd.SendBuffer[4] = 0x38;	
	Cmd.SendBuffer[5] = 0x52;
	Cmd.SendBuffer[6] = 0x7A;
	
	Cmd.SendBuffer[7] = CheckSum(Cmd.SendBuffer, len);	
	UartSendCommand(Cmd.SendBuffer, len);
}

/*******************************************************************************
* 函数名         : CommandProcess
* 描述           : 命令处理。
* 输入           : 无
* 输出           : 无
* 返回           : 执行结果。
                   -0   : 正确。
                   -0xFF: 无卡。
                   -0xFE: 卡操作错误。
                   -0xFD: 没有收到命令。
                   -0xFC: 余额不足。
                   -0xFB: 校验错误。
*******************************************************************************/
unsigned char CommandProcess(void)
{
	unsigned char i, status, bTemp;
	
	//接收到命令
//	bTemp = UartReceiveCommand();
	if(bTemp == 1)
	{
		//校验命令
		if(Cmd.ReceiveBuffer[Cmd.ReceiveBuffer[0]] == CheckSum(Cmd.ReceiveBuffer, Cmd.ReceiveBuffer[0]))
		{
			//获取卡号，经过UartReceiveCommnad处理过后，有以下规律
			//Cmd.ReceiveBuffer[0] 		-> 命令长度
			//Cmd.ReceiveBuffer[1] 		-> 模块地址
			//Cmd.ReceiveBuffer[2] 		-> 命令码
			//Cmd.ReceiveBuffer[3] 		-> 状态码
			//Cmd.ReceiveBuffer[4~5] 	-> 卡类型
			//Cmd.ReceiveBuffer[6~9] 	-> 卡号
			
			Card.UID = Cmd.ReceiveBuffer[9]; Card.UID <<= 8;
			Card.UID |= Cmd.ReceiveBuffer[8]; Card.UID <<= 8;
			Card.UID |= Cmd.ReceiveBuffer[7]; Card.UID <<= 8;
			Card.UID |= Cmd.ReceiveBuffer[6];
			Cmd.Code = Cmd.ReceiveBuffer[2];
			switch(Cmd.Code)
			{
				//读卡号，这里不能删除
				case 0x90:break;
				//读块数据
				case 0x91:
					for(i = 0; i < 16; i++){Card.BlockData[i] = Cmd.ReceiveBuffer[10 + i];}
					break;
				//写块数据，这里不能删除
				case 0x92: break;
				//办卡，这里不能删除
				case 0x93: break;
				//恢复卡，这里不能删除
				case 0x94: break;
				//充值
				case 0x95:
					Card.Value = Cmd.ReceiveBuffer[10];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[11];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[12];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[13];
					break;
				//扣款
				case 0x96:
					Card.Value = Cmd.ReceiveBuffer[10];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[11];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[12];
					Card.Value <<= 8;
					Card.Value |= Cmd.ReceiveBuffer[13];
					break;
				//读身份证，这里不能删除
				case 0xA0:break;
				default: status = 0xFB; break;
			}
			status = Cmd.ReceiveBuffer[3];
		}
		else {status = 0xFB;}
	}
	else{status = 0xFD;}
	return status;
}

/*******************************************************************************
* 函数名         : CheckSum
* 描述           : 命令校验。
* 输入           : 	dat : 要校验的数组。
										num : 校验的字节数。
* 输出           : 无
* 返回           : 校验值。
*******************************************************************************/
unsigned char CheckSum(unsigned char *dat, unsigned char num)
{
  unsigned char bTemp = 0, i;
  
  for(i = 0; i < num; i ++){bTemp ^= dat[i];}
  return bTemp;
}

/*******************************************************************************
* 函数名         : UartSendCommand
* 描述           : 串口发送命令
* 输入           : 	buff : 发送的数组。
										cnt  : 发送的长度
* 输出           : 无
* 返回           : 校验值。
*******************************************************************************/
void UartSendCommand(uint8_t *buff, uint8_t cnt)
{
  	uint8_t i;
	uint8_t data[20];
	uint8_t num = 0;
	
	// 设置帧头
	data[0] = 0x7F;
	for( i = 0; num < cnt+1; i++ )
	{	
		data[i+1] = buff[i];
		num++;
		if( buff[i] == 0x7F )
		{
			i += 1;
			data[i+1] = 0x7F;
		}
	}
	num = i+1;
	
	HAL_UART_Transmit( &CARD_HAL_USARTx, (uint8_t * )&data, num, 0xffff );
}

/*******************************************************************************
* 函数名         : UartReceiveCommand
* 描述           : 命令接收函数。
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
uint8_t UartReceiveCommand(uint8_t data)
{
	static uint8_t start_receive = 0;
	static uint8_t len = 0;
	static unsigned char i = 0;
	
	if( start_receive == 0 )
	{
		if( data == 0x7F )	// 帧头
		{
			start_receive = 1;
			len = 0;
			i = 0;
		}
		return 0;
	}
	else
	{
		if( len == 0 )
		{
			len = data;
		}
		else if( len > 1 )
		{
			len--;
			Cmd.ReceiveBuffer[i++] = data;
		}
		else
		{
			len = 0;
			start_receive = 0;
			// 数据处理
			if( Cmd.ReceiveBuffer[1] == 0x90 )	// 读取卡号
			{
				if( Cmd.ReceiveBuffer[2] == 0x00 )	// 数据正确
				{
					return 2;	// 读取卡号正确
				}
				else
				{
					return 3; // 数据错误
				}
			}
			if( Cmd.ReceiveBuffer[1] == 0x91 )	// 读取块
			{
				if( Cmd.ReceiveBuffer[2] == 0x00 )	// 数据正确
				{
					for( i = 0; i < 16; i++ )
					{
						Cmd.block_data[i] = Cmd.ReceiveBuffer[9+i];
					}
					

				}
				else if( Cmd.ReceiveBuffer[2] == 0xFF )	// 数据错误，没有卡
				{
					return 3; // 数据错误
				}
				else
				{
					return 3; // 数据错误
				}
			}
			else if( Cmd.ReceiveBuffer[1] == 0xAC )	// 设置波特率
			{
				if( Cmd.ReceiveBuffer[2] == 0x00 )	// 数据正确
				{
				}
				else if( Cmd.ReceiveBuffer[2] == 0xFF )	// 数据错误，没有卡
				{
					return 3; // 数据错误
				}
				else
				{
					return 3; // 数据错误
				}
			}
			else
			{
				return 0;
			}

			return 1;
		}
		return 0;
	}
}

uint8_t temp_res;
extern int32_t led_close_counts;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	temp_res = UartReceiveCommand( card_res );
	
	if( temp_res == 1 )	// 获得正确数据
	{
		card_res_flag = CARD_FLAG_RESDATA;
	}
	else if( temp_res == 2 )	// 读取卡号
	{
		if( card_res_flag != CARD_FLAG_LEDLIGHT )
		{
			card_res_flag = CARD_FLAG_EXIST;
		}
	}
	else if( temp_res == 3 )	// 数据错误
	{
		if( card_res_flag == CARD_FLAG_LEDLIGHT )
		{
			led_close_counts--;
			if( led_close_counts <= 0 )
			{
				card_res_flag = CARD_FLAG_NONE;
			}
		}
		else
		{
			card_res_flag = CARD_FLAG_NONE;
		}
		
	}

	HAL_UART_Receive_IT(&huart1,(uint8_t *)&card_res, 1);//接收一个字节
}


