/*
 * DRV8833 - Library for dual motor driver carrier DRV8833.
 * 
 * File: DRV8833.h - Class Specification
 * 
 * Created March 2020 by Christopher Guzman
 * 
 * License: For public use. 
 */

#ifndef DRV8833_H
#define DRV8833_H

#include "Arduino.h"

class DRV8833{

 public:
    DRV8833(int in1, int in2); // Constructor for one motor
    DRV8833(int in1, int in2, int in3, int in4); // Constructor for two motors.

    // Motor_A functions
    void motorA_rev();
    void motorA_fwd();
    void motorA_stop();
    // PWM control
    void motorA_rev(int speed);
    void motorA_fwd(int speed);
  
    // Motor_B functions
    void motorB_rev();
    void motorB_fwd();
    void motorB_stop();
    // PWM control
    void motorB_rev(int speed);
    void motorB_fwd(int speed);

 private:
    // member variables (Arduino Pins)
    int in1, in2; // Motor_A
    int in3, in4; // Motor_B
};

#endif