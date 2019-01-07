void sendData(State* state, BluetoothSerial &s){   
  if (s.hasClient()) {
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
    s.print(payload);
  }
}

void printSerialTable(State* state, HardwareSerial &s){
  s.println("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
  s.println("****************************************************");
  s.println("*\tData\t\t\t\t*");
  s.println("****************************************************");
  s.println("*\t\t\t\t\t*");
  s.println("*\tRPM\tSpeed\tOdo\tFuel\t*"); 
  s.print("*\t");  
  s.print(state->rpm);      
  s.print("\t"); 
  s.print(state->speed);    
  s.print("\t"); 
  s.print(state->odo);    
  s.print("\t"); 
  s.print(state->fuel);    
  s.println("\t*");
  s.println("*\t\t\t\t\t*");
  s.println("*\tGear\tTemp\tVoltage\tOil\t*"); 
  s.print("*\t"); 
  s.print(state->gear);    
  s.print("\t"); 
  s.print(state->temp);    
  s.print("\t"); 
  s.print(state->voltage);    
  s.print("\t"); 
  s.print(state->oilTemp);    
  s.println("\t*");
  s.println("*\t\t\t\t\t*");
  s.println("****************************************************");
}

void sampleData(State* state, long pips){
  // TODO compute ODO from pips
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

  mockData(state, pips);
}

// TODO to be removed and replaced with actual sampling
void mockData(State* state, long pips) {
  state->rpm = abs(((pips*10)%26000)-13000);
  state->odo = (pips) % 20000;
  state->voltage = abs(((pips/10) % 100)-50) / 10.0f + 11.0f ;
  state->oilTemp = (((pips / 5) % 600) / 10.0f) + 60;
  state->gear = ((pips / 100) % 7);
  state->fuel = abs( ((pips / 8) + 50) % 200-100);
  state->temp = (abs((((pips / 8) % 200)-100)) / 2.0f) + 60;
  state->speed = (pips/5) % 250;
  state->turnlight = ((pips / 200) % 2) > 0;
  state->neutral = ((pips / 200) % 2) < 1;
  state->engine = ((pips / 200) % 2) > 0;
  state->lowBeam = ((pips / 200) % 2) <1 ;
  state->highBeam = ((pips / 200) % 2) > 0;
}


