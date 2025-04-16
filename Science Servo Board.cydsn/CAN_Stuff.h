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

#include <project.h>
#include "HindsightCAN/CANLibrary.h"

// CAN Errors (0x10-0x1F)
#define ERROR_NO_NEW_PACKET 0xFFFF
#define ERROR_WRONG_MODE      0x10
#define ERROR_INVALID_MODE    0x11
#define ERROR_INVALID_TTC     0x12
#define ERROR_INVALID_PACKET  0x13
#define ERROR_INVALID_SERVO_DATA 0x14

#define SERVO_COUNT 10
#define SERVO_MAX_ANGLE 180
#define SERVO_MIN_ANGLE 0

int ReadCAN(CANPacket *receivedPacket);
int ProcessCAN(CANPacket* receivedPacket, CANPacket* packetToSend);
void PrintCanPacket(CANPacket packet);

/* [] END OF FILE */
    