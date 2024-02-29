#include "Message.h"
/*----------------Message.c--------------
					Version:202311.11.1441
				   JiangNan University
------------------------------------------
*/
const unsigned char Message_buf[]={RUIJIN,TUPO,XIANGJIANG,WUJIANG,ZUIYI,CHISHUI,JINSHAJIANG,DADUHE,LUDINGQIAO,XUESHAN,MAOGONG,CAODI,LAZIKOU,HUINING,WUQIZHEN,YANAN};
const unsigned char  Message_set_num[] = {RUIJIN_SET,TUPO_SET,XIANGJIANG_SET,WUJIANG_SET,ZUIYI_SET,CHISHUI_SET,JINSHAJIANG_SET,DADUHE_SET,LUDINGQIAO_SET,XUESHAN_SET,MAOGONG_SET,CAODI_SET,LAZIKOU_SET,HUINING_SET,WUQIZHEN_SET,YANAN_SET};
uint8_t Message_num = 16;
uint8_t Message_setting = 3;
void MessageDisplaySet(uint8_t Message)
{
   
    // if(Message == 0xff)
    // {
    //     temp_card.Card_Set = ENABLE;
    // }
	 if(Message == 100)
	 {}
    else if(Message_set_num[Message] == ENABLE)
   {
       Message_setting = ENABLE;
   }
   else if (Message_set_num[Message] == DISABLE)
   {
       Message_setting = DISABLE;
   }
}
void MessageGet(unsigned char data,unsigned char data1,unsigned char data2)
{
    uint8_t temp_Message = 100;
    uint8_t count = 0;
    for(count = 0;count<Message_num;count++)
    {
        if(Message_buf[count] == data)
        {
            if(count == Num_JINSHAJIANG)
            {
                if(data1 == JINSHAJIANG_2)
                {
                    temp_Message = Num_JINSHAJIANG;
                    break;
                }
            }
            else if(count == Num_WUJIANG)
            {
                if(data2 == WUJIANG_3)
                {
                    temp_Message = Num_WUJIANG;
                    break;
                }
            }
            else if(count == Num_DADUHE)
            {
                if(data2 == DADUHE_3)
                {
                    temp_Message = Num_DADUHE;
                    break;
                }
            }
            else
            {
                temp_Message = count;
                break;
            }
        }
    }
        MessageDisplaySet(temp_Message);
}

