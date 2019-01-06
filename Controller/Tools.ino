void sendData(State* state){   
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
  if (SerialBT.hasClient()) {
    SerialBT.print(payload);
  }
  Serial.println(payload);
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
  looper ++ ;
  looper ++ ;
  state->rpm = abs(((looper*1000)%26000)-13000);
  state->odo = (looper * 10) % 20000;
  state->voltage = abs(((looper) % 100)-50) / 10.0f + 11.0f ;
  state->oilTemp = ((looper * 5) % 1300) / 10.0f;
  state->gear = ((looper / 10) % 7);
  state->fuel = abs( ((looper * 2) + 50) % 200-100);
  state->temp = (abs(((looper * 3) % 200-100)) / 2.0f) + 60;
  state->speed = looper % 250;
  state->turnlight = ((looper / 20) % 2) > 0;
  state->neutral = ((looper / 20) % 2) < 1;
  state->engine = ((looper / 20) % 2) > 0;
  state->lowBeam = ((looper / 20) % 2) <1 ;
  state->highBeam = ((looper / 20) % 2) > 0;
}

