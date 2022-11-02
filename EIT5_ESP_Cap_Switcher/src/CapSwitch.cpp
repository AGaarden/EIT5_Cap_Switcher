/*
 * CapSwitch.h - Library for switching capacitors in an antenna system
*/

/* Include header file */
#include "CapSwitch.h"

/*
 * Constructor
 * Output: None
 * Remarks:
 * The following function sets up the capacitor switch board
 * Base switch pin is pin 30. Only 1 switch is started at base
*/
CapSwitch::CapSwitch(uint8_t cap_amount, uint8_t pin_start) {
    /* Set variables given to constructor */
    _cap_amount = cap_amount;
    _pin_start = pin_start;

    /* Set pins as outputs */
    for(int i = 0; i < cap_amount; i++) {
        pinMode((pin_start + i), OUTPUT);
    }
}

/*
 * Name: StaticSwitch
 * Input: capCluster, capState
 * Output: Error code
 * Remarks:
 * 
*/
int CapSwitch::StaticSwitch(CapSwitch capCluster, uint8_t capState) {
    
}