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

// LED stuff
volatile uint8 DBG_time_LED = 0;
volatile uint8 CAN_time_LED = 0;
volatile uint8 ERROR_time_LED = 0;
uint8 address = 0x04;

volatile int error = 0;

// UART stuff
char txData[TX_DATA_SIZE];

// CAN stuff
CANPacket can_recieve;
CANPacket can_send;

// Servo Stuff
int main(void)
{ 
    Initialize();
    volatile int error = 0;
    DBG_time_LED = 0;
    
    
    for(;;)
    {
        if (!PollAndReceiveCANPacket(&can_recieve)) {
            //CAN_LED_Write(OFF);
            //CAN_time_LED = 0;
            // PrintCanPacket(&can_recieve); // DEBUG
            //error = ProcessCAN(&can_recieve, &can_send);
            //DisplayErrorCode(error);
        }
        if (!error) {
            //int ID = GetPacketID(&can_recieve);
            //if (ID == ID_SCIENCE_SERVO_SET) {
            //    uint8_t servoID = GetScienceServoAngleFromPacket(&can_recieve);
            //    uint8_t angle = GetScienceServoAngleFromPacket(&can_recieve);
            //    set_servo_position(servoID, angle);
                  set_servo_position(1, 90);
                
            //}
        }
        set_servo_position(1, 90);
        sprintf(txData, "DBG LED: %x \r\n", DBG_time_LED);
        DBG_LED_Write(ON);
        DBG_time_LED++;
        if (DBG_time_LED >= 10)
            DBG_LED_Write(OFF);
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
   
    sprintf(txData, "Test 1: %x \r\n", address);
    Print(txData);  
    
    initialize_servos();
    
    sprintf(txData, "Test 2: %x \r\n", address);
    Print(txData);
    
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
void DisplayErrorCode(uint8 code) {    
    ERROR_time_LED = 0;
    ERR_LED_Write(OFF);
    
    sprintf(txData, "Error %X: ", code);
    Print(txData);

    switch(code) {
        case ERROR_INVALID_PACKET:
            Print("Packet type not recognized\r\n");
            break;
        case ERROR_INVALID_SERVO_DATA:
            Print("Wrong Servo data\r\n");
            break;
        case ERROR_INVALID_TTC:
            Print("Cannot send that data type\r\n");
            break;
        case ERROR_ESTOP:
            Print("ESTOP\r\n");
            break;
        default:
            Print(":(\r\n");
            break;
    }
}

CY_ISR(LED_Handler) {
    CAN_time_LED++;
    ERROR_time_LED++;
    
    if (ERROR_time_LED >= 10)
        ERR_LED_Write(OFF);
    if (CAN_time_LED >= 2)
        CAN_LED_Write(OFF);
}


/* [] END OF FILE */
