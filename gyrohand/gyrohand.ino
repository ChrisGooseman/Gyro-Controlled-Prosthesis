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

// Debugging functions prototypes
void serialDebug(sensors_event_t, sensors_event_t);

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
  
  serialDebug(a, g);
}

/****** FUNCTION DEFINITIONS ******/

/* Print variables to serial monitor to determine Thresholds values for Gyroscope.
 * @a - accelerometer values
 * @g - gyroscope values
 */
void serialDebug(sensors_event_t a, sensors_event_t g){
  
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
  
  delay(100);
}
