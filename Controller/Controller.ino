//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that x have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int ledPin = 2;
int looper = 0;

int rpm = 0;
int gear = 0;
int odo = 0;
float voltage = 0;
float oilTemp = 0;
int fuel = 0;
int temp = 0;
int speed = 0;
boolean turnlight = false;
boolean neutral = false;
boolean engine = false;
boolean lowBeam = false;
boolean highBeam = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode (ledPin, OUTPUT);
}

void updateData() {
  // TODO  
}

// TODO to be removed and replaced with actual sampling
void mockData() {
  looper ++ ;
  looper ++ ;
  rpm = abs(((looper*1000)%26000)-13000);
  odo = (looper * 10) % 20000;
  voltage = abs(((looper) % 100)-50) / 10.0f + 11.0f ;
  oilTemp = ((looper * 5) % 1300) / 10.0f;
  gear = ((looper / 10) % 7);
  fuel = abs( ((looper * 2) + 50) % 200-100);
  temp = (abs(((looper * 3) % 200-100)) / 2.0f) + 60;
  speed = looper % 250;
  turnlight = ((looper / 20) % 2) > 0;
  neutral = ((looper / 20) % 2) < 1;
  engine = ((looper / 20) % 2) > 0;
  lowBeam = ((looper / 20) % 2) <1 ;
  highBeam = ((looper / 20) % 2) > 0;
  
}



void sendData(){
   
    String payload = (String) "#{"
    +"\"gear\":"+ (gear > 0 ? (String)gear : "null")
    +",\"odo\":"+odo
    +",\"rpm\":" + rpm 
    +",\"voltage\":"+voltage
    +",\"oilTemp\":"+oilTemp
    +",\"fuel\":"+fuel
    +",\"temp\":"+temp
    +",\"speed\":"+speed
    +",\"turnlight\":"+ (turnlight ? "true":"false")
    +",\"neutral\":"+ (neutral ? "true":"false")
    +",\"engine\":"+ (engine ? "true":"false")
    +",\"lowBeam\":"+ (lowBeam ? "true":"false")
    +",\"highBeam\":"+ (highBeam ? "true":"false")
    +"}#";
  if (SerialBT.hasClient()) {
    SerialBT.print(payload);
  }
  Serial.println(payload);
}


void loop() {


  mockData();
  sendData();

  digitalWrite (ledPin, SerialBT.hasClient() ? HIGH : LOW);  

  delay(50);
}
