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
#pragma once
   
#include "cyapicallbacks.h"
#include <stdint.h>
        
#define ON  1
#define OFF 0

#define TX_DATA_SIZE            (100u)

#define Print(message) DBG_UART_UartPutString(message)
#define PrintChar(character) DBG_UART_UartPutChar(character)
#define PrintInt(integer) DBG_UART_UartPutString(itoa(integer, txData, 10))
#define PrintIntBin(integer) DBG_UART_UartPutString(itoa(integer, txData, 2))

#define CAM_SERVO_1 0x6
#define CAM_SERVO_2 0x7

void Initialize(void);
int getSerialAddress();
void DebugPrint(char input);
void DisplayErrorCode(uint8_t code);
void set_servo_position(uint8_t servo, uint8_t position);


/* [] END OF FILE */
