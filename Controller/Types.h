#ifndef Type_h
#define Types_h

typedef struct {
  int rpm;
  int gear;
  int odo;
  float voltage;
  float oilTemp;
  int fuel;
  int temp;
  int speed;
  boolean turnlight;
  boolean neutral;
  boolean engine;
  boolean lowBeam;
  boolean highBeam;
} State;

#endif
