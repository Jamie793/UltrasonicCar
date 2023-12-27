#include "bluetooth.h"

extern u8 cmdData[255] = {0};
u8 bluetoothData[255] = {0};
extern u8 pos = 0;
u16 dataSize = 0;
u16 cmdSize = 0;
u16 strength = 0;
InfoType type;

void Bluetooth_Proc(void)
{

    type = 0;
    type |= cmdData[3];
    type |= cmdData[2] << 8;

    dataSize = 0;
    dataSize |= cmdData[5];
    dataSize |= cmdData[4] << 8;

    cmdSize = 0;
    cmdSize |= cmdData[7];
    cmdSize |= cmdData[6] << 8;

    char cmd[50];
    strncpy(cmd, (char *)(cmdData + 8), cmdSize);

    strength = 0;
    strength |= cmdData[8 + cmdSize + 1];
    strength |= cmdData[8 + cmdSize] << 8;

    switch (type)
    {
    case CONNECT:
        if (strncmp(cmd, "CONNECT", cmdSize) == 0)
        {
            Bluetooth_Send(CONNECT, "OK");
        }
        break;
    case OPERATION:
        if (strncmp(cmd, "LEFT", cmdSize) == 0)
        {
            Car_Move_Left();
            Car_PWM_Set(strength);
        }
        else if (strncmp(cmd, "RIGHT", cmdSize) == 0)
        {
            Car_Move_Right();
            Car_PWM_Set(strength);
        }
        else if (strncmp(cmd, "UP", cmdSize) == 0)
        {
            Car_Move_Forward();
            Car_PWM_Set(strength);
        }
        else if (strncmp(cmd, "DOWN", cmdSize) == 0)
        {
            Car_Move_Backward();
            Car_PWM_Set(strength);
        }
        else if (strncmp(cmd, "lEFT_UP", cmdSize) == 0)
        {
            Car_Turn_Left();
            Car_PWM_Set(strength);
        }
        else if (strncmp(cmd, "RIGHT_UP", cmdSize) == 0)
        {
            Car_Turn_Right();
            Car_PWM_Set(strength);
        }
        else
        {
            Car_PWM_Set(0);
        }
    case HEART:
        if (strncmp(cmd, "HEART", cmdSize) == 0)
        {
            Bluetooth_Send(HEART, "OK");
        }
    default:
        break;
    }
}

void Bluetooth_Send(u16 type, u8 *cmd)
{
    u16 cs = strlen((char *)cmd);

    bluetoothData[0] = 0x05;
    bluetoothData[1] = 0x02;
    bluetoothData[2] = (type >> 8) & 0xFF;
    bluetoothData[3] = type & 0xFF;
    u16 size = cs + 4;
    bluetoothData[4] = (size >> 8) & 0xFF;
    bluetoothData[5] = size & 0xFF;
    bluetoothData[6] = (cs >> 8) & 0xFF;
    bluetoothData[7] = cs & 0xFF;
    strncpy((char *)&bluetoothData[8], (char *)cmd, cs);
    bluetoothData[8 + cs] = 00;
    bluetoothData[8 + cs + 1] = 00;
    bluetoothData[8 + cs + 2] = 0x05;
    bluetoothData[8 + cs + 3] = 0x04;
    for (size_t i = 0; i <= 8 + cs + 3; i++)
    {
        USART_SendData(USART1, bluetoothData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            ;
    }
}
