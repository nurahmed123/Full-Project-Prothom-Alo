#include <Wire.h>

const int MPU_addr = 0x68; // I2C address of the MPU-6050

void setup() {
  Wire.begin(); // Initialize the I2C library
  Serial.begin(9600); // Initialize serial communication at 9600 bps
  // Wake up the MPU-6050
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  // Read raw accelerometer data
  int16_t AcX, AcY, AcZ;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // Starting register address for accelerometer data
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true); // Request 6 bytes of data

  // Read accelerometer data
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();

  // Map accelerometer values to range -250 to 250
  int mappedAcX = map(AcX, -32768, 32767, -250, 250);
  int mappedAcY = map(AcY, -32768, 32767, -250, 250);
  int mappedAcZ = map(AcZ, -32768, 32767, -250, 250);

  // Print the values
  Serial.print("Accelerometer: X = ");
  Serial.print(mappedAcX);
  Serial.print(" | Y = ");
  Serial.print(mappedAcY);
  Serial.print(" | Z = ");
  Serial.println(mappedAcZ);

  delay(100); // Delay for 100 milliseconds (0.1 seconds)
}
