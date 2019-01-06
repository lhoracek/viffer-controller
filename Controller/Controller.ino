/* 
 *  lhoracek @ 2019
 */
#include "Types.h"
#include "BluetoothSerial.h"
#include "EEPROM.h"
#include <oled.h>

#define BT_NAME "Viffer 750"
#define LED_PIN 2
#define BT_MILLIS 40
#define DISPLAY_MILLIS 50
#define EEPROM_MILLIS 10000

#define RPM_PIN 10
#define SPEED_PIN 11

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
State state;
OLED display = OLED(5, 4, 1, 0x3C, 128, 64);

long pips = 0;
long btTimer = 0;
long displayTimer = 0;
long eepromTimer = 0;

portMUX_TYPE rpmMux = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE speedMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleRpmInterrupt() {
  // TODO compute RPM by delay micros from last interrup
  // SMOOTH by couple records
  portENTER_CRITICAL_ISR(&rpmMux);
  // TODO write to separate variable
  portEXIT_CRITICAL_ISR(&rpmMux);
}

void IRAM_ATTR handleSpeedInterrupt() {
  
  // TODO compute speed by delay micros from last
  
  portENTER_CRITICAL_ISR(&speedMux);
  // TODO record number of interrups
  // TODO compute distance by multiplying total number
  // TODO save to variables
  portEXIT_CRITICAL_ISR(&speedMux);
}

void setup() {

  Serial.begin(115200);
  SerialBT.begin(BT_NAME);
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode (LED_PIN, OUTPUT);

  pinMode(RPM_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RPM_PIN), handleRpmInterrupt, RISING);
  pinMode(SPEED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SPEED_PIN), handleSpeedInterrupt, RISING);

  display.begin(); 
  display.set_contrast(255);
  display.draw_string(0,0,"Viffer 750"); 
}

// TODO replace by timers
boolean timerPassed(long *timer, int threshold){
  long mills = millis();
  int sinceLast = mills - *timer;
  if(sinceLast > threshold){
    *timer = mills;
    return true;
  }
  return false;
}

void loop() {
  pips = millis();

  if(timerPassed(&btTimer,BT_MILLIS)){
    sampleData(&state, pips);
    sendData(&state, SerialBT);
  }

  if(timerPassed(&displayTimer,DISPLAY_MILLIS)){
    drawDisplay(&state, display);
  }
  
  digitalWrite (LED_PIN, SerialBT.hasClient() ? HIGH : LOW);
  delay(1);
}

