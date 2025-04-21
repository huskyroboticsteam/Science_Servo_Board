/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "project.h"
#include "cyapicallbacks.h"


// UART stuff
char txData[TX_DATA_SIZE];

// CAN stuff
CANPacket received;
uint8 address = 0x04;

// Servo Stuff


int main(void)
{ 
    Initialize();
    volatile int error;
    
    for(;;)
    {
        if (!error) {
            int ID = GetPacketID(&received);
            if (ID == ID_SCIENCE_SERVO_SET) {
                uint8_t servoID = GetScienceServoAngleFromPacket(&received);
                uint8_t angle = GetScienceServoAngleFromPacket(&received);
                set_servo_position(servoID, angle);
            }
        }
    }
}

void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    
    address = getSerialAddress(); // Need to choose address for this board, I don't know what this supposed to be 
    
    DBG_UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", address);
    Print(txData);
    
    //PWM_Start();
    
    InitCAN(DEVICE_GROUP_SCIENCE, (int)address);
    initialize_servos();

}

/* Let me know which DebugPrint is needed 
void DebugPrint(char input) {
    switch(input) {
        //case 'f':
        //    sprintf(txData, "Mode: %x State:%x \r\n", GetMode(), GetState());
        //    break;
        case 'x':
            sprintf(txData, "bruh\r\n");
            break;
        default:
            sprintf(txData, "what\r\n");
            break;
    }
    Print(txData);
} */

// Using dip to get the address
int getSerialAddress() {
    int address = 0;

    address |= Dip_1_Read() << 0;
    address |= Dip_2_Read() << 1;
    address |= Dip_3_Read() << 2;
    address |= Dip_4_Read() << 3;

    return address;
}



/* [] END OF FILE */
