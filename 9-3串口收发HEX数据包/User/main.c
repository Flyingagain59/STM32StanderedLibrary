#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"

uint8_t key_number;

int main(void)
{
    OLED_Init();
    Serial_Init();
	Key_Init();

	OLED_ShowString(1, 1, "TXpacket");
	OLED_ShowString(3, 1, "RXpacket");

    serial_TxPacket[0] = 0x01;
    serial_TxPacket[1] = 0x02;
    serial_TxPacket[2] = 0x03;
    serial_TxPacket[3] = 0x04;

    Serial_SendPacket();
    while(1)
    {
		key_number = Key_GetNumber();
		if (key_number == 1)
		{
			serial_TxPacket[0] ++;
  			serial_TxPacket[1] ++;
			serial_TxPacket[2] ++;
   			serial_TxPacket[3] ++;
			Serial_SendPacket();

            OLED_ShowHexNum(2, 1, serial_TxPacket[0], 2);
            OLED_ShowHexNum(2, 4, serial_TxPacket[1], 2);
            OLED_ShowHexNum(2, 7, serial_TxPacket[2], 2);
            OLED_ShowHexNum(2, 10, serial_TxPacket[3], 2);			
		}

        if (Serial_GetRxFlag() == 1)
        {
            OLED_ShowHexNum(4, 1, serial_RxPacket[0], 2);
            OLED_ShowHexNum(4, 4, serial_RxPacket[1], 2);
            OLED_ShowHexNum(4, 7, serial_RxPacket[2], 2);
            OLED_ShowHexNum(4, 10, serial_RxPacket[3], 2);
        }
    }
}
