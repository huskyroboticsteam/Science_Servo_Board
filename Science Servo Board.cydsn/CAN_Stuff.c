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

#include <stdio.h>
#include "main.h"
#include "CAN_Stuff.h"
#include "FSM_Stuff.h"
#include "HindsightCAN/CANLibrary.h"

extern char txData[TX_DATA_SIZE];
extern uint8 address;

//Reads from CAN FIFO and changes the state and mode accordingly
int ProcessCAN(CANPacket* receivedPacket, CANPacket* packetToSend) {
    uint16_t packageID = GetPacketID(receivedPacket);
    uint8_t sender_DG = GetSenderDeviceGroupCode(receivedPacket);
    uint8_t sender_SN = GetSenderDeviceSerialNumber(receivedPacket);
    int32_t data = 0;
    int err = 0;
    
    switch(packageID){
            
       // Common Packets
       case(ID_ESTOP):
           Print("\r\n\r\nSTOP\r\n\r\n");
           // stop all movement
           GotoUninitState();
           err = ESTOP_ERR_GENERAL;
           break;
        case(ID_SCIENCE_SERVO_SET): {
            CAN_LED_Write(ON);
            uint8_t servoID = receivedPacket->data[1];
            uint8_t degrees = receivedPacket->data[2];
            
            if(servoID == 0 || servoID > SERVO_COUNT || degrees > SERVO_MAX_ANGLE || degrees < SERVO_MIN_ANGLE) {
                err = ERROR_INVALID_SERVO_DATA;
            }
            break;
        }
        
        
        case(ID_TELEMETRY_PULL):            
            switch(DecodeTelemetryType(receivedPacket))
            {
                // USE CONSTANTS FOR CASES
                case(0):
                    data = 105;
                    break;
                default:
                    err = ERROR_INVALID_TTC;
                    break;
            }
            
            // Assemble and send packet
            AssembleTelemetryReportPacket(packetToSend, sender_DG, sender_SN, receivedPacket->data[3], data);
            
            if (err == 0)
                SendCANPacket(packetToSend);
            
            break;
            
        default: //recieved Packet with non-valid ID
            // could be due to corruption, don't uninit
            return ERROR_INVALID_PACKET;
    }
    
    return err;
}

void PrintCanPacket(CANPacket packet){
    for(int i = 0; i < packet.dlc; i++ ) {
        sprintf(txData,"Byte%d %x   ", i+1, packet.data[i]);
        Print(txData);
    }

    sprintf(txData,"ID:%x %x %x\r\n",packet.id >> 10, 
        (packet.id >> 6) & 0xF , packet.id & 0x3F);
    Print(txData);
}


/* [] END OF FILE */
