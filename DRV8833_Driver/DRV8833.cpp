/*
 * DRV8833 - Library for dual motor driver carrier DRV8833.
 * 
 * File: DRV8833.cpp - Class Implementation
 * 
 * Created March 2020 by Christopher Guzman
 * 
 * License: For public use. 
 */

#include "Arduino.h"
#include "DRV8833.h"

// Single motor constructor
DRV8833::DRV8833(int in1, int in2){
    // initialize motor_A pins and member variables
    this->in1 = in1;
    this->in2 = in2;
    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);

    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, LOW);
}

// Dual motor constructor
DRV8833::DRV8833(int in1, int in2, int in3, int in4){
    // initialize motor_A and motor_B pins and member variables
    this->in1 = in1;
    this->in2 = in2;
    this->in3 = in3;
    this->in4 = in4;

    pinMode(this->in1, OUTPUT);
    pinMode(this->in2, OUTPUT);
    pinMode(this->in3, OUTPUT);
    pinMode(this->in4, OUTPUT);

    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, LOW);
    digitalWrite(this->in3, LOW);
    digitalWrite(this->in4, LOW);
}

/*********************************/
/****    MOTOR A FUNCTIONS    ****/
/*********************************/

void DRV8833::motorA_rev(){
    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, HIGH);
}

void DRV8833::motorA_fwd(){
    digitalWrite(this->in1, HIGH);
    digitalWrite(this->in2, LOW);
}

void DRV8833::motorA_stop(){
    digitalWrite(this->in1, HIGH);
    digitalWrite(this->in2, HIGH);
}

// PWM Functions
void DRV8833::motorA_rev(int speed){
    digitalWrite(this->in1, LOW);
    analogWrite(this->in2, speed);
}

void DRV8833::motorA_fwd(int speed){
    analogWrite(this->in1, speed);
    digitalWrite(this->in2, LOW);
}

/*********************************/
/****    MOTOR B FUNCTIONS    ****/
/*********************************/

void DRV8833::motorB_rev(){
    digitalWrite(this->in3, LOW);
    digitalWrite(this->in4, HIGH);
}

void DRV8833::motorB_fwd(){
    digitalWrite(this->in3, HIGH);
    digitalWrite(this->in4, LOW);
}

void DRV8833::motorB_stop(){
    digitalWrite(this->in3, HIGH);
    digitalWrite(this->in4, HIGH);
}

// PWM Functions
void DRV8833::motorB_rev(int speed){
    digitalWrite(this->in3, LOW);
    analogWrite(this->in4, speed);
}

void DRV8833::motorB_fwd(int speed){
    analogWrite(this->in3, speed);
    digitalWrite(this->in4, LOW);
}