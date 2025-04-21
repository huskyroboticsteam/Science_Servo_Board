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

#include "FSM_Stuff.h"
#include "project.h"
#include "servo.h"

uint8_t currentState  = UNINIT;
uint8_t currentMode   = 0xFF;

void GotoUninitState() {
    currentState = UNINIT;
    // I made a function to reset the all the servos to 0, if emergency break happens, let me know if you want to be something else instead 
    reset_all_servos();
}
void SetStateTo(uint8_t state) {
    currentState = state;
}
void SetModeTo(uint8_t mode) {
    currentMode = mode;
}
uint8_t GetState(){
    return currentState;
}
uint8_t GetMode(){
    return currentMode;
}

/* [] END OF FILE */