// By Bhargav Maniar 2019 
// Using I2C - Inter integrated circuit

#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu6050; // The device

int16_t axisX, axisY, axisZ;
int16_t gyroAxisX, gyroAxisY, gyroAxisZ;
int16_t temperature; 

char buffer[10]; // output stream buffer

void setup() {
  Wire.begin(); // Initialise I2c bus
  Serial.begin(9600); // Serial bus with baud rate of 9600
  mpu6050.initialize(); // Ignore the incorrect spelling

  // Test Connection 
  Serial.print("MPU6050 connection ");
  Serial.println(mpu6050.testConnection() ? "successful." : "failed.");
}

void loop() {
  mpu6050.getMotion6(&axisX, &axisY, &axisZ, &gyroAxisX, &gyroAxisY, &gyroAxisZ); // Read raw data from mpu6050
  temperature = mpu6050.getTemperature(); // Get the temperature value
  printValues();  // Print data in correct format
  delay(1000); // 1 Second delay
}

void printValues()
{
   Serial.print("aX = ");  Serial.print(dtostrf(axisX/16384.0, 4, 1, buffer));  Serial.println(" g, ");
   Serial.print("aY = ");  Serial.print(dtostrf(axisY/16384.0, 4, 1, buffer));  Serial.println(" g, ");
   Serial.print("aZ = ");  Serial.print(dtostrf(axisZ/16384.0, 4, 1, buffer));  Serial.println(" g, ");
   
   Serial.print("gX = ");  Serial.print(dtostrf(gyroAxisX/131.0, 6, 1, buffer));  Serial.println(" °/s, ");
   Serial.print("gY = ");  Serial.print(dtostrf(gyroAxisY/131.0, 6, 1, buffer));  Serial.println(" °/s, ");
   Serial.print("gZ = ");  Serial.print(dtostrf(gyroAxisZ/131.0, 6, 1, buffer));  Serial.println(" °/s, ");
   Serial.print("T = ");  Serial.print(dtostrf(temperature/340.0+36.53, 5, 1, buffer));  Serial.println(" °C");  
   Serial.println();
}
