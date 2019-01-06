void sendData(State* state){   
  if (SerialBT.hasClient()) {
    String payload = (String) "#{"
    +"\"gear\":"+ (state->gear > 0 ? (String)state->gear : "null")
    +",\"odo\":"+state->odo
    +",\"rpm\":" + state->rpm 
    +",\"voltage\":"+state->voltage
    +",\"oilTemp\":"+state->oilTemp
    +",\"fuel\":"+state->fuel
    +",\"temp\":"+state->temp
    +",\"speed\":"+state->speed
    +",\"turnlight\":"+ (state->turnlight ? "true":"false")
    +",\"neutral\":"+ (state->neutral ? "true":"false")
    +",\"engine\":"+ (state->engine ? "true":"false")
    +",\"lowBeam\":"+ (state->lowBeam ? "true":"false")
    +",\"highBeam\":"+ (state->highBeam ? "true":"false")
    +"}#";
    SerialBT.print(payload);
  }
}

void printSerialTable(State* state){
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();

  Serial.print('*');
  Serial.print("\t"); 
  Serial.print("RPM");      
  Serial.print("\t"); 
  Serial.print("Speed");      
  Serial.print("\t"); 
  Serial.print("Odo");      
  Serial.print("\t"); 
  Serial.print("Fuel");      
  Serial.print("\t"); 
  Serial.println('*');

  Serial.print('*');
  Serial.print("\t"); 
  Serial.print(state->rpm);      
  Serial.print("\t"); 
  Serial.print(state->speed);    
  Serial.print("\t"); 
  Serial.print(state->odo);    
  Serial.print("\t"); 
  Serial.print(state->fuel);    
  Serial.print("\t"); 
  Serial.println('*');

  Serial.print('*');
  Serial.print("\t"); 
  Serial.print("Gear");      
  Serial.print("\t"); 
  Serial.print("Temp");      
  Serial.print("\t"); 
  Serial.print("Voltage");      
  Serial.print("\t"); 
  Serial.print("Oil");      
  Serial.print("\t"); 
  Serial.println('*');

  Serial.print('*');
  Serial.print("\t"); 
  Serial.print(state->gear);    
  Serial.print("\t"); 
  Serial.print(state->temp);    
  Serial.print("\t"); 
  Serial.print(state->voltage);    
  Serial.print("\t"); 
  Serial.print(state->oilTemp);    
  Serial.print("\t"); 
  Serial.println('*');
}


void sampleData(State* state){
  state->odo = 0;
  state->voltage = 0.0f;
  state->oilTemp = 0.0f;
  state->gear = 0;
  state->fuel = 0;
  state->temp = 0;
  state->turnlight = false;
  state->neutral = false;
  state->engine = false;
  state->lowBeam = false;
  state->highBeam = false;
}

// TODO to be removed and replaced with actual sampling
void mockData(State* state) {
  state->rpm = abs(((looper*10)%26000)-13000);
  state->odo = (looper) % 20000;
  state->voltage = abs(((looper/10) % 100)-50) / 10.0f + 11.0f ;
  state->oilTemp = ((looper / 5) % 1300) / 10.0f;
  state->gear = ((looper / 100) % 7);
  state->fuel = abs( ((looper / 8) + 50) % 200-100);
  state->temp = (abs((((looper / 8) % 200)-100)) / 2.0f) + 60;
  state->speed = (looper/5) % 250;
  state->turnlight = ((looper / 200) % 2) > 0;
  state->neutral = ((looper / 200) % 2) < 1;
  state->engine = ((looper / 200) % 2) > 0;
  state->lowBeam = ((looper / 200) % 2) <1 ;
  state->highBeam = ((looper / 200) % 2) > 0;
}

