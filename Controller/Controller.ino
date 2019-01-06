/* 
 *  lhoracek @ 2019
 */
#include "Types.h"
#include "BluetoothSerial.h"

#define LED_PIN 11
#define REFRESH_MILLIS 11

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;
int looper = 0;
int lastWrite = 0;
State state;


void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode (LED_PIN, OUTPUT);
}

void loop() {
  int sinceLast = millis() - lastWrite;
  if(sinceLast > REFRESH_MILLIS){
    lastWrite = millis();
    sampleData(&state);
    sendData(&state);
  }
  digitalWrite (LED_PIN, SerialBT.hasClient() ? HIGH : LOW);  
}


