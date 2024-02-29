/*----------------Message.h-------------------
								定点打卡函数
					Version:202311.11.1441
------------------©江南大学-------------------
*/
#ifndef _MESSAGE_H__
#define _MESSAGE_H__
#include "stdio.h"
//打卡点定义区
#define RUIJIN 0xC8
#define TUPO 0xCD
#define XIANGJIANG 0xD1
#define WUJIANG 0xC7
#define ZUIYI 0xD5
#define CHISHUI 0xCB
#define JINSHAJIANG 0xC7
#define DADUHE 0xC7
#define LUDINGQIAO 0xB7
#define XUESHAN 0xC5
#define MAOGONG 0xED
#define CAODI 0xB9
#define LAZIKOU 0xBC
#define HUINING 0xBB
#define WUQIZHEN 0xCE
#define YANAN 0xD1
#define DADUHE_3 0XB6
#define WUJIANG_3 0XD5
#define JINSHAJIANG_2 0XC9

#define ENABLE 1
#define DISABLE 0
/*启动点播报设置*/
#define START_SET           DISABLE
/*播报点启用设置*/
#define RUIJIN_SET          ENABLE
#define TUPO_SET           ENABLE
#define XIANGJIANG_SET      ENABLE
#define WUJIANG_SET         ENABLE
#define ZUIYI_SET           ENABLE
#define CHISHUI_SET         ENABLE
#define JINSHAJIANG_SET      ENABLE
#define DADUHE_SET          ENABLE
#define LUDINGQIAO_SET     ENABLE
#define XUESHAN_SET         ENABLE
#define MAOGONG_SET         ENABLE
#define CAODI_SET           ENABLE
#define LAZIKOU_SET        ENABLE
#define HUINING_SET        ENABLE
#define WUQIZHEN_SET        ENABLE
#define YANAN_SET           ENABLE
#define uint8_t unsigned char 

extern const unsigned char Message_buf[];
extern const unsigned char  Message_set_num[]; 
extern uint8_t Message_num;
extern uint8_t Message_setting;
/**打卡点播报顺序设置，0-15*/
enum  Message_t
{
    Num_RUIJIN = 0,
    Num_TUPO,
    Num_XIANGJIANG,
    Num_WUJIANG,
    Num_ZUIYI,
    Num_CHISHUI,
    Num_JINSHAJIANG,
    Num_DADUHE,
    Num_LUDINGQIAO,
    Num_XUESHAN,
    Num_MAOGONG,
    Num_CAODI,
    Num_LAZIKOU,
    Num_HUINING,
    Num_WUQIZHEN,
    Num_YANAN
};
//功能实现函数
void MessageDisplaySet(uint8_t Message);
void MessageGet(unsigned char data,unsigned char data1,unsigned char data2);


#endif
