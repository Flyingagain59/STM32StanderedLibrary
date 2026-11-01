#include "stm32f10x.h"
#include "LED.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "string.h"

uint8_t key_number;

int main(void)
{
	OLED_Init();
	LED_Init();
	Serial_Init();
	OLED_ShowString(1, 1, "TXpacket");
	OLED_ShowString(3, 1, "RXpacket");

    while(1)
    {
		if(RXflag == 1)
		{
			OLED_ShowString(4, 1, "                      ");
			OLED_ShowString(4, 1, serial_RxPacket);

			if(strcmp(serial_RxPacket, "LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                  ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if(strcmp(serial_RxPacket, "LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                   ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else 
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                   ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			RXflag = 0;
   		}
	}
}

