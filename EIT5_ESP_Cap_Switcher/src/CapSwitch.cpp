/*
 * CapSwitch.h - Library for switching capacitors in an antenna system
*/

/* Include header file */
#include "CapSwitch.h"

/* Include header file for tables */
#include "CapSwitchTables.h"

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
 * Name: FindTableIndex
 * Input: val
 * Output: Index
*/
int CapSwitch::FindTableIndex(uint8_t val) {
    
    for(int i = 0; i < tableSize; i++) {
        if(CapTable[i][0] == val) {
            return i;
        }
    }
}

/*
 * Name: StaticSwitch
 * Input: capState
 * Output: Error code
 * Remarks:
 * 
*/
int CapSwitch::ClusterStaticSwitch(uint8_t capState) {
    
    unsigned char b;
    int tableIndex = FindTableIndex(capState);
    
    for(int j = _cap_amount - 1; 0 <= j; j--) {
        b = (CapTable[tableIndex][1] >> j) & 0b01;
        uint8_t capPin = _pin_start + j;

        if(b) {
            digitalWrite(capPin, HIGH);
        }
        else {
            digitalWrite(capPin, LOW);
        }
    }
    
}

/*
 * Name: SingleStaticSwitch
 * Input: capCluster, capState
 * Output: Error code
 * Remarks:
*/
int CapSwitch::SingleStaticSwitch(uint8_t capState) {

    digitalWrite((_pin_start), !_single_pin_state);
    _single_pin_state = !_single_pin_state;

    return 0;
}

/*
 * Name: PWMSwitch
*/
int CapSwitch::SinglePWMSwitch(uint8_t pwmVal) {

}

/*
 * Name: TestSwitches
 * Input: capCluster
 * Output: Error code
 * Remarks: uses CapTableTest LUT
*/
int CapSwitch::TestSwitches() {

    /* 16 test cases in the LUT */
    for(int i = 0; i < 16; i++) {

        unsigned char b;
        for(int j = 3; 0 <= j; j--) {
            b = (CapTableTest[i][1] >> j) & 0b01;
            uint8_t capPin = _pin_start + j;

            if(b) {
                digitalWrite(capPin, HIGH);
            }
            else {
                digitalWrite(capPin, LOW);
            }
        }
        delay(1000);
    }

    return 0;
}