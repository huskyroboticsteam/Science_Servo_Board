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
#include "PCA9685.h"
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "cyapicallbacks.h"
#include "CAN_Stuff.h"
#include "CANScience.h"
#include "DBG_UART.h"

#define CE_SERVO 0 
#define SP_SERVO 1
#define TAMP_SERVO 2
#define FLT_SERVO 3
#define HOLE_SERVO 4 
#define MF_SERVO 5
#define SSC_SERVO 6
#define SERVO8 7 // No function so far
#define SERVO9 8 // No function so far
#define SERVO10 9 // No function so far

#define SERVO_COUNT 10
#define SERVO_MAX_ANGLE 180
#define SERVO_MIN_ANGLE 0

void initialize_servos(void);
int set_servo_position(uint8_t servo, uint8_t degrees);
int get_servo_position(int servo);
void reset_all_servos();

/* [] END OF FILE */
