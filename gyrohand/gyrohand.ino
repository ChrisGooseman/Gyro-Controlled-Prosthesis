/*
 * Utility code for 3D printed prosthetic hand prototype controlled by Arduino and MPU6050
 * Gyroscope read gesture controls the function of the hand. Closing and opening at this stage. 
 * Code tested on Arduino Nano clone.
 * Gyroscope/Accelerometer - ITG/MPU - HiLetgo GY-521 MPU-6050
 * Motor Driver Carrier - DRV8833 - KOOBOOK DRV8833
 * Motors used are N20 motors with Encoders.
 * All electronic parts purchased on Amazon. 
 * 
 * Created March 2020 by Christopher Guzman
 * 
 * The software is free for use. 
 */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <DRV8833.h>
#include <Encoder.h> // https://github.com/PaulStoffregen/Encoder

// Setting up MPU6050
Adafruit_MPU6050 mpu;

// Setting up motor Encoders
Encoder encA(2, 3); // Interrupt pins provide better results for readings
long a_position;  // Position of encoder
int graspThreshold = 1300; // Encoder value for full grasp

// Setting up motor Drivers
DRV8833 drvOne(5, 6, 9, 10); // Two motors for four fingers

// Hand state variables
bool isOpen = true;

// Variable to see if utility is trying to be triggered
bool trigger = false;
int gyroThreshold = 15; // Y-axis gyro value that will trigger function
int timeThreshold = 2000; // Time to wait for another trigger
int timeDebounce = 100; // Small pause delay
// Variables to check if for timeThreshold
int timeStart;
int timeNow;

// Debugging function prototypes and variables
void serialMpuDebug(sensors_event_t, sensors_event_t);
void serialEncDebug();
int maxVal = 0;

// Gesture Functions
void grasp();

void setup() {
  Serial.begin(115200);

  if(!mpu.begin()){
    Serial.println("MPU Sensor Init Failed");
    while(1)
      yield();
  }
  Serial.println("Found MPU Sensor");

  // Setting MPU ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  // Read in values from MPU6050
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  //serialMpuDebug(a, g);
  //serialEncDebug();

  // Check for grasp trigger
  if(g.gyro.y >= gyroThreshold){
    timeStart = millis();
    trigger = true;
  }
  timeNow = millis();

  while(trigger && (timeNow - timeStart <= timeThreshold)){
    while(timeNow - timeStart <= timeDebounce){
      timeNow = millis();
    }
    mpu.getEvent(&a, &g, &temp);
    if(g.gyro.y >= gyroThreshold){
      grasp();
      trigger = false;
    }
    timeNow = millis();
  }
  trigger = false;
}

/****** FUNCTION DEFINITIONS ******/

/* 
 *  Print variables to serial monitor to determine Thresholds values for Gyroscope.
 * @a - accelerometer values
 * @g - gyroscope values
 */
void serialMpuDebug(sensors_event_t a, sensors_event_t g){
  
  // Serial display for debugging
  // Accelerometer values
  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 2);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 2);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 2);
  Serial.println(" m/s^2");

  // Gyroscope values  
  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print(g.gyro.x, 2);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y, 2);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z, 2);
  Serial.println(" rps");

  if(g.gyro.y > maxVal)
    maxVal = g.gyro.y;

  Serial.print("MAX: ");
  Serial.println(maxVal);
  
  delay(100);
}

/*
 * Print Encoder position for motor debugging
 */
 void serialEncDebug(){
  a_position = encA.read();

  Serial.print("A Encoder: ");
  Serial.println(a_position);
  
  delay(100);
 }

 /*
  * Function opens or closes the hand. 
  */
  void grasp(){
    // Close the hand if it is open. 
    if(isOpen){
      while(a_position <= graspThreshold){
        drvOne.motorA_fwd(200);
        drvOne.motorB_fwd(200);
        a_position = encA.read();
        Serial.println(a_position);
      }
    }// Open the hand if it is closed. 
    else{
      while(a_position >= 0){
        drvOne.motorA_rev(200);
        drvOne.motorB_rev(200);
        a_position = encA.read();
        Serial.println(a_position);
      }
    }
    // Stop motors.
    drvOne.motorA_stop();
    drvOne.motorB_stop();
    // change the state of the hand. 
    isOpen = !isOpen;
  }
