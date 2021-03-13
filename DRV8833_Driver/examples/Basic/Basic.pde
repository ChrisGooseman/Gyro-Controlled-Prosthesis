/*
 * DRV8833 Library test - Basic Example
 * 
 * File: Basic.pde - Test for connecting one motor to DRV8833 motor driver 
 * carrier.
 * Test completed using an Arduino NanoV3.0 clone with ATmega328P
 * in1 and in2 pins on DRV8833 are connected to pins D3 and D2 of Nano
 * respectively. DRV8833 is powered externally with 10V. Positive connection
 * of power source is attached to the DRV8833's VCC pin. Negative connection
 * of power source is attached to the DRV8833's GND pin. Nano is also grounded to
 * to the DRV8833's GND pin.
 * 
 * Created March 2020 by Christopher Guzman
 * 
 * License: For public use. 
 */

#include <DRV8833.h>

// Instantiate DRV8833 object - Replace pins if needed.
DRV8833 driver(3, 2);

void setup(){
    Serial.begin(115200);

    while(!Serial); // Wait for Serial connection

}

void loop(){
    Serial.println("Moving Forward");
    // Move Motor Forward
    driver.motorA_fwd();
    delay(500);

    // Stop the motor
    Serial.println("Stopping Motor");
    driver.motorA_stop();
    delay(200);

    Serial.println("Moving in Reverse");
    driver.motorA_rev();
    delay(500);

    // Stop the motor
    Serial.println("Stopping Motor");
    driver.motorA_stop();
    delay(200);
}