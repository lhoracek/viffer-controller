/* 
 *  lhoracek @ 2019
 */
#include "Types.h"
#include "BluetoothSerial.h"

#define BT_NAME "Viffer 750"
#define LED_PIN 2
#define REFRESH_MILLIS 40

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
long looper = 0;
long lastWrite = 0;
State state;

void setup() {
  Serial.begin(230400);
  SerialBT.begin(BT_NAME);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode (LED_PIN, OUTPUT);
}

void loop() {
  looper ++;
  int sinceLast = millis() - lastWrite;
  if(sinceLast > REFRESH_MILLIS){
    lastWrite = millis();
    mockData(&state);
    sendData(&state);
    //printSerialTable(&state);
    digitalWrite (LED_PIN, SerialBT.hasClient() ? HIGH : LOW);
  }
  delay(1);
}

