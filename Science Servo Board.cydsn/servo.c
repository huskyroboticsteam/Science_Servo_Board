/* File:         sensor.c
 * Authors:      
 * Organization: Husky Robotics Team
 * 
 * This file includes fuction implementations for the servos on the 
 * Science Board including continuous servos
 */
#include <stdint.h>
#include "CANLibrary.h"
#include "CANScience.h"
#include "PCA9685.h"
#include "project.h"
#include "servo.h"

char txData[TX_DATA_SIZE];

int16 current_servo_values[10] = {};

void initialize_servos() {
    pca_init();
    
}

// sets the PCA duty cycle for positional servos 1-10
// degrees is from 0 to 180
int set_servo_position(uint8_t servo, uint8_t degrees){
    float32 duty;
    if(degrees > SERVO_MAX_ANGLE) degrees = SERVO_MAX_ANGLE;
	if(degrees < SERVO_MIN_ANGLE) degrees = SERVO_MIN_ANGLE;
	if (servo < 0 || servo > SERVO_COUNT){ 
        return 1;
    }
    
    current_servo_values[servo] = degrees;
    
    duty = (degrees/180.0)*5 + 5;
    sprintf(txData, "Duty: %f \r\n", duty);
    sprintf(txData, "Servo: %hhu \r\n", servo);
   	setPWMFromDutyCycle(servo, duty);
    return 0;
}

int get_servo_position(int servo){
    if (servo < 0 || servo >= SERVO_COUNT){ 
        return 1;
    }
    return current_servo_values[servo];
}

void reset_all_servos() {
    for (int i = 0; i < SERVO_COUNT; i++) {
        current_servo_values[i] = 0;
        set_servo_position(i, 0);
    }
}

/* [] END OF FILE */
