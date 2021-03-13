/*
 * DRV8833 Library test - Speed Example
 * 
 * File: Speed.pde - Test for connecting one motor to DRV8833 motor driver 
 * carrier using PWM.
 * Test completed using an Arduino NanoV3.0 clone with ATmega328P
 * in1 and in2 pins on DRV8833 are connected to pins D3 and D5 of Nano
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
DRV8833 driver(3, 5);

void setup(){
    Serial.begin(115200);

    while(!Serial); // Wait for Serial Connection
}

void loop(){
    Serial.println("Speeding up");
    for(int i = 0; i <= 255; i++){
        driver.motorA_fwd(i);
        delay(50);
    }

    delay(500);

    Serial.println("Slowing down");
    for(int i = 255; i >= 0; i--){
        driver.motorA_fwd(i);
        delay(50);
    }
    
    Serial.println("Motor Stopped");
    driver.motorA_stop();
    delay(500);
}
