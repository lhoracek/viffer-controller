/* 
 *  lhoracek @ 2019
 */
#include "Types.h"
#include "BluetoothSerial.h"

#define BT_NAME "Viffer 750"
#define LED_PIN 2
#define BT_MILLIS 40
#define CONSOLE_MILLIS 500

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
State state;

long looper = 0;
long btTimer = 0;
long consoleTimer = 0;

void setup() {
  Serial.begin(1000000);
  SerialBT.begin(BT_NAME);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode (LED_PIN, OUTPUT);
}

void loop() {
  looper ++;
  int sinceLastBT = millis() - btTimer;
  if(sinceLastBT > BT_MILLIS){
    btTimer = millis();
    sampleData(&state);
    sendData(&state, SerialBT);
  }

  int sinceLastConsole = millis() - consoleTimer;
  if(sinceLastConsole > CONSOLE_MILLIS){
    consoleTimer = millis();
    printSerialTable(&state, Serial);
  }
  
  digitalWrite (LED_PIN, SerialBT.hasClient() ? HIGH : LOW);
  delay(1);
}

