#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Bluetooth device name

  Serial.println("ESP32 Bluetooth Serial Demo");
}

void loop() {
  if (SerialBT.available()) {
    String incomingData = SerialBT.readStringUntil('\n');
    Serial.print("Received data: ");
    Serial.println(incomingData);
  }
}
